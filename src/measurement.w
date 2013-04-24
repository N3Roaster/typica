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
class Measurement : public QVariantMap
{
	public:
		Measurement(double temperature = 0, QTime time = QTime(),
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
		Measurement toRankine();
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
	return value("temperature").toDouble();
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
and a public destructor.

@<Register meta-types@>=
qRegisterMetaType<Measurement>("Measurement");