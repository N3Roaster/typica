pluginContext.table.setHeaderData(0, "Time");
pluginContext.table.setHeaderData(1, "Temperature");
pluginContext.table.setHeaderData(2, "Set");
pluginContext.table.setHeaderData(3, "Fan");
pluginContext.table.setHeaderData(4, "Heater");
pluginContext.table.setHeaderData(5, "Note");
pluginContext.table.clearOutputColumns();
pluginContext.table.addOutputTemperatureColumn(1);
pluginContext.table.addOutputTemperatureColumn(2);
pluginContext.table.addOutputControlColumn(3);
pluginContext.table.addOutputControlColumn(4);
pluginContext.table.addOutputAnnotationColumn(5);
var lines = pluginContext.data.split('\n');
for(var i = 0; i < lines.length; i++) {
	var fields = lines[i].split(',');
	if(fields[5] == "roasting") {
		var time = new QTime;
		time = time.addSecs(Number(fields[0]));
		pluginContext.newMeasurement(new Measurement(Units.convertTemperature(fields[4], Units.Celsius, Units.Fahrenheit), time), 1);
		pluginContext.newMeasurement(new Measurement(Units.convertTemperature(fields[2], Units.Celsius, Units.Fahrenheit), time), 2);
		pluginContext.newMeasurement(new Measurement(fields[1], time, Units.Unitless), 3);
		pluginContext.newMeasurement(new Measurement(fields[6], time, Units.Unitless), 4);
	}
}
for(var i = 1; i < 5; i++) {
	pluginContext.table.newAnnotation("End", i, 5);
}