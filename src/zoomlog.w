@* A table of roasting data.

\noindent A typical roast log is a table listing temperature measurements taken
at regular intervals. The introduction of a computer brings several advantages.
A human does not need to record the measurements. Every measurement taken can be
logged, but the measurements do not all need to be displayed. The |ZoomLog|
class presents a table with time, temperature, and annotation for one or more
sets of roasting data and allows the user to select from a few different levels
of detail.

Experience has shown that one measurement every 30 or 15 seconds is most useful,
but it is also possible to view one measurement every 1, 5, 10, or 60 seconds
and there is an option to view every measurement collected. This last is what is
saved to a file.

The zooming log is implemented by keeping a measurement model with every level
of detail of interest and making sure that new measurements get to the models
they belong in. Switching the level of detail of the view then becomes a matter
of changing which model the view is using. This is very inefficient in terms of
space, but it is very fast and simple to code.

Starting in version 1.4, column sizes are persisted automatically using the
same method as described in the section on |SqlQueryView|.

Starting in version 1.8, |rowCount()| is |Q_INVOKABLE|. This allows the manual
log entry interface to easily determine if any roasting data exists to save.

@<Class declarations@>=
class MeasurementModel;@/
class ZoomLog : public QTableView@/
{@/
    @[Q_OBJECT@]@;
    @<ZoomLog private member data@>@;
    void switchLOD(MeasurementModel *m);@/
    @[private slots@]:@/
        void centerOn(int row);
        void persistColumnResize(int column, int oldsize, int newsize);
        void restoreColumnWidths();
    public:@/
        ZoomLog();
        QVariant data(int row, int column) const;
        @[Q_INVOKABLE@,@, int rowCount();
        bool saveXML(QIODevice *device);
        bool saveCSV(QIODevice *device);
        QString lastTime(int series);
        @[Q_INVOKABLE@,@, Units::Unit displayUnits()@];@t\2\2@>@/
    @[public slots@]:@/
        void setVisible(bool visibility);
        void setHeaderData(int section, QString text);
        void LOD_ms();
        void LOD_1s();
        void LOD_5s();
        void LOD_10s();
        void LOD_15s();
        void LOD_30s();
        void LOD_1m();
        void newMeasurement(Measurement measure, int tempcolumn);
        void newAnnotation(QString annotation, int tempcolumn,
                            int annotationcolumn);
        void clear();
        void addOutputTemperatureColumn(int column);
        void addOutputControlColumn(int column);
        void addOutputAnnotationColumn(int column);
        void clearOutputColumns();
        void setDisplayUnits(Units::Unit scale);
        void addToCurrentColumnSet(int column);
        void clearCurrentColumnSet();@/
    protected:@/
        virtual void showEvent(QShowEvent *event);
};

@ This class uses a different model for each level of detail and provides logic
for placing measurements and annotations in the appropriate models. A list of
each model is provided for conveniently performing operations that apply to
every model.

@<ZoomLog private member data@>=
MeasurementModel *model_ms;
MeasurementModel *model_1s;
MeasurementModel *model_5s;
MeasurementModel *model_10s;
MeasurementModel *model_15s;
MeasurementModel *model_30s;
MeasurementModel *model_1m;
std::vector<MeasurementModel *> modelSet;
std::map<int, Measurement> lastMeasurement;
MeasurementModel *currentModel;
std::vector<int> saveTempCols;
std::vector<int> saveControlCols;
std::vector<int> saveNoteCols;
std::vector<int> currentColumnSet;

@ Most of the functionality this class provides is in getting measurements to
the right models. Every measurement goes to the full detail model. We also keep
track of the most recent measurement to detect the first measurement in a new
second and pass all of these on to the 1 second level of detail model. Some of
these are also passed to other models. Additionally, the models that store
coarser data strip the millisecond portion of the time.

A decision was made to present data promptly. With a high sample rate, some
might prefer an average of a few measurements near the reported time, but such
a feature does not exist in \pn{} currently.

The first measurement is always added to each model.

@<ZoomLog Implementation@>=
void ZoomLog::newMeasurement(Measurement measure, int tempcolumn)
{
    if(measure.time() != QTime(0, 0, 0, 0))
    {
        @<Synthesize measurements for slow hardware@>@;
    }
    model_ms->newMeasurement(measure, tempcolumn);
    if(lastMeasurement.count(tempcolumn) > 0)
    {
        if(measure.time().second() !=
            lastMeasurement[tempcolumn].time().second())
        {
            Measurement adjusted = measure;
            QTime adjtime(0, measure.time().minute(), measure.time().second(), 0);
            adjusted.setTime(adjtime);
            model_1s->newMeasurement(adjusted, tempcolumn);
            if(adjusted.time().second() % 5 == 0)
            {
                model_5s->newMeasurement(adjusted, tempcolumn);
                if(adjusted.time().second() % 10 == 0)
                {
                    model_10s->newMeasurement(adjusted, tempcolumn);
                }
                if(adjusted.time().second() % 15 == 0)
                {
                    model_15s->newMeasurement(adjusted, tempcolumn);
                    if(adjusted.time().second() % 30 == 0)
                    {
                        model_30s->newMeasurement(adjusted, tempcolumn);
                        if(adjusted.time().second() == 0)
                        {
                            model_1m->newMeasurement(adjusted, tempcolumn);
                        }
                    }
                }
            }
        }
        @<Synthesize measurements for columns in set@>@;
    }
    else
    {
        @<Add the first measurement to every model@>@;
    }
    lastMeasurement[tempcolumn] = measure;
}

@ The first measurement in a series should be the epoch measurement. This
should exist in every level of detail.

@<Add the first measurement to every model@>=
for(MeasurementModel *m: modelSet)
{
    m->newMeasurement(measure, tempcolumn);
}

@ Some measurement hardware in use cannot guarantee delivery of at least one
measurement per second. This causes problems for the current |ZoomLog|
implementation as, for example, if there is no measurement at a time where
the seconds are divisible by 5, there will be no entry in that view. This can
result in situations where the |ZoomLog| at its default view of one measurement
every 30 seconds might not display any data at all aside from the first
measurement, the last measurement, and any measurement that happens to have an
annotation associated with it. The solution in this case is to synthesize
measurements so that the |ZoomLog| thinks it gets at least one measurement
every second.

Prior to version 1.8 this simply replicated the last measurement every second
until the time for the most recent measurement was reached, however this yields
problematic results when loading saved data or attempting to use this view for
manual data entry. The current behavior performs a linear interpolation which
will match the graph.

@<Synthesize measurements for slow hardware@>=
if(lastMeasurement.count(tempcolumn) > 0)
{
    if(lastMeasurement[tempcolumn].time() < measure.time())
    {
        std::vector<QTime> timelist;
        std::vector<double> templist;
        QTime z = QTime(0, 0, 0, 0);
        double ptime = (double)(z.secsTo(lastMeasurement[tempcolumn].time()));
        double ptemp = lastMeasurement[tempcolumn].temperature();
        double ctime = (double)(z.secsTo(measure.time()));
        double ctemp = measure.temperature();
        for(QTime i = lastMeasurement[tempcolumn].time().addSecs(1); i < measure.time(); i = i.addSecs(1))
        {
            timelist.push_back(i);
            double v = ((ptemp * (ctime - z.secsTo(i))) + (ctemp * (z.secsTo(i) - ptime))) / (ctime - ptime);
            templist.push_back(v);
        }
        for(unsigned int i = 0; i < timelist.size(); i++)
        {
            Measurement synthesized = measure;
            synthesized.setTime(timelist[i]);
            synthesized.setTemperature(templist[i]);
            newMeasurement(synthesized, tempcolumn);
        }
    }
}

@ New to \pn{} 1.4 is the concept of a current column set. This was added to
improve support for devices where measurements on different data series may not
arrive at exactly the same time and for multi-device configurations where
measurements from different devices are unlikely to arrive at the same time.
This can cause issues with log annotations and serialization. The solution is
to group all columns that are logically part of the same data acquisition
process and as measurements come in, the most recent measurement from other
columns can be duplicated at the new time. Two methods are responsible for
managing this measurement set. One adds a column to the set and the other
removes all columns from the set.

@<ZoomLog Implementation@>=
void ZoomLog::addToCurrentColumnSet(int column)
{
    currentColumnSet.push_back(column);
}

void ZoomLog::clearCurrentColumnSet()
{
    currentColumnSet.clear();
}

@ Replicating the measurements occurs as measurements are delivered. Note
that this code will not be called for the first measurement in each column.

@<Synthesize measurements for columns in set@>=
if(std::find(currentColumnSet.begin(), currentColumnSet.end(), tempcolumn) != currentColumnSet.end())
{
    for(int replicationcolumn: currentColumnSet)
    {
        if(replicationcolumn != tempcolumn)
        {
            if(lastMeasurement.count(replicationcolumn) > 0)
            {
                if(measure.time() > lastMeasurement[replicationcolumn].time())
                {
                    Measurement synthetic = lastMeasurement[replicationcolumn];
                    synthetic.setTime(measure.time());
                    model_ms->newMeasurement(synthetic, replicationcolumn);
                    if(synthetic.time().second() != lastMeasurement[replicationcolumn].time().second())@/
                    {
                        Measurement adjusted = synthetic;
                        adjusted.setTime(QTime(0, synthetic.time().minute(), synthetic.time().second(), 0));
                        model_1s->newMeasurement(adjusted, replicationcolumn);
                        if(adjusted.time().second() % 5 == 0)
                        {
                            model_5s->newMeasurement(adjusted, replicationcolumn);
                            if(adjusted.time().second() % 10 == 0)
                            {
                                model_10s->newMeasurement(adjusted, replicationcolumn);
                            }
                            if(adjusted.time().second() % 15 == 0)
                            {
                                model_15s->newMeasurement(adjusted, replicationcolumn);
                                if(adjusted.time().second() % 30 == 0)
                                {
                                    model_30s->newMeasurement(adjusted, replicationcolumn);
                                    if(adjusted.time().second() == 0)
                                    {
                                        model_1m->newMeasurement(adjusted, replicationcolumn);
                                    }
                                }
                            }
                        }
                    }
                    lastMeasurement[replicationcolumn] = synthetic;
                }
            }
        }
    }
}

@ Just as the first measurement should exist at every level of detail, so should
any annotations. The measurement models will, when presented with an annotation,
apply it to the most recently entered measurement in the specified data series.
This presents a problem for the coarser views as the data point the annotation
belongs to most likely does not exist in that view. Furthermore, the model as it
is currently written will overwrite annotations that already exist on a
measurement if it is still the most recently entered. When collecting samples
during profile development, it is common to produce several annotations in a
short amount of time. The most useful thing to do in such a case is to add the
most recent measurement to each model and then apply the annotation. This, of
course, should only be done if there is a most recent measurement. An annotation
regarding the starting condition of the roaster should apply to the yet to be
recorded time zero measurement.

Note that only the value from the temperature column specified is displayed in
the row with the annotation. It would be better to check the full detail model
to determine if there are other measurements at the annotation time and present
these as well. Another possibility in the case of data not existing in other
temperature columns would be to interpolate a value from the existing data in
these columns, however this is potentially challenging as I would want to keep
true measurements distinct from estimations.

@<ZoomLog Implementation@>=
void ZoomLog::newAnnotation(QString annotation, int tempcolumn,
                            int annotationcolumn)
{
    model_ms->newAnnotation(annotation, tempcolumn, annotationcolumn);
    if(lastMeasurement.count(tempcolumn) > 0)
    {
        for(MeasurementModel *m: modelSet)
        {
            m->newMeasurement(lastMeasurement[tempcolumn], tempcolumn);
        }
    }
    for(MeasurementModel *m: modelSet)
    {
        m->newAnnotation(annotation, tempcolumn, annotationcolumn);
    }
}

@ As measurements are added to the model, the model will emit rowChanged
signals. These signals are connected to a function here that will attempt to
scroll the view to keep the most recently entered data in the center of the
view.

@<ZoomLog Implementation@>=
void ZoomLog::centerOn(int row)
{
    scrollTo(currentModel->index(row, 0), QAbstractItemView::PositionAtCenter);
}

@ Once we are done with the data in the table, we want to clear it to prepare
for new data. This also clears the lists holding the output columns to use when
saving data.

@<ZoomLog Implementation@>=
void ZoomLog::clear()
{
    for(MeasurementModel *m: modelSet)
    {
        m->clear();
    }
    lastMeasurement.clear();
    saveTempCols.clear();
    saveControlCols.clear();
    saveNoteCols.clear();
}

@ These are depreciated methods originally written to assist in serializing
model data prior to the introduction of the |XMLOutput| class. These methods are
likely to be removed in a future version of the program.

@<ZoomLog Implementation@>=
QVariant ZoomLog::data(int row, int column) const
{
    return model_ms->data(model_ms->index(row, column, QModelIndex()),
                            Qt::DisplayRole);
}

int ZoomLog::rowCount()
{
    return model_ms->rowCount();
}

@ This method initializes an |XMLOutput| instance, passes the columns that we
would like to save to that object, and uses it to write an XML file with the
desired data to the specified device.

Since the output format does not currently specify a unit, there is an
assumption that the XML output will always have measurements in Fahrenheit. If
the model is not currently displaying measurements in Fahrenheit, it is asked to
do so before writing the XML data. User preference is restored after the XML
data has been written. Since this change is only performed on |model_ms|, most
users will never notice this.

@<ZoomLog Implementation@>=
bool ZoomLog::saveXML(QIODevice *device)
{
    Units::Unit prevUnits = model_ms->displayUnits();
    if(prevUnits != Units::Fahrenheit)
    {
        model_ms->setDisplayUnits(Units::Fahrenheit);
    }
    XMLOutput writer(model_ms, device, 0);
    for(int c: saveTempCols)
    {
        writer.addTemperatureColumn(model_ms->headerData(c, Qt::Horizontal).
                                              toString(), c);
    }
    for(int c: saveControlCols)
    {
        writer.addControlColumn(model_ms->headerData(c, Qt::Horizontal).
                                          toString(), c);
    }
    for(int c: saveNoteCols)
    {
        writer.addAnnotationColumn(model_ms->headerData(c, Qt::Horizontal).
                                             toString(), c);
    }
    bool retval = writer.output();
    if(prevUnits != Units::Fahrenheit)
    {
        model_ms->setDisplayUnits(prevUnits);
    }
    return retval;
}

@ This method is similar to |saveXML()|. The main difference is that CSV data is
exported instead of XML.

@<ZoomLog Implementation@>=
bool ZoomLog::saveCSV(QIODevice *device)
{
    CSVOutput writer(currentModel, device, 0);
    for(int c: saveTempCols)
    {
        writer.addTemperatureColumn(model_ms->headerData(c, Qt::Horizontal).
                                                         toString(), c);
    }
    for(int c: saveControlCols)
    {
        writer.addControlColumn(model_ms->headerData(c, Qt::Horizontal).
                                                     toString(), c);
    }
    for(int c: saveNoteCols)
    {
        writer.addAnnotationColumn(model_ms->headerData(c, Qt::Horizontal).
                                             toString(), c);
    }
    return writer.output();
}

@ Several little functions, all alike\nfnote{If you get the reference, you may
enjoy reading another \cweb{} program:\par\indent\pdfURL{%
http://www-cs-staff.stanford.edu/$\sim$uno/programs/advent.w.gz}
{http://www-cs-staff.stanford.edu/~uno/programs/advent.w.gz}}, are used to
switch the view from one level of detail to another.

@<ZoomLog Implementation@>=
void ZoomLog::switchLOD(MeasurementModel *m)
{
    disconnect(currentModel, SIGNAL(rowChanged(int)), this, 0);
    setModel(m);
    currentModel = m;
    connect(currentModel, SIGNAL(rowChanged(int)), this, SLOT(centerOn(int)));
}

void ZoomLog::LOD_ms()
{
    switchLOD(model_ms);
}

void ZoomLog::LOD_1s()
{
    switchLOD(model_1s);
}

void ZoomLog::LOD_5s()
{
    switchLOD(model_5s);
}

void ZoomLog::LOD_10s()
{
    switchLOD(model_10s);
}

void ZoomLog::LOD_15s()
{
    switchLOD(model_15s);
}

void ZoomLog::LOD_30s()
{
    switchLOD(model_30s);
}

void ZoomLog::LOD_1m()
{
    switchLOD(model_1m);
}

@ It can be useful to display temperature measurements in various units. To do
so, we simply tell all of the models which unit to provide data in. It is also
possible to obtain the currently selected unit.

@<ZoomLog Implementation@>=
void ZoomLog::setDisplayUnits(Units::Unit scale)
{
    model_ms->setDisplayUnits(scale);
    model_1s->setDisplayUnits(scale);
    model_5s->setDisplayUnits(scale);
    model_10s->setDisplayUnits(scale);
    model_15s->setDisplayUnits(scale);
    model_30s->setDisplayUnits(scale);
    model_1m->setDisplayUnits(scale);
}

Units::Unit ZoomLog::displayUnits()
{
    return model_ms->displayUnits();
}

@ For convenience, a method is provided for returning a string containing the
time of the last inserted measurement in a given data series.

@<ZoomLog Implementation@>=
QString ZoomLog::lastTime(int series)
{
    Measurement measure = lastMeasurement[series];
    QTime time = measure.time();
    return time.toString("h:mm:ss.zzz");
}

@ This just leaves the initial table setup.

@<ZoomLog Implementation@>=
ZoomLog::ZoomLog() : QTableView(NULL), model_ms(new MeasurementModel(this)),
    model_1s(new MeasurementModel(this)),@/ model_5s(new MeasurementModel(this)),
    model_10s(new MeasurementModel(this)),@/ model_15s(new MeasurementModel(this)),
    model_30s(new MeasurementModel(this)),@/ model_1m(new MeasurementModel(this))@/
{@/
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);
    modelSet.push_back(model_ms);
    modelSet.push_back(model_1s);
    modelSet.push_back(model_5s);
    modelSet.push_back(model_10s);
    modelSet.push_back(model_15s);
    modelSet.push_back(model_30s);
    modelSet.push_back(model_1m);
    currentModel = model_30s;
    setModel(currentModel);
    connect(currentModel, SIGNAL(rowChanged(int)), this, SLOT(centerOn(int)));
    connect(horizontalHeader(), SIGNAL(sectionResized(int, int, int)),
            this, SLOT(persistColumnResize(int, int, int)));
    connect(horizontalHeader(), SIGNAL(sectionCountChanged(int, int)),
            this, SLOT(restoreColumnWidths()));
}

@ A new method was added to this class for version 1.0.7. This allows header
data to be set on the log and have it propagate to the model set. The longer
term plan involves removing the hard coding of some of the header data.

@<ZoomLog Implementation@>=
void ZoomLog::setHeaderData(int section, QString text)
{
    MeasurementModel *m;
    foreach(m, modelSet)
    {
        m->setHeaderData(section, Qt::Horizontal, QVariant(text));
    }
}

@ As of version 1.2.3, these methods replace similar methods added for version
1.0.8. The main difference is that it is now possible to save multiple data
series to the same output document.

Starting in version 1.6 it is possible to save control columns. These should
contain unitless data which should remain unaffected by the current displayed
unit.

@<ZoomLog Implementation@>=
void ZoomLog::addOutputTemperatureColumn(int column)
{
    saveTempCols.push_back(column);
}

void ZoomLog::addOutputControlColumn(int column)
{
    saveControlCols.push_back(column);
}

void ZoomLog::addOutputAnnotationColumn(int column)
{
    saveNoteCols.push_back(column);
}

void ZoomLog::clearOutputColumns()
{
    saveTempCols.clear();
    saveControlCols.clear();
    saveNoteCols.clear();
}

@ Starting in version 1.4 two methods have been introduced which are used to
save and restore column widths.

@<ZoomLog Implementation@>=
void ZoomLog::persistColumnResize(int column, int, int newsize)
{
    @<Save updated column size@>@;
}

void ZoomLog::restoreColumnWidths()
{
    @<Restore table column widths@>@;
}

void ZoomLog::setVisible(bool visibility)
{
    QTableView::setVisible(visibility);
}

void ZoomLog::showEvent(QShowEvent *)
{
    @<Restore table column widths@>@;
}

@ The |ZoomLog| class is one of the more complicated classes to expose to the
scripting engine. In addition to a script constructor, we also need functions
for saving and restoring the state of the display and functions for saving data
from the log in the supported formats.

@<Function prototypes for scripting@>=
void setZoomLogProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructZoomLog(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveXML(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveCSV(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveState(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_restoreState(QScriptContext *context,
                                  QScriptEngine *engine);
QScriptValue ZoomLog_lastTime(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveTemporary(QScriptContext *context,
                                   QScriptEngine *engnie);
QScriptValue ZoomLog_setDisplayUnits(QScriptContext *context,
                                     QScriptEngine *engine);

@ Of these, the global object only needs to know about the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructZoomLog);
value = engine->newQMetaObject(&ZoomLog::staticMetaObject, constructor);
engine->globalObject().setProperty("ZoomLog", value);

@ The script constructor sets properties on the newly created object to allow
the other functions to be called.

@<Functions for scripting@>=
QScriptValue constructZoomLog(QScriptContext *, QScriptEngine *engine)@/
{@/
    QScriptValue object = engine->newQObject(new ZoomLog);
    setZoomLogProperties(object, engine);
    return object;@/
}

void setZoomLogProperties(QScriptValue value, QScriptEngine *engine)
{
    setQTableViewProperties(value, engine);
    value.setProperty("saveXML", engine->newFunction(ZoomLog_saveXML));
    value.setProperty("saveCSV", engine->newFunction(ZoomLog_saveCSV));
    value.setProperty("saveState", engine->newFunction(ZoomLog_saveState));
    value.setProperty("restoreState",
                      engine->newFunction(ZoomLog_restoreState));
    value.setProperty("lastTime", engine->newFunction(ZoomLog_lastTime));
    value.setProperty("saveTemporary",
                      engine->newFunction(ZoomLog_saveTemporary));
    value.setProperty("setDisplayUnits", engine->newFunction(ZoomLog_setDisplayUnits));
}

@ The functions for saving data are simple wrappers around the corresponding
calls in |ZoomLog|, except for a function added for saving data to a temporary
file. The last provides the name of the file saved for use in copying that data
to a database entry.

@<Functions for scripting@>=
QScriptValue ZoomLog_saveXML(QScriptContext *context, QScriptEngine *engine)
{
    ZoomLog *self = getself<ZoomLog *>(context);
    bool retval = self->saveXML(argument<QIODevice *>(0, context));
    return QScriptValue(engine, retval);
}

QScriptValue ZoomLog_saveCSV(QScriptContext *context, QScriptEngine *engine)
{
    ZoomLog *self = getself<ZoomLog *>(context);
    bool retval = self->saveCSV(argument<QIODevice *>(0, context));
    return QScriptValue(engine, retval);
}

QScriptValue ZoomLog_saveTemporary(QScriptContext *context,
                                   QScriptEngine *engine)
{
    ZoomLog *self = getself<ZoomLog *>(context);
    QString filename = QDir::tempPath();
    filename.append("/");
    filename.append(QUuid::createUuid().toString());
    filename.append(".xml");
    QFile *file = new QFile(filename);
    self->saveXML(file);
    file->close();
    delete file;
    return QScriptValue(engine, filename);
}

@ The remaining functions are convenience functions for use with the scripting
engine. One will save the column widths to a |QSettings| object. Another will
restore the column widths from settings. Finally, there is a function for
obtaining a string representation of the most recent measurement from a data
series.

\danger There are a couple of problems with these functions. First, the body of
these functions would probably be better off as methods in the |ZoomLog| class
proper, either as slots or |Q_INVOKABLE| so the special scripting functions
could be eliminated. Second, rather than polluting the settings with separate
entries for each column, it would probably be better to store all of these
values in an array.\endanger

|ZoomLog_saveState()| was changed in version 1.2.3 to not save a new value for
the column width if that width is |0|. This was done mainly to ease debugging.
Similarly, |ZoomLog_restoreState()| picks a new default value when |0| is
encountered.

@<Functions for scripting@>=
QScriptValue ZoomLog_saveState(QScriptContext *context, QScriptEngine *)
{
    ZoomLog *self = getself<@[ZoomLog *@]>(context);
    QString key = argument<QString>(0, context);
    int columns = argument<int>(1, context);
    QSettings settings;
    for(int i = 0; i < columns; i++)
    {
        if(self->columnWidth(i))
        {
            settings.beginGroup(key);
            settings.setValue(QString("%1").arg(i), self->columnWidth(i));
            settings.endGroup();
        }
    }
    return QScriptValue();
}

QScriptValue ZoomLog_restoreState(QScriptContext *context, QScriptEngine *)
{
    ZoomLog *self = getself<@[ZoomLog *@]>(context);
    QString key = argument<QString>(0, context);
    int columns = argument<int>(1, context);
    QSettings settings;
    for(int i = 0; i < columns; i++)
    {
        settings.beginGroup(key);
        self->setColumnWidth(i,
            settings.value(QString("%1").arg(i), 80).toInt());
        if(settings.value(QString("%1").arg(i), 80).toInt() == 0)
        {
            self->setColumnWidth(i, 80);
        }
        settings.endGroup();
    }
    return QScriptValue();
}

QScriptValue ZoomLog_lastTime(QScriptContext *context, QScriptEngine *engine)
{
    ZoomLog *self = getself<@[ZoomLog *@]>(context);
    return QScriptValue(engine, self->lastTime(argument<int>(0, context)));
}

@ There seems to be a bad interaction when enumerated value types as used as
the argument to slot methods called through QtScript. Script code that attempts
to make use of the enumeration appears to get the value without any type
information. When attempting to use that value as an argument the meta-object
system cannot find an appropriate match and the script just hangs silently.
The solution is to wrap such methods in the script bindings and explicitly cast
the argument value to the enumerated type. This looks stupid but it works.

@<Functions for scripting@>=
QScriptValue ZoomLog_setDisplayUnits(QScriptContext *context, QScriptEngine *)
{
    ZoomLog *self = getself<@[ZoomLog *@]>(context);
    self->setDisplayUnits((Units::Unit)argument<int>(0, context));
    return QScriptValue();
}
