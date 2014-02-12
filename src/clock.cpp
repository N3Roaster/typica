/*244:*/
#line 52 "./clock.w"

#include "clock.h"

/*245:*/
#line 61 "./clock.w"

Clock::Clock():QObject(NULL)
{
reference.start();
}

Clock::~Clock()
{

}

/*:245*//*246:*/
#line 79 "./clock.w"

qint64 Clock::timestamp()
{
guard.lock();
qint64 retval= reference.elapsed();
guard.unlock();
emit newTime(retval);
return retval;
}

void Clock::setEpoch()
{
guard.lock();
reference.restart();
guard.unlock();
emit newTime(0);
}

/*:246*/
#line 55 "./clock.w"


/*:244*/
