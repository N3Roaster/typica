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
	unit = Units::gram;
}
else if(responseParts[1] == "oz")
{
	unit = Units::ounce;
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

void SerialScale::weight()
{
	write("!KP\x0D");
}
