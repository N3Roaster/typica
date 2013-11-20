@** Measurement timing.

\noindent Previously, all timing operations were performed with the system
time. While inefficient, that did work most of the time with the hardware and
operating systems that were common at the time. Starting with Qt 4.7, however,
a better approach became available and as hardware becomes cheaper and with the
defualt system time settings in Windows 8, it makes sense to switch timing
operations to something based on |QElapsedTimer|. On platforms that \pn{} is
currently supported on this should always provide a monotonic timer for
measuring the number of milliseconds that have elapsed since an arbitrary
starting point. This is more efficient and more reliable than a system time
based approach and does not require special casing certain edge cases that were
required previously.

With this code, a reference clock is passed to every object that requires batch
time data and the starting time can be conveniently reset, eliminating the need
for an object to convert time data to elapsed time relative to a starting
point.

@s qint64 int
@s QElapsedTimer int
@s QMutex int

@(clock.h@>=
#include <QElapsedTimer>
#include <QMutex>
#include <QObject>

#ifndef ClockHeader
#define ClockHeader

class Clock : public QObject
{
	@[Q_OBJECT@]@;
	public:@/
		Clock();
		~Clock();
		qint64 timestamp();@/
	@[public slots@]:@/
		void setEpoch();@/
	@[signals@]:@/
		void newTime(qint64 time);@/
	private:@/
		QElapsedTimer reference;
		QMutex guard;
};

#endif

@ The implementation is in its own file.

@(clock.cpp@>=
#include "clock.h"

@<Clock implementation@>@;

@ The timer is started on creation so that it may immediately be passed to
instances of hardware interface classes and produce measurements for use in
instantaneous displays. The clock should be reset at the start of each batch.

@<Clock implementation@>=
Clock::Clock() : QObject(NULL)
{
	reference.start();
}

Clock::~Clock()
{
	/* Nothing needs to be done here. */
}

@ Because timing data may be requested from multiple threads simultanously and
|QElapsedTimer| is not thread safe, access to the reference clock must be
guarded.

Whenever a new timestamp is generated, a signal is emitted. This can be used to
drive a batch timer display.

@<Clock implementation@>=
qint64 Clock::timestamp()
{
	guard.lock();
	qint64 retval = reference.elapsed();
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

@ The host environment must be able to instantiate this class. This is done in
the usual way.

@<Function prototypes for scripting@>=
QScriptValue constructClock(QScriptContext *context, QScriptEngine *engine);

@ The host environment is informed of this function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructClock);
engine->globalObject().setProperty("Clock", constructor);

@ Implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructClock(QScriptContext *context, QScriptEngine *engine)
{
	return engine->newQObject(new Clock());
}

@ The header must be included.

@<Header files to include@>=
#include "clock.h"

