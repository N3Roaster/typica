@** Configuration of Serial Devices Using Modbus RTU.

\noindent One protocol that is used across a broad class of devices is called
Modbus RTU. This protocol allows multiple devices to communicate over a two
wire bus which can be connected to a single serial port. The communication
protocol involves a single message which is sent from a master device (in this
case the computer running Typica) to a slave device (the device we would like
to send information to or receive information from) which is followed by a
response message from the slave to the master. After a brief wait the master
can then send another message to any slave on the bus and this process repeats.
Every outgoing message provides a station address to identify which slave on
the bus should respond, a function code to identify which of a broad class of
operations has been requested, the required data for the function specified,
and a cyclic redundancy check to validate the message.

There are multiple variants of this protocol. Modbus RTU is a binary protocol,
however an ASCII version of the protocol also exists, as does a version of the
protocol which operates over TCP. At present I have no interest in adding
support for Modbus ASCII because I am not aware of any devices of interest
which support that protocol and not the more efficient Modbus RTU variant, but
if the feature were requested by anybody I would be willing to change that
assessment and have hardware available which could be used to test this
support. Modbus TCP support is more interesting but I do not currently have any
hardware to test this.

The protocol is used with several different types of devices for various
purposes which may be of interest with Typica. Common examples include PID
controllers which can provide several potentially interesting types of
information, frequency inverters which can be used to report and control the
speed of drum and impeller motors, and manometers that can be used to report
fuel pressure. Fully general support for all device classes is a current long
term plan. Initial support focuses on temperature process and set values with
additional features added as I am able to test functionality.

At present, there are four different types of configuration widgets
representing different aspects of the system configuration. First there is a
widget for configuring the bus port. Information here is used to set up the
serial port the devices are connected to. Next there is a widget for
configuring a device. Each device has a station ID which must be unique on the
bus it is connected to (but in cases where multiple busses are connected,
devices on different busses can share the same station ID) and there are
quirks in protocol support on certain devices so it is possible to indicate,
for example, that messages sent to a particular device should not combine
requests for data from multiple contiguous registers into a single request.
There is then a widget for configuring the interpretation of measurements.
Many panel displays reporting temperature measurements produce fixed point
values where we must know how many places are after the decimal point and
what unit the values are reported in. These may be fixed values or they may
be queried from the device in question. Next there are widgets that correspond
to data channels in Typica. These may come from read only addresses such as
a process value or they may be associated with read write addresses, in which
case there may also be a desire to create a control during roasting that
allows information to be sent to the device. This structure allows additional
node types to be provided as needed for future features.

@<Class declarations@>=
class ModbusRtuPortConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:
		@[Q_INVOKABLE@]@, ModbusRtuPortConfWidget(DeviceTreeModel *model,
		                                          const QModelIndex &index);
	@[private slots@]:@/
		void updatePort(const QString &newPort);
		void updateBaudRate(const QString &newRate);
		void updateParity(const QString &newParity);
		void updateFlowControl(const QString &newFlow);
		void updateStopBits(const QString &newStopBits);
};

@ Aside from the extra information compared with other configuration widgets
previously described, there is nothing surprising about the implementation.

