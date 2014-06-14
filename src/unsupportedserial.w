@** Script Driven Devices.

\noindent There are many data acquisition products that are reasonable to use
with \pn which are not natively supported due to lack of available hardware
for testing, lack of time or money to develop that support, or lack of
documentation. It has also become relatively simple for hardware tinkerers to
develop new devices matching this description as well. Vendors in this space
tend to give inadequate consideration to interoperability and with some devices
the communications protocol used changes significantly between firmware
revisions. There are simply far too many devices like this to support
everything. At the same time there are people with these devices who are
capable of programming the basic communications handling but have difficulty
with integrating that with \pn. By providing an in-program environment that
handles much of the boilerplate and allowing people to write scripts
implementing these protocols without the need to modify core \pn code or
recompile the program, these people may find it easier to make their existing
hardware work. Such scripts can also serve as prototypes for native support.

Configuration widgets for these devices allow key value pairs to be specified
both at the device level and on a per-channel basis. This is intentionally kept
generic as it is impossible to know what configurable details may be required.
Common configurations will have a device node representing a single logical
device, usually a single physical device but this is not in any way enforced,
and one child node per channel. These details are made available to the device
script and are used to integrate with the logging view.

Some of the naming conventions used here are legacy of the initial conception
of this feature and should be changed before release if there is time to do so.
While initial support will be focused on devices that present as a serial port,
there is no reason this could not be extended to cover devices that are
interfaced through USB HID, Bluetooth, COM, output piped from an external
console program, devices interfaced through arbitrary libraries, or any other
class of device not directly supported in the core code should there be an
interest in any of these.

@<Class declarations@>=
class UnsupportedSerialDeviceConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE UnsupportedSerialDeviceConfWidget(DeviceTreeModel *model,
		                                              const QModelIndex &index);
	private slots:
		void updateConfiguration();
		void saveScript();
		void addChannel();
	private:
		SaltModel *deviceSettingsModel;
		QTextEdit *scriptEditor;
};

@ The device configuration widget consists of two tabs. One tab provides a
button for adding channels and an area for entering device specific
configuration details. The other provides an area for entering the device
script. This may be extended later to provide better editing, testing, and
debugging support, but the initial concern is simply having a working feature.

@<UnsupportedSerialDeviceConfWidget implementation@>=
UnsupportedSerialDeviceConfWidget::UnsupportedSerialDeviceConfWidget(DeviceTreeModel *model,
                                                                     const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index),
	deviceSettingsModel(new SaltModel(2)),
	scriptEditor(new QTextEdit)
{
	QVBoxLayout *dummyLayout = new QVBoxLayout;
	QTabWidget *central = new QTabWidget;
	QWidget *deviceConfigurationWidget = new QWidget;
	QVBoxLayout *deviceConfigurationLayout = new QVBoxLayout;
	QPushButton *addChannelButton = new QPushButton(tr("Add Channel"));
	deviceConfigurationLayout->addWidget(addChannelButton);
	connect(addChannelButton, SIGNAL(clicked()), this, SLOT(addChannel()));
	QLabel *deviceSettingsLabel = new QLabel(tr("Device Settings:"));
	deviceConfigurationLayout->addWidget(deviceSettingsLabel);
	QTableView *deviceSettingsView = new QTableView;
	deviceSettingsModel->setHeaderData(0, Qt::Horizontal, tr("Key"));
	deviceSettingsModel->setHeaderData(1, Qt::Horizontal, tr("Value"));
	deviceSettingsView->setModel(deviceSettingsModel);
	deviceConfigurationLayout->addWidget(deviceSettingsView);
	
	deviceConfigurationWidget->setLayout(deviceConfigurationLayout);
	central->addTab(deviceConfigurationWidget, tr("Configuration"));
	central->addTab(scriptEditor, tr("Script"));
	dummyLayout->addWidget(central);
	
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "keys" || node.attribute("name") == "values")
		{
			int column = 0;
			if(node.attribute("name") == "values")
			{
				column = 1;
			}
			QString data = node.attribute("value");
			if(data.length() > 3)
			{
				data.chop(2);
				data = data.remove(0, 2);
			}
			QStringList keyList = data.split(", ");
			for(int j = 0; j < keyList.size(); j++)
			{
				deviceSettingsModel->setData(deviceSettingsModel->index(j, column),
				                             QVariant(keyList.at(j)),
				                             Qt::EditRole);
			}
		}
		else if(node.attribute("name") == "script")
		{
			scriptEditor->setPlainText(node.attribute("value"));
		}
	}
	
	connect(deviceSettingsModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
	        this, SLOT(updateConfiguration()));
	connect(scriptEditor, SIGNAL(textChanged()), this, SLOT(saveScript()));
	setLayout(dummyLayout);
}

