/*1058:*/
#line 103 "./scales.w"

#ifndef TypicaScaleInclude
#define TypicaScaleInclude

#include "3rdparty/qextserialport/src/qextserialport.h"
#include "units.h"

class SerialScale:public QextSerialPort
{
Q_OBJECT
public:
SerialScale(const QString&port);
public slots:
void tare();
void weigh();
void setWeighCommand(const QString&command);
void setCommandTerminator(const QString&terminator);
signals:
void newMeasurement(double weight,Units::Unit unit);
private slots:
void dataAvailable();
private:
QByteArray responseBuffer;
QByteArray weighCommand;
QByteArray commandTerminator;
};

#endif

/*:1058*/