@<ModbusRtuPortConfWidget implementation@>=
ModbusRtuPortConfWidget::ModbusRtuPortConfWidget(DeviceTreeModel *model,
                                                 const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QToolButton *addDeviceButton = new QToolButton;
	addDeviceButton->setText(tr("Add Device"));
	NodeInserter *addModbusRtuDevice = new NodeInserter("Modbus RTU Device",
	                                                    "Modbus RTU Device",
														"modbusrtudevice");
	connect(addModbusRtuDevice, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *deviceMenu = new QMenu;
	deviceMenu->addAction(addModbusRtuDevice);
	addDeviceButton->setMenu(deviceMenu);
	addDeviceButton->setPopupMode(QToolButton::InstantPopup);
	layout->addRow(QString(), addDeviceButton);
	PortSelector *port = new PortSelector;
	layout->addRow(tr("Port:"), port);
	connect(port, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updatePort(QString)));
	connect(port, SIGNAL(editTextChanged(QString)),
	        this, SLOT(updatePort(QString)));
	BaudSelector *rate = new BaudSelector;
	layout->addRow(tr("Baud:"), rate);
	connect(rate, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateBaudRate(QString)));
	ParitySelector *parity = new ParitySelector;
	layout->addRow(tr("Parity:"), parity);
	connect(parity, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateParity(QString)));
	FlowSelector *flow = new FlowSelector;
	layout->addRow(tr("Flow Control:"), flow);
	connect(flow, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateFlowControl(QString)));
	StopSelector *stop = new StopSelector;
	layout->addRow(tr("Stop Bits:"), stop);
	connect(stop, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateStopBits(QString)));
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "port")
		{
			int j = port->findText(node.attribute("value"));
			if(j >= 0)
			{
				port->setCurrentIndex(j);
			}
			else
			{
				port->insertItem(0, node.attribute("value"));
				port->setCurrentIndex(0);
			}
		}
		else if(node.attribute("name") == "baudrate")
		{
			rate->setCurrentIndex(rate->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "parity")
		{
			parity->setCurrentIndex(parity->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "flowcontrol")
		{
			flow->setCurrentIndex(flow->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "stopbits")
		{
			stop->setCurrentIndex(stop->findText(node.attribute("value")));
		}
	}
	updatePort(port->currentText());
	updateBaudRate(rate->currentText());
	updateParity(parity->currentText());
	updateFlowControl(flow->currentText());
	updateStopBits(stop->currentText());
	setLayout(layout);
}

void ModbusRtuPortConfWidget::updatePort(const QString &newPort)
{
	updateAttribute("port", newPort);
}

void ModbusRtuPortConfWidget::updateBaudRate(const QString &newRate)
{
	updateAttribute("baudrate", newRate);
}

void ModbusRtuPortConfWidget::updateParity(const QString &newParity)
{
	updateAttribute("parity", newParity);
}

void ModbusRtuPortConfWidget::updateFlowControl(const QString &newFlow)
{
	updateAttribute("flowcontrol", newFlow);
}

void ModbusRtuPortConfWidget::updateStopBits(const QString &newStopBits)
{
	updateAttribute("stopbits", newStopBits);
}

@ With the port the bus is connected to configured, we need to provide a
widget for configuring a particular device. At present the device
configuration consists of the station ID and the maximum number of
contiguous registers that can be grouped into a single request for functions
that normally allow access to multiple registers in a single request. This
setting is required as I have encountered devices which only allow a single
register to be accessed in one request despite the use of functions which are
intended for access to multiple registers. Setting a value other than 1 would
allow devices to combine requests to multiple contiguous registers in a single
request which would allow collecting these measurements at a faster rate with
clock skew.

The station ID is a number between 0 and 255. Zero is typically the broadcast
address which reaches all devices on the bus and is generally not recommended
except in particular circumstances.

Under each device it is possible to set up a configuration group which
determines how certain measurements are interpreted.

@<Class declarations@>=
class ModbusRtuDeviceConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuDeviceConfWidget(DeviceTreeModel *model,
		                                            const QModelIndex &index);
	@[private slots@]:@/
		void updateStationNumber(int newStation);
		void updateRegisterLimit(int newLimit);
};

@ The values in |registerLimit| range from 1 to 125. Setting this value to 1
means that every register read will require a separate message to request that
value. Higher values allow device communications code to combine requests for
multiple contiguous registers in a single request with the upper limit of 125
a consequence of the maximum message length imposed by the Modbus RTU protocol.

It is possible to configure arbitrarily many configuration groups under a
device and the "Custom Unit Values" option allows logging different types of
control variables in sensible units. Each custom unit should also have
configuration options set for the graph view.