@ Device configuration data is entered through an ordinary |QTableView| with a
|SaltModel| backing. The original use case for that model does not apply here,
but that model does ensure that additional blank rows are added as needed so
that arbitrarily many key value pairs can be entered. When data changes in the
model we write the full content of the model out. Note that commas may not be
used in keys or values. For keys in which lists make sense, a different
delimiter must be chosen.

@<UnsupportedSerialDeviceConfWidget implementation@>=
void UnsupportedSerialDeviceConfWidget::updateConfiguration()
{
	updateAttribute("keys", deviceSettingsModel->arrayLiteral(0, Qt::DisplayRole));
	updateAttribute("values", deviceSettingsModel->arrayLiteral(1, Qt::DisplayRole));
}

@ Every time the script text is changed, the new version of the script is
saved. My expectation is that scripts will either be small or that they will be
pasted in from outside of \pn so that this decision will not cause usability
issues, however if I am wrong about this there may be a need to handle this
more intelligently.

@<UnsupportedSerialDeviceConfWidget implementation@>=
void UnsupportedSerialDeviceConfWidget::saveScript()
{
	updateAttribute("script", scriptEditor->toPlainText());
}

@ Typica requires channel nodes to simplify integration with other existing
device code. Providing a new node type allows arbitrary attributes to be
configured on a per-channel basis without resorting to strange conventions in
the device configuration.

@<UnsupportedSerialDeviceConfWidget implementation@>=
void UnsupportedSerialDeviceConfWidget::addChannel()
{
	insertChildNode(tr("Channel"), "unsupporteddevicechannel");
}

@ Channel configuration for unsupported devices is like unsupported device
configuration in that arbitrary key value pairs may be entered for use by the
device script. Conventions common to all other channel node types are also
present here.

@<Class declarations@>=
class UnsupportedDeviceChannelConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE UnsupportedDeviceChannelConfWidget(DeviceTreeModel *model,
		                                               const QModelIndex &index);
	private slots:
		void updateColumnName(const QString &value);
		void updateHidden(bool hidden);
		void updateConfiguration();
	private:
		SaltModel *channelSettingsModel;
};

@ The constructor is typical for for channel node configuraion widgets.

@<UnsupportedSerialDeviceConfWidget implementation@>=
UnsupportedDeviceChannelConfWidget::UnsupportedDeviceChannelConfWidget(DeviceTreeModel *model,
                                                                       const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index),
	channelSettingsModel(new SaltModel(2))
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *columnName = new QLineEdit;
	layout->addRow(tr("Column Name:"), columnName);
	QCheckBox *hideSeries = new QCheckBox("Hide this channel");
	layout->addRow(hideSeries);
	QTableView *channelSettings = new QTableView;
	channelSettingsModel->setHeaderData(0, Qt::Horizontal, "Key");
	channelSettingsModel->setHeaderData(1, Qt::Horizontal, "Value");
	channelSettings->setModel(channelSettingsModel);
	layout->addRow(channelSettings);
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
		else if(node.attribute("name") == "keys" || node.attribute("name") == "values")
		{
			int column = 0;
			if(node.attribute("name") == "values")
			{
				column = 1;
			}
			QString data = node.attribute("value");
			if(data.length() > 3)
			{
				data.chop(2);
				data = data.remove(0, 2);
			}
			QStringList keyList = data.split(", ");
			for(int j = 0; j < keyList.size(); j++)
			{
				channelSettingsModel->setData(channelSettingsModel->index(j, column),
				                              QVariant(keyList.at(j)),
				                              Qt::EditRole);
			}
		}
	}
	connect(columnName, SIGNAL(textEdited(QString)), this, SLOT(updateColumnName(QString)));
	connect(hideSeries, SIGNAL(toggled(bool)), this, SLOT(updateHidden(bool)));
	connect(channelSettingsModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
	        this, SLOT(updateConfiguration()));
}

