/*243:*/
#line 24 "./clock.w"

#include <QElapsedTimer> 
#include <QMutex> 
#include <QObject> 

#ifndef ClockHeader
#define ClockHeader

class Clock:public QObject
{
Q_OBJECT
public:
Clock();
~Clock();
qint64 timestamp();
public slots:
void setEpoch();
signals:
void newTime(qint64 time);
private:
QElapsedTimer reference;
QMutex guard;
};

#endif

/*:243*/
