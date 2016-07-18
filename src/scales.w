@** Collecting Measurements from Scales.

\noindent When a computer connected scale is available, it can be useful to
eliminate manual transcription from the data entry for batches. In general it
is difficult to determine where a measurement should go automatically, but
there are a number of situations where the ability to drag a measurement from a
label and drop it to whatever input widget is appropriate would be a useful
operation to support.

To support this, we need to subclass |QLabel| to allow it to initiate a drag
and drop operation.

@(draglabel.h@>=
#ifndef TypicaDragLabelInclude
#define TypicaDragLabelInclude

#include <QLabel>

class DragLabel : public QLabel
{
	Q_OBJECT
	public:
		explicit DragLabel(const QString &labelText, QWidget *parent = NULL);
	protected:
		void mousePressEvent(QMouseEvent *event);
};

#endif

@ The font size of the label is increased by default to make it easier to
manipulate on a touch screen. Otherwise, there is little to do in this class.

@(draglabel.cpp@>=
#include "draglabel.h"

#include <QDrag>
#include <QMouseEvent>

DragLabel::DragLabel(const QString &labelText, QWidget *parent) :
	QLabel(labelText, parent)
{
	QFont labelFont = font();
	labelFont.setPointSize(14);
	setFont(labelFont);
}

void DragLabel::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		QDrag *drag = new QDrag(this);
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(text());
		drag->setMimeData(mimeData);
		drag->exec();
	}
}

@ We require the ability to create these labels from the host environment.
First we include the appropriate header.

@<Header files to include@>=
#include "draglabel.h"

@ Next, a pair of function prototypes.

@<Function prototypes for scripting@>=
QScriptValue constructDragLabel(QScriptContext *context, QScriptEngine *engine);
void setDragLabelProperties(QScriptValue value, QScriptEngine *engine);

@ These are made known to the host environment as usual.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructDragLabel);
value = engine->newQMetaObject(&DragLabel::staticMetaObject, constructor);
engine->globalObject().setProperty("DragLabel", value);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructDragLabel(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	QString labelText = "";
	if(context->argumentCount() == 1)
	{
		labelText = argument<QString>(0, context);
	}
	object = engine->newQObject(new DragLabel(labelText));
	setDragLabelProperties(object, engine);
	return object;
}

void setDragLabelProperties(QScriptValue value, QScriptEngine *engine)
{
	setQLabelProperties(value, engine);
}

@ An object is also required to communicate with a scale. This is responsible
for setting up a connection over a serial port, sending commands out to the
scale, buffering and interpreting the response, and signaling new measurements.

