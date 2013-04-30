@** A Rate of Change Indicator.

\noindent A common metric used for understanding roast profiles is the rate of
temperature change over a given amount of time. When roasters discuss roast
profiles it is not uncommon to hear references to the change in temperature per
30 seconds or per minute, often with the sloppy shorthand $\Delta$ or with the
term Rate of Rise (RoR). This is most commonly calculated from the secant line
defined by two measurement points at the desired separation, however this may
not be the most useful way to calculate this value.

The rate of change can be considered as its own data series which happens to be
derived from a primary measurement series. The interface for producing this
series can sensibly match other classes which store, forward, or manipulate
measurement data.

@<Class declarations@>=
class RateOfChange : public QObject
{
	Q_OBJECT
	public:
		RateOfChange(int cachetime = 1, int scaletime = 1);
	public slots:
		void newMeasurement(Measurement measure);
		void setCacheTime(int seconds);
		void setScaleTime(int seconds);
	signals:
		void measurement(Measurement measure);
	private:
		int ct;
		int st;
		QList<Measurement> cache;
		QMap<double,double> smoothCache;
};

@ The interesting part of this class is in the |newMeasurement()| method. This
is a slot method that will be called for every new measurement in the primary
series. We require at least two measurements before calculating a rate of
temperature change.

@<RateOfChange implementation@>=
void RateOfChange::newMeasurement(Measurement measure)
{
	cache.append(measure);
	@<Remove stale measurements from rate cache@>@;
	if(cache.size() >= 2)
	{
		@<Calculate rate of change@>@;
	}
}

@ To calculate the rate of temperature change we require at least two cached
measurements. Using only the most recent two measurements will result in a
highly volatile rate of change while using two data points that are more
separated will smooth out random fluctuations but provide a less immediate
response to a change in the rate of change. For this reason we provide two
parameters that can be adjusted independently: the amount of time we allow a
measurement to stay in the cache determines how far apart the measurements
used to calculate the rate of change are while a separate scale time is used
to determine how the calculated value is presented. We never allow fewer than
two cached values, but we can force the most volatile calculation by setting
the cache time to 0 seconds.

@<Remove stale measurements from rate cache@>=
if(cache.size() > 2)
{
	bool done = false;
	while(!done)
	{
		if(cache.front().time().secsTo(cache.back().time()) > ct)
		{
			cache.removeFirst();
		}
		else
		{
			done = true;
		}
		if(cache.size() < 3)
		{
			done = true;
		}
	}
}

@ When calculating the rate of change we are doing something that will
fundamentally increase the noise expressed through the derived series.
Delivering a derived series that both lacks excessive volatility and remains
acceptably accurate requires careful tuning.

The measurement will carry the fact that it is a relative measurement.

@<Calculate rate of change@>=
QList<double> rates;
for(int i = 1; i < cache.size(); i++)
{
	double mdiff = cache.at(i).temperature() - cache.at(i-1).temperature();
	double tdiff = (double)(cache.at(i-1).time().msecsTo(cache.at(i).time())) / 1000.0;
	rates.append(mdiff/tdiff);
}
double acc = 0.0;
for(int i = 0; i < rates.size(); i++)
{
	acc += rates.at(i);
}
double pavg = acc /= rates.size();
double v2 = pavg * st;
Measurement value(v2, cache.back().time(), cache.back().scale());
value.insert("relative", true);
emit measurement(value);

@ The rest of the class implementation is trivial.

@<RateOfChange implementation@>=
RateOfChange::RateOfChange(int cachetime, int scaletime) : ct(cachetime), st(1)
{
	setScaleTime(scaletime);
}

void RateOfChange::setCacheTime(int seconds)
{
	ct = seconds;
}

void RateOfChange::setScaleTime(int seconds)
{
	st = (seconds > 0 ? seconds : 1);
}

@ This is exposed to the host environment in the usual way.

@<Function prototypes for scripting@>=
QScriptValue constructRateOfChange(QScriptContext *context, QScriptEngine *engine);
void setRateOfChangeProperties(QScriptValue value, QScriptEngine *engine);

@ The constructor is registered with the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructRateOfChange);
value = engine->newQMetaObject(&RateOfChange::staticMetaObject, constructor);
engine->globalObject().setProperty("RateOfChange", value);

@ The constructor takes two arguments if they are provided.

@<Functions for scripting@>=
QScriptValue constructRateOfChange(QScriptContext *context, QScriptEngine *engine)
{
	int cachetime = 1;
	int scaletime = 1;
	if(context->argumentCount() > 0)
	{
		cachetime = argument<int>(0, context);
		if(context->argumentCount() > 1)
		{
			scaletime = argument<int>(1, context);
		}
	}
	QScriptValue object = engine->newQObject(new RateOfChange(cachetime, scaletime));
	setRateOfChangeProperties(object, engine);
	return object;
}

void setRateOfChangeProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@ To make use of this feature conveniently, we must integrate this with the
in-program configuration system by providing a configuration widget.

@<Class declarations@>=
class RateOfChangeConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE RateOfChangeConfWidget(DeviceTreeModel *model, const QModelIndex &index);
	private slots:
		void updateColumn(const QString &column);
		void updateCacheTime(const QString &seconds);
		void updateScaleTime(const QString &seconds);
};

@ The constructor sets up the user interface.

@<RateOfChangeConfWidget implementation@>=
RateOfChangeConfWidget::RateOfChangeConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *column = new QLineEdit;
	layout->addRow(tr("Primary series column name:"), column);
	QSpinBox *cacheTime = new QSpinBox;
	cacheTime->setMinimum(0);
	cacheTime->setMaximum(300);
	layout->addRow(tr("Cache time:"), cacheTime);
	QSpinBox *scaleTime = new QSpinBox;
	scaleTime->setMinimum(1);
	scaleTime->setMaximum(300);
	layout->addRow(tr("Scale time:"), scaleTime);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "column")
		{
			column->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "cache")
		{
			cacheTime->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "scale")
		{
			scaleTime->setValue(node.attribute("value").toInt());
		}
	}
	updateColumn(column->text());
	updateCacheTime(cacheTime->text());
	updateScaleTime(scaleTime->text());
	connect(column, SIGNAL(textEdited(QString)), this, SLOT(updateColumn(QString)));
	connect(cacheTime, SIGNAL(valueChanged(QString)), this, SLOT(updateCacheTime(QString)));
	connect(scaleTime, SIGNAL(valueChanged(QString)), this, SLOT(updateScaleTime(QString)));
	setLayout(layout);
}

@ A set of update methods modify the device configuration to reflect changes in
the configuration widget.

@<RateOfChangeConfWidget implementation@>=
void RateOfChangeConfWidget::updateColumn(const QString &column)
{
	updateAttribute("column", column);
}

void RateOfChangeConfWidget::updateCacheTime(const QString &seconds)
{
	updateAttribute("cache", seconds);
}

void RateOfChangeConfWidget::updateScaleTime(const QString &seconds)
{
	updateAttribute("scale", seconds);
}

@ This is registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("rate", RateOfChangeConfWidget::staticMetaObject);

@ This is accessed through the advanced features menu.

@<Add node inserters to advanced features menu@>=
NodeInserter *rateOfChangeInserter = new NodeInserter(tr("Rate of Change"), tr("Rate of Change"), "rate");
connect(rateOfChangeInserter, SIGNAL(triggered(QString, QString)), this, SLOT(insertChildNode(QString, QString)));
advancedMenu->addAction(rateOfChangeInserter);

@ Our class implementation is currently expanded into |"typica.cpp"|.

@<Class implementations@>=
@<RateOfChangeConfWidget implementation@>