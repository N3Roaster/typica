@** Support for Devices Using the DATAQ SDK.

\noindent Support for hardware from DATAQ Instruments is currently provided
through the DATAQ SDK. This means that this support is currently only available
on Microsoft Windows. The first planned supported device is the DI-145 with
support for the DI-148U planned later. The devices are sufficiently similar
that adding support for other devices from this manufacturer should be easy,
but I do not have hardware samples to use for testing with other devices. The
DI-145 additionally has a documented serial protocol which should make the
hardware usable without the DATAQ SDK both on Microsoft Windows and on other
platforms for which there is a suitable serial driver.

Originally the classes were surrounded with conditional compilation directives
but moc failed to generate the appropriate meta-objects on Windows when this
was done. The |DataqSdkDevice| and |DataqSdkDeviceImplementation| classes will
truly only work on Microsoft Windows at this time. Attempts to use it elsewhere
will not end well.

@<Class declarations@>=
class DataqSdkDeviceImplementation;
class DataqSdkDevice : public QObject
{
	Q_OBJECT
	DataqSdkDeviceImplementation *imp;
	private slots:
		void threadFinished();
	public:
		DataqSdkDevice(QString device);
		~DataqSdkDevice();
		Channel* newChannel(Units::Unit scale);
		Q_INVOKABLE void setClockRate(double Hz);
		Q_INVOKABLE void start();
		static QStringList detectPorts();
		static QStringList detectHardware(); // Friendly names
};

@ The |DataqSdkDevice| class has as a private member an instance of a class
called |DataqSdkDeviceImplementation|. The two classes together create and run
a new thread of execution. This thread spends most of its time blocking while
waiting for a new measurement to become available. When a new measurement is
available, that measurement is passed to the appropriate channel which in turn
passes it to any interested object.

Note that subclassing |QThread| in this way is no longer considered best
practice. This particular code architecture is based on code written when this
was considered the right thing to do, but it would be good to rewrite this to
not subclass |QThread| now that this is no longer required.

@<Class declarations@>=
class DataqSdkDeviceImplementation : public QThread
{
	Q_OBJECT
	public:
		DataqSdkDeviceImplementation();
		~DataqSdkDeviceImplementation();
		void run();
		@<DATAQ SDK library function pointers@>@;
		@<DataqSdkDeviceImplementation member data@>@;
	public slots:
		void measure();
	private:
		qint16 *buffer;
};

@ While the |DAQ| class for communicating with National Instruments devices
uses a single function pointer type, increased variety of function signatures
in the DATAQ SDK makes using several types a better option. This also
eliminates the need for explicit casts on the arguments.

@<DATAQ SDK library function pointers@>=
typedef struct di_inlist_struct {
	unsigned short chan;
	unsigned short diff;
	unsigned short gain;
	unsigned short unipolar;
	unsigned short dig_out_enable;
	unsigned short dig_out;
	unsigned short ave;
	unsigned short counter;
} DI_INLIST_STRUCT;

typedef int (PASCAL *FPDIOPEN)(unsigned);
typedef int (PASCAL *FPDICLOSE)(void);
typedef double (PASCAL *FPDISAMPLERATE)(double, long*, long*);
typedef double (PASCAL *FPDIMAXIMUMRATE)(double);
typedef int (PASCAL *FPDILISTLENGTH)(unsigned, unsigned);
typedef int (PASCAL *FPDIINLIST)(di_inlist_struct*);
typedef int* (PASCAL *FPDIBUFFERALLOC)(unsigned, unsigned);
typedef int (PASCAL *FPDISTARTSCAN)(void);
typedef unsigned (PASCAL *FPDISTATUSREAD)(short*, unsigned);
typedef unsigned (PASCAL *FPDIBUFFERSTATUS)(unsigned);
typedef int (PASCAL *FPDIBURSTRATE)(unsigned);
typedef int (PASCAL *FPDISTOPSCAN)(void);

