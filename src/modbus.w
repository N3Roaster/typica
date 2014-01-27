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

@ From here we need to provide a widget for configuring a particular device.
At a minimum this would require setting the station number to a value between
0 and 255. Zero is typically the broadcast address which reaches all devices
on the bus and is not generally recommended for use except in particular
circumstances. There are, however, a number of settings that influence all of
the currently supported child nodes and these settings are in the device
configuration widget instead of requiring that information to be duplicated
across multiple child nodes.

The Modbus RTU protocol is very general in scope and leaves many of the
details of how to do certain things up to the manufacturer. For rudimentary
support of devices using this protocol, the documentation for several devices
was consulted and a test rig with one device was set up. There are a number of
assumptions made for this initial support and to better support additional
device classes it may become necessary to expand on what is provided initially.
The primary focus presently is on the use of PID controllers as temperature
indicators with the ability to modify a set value in the case where this is
used as a controller rather than just a display.

All of the devices studied prior to adding this support made use of scaled
integer representation. In order to correctly determine the measured process
value it is necessary to know the unit of the measurement and the position of
the decimal point. It is generally possible to query this information, however
it may be useful to provide a way to specify fixed values in the event that a
device exposes these details in a way that is incompatible with my assumptions.

@<Class declarations@>=
class ModbusRtuDeviceConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuDeviceConfWidget(DeviceTreeModel *model,
		                                            const QModelIndex &index);
	@[private slots@]:@/
		void updateStationNumber(int newStation);
		void updateFixedUnit(bool newFixed);
		void updateFixedDecimal(bool newFixed);
		void updateUnit(const QString &newUnit);
		void updateUnitAddress(int newAddress);
		void updateValueF(int newValue);
		void updateValueC(int newValue);
		void updatePrecisionAddress(int newAddress);
		void updatePrecisionValue(int newValue);
	private:@/
		QStackedLayout *unitSpecificationLayout;
		QStackedLayout *decimalSpecificationLayout;
};

@ This widget has a number of differences from previous configuration widgets.
Perhaps most significantly there are controls which do not provide a text based
signal on state change. We also set certain controls as disabled when the
provided values are not relevant to operations such as when switching between
fixed decimal position and looking up decimal position from the device. Aside
from these details the widget operates according to the same principles as the
other widgets already seen.

