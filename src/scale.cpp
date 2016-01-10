/*1008:*/
#line 131 "./scales.w"

#include "scale.h"
#include <QStringList> 

SerialScale::SerialScale(const QString&port):
QextSerialPort(port,QextSerialPort::EventDriven)
{
connect(this,SIGNAL(readyRead()),this,SLOT(dataAvailable()));
}

/*:1008*//*1009:*/
#line 149 "./scales.w"

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
/*1010:*/
#line 189 "./scales.w"

QStringList responseParts= QString(responseBuffer.simplified()).split(' ');
if(responseParts.size()> 2)
{
responseParts.removeFirst();
responseParts.replace(0,QString("-%1").arg(responseParts[0]));
}
double weight= responseParts[0].toDouble();
Units::Unit unit= Units::Unitless;
if(responseParts[1]=="lb")
{
unit= Units::Pound;
}
else if(responseParts[1]=="kg")
{
unit= Units::Kilogram;
}
else if(responseParts[1]=="g")
{
unit= Units::Gram;
}
else if(responseParts[1]=="oz")
{
unit= Units::Ounce;
}
emit newMeasurement(weight,unit);

/*:1010*/
#line 161 "./scales.w"

responseBuffer.clear();
}
}
}

/*:1009*//*1011:*/
#line 220 "./scales.w"

void SerialScale::tare()
{
write("!KT\x0D");
}

void SerialScale::weigh()
{
write("!KP\x0D");
}

/*:1011*/