FPDIOPEN di_open;
FPDICLOSE di_close;
FPDISAMPLERATE di_sample_rate;
FPDIMAXIMUMRATE di_maximum_rate;
FPDILISTLENGTH di_list_length;
FPDIINLIST di_inlist;
FPDIBUFFERALLOC di_buffer_alloc;
FPDISTARTSCAN di_start_scan;
FPDISTATUSREAD di_status_read;
FPDIBUFFERSTATUS di_buffer_status;
FPDIBURSTRATE di_burst_rate;
FPDISTOPSCAN di_stop_scan;

@ The |PASCAL| macro is defined in the {\tt windef.h} header file which will
need to be included. This modifies the mechanics of the function call. A
feature of the C language which C++ inherits is the ability to create variadic
functions. To facilitate this, when one function calls another, the function
making that call is responsible for cleaning up the stack. The function being
called has no reliable way of knowing how many and what type of arguments have
been passed if it is a variadic function, but this can be determined in the
calling function at compile time. This is effectively a compiler implementation
detail which is unimportant to the vast majority of application code. Use of
the |PASCAL| macro informs the compiler that the function being called will
clean up the stack itself. This precludes the use of variadic functions, but
results in a smaller executable. The choice of name for that macro is
unfortunate as arguments are placed on the stack in the order opposite of
calling conventions of the Pascal programming language, but these are
unimportant details so long as the resulting program works.

@<Header files to include@>=
#ifdef Q_OS_WIN32
#include <windef.h>
#else
#define PASCAL
#endif

@ |DataqSdkDeviceImplementation| maintains information about the device and the
channels the measurements are sent to.

@<DataqSdkDeviceImplementation member data@>=
bool isOpen;
double sampleRate;
long oversample;
long burstDivisor;
QString device;
unsigned deviceNumber;
QVector<Channel*> channelMap;

int error;
int channels;
bool ready;
QLibrary *driver;
QVector<Units::Unit> unitMap;
int *input_buffer;
QTimer *eventClock;
QMultiMap<int, double> smoother;

@ Most of the interesting work associated with the |DataqSdkDevice| class is
handled in the |measure()| method of |DataqSdkDeviceImplementation|. This
method will block until a measurement is available. Once |buffer| is filled by
|di_status_read()| that function returns and new |Measurement| objects are
created based on the information in the buffer. These measurements are sent to
|Channel| objects tracked by |channelMap|.

The buffered values are presented in terms of ADC counts. Before using these
values to convert to a voltage measurement, the two least significant binary
digits of the count are set to 0 to improve measurement accuracy as recommended
in the DATAQ SDK reference documentation.

One of the use cases for this class is using the data port provided on some
roasters from Diedrich Manufacturing. In this case there are three channels
that are used: one provides a 0-10V signal that maps to temperature
measurements of 32 to 1832 degrees F, one provides a signal in the same range
requiring distinguishing among three values for air flow settings, and one is
intended to show a percentage for the fuel setting. After experimenting with
the most direct approach, there are limitations of the hardware that complicate
matters for the channel representing bean temperature. The hardware is
providing a 14 bit value representing a signal in the range of +/-10V so as a
practical matter we only have 13 bits for temperature values. There is a desire
to present measurements with at least one digit after the decimal point,
meaning that we require 18,000 distinct values despite likely only ever seeing
values in the lower third of that range. A 13 bit value only allows 8,192
distinct values to be represented. The result of this is that stable signals
between representable values are coded in an inconsistent fashion which can be
seen as displayed measurements varying erratically. The usual solution to this
problem is to collect many measurements quickly and average them, which is a
reasonable thing to do with the sample rates available on DATAQ hardware.
Examining measurements at a higher sample rate unfortunately reveals a periodic
structure to the measurement error which averaging alone is not adequate to
solve. The quality of the measurements can be improved somewhat by removing the
extreme values from each set of measurements prior to averaging, however this
does not fully address the lower frequency error sources. Further improvements
can be made by maintaining a multimap of recent ADC count values to averaged
voltage values and producing results that take this slightly longer term data
into account. This is essential for obtaining a sufficiently stable low
temperature calibration value and introduces minimal additional measurement
latency during a roast.

