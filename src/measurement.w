@** Measurement representation.

\noindent Most of the information in a roast log will be measurements of
various sorts. These could be temperature measurements, control settings,
data derived from other data series, and so on. There are three key elements to
a measurement: the value of the measurement, the unit that the measurement was
taken in, and the time the measurement was collected.

Starting in Typica 1.6 the |Measurement| class implementation was changed so
that every |Measurement| is a |QVariantMap|. Additional methods are provided on
top of this map so that this change is transparent to code that has already
been written against the old class, but over time these methods will be
depreciated and code can work directly with the |QVariantMap| interface to
allow |Measurement| objects to carry much more information.

As |QVariantMap| is implicitly shared and |Measurement| adds no new data
members we no longer require copy and assignment operators.

@<Class declarations@>=
class Measurement : public QVariantMap@/
{@t\1@>@/
	public:@/
		Measurement(double temperature = 0, QTime time = QTime(),@|
                    Units::Unit sc = Units::Fahrenheit);
		Measurement(double temperature);
		double temperature() const;
		QTime time() const;
		void setTemperature(double temperature);
		void setTime(QTime time);
		void setUnit(Units::Unit scale);
		Units::Unit scale() const;
		Measurement toFahrenheit();
		Measurement toCelsius();
		Measurement toKelvin();
		Measurement toRankine();@t\2@>@/
};

@ Time, measured value, and unit are stored at well known keys.

@<Measurement implementation@>=
Measurement::Measurement(double temperature, QTime time, Units::Unit sc)
{
	insert("measurement", temperature);
	insert("time", time);
	insert("unit", sc);
}

Measurement::Measurement(double temperature)
{
	insert("measurement", temperature);
	insert("time", QTime::currentTime());
	insert("unit", Units::Fahrenheit);
}

void Measurement::setTemperature(double temperature)
{
	insert("measurement", temperature);
}

void Measurement::setTime(QTime time)
{
	insert("time", time);
}

void Measurement::setUnit(Units::Unit scale)
{
	insert("unit", scale);
}

double Measurement::temperature() const
{
	return value("measurement").toDouble();
}

QTime Measurement::time() const
{
	return value("time").toTime();
}

Units::Unit Measurement::scale() const
{
	return (Units::Unit)(value("unit").toInt());
}

@ Unit conversion methods will likely be the first things to be depreciated as
the functionality is fully available from the |Units| class.

@<Measurement implementation@>=
Measurement Measurement::toFahrenheit()
{
	return Measurement(Units::convertTemperature(this->temperature(),
	                                             this->scale(), Units::Fahrenheit),
	                   this->time(), Units::Fahrenheit);
}

Measurement Measurement::toCelsius()
{
	return Measurement(Units::convertTemperature(this->temperature(),
	                                             this->scale(), Units::Celsius),
	                   this->time(), Units::Celsius);
}

Measurement Measurement::toKelvin()
{
	return Measurement(Units::convertTemperature(this->temperature(),
	                                             this->scale(), Units::Kelvin),
	                   this->time(), Units::Kelvin);
}

Measurement Measurement::toRankine()
{
	return Measurement(Units::convertTemperature(this->temperature(),
	                                             this->scale(), Units::Rankine),
	                   this->time(), Units::Rankine);
}

@ In the future we will be able to drop the |Measurement| class entirely and
just pass around |QVariantMap| but until then we need to be able to pass these
objects through the signals and slots mechanism. This requires that we have a
public default constructor (already defined above), a public copy constructor,
and a public destructor. These latter two are default generated.

@<Register meta-types@>=
qRegisterMetaType<Measurement>("Measurement");

@ A little more is required to use |Measurement| objects in scripts.

@<Class declarations@>=
Q_DECLARE_METATYPE(Measurement)

@ The only thing unusual here is the conversion to and from script values.

@<Function prototypes for scripting@>=
QScriptValue constructMeasurement(QScriptContext *context, QScriptEngine *engine);
void setMeasurementProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue Measurement_toScriptValue(QScriptEngine *engine, const Measurement &measurement);
void Measurement_fromScriptValue(const QScriptValue &value, Measurement &measurement);

@ This follows much the same pattern as other types not derived from |QObject|.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructMeasurement);
engine->globalObject().setProperty("Measurement", constructor);
qScriptRegisterMetaType(engine, Measurement_toScriptValue, Measurement_fromScriptValue);

@ The constructor takes two or three arguments. If the third arguement is not
supplied, we will assume that the measurements are in degrees Fahrenheit.

@<Functions for scripting@>=
QScriptValue constructMeasurement(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 2 || context->argumentCount() == 3)
	{
		double measurement = argument<double>(0, context);
		QTime timestamp = argument<QTime>(1, context);
		Units::Unit unit = Units::Fahrenheit;
		if(context->argumentCount() == 3)
		{
			unit = argument<Units::Unit>(2, context);
		}
		object = engine->toScriptValue<Measurement>(Measurement(measurement, timestamp, unit));
		setMeasurementProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "Measurement::Measurement(). This method takes two "@|
		                    "or three arguments.");
	}
	return object;
}

@ No additional properties are currently needed, but if they were, they would go here.

@<Functions for scripting@>=
void setMeasurementProperties(QScriptValue, QScriptEngine *)
{
	/* Nothing needs to be done here. */
}

@ The script value conversions are reasonably straightforward.

@<Functions for scripting@>=
QScriptValue Measurement_toScriptValue(QScriptEngine *engine, const Measurement &measurement)
{
	QVariant var;
	var.setValue(measurement);
	return engine->newVariant(var);
}

void Measurement_fromScriptValue(const QScriptValue &value, Measurement &measurement)
{
	measurement = value.toVariant().value<Measurement>();
}
