@** Another Approach for Modbus RTU Support.

\noindent The original code for dealing with Modbus RTU devices had a number of
limitations. It was awkward to configure, limited to using a single device per
bus, supported a small number of channels, and only worked with fixed point
numeric representations. The following sections are an initial draft of a more
flexible reworking of Modbus RTU support which should be easier to extend to
cover Modbus TCP, allows a wider range of numeric representations, and allows
for the use of any number of devices on the bus and any number of channels.

Initial support is focused on function 3 and 4 registers with a known
configuration. Outputs and the ability to configure inputs based on the values
at other addresses will be added later. Modbus TCP support is also planned.

Once feature parity with the old Modbus code is reached, the older code will be
removed.

Rather than use a single configuration widget for the entire bus, this is now
split to use one configuration widget for the bus and another widget for an
input channel.

@<Class declarations@>=
class ModbusNGConfWidget : public BasicDeviceConfigurationWidget
{
    Q_OBJECT
    public:
        Q_INVOKABLE ModbusNGConfWidget(DeviceTreeModel *model, const QModelIndex &index);
    private slots:
        void updatePort(const QString &value);
        void updateBaudRate(const QString &value);
        void updateParity(int value);
        void updateFlowControl(int value);
        void updateStopBits(int value);
        void addInput();
    private:
        ParitySelector *m_parity;
        FlowSelector *m_flow;
        StopSelector *m_stop;
};

@ The configuration widget for the bus only handles the details of the serial
port and allows adding child nodes representing input channels.

@<ModbusNG implementation@>=
ModbusNGConfWidget::ModbusNGConfWidget(DeviceTreeModel *model, const QModelIndex &index) :
    BasicDeviceConfigurationWidget(model, index), m_parity(new ParitySelector),
    m_flow(new FlowSelector), m_stop(new StopSelector)
{
    QFormLayout *layout = new QFormLayout;
    PortSelector *port = new PortSelector;
    BaudSelector *baud = new BaudSelector;
    QPushButton *newInput = new QPushButton(tr("Add Input Channel"));
    layout->addRow(QString(tr("Port:")), port);
    layout->addRow(QString(tr("Baud rate:")), baud);
    layout->addRow(QString(tr("Parity:")), m_parity);
    layout->addRow(QString(tr("Flow control:")), m_flow);
    layout->addRow(QString(tr("Stop bits:")), m_stop);
    layout->addRow(newInput);

    @<Get device configuration data for current node@>@;

    for(int i = 0; i < configData.size(); i++)
    {
        node = configData.at(i).toElement();
        if(node.attribute("name") == "port")
        {
            int idx = port->findText(node.attribute("value"));
            if(idx >= 0)
            {
                port->setCurrentIndex(idx);
            }
            else
            {
                port->addItem(node.attribute("value"));
            }
        }
        else if(node.attribute("name") == "baud")
        {
            baud->setCurrentIndex(baud->findText(node.attribute("value")));
        }
        else if(node.attribute("name") == "parity")
        {
            m_parity->setCurrentIndex(m_parity->findData(node.attribute("value")));
        }
        else if(node.attribute("name") == "flow")
        {
            m_flow->setCurrentIndex(m_flow->findData(node.attribute("value")));
        }
        else if(node.attribute("name") == "stop")
        {
            m_stop->setCurrentIndex(m_stop->findData(node.attribute("value")));
        }
    }

    updatePort(port->currentText());
    updateBaudRate(baud->currentText());
    updateParity(m_parity->currentIndex());
    updateFlowControl(m_flow->currentIndex());
    updateStopBits(m_stop->currentIndex());
    connect(port, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePort(QString)));
    connect(port, SIGNAL(editTextChanged(QString)), this, SLOT(updatePort(QString)));
    connect(baud, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateBaudRate(QString)));
    connect(m_parity, SIGNAL(currentIndexChanged(int)), this, SLOT(updateParity(int)));
    connect(m_flow, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateFlowControl(int)));
    connect(m_stop, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStopBits(int)));
    connect(newInput, SIGNAL(clicked()), this, SLOT(addInput()));

    setLayout(layout);
}

void ModbusNGConfWidget::updatePort(const QString &value)
{
    updateAttribute("port", value);
}

void ModbusNGConfWidget::updateBaudRate(const QString &value)
{
    updateAttribute("baud", value);
}

void ModbusNGConfWidget::updateParity(int value)
{
    updateAttribute("parity", m_parity->itemData(value).toString());
}

void ModbusNGConfWidget::updateFlowControl(int value)
{
    updateAttribute("flow", m_flow->itemData(value).toString());
}

void ModbusNGConfWidget::updateStopBits(int value)
{
    updateAttribute("stop", m_stop->itemData(value).toString());
}

void ModbusNGConfWidget::addInput()
{
    insertChildNode(tr("Input"), "modbusnginput");
}

@ Next, there is a configuration widget for input channels.

@<Class declarations@>=
class ModbusNGInputConfWidget : public BasicDeviceConfigurationWidget
{
    Q_OBJECT
    public:
        Q_INVOKABLE ModbusNGInputConfWidget(DeviceTreeModel *model, const QModelIndex &index);
    private slots:
        void updateStation(int value);
        void updateAddress(int value);
        void updateFunction(int value);
        void updateFormat(int value);
        void updateDecimals(int value);
        void updateUnit(int value);
        void updateColumnName(const QString &value);
        void updateHidden(bool value);
};

@ This is where the function, address, and additional required details about
an input channel are defind.

