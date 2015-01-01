@** Phidgets 1048.

\noindent Phidgets, Inc. has provided one of their four channel temperature
sensor devices so that support could be added to \pn{}. This was originally
planned for version 1.7, however early support was rushed in for the 1.6.3
release. As a result, this support is not full featured, but it should still be
adequate for the most common uses.

Two configuration widgets are required. The first is for the device as a whole.

@<Class declarations@>=
class PhidgetsTemperatureSensorConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE PhidgetsTemperatureSensorConfWidget(DeviceTreeModel *model,
                                                        const QModelIndex &index);
	private slots:
		void addChannel();
		void updateRate(int ms);
};

@ This widget allows specification of a device wide sample rate and allows
adding channels for the device to monitor. The device specifications indicate
temperature updates happen up to 25 times per second, but this is generally
excessive for \pn{} so a default rate is set to a multiple of this close to
3 updates per second. There are other options for collecting measurements from
this device and I have not yet had time to experiment with all of the options
to determine the best approach suitable for coffee roasting applications.

@<Phidgets implementation@>=
PhidgetsTemperatureSensorConfWidget::PhidgetsTemperatureSensorConfWidget(DeviceTreeModel *model,
                                                                         const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QPushButton *addChannelButton = new QPushButton(tr("Add Channel"));
	QSpinBox *sampleRate = new QSpinBox;
	sampleRate->setMinimum(40);
	sampleRate->setMaximum(600);
	sampleRate->setSingleStep(40);
	sampleRate->setValue(360);

	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "sampleRate")
		{
			sampleRate->setValue(node.attribute("value").toInt());
		}
	}
	updateRate(sampleRate->value());

	connect(sampleRate, SIGNAL(valueChanged(int)), this, SLOT(updateRate(int)));
	connect(addChannelButton, SIGNAL(clicked()), this, SLOT(addChannel()));

	layout->addRow(addChannelButton);
	layout->addRow(tr("Sample rate:"), sampleRate);
	setLayout(layout);
}

@ Adding another channel is handled in the usual way, with the channel
configured in a separate widget.

@<Phidgets implementation@>=
void PhidgetsTemperatureSensorConfWidget::addChannel()
{
	insertChildNode(tr("Channel"), "phidgets1048channel");
}

@ Changes to the sample rate are saved as an attribute of the node as usual.

@<Phidgets implementation@>=
void PhidgetsTemperatureSensorConfWidget::updateRate(int ms)
{
	updateAttribute("sampleRate", QString("%1").arg(ms));
}

@ The other required configuration widget is for a single channel.

@<Class declarations@>=
class PhidgetTemperatureSensorChannelConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE PhidgetTemperatureSensorChannelConfWidget(DeviceTreeModel *model,
                                                              const QModelIndex &index);
	private slots:
		void updateColumnName(const QString &value);
		void updateHidden(bool hidden);
		void updateTC(int index);
		void updateChannel(int channel);
	private:
		QComboBox *tcType;
};

@ For each channel it is necessary to specify which channel of the device
measurements will come in on. The thermocouple type should be set to match the
type of the thermocouple attached to that channel. The column name and if the
channel is hidden has the same meaning as in channels on other devices.

@<Phidgets implementation@>=
PhidgetTemperatureSensorChannelConfWidget::PhidgetTemperatureSensorChannelConfWidget(
	DeviceTreeModel *model, const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index),
	tcType(new QComboBox)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *columnName = new QLineEdit;
	layout->addRow(tr("Column Name:"), columnName);
	QCheckBox *hideSeries = new QCheckBox("Hide this channel");
	layout->addRow(hideSeries);
	layout->addRow(tr("Thermocouple Type:"), tcType);
	tcType->addItem("Type K", "1");
	tcType->addItem("Type J", "2");
	tcType->addItem("Type E", "3");
	tcType->addItem("Type T", "4");
	QSpinBox *channel = new QSpinBox;
	layout->addRow(tr("Channel:"), channel);
	channel->setMinimum(0);
	channel->setMaximum(3);
	setLayout(layout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "columnname")
		{
			columnName->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "hidden")
		{
			hideSeries->setChecked(node.attribute("value") == "true");
		}
		else if(node.attribute("name") == "tctype")
		{
			tcType->setCurrentIndex(tcType->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "channel")
		{
			channel->setValue(node.attribute("value").toInt());
		}
	}
	updateColumnName(columnName->text());
	updateHidden(hideSeries->isChecked());
	updateTC(tcType->currentIndex());
	updateChannel(channel->value());
	connect(columnName, SIGNAL(textEdited(QString)), this, SLOT(updateColumnName(QString)));
	connect(hideSeries, SIGNAL(toggled(bool)), this, SLOT(updateHidden(bool)));
	connect(tcType, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTC(int)));
	connect(channel, SIGNAL(valueChanged(int)), this, SLOT(updateChannel(int)));
}