@(scale.h@>=
#ifndef TypicaScaleInclude
#define TypicaScaleInclude

#include "3rdparty/qextserialport/src/qextserialport.h"
#include "units.h"

class SerialScale : public QextSerialPort
{
	Q_OBJECT
	public:
		SerialScale(const QString &port);
	public slots:
		void tare();
		void weigh();
		void setWeighCommand(const QString &command);
		void setCommandTerminator(const QString &terminator);
	signals:
		void newMeasurement(double weight, Units::Unit unit);
	private slots:
		void dataAvailable();
	private:
		QByteArray responseBuffer;
		QByteArray weighCommand;
		QByteArray commandTerminator;
};

#endif

@ The constructor tells the port that this should be event driven and connects
a signal to buffer data..

@(scale.cpp@>=
#include "scale.h"
#include <QStringList>

SerialScale::SerialScale(const QString &port) :
	QextSerialPort(port, QextSerialPort::EventDriven)
{
	connect(this, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
}

@ The |dataAvailable| method handles buffering incoming data and processing
responses when they have come in. Serial port communications are likely to be
very slow in comparison to everything else so it is likely that only one
character will come in at a time.

Note that this currently only understands single line output and a limited
selection of units.

@(scale.cpp@>=
void SerialScale::dataAvailable()
{
	responseBuffer.append(readAll());
	if(responseBuffer.contains("\x0D"))
	{
		if(responseBuffer.contains("!"))
		{
			responseBuffer.clear();
		}
		else
		{
			@<Process weight measurement@>@;
			responseBuffer.clear();
		}
	}
}

@ Each line of data consists of an optional sign character possibly followed
by a space followed by characters representing a number followed by a
space followed by characters indicating a unit. This may be preceeded and
followed by a variable amount of white space. To process a new measurement, we
must remove the excess white space, split the number from the unit, prepend the
sign to the number if it is present, convert the string representing the number
to a numeric type, and determine which unit the measurement is in.

\medskip

\settabs 8 \columns
\+&&&{\tt |"lb"|}&|Units::Pound|\cr
\+&&&{\tt |"kg"|}&|Units::Kilogram|\cr
\+&&&{\tt |"g"|}&|Units::Gram|\cr
\+&&&{\tt |"oz"|}&|Units::Ounce|\cr

\smallskip

\centerline{Table \secno: Unit Strings and Representative Unit Enumeration}

\medskip

@<Process weight measurement@>=
QStringList responseParts = QString(responseBuffer.simplified()).split(' ');
if(responseParts.size() > 2)
{
	responseParts.removeFirst();
	responseParts.replace(0, QString("-%1").arg(responseParts[0]));
}
double weight = responseParts[0].toDouble();
Units::Unit unit = Units::Unitless;
if(responseParts[1].compare("lb", Qt::CaseInsensitive) == 0)
{
	unit = Units::Pound;
}
else if(responseParts[1].compare("kg", Qt::CaseInsensitive) == 0)
{
	unit = Units::Kilogram;
}
else if(responseParts[1].compare("g", Qt::CaseInsensitive) == 0)
{
	unit = Units::Gram;
}
else if(responseParts[1].compare("oz", Qt::CaseInsensitive) == 0)
{
	unit = Units::Ounce;
}
emit newMeasurement(weight, unit);

@ Two methods are used to send commands to the scale. I am unsure of how well
standardized remote key operation of scales are. The class may need to be
extended to support more devices.

@(scale.cpp@>=
void SerialScale::tare()
{
	write("!KT\x0D");
}

void SerialScale::weigh()
{
	//write("!KP\x0D");
	write(weighCommand + commandTerminator);
}

void SerialScale::setWeighCommand(const QString &command)
{
	weighCommand = command.toAscii();
}

void SerialScale::setCommandTerminator(const QString &terminator)
{
	if(terminator == "CRLF")
	{
		commandTerminator = "\x0D\x0A";
	}
	else if(terminator == "CR")
	{
		commandTerminator = "\x0D";
	}
	else if(terminator == "LF")
	{
		commandTerminator = "\x0A";
	}
}

@ This must be available to the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructSerialScale(QScriptContext *context, QScriptEngine *engine);
void setSerialScaleProperties(QScriptValue value, QScriptEngine *engine);

@ These functions are made known to the scripting engine in the usual way.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructSerialScale);
value = engine->newQMetaObject(&SerialScale::staticMetaObject, constructor);
engine->globalObject().setProperty("SerialScale", value);

@ If we are to set up the serial ports from the host environment, a few
enumerated types must be made known to the meta-object system.

@<Class declarations@>=
Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(FlowType)

@ For each of these, a pair of functions converts values to script values and
back. This is a very annoying aspect of the version of QextSerialPort currently
used by \pn{}.

@<Function prototypes for scripting@>=
QScriptValue BaudRateType_toScriptValue(QScriptEngine *engine, const BaudRateType &value);
void BaudRateType_fromScriptValue(const QScriptValue &sv, BaudRateType &value);
QScriptValue DataBitsType_toScriptValue(QScriptEngine *engine, const DataBitsType &value);
void DataBitsType_fromScriptValue(const QScriptValue &sv, DataBitsType &value);
QScriptValue ParityType_toScriptValue(QScriptEngine *engine, const ParityType &value);
void ParityType_fromScriptValue(const QScriptValue &sv, ParityType &value);
QScriptValue StopBitsType_toScriptValue(QScriptEngine *engine, const StopBitsType &value);
void StopBitsType_fromScriptValue(const QScriptValue &sv, StopBitsType &value);
QScriptValue FlowType_toScriptValue(QScriptEngine *engine, const FlowType &value);
void FlowType_fromScriptValue(const QScriptValue &sv, FlowType &value);

@ These are implemented thusly.

@<Functions for scripting@>=
QScriptValue BaudRateType_toScriptValue(QScriptEngine *engine, const BaudRateType &value)
{
	return engine->newVariant(QVariant((int)(value)));
}

void BaudRateType_fromScriptValue(const QScriptValue &sv, BaudRateType &value)
{
	value = (BaudRateType)(sv.toVariant().toInt());
}

QScriptValue DataBitsType_toScriptValue(QScriptEngine *engine, const DataBitsType &value)
{
	return engine->newVariant(QVariant((int)(value)));
}

void DataBitsType_fromScriptValue(const QScriptValue &sv, DataBitsType &value)
{
	value = (DataBitsType)(sv.toVariant().toInt());
}

QScriptValue ParityType_toScriptValue(QScriptEngine *engine, const ParityType &value)
{
	return engine->newVariant(QVariant((int)(value)));
}

void ParityType_fromScriptValue(const QScriptValue &sv, ParityType &value)
{
	value = (ParityType)(sv.toVariant().toInt());
}

QScriptValue StopBitsType_toScriptValue(QScriptEngine *engine, const StopBitsType &value)
{
	return engine->newVariant(QVariant((int)(value)));
}

void StopBitsType_fromScriptValue(const QScriptValue &sv, StopBitsType &value)
{
	value = (StopBitsType)(sv.toVariant().toInt());
}

QScriptValue FlowType_toScriptValue(QScriptEngine *engine, const FlowType &value)
{
	return engine->newVariant(QVariant((int)(value)));
}

void FlowType_fromScriptValue(const QScriptValue &sv, FlowType &value)
{
	value = (FlowType)(sv.toVariant().toInt());
}

@ These conversion functions are then registered.

@<Set up the scripting engine@>=
qScriptRegisterMetaType(engine, BaudRateType_toScriptValue, BaudRateType_fromScriptValue);
qScriptRegisterMetaType(engine, DataBitsType_toScriptValue, DataBitsType_fromScriptValue);
qScriptRegisterMetaType(engine, ParityType_toScriptValue, ParityType_fromScriptValue);
qScriptRegisterMetaType(engine, StopBitsType_toScriptValue, StopBitsType_fromScriptValue);
qScriptRegisterMetaType(engine, FlowType_toScriptValue, FlowType_fromScriptValue);

@ In order to make this class available to the host environment, we must also
include the appropriate header file.

@<Header files to include@>=
#include "scale.h"

@ Most of the properties of interest should be added automatically, however
there are non-slot methods in |QIODevice| that we require.

@<Functions for scripting@>=
void setSerialScaleProperties(QScriptValue value, QScriptEngine *engine)
{
	setQIODeviceProperties(value, engine);
}

@ The script constructor should seem familiar.

@<Functions for scripting@>=
QScriptValue constructSerialScale(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 1)
	{
		object = engine->newQObject(new SerialScale(argument<QString>(0, context)));
		setSerialScaleProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "
		                    "SerialScale. The constructor takes one string "
		                    "as an argument specifying a port name.");
	}
	return object;
}

@ In order to allow configuration of scales from within \pn{}, a configuration
widget must be provided.

@<Class declarations@>=
class SerialScaleConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE SerialScaleConfWidget(DeviceTreeModel *model,
		                                  const QModelIndex &index);
	private slots:
		void updatePort(const QString &newPort);
		void updateBaudRate(const QString &rate);
		void updateParity(int index);
		void updateFlowControl(int index);
		void updateStopBits(int index);
		void updateWeighCommand(const QString &command);
		void updateCommandTerminator(const QString &terminator);
	private:
		PortSelector *port;
		BaudSelector *baud;
		ParitySelector *parity;
		FlowSelector *flow;
		StopSelector *stop;
		QLineEdit *weighcommand;
		QComboBox *commandterminator;
};

@ This is very similar to other configuration widgets.

@<SerialScaleConfWidget implementation@>=
SerialScaleConfWidget::SerialScaleConfWidget(DeviceTreeModel *model,
                                             const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index),
  port(new PortSelector), baud(new BaudSelector), parity(new ParitySelector),
  flow(new FlowSelector), stop(new StopSelector),
  weighcommand(new QLineEdit("!KP")), commandterminator(new QComboBox)
{
	QFormLayout *layout = new QFormLayout;
	layout->addRow(tr("Port:"), port);
	connect(port, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updatePort(QString)));
	connect(port, SIGNAL(editTextChanged(QString)),
	        this, SLOT(updatePort(QString)));
	layout->addRow(tr("Baud:"), baud);
	connect(baud, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateBaudRate(QString)));
	layout->addRow(tr("Parity:"), parity);
	connect(parity, SIGNAL(currentIndexChanged(int)),
	        this, SLOT(updateParity(int)));
	layout->addRow(tr("Flow Control:"), flow);
	connect(flow, SIGNAL(currentIndexChanged(int)),
	        this, SLOT(updateFlowControl(int)));
	layout->addRow(tr("Stop Bits:"), stop);
	connect(stop, SIGNAL(currentIndexChanged(int)),
	        this, SLOT(updateStopBits(int)));
	layout->addRow(tr("Weigh Command:"), weighcommand);
	connect(weighcommand, SIGNAL(textChanged(QString)),
	        this, SLOT(updateWeighCommand(QString)));
	commandterminator->addItem("CRLF");
	commandterminator->addItem("CR");
	commandterminator->addItem("LF");
	layout->addRow(tr("Command Terminator:"), commandterminator);
	connect(commandterminator, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateCommandTerminator(QString)));
	
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
			baud->setCurrentIndex(baud->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "parity")
		{
			parity->setCurrentIndex(parity->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "flowcontrol")
		{
			flow->setCurrentIndex(flow->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "stopbits")
		{
			stop->setCurrentIndex(stop->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "weighcommand")
		{
			weighcommand->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "commandterminator")
		{
			commandterminator->setCurrentIndex(
				commandterminator->findText(node.attribute("value")));
		}
	}
	updatePort(port->currentText());
	updateBaudRate(baud->currentText());
	updateParity(parity->currentIndex());
	updateFlowControl(flow->currentIndex());
	updateStopBits(stop->currentIndex());
	updateWeighCommand(weighcommand->text());
	updateCommandTerminator(commandterminator->currentText());
	setLayout(layout);
}

@ Update methods are the same as were used in |ModbusRtuPortConfWidget|.

@<SerialScaleConfWidget implementation@>=
void SerialScaleConfWidget::updatePort(const QString &newPort)
{
	updateAttribute("port", newPort);
}

void SerialScaleConfWidget::updateBaudRate(const QString &rate)
{
	updateAttribute("baudrate", rate);
}

void SerialScaleConfWidget::updateParity(int index)
{
	updateAttribute("parity", parity->itemData(index).toString());
}

void SerialScaleConfWidget::updateFlowControl(int index)
{
	updateAttribute("flowcontrol", flow->itemData(index).toString());
}

void SerialScaleConfWidget::updateStopBits(int index)
{
	updateAttribute("stopbits", stop->itemData(index).toString());
}

void SerialScaleConfWidget::updateWeighCommand(const QString &command)
{
	updateAttribute("weighcommand", command);
}

void SerialScaleConfWidget::updateCommandTerminator(const QString &terminator)
{
	updateAttribute("commandterminator", terminator);
}

@ The configuration widget is registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("scale", SerialScaleConfWidget::staticMetaObject);

@ A |NodeInserter| is also added.

@<Register top level device configuration nodes@>=
inserter = new NodeInserter(tr("Serial Scale"), tr("Scale"), "scale", NULL);
topLevelNodeInserters.append(inserter);