@<ModbusNG implementation@>=
ModbusNGInputConfWidget::ModbusNGInputConfWidget(DeviceTreeModel *model, const QModelIndex &index) : BasicDeviceConfigurationWidget(model, index)
{
    QFormLayout *layout = new QFormLayout;
    QSpinBox *station = new QSpinBox;
    station->setMinimum(1);
    station->setMaximum(247);
    layout->addRow(tr("Station ID"), station);
    QComboBox *function = new QComboBox;
    function->addItem("3", "3");
    function->addItem("4", "4");
    function->setCurrentIndex(1);
    layout->addRow(tr("Function"), function);
    ShortHexSpinBox *address = new ShortHexSpinBox;
    layout->addRow(tr("Address"), address);
    QComboBox *format = new QComboBox;
    format->addItem(tr("16 bits fixed point"), "16fixedint");
    format->addItem(tr("32 bits floating point (High Low)"), "32floathl");
    format->addItem(tr("32 bits floating point (Low High)"), "32floatlh");
    layout->addRow(tr("Data format"), format);
    QSpinBox *decimals = new QSpinBox;
    decimals->setMinimum(0);
    decimals->setMaximum(9);
    layout->addRow(tr("Decimal places"), decimals);
    QComboBox *unit = new QComboBox;
    unit->addItem("Celsius", "C");
    unit->addItem("Fahrenheit", "F");
    unit->setCurrentIndex(1);
    layout->addRow(tr("Unit"), unit);
    QLineEdit *column = new QLineEdit;
    layout->addRow(tr("Column name"), column);
    QCheckBox *hidden = new QCheckBox(tr("Hide this channel"));
    layout->addRow(hidden);
    
    @<Get device configuration data for current node@>@;
    for(int i = 0; i < configData.size(); i++)
    {
        node = configData.at(i).toElement();
        if(node.attribute("name") == "station")
        {
            station->setValue(node.attribute("value").toInt());
        }
        else if(node.attribute("name") == "function")
        {
            function->setCurrentIndex(function->findText(node.attribute("value")));
        }
        else if(node.attribute("name") == "address")
        {
            address->setValue(node.attribute("value").toInt());
        }
        else if(node.attribute("name") == "format")
        {
            format->setCurrentIndex(format->findData(node.attribute("value")));
        }
        else if(node.attribute("name") == "decimals")
        {
            decimals->setValue(node.attribute("value").toInt());
        }
        else if(node.attribute("name") == "unit")
        {
            unit->setCurrentIndex(unit->findData(node.attribute("value")));
        }
        else if(node.attribute("name") == "column")
        {
            column->setText(node.attribute("value"));
        }
        else if(node.attribute("name") == "hidden")
        {
            hidden->setChecked(node.attribute("value") == "true" ? true : false);
        }
    }
    updateStation(station->value());
    updateFunction(function->currentIndex());
    updateAddress(address->value());
    updateFormat(format->currentIndex());
    updateDecimals(decimals->value());
    updateUnit(unit->currentIndex());
    updateColumnName(column->text());
    updateHidden(hidden->isChecked());
    
    connect(station, SIGNAL(valueChanged(int)), this, SLOT(updateStation(int)));
    connect(function, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFunction(int)));
    connect(address, SIGNAL(valueChanged(int)), this, SLOT(updateAddress(int)));
    connect(format, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFormat(int)));
    connect(decimals, SIGNAL(valueChanged(int)), this, SLOT(updateDecimals(int)));
    connect(unit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));
    connect(column, SIGNAL(textEdited(QString)), this, SLOT(updateColumnName(QString)));
    connect(hidden, SIGNAL(toggled(bool)), this, SLOT(updateHidden(bool)));
    
    setLayout(layout);
}

void ModbusNGInputConfWidget::updateStation(int value)
{
    updateAttribute("station", QString("%1").arg(value));
}

void ModbusNGInputConfWidget::updateFunction(int  value)
{
    updateAttribute("function", QString("%1").arg(value == 0 ? "3" : "4"));
}

void ModbusNGInputConfWidget::updateAddress(int value)
{
    updateAttribute("address", QString("%1").arg(value));
}

void ModbusNGInputConfWidget::updateFormat(int value)
{
    switch(value)
    {
        case 0:
            updateAttribute("format", "16fixedint");
            break;
        case 1:
            updateAttribute("format", "32floathl");
            break;
        case 2:
            updateAttribute("format", "32floatlh");
            break;
    }
}

void ModbusNGInputConfWidget::updateDecimals(int value)
{
    updateAttribute("decimals", QString("%1").arg(value));
}

void ModbusNGInputConfWidget::updateUnit(int value)
{
    switch(value)
    {
        case 0:
            updateAttribute("unit", "C");
            break;
        case 1:
            updateAttribute("unit", "F");
            break;
    }
}

void ModbusNGInputConfWidget::updateColumnName(const QString &value)
{
    updateAttribute("column", value);
}

void ModbusNGInputConfWidget::updateHidden(bool value)
{
    updateAttribute("hidden", value ? "true" : "false");
}

@ The configuration widgets need to be registered.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("modbusngport", ModbusNGConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbusnginput",
                                      ModbusNGInputConfWidget::staticMetaObject);

@ A |NodeInserter| is also needed.

@<Register top level device configuration nodes@>=
inserter = new NodeInserter(tr("ModbusNG Port"), tr("Modbus RTU Port"), "modbusngport", NULL);
topLevelNodeInserters.append(inserter);

@ Another class is used to handle the communication with the bus and serve as
an integration point for \pn{}.

