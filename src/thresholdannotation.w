@** Threshold Annotations.

\noindent Value annotations are fine for cases where we want to capture the
fact that a control series has changed to some specific value, but there are
times when it is more useful to know when a data series has passed through some
value in a particular direction even if the exact value of interest is never
directly recorded. For example, it would be possible to automatically mark a
point near turnaround by watching for a rate of temperature change ascending
through 0. This could also be set up to match range timers and mark events of
interest that begin at consistent temperatures.

As usual, this is a feature that must be configured on a per roaster basis.

@<Class declarations@>=
class ThresholdAnnotationConfWidget : public BasicDeviceConfigurationWidget
{
    Q_OBJECT
    public:
        Q_INVOKABLE ThresholdAnnotationConfWidget(DeviceTreeModel *model,
                                                  const QModelIndex &index);
    private slots:
        void updateSourceColumn(const QString &source);
        void updateThreshold(double value);
        void updateDirection(int index);
        void updateAnnotation(const QString &note);
};

@ The configuration widget needs to provide fields for determining which data
series should be used to generate the annotation, the value that the
|ThresholdDetector| should use as its trigger, the direction this should fire
on, and the text of the annotation.

@<ThresholdAnnotationConfWidget implementation@>=
ThresholdAnnotationConfWidget::ThresholdAnnotationConfWidget(DeviceTreeModel *model,
                                                             const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
    QFormLayout *layout = new QFormLayout;
    QLineEdit *source = new QLineEdit;
    layout->addRow(tr("Source column name:"), source);
    QDoubleSpinBox *value = new QDoubleSpinBox;
    value->setMinimum(-9999.99);
    value->setMaximum(9999.99);
    value->setDecimals(2);
    layout->addRow(tr("Threshold value:"), value);
    QComboBox *direction = new QComboBox;
    direction->addItem(tr("Ascending"));
    direction->addItem(tr("Descending"));
    layout->addRow(tr("Direction:"), direction);
    QLineEdit *annotation = new QLineEdit;
    layout->addRow(tr("Annotation:"), annotation);
    @<Get device configuration data for current node@>@;
    for(int i = 0; i < configData.size(); i++)
    {
        node = configData.at(i).toElement();
        if(node.attribute("name") == "source")
        {
            source->setText(node.attribute("value"));
        }
        else if(node.attribute("name") == "value")
        {
            value->setValue(node.attribute("value").toDouble());
        }
        else if(node.attribute("name") == "direction")
        {
            direction->setCurrentIndex(node.attribute("value").toInt());
        }
        else if(node.attribute("name") == "annotation")
        {
            annotation->setText(node.attribute("value"));
        }
    }
    updateSourceColumn(source->text());
    updateThreshold(value->value());
    updateDirection(direction->currentIndex());
    updateAnnotation(annotation->text());
    connect(source, SIGNAL(textEdited(QString)), this, SLOT(updateSourceColumn(QString)));
    connect(value, SIGNAL(valueChanged(double)), this, SLOT(updateThreshold(double)));
    connect(direction, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDirection(int)));
    connect(annotation, SIGNAL(textEdited(QString)), this, SLOT(updateAnnotation(QString)));
    setLayout(layout);
}

@ Configuration of the model is done as usual.

@<ThresholdAnnotationConfWidget implementation@>=
void ThresholdAnnotationConfWidget::updateSourceColumn(const QString &source)
{
    updateAttribute("source", source);
}

void ThresholdAnnotationConfWidget::updateThreshold(double value)
{
    updateAttribute("value", QString("%1").arg(value));
}

void ThresholdAnnotationConfWidget::updateDirection(int direction)
{
    updateAttribute("direction", QString("%1").arg(direction));
}

void ThresholdAnnotationConfWidget::updateAnnotation(const QString &annotation)
{
    updateAttribute("annotation", annotation);
}

@ The configurationwidget is registered with the configuration system as usual.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("thresholdannotation",
                                      ThresholdAnnotationConfWidget::staticMetaObject);

@ A NodeInserter makes the configuration available.

@<Add annotation control node inserters@>=
NodeInserter *thresholdAnnotationInserter = new NodeInserter(tr("Threshold Annotation"),
                                                             tr("Threshold Annotation"),
                                                             "thresholdannotation");
annotationMenu->addAction(thresholdAnnotationInserter);
connect(thresholdAnnotationInserter, SIGNAL(triggered(QString, QString)),
        this, SLOT(insertChildNode(QString, QString)));

@ While we could use |ThresholdDetector| in the configuration directly, it is
easier to provide another class with the same interface as |AnnotationButton|
to leverage existing code for handling these.

@<Class declarations@>=
class Annotator : public QObject
{@t\1@>@/
    Q_OBJECT@;
    QString note;
    int tc;
    int ac;
    QTimer t;
    public:
        Annotator(const QString &text);@/
    @t\4@>public slots@t\kern-3pt@>:@/
        void setAnnotation(const QString &annotation);
        void setTemperatureColumn(int tempcolumn);
        void setAnnotationColumn(int annotationcolumn);
        void annotate();
    private slots:
        void catchTimer();
    signals:@/
        void annotation(QString annotation, int tempcolumn, int notecolumn);@t\2@>@/
}@t\kern-3pt@>;

@ To use this class with a |ThresholdDetector|, simply connect the
|timeForValue()| signal to the |annotate()| slot and use the existing
|AnnotationButton| code to keep the columns up to date.

@<Annotator implementation@>=
Annotator::Annotator(const QString &text) : QObject(NULL), note(text)
{
    t.setInterval(0);
    t.setSingleShot(true);
    connect(&t, SIGNAL(timeout()), this, SLOT(catchTimer()));
}

void Annotator::setAnnotation(const QString &annotation)
{
    note = annotation;
}

void Annotator::setTemperatureColumn(int tempcolumn)
{
    tc = tempcolumn;
}

void Annotator::setAnnotationColumn(int annotationcolumn)
{
    ac = annotationcolumn;
}

@ When connecting a |ThresholdDetector| to an |Annotator| directly, the
annotation can be recorded before the measurement reaches the log. The result
of this is that the annotation appears with the measurement immediately before
the one it should appear next to. To solve this, the annotation is delayed
until the next iteration of the event loop.

@<Annotator implementation@>=
void Annotator::catchTimer()
{
    emit annotation(note, tc, ac);
}

void Annotator::annotate()
{
    t.start();
}

@ It must be possible to create these from a script.

@<Function prototypes for scripting@>=
QScriptValue constructAnnotator(QScriptContext *context,
                                QScriptEngine *engine);
void setAnnotatorProperties(QScriptValue value, QScriptEngine *engine);

@ The engine is informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructAnnotator);
value = engine->newQMetaObject(&Annotator::staticMetaObject, constructor);
engine->globalObject().setProperty("Annotator", value);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructAnnotator(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue object = engine->newQObject(new Annotator(argument<QString>(0, context)));
    setAnnotatorProperties(object, engine);
    return object;
}

void setAnnotatorProperties(QScriptValue value, QScriptEngine *engine)
{
    setQObjectProperties(value, engine);
}

