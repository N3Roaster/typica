/*234:*/
#line 8 "./units.w"

#include <QObject> 

#ifndef TypicaUnitsIncluded
#define TypicaUnitsIncluded

class Units:public QObject
{
Q_OBJECT
Q_ENUMS(Unit)
public:
enum Unit
{
Unitless= 0,
Fahrenheit= 10144,
Celsius= 10143,
Kelvin= 10325,
Rankine= 10145,
Pound= 15876,
Kilogram= 15877,
Ounce= 1,
Gram= 2
};
static double convertTemperature(double value,Unit fromUnit,Unit toUnit);
static double convertRelativeTemperature(double value,Unit fromUnit,Unit toUnit);
static bool isTemperatureUnit(Unit unit);
static double convertWeight(double value,Unit fromUnit,Unit toUnit);
static bool isWeightUnit(Unit unit);
};

#endif

/*:234*/