At present smoothing is applied to the first data channel and no others. It
should be possible to enable or disable adaptive smoothing for all channels
independently to better handle different hardware configurations.

@<DataqSdkDevice implementation@>=
void DataqSdkDeviceImplementation::measure()
{
	unsigned count = channels * 40;
	di_status_read(buffer, count);
	QTime time = QTime::currentTime();
	for(unsigned int i = 0; i < count; i++)
	{
		buffer[i] = buffer[i] & 0xFFFC;
	}
	QList<int> countList;
	for(unsigned int i = 0; i < (unsigned)channels; i++)
	{
		QList<double> channelBuffer;
		for(unsigned int j = 0; j < 40; j++)
		{
			channelBuffer << ((double)buffer[i+(channels*j)] * 10.0) / 32768.0;
			if(i == 0)
			{
				countList << buffer[i+(channels*j)];
			}
		}
		double value = 0.0;
		for(unsigned int j = 0; j < 40; j++)
		{
			value += channelBuffer[j];
		}
		value /= 40.0;
		if(i == 0)
		{
			QList<double> smoothingList;
			smoothingList << value;
			QList<int> smoothingKeys = smoother.uniqueKeys();
			for(int j = 0; j < smoothingKeys.size(); j++)
			{
				if(countList.contains(smoothingKeys[j]))
				{
					QList<double> keyValues = smoother.values(smoothingKeys[j]);
					for(int k = 0; k < keyValues.size(); k++)
					{
						smoothingList << keyValues[k];
					}
				}
				else
				{
					smoother.remove(smoothingKeys[j]);
				}
			}
			qSort(countList);
			int lastCount = 0;
			for(int j = 0; j < countList.size(); j++)
			{
				if(j == 0 || countList[j] != lastCount)
				{
					smoother.insert(countList[j], value);
					lastCount = countList[j];
				}
			}
			value = 0.0;
			for(int j = 0; j < smoothingList.size(); j++)
			{
				value += smoothingList[j];
			}
			value /= smoothingList.size();
		}
		Measurement measure(value, time, unitMap[i]);
		channelMap[i]->input(measure);
	}
}

@ It was noted that |di_status_read()| blocks until it is able to fill the
|buffer| passed to it. To prevent this behavior from having adverse effects on
the rest of the program, |measure()| is called from a loop running in its own
thread of execution. When the thread is started, it begins its execution from
the |run()| method of |DataqSdkDeviceImplementation| which overrides the
|run()| method of |QThread|.

The while loop is controlled by |ready| which is set to |false| when there is
an error in collecting a measurement or when there is a desire to stop logging.
It could also be set to |false| for reconfiguration events.

All device initialization happens in this method.

Note that while the equivalent method when communicating with National
Instruments hardware sets a time critical thread priority in an attempt to cut
down on the variation in time between recorded measurements, that is a really
bad idea when using the DATAQ SDK. The result was that the main thread never
got enough time to report measurements and responsiveness throughout the entire
system became barely usable to the point that it was difficult to kill the
process. If anybody reading this can provide some insight into why setting the
thread priority is fine with interacting with either DAQmx or DAQmxBase but not
when interacting with the DATAQ SDK, I would like to read such an explanation.

