@** Unsupported Serial Port Devices

\noindent There are many data acquisition products which connect over or
present themselves as a serial port and it has become relatively easy for
hardware tinkerers to develop new devices matching this description. In this
space there is no apparent consideration given to interoperability and with
some devices the communications protocol even changes significantly between
firmware revisions. There are far too many devices like this to support
everything. At the same time, there are people who have these devices, are
capable of programming the basic communications handling, but have difficulty
with all of the supporting code that must be written to properly integrate with
the rest of \pn. By providing an in-program environment that handles much of
the boilerplate and allowing people to write scripts implementing these
protocols without the need to modify core \pn code or recompile the program,
these people may find it easier to make their existing hardware work. Such
scripts can also serve as prototypes for later integration.

It is common among these devices that port settings aside from the port name
are fixed, but there may be other characteristics that are configurable on a
per-device or per-channel basis. As it is impossible to know what these
details might be, the configuration widgets for these devices and channels
simply provide space to provide key value pairs which are provided to the host
environment. Common configurations will have a device node representing a
single logical device, usually a single physical device but this is not in any
way enforced, and one child node per channel, the details of which are made
available to the device script and are also used to integrate with the logging
view.

The use of the word serial should be considered legacy of the initial
conception of this feature. The implementation here is sufficiently generic
that there is no reason this could not be extended to cover devices that are
interfaced through USB HID, Bluetooth, COM, output piped from an external
console program, devices interfaced through arbitrary libraries, or any other
class of device not directly supported in the core code should there be an
interest in these.

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

@ At present, implementations are not broken out to a separate file. This
should be changed at some point.

@<Class implementations@>=
@<UnsupportedSerialDeviceConfWidget implementation@>