@<ModbusRtuDeviceConfWidget implementation@>=
ModbusRtuDeviceConfWidget::ModbusRtuDeviceConfWidget(DeviceTreeModel *model,
                                                     const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QToolButton *addGroupButton = new QToolButton;
	addGroupButton->setText(tr("Add Value Interpretation Group"));
	NodeInserter *addTempConfGroup = new NodeInserter("Temperature Values",
	                                                  "Temperature Values",
													  "modbustempconfgroup");
	NodeInserter *addCustomConfGroup = new NodeInserter("Custom Unit Values",
	                                                    "Custom Unit Values",
	                                                    "modbuscustomunitconfgroup");
	connect(addTempConfGroup, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(addCustomConfGroup, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *configMenu = new QMenu;
	configMenu->addAction(addTempConfGroup);
	configMenu->addAction(addCustomConfGroup);
	addGroupButton->setMenu(channelMenu);
	addGroupButton->setPopupMode(QToolButton::InstantPopup);
	layout->addRow(QString(), addGroupButton);

	QSpinBox *stationNumber = new QSpinBox;
	stationNumber->setMinimum(0);
	stationNumber->setMaximum(255);
	layout->addRow(tr("Station ID"), stationNumber);

	QSpinBox *registerLimit = new QSpinBox;
	registerLimit->setMinimum(1);
	registerLimit->setMaximum(125);
	layout->addRow(tr("Maximum Registers per Message"), registerLimit);
	
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "station")
		{
			stationNumber->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "registerlimit")
		{
			registerLimit->setValue(node.attribute("value").toInt());
		}
	}
	
	updateStationNumber(stationNumber->value());
	updateRegisterLimit(registerLimit->value());

	connect(stationNumber, SIGNAL(valueChanged(int)),
	        this, SLOT(updateStationNumber(int)));
	connect(registerLimitm SIGNAL(valueChanged(int)),
	        this, SLOT(updateRegisterLimit(int)));

	setLayout(layout);
}

void ModbusRtuDeviceConfWidget::updateStationNumber(int newStation)
{
	updateAttribute("station", QString("%1").arg(newStation));
}

void ModbusRtuDeviceConfWidget::updateRegisterLimit(int newLimit)
{
	updateAttribute("registerlimit", QString("%1").arg(newLimit));
}

@ There are several plausible types of information that we may wish to log from
devices that understand Modbus RTU and some devices will support more than one
type of data. Due to limitations in the protocol, this information is not
self-documenting and Typica must be told how the data is to be interpreted. To
avoid excessive data entry when monitoring multiple registers with information
that should be interpreted in the same way as is common, the configuration of
these registers is grouped.

@<Class declarations@>=
class ModbusRtuTempConfGroupConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuTempConfGroupConfWidget(DeviceTreeModel *model,
		                                                   const QModelIndex &index);
	@[private slots@]:@/
		void updateFixedUnit(bool newValue);
		void updateFixedPrecision(bool newValue);
		void updateUnit(const QString &newValue);
		void updatePrecision(int newValue);
		void updateUnitAddress(int newValue);
		void updateFValue(int newValue);
		void updateCValue(int newValue);
		void updatePrecisionAddress(int newValue);
	private:
		QStackedLayout *unitSpecificationLayout;
		QStackedLayout *precisionSpecificationLayout;
};

@ Registers in Modbus RTU provide access to 16 bit integer values, but most
devices that provide access to temperature data will present this as a fixed
point decimal value. In order to correctly interpret this information we must
know how many positions the decimal point should be shifted and what the
current measurement unit is. Both of these are often configurable and Typica
provides two options for configuring this. One option is to fix the value. If
you know that a particular device will always be set so that one place should
be considered to be after the decimal point and temperature measurements will
always be in degrees Fahrenheit, you can just specify that this is the case.
Alternately, you can specify the function and address to check the current
configuration and in the case of units provide which unit maps to what value.

As details that are specific to temperature handling are configured in the
group configuration, register configuration nodes can be generic.

At present, when querying configuration details

@<ModbusRtuTempConfGroupConfWidget implementation@>=
ModbusRtuTempConfGroupConfWidget::ModbusRtuTempConfGroupConfWidget(DeviceTreeModel *model,
                                                                   const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index),