@<ModbusRtuDeviceConfWidget implementation@>=
ModbusRtuDeviceConfWidget::ModbusRtuDeviceConfWidget(DeviceTreeModel *model,
                                                     const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index),
	unitSpecificationLayout(new QStackedLayout),
	decimalSpecificationLayout(new QStackedLayout)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QToolButton *addChannelButton = new QToolButton;
	addChannelButton->setText(tr("Add Channel"));
	NodeInserter *addTemperaturePV = new NodeInserter("Temperature Process Value",
	                                                  "Temperature Process Value",
													  "modbustemperaturepv");
	NodeInserter *addTemperatureSV = new NodeInserter("Temperature Set Value",
	                                                  "Temperature Set Value",
													  "modbustemperaturesv");
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
	QHBoxLayout *stationLayout = new QHBoxLayout;
	QLabel *stationLabel = new QLabel(tr("Station:"));
	QSpinBox *stationNumber = new QSpinBox;
	stationNumber->setMinimum(0);
	stationNumber->setMaximum(255);
	stationLayout->addWidget(stationLabel);
	stationLayout->addWidget(stationNumber);
	layout->addLayout(stationLayout);
	QCheckBox *fixedUnit = new QCheckBox(tr("Fixed Temperature Unit"));
	layout->addWidget(fixedUnit);
	QWidget *fixedUnitPlaceholder = new QWidget(this);
	QHBoxLayout *fixedUnitLayout = new QHBoxLayout;
	QLabel *fixedUnitLabel = new QLabel(tr("Temperature Unit:"));
	QComboBox *fixedUnitSelector = new QComboBox;
	fixedUnitSelector->addItem("Fahrenheit");
	fixedUnitSelector->addItem("Celsius");
	fixedUnitLayout->addWidget(fixedUnitLabel);
	fixedUnitLayout->addWidget(fixedUnitSelector);
	fixedUnitPlaceholder->setLayout(fixedUnitLayout);
	unitSpecificationLayout->addWidget(fixedUnitPlaceholder);
	QWidget *queriedUnitPlaceholder = new QWidget(this);
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
	QWidget *fixedPrecisionPlaceholder = new QWidget(this);
	QFormLayout *fixedPrecisionLayout = new QFormLayout;
	QSpinBox *fixedPrecisionValue = new QSpinBox;
	fixedPrecisionValue->setMinimum(0);
	fixedPrecisionValue->setMaximum(9);
	fixedPrecisionLayout->addRow("Places after the decimal point:",
	                             fixedPrecisionValue);
	fixedPrecisionPlaceholder->setLayout(fixedPrecisionLayout);
	decimalSpecificationLayout->addWidget(fixedPrecisionPlaceholder);
	QWidget *queriedPrecisionPlaceholder = new QWidget(this);
	QFormLayout *queriedPrecisionLayout = new QFormLayout;
	ShortHexSpinBox *precisionAddress = new ShortHexSpinBox;
	queriedPrecisionLayout->addRow("Function 0x03 Decimal Position Address:",
	                                    precisionAddress);
	queriedPrecisionPlaceholder->setLayout(queriedPrecisionLayout);
	decimalSpecificationLayout->addWidget(queriedPrecisionPlaceholder);
	layout->addLayout(decimalSpecificationLayout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "station")
		{
			stationNumber->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fixedunit")
		{
			if(node.attribute("value") == "true")
			{
				fixedUnit->setCheckState(Qt::Checked);
			}
			else if(node.attribute("value") == "false")
			{
				fixedUnit->setCheckState(Qt::Unchecked);
			}
		}
		else if(node.attribute("name") == "fixedprecision")
		{
			fixedPrecisionValue->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "unit")
		{
			fixedUnitSelector->setCurrentIndex(fixedUnitSelector->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "unitaddress")
		{
			unitAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fvalue")
		{
			valueF->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "cvalue")
		{
			valueC->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "precisionaddress")
		{
			precisionAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "precision")
		{
			fixedPrecisionValue->setValue(node.attribute("value").toInt());
		}
	}
	updateStationNumber(stationNumber->value());
	updateFixedUnit(fixedUnit->isChecked());
	updateFixedDecimal(fixedPrecision->isChecked());
	updateUnit(fixedUnitSelector->currentText());
	updateUnitAddress(unitAddress->value());
	updateValueF(valueF->value());
	updateValueC(valueC->value());
	updatePrecisionAddress(precisionAddress->value());
	updatePrecisionValue(fixedPrecisionValue->value());
	connect(stationNumber, SIGNAL(valueChanged(int)),
	        this, SLOT(updateStationNumber(int)));
	connect(fixedUnitSelector, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateUnit(QString)));
	connect(unitAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateUnitAddress(int)));
	connect(valueF, SIGNAL(valueChanged(int)),
	        this, SLOT(updateValueF(int)));
	connect(valueC, SIGNAL(valueChanged(int)),
	        this, SLOT(updateValueC(int)));
	connect(fixedUnit, SIGNAL(toggled(bool)),
	        this, SLOT(updateFixedUnit(bool)));
	connect(fixedPrecision, SIGNAL(toggled(bool)),
	        this, SLOT(updateFixedDecimal(bool)));
	connect(fixedPrecisionValue, SIGNAL(valueChanged(int)),
	        this, SLOT(updatePrecisionValue(int)));
	connect(precisionAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updatePrecisionAddress(int)));
	setLayout(layout);
}

void ModbusRtuDeviceConfWidget::updateStationNumber(int newStation)
{
	updateAttribute("station", QString("%1").arg(newStation));
}

void ModbusRtuDeviceConfWidget::updateFixedUnit(bool newFixed)
{
	if(newFixed)
	{
		unitSpecificationLayout->setCurrentIndex(0);
		updateAttribute("fixedunit", "true");
	}
	else
	{
		unitSpecificationLayout->setCurrentIndex(1);
		updateAttribute("fixedunit", "false");
	}
}

void ModbusRtuDeviceConfWidget::updateFixedDecimal(bool newFixed)
{
	if(newFixed)
	{
		decimalSpecificationLayout->setCurrentIndex(0);
		updateAttribute("fixedprecision", "true");
	}
	else
	{
		decimalSpecificationLayout->setCurrentIndex(1);
		updateAttribute("fixedprecision", "false");
	}
}

void ModbusRtuDeviceConfWidget::updateUnit(const QString &newUnit)
{
	updateAttribute("unit", newUnit);
}

void ModbusRtuDeviceConfWidget::updateUnitAddress(int newAddress)
{
	updateAttribute("unitaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceConfWidget::updateValueF(int newValue)
{
	updateAttribute("fvalue", QString("%1").arg(newValue));
}

void ModbusRtuDeviceConfWidget::updateValueC(int newValue)
{
	updateAttribute("cvalue", QString("%1").arg(newValue));
}

void ModbusRtuDeviceConfWidget::updatePrecisionAddress(int newAddress)
{
	updateAttribute("precisionaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceConfWidget::updatePrecisionValue(int newValue)
{
	updateAttribute("precision", QString("%1").arg(newValue));
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