@<DataqSdkDevice implementation@>=
void DataqSdkDeviceImplementation::run()
{
	if(!ready)
	{
		error = 9; // Device data not available
		return;
	}
	driver = new QLibrary(device);
	if(!driver->load())
	{
		error = 1; // Failed to load driver.
		qDebug() << "Failed to load driver: " << device;
		return;
	}
	di_open = (FPDIOPEN)driver->resolve("di_open");
	di_close = (FPDICLOSE)driver->resolve("di_close");
	di_sample_rate = (FPDISAMPLERATE)driver->resolve("di_sample_rate");
	di_maximum_rate = (FPDIMAXIMUMRATE)driver->resolve("di_maximum_rate");
	di_list_length = (FPDILISTLENGTH)driver->resolve("di_list_length");
	di_inlist = (FPDIINLIST)driver->resolve("di_inlist");
	di_buffer_alloc = (FPDIBUFFERALLOC)driver->resolve("di_buffer_alloc");
	di_start_scan = (FPDISTARTSCAN)driver->resolve("di_start_scan");
	di_status_read = (FPDISTATUSREAD)driver->resolve("di_status_read");
	di_buffer_status = (FPDIBUFFERSTATUS)driver->resolve("di_buffer_status");
	di_burst_rate = (FPDIBURSTRATE)driver->resolve("di_burst_rate");
	di_stop_scan = (FPDISTOPSCAN)driver->resolve("di_stop_scan");
	if((!di_open) || (!di_close) || (!di_sample_rate) || (!di_maximum_rate) ||
	   (!di_list_length) || (!di_inlist) || (!di_buffer_alloc) ||
	   (!di_start_scan) || (!di_status_read) || (!di_buffer_status) ||
	   (!di_burst_rate) || (!di_stop_scan))
	{
		error = 2; // Failed to link required symbol
		return;
	}
	error = di_open(deviceNumber);
	if(error)
	{
		di_close();
		error = di_open(deviceNumber);
		if(error)
		{
			error = 3; // Failed to open device
			di_close();
			return;
		}
	}
	isOpen = true;
	di_maximum_rate(240.0);
	sampleRate = di_sample_rate(sampleRate * channels * 40, &oversample,
	                            &burstDivisor);
	buffer = new qint16[(int)sampleRate];
	di_inlist_struct inlist[16] = {{0}};
	for(unsigned short i = 0; i < channels; i++)
	{
		inlist[i].chan = i;
		inlist[i].gain = 0;
		inlist[i].ave = 1;
		inlist[i].counter = (oversample - 1);
	}
	error = di_list_length(channels, 0);
	if(error)
	{
		error = 4; // List length error
		return;
	}
	error = di_inlist(inlist);
	if(error)
	{
		error = 5; // Inlist error
		return;
	}
	input_buffer = di_buffer_alloc(0, 4096);
	if(input_buffer == NULL)
	{
		error = 6; // Failed to allocate buffer
		return;
	}
	error = di_start_scan();
	if(error)
	{
		error = 7; // Failed to start scanning
		return;
	}
	while(ready)
	{
		measure();
	}
}

@ When the loop exits, |DataqSdkDeviceImplementation| emits a finished signal
to indicate that the thread is no longer running. This could be due to normal
conditions or there could be a problem that should be reported. That signal is
connected to a function that checks for error conditions and reports them if
needed.

@<DataqSdkDevice implementation@>=
void DataqSdkDevice::threadFinished()
{
	if(imp->error)
	{
		@<Display DATAQ SDK Error@>@;
	}
}

@ The DATAQ SDK does not have a single method for reporting errors. Instead,
any method that can return an error code has its return value checked and
|error| is set to a value that allows the source of the problem to be
determined. At present, error handling is very poor.

@<Display DATAQ SDK Error@>=
imp->ready = false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
warning.setInformativeText(tr("An error occurred"));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

@ Starting the thread is very simple. Device initialization happens in the new
thread which then begins taking measurements. The call to |imp->start()| starts
the new thread and passes control of that thread to |imp->run()|. The main
thread of execution returns without waiting for the new thread to do anything.
When the thread is finished, the |finished()| signal is emitted which we have
connected to |threadFinished()|.

@<DataqSdkDevice implementation@>=
void DataqSdkDevice::start()
{
	connect(imp, SIGNAL(finished()), this, SLOT(threadFinished()));
	imp->start();
}

@ When configuring Typica to use a device supported through the DATAQ SDK it is
useful to have a way to report the ports where supported hardware has been
detected. This is also used for automatic detection.