unitSpecificationLayout(new QStackedLayout),
precisionSpecificationLayout(new QStackedLayout)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QToolButton *addChannelButton = new QToolButton;
	addChannelButton->setText(tr("Add Channel"));
	NodeInserter *addTemperaturePV = new NodeInserter("Read Only Value",
	                                                  "Read Only Value",
	                                                  "modbusrvalue");
	NodeInserter *addTemperatureSV = new NodeInserter("Read Write Value",
	                                                  "Read Write Value",
	                                                  "modbusrwvalue");
	connect(addTemperaturePV, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(addTemperatureSV, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *channelMenu = new QMenu;
	channelMenu->addAction(addTemperaturePV);
	channelMenu->addAction(addTemperatureSV);
	addChannelButton->setMenu(channelMenu);
	addChannelButton->setPopupMode(QToolButton::InstantPopup);
	layout->addWidget(addChannelButton);
	
	QCheckBox *fixedUnit = new QCheckBox(tr("Fixed Temperature Unit"));
	layout->addWidget(fixedUnit);
	QWidget *fixedUnitPlaceholder = new QWidget;
	QHBoxLayout *fixedUnitLayout = new QHBoxLayout;
	QLabel *fixedUnitLabel = new QLabel(tr("Unit:"));
	QComboBox *fixedUnitSelector = new QComboBox;
	fixedUnitSelector->addItem("Fahrenheit");
	fixedUnitSelector->addItem("Celsius");
	fixedUnitLayout->addWidget(fixedUnitLabel);
	fixedUnitLayout->addWidget(fixedUnitSelector);
	fixedUnitPlaceholder->setLayout(fixedUnitLayout);
	unitSpecificationLayout->addWidget(fixedUnitPlaceholder);
	
	QWidget *queriedUnitPlaceholder = new QWidget;
	QFormLayout *queriedUnitLayout = new QFormLayout;
	ShortHexSpinBox *unitAddress = new ShortHexSpinBox;
	queriedUnitLayout->addRow(tr("Function 0x03 Unit Address:"), unitAddress);
	QSpinBox *valueF = new QSpinBox;
	valueF->setMinimum(0);
	valueF->setMaximum(65535);
	queriedUnitLayout->addRow(tr("Value for Fahrenheit"), valueF);
	QSpinBox *valueC = new QSpinBox;
	valueC->setMinimum(0);
	valueC->setMaximum(65535);
	queriedUnitLayout->addRow(tr("Value for Celsius"), valueC);
	queriedUnitPlaceholder->setLayout(queriedUnitLayout);
	unitSpecificationLayout->addWidget(queriedUnitPlaceholder);
	layout->addLayout(unitSpecificationLayout);
	
	QCheckBox *fixedPrecision = new QCheckBox(tr("Fixed Precision"));
	layout->addWidget(fixedPrecision);
	QWidget *fixedPrecisionPlaceholder = new QWidget;
	QFormLayout *fixedPrecisionLayout = new QFormLayout;
	QSpinBox *fixedPrecisionValue = new QSpinBox;
	fixedPrecisionValue->setMinimum(0);
	fixedPrecisionValue->setMaximum(9);
	fixedPrecisionLayout->addRow("Places after the decimal point:", fixedPrecisionValue);
	fixedPrecisionPlaceholder->setLayout(fixedPrecisionLayout);
	precisionSpecificationLayout->addWidget(fixedPrecisionPlaceholder);
	
	QWidget *queriedPrecisionPlaceholder = new QWidget;
	QFormLayout *queriedPrecisionLayout = new QFormLayout;
	ShortHexSpinBox *precisionAddress = new ShortHexSpinBox;
	queriedPrecisionLayout->addRow(tr("Function 0x03 Decimal Position Address"),
                                   precisionAddress);
    queriedPrecisionPlaceholder->setLayout(queriedPrecisionLayout);
    precisionSpecificationLayout->addWidget(queriedPrecisionPlaceholder);
    layout->addLayout(precisionSpecificationLayout);
    
    @<Get device configuration data for current node@>@;
    for(int i = 0; i < configData.size(); i++)
    {
		node = configData.at(i).toElement();
		switch(node.attribute("name"))
		{
			case "fixedunit":
				if(node.attribute("value") == "true")
				{
					fixedUnit->setCheckState(Qt::Checked);
				}
				else
				{
					fixedUnit->setCheckState(Qt::Unchecked);
				}
				break;
			case "fixedprecision":
				if(node.attribute("value") == "true")
				{
					fixedPrecision->setCheckState(Qt::Checked);
				}
				else
				{
					fixedPrecision->setCheckState(Qt::Unchecked);
				}
				break;
			case "unit":
				fixedUnitSelector->
					setCurrentIndex(fixedUnitSelector->findText(node.attribute("value")));
				break;
			case "unitaddress":
				unitAddress->setValue(node.attribute("value").toInt());
				break;
			case "fvalue":
				valueF->setValue(node.attribute("value").toInt());
				break;
			case "cvalue":
				valueC->setValue(node.attribute("value").toInt());
				break;
			case "precisionaddress":
				precisionAddress->setValue(node.attribute("value").toInt());
				break;
			case "precision":
				fixedPrecisionValue->setValue(node.attribute("value").toInt());
				break;
			default:
				break;
		}
    }
    updateFixedUnit(fixedUnit->isChecked());
    updateFixedPrecision(fixedPrecision->isChecked());
    updateUnit(fixedUnitSelector->currentText());
    updateUnitAddress(unitAddress->value());
    updateFValue(valueF->value());
    updateCValue(valueC->value());
    updatePrecisionAddress(precisionAddress->value());
    updatePrecision(fixedPrecisionValue->value());
    
    connect(fixedUnit, SIGNAL(toggled(bool)), this, SLOT(updateFixedUnit(bool)));
    connect(fixedPrecision, SIGNAL(toggled(bool)), this, SLOT(updateFixedPrecision(bool)));
    connect(fixedUnitSelector, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(updateUnit(QString)));
    connect(unitAddress, SIGNAL(valueChanged(int)), this, SLOT(updateUnitAddress(int)));
    connect(valueF, SIGNAL(valueChanged(int)), this, SLOT(updateFValue(int)));
    connect(valueC, SIGNAL(valueChanged(int)), this, SLOT(updateCValue(int)));
    connect(precisionAddress, SIGNAL(valueChanged(int)), this, SLOT(updatePrecisionAddress(int)));
    connect(fixedPrecisionValue, SIGNAL(valueChanged(int)), this, SLOT(updatePrecision(int)));
}

@ The methods that update the current configuration attributes are typical,
however the check boxes also update which configuration controls are currently
displayed.

@<ModbusRtuTempConfGroupConfWidget implementation@>=
void ModbusRtuTempConfGroupConfWidget::updateFixedUnit(bool newValue)
{
	if(newValue)
	{
		unitSpecificationLayout->setCurrentIndex(0);
		updateAttribute("fixedunit", "true");
	} else {
		unitSpecificationLayout->setCurrentIndex(1);
		updateAttribute("fixedunit", "false");
	}
}

void ModbusRtuTempConfGroupConfWidget::updateFixedPrecision(bool newValue)
{
	if(newValue)
	{
		precisionSpecificationLayout->setCurrentIndex(0);
		updateAttribute("fixedprecision", "true");
	} else {
		precisionSpecificationLayout->setCurrentIndex(1);
		updateAttribute("fixedprexision", "false");
	}
}

void ModbusRtuTempConfGroupConfWidget::updateUnit(const QString &newValue)
{
	updateAttribute("unit", newValue);
}

void ModbusRtuTempConfGroupConfWidget::updatePrecision(int newValue)
{
	updateAttribute("precision", QString("%1").arg(newValue));
}

void ModbusRtuTempConfGroupConfWidget::updateUnitAddress(int newValue)
{
	updateAttribute("unitaddress", QString("%1").arg(newValue));
}

void ModbusRtuTempConfGroupConfWidget::updateFValue(int newValue)
{
	updateAttribute("fvalue", QString("%1").arg(newValue));
}

void ModbusRtuTempConfGroupConfWidget::updateCValue(int newValue)
{
	updateAttribute("cvalue", QString("%1").arg(newValue));
}

void ModbusRtuTempConfGroupConfWidget::updatePrecisionAddress(int newValue)
{
	updateAttribute("precisionaddress", QString("%1").arg(newValue));
}

@ Custom unit value configuration groups are slightly different from
temperature value configuration groups. At present only fixed configuration
options are available. That limitation may be removed in the future in
support of other desired features, however it is expected that most people do
not change unit representation on a given device often enough that the need
to change preferences in software as well are an inconvenience.

@<Class declarations@>=
class ModbusRtuCustomGroupConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuCustomGroupConfWidget(DeviceTreeModel *model,
		                                                 const QModelIndex &index);
	@[private slots@]:@/
		void updateUnit(const QString &newValue);
		void updatePrecision(int newValue);
};

