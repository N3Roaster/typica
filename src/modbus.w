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

@ While the old design only needed to deal with a small number of potential
messages and responses, it makes sense for the new design to use a scan list
of arbitrary length. An initial implementation can simply store the data needed
to make requests, properly interpret the results, and output data to the
correct channels. There is room to improve operational efficiency later by
batching operations on adjacent addresses on the same function into a single
request, but there are known devices in use in coffee roasters which do not
support reading from multiple registers simultaneously, so there must also be a
way to turn such optimizations off.

@<Class declarations@>=
enum ModbusDataFormat
{
    Int16,
    FloatHL,
    FloatLH
};

struct ModbusScanItem
{
    QByteArray request;
    ModbusDataFormat format;
    int decimalPosition;
    Units::Unit unit;
    mutable double lastValue;
};

@ Another class is used to handle the communication with the bus and serve as
an integration point for \pn{}.

@<Class declarations@>=
class ModbusNG : public QObject
{
    Q_OBJECT
    public:
        ModbusNG(DeviceTreeModel *model, const QModelIndex &index);
        ~ModbusNG();
        Q_INVOKABLE int channelCount();
        Channel* getChannel(int);
        Q_INVOKABLE QString channelColumnName(int);
        Q_INVOKABLE QString channelIndicatorText(int);
        Q_INVOKABLE bool isChannelHidden(int);
    private slots:
        void sendNextMessage();
        void timeout();
        void dataAvailable();
    private:
        quint16 calculateCRC(QByteArray data);
        QextSerialPort *port;
        int delayTime;
        QTimer *messageDelayTimer;
        QTimer *commTimeout;
        int scanPosition;
        bool waiting;
        QByteArray responseBuffer;
        QList<Channel*> channels;
        QList<ModbusScanItem> scanList;
        QList<QString> channelNames;
        QList<QString> channelLabels;
        QList<bool> hiddenStates;
};

@ One of the things that the old Modbus code got right was in allowing the
constructor to handle device configuration by accepting its configuration
sub-tree. In this design, child nodes establish a scan list.