@<DataqSdkDevice implementation@>=
QStringList DataqSdkDevice::detectHardware()
{
	QSettings deviceLookup("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\usbser\\Enum",
	             QSettings::NativeFormat);
	QStringList keys = deviceLookup.childKeys();
	QStringList devices;
	for(int i = 0; i < keys.size(); i++)
	{
		QString value = deviceLookup.value(keys.at(i)).toString();
		if(value.startsWith("USB\\VID_0683&PID_1450\\"))
		{
			devices.append(value.split("\\").at(2));
		}
	}
	QStringList portList;
	foreach(QString device, devices)
	{
		QString deviceKey = QString("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_0683&PID_1450\\%1").arg(device);
		QSettings deviceEntry(deviceKey, QSettings::NativeFormat);
		portList.append(deviceEntry.value("FriendlyName").toString());
	}
	return portList;
}

QStringList DataqSdkDevice::detectPorts()
{
	QStringList friendlyNames = detectHardware();
	QStringList portList;
	foreach(QString name, friendlyNames)
	{
		name.remove(0, name.indexOf("COM"));
		name.chop(1);
		portList.append(name);
	}
	return portList;
}

@ Setting up the device begins by constructing a new |DataqSdkDevice| object.
The constructor takes as its argument a string which identifies the device. For
legacy reasons this currently accepts device names such as |"Dev1"| and looks
up currently connected devices to determine which serial port should be used.
Now that it is preferred to configure devices graphically this is not a good
way to do this. This should be changed before release.

@<DataqSdkDevice implementation@>=
DataqSdkDevice::DataqSdkDevice(QString device) : imp(new DataqSdkDeviceImplementation)
{
	bool usesAuto = false;
	int autoIndex = device.toInt(&usesAuto);
	QString finalizedPort;
	if(usesAuto)
	{
		QStringList portList = detectPorts();
		if(autoIndex > 0 && autoIndex <= portList.size())
		{
			finalizedPort = portList.at(autoIndex - 1);
		}
		else
		{
			imp->error = 8; // Failed to find device.
			qDebug() << "Failed to detect port.";
		}
	}
	else
	{
		finalizedPort = device;
	}
	int rstart = finalizedPort.indexOf("COM");
	finalizedPort.remove(0, rstart + 3);
	if(finalizedPort.toInt() < 10)
	{
		imp->device = QString("DI10%1NT.DLL").arg(finalizedPort);
	}
	else
	{
		imp->device = QString("DI1%1NT.DLL").arg(finalizedPort);
	}
	imp->deviceNumber = 0x12C02D00;
	imp->deviceNumber += finalizedPort.toInt();
	imp->ready = true;
}

@ Once the |DataqSdkDevice| is created, one or more channels can be added.

@<DataqSdkDevice implementation@>=
Channel* DataqSdkDevice::newChannel(Units::Unit scale)
{
	Channel *retval = NULL;
	if(imp->ready)
	{
		retval = new Channel();
		imp->channelMap[imp->channels] = retval;
		imp->unitMap[imp->channels] = scale;
		imp->channels++;
	}
	return retval;
}

@ Once the channels are created, it is necessary to set the clock rate of the
device. The DATAQ SDK will set the clock rate to be whichever value is closest
to the specified value that is supported by the hardware. Note that when
measuring multiple channels the device clock rate should be the desired sample
rate per channel multiplied by the number of channels.

The amount of time between measurements may vary slightly. Tests have shown
that while most measurements come within 1ms of the expected time, some
measurements do not come in within 100ms of the expected time.

@<DataqSdkDevice implementation@>=
void DataqSdkDevice::setClockRate(double Hz)
{
	imp->sampleRate = Hz;
}

@ The destructor instructs the measurement thread to stop, waits for it to
finish, and resets the device. If this is not done, an error would be issued
the next time a program attempted to use the device.

@<DataqSdkDevice implementation@>=
DataqSdkDevice::~DataqSdkDevice()
{
	if(imp->ready)
	{
		imp->ready = false;
	}
	imp->wait(ULONG_MAX);
	delete imp;
}

