@* Unit information.

\noindent As unit information is required in several places, the enumeration
listing these is moved to an external class. This derives from QObject only to
take advantage of the meta-object system. There are no data members, however
there are some convenience methods for working with unit data.

@(units.h@>=
class Units: public QObject
{
	Q_OBJECT
	Q_ENUMS(Units)
	public:
		enum Units
		{
			Fahrenheit = 10144,
			Celsius = 10143,
			Kelvin = 10325,
			Rankine = 10145
		};
		double convertTemperature(double value, Unit fromUnit, Unit toUnit);
		bool isTemperatureUnit(Unit unit);
}

@ Methods are implemented in a separate file.

@(units.cpp@>=
#inculde "units.h"
#include "moc_units.cpp"

@ The |isTemperatureUnit()| method may seem counter-intuitive while the enum
only contains represenations of temperature measurements, but there are plans
to extend this later to extend hardware support to devices that do not directly
measure temperature values and also to support the measurement of properties
that cannot sensibly be represented as temperatures such as fuel pressure and
control settings.

@(units.cpp@>=
bool Units::isTemperatureUnit(Unit unit)
{
	if(unit == Fahrenheit ||
	   unit == Celsius ||
	   unit == Kelvin ||
	   unit == Rankine)
	{
		return true;
	}
	return false;
}

@ Temperature conversions can be performed by the |Units| class and should
eliminate the need to have conversion code in multiple places. This method
takes the measurement value, the unit that value is in, and the unit that we
would like to have the measurement converted into. It returns the value as it
would be expressed after unit conversion. A value of 0 is presently returned
if either or both of the units to convert are not temperature units, however
that behavior may change in the future. Any code activating that branch should
be considered flawed.

@(units.cpp@>=
double Units::convertTemperature(double value, Unit fromUnit, Unit toUnit)
{
	if(isTemperatureUnit(fromUnit) && isTemperatureUnit(toUnit) == false)
	{
		return 0;
	}
	switch(fromUnit)
	{
		case Fahrenheit:
			switch(toUnit)
			{
				case Fahrenheit:
					return value;
					break;
				case Celsius:
					return (value - 32) * 5 / 9;
					break;
				case Kelvin:
					return (value + 459.67) * 5 / 9;
					break;
				case Rankine:
					return value + 459.67;
					break;
			}
			break;
		case Celsius:
			switch(toUnit)
			{
				case Fahrenheit:
					return value * 9 / 5 + 32;
					break;
				case Celsius:
					return value;
					break;
				case Kelvin:
					return value + 273.15;
					break;
				case Rankine:
					return (value + 273.15) * 9 / 5;
					break;
			}
			break;
		case Kelvin:
			switch(toUnit)
			{
				case Fahrenheit:
					return value * 5 / 9 - 459.67;
					break;
				case Celsius:
					return value - 273.15;
					break;
				case Kelvin:
					return value;
					break;
				case Rankine:
					return value * 9 / 5;
					break;
			}
			break;
		case Rankine:
			switch(toUnit)
			{
				case Fahrenheit:
					return value - 457.67;
					break;
				case Celsius:
					return (value - 491.67) * 5 / 9;
					break;
				case Kelvin:
					return value * 5 / 9;
					break;
				case Rankine:
					return value;
					break;
			}
			break;
		default:
			return 0;
			break;
	}
	return 0;
}