@ The unit string is used as a key for the graph widget and its configuration,
allowing proper construction of secondary axes and matching of measurements to
the proper representation.

@<ModbusRtuCustomGroupConfWidget implementation@>=
ModbusRtuCustomGroupConfWidget::ModbusRtuCustomGroupConfWidget(DeviceTreeModel *model,
                                                               const QModelIndex &index)
{
	QFormLayout *layout = new QFormLayout;
	QToolButton *addChannelButton = new QToolButton;
	addChannelButton->setText(tr("Add Channel"));
	NodeInserter *addTemperaturePV = new NodeInserter("Read Only Value",
	                                                  "Read Only Value",
	                                                  "modbusrvalue");
	NodeInserter *addTemperatureSV = new NodeInserter("Read Write Value",
	                                                  "Read Write Value",
	                                                  "modbusrwvalue");
	connect(addTemperaturePV, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(addTemperatureSV, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *channelMenu = new QMenu;
	channelMenu->addAction(addTemperaturePV);
	channelMenu->addAction(addTemperatureSV);
	addChannelButton->setMenu(channelMenu);
	addChannelButton->setPopupMode(QToolButton::InstantPopup);
	layout->addRow(QString(), addChannelButton);
	
	QLineEdit *unit = new QLineEdit;
	QSpinBox *precision = new QSpinBox;
	precision->setMinimum(0);
	precision->setMaximum(9);
	layout->addRow(tr("Unit name:"), unit);
	layout->addRow(tr("Places after the decimal point:"), precision);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "unit")
		{
			unit->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "precision")
		{
			precision->setValue(node.attribute("value").toInt());
		}
	}
	updateUnit(unit->text());
	updatePrecision(precision->value());
	connect(unit, SIGNAL(textChanged(QString)), this, SLOT(updateUnit(QString)));
	connect(precision, SIGNAL(valueChanged(int)), this, SLOT(updatePrecision(int)));
}

