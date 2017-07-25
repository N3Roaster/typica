@** Difference and Mean.

\noindent Some roasters find value in comparing the difference between
measurements on different data series. For example, the difference between
intake and exhaust air or the difference between air and seed temperatures.
These can be expressed as an additional relative temperature series. Similarly,
a roaster might have multiple thermocouples where neither is individually as
reliable as taking the mean between the two. The difference and mean series
allow either of these to be calculated automatically.

Since these are very similar structurally, a common base class is provided
for performing some calculation based on two inputs. Difference and mean
series then only need to override the |calculate()| method.

@<Class declarations@>=
class MergeSeries : public QObject
{
	Q_OBJECT
	public:
		MergeSeries();
	public slots:
		void in1(Measurement measure);
		void in2(Measurement measure);
	signals:
		void newData(Measurement measure);
	protected:
		virtual void calculate(Measurement m1, Measurement m2) = 0;
	private:
		Measurement last1;
		Measurement last2;
		bool received1;
		bool received2;
};

class DifferenceSeries : public MergeSeries
{
	Q_OBJECT
	public:
		DifferenceSeries();
	protected:
		void calculate(Measurement m1, Measurement m2);
};

class MeanSeries : public MergeSeries
{
	Q_OBJECT
	public:
		MeanSeries();
	protected:
		void calculate(Measurement m1, Measurement m2);
};

@ Classes derived from |MergeSeries| will wait until there is a measurement
from both series and then call |calculate()| with the most recent measurement
from each. This allows the use of measurements from sources with different
sample rates, though there is no guarantee that measurements with the closest
timestamps will be paired. This is done to minimize latency on the series.

@<MergeSeries implementation@>=
void MergeSeries::in1(Measurement measure)
{
	last1 = measure;
	received1 = true;
	if(received1 && received2)
	{
		calculate(last1, last2);
		received1 = false;
		received2 = false;
	}
}

void MergeSeries::in2(Measurement measure)
{
	last2 = measure;
	received2 = true;
	if(received1 && received2)
	{
		calculate(last1, last2);
		received1 = false;
		received2 = false;
	}
}

@ The constructor just needs to set the initial |bool|s to |false|.

@<MergeSeries implementation@>=
MergeSeries::MergeSeries() : QObject(NULL), received1(false), received2(false)
{
	/* Nothing needs to be done here. */
}

@ The calculations will emit a new |Measurement| with the calculated
temperature value. If the measurement times are different, the highest value
is used. A difference needs to be treated as a relative measurement whereas a
mean does not.

@<MergeSeries implementation@>=
void DifferenceSeries::calculate(Measurement m1, Measurement m2)
{
	Measurement outval(m1.temperature() - m2.temperature(),
	                   (m1.time() > m2.time() ? m1.time() : m2.time()));
	outval.insert("relative", true);
	emit newData(outval);
}

void MeanSeries::calculate(Measurement m1, Measurement m2)
{
	Measurement outval((m1.temperature() + m2.temperature()) / 2,
                       (m1.time() > m2.time() ? m1.time() : m2.time()));
	emit newData(outval);
}

@ Nothing special needs to happen in the constructors.

@<MergeSeries implementation@>=
DifferenceSeries::DifferenceSeries() : MergeSeries()
{
	/* Nothing needs to be done here. */
}

MeanSeries::MeanSeries() : MergeSeries()
{
	/* Nothing needs to be done here. */
}

@ The base class does not need to be exposed to the host environment, but the
derived classes do.

@<Function prototypes for scripting@>=
QScriptValue constructDifferenceSeries(QScriptContext *context,
                                       QScriptEngine *engine);
QScriptValue constructMeanSeries(QScriptContext *context,
                                 QScriptEngine *engine);