@ The constructor and destructor in |DataqSdkDeviceImplementation| currently
limit the number of channels to 4. As additional devices are supported this
restriction should be lifted.

Very little is needed from the constructor. The destructor is responsible for
closing the device and unloading the device driver.

@<DataqSdkDevice implementation@>=
DataqSdkDeviceImplementation::DataqSdkDeviceImplementation() : QThread(NULL),
	channelMap(4), error(0), channels(0), ready(false), unitMap(4)
{
	/* Nothing needs to be done here. */
}

DataqSdkDeviceImplementation::~DataqSdkDeviceImplementation()
{
	if(isOpen)
	{
		di_stop_scan();
		di_close();
	}
	if(driver->isLoaded())
	{
		driver->unload();
	}
}

@ This is exposed to the scripting engine in the usual way.

@<Function prototypes for scripting@>=
QScriptValue constructDataqSdkDevice(QScriptContext *context, QScriptEngine *engine);
QScriptValue DataqSdkDevice_newChannel(QScriptContext *context, QScriptEngine *engine);
void setDataqSdkDeviceProperties(QScriptValue value, QScriptEngine *engine);

@ These functions are made known to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructDataqSdkDevice);
value = engine->newQMetaObject(&DataqSdkDevice::staticMetaObject, constructor);
engine->globalObject().setProperty("DataqSdkDevice", value);

@ When creating a new device we make sure that it is owned by the script
engine. This is necessary to ensure that the destructor is called before \pn{}
exits. Just as the constructor requires an argument that specifies the device
name, the constructor available from a script also requires this argument.

@<Functions for scripting@>=
QScriptValue constructDataqSdkDevice(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 1)
	{
		object = engine->newQObject(new DataqSdkDevice(argument<QString>(0, context)),
		                            QScriptEngine::ScriptOwnership);
		setDataqSdkDeviceProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "
		                    "DataqSdkDevice. The constructor takes one string "
		                    "as an argument specifying a device name. "
		                    "Example: Dev1");
	}
	return object;
}

@ As |DataqSdkDevice| inherits |QObject| we add the |newChannel()| property
after adding any |QObject| properties.

@<Functions for scripting@>=
void setDataqSdkDeviceProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("newChannel", engine->newFunction(DataqSdkDevice_newChannel));
}

@ The |newChannel()| wrapper requires one argument to specify the measurement
unit that will eventually be produced from that channel.

@<Functions for scripting@>=
QScriptValue DataqSdkDevice_newChannel(QScriptContext *context, QScriptEngine *engine)
{
	DataqSdkDevice *self = getself<DataqSdkDevice *>(context);
	QScriptValue object;
	if(self)
	{
		object = engine->newQObject(self->newChannel((Units::Unit)argument<int>(0, context)));
		setChannelProperties(object, engine);
	}
	return object;
}

@ In order to configure supported devices within Typica, a set of configuration
controls is required. First there is the base device configuration widget.

@<Class declarations@>=
class DataqSdkDeviceConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE DataqSdkDeviceConfWidget(DeviceTreeModel *model,
		                                     const QModelIndex &index);
	private slots:
		void updateAutoSelect(bool automatic);
		void updateDeviceNumber(int deviceNumber);
		void updatePort(QString portId);
		void addChannel();
	private:
		QStackedWidget *deviceIdStack;
};

@ The constructor sets up the interface for updating device configuration
settings.