void ModbusRtuCustomGroupConfWidget::updateUnit(const QString &newValue)
{
	updateAttribute("unit", newValue);
}

void ModbusRtuCustomGroupConfWidget::updatePrecision(int newValue)
{
	updateAttribute("precision", QString("%1").arg(newValue));
}

@ With the details of measurement interpretation configured elsewhere, the
configuration of which registers we would like to read and write apply equally
well to any sort of register group. Read only values require the request function,
the address to read, the column name for the data channel that address represents,
and if we would like to hide that channel.

@<Class declarations@>=
class ModbusRtuReadRegisterConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuReadRegisterConfWidget(DeviceTreeModel *model,
		                                                  const QModelIndex &index);
	@[private slots@]:@/
		void updateFunction(int newValue);
		void updateAddress(int newValue);
		void updateName(const QString &newValue);
		void updateHidden(bool newValue);
};

@ There is nothing exceptional about the implementation.

@<ModbusRtuReadRegisterConfWidget implementation@>=
ModbusRtuReadRegisterConfWidget::ModbusRtuReadRegisterConfWidget(DeviceTreeModel *model,
                                                                 const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	ShortHexSpinBox *function = new ShortHexSpinBox;
	function->setValue(4);
	function->setMinimum(1);
	function->setMaximum(255);
	ShortHexSpinBox *address = new ShortHexSpinBox;
	QLineEdit *column = new QLineEdit;
	QCheckBox *hidden = new QComboBox(tr("Hide this channel"));
	layout->addRow(tr("Read function"), function);
	layout->addRow(tr("Read address"), address);
	layout->addRow(tr("Column name"), column);
	layout->addRow(QString(), hidden);
	
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "function")
		{
			function->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "address")
		{
			address->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "column")
		{
			column->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "hidden")
		{
			if(node.attribute("value") == "true")
			{
				hidden->setCheckState(Qt::Checked);
			}
			else
			{
				hidden->setCheckState(Qt::Unchecked);
			}
		}
	}
	updateFunction(function->value());
	updateAddress(address->value());
	updateName(column->text());
	updateHidden(hidden->isChecked());
	connect(function, SIGNAL(valueChanged(int)), this, SLOT(updateFunction(int)));
	connect(address, SIGNAL(valueChanged(int)), this, SLOT(updateAddress(int)));
	connect(column, SIGNAL(textChanged(QString)), this, SLOT(updateName(QString)));
	connect(hidden, SIGNAL(toggled(bool)), this, SLOT(updateHidden(bool)));
	setLayout(layout);
}