@ The constructors are registered in the usual way.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructDifferenceSeries);
value = engine->newQMetaObject(&DifferenceSeries::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("DifferenceSeries", value);
constructor = engine->newFunction(constructMeanSeries);
value = engine->newQMetaObject(&MeanSeries::staticMetaObject, constructor);
engine->globalObject().setProperty("MeanSeries", value);

@ The constructors are trivial.

@<Functions for scripting@>=
QScriptValue constructDifferenceSeries(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new DifferenceSeries);
	setQObjectProperties(object, engine);
	return object;
}

QScriptValue constructMeanSeries(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new MeanSeries);
	setQObjectProperties(object, engine);
	return object;
}

@ Both of these require configuration, however since these are structurally
identical, rather than create multiple configuration widgets I have opted to
instead have a selector to choose between the two options.

@<Class declarations@>=
class MergeSeriesConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE MergeSeriesConfWidget(DeviceTreeModel *model,
                                          const QModelIndex &index);
	private slots:
		void updateColumn1(const QString &column);
		void updateColumn2(const QString &column);
		void updateOutput(const QString &column);
		void updateType(int type);
};

@ The constructor sets up the user interface.

@<MergeSeriesConfWidget implementation@>=
MergeSeriesConfWidget::MergeSeriesConfWidget(DeviceTreeModel *model,
                                             const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QComboBox *type = new QComboBox;
	type->addItem(tr("Difference"), QVariant("Difference"));
	type->addItem(tr("Mean"), QVariant("Mean"));
	layout->addRow(tr("Series type:"), type);
	QLineEdit *column1 = new QLineEdit;
	layout->addRow(tr("First input column name:"), column1);
	QLineEdit *column2 = new QLineEdit;
	layout->addRow(tr("Second input column name:"), column2);
	QLineEdit *output = new QLineEdit;
	layout->addRow(tr("Output column name:"), output);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "type")
		{
			type->setCurrentIndex(type->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "column1")
		{
			column1->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "column2")
		{
			column2->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "output")
		{
			output->setText(node.attribute("value"));
		}
	}
	updateColumn1(column1->text());
	updateColumn2(column2->text());
	updateOutput(output->text());
	updateType(type->currentIndex());
	connect(column1, SIGNAL(textEdited(QString)), this, SLOT(updateColumn1(QString)));
	connect(column2, SIGNAL(textEdited(QString)), this, SLOT(updateColumn2(QString)));
	connect(output, SIGNAL(textEdited(QString)), this, SLOT(updateOutput(QString)));
	connect(type, SIGNAL(currentIndexChanged(int)), this, SLOT(updateType(int)));
	setLayout(layout);
}

@ The update methods are trivial.

@<MergeSeriesConfWidget implementation@>=
void MergeSeriesConfWidget::updateColumn1(const QString &column)
{
	updateAttribute("column1", column);
}

void MergeSeriesConfWidget::updateColumn2(const QString &column)
{
	updateAttribute("column2", column);
}

void MergeSeriesConfWidget::updateOutput(const QString &column)
{
	updateAttribute("output", column);
}

void MergeSeriesConfWidget::updateType(int index)
{
	switch(index)
	{
		case 0:
			updateAttribute("type", "Difference");
			break;
		case 1:
			updateAttribute("type", "Mean");
			break;
		default:
			break;
	}
}

@ This is registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("mergeseries",
                                      MergeSeriesConfWidget::staticMetaObject);

@ This is accessed through the advanced features menu.

@<Add node inserters to advanced features menu@>=
NodeInserter *mergeSeriesInserter = new NodeInserter(tr("Merge Series"),
                                                     tr("Merge"),
                                                     "mergeseries");
connect(mergeSeriesInserter, SIGNAL(triggered(QString, QString)),
        this, SLOT(insertChildNode(QString, QString)));
advancedMenu->addAction(mergeSeriesInserter);

@ The class implementations are currently expanded into |"typica.cpp"|.

@<Class implementations@>=
@<MergeSeriesConfWidget implementation@>
@<MergeSeries implementation@>