@<DataqSdkDeviceConfWidget implementation@>=
DataqSdkDeviceConfWidget::DataqSdkDeviceConfWidget(DeviceTreeModel *model,
                                                   const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index),
	deviceIdStack(new QStackedWidget)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QCheckBox *autoDetect = new QCheckBox("Automatically select device");
	layout->addWidget(autoDetect);
	QWidget *autoLayerWidget = new QWidget;
	QHBoxLayout *autoLayerLayout = new QHBoxLayout;
	QLabel *autoLabel = new QLabel(tr("Device number"));
	QSpinBox *autoNumber = new QSpinBox;
	autoNumber->setMinimum(1);
	autoNumber->setMaximum(99);
	autoLayerLayout->addWidget(autoLabel);
	autoLayerLayout->addWidget(autoNumber);
	autoLayerWidget->setLayout(autoLayerLayout);
	QWidget *fixedLayerWidget = new QWidget;
	QHBoxLayout *fixedLayerLayout = new QHBoxLayout;
	QLabel *fixedLabel = new QLabel(tr("Device port"));
	QComboBox *portSelection = new QComboBox;
	portSelection->setEditable(true);
	portSelection->addItems(DataqSdkDevice::detectHardware());
	fixedLayerLayout->addWidget(fixedLabel);
	fixedLayerLayout->addWidget(portSelection);
	fixedLayerWidget->setLayout(fixedLayerLayout);
	deviceIdStack->addWidget(autoLayerWidget);
	deviceIdStack->addWidget(fixedLayerWidget);
	layout->addWidget(deviceIdStack);
	QPushButton *addChannelButton = new QPushButton(tr("Add Channel"));
	layout->addWidget(addChannelButton);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "autoSelect")
		{
			autoDetect->setChecked(node.attribute("value") == "true" ? true : false);
		}
		else if(node.attribute("name") == "deviceNumber")
		{
			autoNumber->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "port")
		{
			int index = portSelection->findText(node.attribute("value"));
			if(index > -1)
			{
				portSelection->setCurrentIndex(index);
			}
			else
			{
				portSelection->setEditText(node.attribute("value"));
			}
		}
	}
	updateAutoSelect(autoDetect->isChecked());
	updateDeviceNumber(autoNumber->value());
	updatePort(portSelection->currentText());
	connect(autoDetect, SIGNAL(toggled(bool)), this, SLOT(updateAutoSelect(bool)));
	connect(autoNumber, SIGNAL(valueChanged(int)), this, SLOT(updateDeviceNumber(int)));
	connect(portSelection, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePort(QString)));
	connect(addChannelButton, SIGNAL(clicked()), this, SLOT(addChannel()));
	setLayout(layout);
}

@ In addition to setting a value in the device configuration, the choice to
automatically select devices also requires changing which controls in the
configuration widget are presently available. It is recommended that automatic
device selection is only used in cases where there is a single device supported
by the DATAQ SDK present and it will always be the first detected device
regardless of the current virtual COM port number. In cases where multiple
devices must be connected, it is recommended to always plug devices into the
same port and specify the port for each device explicitly.

@<DataqSdkDeviceConfWidget implementation@>=
void DataqSdkDeviceConfWidget::updateAutoSelect(bool automatic)
{
	if(automatic)
	{
		updateAttribute("autoSelect", "true");
		deviceIdStack->setCurrentIndex(0);
	}
	else
	{
		updateAttribute("autoSelect", "false");
		deviceIdStack->setCurrentIndex(1);
	}
}

@ Other update methods only need to set a new current value.

@<DataqSdkDeviceConfWidget implementation@>=
void DataqSdkDeviceConfWidget::updateDeviceNumber(int deviceNumber)
{
	updateAttribute("deviceNumber", QString("%1").arg(deviceNumber));
}

void DataqSdkDeviceConfWidget::updatePort(QString portId)
{
	updateAttribute("port", portId);
}

@ The Add Channel button creates a new configuration node.

@<DataqSdkDeviceConfWidget implementation@>=
void DataqSdkDeviceConfWidget::addChannel()
{
	insertChildNode(tr("Channel"), "dataqsdkchannel");
}

@ These configuration widgets are registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("dataqsdk", DataqSdkDeviceConfWidget::staticMetaObject);

@ A |NodeInserter| is also added to provide access to
|DataqSdkDeviceConfWidget|, but only on Windows.

@<Register top level device configuration nodes@>=
#ifdef Q_OS_WIN32
inserter = new NodeInserter(tr("DATAQ SDK Device"), tr("DATAQ Device"),
                            "dataqsdk", NULL);
topLevelNodeInserters.append(inserter);
#endif

