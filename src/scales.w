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
	signals:
		void newMeasurement(double weight, Units::Unit unit);
	private slots:
		void dataAvailable();
	private:
		QByteArray responseBuffer;
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
		if(responseBuffer.startsWith("!"))
		{
			responseBuffer.clear();
			weigh();
		}
		else
		{
			@<Process weight measurement@>@;
			responseBuffer.clear();
		}
	}
}

@ Each line of data consists of characters representing a number followed by a
space followed by characters indicating a unit. This may be preceeded and
followed by a variable amount of white space. To process a new measurement, we
must remove the excess white space, split the number from the unit, convert the
string representing the number to a numeric type, and determine which unit the
measurement is in.

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
double weight = responseParts[0].toDouble();
Units::Unit unit = Units::Unitless;
if(responseParts[1] == "lb")
{
	unit = Units::Pound;
}
else if(responseParts[1] == "kg")
{
	unit = Units::Kilogram;
}
else if(responseParts[1] == "g")
{
	unit = Units::Gram;
}
else if(responseParts[1] == "oz")
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
	write("!KP\x0D");
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

@ While the |SerialScale| class will always 