@ Channel configuration settings are persisted as they are made.

@<Phidgets implementation@>=
void PhidgetTemperatureSensorChannelConfWidget::updateColumnName(const QString &value)
{
	updateAttribute("columnname", value);
}

void PhidgetTemperatureSensorChannelConfWidget::updateHidden(bool hidden)
{
	updateAttribute("hidden", hidden ? "true" : "false");
}

void PhidgetTemperatureSensorChannelConfWidget::updateTC(int index)
{
	updateAttribute("tctype", tcType->itemData(index).toString());
}

void PhidgetTemperatureSensorChannelConfWidget::updateChannel(int channel)
{
	updateAttribute("channel", QString("%1").arg(channel));
}

@ The configuration widgets need to be registered so they can be instantiated as
appropriate.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("phidgets1048",
	PhidgetsTemperatureSensorConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("phidgets1048channel",
	PhidgetTemperatureSensorChannelConfWidget::staticMetaObject);

@ A |NodeInserter| for the device node is also required, but this should only
be provided if the required library is installed.

@<Register top level device configuration nodes@>=
QLibrary phidgetsCheck("phidget21");
if(phidgetsCheck.load())
{
	inserter = new NodeInserter(tr("Phidgets 1048"), tr("Phidgets 1048"),
		"phidgets1048", NULL);
	topLevelNodeInserters.append(inserter);
	phidgetsCheck.unload();
}
else
{
	phidgetsCheck.setFileName("Phidget21.framework/phidget21");
	if(phidgetsCheck.load())
	{
		inserter = new NodeInserter(tr("Phidgets 1048"), tr("Phidgets 1048"),
		"phidgets1048", NULL);
		topLevelNodeInserters.append(inserter);
		phidgetsCheck.unload();
	}
}

@ As usual, a class representing the device is provided.

@<Class declarations@>=
class PhidgetsTemperatureSensor : public QObject
{
	Q_OBJECT
	public:
		Q_INVOKABLE PhidgetsTemperatureSensor(const QModelIndex &deviceIndex);
		Q_INVOKABLE int channelCount();
		Channel* getChannel(int channel);
		Q_INVOKABLE bool isChannelHidden(int channel);
		Q_INVOKABLE QString channelColumnName(int channel);
		Q_INVOKABLE QString channelIndicatorText(int channel);
	public slots:
		void start();
		void stop();
	private slots:
		void getMeasurements();
	private:
		QList<int> channelIndices;
		QList<int> tctypes;
		QList<Channel*> channelList;
		QMap<int, Channel*> channelMap;
		QList<bool> hiddenState;
		QList<QString> columnNames;
		QList<QString> indicatorTexts;
		QLibrary driver;
		QTimer sampleTimer;
		void *device;
		@<Phidgets 1048 function pointers@>@;
};

@ The constructor uses the configuration data to set up the interface used for
integration with the logging view.

@<Phidgets implementation@>=
PhidgetsTemperatureSensor::PhidgetsTemperatureSensor(const QModelIndex &index)
	: QObject(NULL), driver("phidget21"), device(NULL)
{
	DeviceTreeModel *model = (DeviceTreeModel *)(index.model());
	QDomElement deviceReferenceElement =
		model->referenceElement(model->data(index, Qt::UserRole).toString());
	QDomNodeList deviceConfigData = deviceReferenceElement.elementsByTagName("attribute");
	QDomElement node;
	for(int i = 0; i < deviceConfigData.size(); i++)
	{
		node = deviceConfigData.at(i).toElement();
		if(node.attribute("name") == "sampleRate")
		{
			sampleTimer.setInterval(node.attribute("value").toInt());
		}
	}
	if(model->hasChildren(index))
	{
		for(int i = 0; i < model->rowCount(index); i++)
		{
			QModelIndex channelIndex = model->index(i, 0, index);
			QDomElement channelReference = model->referenceElement(model->data(channelIndex, 32).toString());
			QDomElement channelReferenceElement = model->referenceElement(model->data(channelIndex, Qt::UserRole).toString());
			QDomNodeList channelConfigData = channelReferenceElement.elementsByTagName("attribute");
			for(int j = 0; j < channelConfigData.size(); j++)
			{
				node = channelConfigData.at(j).toElement();
				if(node.attribute("name") == "channel")
				{
					int channelID = node.attribute("value").toInt();
					channelIndices.append(channelID);
					Channel* channel = new Channel;
					channelList.append(channel);
					channelMap.insert(channelID, channel);
				}
				else if(node.attribute("name") == "hidden")
				{
					hiddenState.append(node.attribute("value") == "true");
				}
				else if(node.attribute("name") == "columnname")
				{
					columnNames.append(node.attribute("value"));
				}
				else if(node.attribute("name") == "tctype")
				{
					tctypes.append(node.attribute("value").toInt());
				}
			}
			indicatorTexts.append(model->data(channelIndex, Qt::DisplayRole).toString());
		}
	}
}

@ There is a distinction between logical and physical channels. Physical
channels are specified as a configuration attribute and are used for
communication with hardware. Logical channels are determined by the order of
nodes in the configuration and are used for integrating device support with the
rest of the program.

@<Phidgets implementation@>=
int PhidgetsTemperatureSensor::channelCount()
{
	return channelList.length();
}

Channel* PhidgetsTemperatureSensor::getChannel(int channel)
{
	return channelList.at(channel);
}

@ Some information is available about each channel.

@<Phidgets implementation@>=
bool PhidgetsTemperatureSensor::isChannelHidden(int channel)
{
	return hiddenState.at(channel);
}

QString PhidgetsTemperatureSensor::channelColumnName(int channel)
{
	if(channel >= 0 && channel < columnNames.length())
	{
		return columnNames.at(channel);
	}
	return QString();
}

QString PhidgetsTemperatureSensor::channelIndicatorText(int channel)
{
	if(channel >= 0 && channel < indicatorTexts.length())
	{
		return indicatorTexts.at(channel);
	}
	return QString();
}

@ To avoid introducing dependencies on a library that is only needed for
hardware that may not exist, the phidget21 library is only loaded at runtime
if it is needed. Some function pointers and associated types are, therefore,
required. This approach also means the associated header does not need to
exist at compile time.

@<Phidgets 1048 function pointers@>=
typedef int (*PhidgetHandleOnly)(void *);
typedef int (*PhidgetHandleInt)(void *, int);
typedef int (*PhidgetHandleIntInt)(void *, int, int);
typedef int (*PhidgetHandleIntDoubleOut)(void *, int, double*);
PhidgetHandleOnly createDevice;
PhidgetHandleInt openDevice;
PhidgetHandleInt waitForOpen;
PhidgetHandleIntInt setTCType;
PhidgetHandleIntDoubleOut getTemperature;
PhidgetHandleOnly closeDevice;
PhidgetHandleOnly deleteDevice;

@ Library loading is deferred until we are ready to open a device.

@<Phidgets implementation@>=
void PhidgetsTemperatureSensor::start()
{
	if(!driver.load())
	{
		driver.setFileName("Phidget21.framework/phidget21");
		if(!driver.load())
		{
			QMessageBox::critical(NULL, tr("Typica: Driver not found"),
				tr("Failed to find phidget21. Please install it."));
			return;
		}
	}
	if((createDevice = (PhidgetHandleOnly) driver.resolve("CPhidgetTemperatureSensor_create")) == 0 || @|
       (openDevice = (PhidgetHandleInt) driver.resolve("CPhidget_open")) == 0 || @|
       (waitForOpen = (PhidgetHandleInt) driver.resolve("CPhidget_waitForAttachment")) == 0 || @|
       (setTCType = (PhidgetHandleIntInt) driver.resolve("CPhidgetTemperatureSensor_setThermocoupleType")) == 0 || @|
       (getTemperature = (PhidgetHandleIntDoubleOut) driver.resolve("CPhidgetTemperatureSensor_getTemperature")) == 0 || @|
       (closeDevice = (PhidgetHandleOnly) driver.resolve("CPhidget_close")) == 0 || @|
       (deleteDevice = (PhidgetHandleOnly) driver.resolve("CPhidget_delete")) == 0)
	{
		QMessageBox::critical(NULL, tr("Typica: Link error"),
			tr("Failed to link a required symbol in phidget21."));
		return;
	}
	createDevice(&device);
	openDevice(device, -1);
	int error;
	if(error = waitForOpen(device, 10000))
	{
		closeDevice(device);
		deleteDevice(device);
		QMessageBox::critical(NULL, tr("Typica: Failed to Open Device"),
			tr("CPhidget_waitForAttachment returns error %n", 0, error));
		return;
	}
	for(int i = 0; i < channelIndices.length(); i++)
	{
		setTCType(device, channelIndices.at(i), tctypes.at(i));
	}
	connect(&sampleTimer, SIGNAL(timeout()), this, SLOT(getMeasurements()));
	sampleTimer.start();
}

@ Once the device is started, we periodically request measurements and pass
them to the appropriate |Channel|.

@<Phidgets implementation@>=
void PhidgetsTemperatureSensor::getMeasurements()
{
	double value = 0.0;
	QTime time = QTime::currentTime();
	foreach(int i, channelIndices)
	{
		getTemperature(device, i, &value);
		Measurement measure(value * 9.0 / 5.0 + 32.0, time);
		channelMap[i]->input(measure);
	}
}

@ Some clean up is needed in the |stop()| method.

@<Phidgets implementation@>=
void PhidgetsTemperatureSensor::stop()
{
	sampleTimer.stop();
	closeDevice(device);
	deleteDevice(device);
	driver.unload();
}

@ The implementation currently goes into typica.cpp.

@<Class implementations@>=
@<Phidgets implementation@>@;

@ The |PhidgetsTemperatureSensor| needs to be available from the host
environment. This detail is likely to change in the future.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructPhidgetsTemperatureSensor);
value = engine->newQMetaObject(&PhidgetsTemperatureSensor::staticMetaObject, constructor);
engine->globalObject().setProperty("PhidgetsTemperatureSensor", value);