@ Arbitrary channel configuration data is handled in the same way as device
level settings while the column name and hidden status is handled in the same
way as they are in other channel nodes.

@<UnsupportedSerialDeviceConfWidget implementation@>=
void UnsupportedDeviceChannelConfWidget::updateColumnName(const QString &value)
{
	updateAttribute("columnname", value);
}

void UnsupportedDeviceChannelConfWidget::updateHidden(bool hidden)
{
	updateAttribute("hidden", hidden ? "true" : "false");
}

void UnsupportedDeviceChannelConfWidget::updateConfiguration()
{
	updateAttribute("keys", channelSettingsModel->arrayLiteral(0, Qt::DisplayRole));
	updateAttribute("values", channelSettingsModel->arrayLiteral(1, Qt::DisplayRole));
}

@ The configuration widgets need to be registered so they can be instantiated
as appropriate.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("unsupporteddevicechannel",
	UnsupportedDeviceChannelConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("unsupporteddevice",
	UnsupportedSerialDeviceConfWidget::staticMetaObject);

@ A |NodeInserter| for the device node is also provided.

@<Register top level device configuration nodes@>=
inserter = new NodeInserter(tr("Other Device"), tr("Other Device"),
	"unsupporteddevice", NULL);
topLevelNodeInserters.append(inserter);

@ A device abstraction is not strictly required for this feature, however
having one greatly simplifies integrating this feature. At some point I would
like to revise other device abstraction classes so that a huge amount of
boilerplate associated with these can be removed from configuration documents.

This device abstraction includes features in a few particular categories. First
there are methods that are required for integrating the device with the logging
view. The logging view instantiates the device abstraction, passing in the
configuration data required to properly set up the device. It then is able to
query information about the measurement channels that have been configured for
this device and can set up all of the relevant indicators. Some device classes
may be able to produce annotations, so this class can be treated exactly the
same as any other annotation source. Another requested feature includes the
ability of a device to trigger the start and end of batches, so signals are
provided for this capability. Finally, there are methods associated with
starting and stopping the device. The |start()| method will be called when the
logging view has finished making all of the signal connections. The |stop()|
method will be called when the logging view is closed, giving script code the
chance to cleanly release any resources that must be held for device
communications.

@<Class declarations@>=
class JavaScriptDevice : public QObject
{
	Q_OBJECT
	public:
		Q_INVOKABLE JavaScriptDevice(const QModelIndex &deviceIndex,
		                             QScriptEngine *engine);
		Q_INVOKABLE int channelCount();
		Channel* getChannel(int channel);
		Q_INVOKABLE bool isChannelHidden(int channel);
		Q_INVOKABLE Units::Unit expectedChannelUnit(int channel);
		Q_INVOKABLE QString channelColumnName(int channel);
		Q_INVOKABLE QString channelIndicatorText(int channel);
	public slots:
		void setTemperatureColumn(int tcol);
		void setAnnotationColumn(int ncol);
		void start();
		void stop();
	signals:
		void annotation(QString note, int tcol, int ncol);
		void triggerStartBatch();
		void triggerStopBatch();
		void deviceStopRequested();
	private:
		QVariantMap deviceSettings;
		QString deviceScript;
		QList<Channel *> channelList;
		QList<bool> hiddenState;
		QList<Units::Unit> channelUnits;
		QList<QString> columnNames;
		QList<QString> indicatorTexts;
		QList<QVariantMap> channelSettings;
		int annotationTemperatureColumn;
		int annotationNoteColumn;
		QScriptEngine *scriptengine;
};

@ The |JavaScriptDevice| instance provides two interfaces. Its invokable
methods provide the information needed to integrate script driven devices with
a generic logging view. Additional information is also exposed through the host
environment running the device script. This means that the class requires
knowledge of the host environment, which it obtains through a script function
similar to what is done for window creation.

The name of the function is generic so this may be easily extended later to
create all device abstraction instances.

@<Function prototypes for scripting@>=
QScriptValue createDevice(QScriptContext *context, QScriptEngine *engine);

@ That method is made available to the scripting engine.

@<Set up the scripting engine@>=
engine->globalObject().setProperty("createDevice",
                                   engine->newFunction(createDevice));

@ This function currently creates a |JavaScriptDevice| from a device
configuration node which must be passed through as an argument.

@<Functions for scripting@>=
QScriptValue createDevice(QScriptContext *context, QScriptEngine *engine)@/
{
	QModelIndex deviceIndex = argument<QModelIndex>(0, context);
	JavaScriptDevice *device = new JavaScriptDevice(deviceIndex, engine);
	QScriptValue object = engine->newQObject(device);
	setQObjectProperties(object, engine);
	object.setProperty("getChannel", engine->newFunction(JavaScriptDevice_getChannel));
	return object;
}

@ The |start()| method is responsible for preparing the host environment and
executing the device script.

@<JavaScriptDevice implementation@>=
void JavaScriptDevice::start()
{
	QScriptValue object = scriptengine->newQObject(this);
	@<Expose device settings as object property@>@;
	@<Expose channels and channel settings to device script@>@;
	QScriptContext *context = scriptengine->currentContext();
	QScriptValue oldThis = context->thisObject();
	context->setThisObject(object);
	QScriptValue result = scriptengine->evaluate(deviceScript);
	QScriptEngine *engine = scriptengine;
	@<Report scripting errors@>@;
	context->setThisObject(oldThis);
}

@ Device settings are only needed from the device script itself. As such, these
are presented under a settings property available from the |this| object when
the script is run.

@<Expose device settings as object property@>=
QScriptValue settingsObject = scriptengine->newObject();
QVariantMap::const_iterator i = deviceSettings.constBegin();
while(i != deviceSettings.constEnd())
{
	settingsObject.setProperty(i.key(), i.value().toString());
	i++;
}
object.setProperty("settings", settingsObject);

@ While channels are available to the device script through the same
|getChannel()| interface used outside of the device script for integration
purposes, it is more convenient to have an array of channels with channel
specific settings as properties of the channel.

@<Expose channels and channel settings to device script@>=
QScriptValue channelsArray = scriptengine->newArray(channelCount());
for(int i = 0; i < channelCount(); i++)
{
	QScriptValue channelObject = scriptengine->newQObject(getChannel(i));
	QScriptValue channelSettingsObject = scriptengine->newObject();
	QVariantMap::const_iterator j = channelSettings.at(i).constBegin();
	while(j != channelSettings.at(i).constEnd())
	{
		channelSettingsObject.setProperty(j.key(), j.value().toString());
		j++;
	}
	channelObject.setProperty("settings", channelSettingsObject);
	channelsArray.setProperty(i, channelObject);
}
object.setProperty("channels", channelsArray);

@ Currently we require wrapper functions to work with channels in the host
environment.

@<Function prototypes for scripting@>=
QScriptValue JavaScriptDevice_getChannel(QScriptContext *context, QScriptEngine *engine);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue JavaScriptDevice_getChannel(QScriptContext *context, QScriptEngine *engine)
{
	JavaScriptDevice *self = getself<JavaScriptDevice *>(context);
	QScriptValue object;
	if(self)
	{
		object = engine->newQObject(self->getChannel(argument<int>(0, context)));
		setChannelProperties(object, engine);
	}
	return object;
}

@ The |stop()| method just fires off a signal that the script can hook into for
any required cleanup.

@<JavaScriptDevice implementation@>=
void JavaScriptDevice::stop()
{
	emit deviceStopRequested();
}

@ The constructor is responsible for all boilerplate initialization required
for integrating script defined devices with the logging view.

Note: At present expected units are assumed to be Fahrenheit. The configuration
widget must be updated to allow at least for control measurements and
eventually support for runtime defined units should also be added.

@<JavaScriptDevice implementation@>=
JavaScriptDevice::JavaScriptDevice(const QModelIndex &index,
                                   QScriptEngine *engine) :
	QObject(NULL), scriptengine(engine)
{
	DeviceTreeModel *model = (DeviceTreeModel *)(index.model());
	QDomElement deviceReferenceElement =
		model->referenceElement(model->data(index, Qt::UserRole).toString());
	QDomNodeList deviceConfigData = deviceReferenceElement.elementsByTagName("attribute");
	QDomElement node;
	QStringList deviceKeys;
	QStringList deviceValues;
	for(int i = 0; i < deviceConfigData.size(); i++)
	{
		node = deviceConfigData.at(i).toElement();
		if(node.attribute("name") == "keys")
		{
			QString data = node.attribute("value");
			if(data.length() > 3)
			{
				data.chop(2);
				data = data.remove(0, 2);
			}
			deviceKeys = data.split(", ");
		}
		else if(node.attribute("name") == "values")
		{
			QString data = node.attribute("value");
			if(data.length() > 3)
			{
				data.chop(2);
				data = data.remove(0, 2);
			}
			deviceValues = data.split(", ");
		}
		else if(node.attribute("name") == "script")
		{
			deviceScript = node.attribute("value");
		}
		deviceSettings.insert(node.attribute("name"), node.attribute("value"));
	}
	for(int i = 0; i < qMin(deviceKeys.length(), deviceValues.length()); i++)
	{
		deviceSettings.insert(deviceKeys[i], deviceValues[i]);
	}
	if(model->hasChildren(index))
	{
		for(int i = 0; i < model->rowCount(index); i++)
		{
			QModelIndex channelIndex = model->index(i, 0, index);
			QDomElement channelReference = model->referenceElement(model->data(channelIndex, 32).toString());
			channelList.append(new Channel);
			QDomElement channelReferenceElement =
				model->referenceElement(model->data(channelIndex, Qt::UserRole).toString());
			QDomNodeList channelConfigData =
				channelReferenceElement.elementsByTagName("attribute");
			QStringList channelKeys;
			QStringList channelValues;
			for(int j = 0; j < channelConfigData.size(); j++)
			{
				node = channelConfigData.at(j).toElement();
				if(node.attribute("name") == "keys")
				{
					QString data = node.attribute("value");
					if(data.length() > 3)
					{
						data.chop(2);
						data = data.remove(0, 2);
					}
					channelKeys = data.split(", ");
				}
				else if(node.attribute("name") == "values")
				{
					QString data = node.attribute("value");
					if(data.length() > 3)
					{
						data.chop(2);
						data = data.remove(0, 2);
					}
					channelValues = data.split(", ");
				}
				else if(node.attribute("name") == "hidden")
				{
					hiddenState.append(node.attribute("value") == "true");
				}
				else if(node.attribute("name") == "columnname")
				{
					columnNames.append(node.attribute("value"));
				}
			}
			QVariantMap cs;
			for(int j = 0; j < qMin(channelKeys.length(), channelValues.length()); j++)
			{
				cs.insert(channelKeys[j], channelValues[j]);
			}
			channelSettings.append(cs);
			indicatorTexts.append(model->data(channelIndex, Qt::DisplayRole).toString());
			channelUnits.append(Units::Fahrenheit);
		}
	}
}

@ Several methods are available to query information about the configured
channels.

@<JavaScriptDevice implementation@>=
int JavaScriptDevice::channelCount()
{
	return channelList.length();
}

Channel* JavaScriptDevice::getChannel(int channel)
{
	return channelList.at(channel);
}

bool JavaScriptDevice::isChannelHidden(int channel)
{
	return hiddenState.at(channel);
}

Units::Unit JavaScriptDevice::expectedChannelUnit(int channel)
{
	return channelUnits.at(channel);
}

QString JavaScriptDevice::channelColumnName(int channel)
{
	if(channel >= 0 && channel < columnNames.length())
	{
		return columnNames.at(channel);
	}
	return QString();
}

QString JavaScriptDevice::channelIndicatorText(int channel)
{
	return indicatorTexts.at(channel);
}

@ Two slots are provided for controlling the placement of annotations.

@<JavaScriptDevice implementation@>=
void JavaScriptDevice::setTemperatureColumn(int tcol)
{
	annotationTemperatureColumn = tcol;
}

void JavaScriptDevice::setAnnotationColumn(int ncol)
{
	annotationNoteColumn = ncol;
}

@ Device scripts must be able to produce measurements on a channel. To do this,
a function is provided for obtaining a timestamp. The returned timestamp should
not be examined as future changes may break assumptions about the content of
the timestamp.

@<Function prototypes for scripting@>=
QScriptValue getMeasurementTimestamp(QScriptContext *context, QScriptEngine *engine);

@ That method is made available to the scripting engine.

@<Set up the scripting engine@>=
engine->globalObject().setProperty("getMeasurementTimestamp",
                                   engine->newFunction(getMeasurementTimestamp));

@ At present this simply obtains the current system time. It is planned to
switch to a better quality clock in the future, but this should be done for
everything that uses |Measurement| objects at once.

@<Functions for scripting@>=
QScriptValue getMeasurementTimestamp(QScriptContext *, QScriptEngine *engine)@/
{
	return engine->toScriptValue<QTime>(QTime::currentTime());
}

@ At present, implementations are not broken out to a separate file. This
should be changed at some point.

@<Class implementations@>=
@<UnsupportedSerialDeviceConfWidget implementation@>
@<JavaScriptDevice implementation@>

@* Serial Ports.

\noindent The first use case for script driven devices was connecting to
devices which present themselves as a serial port. This covers a broad range
of data acquisition products. To provide this support, |QextSerialPort|, which
was already used to support some other hardware options, is directly exposed to
the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructSerialPort(QScriptContext *context, QScriptEngine *engine);
void setSerialPortProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue SerialPort_flush(QScriptContext *context, QScriptEngine *engine);

@ Our constructor is passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructSerialPort);
value = engine->newQMetaObject(&QextSerialPort::staticMetaObject, constructor);
engine->globalObject().setProperty("SerialPort", value);

@ At present we only support event driven communications and are not passing
any port settings through the constructor. Such functionality may be added in
the future, but it is not strictly necessary.

@<Functions for scripting@>=
QScriptValue constructSerialPort(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QextSerialPort());
	setSerialPortProperties(object, engine);
	return object;
}

@ Some properties of |QIODevice| are brought in as usual for similar subclasses
but we also add a wrapper around the |flush()| method.

@<Functions for scripting@>=
void setSerialPortProperties(QScriptValue value, QScriptEngine *engine)
{
	setQIODeviceProperties(value, engine);
	value.setProperty("flush", engine->newFunction(SerialPort_flush));
}

@ The wrapper around |flush()| is trivial.

@<Functions for scripting@>=
QScriptValue SerialPort_flush(QScriptContext *context, QScriptEngine *)
{
	QextSerialPort *self = getself<QextSerialPort *>(context);
	self->flush();
	return QScriptValue();
}


