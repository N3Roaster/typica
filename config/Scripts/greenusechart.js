// Data access functions
var label = function(d) {return d[0];};
var greenValue = function(d) {return d[1];};
var transactionCount = function(d) {return d[2];};
var roastValue = function(d) {return d[3];};

// Chart parameters
var valueLabelWidth = 0; // Temporary, will be updated when labels are generated
var barHeight = 30;
var barHeight2 = barHeight / 2;
var barLabelWidth = 0;
var barLabelPadding = 5;
var gridLabelHeight = 18;
var gridChartOffset = 3;
var maxBarWidth = 500;

// Scales
var x1s = d3.scale.linear().domain([0, d3.max(data, function(d) { return greenValue(d); })*1.15]).range([0, maxBarWidth]);
var x2s = d3.scale.linear().domain([0, d3.max(data, function(d) { return transactionCount(d); })*1.15]).range([0, maxBarWidth]);
var ys = d3.scale.ordinal().domain(d3.range(0, data.length)).rangeBands([0, data.length * barHeight]);
var ytext = function(d, i) {return ys(i) + ys.rangeBand() / 2;};
var ybar = function(d, i) {return ys(i);};
var ybar2 = function(d, i) {return ys(i) + (barHeight2 / 2)};
var ybar3 = function(d, i) {return ys(i);};
var ybar4 = function(d, i) {return ys(i) + barHeight;};

// Chart
var svg = d3.select("#chart").append("svg")
	.attr("width", 1000)
	.attr("height", gridLabelHeight + gridLabelHeight + gridChartOffset + data.length * barHeight);

// Bar labels
var yxe = svg.append("g")
	.attr("class", "y axis left");
yxe.selectAll("text").data(data).enter().append("text")
	.attr("y", ytext)
	.attr("stroke", "none")
	.attr("fill", "black")
	.attr("dy", ".35em")
	.attr("text-anchor", "end")
	.text(label);
// Determine maximum label width
yxe.selectAll("text").each(function() {
	if(barLabelWidth < this.getComputedTextLength()) {
		barLabelWidth = this.getComputedTextLength();
	}
});
barLabelWidth += 10;
yxe.attr("transform", "translate(" + (barLabelWidth - barLabelPadding) + "," + (gridLabelHeight + gridChartOffset) + ")");

// Weight axis
var x1xe = svg.append("g")
	.attr("class", "x axis top")
	.attr("transform", "translate(" + barLabelWidth + "," + gridLabelHeight + ")");
	
x1xe.selectAll("text").data(x1s.ticks(10)).enter().append("text")
	.attr("x", x1s)
	.attr("dy", -3)
	.attr("text-anchor", "middle")
	.text(String);
// Top ticks extend approximately half way down the chart
x1xe.selectAll("line").data(x1s.ticks(10)).enter().append("line")
	.attr("x1", x1s)
	.attr("x2", x1s)
	.attr("y1", 0)
	.attr("y2", ys.rangeExtent()[1] /2)
	.style("stroke", "#ccc");

// Transaction count axis
var x2xe = svg.append("g")
	.attr("class", "x axis bottom")
	.attr("transform", "translate(" + barLabelWidth + "," + (ys.rangeExtent()[1] + gridChartOffset + gridLabelHeight + gridLabelHeight) + ")");

x2xe.selectAll("text").data(x2s.ticks(10)).enter().append("text")
	.attr("x", x2s)
	.attr("dy", -3)
	.attr("text-anchor", "middle")
	.text(String);
// Bottom ticks extend approximately half way up the chart	
x2xe.selectAll("line").data(x2s.ticks(10)).enter().append("line")
	.attr("x1", x2s)
	.attr("x2", x2s)
	.attr("y1", -gridLabelHeight - (ys.rangeExtent()[1] /2))
	.attr("y2", -gridLabelHeight)
	.style("stroke", "#ccc");

// Green coffee bars
var gbars = svg.append("g")
	.attr("transform", "translate(" + barLabelWidth + "," + (gridLabelHeight + gridChartOffset) + ")");
gbars.selectAll("rect").data(data).enter().append("rect")
	.attr("y", ybar)
	.attr("height", barHeight)
	.attr("width", function(d) {return x1s(greenValue(d));})
	.attr("stroke", "white")
	.attr("fill", "royalblue");

// Roasted coffee bars
var rbars = svg.append("g")
	.attr("transform", "translate(" + barLabelWidth + "," + (gridLabelHeight + gridChartOffset) + ")");
rbars.selectAll("rect").data(data).enter().append("rect")
	.attr("y", ybar2)
	.attr("height", barHeight2)
	.attr("width", function(d) {return x1s(roastValue(d));})
	.attr("stroke", "white")
	.attr("fill", "orangered");

// Transaction ticks
var tticks = svg.append("g")
	.attr("transform", "translate(" + barLabelWidth + "," + (gridLabelHeight + gridChartOffset) + ")");
tticks.selectAll("line").data(data).enter().append("line")
	.attr("x1", function(d) {return x2s(transactionCount(d));})
	.attr("x2", function(d) {return x2s(transactionCount(d));})
	.attr("y1", ybar3)
	.attr("y2", ybar4)
	.attr("stroke-width", "3")
	.style("stroke", "black");