@ Two function prototypes are needed.

@<Function prototypes for scripting@>=
QScriptValue constructPhidgetsTemperatureSensor(QScriptContext *context, QScriptEngine *engine);
QScriptValue Phidgets_getChannel(QScriptContext *context, QScriptEngine *engine);

@ The script constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructPhidgetsTemperatureSensor(QScriptContext *context, QScriptEngine *engine)
{
	if(context->argumentCount() != 1)
	{
		context->throwError("Incorrect number of arguments passed to "@|
                            "PhidgetsTemperatureSensor constructor. This takes "@|
                            "a QModelIndex.");
	}
	QScriptValue object = engine->newQObject(new PhidgetsTemperatureSensor(argument<QModelIndex>(0, context)), QScriptEngine::ScriptOwnership);
	setQObjectProperties(object, engine);
	object.setProperty("getChannel", engine->newFunction(Phidgets_getChannel));
	return object;
}

@ As usual, a wrapper is needed for getting channels.

@<Functions for scripting@>=
QScriptValue Phidgets_getChannel(QScriptContext *context, QScriptEngine *engine)
{
	PhidgetsTemperatureSensor *self = getself<PhidgetsTemperatureSensor *>(context);
	QScriptValue object;
	if(self)
	{
		object = engine->newQObject(self->getChannel(argument<int>(0, context)));
		setChannelProperties(object, engine);
	}
	return object;
}