void ModbusRtuReadRegisterConfWidget::updateFunction(int newValue)
{
	updateAttribute("function", QString("%1").arg(newValue));
}

void ModbusRtuReadRegisterConfWidget::updateAddress(int newValue)
{
	updateAttribute("address", QString("%1").arg(newValue));
}

void ModbusRtuReadRegisterConfWidget::updateName(const QString &newValue)
{
	updateAttribute("column", newValue);
}

void ModbusRtuReadRegisterConfWidget::updateHidden(bool newValue)
{
	updateAttribute("hidden", newValue ? "true" : "false");
}


@ Initial Modbus RTU support is very limited and only considers temperature
process and set values. While in some cases it would be possible to cleverly
adapt this support to broader categories this is an area that must be extended
later to cover at least unitless control values and on/off status values. It
would be ideal to cover a broad range of useful properties. To read process
values we need to know the address that the current process value can be read
from.

@<Class declarations@>=
class ModbusRtuDeviceTPvConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuDeviceTPvConfWidget(DeviceTreeModel *model,
		                                               const QModelIndex &index);
	@[private slots@]:@/
		void updateAddress(int newAddress);
};

@ This requires only a single field to store the address to query the current
process value.

@<ModbusRtuDeviceTPvConfWidget implementation@>=
ModbusRtuDeviceTPvConfWidget::ModbusRtuDeviceTPvConfWidget(DeviceTreeModel *model,
                                                           const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	ShortHexSpinBox *address = new ShortHexSpinBox;
	layout->addRow(tr("Function 0x04 Process Value Address"), address);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "address")
		{
			address->setValue(node.attribute("value").toInt());
			break;
		}
	}
	updateAddress(address->value());
	connect(address, SIGNAL(valueChanged(int)), this, SLOT(updateAddress(int)));
	setLayout(layout);
}

void ModbusRtuDeviceTPvConfWidget::updateAddress(int newAddress)
{
	updateAttribute("address", QString("%1").arg(newAddress));
}

@ Set values are slightly more complicated as we may want either a fixed range
or the ability to query the device for its current allowed range, but nothing
is here that hasn'@q'@>t been seen elsewhere.

@<Class declarations@>=
class ModbusRtuDeviceTSvConfWidget : public BasicDeviceConfigurationWidget@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		Q_INVOKABLE@, ModbusRtuDeviceTSvConfWidget(DeviceTreeModel *model,
		                                               const QModelIndex &index);
	@[private slots@]:@/
		void updateReadAddress(int newAddress);
		void updateWriteAddress(int newAddress);
		void updateFixedRange(bool fixed);
		void updateLower(const QString &lower);
		void updateUpper(const QString &upper);
		void updateLowerAddress(int newAddress);
		void updateUpperAddress(int newAddress);@/
	private:@/
		QStackedLayout *boundsLayout;
};

@ Upper and lower bounds when operating on a fixed range are still subject to
decimal position rules in the parent node. It may be a good idea to enforce
this, however at present the person configuring the system is trusted to know
what they are doing.

