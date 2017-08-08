/*291:*/
#line 42 "./units.w"

#include "units.h"
#include <QtDebug> 

/*:291*//*292:*/
#line 53 "./units.w"

bool Units::isTemperatureUnit(Unit unit)
{
return(unit==Fahrenheit||
unit==Celsius||
unit==Kelvin||
unit==Rankine);
}

/*:292*//*293:*/
#line 71 "./units.w"

double Units::convertTemperature(double value,Unit fromUnit,Unit toUnit)
{
if(!(isTemperatureUnit(fromUnit)&&isTemperatureUnit(toUnit)))
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
return(value-32.0)*5.0/9.0;
break;
case Kelvin:
return(value+459.67)*5.0/9.0;
break;
case Rankine:
return value+459.67;
break;
default:
qDebug()<<"Warning: Non-sensical unit conversion.";
break;
}
break;
case Celsius:
switch(toUnit)
{
case Fahrenheit:
return value*9.0/5.0+32.0;
break;
case Celsius:
return value;
break;
case Kelvin:
return value+273.15;
break;
case Rankine:
return(value+273.15)*9.0/5.0;
break;
default:
qDebug()<<"Warning: Non-sensical unit conversion.";
break;
}
break;
case Kelvin:
switch(toUnit)
{
case Fahrenheit:
return value*5.0/9.0-459.67;
break;
case Celsius:
return value-273.15;
break;
case Kelvin:
return value;
break;
case Rankine:
return value*9.0/5.0;
break;
default:
qDebug()<<"Warning: Non-sensical unit conversion.";
break;
}
break;
case Rankine:
switch(toUnit)
{
case Fahrenheit:
return value-457.67;
break;
case Celsius:
return(value-491.67)*5.0/9.0;
break;
case Kelvin:
return value*5.0/9.0;
break;
case Rankine:
return value;
break;
default:
qDebug()<<"Warning: Non-sensical unit conversion.";
break;
}
break;
default:
return 0;
break;
}
return 0;
}

/*:293*//*294:*/
#line 169 "./units.w"

double Units::convertRelativeTemperature(double value,Unit fromUnit,Unit toUnit)
{
if(!(isTemperatureUnit(fromUnit)&&isTemperatureUnit(toUnit)))
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
return value*(5.0/9.0);
break;
case Kelvin:
return value*(5.0/9.0);
break;
case Rankine:
return value;
break;
default:
return 0;
break;
}
break;
case Celsius:
switch(toUnit)
{
case Fahrenheit:
return value*(9.0/5.0);
break;
case Celsius:
return value;
break;
case Kelvin:
return value;
break;
case Rankine:
return value*(9.0/5.0);
break;
default:
return 0;
break;
}
break;
case Kelvin:
switch(toUnit)
{
case Fahrenheit:
return value*(5.0/9.0);
break;
case Celsius:
return value;
break;
case Kelvin:
return value;
break;
case Rankine:
return value*(9.0/5.0);
break;
default:
return 0;
break;
}
break;
case Rankine:
switch(toUnit)
{
case Fahrenheit:
return value;
break;
case Celsius:
return value*(5.0/9.0);
break;
case Kelvin:
return value*(5.0/9.0);
break;
case Rankine:
return value;
break;
default:
return 0;
break;
}
break;
default:
return 0;
break;
}
return 0;
}

/*:294*//*295:*/
#line 267 "./units.w"

double Units::convertWeight(double value,Unit fromUnit,Unit toUnit)
{
if(isWeightUnit(fromUnit)&&isWeightUnit(toUnit))
{
switch(fromUnit)
{
case Pound:
switch(toUnit)
{
case Pound:
return value;
break;
case Kilogram:
return value/2.2;
break;
case Ounce:
return value*16.0;
break;
case Gram:
return value/0.0022;
break;
default:
return 0;
break;
}
break;
case Kilogram:
switch(toUnit)
{
case Pound:
return value*2.2;
break;
case Kilogram:
return value;
break;
case Ounce:
return value*35.2;
break;
case Gram:
return value*1000.0;
break;
default:
return 0;
break;
}
break;
case Ounce:
switch(toUnit)
{
case Pound:
return value/16.0;
break;
case Kilogram:
return value/35.2;
break;
case Ounce:
return value;
break;
case Gram:
return value/0.0352;
break;
default:
return 0;
break;
}
break;
case Gram:
switch(toUnit)
{
case Pound:
return value*0.0022;
break;
case Kilogram:
return value/1000.0;
break;
case Ounce:
return value*0.0352;
break;
case Gram:
return value;
break;
default:
return 0;
break;
}
break;
default:
return 0;
break;
}
}
return 0;
}

bool Units::isWeightUnit(Unit unit)
{
return(unit==Pound||
unit==Kilogram||
unit==Ounce||
unit==Gram);
}

/*:295*/