@<ModbusNG implementation@>=
ModbusNG::ModbusNG(DeviceTreeModel *model, const QModelIndex &index) :
    QObject(NULL), messageDelayTimer(new QTimer), commTimeout(new QTimer),
    scanPosition(0), waiting(false)
{
    QDomElement portReferenceElement =
        model->referenceElement(model->data(index, Qt::UserRole).toString());
    QDomNodeList portConfigData = portReferenceElement.elementsByTagName("attribute");
    QDomElement node;
    QVariantMap attributes;
    for(int i = 0; i < portConfigData.size(); i++)
    {
        node = portConfigData.at(i).toElement();
        attributes.insert(node.attribute("name"), node.attribute("value"));
    }
    port = new QextSerialPort(attributes.value("port").toString(),
                              QextSerialPort::EventDriven);
    port->setBaudRate((BaudRateType)(attributes.value("baud").toInt()));
    port->setDataBits(DATA_8);
    port->setParity((ParityType)attributes.value("parity").toInt());
    port->setStopBits((StopBitsType)attributes.value("stop").toInt());
    port->setFlowControl((FlowType)attributes.value("flow").toInt());
    delayTime = (int)(((double)(1)/(double)(attributes.value("baud").toInt())) * 144000.0);
    messageDelayTimer->setSingleShot(true);
    commTimeout->setSingleShot(true);
    connect(messageDelayTimer, SIGNAL(timeout()), this, SLOT(sendNextMessage()));
    connect(commTimeout, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(port, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
    port->open(QIODevice::ReadWrite);
    for(int i = 0; i < model->rowCount(index); i++)
    {
        QModelIndex channelIndex = model->index(i, 0, index);
        QDomElement channelReferenceElement =
            model->referenceElement(model->data(channelIndex, Qt::UserRole).toString());
        QDomNodeList channelConfigData =
            channelReferenceElement.elementsByTagName("attribute");
        QDomElement channelNode;
        QVariantMap channelAttributes;
        for(int j = 0; j < channelConfigData.size(); j++)
        {
            channelNode = channelConfigData.at(j).toElement();
            channelAttributes.insert(channelNode.attribute("name"),
                                     channelNode.attribute("value"));
        }
        ModbusScanItem scanItem;
        QString format = channelAttributes.value("format").toString();
        if(format == "16fixedint")
        {
            scanItem.format = Int16;
        }
        else if(format == "32floathl")
        {
            scanItem.format = FloatHL;
        }
        else if(format == "32floatlh")
        {
            scanItem.format = FloatLH;
        }
        scanItem.request.append((char)channelAttributes.value("station").toInt());
        scanItem.request.append((char)channelAttributes.value("function").toInt());
        quint16 startAddress = (quint16)channelAttributes.value("address").toInt();
        char *startAddressBytes = (char*)&startAddress;
        scanItem.request.append(startAddressBytes[1]);
        scanItem.request.append(startAddressBytes[0]);
        scanItem.request.append((char)0x00);
        if(scanItem.format == Int16)
        {
            scanItem.request.append((char)0x01);
        }
        else
        {
            scanItem.request.append((char)0x02);
        }
        quint16 crc = calculateCRC(scanItem.request);
        char *crcBytes = (char*)&crc;
        scanItem.request.append(crcBytes[0]);
        scanItem.request.append(crcBytes[1]);
        scanItem.decimalPosition = channelAttributes.value("decimals").toInt();
        if(channelAttributes.value("unit").toString() == "C")
        {
            scanItem.unit = Units::Celsius;
        }
        else
        {
            scanItem.unit = Units::Fahrenheit;
        }
        scanList.append(scanItem);
        channels.append(new Channel);
        channelNames.append(channelAttributes.value("column").toString());
        hiddenStates.append(
            channelAttributes.value("hidden").toString() == "true" ? true : false);
        channelLabels.append(model->data(channelIndex, 0).toString());
    }
    messageDelayTimer->start();
}

ModbusNG::~ModbusNG()
{
    commTimeout->stop();
    messageDelayTimer->stop();
    port->close();
}

void ModbusNG::sendNextMessage()
{
    if(scanList.length() > 0 && !waiting)
    {
        port->write(scanList.at(scanPosition).request);
        commTimeout->start(2000);
        messageDelayTimer->start(delayTime);
        waiting = true;
    }
}

void ModbusNG::timeout()
{
    qDebug() << "Communications timeout.";
    messageDelayTimer->start();
}

void ModbusNG::dataAvailable()
{
    if(messageDelayTimer->isActive())
    {
        messageDelayTimer->stop();
    }
    responseBuffer.append(port->readAll());
    if(responseBuffer.size() < 5)
    {
        return;
    }
    if(responseBuffer.size() < 5 + responseBuffer.at(2))
    {
        return;
    }
    responseBuffer = responseBuffer.left(5 + responseBuffer.at(2));
    commTimeout->stop();
    if(calculateCRC(responseBuffer) == 0)
    {
        quint16 intresponse;
        float floatresponse;
        char *ibytes = (char*)&intresponse;
        char *fbytes = (char*)&floatresponse;
        double output;
        switch(scanList.at(scanPosition).format)
        {
            case Int16:
                ibytes[0] = responseBuffer.at(4);
                ibytes[1] = responseBuffer.at(3);
                output = intresponse;
                for(int i = 0; i < scanList.at(scanPosition).decimalPosition; i++)
                {
                    output /= 10;
                }
                break;
            case FloatHL:
                fbytes[0] = responseBuffer.at(4);
                fbytes[1] = responseBuffer.at(3);
                fbytes[2] = responseBuffer.at(6);
                fbytes[3] = responseBuffer.at(5);
                output = floatresponse;
                break;
            case FloatLH:
                fbytes[0] = responseBuffer.at(6);
                fbytes[1] = responseBuffer.at(5);
                fbytes[2] = responseBuffer.at(4);
                fbytes[3] = responseBuffer.at(3);
                output = floatresponse;
                break;
        }
        if(scanList.at(scanPosition).unit == Units::Celsius)
        {
            output = output * 9.0 / 5.0 + 32.0;
        }
        scanList.at(scanPosition).lastValue = output;
    }
    else
    {
        qDebug() << "CRC failed";
    }
    scanPosition = (scanPosition + 1) % scanList.size();
    if(scanPosition == 0)
    {
        QTime time = QTime::currentTime();
        for(int i = 0; i < scanList.size(); i++)
        {
            channels.at(i)->input(Measurement(scanList.at(i).lastValue, time, Units::Fahrenheit));
        }
    }
    responseBuffer.clear();
    waiting = false;
    messageDelayTimer->start(delayTime);
}

quint16 ModbusNG::calculateCRC(QByteArray data)
{
    quint16 retval = 0xFFFF;
    int i = 0;
    while(i < data.size())
    {
        retval ^= 0x00FF & (quint16)data.at(i);
        for(int j = 0; j < 8; j++)
        {
            if(retval & 1)
            {
                retval = (retval >> 1) ^ 0xA001;
            }
            else
            {
                retval >>= 1;
            }
        }
        i++;
    }
    return retval;
}

int ModbusNG::channelCount()
{
    return channels.size();
}

Channel* ModbusNG::getChannel(int channel)
{
    return channels.at(channel);
}

QString ModbusNG::channelColumnName(int channel)
{
    return channelNames.at(channel);
}

QString ModbusNG::channelIndicatorText(int channel)
{
    return channelLabels.at(channel);
}

bool ModbusNG::isChannelHidden(int channel)
{
    return hiddenStates.at(channel);
}

@ This class must be exposed to the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructModbusNG(QScriptContext *context, QScriptEngine *engine);
void setModbusNGProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue ModbusNG_getChannel(QScriptContext *context, QScriptEngine *engine);

@ The host environment is informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructModbusNG);
value = engine->newQMetaObject(&ModbusNG::staticMetaObject, constructor);
engine->globalObject().setProperty("ModbusNG", value);

@ The constructor takes the configuration model and the index to the device as
arguments.

@<Functions for scripting@>=
QScriptValue constructModbusNG(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue object;
    if(context->argumentCount() == 2)
    {
        object = engine->newQObject(new ModbusNG(argument<DeviceTreeModel *>(0, context),
                                                 argument<QModelIndex>(1, context)),
                                    QScriptEngine::ScriptOwnership);
        setModbusNGProperties(object, engine);
    }
    else
    {
        context->throwError("Incorrect number of arguments passed to "@|
            "ModbusNG constructor.");
    }
    return object;
}

void setModbusNGProperties(QScriptValue value, QScriptEngine *engine)
{
    setQObjectProperties(value, engine);
    value.setProperty("getChannel", engine->newFunction(ModbusNG_getChannel));
}

QScriptValue ModbusNG_getChannel(QScriptContext *context, QScriptEngine *engine)
{
    ModbusNG *self = getself<ModbusNG *>(context);
    QScriptValue object;
    if(self)
    {
        object = engine->newQObject(self->getChannel(argument<int>(0, context)));
        setChannelProperties(object, engine);
    }
    return object;
}