@<ModbusRtuDeviceTSvConfWidget implementation@>=
ModbusRtuDeviceTSvConfWidget::ModbusRtuDeviceTSvConfWidget(DeviceTreeModel *model,
                                                           const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index), boundsLayout(new QStackedLayout)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QFormLayout *addressLayout = new QFormLayout;
	ShortHexSpinBox *readAddress = new ShortHexSpinBox;
	ShortHexSpinBox *writeAddress = new ShortHexSpinBox;
	addressLayout->addRow(tr("Function 0x04 Read Set Value Address:"), readAddress);
	addressLayout->addRow(tr("Function 0x06 Write Set Value Address:"), writeAddress);
	layout->addLayout(addressLayout);
	QCheckBox *fixedRange = new QCheckBox(tr("Fixed Set Value Range"));
	layout->addWidget(fixedRange);
	QWidget *queriedRangePlaceholder = new QWidget(this);
	QFormLayout *queriedRangeLayout = new QFormLayout;
	ShortHexSpinBox *lowerAddress = new ShortHexSpinBox;
	ShortHexSpinBox *upperAddress = new ShortHexSpinBox;
	queriedRangeLayout->addRow(tr("Function 0x03 Minimum Set Value Address"),
	                           lowerAddress);
	queriedRangeLayout->addRow(tr("Function 0x03 Maximum Set Value Address"),
	                           upperAddress);
	queriedRangePlaceholder->setLayout(queriedRangeLayout);
	boundsLayout->addWidget(queriedRangePlaceholder);
	QWidget *fixedRangePlaceholder = new QWidget(this);
	QFormLayout *fixedRangeLayout = new QFormLayout;
	QLineEdit *fixedLower = new QLineEdit;
	QLineEdit *fixedUpper = new QLineEdit;
	fixedRangeLayout->addRow(tr("Minimum Set Value:"), fixedLower);
	fixedRangeLayout->addRow(tr("Maximum Set Value:"), fixedUpper);
	fixedRangePlaceholder->setLayout(fixedRangeLayout);
	boundsLayout->addWidget(fixedRangePlaceholder);
	layout->addLayout(boundsLayout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "readaddress")
		{
			readAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "writeaddress")
		{
			writeAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fixedrange")
		{
			if(node.attribute("value") == "true")
			{
				fixedRange->setCheckState(Qt::Checked);
			}
			else if(node.attribute("value") == "false")
			{
				fixedRange->setCheckState(Qt::Unchecked);
			}
		}
		else if(node.attribute("name") == "fixedlower")
		{
			fixedLower->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "fixedupper")
		{
			fixedUpper->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "loweraddress")
		{
			lowerAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "upperaddress")
		{
			upperAddress->setValue(node.attribute("value").toInt());
		}
	}
	updateReadAddress(readAddress->value());
	updateWriteAddress(writeAddress->value());
	updateFixedRange(fixedRange->isChecked());
	updateLower(fixedLower->text());
	updateUpper(fixedUpper->text());
	updateLowerAddress(lowerAddress->value());
	updateUpperAddress(upperAddress->value());
	connect(readAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateReadAddress(int)));
	connect(writeAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateWriteAddress(int)));
	connect(fixedRange, SIGNAL(toggled(bool)), this, SLOT(updateFixedRange(bool)));
	connect(fixedLower, SIGNAL(textChanged(QString)),
	        this, SLOT(updateLower(QString)));
	connect(fixedUpper, SIGNAL(textChanged(QString)),
	        this, SLOT(updateUpper(QString)));
	connect(lowerAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateLowerAddress(int)));
	connect(upperAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateUpperAddress(int)));
	setLayout(layout);
}

void ModbusRtuDeviceTSvConfWidget::updateReadAddress(int newAddress)
{
	updateAttribute("readaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateWriteAddress(int newAddress)
{
	updateAttribute("writeaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateFixedRange(bool fixed)
{
	if(fixed)
	{
		updateAttribute("fixedrange", "true");
		boundsLayout->setCurrentIndex(1);
	}
	else
	{
		updateAttribute("fixedrange", "false");
		boundsLayout->setCurrentIndex(0);
	}
}

void ModbusRtuDeviceTSvConfWidget::updateLower(const QString &lower)
{
	updateAttribute("fixedlower", lower);
}

void ModbusRtuDeviceTSvConfWidget::updateUpper(const QString &upper)
{
	updateAttribute("fixedupper", upper);
}

void ModbusRtuDeviceTSvConfWidget::updateLowerAddress(int newAddress)
{
	updateAttribute("loweraddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateUpperAddress(int newAddress)
{
	updateAttribute("upperaddress", QString("%1").arg(newAddress));
}

@ The configuration widgets need to be registered.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("modbusrtuport", ModbusRtuPortConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbusrtudevice", ModbusRtuDeviceConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturepv", ModbusRtuDeviceTPvConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturesv", ModbusRtuDeviceTSvConfWidget::staticMetaObject);

@ A |NodeInserter| for the driver configuration widget is also needed. Note
that this is temporarily disabled. These configuration widgets will become
useful when I rearchitect the Modbus RTU support in a future release.

@<Register top level device configuration nodes@>=
inserter = new NodeInserter(tr("Modbus RTU Port"), tr("Modbus RTU Port"), "modbusrtuport", NULL);
topLevelNodeInserters.append(inserter);

