#define PROGRAM_NAME "Typica" \

#define FULLTIMETOINT(t) (t.msec() +(t.second() *1000) +(t.minute() *60*1000) )  \

#define TIMETOINT(t) ((t.hour() *60*60) +(t.minute() *60) +(t.second() ) )  \

#define TIMESUBTRACT(t1,t2) (t1.addSecs(-(TIMETOINT(t2) ) ) .addMSecs(-t2.msec() ) )  \

#define AppInstance (qobject_cast<Application*> (qApp) )  \

/*15:*/
#line 753 "./typica.w"

/*17:*/
#line 834 "./typica.w"

#include <QtCore> 
#include <QtGui> 
#include <QtScript> 
#include <QtScriptTools> 
#include <QtXml> 
#include <QtSql> 
#include <QtDebug> 
#include <QtXmlPatterns> 
#include <QtWebKit> 

/*:17*//*666:*/
#line 15618 "./typica.w"

#include "qextserialport.h"
#include "qextserialenumerator.h"

/*:666*/
#line 754 "./typica.w"

/*31:*/
#line 1133 "./typica.w"

class ScriptQMainWindow:public QMainWindow
{
Q_OBJECT
public:
ScriptQMainWindow();
public slots:
void show();
void saveSizeAndPosition(const QString&key);
void restoreSizeAndPosition(const QString&key);
void displayStatus(const QString&message= QString());
protected:
void closeEvent(QCloseEvent*event);
void showEvent(QShowEvent*event);
signals:
void aboutToClose(void);
};

/*:31*//*134:*/
#line 3252 "./typica.w"

class SqlQueryConnection:public QSqlQuery
{
public:
SqlQueryConnection(const QString&query= QString());
~SqlQueryConnection();
QSqlQuery*operator->();
private:
QString connection;
QSqlQuery*q;
};

/*:134*//*190:*/
#line 5026 "./typica.w"

class NumericDelegate:public QItemDelegate
{
Q_OBJECT
public:
NumericDelegate(QObject*parent= NULL);
QWidget*createEditor(QWidget*parent,
const QStyleOptionViewItem&option,
const QModelIndex&index)const;
void setEditorData(QWidget*editor,const QModelIndex&index)const;
void setModelData(QWidget*editor,QAbstractItemModel*model,
const QModelIndex&index)const;
void updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&index)const;
};

/*:190*//*216:*/
#line 5664 "./typica.w"

class Measurement
{
public:
enum TemperatureUnits
{
Fahrenheit= 10144,
Celsius= 10143,
Kelvin= 10325,
Rankine= 10145
};
private:
double theTemperature;
QTime theTime;
TemperatureUnits unit;
public:
Measurement(double temperature= 0,QTime time= QTime(),
TemperatureUnits sc= Fahrenheit);
Measurement(double temperature);
Measurement(const Measurement&x);
Measurement&operator= (Measurement&x);
~Measurement();
double temperature()const;
QTime time()const;
void setTemperature(double temperature);
void setTime(QTime time);
void setUnit(TemperatureUnits scale);
TemperatureUnits scale();
Measurement toFahrenheit();
Measurement toCelsius();
Measurement toKelvin();
Measurement toRankine();
};

/*:216*//*228:*/
#line 5966 "./typica.w"

class Channel;
class DAQImplementation;

class DAQ:public QObject
{
Q_OBJECT
Q_ENUMS(TemperatureUnits)
Q_ENUMS(ThermocoupleType)
DAQImplementation*imp;
private slots:
void threadFinished();
public:
DAQ(QString device,const QString&driver= QString("nidaqmxbase"));
~DAQ();
Channel*newChannel(int units,int thermocouple);
Q_INVOKABLE void setClockRate(double Hz);
Q_INVOKABLE void start();
Q_INVOKABLE void stop();
enum TemperatureUnits
{
Fahrenheit= 10144,
Celsius= 10143,
Kelvin= 10325,
Rankine= 10145
};
enum ThermocoupleType
{
TypeJ= 10072,
TypeK= 10073,
TypeN= 10077,
TypeR= 10082,
TypeS= 10085,
TypeT= 10086,
TypeB= 10047,
TypeE= 10055
};
};

/*:228*//*229:*/
#line 6012 "./typica.w"

class DAQImplementation:public QThread
{
Q_OBJECT
public:
DAQImplementation(const QString&driverinfo);
~DAQImplementation();
void run();
void measure();
/*230:*/
#line 6032 "./typica.w"

typedef int(*daqfp)(...);
daqfp read;
daqfp errorInfo;
daqfp startTask;
daqfp createTask;
daqfp createChannel;
daqfp setClock;
daqfp stopTask;
daqfp clearTask;
daqfp resetDevice;
daqfp waitForMeasurement;

/*:230*/
#line 6021 "./typica.w"

/*231:*/
#line 6048 "./typica.w"

bool useBase;
QString device;
QVector<Channel*> channelMap;
unsigned int handle;
int error;
int channels;
bool ready;
QLibrary driver;
QVector<Measurement::TemperatureUnits> unitMap;

/*:231*/
#line 6022 "./typica.w"

};

/*:229*//*247:*/
#line 6545 "./typica.w"

class FakeDAQImplementation:public QThread
{
Q_OBJECT
public:
FakeDAQImplementation();
~FakeDAQImplementation();
void run();
void measure();
QVector<Channel*> channelMap;
int channels;
bool ready;
double clockRate;
};

class FakeDAQ:public QObject
{
Q_OBJECT
FakeDAQImplementation*imp;
public:
FakeDAQ(QString device);
~FakeDAQ();
Channel*newChannel(int units,int thermocouple);
Q_INVOKABLE void setClockRate(double Hz);
Q_INVOKABLE void start();
};

/*:247*//*254:*/
#line 6732 "./typica.w"

class Channel:public QObject
{
Q_OBJECT
public:
Channel();
~Channel();
public slots:
void input(Measurement measurement);
signals:
void newData(Measurement);
};

/*:254*//*258:*/
#line 6795 "./typica.w"

class LinearCalibrator:public QObject
{
Q_OBJECT
Q_PROPERTY(double measuredLower READ measuredLower
WRITE setMeasuredLower)
Q_PROPERTY(double measuredUpper READ measuredUpper
WRITE setMeasuredUpper)
Q_PROPERTY(double mappedLower READ mappedLower WRITE setMappedLower)
Q_PROPERTY(double mappedUpper READ mappedUpper WRITE setMappedUpper)
Q_PROPERTY(bool closedRange READ isClosedRange WRITE setClosedRange)
Q_PROPERTY(double sensitivity READ sensitivity WRITE setSensitivity)
public:
LinearCalibrator(QObject*parent= NULL);
double measuredLower();
double measuredUpper();
double mappedLower();
double mappedUpper();
bool isClosedRange();
double sensitivity();
public slots:
void setMeasuredLower(double lower);
void setMeasuredUpper(double upper);
void setMappedLower(double lower);
void setMappedUpper(double upper);
void setClosedRange(bool closed);
void setSensitivity(double sensitivity);
void newMeasurement(Measurement measure);
signals:
void measurement(Measurement measure);
private:
double Lo1;
double Lo2;
double Up1;
double Up2;
double sensitivitySetting;
bool clamp;
};

/*:258*//*265:*/
#line 6989 "./typica.w"

class LinearSplineInterpolator:public QObject
{
Q_OBJECT
public:
LinearSplineInterpolator(QObject*parent= NULL);
Q_INVOKABLE void add_pair(double source,double destination);
public slots:
void newMeasurement(Measurement measure);
signals:
void newData(Measurement measure);
private:
void make_interpolators();
QMap<double,double> *pairs;
QList<LinearCalibrator*> *interpolators;
};

/*:265*//*270:*/
#line 7124 "./typica.w"

class TemperatureDisplay:public QLCDNumber
{
Q_OBJECT
Q_ENUMS(DisplayUnits)
int unit;
public:
enum DisplayUnits
{
Auto= -1,
Fahrenheit= 10144,
Celsius= 10143,
Kelvin= 10325,
Rankine= 10145
};
TemperatureDisplay(QWidget*parent= NULL);
~TemperatureDisplay();
public slots:
void setValue(Measurement temperature);
void invalidate();
void setDisplayUnits(DisplayUnits scale);
};

/*:270*//*279:*/
#line 7300 "./typica.w"

class MeasurementTimeOffset:public QObject
{
Q_OBJECT
QTime epoch;
QTime previous;
bool hasPrevious;
public:
MeasurementTimeOffset(QTime zero);
QTime zeroTime();
public slots:
void newMeasurement(Measurement measure);
void setZeroTime(QTime zero);
signals:
void measurement(Measurement measure);
};

/*:279*//*286:*/
#line 7450 "./typica.w"

class ThresholdDetector:public QObject
{
Q_OBJECT
Q_ENUMS(EdgeDirection)
public:
enum EdgeDirection{
Ascending,Descending
};
ThresholdDetector(double value);
public slots:
void newMeasurement(Measurement measure);
void setThreshold(double value);
void setEdgeDirection(EdgeDirection direction);
signals:
void timeForValue(double);
private:
double previousValue;
double threshold;
EdgeDirection currentDirection;
};

/*:286*//*291:*/
#line 7556 "./typica.w"

class ZeroEmitter:public QObject
{
Q_OBJECT
int col;
double temp;
public:
ZeroEmitter(int tempcolumn);
int column();
double lastTemperature();
public slots:
void newMeasurement(Measurement measure);
void setColumn(int column);
void emitZero();
signals:
void measurement(Measurement measure,int tempcolumn);
};

/*:291*//*296:*/
#line 7649 "./typica.w"

class MeasurementAdapter:public QObject
{
Q_OBJECT
int col;
public:
MeasurementAdapter(int tempcolumn);
int column();
public slots:
void newMeasurement(Measurement measure);
void setColumn(int column);
signals:
void measurement(Measurement measure,int tempcolumn);
};

/*:296*//*301:*/
#line 7738 "./typica.w"

class GraphView:public QGraphicsView
{
Q_OBJECT
QGraphicsScene*theScene;
QMap<int,QList<QGraphicsLineItem*> *> *graphLines;
QMap<int,QPointF> *prevPoints;
QMap<int,double> *translations;
QList<QGraphicsItem*> *gridLinesF;
QList<QGraphicsItem*> *gridLinesC;
public:
GraphView(QWidget*parent= NULL);
void removeSeries(int column);
protected:
void resizeEvent(QResizeEvent*event);
public slots:
void newMeasurement(Measurement measure,int tempcolumn);
void setSeriesTranslation(int column,double offset);
void clear();
void showF();
void showC();
};

/*:301*//*316:*/
#line 8089 "./typica.w"

class MeasurementModel;
class ZoomLog:public QTableView
{
Q_OBJECT
/*317:*/
#line 8137 "./typica.w"

MeasurementModel*model_ms;
MeasurementModel*model_1s;
MeasurementModel*model_5s;
MeasurementModel*model_10s;
MeasurementModel*model_15s;
MeasurementModel*model_30s;
MeasurementModel*model_1m;
QList<MeasurementModel*> modelSet;
QHash<int,Measurement> lastMeasurement;
MeasurementModel*currentModel;
QList<int> saveTempCols;
QList<int> saveNoteCols;
QList<int> currentColumnSet;

/*:317*/
#line 8094 "./typica.w"

void switchLOD(MeasurementModel*m);
private slots:
void centerOn(int row);
void persistColumnResize(int column,int oldsize,int newsize);
void restoreColumnWidths();
public:
ZoomLog();
QVariant data(int row,int column)const;
int rowCount();
bool saveXML(QIODevice*device);
bool saveCSV(QIODevice*device);
QString lastTime(int series);
Q_INVOKABLE int displayUnits();
public slots:
void setVisible(bool visibility);
void setHeaderData(int section,QString text);
void LOD_ms();
void LOD_1s();
void LOD_5s();
void LOD_10s();
void LOD_15s();
void LOD_30s();
void LOD_1m();
void newMeasurement(Measurement measure,int tempcolumn);
void newAnnotation(QString annotation,int tempcolumn,
int annotationcolumn);
void clear();
void addOutputTemperatureColumn(int column);
void addOutputAnnotationColumn(int column);
void clearOutputColumns();
void setDisplayUnits(int scale);
void addToCurrentColumnSet(int column);
void clearCurrentColumnSet();
protected:
virtual void showEvent(QShowEvent*event);
};

/*:316*//*340:*/
#line 8751 "./typica.w"

class MeasurementList;
class MeasurementModel:public QAbstractItemModel
{
Q_OBJECT
Q_ENUMS(DisplayUnits);
int unit;
QList<MeasurementList*> *entries;
QStringList*hData;
int colcount;
QHash<int,int> *lastTemperature;
QList<MeasurementList*> ::iterator lastInsertion;
public:
enum DisplayUnits
{
Auto= -1,
Fahrenheit= 10144,
Celsius= 10143,
Kelvin= 10325,
Rankine= 10145
};
MeasurementModel(QObject*parent= NULL);
~MeasurementModel();
int rowCount(const QModelIndex&parent= QModelIndex())const;
int columnCount(const QModelIndex&parent= QModelIndex())const;
bool setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int role= Qt::DisplayRole);
QVariant data(const QModelIndex&index,int role)const;
bool setData(const QModelIndex&index,const QVariant&value,
int role= Qt::EditRole);
Qt::ItemFlags flags(const QModelIndex&index)const;
QVariant headerData(int section,Qt::Orientation orientation,
int role= Qt::DisplayRole)const;
QModelIndex index(int row,int column,
const QModelIndex&parent= QModelIndex())const;
QModelIndex parent(const QModelIndex&index)const;
int displayUnits();
public slots:
void newMeasurement(Measurement measure,int tempcolumn);
void newAnnotation(QString annotation,int tempcolumn,
int annotationColumn);
void clear();
void setDisplayUnits(int scale);
signals:
void rowChanged(int);
};

/*:340*//*341:*/
#line 8803 "./typica.w"

class MeasurementList:public QVariantList
{
public:
bool operator<(const MeasurementList&other)const;
bool operator==(const MeasurementList&other)const;
};

/*:341*//*367:*/
#line 9440 "./typica.w"

class AnnotationButton:public QPushButton
{
Q_OBJECT
QString note;
int tc;
int ac;
int count;
public:
AnnotationButton(const QString&text,QWidget*parent= NULL);
public slots:
void setAnnotation(const QString&annotation);
void setTemperatureColumn(int tempcolumn);
void setAnnotationColumn(int annotationcolumn);
void annotate();
void resetCount();
signals:
void annotation(QString annotation,int tempcolumn,
int notecolumn);
};

/*:367*//*375:*/
#line 9565 "./typica.w"

class AnnotationSpinBox:public QDoubleSpinBox
{
Q_OBJECT
QString pretext;
QString posttext;
int tc;
int ac;
bool change;
public:
AnnotationSpinBox(const QString&pret,const QString&postt,
QWidget*parent= NULL);
public slots:
void setPretext(const QString&pret);
void setPosttext(const QString&postt);
void setTemperatureColumn(int tempcolumn);
void setAnnotationColumn(int annotationcolumn);
void annotate();
void resetChange();
signals:
void annotation(QString annotation,int tempcolumn,
int notecolumn);
};

/*:375*//*383:*/
#line 9724 "./typica.w"

class TimerDisplay:public QLCDNumber
{
Q_OBJECT
/*384:*/
#line 9774 "./typica.w"

Q_PROPERTY(QTime seconds READ seconds WRITE setTimer)
Q_PROPERTY(TimerMode mode READ mode WRITE setMode)
Q_PROPERTY(bool running READ isRunning)
Q_PROPERTY(QTime resetValue READ resetValue WRITE setResetValue)
Q_PROPERTY(QString displayFormat READ displayFormat WRITE setDisplayFormat)
Q_PROPERTY(bool autoReset READ autoReset WRITE setAutoReset)

/*:384*/
#line 9728 "./typica.w"

private slots:
void updateTime();
void setCountUpMode();
void setCountDownMode();
void setClockMode();
public:
TimerDisplay(QWidget*parent= NULL);
~TimerDisplay();
enum TimerMode
{
CountUp,
CountDown,
Clock
};
QString value();
QTime seconds();
TimerMode mode();
bool isRunning();
QTime resetValue();
QString displayFormat();
bool autoReset();
public slots:
void setTimer(QTime value= QTime(0,0,0));
void setMode(TimerMode mode);
void startTimer();
void stopTimer();
void copyTimer();
void setResetValue(QTime value= QTime(0,0,0));
void reset();
void setDisplayFormat(QString format);
void setAutoReset(bool reset);
void updateDisplay();
signals:
void valueChanged(QTime);
void runStateChanged(bool);
private:
/*385:*/
#line 9784 "./typica.w"

QTime s;
QTime r;
QTimer clock;
TimerDisplay::TimerMode m;
bool running;
bool ar;
QAction*startAction;
QAction*stopAction;
QAction*resetAction;
QString f;
QTime relative;
QTime base;

/*:385*/
#line 9765 "./typica.w"

};

/*:383*//*405:*/
#line 10143 "./typica.w"

class PackLayout:public QLayout
{
int doLayout(const QRect&rect,bool testOnly)const;
QList<QLayoutItem*> itemList;
Qt::Orientations orientation;
public:
PackLayout(QWidget*parent,int margin= 0,int spacing= -1);
PackLayout(int spacing= -1);
~PackLayout();
void addItem(QLayoutItem*item);
Qt::Orientations expandingDirections()const;
bool hasHeightForWidth()const;
int heightForWidth(int width)const;
int count()const;
QLayoutItem*itemAt(int index)const;
QSize minimumSize()const;
void setGeometry(const QRect&rect);
void setOrientation(Qt::Orientations direction);
QSize sizeHint()const;
QLayoutItem*takeAt(int index);
};

/*:405*//*418:*/
#line 10421 "./typica.w"

class SceneButton:public QGraphicsScene
{
Q_OBJECT
public:
SceneButton();
~SceneButton();
protected:
void mousePressEvent(QGraphicsSceneMouseEvent*mouseEvent);
signals:
void clicked(QPoint pos);
};

/*:418*//*420:*/
#line 10463 "./typica.w"

class WidgetDecorator:public QWidget
{
Q_OBJECT
PackLayout*layout;
QGraphicsView*label;
QGraphicsTextItem*text;
SceneButton*scene;
public:
WidgetDecorator(QWidget*widget,const QString&labeltext,
Qt::Orientations orientation= Qt::Horizontal,
QWidget*parent= NULL,Qt::WindowFlags f= 0);
~WidgetDecorator();
void setBackgroundBrush(QBrush background);
void setTextColor(QColor color);
};

/*:420*//*431:*/
#line 10638 "./typica.w"

class LogEditWindow:public QMainWindow
{
Q_OBJECT
QWidget*centralWidget;
PackLayout*mainLayout;
QHBoxLayout*addRowsLayout;
QLabel*startTimeLabel;
QTimeEdit*startTime;
QLabel*endTimeLabel;
QTimeEdit*endTime;
QLabel*intervalLabel;
QSpinBox*interval;
QPushButton*addRows;
QAction*saveXml;
QAction*saveCsv;
QAction*openXml;
MeasurementModel*model;
QTableView*log;
private slots:
void addTheRows();
void saveXML();
void saveCSV();
void openXML();
protected:
void closeEvent(QCloseEvent*event);
public:
LogEditWindow();
};

/*:431*//*445:*/
#line 10946 "./typica.w"

class XMLOutput:public QObject
{
Q_OBJECT
MeasurementModel*data;
QIODevice*out;
int time;
QMap<int,QString> temperatureColumns;
QMap<int,QString> annotationColumns;
public:
XMLOutput(MeasurementModel*model,QIODevice*device,int timec= 0);
void addTemperatureColumn(const QString&series,int column);
void addAnnotationColumn(const QString&series,int column);
void setModel(MeasurementModel*model);
void setTimeColumn(int column);
void setDevice(QIODevice*device);
bool output();
};

/*:445*//*452:*/
#line 11142 "./typica.w"

class XMLInput:public QObject
{
Q_OBJECT
int firstc;
QIODevice*in;
public:
XMLInput(QIODevice*input,int c);
void setFirstColumn(int column);
void setDevice(QIODevice*device);
bool input();
signals:
void measure(Measurement,int);
void annotation(QString,int,int);
void newTemperatureColumn(int,QString);
void newAnnotationColumn(int,QString);
void lastColumn(int);
};

/*:452*//*463:*/
#line 11383 "./typica.w"

class CSVOutput
{
MeasurementModel*data;
QIODevice*out;
int time;
QMap<int,QString> temperatureColumns;
QMap<int,QString> annotationColumns;
public:
CSVOutput(MeasurementModel*model,QIODevice*device,int timec= 0);
void addTemperatureColumn(const QString&series,int column);
void addAnnotationColumn(const QString&series,int column);
void setModel(MeasurementModel*model);
void setTimeColumn(int column);
void setDevice(QIODevice*device);
bool output();
};

/*:463*//*477:*/
#line 11644 "./typica.w"

class NodeInserter;
class DeviceTreeModel;
class Application:public QApplication
{
Q_OBJECT
public:
Application(int&argc,char**argv);
QDomDocument*configuration();
/*591:*/
#line 14029 "./typica.w"

QDomDocument deviceConfiguration();

/*:591*//*624:*/
#line 14702 "./typica.w"

void registerDeviceConfigurationWidget(QString driver,QMetaObject widget);
QWidget*deviceConfigurationWidget(DeviceTreeModel*model,
const QModelIndex&index);

/*:624*//*629:*/
#line 14806 "./typica.w"

QList<NodeInserter*> topLevelNodeInserters;

/*:629*/
#line 11653 "./typica.w"

QSqlDatabase database();
QScriptEngine*engine;
public slots:
/*592:*/
#line 14036 "./typica.w"

void saveDeviceConfiguration();

/*:592*/
#line 11657 "./typica.w"

private:
/*590:*/
#line 14020 "./typica.w"

QDomDocument deviceConfigurationDocument;

/*:590*//*623:*/
#line 14696 "./typica.w"

QHash<QString,QMetaObject> deviceConfigurationWidgets;

/*:623*/
#line 11659 "./typica.w"

QDomDocument conf;
};

/*:477*//*485:*/
#line 11783 "./typica.w"

class SaltModel:public QAbstractItemModel
{
Q_OBJECT
QList<QList<QMap<int,QVariant> > > modelData;
QStringList hData;
int colcount;
public:
SaltModel(int columns);
~SaltModel();
int rowCount(const QModelIndex&parent= QModelIndex())const;
int columnCount(const QModelIndex&parent= QModelIndex())const;
bool setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int role= Qt::DisplayRole);
QVariant data(const QModelIndex&index,int role)const;
bool setData(const QModelIndex&index,const QVariant&value,
int role= Qt::EditRole);
Qt::ItemFlags flags(const QModelIndex&index)const;
QVariant headerData(int section,Qt::Orientation orientation,
int role= Qt::DisplayRole)const;
QModelIndex index(int row,int column,
const QModelIndex&parent= QModelIndex())const;
QModelIndex parent(const QModelIndex&index)const;
QString arrayLiteral(int column,int role)const;
QString quotedArrayLiteral(int column,int role)const;
};

/*:485*//*498:*/
#line 12096 "./typica.w"

class SqlComboBox:public QComboBox
{
Q_OBJECT
int dataColumn;
int displayColumn;
bool dataColumnShown;
public:
SqlComboBox();
~SqlComboBox();
SqlComboBox*clone(QWidget*parent);
public slots:
void addNullOption();
void addSqlOptions(QString query);
void setDataColumn(int column);
void setDisplayColumn(int column);
void showData(bool show);
};

/*:498*//*505:*/
#line 12218 "./typica.w"

class SqlComboBoxDelegate:public QItemDelegate
{
Q_OBJECT
SqlComboBox*delegate;
public:
SqlComboBoxDelegate(QObject*parent= NULL);
QWidget*createEditor(QWidget*parent,
const QStyleOptionViewItem&option,
const QModelIndex&index)const;
void setEditorData(QWidget*editor,const QModelIndex&index)const;
void setModelData(QWidget*editor,QAbstractItemModel*model,
const QModelIndex&index)const;
void setWidget(SqlComboBox*widget);
virtual QSize sizeHint()const;
void updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&index)const;
};

/*:505*//*516:*/
#line 12377 "./typica.w"

class SqlConnectionSetup:public QDialog
{
Q_OBJECT
public:
SqlConnectionSetup();
~SqlConnectionSetup();
public slots:
void testConnection();
private:
QFormLayout*formLayout;
QComboBox*driver;
QLineEdit*hostname;
QLineEdit*dbname;
QLineEdit*user;
QLineEdit*password;
QVBoxLayout*layout;
QHBoxLayout*buttons;
QPushButton*cancelButton;
QPushButton*connectButton;
};

/*:516*//*521:*/
#line 12505 "./typica.w"

class SqlQueryView:public QTableView
{
Q_OBJECT
public:
SqlQueryView(QWidget*parent= NULL);
void setQuery(const QString&query);
bool setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int role);
Q_INVOKABLE QVariant data(int row,int column,
int role= Qt::DisplayRole);
signals:
void openEntry(QString key);
void openEntryRow(int row);
protected:
virtual void showEvent(QShowEvent*event);
private slots:
void openRow(const QModelIndex&index);
void persistColumnResize(int column,int oldsize,int newsize);
};

/*:521*//*536:*/
#line 12753 "./typica.w"

class ReportAction:public QAction
{
Q_OBJECT
public:
ReportAction(const QString&fileName,const QString&reportName,
QObject*parent= NULL);
private slots:
void createReport();
private:
QString reportFile;
};

/*:536*//*548:*/
#line 12962 "./typica.w"

class ReportTable:public QObject
{
Q_OBJECT
QTextFrame*area;
QDomElement configuration;
QMap<QString,QVariant> bindings;
public:
ReportTable(QTextFrame*frame,QDomElement description);
~ReportTable();
Q_INVOKABLE void bind(QString placeholder,QVariant value);
public slots:
void refresh();
};

/*:548*//*560:*/
#line 13198 "./typica.w"

class FormArray:public QScrollArea
{
Q_OBJECT
QDomElement configuration;
QWidget itemContainer;
QVBoxLayout itemLayout;
int maxwidth;
int maxheight;
public:
FormArray(QDomElement description);
Q_INVOKABLE QWidget*elementAt(int index);
Q_INVOKABLE int elements();
public slots:
void addElements(int copies= 1);
void removeAllElements();
void setMaximumElementWidth(int width);
void setMaximumElementHeight(int height);
};

/*:560*//*570:*/
#line 13414 "./typica.w"

class ScaleControl:public QGraphicsView
{
Q_OBJECT
Q_PROPERTY(double initialValue READ initialValue WRITE setInitialValue)
Q_PROPERTY(double finalValue READ finalValue WRITE setFinalValue)
/*571:*/
#line 13440 "./typica.w"

QGraphicsScene scene;
QGraphicsPolygonItem initialDecrement;
QGraphicsPolygonItem initialIncrement;
QGraphicsPolygonItem finalDecrement;
QGraphicsPolygonItem finalIncrement;
QGraphicsPolygonItem initialIndicator;
QGraphicsPolygonItem finalIndicator;
QGraphicsPathItem scaleLine;
QPolygonF left;
QPolygonF right;
QPolygonF down;
QPolygonF up;
QPainterPath scalePath;
QBrush initialBrush;
QBrush finalBrush;
double nonScoredValue;
double scoredValue;
bool initialSet;
bool finalSet;
bool scaleDown;

/*:571*/
#line 13420 "./typica.w"

public:
ScaleControl();
double initialValue(void);
double finalValue(void);
virtual QSize sizeHint()const;
public slots:
void setInitialValue(double value);
void setFinalValue(double value);
signals:
void initialChanged(double);
void finalChanged(double);
protected:
virtual void mousePressEvent(QMouseEvent*event);
virtual void mouseReleaseEvent(QMouseEvent*event);
};

/*:570*//*582:*/
#line 13737 "./typica.w"

class IntensityControl:public QGraphicsView
{
Q_OBJECT
Q_PROPERTY(double value READ value WRITE setValue)
QGraphicsScene scene;
QGraphicsPolygonItem decrement;
QGraphicsPolygonItem increment;
QGraphicsPolygonItem indicator;
QGraphicsPathItem scaleLine;
QPolygonF left;
QPolygonF up;
QPolygonF down;
QPainterPath scalePath;
QBrush theBrush;
double theValue;
bool valueSet;
bool scaleDown;
public:
IntensityControl();
double value();
virtual QSize sizeHint()const;
public slots:
void setValue(double val);
signals:
void valueChanged(double);
protected:
virtual void mousePressEvent(QMouseEvent*event);
virtual void mouseReleaseEvent(QMouseEvent*event);
};

/*:582*//*598:*/
#line 14125 "./typica.w"

class DeviceTreeModelNode
{
public:
DeviceTreeModelNode(QDomNode&node,int row,
DeviceTreeModelNode*parent= NULL);
~DeviceTreeModelNode();
DeviceTreeModelNode*child(int index);
DeviceTreeModelNode*parent();
QDomNode node()const;
int row();
private:
QDomNode domNode;
QHash<int,DeviceTreeModelNode*> children;
int rowNumber;
DeviceTreeModelNode*parentItem;
};

/*:598*//*600:*/
#line 14200 "./typica.w"

class DeviceTreeModel:public QAbstractItemModel
{
Q_OBJECT
public:
DeviceTreeModel(QObject*parent= NULL);
~DeviceTreeModel();
QVariant data(const QModelIndex&index,int role)const;
Qt::ItemFlags flags(const QModelIndex&index)const;
QVariant headerData(int section,Qt::Orientation orientation,
int role= Qt::DisplayRole)const;
QModelIndex index(int row,int column,
const QModelIndex&parent= QModelIndex())const;
QModelIndex parent(const QModelIndex&child)const;
int rowCount(const QModelIndex&parent= QModelIndex())const;
int columnCount(const QModelIndex&parent= QModelIndex())const;
bool setData(const QModelIndex&index,const QVariant&value,
int role);
bool removeRows(int row,int count,const QModelIndex&parent);
QDomElement referenceElement(const QString&id);
public slots:
void newNode(const QString&name,const QString&driver,
const QModelIndex&parent);
private:
QDomDocument document;
DeviceTreeModelNode*root;
QDomNode referenceSection;
QDomNode treeRoot;
};

/*:600*//*619:*/
#line 14654 "./typica.w"

Q_DECLARE_METATYPE(QModelIndex)

/*:619*//*627:*/
#line 14761 "./typica.w"

class NodeInserter:public QAction
{
Q_OBJECT
public:
NodeInserter(const QString&title,const QString&name,
const QString&driver,QObject*parent= NULL);
signals:
void triggered(QString name,QString driver);
private slots:
void onTriggered();
private:
QString defaultNodeName;
QString driverString;
};

/*:627*//*630:*/
#line 14812 "./typica.w"

class DeviceConfigurationWindow:public QMainWindow
{
Q_OBJECT
public:
DeviceConfigurationWindow();
public slots:
void addDevice();
void removeNode();
void newSelection(const QModelIndex&index);
private:
QDomDocument document;
DeviceTreeModel*model;
QTreeView*view;
QScrollArea*configArea;
};

/*:630*//*638:*/
#line 14956 "./typica.w"

class BasicDeviceConfigurationWidget:public QWidget
{
Q_OBJECT
public:
BasicDeviceConfigurationWidget(DeviceTreeModel*model,
const QModelIndex&index);
public slots:
void insertChildNode(const QString&name,const QString&driver);
void updateAttribute(const QString&name,const QString&value);
protected:
DeviceTreeModel*deviceModel;
QModelIndex currentNode;
};

/*:638*//*642:*/
#line 15041 "./typica.w"

class RoasterConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE RoasterConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateRoasterId(int id);
};

/*:642*//*647:*/
#line 15168 "./typica.w"

class NiDaqMxBaseDriverConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxBaseDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
};

/*:647*//*649:*/
#line 15214 "./typica.w"

class NiDaqMxBase9211ConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxBase9211ConfWidget(DeviceTreeModel*device,
const QModelIndex&index);
private slots:
void addChannel();
void updateDeviceId(const QString&newId);
};

/*:649*//*653:*/
#line 15300 "./typica.w"

class Ni9211TcConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE Ni9211TcConfWidget(DeviceTreeModel*device,
const QModelIndex&index);
private slots:
void updateThermocoupleType(const QString&type);
void updateColumnName(const QString&name);
};

/*:653*//*658:*/
#line 15402 "./typica.w"

class NiDaqMxDriverConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
};

/*:658*//*660:*/
#line 15443 "./typica.w"

class NiDaqMx9211ConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMx9211ConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void addChannel();
void updateDeviceId(const QString&newId);
};

/*:660*//*662:*/
#line 15512 "./typica.w"

class NiDaqMxTc01ConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxTc01ConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateDeviceId(const QString&newId);
void updateThermocoupleType(const QString&type);
void updateColumnName(const QString&name);
};

/*:662*//*667:*/
#line 15629 "./typica.w"

class PortSelector:public QComboBox
{
Q_OBJECT
public:
PortSelector(QWidget*parent= NULL);
private slots:
void addDevice(QextPortInfo port);
private:
QextSerialEnumerator*lister;
};

/*:667*//*669:*/
#line 15673 "./typica.w"

class BaudSelector:public QComboBox
{
Q_OBJECT
Q_ENUMS(BaudRateType)
public:
BaudSelector(QWidget*parent= NULL);
enum BaudRateType
{
#if defined(Q_OS_UNIX) || defined(qdoc)
BAUD50= 50,
BAUD75= 75,
BAUD134= 134,
BAUD150= 150,
BAUD200= 200,
BAUD1800= 1800,
#if defined(B76800) || defined(qdoc)
BAUD76800= 76800,
#endif
#if (defined(B230400) && defined(B4000000)) || defined(qdoc)
BAUD230400= 230400,
BAUD460800= 460800,
BAUD500000= 500000,
BAUD576000= 576000,
BAUD921600= 921600,
BAUD1000000= 1000000,
BAUD1152000= 1152000,
BAUD1500000= 1500000,
BAUD2000000= 2000000,
BAUD2500000= 2500000,
BAUD3000000= 3000000,
BAUD3500000= 3500000,
BAUD4000000= 4000000,
#endif
#endif
#if defined(Q_OS_WIN) || defined(qdoc)
BAUD14400= 14400,
BAUD56000= 56000,
BAUD128000= 128000,
BAUD256000= 256000,
#endif
BAUD110= 110,
BAUD300= 300,
BAUD600= 600,
BAUD1200= 1200,
BAUD2400= 2400,
BAUD4800= 4800,
BAUD9600= 9600,
BAUD19200= 19200,
BAUD38400= 38400,
BAUD57600= 57600,
BAUD115200= 115200
};
};

/*:669*//*671:*/
#line 15744 "./typica.w"

class ParitySelector:public QComboBox
{
Q_OBJECT
Q_ENUMS(ParityType)
public:
ParitySelector(QWidget*parent= NULL);
enum ParityType
{
PAR_NONE,
PAR_ODD,
PAR_EVEN,
#if defined(Q_OS_WIN) || defined(qdoc)
PAR_MARK,
#endif
PAR_SPACE
};
};

/*:671*//*673:*/
#line 15782 "./typica.w"

class FlowSelector:public QComboBox
{
Q_OBJECT
Q_ENUMS(FlowType)
public:
FlowSelector(QWidget*parent= NULL);
enum FlowType
{
FLOW_OFF,
FLOW_HARDWARE,
FLOW_XONXOFF
};
};

/*:673*//*675:*/
#line 15815 "./typica.w"

class StopSelector:public QComboBox
{
Q_OBJECT
Q_ENUMS(StopBitsType)
public:
StopSelector(QWidget*parent= NULL);
enum StopBitsType
{
STOP_1,
#if defined(Q_OS_WIN) || defined(qdoc)
STOP_1_5,
#endif
STOP_2
};
};

/*:675*//*678:*/
#line 15868 "./typica.w"

class ShortHexSpinBox:public QSpinBox
{
Q_OBJECT
public:
ShortHexSpinBox(QWidget*parent= NULL);
virtual QValidator::State validate(QString&input,int&pos)const;
protected:
virtual int valueFromText(const QString&text)const;
virtual QString textFromValue(int value)const;
};

/*:678*//*680:*/
#line 15930 "./typica.w"

class ModbusRtuPortConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusRtuPortConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updatePort(const QString&newPort);
void updateBaudRate(const QString&newRate);
void updateParity(const QString&newParity);
void updateFlowControl(const QString&newFlow);
void updateStopBits(const QString&newStopBits);
};

/*:680*//*682:*/
#line 16081 "./typica.w"

class ModbusRtuDeviceConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusRtuDeviceConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateStationNumber(int newStation);
void updateFixedUnit(bool newFixed);
void updateFixedDecimal(bool newFixed);
void updateUnit(const QString&newUnit);
void updateUnitAddress(int newAddress);
void updateValueF(int newValue);
void updateValueC(int newValue);
void updatePrecisionAddress(int newAddress);
void updatePrecisionValue(int newValue);
private:
QStackedLayout*unitSpecificationLayout;
QStackedLayout*decimalSpecificationLayout;
};

/*:682*//*684:*/
#line 16340 "./typica.w"

class ModbusRtuDeviceTPvConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateAddress(int newAddress);
};

/*:684*//*686:*/
#line 16386 "./typica.w"

class ModbusRtuDeviceTSvConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusRtuDeviceTSvConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateReadAddress(int newAddress);
void updateWriteAddress(int newAddress);
void updateFixedRange(bool fixed);
void updateLower(const QString&lower);
void updateUpper(const QString&upper);
void updateLowerAddress(int newAddress);
void updateUpperAddress(int newAddress);
private:
QStackedLayout*boundsLayout;
};

/*:686*//*690:*/
#line 16580 "./typica.w"

class AnnotationButtonConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE AnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateButtonText(const QString&text);
void updateAnnotationText(const QString&text);
};

/*:690*//*694:*/
#line 16648 "./typica.w"

class ReconfigurableAnnotationButtonConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateButtonText(const QString&text);
void updateAnnotationText(const QString&text);
};

/*:694*//*697:*/
#line 16722 "./typica.w"

class NoteSpinConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NoteSpinConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateLabel(const QString&text);
void updateMinimum(const QString&minimum);
void updateMaximum(const QString&maximum);
void updatePrecision(int precision);
void updatePretext(const QString&text);
void updatePosttext(const QString&text);
};

/*:697*//*700:*/
#line 16843 "./typica.w"

class ModbusRTUDevice:public QObject
{
Q_OBJECT
public:
ModbusRTUDevice(DeviceTreeModel*model,const QModelIndex&index);
~ModbusRTUDevice();
void queueMessage(QByteArray request,QObject*object,const char*callback);
Q_INVOKABLE double SVLower();
Q_INVOKABLE double SVUpper();
Q_INVOKABLE int decimals();
QList<Channel*> channels;
public slots:
void outputSV(double sv);
signals:
void SVLowerChanged(double);
void SVUpperChanged(double);
void SVDecimalChanged(int);
void queueEmpty();
private slots:
void dataAvailable();
void sendNextMessage();
void decimalResponse(QByteArray response);
void unitResponse(QByteArray response);
void svlResponse(QByteArray response);
void svuResponse(QByteArray response);
void requestMeasurement();
void mResponse(QByteArray response);
void ignore(QByteArray response);
private:
QextSerialPort*port;
QByteArray responseBuffer;
QList<QByteArray> messageQueue;
QList<QObject*> retObjQueue;
QList<char*> callbackQueue;
quint16 calculateCRC(QByteArray data);
QTimer*messageDelayTimer;
int delayTime;
char station;
int decimalPosition;
int valueF;
int valueC;
bool unitIsF;
double outputSVLower;
double outputSVUpper;
QByteArray outputSVStub;
QByteArray pvStub;
QByteArray svStub;
QByteArray mStub;
quint16 pvaddress;
quint16 svaddress;
bool svenabled;
bool readingsv;
double savedpv;
bool waiting;
};

/*:700*//*715:*/
#line 17515 "./typica.w"

class ModbusConfigurator:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusConfigurator(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updatePort(const QString&newPort);
void updateBaudRate(const QString&newRate);
void updateParity(const QString&newParity);
void updateFlowControl(const QString&newFlow);
void updateStopBits(const QString&newStopBits);
void updateStation(int station);
void updateFixedDecimal(bool fixed);
void updateDecimalAddress(int address);
void updateDecimalPosition(int position);
void updateFixedUnit(bool fixed);
void updateUnitAddress(int address);
void updateValueForF(int value);
void updateValueForC(int value);
void updateUnit(const QString&newUnit);
void updatePVAddress(int address);
void updateSVEnabled(bool enabled);
void updateSVReadAddress(int address);
void updateDeviceLimit(bool query);
void updateSVLowerAddress(int address);
void updateSVUpperAddress(int address);
void updateSVLower(double value);
void updateSVUpper(double value);
void updateSVWritable(bool canWriteSV);
void updateSVWriteAddress(int address);
void updatePVColumnName(const QString&name);
void updateSVColumnName(const QString&name);
private:
PortSelector*port;
BaudSelector*baud;
ParitySelector*parity;
FlowSelector*flow;
StopSelector*stop;
QSpinBox*station;
QCheckBox*decimalQuery;
ShortHexSpinBox*decimalAddress;
QSpinBox*decimalPosition;
QCheckBox*unitQuery;
ShortHexSpinBox*unitAddress;
QSpinBox*valueF;
QSpinBox*valueC;
QComboBox*fixedUnit;
ShortHexSpinBox*pVAddress;
QCheckBox*sVEnabled;
ShortHexSpinBox*sVReadAddress;
QCheckBox*deviceLimit;
ShortHexSpinBox*sVLowerAddr;
ShortHexSpinBox*sVUpperAddr;
QDoubleSpinBox*sVLower;
QDoubleSpinBox*sVUpper;
QCheckBox*sVWritable;
ShortHexSpinBox*sVOutputAddr;
QLineEdit*pVColumnName;
QLineEdit*sVColumnName;
};

/*:715*//*719:*/
#line 18021 "./typica.w"

class LinearSplineInterpolationConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE LinearSplineInterpolationConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateSourceColumn(const QString&source);
void updateDestinationColumn(const QString&dest);
void updateKnots();
private:
SaltModel*knotmodel;
};

/*:719*//*725:*/
#line 18145 "./typica.w"

class TranslationConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE TranslationConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateMatchingColumn(const QString&column);
void updateTemperature();
private:
QDoubleSpinBox*temperatureValue;
QComboBox*unitSelector;
};

/*:725*/
#line 755 "./typica.w"

/*23:*/
#line 997 "./typica.w"

void setQObjectProperties(QScriptValue value,QScriptEngine*engine);

/*:23*//*25:*/
#line 1012 "./typica.w"

void setQPaintDeviceProperties(QScriptValue value,QScriptEngine*engine);
void setQLayoutItemProperties(QScriptValue value,QScriptEngine*engine);

/*:25*//*27:*/
#line 1037 "./typica.w"

void setQWidgetProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQWidget(QScriptContext*context,QScriptEngine*engine);
QScriptValue QWidget_setLayout(QScriptContext*context,QScriptEngine*engine);
QScriptValue QWidget_activateWindow(QScriptContext*context,
QScriptEngine*engine);

/*:27*//*35:*/
#line 1235 "./typica.w"

QScriptValue constructQMainWindow(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QMainWindow_setCentralWidget(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QMainWindow_menuBar(QScriptContext*context,
QScriptEngine*engine);
void setQMainWindowProperties(QScriptValue value,QScriptEngine*engine);

/*:35*//*40:*/
#line 1334 "./typica.w"

void setQMenuBarProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QMenuBar_addMenu(QScriptContext*context,QScriptEngine*engine);

/*:40*//*43:*/
#line 1379 "./typica.w"

void setQMenuProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QMenu_addAction(QScriptContext*context,QScriptEngine*engine);
QScriptValue QMenu_addSeparator(QScriptContext*context,QScriptEngine*engine);

/*:43*//*46:*/
#line 1445 "./typica.w"

void setQFrameProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQFrame(QScriptContext*context,QScriptEngine*engine);

/*:46*//*49:*/
#line 1478 "./typica.w"

void setQLabelProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQLabel(QScriptContext*context,QScriptEngine*engine);

/*:49*//*52:*/
#line 1519 "./typica.w"

QScriptValue constructQSplitter(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSplitter_addWidget(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_saveState(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_restoreState(QScriptContext*context,
QScriptEngine*engine);
void setQSplitterProperties(QScriptValue value,QScriptEngine*engine);

/*:52*//*57:*/
#line 1638 "./typica.w"

void setQLayoutProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QLayout_addWidget(QScriptContext*context,QScriptEngine*engine);

/*:57*//*59:*/
#line 1693 "./typica.w"

QScriptValue constructQBoxLayout(QScriptContext*context,
QScriptEngine*engine);
void setQBoxLayoutProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QBoxLayout_addLayout(QScriptContext*context,QScriptEngine*engine);
QScriptValue QBoxLayout_addWidget(QScriptContext*context,QScriptEngine*engine);

/*:59*//*63:*/
#line 1806 "./typica.w"

QScriptValue constructQAction(QScriptContext*context,QScriptEngine*engine);
QScriptValue QAction_setShortcut(QScriptContext*context,
QScriptEngine*engine);
void setQActionProperties(QScriptValue value,QScriptEngine*engine);

/*:63*//*66:*/
#line 1862 "./typica.w"

QScriptValue QFileDialog_getOpenFileName(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QFileDialog_getSaveFileName(QScriptContext*context,
QScriptEngine*engine);
void setQFileDialogProperties(QScriptValue value,QScriptEngine*engine);
void setQDialogProperties(QScriptValue value,QScriptEngine*engine);

/*:66*//*71:*/
#line 1973 "./typica.w"

QScriptValue constructQFile(QScriptContext*context,QScriptEngine*engine);
void setQFileProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QFile_remove(QScriptContext*context,QScriptEngine*engine);
void setQIODeviceProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QIODevice_open(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_close(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_readToString(QScriptContext*context,
QScriptEngine*engine);

/*:71*//*78:*/
#line 2095 "./typica.w"

QScriptValue constructQBuffer(QScriptContext*context,QScriptEngine*engine);
void setQBufferProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QBuffer_setData(QScriptContext*context,QScriptEngine*engine);

/*:78*//*81:*/
#line 2140 "./typica.w"

QScriptValue constructXQuery(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_bind(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_exec(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_setQuery(QScriptContext*context,QScriptEngine*engine);
void setXQueryProperties(QScriptValue value,QScriptEngine*engine);

/*:81*//*87:*/
#line 2213 "./typica.w"

QScriptValue constructXmlWriter(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlWriter_setDevice(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeAttribute(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeCDATA(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeCharacters(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeDTD(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlWriter_writeEmptyElement(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeEndDocument(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeEndElement(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeEntityReference(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeProcessingInstruction(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeStartDocument(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeStartElement(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlWriter_writeTextElement(QScriptContext*context,
QScriptEngine*engine);
void setXmlWriterProperties(QScriptValue value,QScriptEngine*engine);

/*:87*//*96:*/
#line 2431 "./typica.w"

QScriptValue constructXmlReader(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlReader_atEnd(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlReader_attribute(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlReader_hasAttribute(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlReader_isDTD(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlReader_isStartElement(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlReader_name(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlReader_readElementText(QScriptContext*context,
QScriptEngine*engine);
QScriptValue XmlReader_readNext(QScriptContext*context,QScriptEngine*engine);
QScriptValue XmlReader_text(QScriptContext*context,QScriptEngine*engine);
void setXmlReaderProperties(QScriptValue value,QScriptEngine*engine);

/*:96*//*103:*/
#line 2566 "./typica.w"

QScriptValue QSettings_value(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSettings_setValue(QScriptContext*context,QScriptEngine*engine);
void setQSettingsProperties(QScriptValue value,QScriptEngine*engine);

/*:103*//*107:*/
#line 2648 "./typica.w"

QScriptValue constructQLCDNumber(QScriptContext*context,
QScriptEngine*engine);
void setQLCDNumberProperties(QScriptValue value,QScriptEngine*engine);

/*:107*//*110:*/
#line 2686 "./typica.w"

QScriptValue constructQTime(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_addMSecs(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_addSecs(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_elapsed(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_hour(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_isNull(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_isValid(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_minute(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_msec(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_msecsTo(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_restart(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_second(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_secsTo(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_setHMS(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_start(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_toString(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_currentTime(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_fromString(QScriptContext*context,QScriptEngine*engine);
QScriptValue QTime_valueOf(QScriptContext*context,QScriptEngine*engine);
void setQTimeProperties(QScriptValue value,QScriptEngine*engine);

/*:110*//*125:*/
#line 3155 "./typica.w"

void setQAbstractScrollAreaProperties(QScriptValue value,
QScriptEngine*engine);

/*:125*//*127:*/
#line 3170 "./typica.w"

void setQAbstractItemViewProperties(QScriptValue value,QScriptEngine*engine);

/*:127*//*129:*/
#line 3183 "./typica.w"

void setQGraphicsViewProperties(QScriptValue value,QScriptEngine*engine);
void setQTableViewProperties(QScriptValue value,QScriptEngine*engine);

/*:129*//*131:*/
#line 3207 "./typica.w"

void setQAbstractButtonProperties(QScriptValue value,QScriptEngine*engine);
void setQPushButtonProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQPushButton(QScriptContext*context,
QScriptEngine*engine);

/*:131*//*138:*/
#line 3306 "./typica.w"

void setQSqlQueryProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQSqlQuery(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSqlQuery_bind(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSqlQuery_bindDeviceData(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSqlQuery_bindFileData(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSqlQuery_exec(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSqlQuery_executedQuery(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSqlQuery_invalidate(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSqlQuery_next(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSqlQuery_prepare(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSqlQuery_value(QScriptContext*context,QScriptEngine*engine);

/*:138*//*145:*/
#line 3476 "./typica.w"

QScriptValue baseName(QScriptContext*context,QScriptEngine*engine);
QScriptValue dir(QScriptContext*context,QScriptEngine*engine);
QScriptValue sqlToArray(QScriptContext*context,QScriptEngine*engine);
QScriptValue setFont(QScriptContext*context,QScriptEngine*engine);
QScriptValue annotationFromRecord(QScriptContext*context,
QScriptEngine*engine);
QScriptValue setTabOrder(QScriptContext*context,QScriptEngine*engine);

/*:145*//*156:*/
#line 3759 "./typica.w"

QScriptValue createWindow(QScriptContext*context,QScriptEngine*engine);
void addLayoutToWidget(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addLayoutToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addSplitterToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addSplitterToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void populateGridLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void populateBoxLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void populateSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void populateWidget(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void populateStackedLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addTemperatureDisplayToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addTemperatureDisplayToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addTimerDisplayToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addTimerDisplayToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addDecorationToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addDecorationToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addWidgetToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addButtonToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addZoomLogToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addGraphToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addSqlDropToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addSaltToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addLineToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addTextToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addSqlQueryViewToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addCalendarToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addSpinBoxToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:156*//*202:*/
#line 5279 "./typica.w"

void setQDateEditProperties(QScriptValue value,QScriptEngine*engine);
void setQDateTimeEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QDateTimeEdit_setDate(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QDateTimeEdit_day(QScriptContext*context,QScriptEngine*engine);
QScriptValue QDateTimeEdit_month(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QDateTimeEdit_year(QScriptContext*context,QScriptEngine*engine);

/*:202*//*203:*/
#line 5294 "./typica.w"

QScriptValue findChildObject(QScriptContext*context,QScriptEngine*engine);

/*:203*//*207:*/
#line 5421 "./typica.w"

void setSaltTableProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue SaltTable_bindableColumnArray(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SaltTable_bindableQuotedColumnArray(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SaltTable_columnSum(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SaltTable_columnArray(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SaltTable_data(QScriptContext*context,QScriptEngine*engine);
QScriptValue SaltTable_model(QScriptContext*context,QScriptEngine*engine);
QScriptValue SaltTable_quotedColumnArray(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SaltTable_setData(QScriptContext*context,QScriptEngine*engine);

/*:207*//*214:*/
#line 5591 "./typica.w"

void setSqlComboBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQComboBoxProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QComboBox_currentData(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QComboBox_addItem(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_setModel(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_findText(QScriptContext*context,QScriptEngine*engine);

/*:214*//*242:*/
#line 6467 "./typica.w"

QScriptValue constructDAQ(QScriptContext*context,QScriptEngine*engine);
QScriptValue DAQ_newChannel(QScriptContext*context,QScriptEngine*engine);
void setDAQProperties(QScriptValue value,QScriptEngine*engine);

/*:242*//*251:*/
#line 6665 "./typica.w"

QScriptValue constructFakeDAQ(QScriptContext*context,QScriptEngine*engine);
QScriptValue FakeDAQ_newChannel(QScriptContext*context,QScriptEngine*engine);
void setFakeDAQProperties(QScriptValue value,QScriptEngine*engine);

/*:251*//*256:*/
#line 6766 "./typica.w"

void setChannelProperties(QScriptValue value,QScriptEngine*engine);

/*:256*//*262:*/
#line 6942 "./typica.w"

QScriptValue constructLinearCalibrator(QScriptContext*context,
QScriptEngine*engine);
void setLinearCalibratorProperties(QScriptValue value,QScriptEngine*engine);

/*:262*//*267:*/
#line 7081 "./typica.w"

QScriptValue constructLinearSplineInterpolator(QScriptContext*context,QScriptEngine*engine);
void setLinearSplineInterpolatorProperties(QScriptValue value,QScriptEngine*engine);

/*:267*//*276:*/
#line 7263 "./typica.w"

QScriptValue constructTemperatureDisplay(QScriptContext*context,
QScriptEngine*engine);
void setTemperatureDisplayProperties(QScriptValue value,QScriptEngine*engine);

/*:276*//*283:*/
#line 7400 "./typica.w"

QScriptValue constructMeasurementTimeOffset(QScriptContext*context,
QScriptEngine*engine);
void setMeasurementTimeOffsetProperties(QScriptValue value,
QScriptEngine*engine);

/*:283*//*288:*/
#line 7513 "./typica.w"

QScriptValue constructThresholdDetector(QScriptContext*context,QScriptEngine*engine);
void setThresholdDetectorProperties(QScriptValue value,QScriptEngine*engine);

/*:288*//*293:*/
#line 7610 "./typica.w"

QScriptValue constructZeroEmitter(QScriptContext*context,
QScriptEngine*engine);
void setZeroEmitterProperties(QScriptValue value,QScriptEngine*engine);

/*:293*//*298:*/
#line 7689 "./typica.w"

QScriptValue constructMeasurementAdapter(QScriptContext*context,
QScriptEngine*engine);
void setMeasurementAdapterProperties(QScriptValue value,QScriptEngine*engine);

/*:298*//*313:*/
#line 8039 "./typica.w"

void setGraphViewProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructGraphView(QScriptContext*context,QScriptEngine*engine);

/*:313*//*335:*/
#line 8602 "./typica.w"

void setZoomLogProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructZoomLog(QScriptContext*context,QScriptEngine*engine);
QScriptValue ZoomLog_saveXML(QScriptContext*context,QScriptEngine*engine);
QScriptValue ZoomLog_saveCSV(QScriptContext*context,QScriptEngine*engine);
QScriptValue ZoomLog_saveState(QScriptContext*context,QScriptEngine*engine);
QScriptValue ZoomLog_restoreState(QScriptContext*context,
QScriptEngine*engine);
QScriptValue ZoomLog_lastTime(QScriptContext*context,QScriptEngine*engine);
QScriptValue ZoomLog_saveTemporary(QScriptContext*context,
QScriptEngine*engnie);

/*:335*//*372:*/
#line 9527 "./typica.w"

QScriptValue constructAnnotationButton(QScriptContext*context,
QScriptEngine*engine);
void setAnnotationButtonProperties(QScriptValue value,QScriptEngine*engine);

/*:372*//*380:*/
#line 9667 "./typica.w"

QScriptValue constructAnnotationSpinBox(QScriptContext*context,
QScriptEngine*engine);
void setAnnotationSpinBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQDoubleSpinBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQAbstractSpinBoxProperties(QScriptValue value,QScriptEngine*engine);

/*:380*//*401:*/
#line 10090 "./typica.w"

QScriptValue constructTimerDisplay(QScriptContext*context,
QScriptEngine*engine);
void setTimerDisplayProperties(QScriptValue value,QScriptEngine*engine);

/*:401*//*428:*/
#line 10584 "./typica.w"

void setWidgetDecoratorProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructWidgetDecorator(QScriptContext*context,
QScriptEngine*engine);

/*:428*//*441:*/
#line 10867 "./typica.w"

QScriptValue constructLogEditWindow(QScriptContext*context,
QScriptEngine*engine);

/*:441*//*460:*/
#line 11341 "./typica.w"

QScriptValue constructXMLInput(QScriptContext*context,QScriptEngine*engine);
QScriptValue XMLInput_input(QScriptContext*context,QScriptEngine*engine);

/*:460*//*476:*/
#line 11624 "./typica.w"

QScriptValue constructWebView(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_load(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_print(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_setContent(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_setHtml(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_saveXml(QScriptContext*context,QScriptEngine*);
void addWebViewToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void setQWebViewProperties(QScriptValue value,QScriptEngine*engine);

/*:476*//*531:*/
#line 12640 "./typica.w"

void setSqlQueryViewProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructSqlQueryView(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SqlQueryView_setQuery(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SqlQueryView_setHeaderData(QScriptContext*context,
QScriptEngine*engine);

/*:531*//*541:*/
#line 12869 "./typica.w"

void addReportToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:541*//*557:*/
#line 13153 "./typica.w"

void setQTextEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QTextEdit_print(QScriptContext*context,QScriptEngine*engine);

/*:557*//*567:*/
#line 13348 "./typica.w"

void addFormArrayToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:567*//*588:*/
#line 13932 "./typica.w"

void addScaleControlToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addIntensityControlToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:588*//*614:*/
#line 14518 "./typica.w"

QScriptValue constructDeviceTreeModel(QScriptContext*context,
QScriptEngine*engine);
void setDeviceTreeModelProperties(QScriptValue value,QScriptEngine*engine);
void setQAbstractItemModelProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue DeviceTreeModel_referenceElement(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QAbstractItemModel_data(QScriptContext*context,QScriptEngine*engine);
QScriptValue QAbstractItemModel_index(QScriptContext*context,QScriptEngine*engine);
QScriptValue QAbstractItemModel_rowCount(QScriptContext*context,QScriptEngine*engine);
QScriptValue QAbstractItemModel_hasChildren(QScriptContext*context,QScriptEngine*engine);

/*:614*//*620:*/
#line 14660 "./typica.w"

QScriptValue QModelIndex_toScriptValue(QScriptEngine*engine,const QModelIndex&index);
void QModelIndex_fromScriptValue(const QScriptValue&value,QModelIndex&index);

/*:620*//*635:*/
#line 14928 "./typica.w"

QScriptValue constructDeviceConfigurationWindow(QScriptContext*context,
QScriptEngine*engine);

/*:635*//*710:*/
#line 17422 "./typica.w"

QScriptValue constructModbusRTUDevice(QScriptContext*context,QScriptEngine*engine);
QScriptValue ModbusRTUDevice_pVChannel(QScriptContext*context,QScriptEngine*engine);
QScriptValue ModbusRTUDevice_sVChannel(QScriptContext*context,QScriptEngine*engine);
void setModbusRTUDeviceProperties(QScriptValue value,QScriptEngine*engine);

/*:710*/
#line 756 "./typica.w"

/*16:*/
#line 764 "./typica.w"

/*628:*/
#line 14781 "./typica.w"

NodeInserter::NodeInserter(const QString&title,const QString&name,
const QString&driver,QObject*parent):
QAction(title,parent),defaultNodeName(name),driverString(driver)
{
connect(this,SIGNAL(triggered()),this,SLOT(onTriggered()));
}

void NodeInserter::onTriggered()
{
emit triggered(defaultNodeName,driverString);
}

/*:628*/
#line 765 "./typica.w"

/*217:*/
#line 5704 "./typica.w"

Measurement::Measurement(double temperature,QTime time,
TemperatureUnits sc):
theTemperature(temperature),theTime(time),unit(sc)
{

}

Measurement::Measurement(double temperature):
theTemperature(temperature),theTime(QTime::currentTime()),
unit(Fahrenheit)
{

}

/*:217*//*219:*/
#line 5732 "./typica.w"

Measurement::Measurement(const Measurement&x):
theTemperature(x.temperature()),theTime(x.time()),
unit(x.unit)
{

}

Measurement::~Measurement()
{

}

/*:219*//*220:*/
#line 5748 "./typica.w"

Measurement&Measurement::operator= (Measurement&x)
{
theTemperature= x.temperature();
theTime= x.time();
unit= x.unit;
return*this;
}

/*:220*//*221:*/
#line 5762 "./typica.w"

double Measurement::temperature()const
{
return theTemperature;
}

QTime Measurement::time()const
{
return theTime;
}

void Measurement::setTemperature(double temperature)
{
theTemperature= temperature;
}

void Measurement::setTime(QTime time)
{
theTime= time;
}

/*:221*//*222:*/
#line 5788 "./typica.w"

void Measurement::setUnit(TemperatureUnits scale)
{
unit= scale;
}

Measurement::TemperatureUnits Measurement::scale()
{
return unit;
}

/*:222*//*223:*/
#line 5808 "./typica.w"

Measurement Measurement::toFahrenheit()
{
switch(unit)
{
case Celsius:
return Measurement(this->temperature()*9/5+32,this->time(),
Fahrenheit);
break;
case Kelvin:
return Measurement(this->temperature()*5/9-459.67,
this->time(),Fahrenheit);
break;
case Rankine:
return Measurement(this->temperature()-459.67,this->time(),
Fahrenheit);
break;
default:
return Measurement(this->temperature(),this->time(),Fahrenheit);
break;
}
}

/*:223*//*224:*/
#line 5833 "./typica.w"

Measurement Measurement::toCelsius()
{
switch(unit)
{
case Fahrenheit:
return Measurement((this->temperature()-32)*5/9,this->time(),
Celsius);
break;
case Kelvin:
return Measurement(this->temperature()-273.15,this->time(),
Celsius);
break;
case Rankine:
return Measurement((this->temperature()-491.67)*5/9,
this->time(),Celsius);
break;
default:
return Measurement(this->temperature(),this->time(),Celsius);
break;
}
}

/*:224*//*225:*/
#line 5859 "./typica.w"

Measurement Measurement::toKelvin()
{
switch(unit)
{
case Fahrenheit:
return Measurement((this->temperature()+459.67)*5/9,
this->time(),Kelvin);
break;
case Celsius:
return Measurement(this->temperature()+273.15,this->time(),
Kelvin);
break;
case Rankine:
return Measurement(this->temperature()*5/9,this->time(),
Kelvin);
break;
default:
return Measurement(this->temperature(),this->time(),Kelvin);
break;
}
}

/*:225*//*226:*/
#line 5884 "./typica.w"

Measurement Measurement::toRankine()
{
switch(unit)
{
case Fahrenheit:
return Measurement(this->temperature()+459.67,this->time(),
Rankine);
break;
case Celsius:
return Measurement((this->temperature()+273.15)*9/5,
this->time(),Rankine);
break;
case Kelvin:
return Measurement(this->temperature()*9/5,this->time(),
Rankine);
break;
default:
return Measurement(this->temperature(),this->time(),Rankine);
break;
}
}

/*:226*/
#line 766 "./typica.w"

/*232:*/
#line 6073 "./typica.w"

void DAQImplementation::measure()
{
int samplesRead= 0;
double buffer[channels];
error= read((unsigned int)(handle),(signed long)(1),(double)(10.0),
(unsigned long)(0),buffer,(unsigned long)(channels),
&samplesRead,(signed long)(0));
if(error)
{
ready= false;
}
else
{
if(samplesRead)
{
QTime time= QTime::currentTime();
for(int i= 0;i<samplesRead;i++)
{
for(int j= 0;j<channels;j++)
{
Measurement measure(buffer[j+(i*channels)],time,
unitMap[j]);
channelMap[j]->input(measure);
}
}
}
}
}

/*:232*//*233:*/
#line 6115 "./typica.w"

void DAQImplementation::run()
{
setPriority(QThread::TimeCriticalPriority);
while(ready)
{
measure();
}
}

/*:233*//*234:*/
#line 6131 "./typica.w"

void DAQ::threadFinished()
{
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6136 "./typica.w"

}
}

/*:234*//*236:*/
#line 6207 "./typica.w"

void DAQ::start()
{
if(imp->ready)
{
imp->error= imp->startTask(imp->handle);
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6215 "./typica.w"

}
else
{
connect(imp,SIGNAL(finished()),this,SLOT(threadFinished()));
imp->start();
}
}
}

void DAQ::stop()
{
if(imp->useBase)
{
imp->ready= false;
imp->wait(ULONG_MAX);
imp->stopTask(imp->handle);
}
else
{
imp->ready= false;
imp->error= imp->stopTask(imp->handle);
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6239 "./typica.w"

}
imp->error= imp->clearTask(imp->handle);
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6244 "./typica.w"

}
}
}

/*:236*//*237:*/
#line 6254 "./typica.w"

DAQ::DAQ(QString device,const QString&driver):imp(new DAQImplementation(driver))
{
imp->device= device;
imp->error= imp->createTask(device.toAscii().data(),&(imp->handle));
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6261 "./typica.w"

}
else
{
imp->ready= true;
}
}

/*:237*//*238:*/
#line 6275 "./typica.w"

Channel*DAQ::newChannel(int units,int thermocouple)
{
Channel*retval= new Channel();
imp->channelMap[imp->channels]= retval;
imp->unitMap[imp->channels]= (Measurement::TemperatureUnits)units;
imp->channels++;
if(imp->ready)
{
if(imp->useBase)
{
imp->error= imp->createChannel(imp->handle,
QString("%1/ai%2").arg(imp->device).
arg(imp->channels-1).
toAscii().data(),
"",(double)(-1.0),(double)(100.0),
(signed long)(units),
(signed long)(thermocouple),
(signed long)(10200),(double)(0),
"");
}
else
{
imp->error= imp->createChannel(imp->handle,
QString("%1/ai%2").arg(imp->device).
arg(imp->channels-1).
toAscii().data(),
"",(double)(50.0),(double)(500.0),
(signed long)(units),
(signed long)(thermocouple),
(signed long)(10200),(double)(0),
"");
}
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6310 "./typica.w"

}
}
return retval;
}

/*:238*//*239:*/
#line 6324 "./typica.w"

void DAQ::setClockRate(double Hz)
{
if(imp->ready)
{
imp->error= imp->setClock(imp->handle,"OnboardClock",Hz,
(signed long)(10280),(signed long)(10123),
(unsigned long long)(1));
if(imp->error)
{
/*235:*/
#line 6182 "./typica.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes= imp->errorInfo(NULL,0);
char string[bytes];
imp->errorInfo(string,bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:235*/
#line 6334 "./typica.w"

}
}
}

/*:239*//*240:*/
#line 6344 "./typica.w"

DAQ::~DAQ()
{
if(imp->useBase)
{
imp->resetDevice(imp->device.toAscii().data());
imp->clearTask(imp->handle);
}
else
{
if(imp->ready)
{
imp->ready= false;
imp->wait(ULONG_MAX);
imp->stopTask(imp->handle);
imp->resetDevice(imp->device.toAscii().data());
imp->clearTask(imp->handle);
}
}
delete imp;
}

/*:240*//*241:*/
#line 6375 "./typica.w"

DAQImplementation::DAQImplementation(const QString&driverinfo)
:QThread(NULL),channelMap(4),handle(0),error(0),channels(0),ready(false),
unitMap(4)
{
if(driverinfo=="nidaqmxbase")
{
useBase= true;
}
else
{
useBase= false;
}
if(useBase)
{
driver.setFileName("nidaqmxbase.framework/nidaqmxbase");
if(!driver.load())
{
driver.setFileName("nidaqmxbase");
if(!driver.load())
{
QMessageBox::critical(NULL,tr("Typica: Driver not found"),
tr("Failed to find nidaqmxbase. Please install it."));
QApplication::quit();
}
}
}
else
{
driver.setFileName("nicaiu");
if(!driver.load())
{
QMessageBox::critical(NULL,tr("Typica: Driver not found"),
tr("Failed to find nidaqmx. Please install it."));
QApplication::quit();
}
}
if(useBase)
{
if((createTask= (daqfp)driver.resolve("DAQmxBaseCreateTask"))==0||
(startTask= (daqfp)driver.resolve("DAQmxBaseStartTask"))==0||
(stopTask= (daqfp)driver.resolve("DAQmxBaseStopTask"))==0||
(clearTask= (daqfp)driver.resolve("DAQmxBaseClearTask"))==0||
(createChannel= (daqfp)driver.resolve("DAQmxBaseCreateAIThrmcplChan"))
==0||
(setClock= (daqfp)driver.resolve("DAQmxBaseCfgSampClkTiming"))==
0||
(read= (daqfp)driver.resolve("DAQmxBaseReadAnalogF64"))==0||
(errorInfo= (daqfp)driver.resolve("DAQmxBaseGetExtendedErrorInfo"))==
0||
(resetDevice= (daqfp)driver.resolve("DAQmxBaseResetDevice"))==0)
{
waitForMeasurement= NULL;
QMessageBox::critical(NULL,tr("Typica: Link error"),
tr("Failed to link a required symbol in NI-DAQmxBase."));
QApplication::quit();
}
}
else
{
if((createTask= (daqfp)driver.resolve("DAQmxCreateTask"))==0||
(startTask= (daqfp)driver.resolve("DAQmxStartTask"))==0||
(stopTask= (daqfp)driver.resolve("DAQmxStopTask"))==0||
(clearTask= (daqfp)driver.resolve("DAQmxClearTask"))==0||
(createChannel= (daqfp)driver.resolve("DAQmxCreateAIThrmcplChan"))
==0||
(setClock= (daqfp)driver.resolve("DAQmxCfgSampClkTiming"))==0||
(read= (daqfp)driver.resolve("DAQmxReadAnalogF64"))==0||
(errorInfo= (daqfp)driver.resolve("DAQmxGetExtendedErrorInfo"))==
0||
(resetDevice= (daqfp)driver.resolve("DAQmxResetDevice"))==0||
(waitForMeasurement= (daqfp)driver.resolve("DAQmxWaitUntilTaskDone"))==0)
{
QMessageBox::critical(NULL,tr("Typica: Link error"),
tr("Failed to link a required symbol in NI-DAQmx."));
QApplication::quit();
}
}
}

DAQImplementation::~DAQImplementation()
{
driver.unload();
}

/*:241*/
#line 767 "./typica.w"

/*248:*/
#line 6577 "./typica.w"

void FakeDAQImplementation::measure()
{
msleep((int)(1000/clockRate));
QTime time= QTime::currentTime();
for(int i= 0;i<channels;i++)
{
Measurement measure(qrand()%500,time);
channelMap[i]->input(measure);
}
}

/*:248*//*249:*/
#line 6591 "./typica.w"

void FakeDAQImplementation::run()
{
setPriority(QThread::TimeCriticalPriority);
while(ready)
{
measure();
}
}

FakeDAQImplementation::FakeDAQImplementation():QThread(NULL),channelMap(4),
channels(0),ready(false),clockRate(1)
{

}

FakeDAQImplementation::~FakeDAQImplementation()
{

}

/*:249*//*250:*/
#line 6616 "./typica.w"

void FakeDAQ::start()
{
if(imp->ready)
{
imp->start();
}
}

FakeDAQ::FakeDAQ(QString):imp(new FakeDAQImplementation())
{
imp->ready= true;
}

Channel*FakeDAQ::newChannel(int,int)
{
Channel*retval;
if(imp->ready)
{
retval= new Channel();
imp->channelMap[imp->channels]= retval;
imp->channels++;
}
else
{
return NULL;
}
return retval;
}

void FakeDAQ::setClockRate(double Hz)
{
if(imp->ready)
{
imp->clockRate= Hz;
}
}

FakeDAQ::~FakeDAQ()
{
imp->ready= false;
imp->wait(ULONG_MAX);
delete imp;
}

/*:250*/
#line 768 "./typica.w"

/*255:*/
#line 6747 "./typica.w"

Channel::Channel():QObject(NULL)
{

}

Channel::~Channel()
{

}

void Channel::input(Measurement measurement)
{
emit newData(measurement);
}

/*:255*/
#line 769 "./typica.w"

/*271:*/
#line 7158 "./typica.w"

void TemperatureDisplay::setValue(Measurement temperature)
{
QString number;
switch(unit)
{
case Auto:
switch(temperature.scale())
{
case Fahrenheit:
display(QString("%1'F").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Celsius:
display(QString("%1'C").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Kelvin:
display(QString("%1").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Rankine:
display(QString("%1'r").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
}
break;
case Fahrenheit:
display(QString("%1'F").
arg(number.setNum(temperature.toFahrenheit().temperature(),'f',
2)));
break;
case Celsius:
display(QString("%1'C").
arg(number.setNum(temperature.toCelsius().temperature(),'f',
2)));
break;
case Kelvin:
display(QString("%1").
arg(number.setNum(temperature.toKelvin().temperature(),'f',
2)));
break;
case Rankine:
display(QString("%1'r").
arg(number.setNum(temperature.toRankine().temperature(),'f',
2)));
break;
}
}

/*:271*//*272:*/
#line 7218 "./typica.w"

TemperatureDisplay::TemperatureDisplay(QWidget*parent):
QLCDNumber(8,parent),unit(Auto)
{
setSegmentStyle(Filled);
display("---.--'F");
}

/*:272*//*273:*/
#line 7234 "./typica.w"

void TemperatureDisplay::invalidate()
{
display("---.--'F");
}

/*:273*//*274:*/
#line 7246 "./typica.w"

void TemperatureDisplay::setDisplayUnits(DisplayUnits scale)
{
unit= scale;
}

/*:274*//*275:*/
#line 7254 "./typica.w"

TemperatureDisplay::~TemperatureDisplay()
{

}

/*:275*/
#line 770 "./typica.w"

/*280:*/
#line 7334 "./typica.w"

void MeasurementTimeOffset::newMeasurement(Measurement measure)
{
if(measure.time()<epoch)
{
if(hasPrevious)
{
QTime jitBase(epoch.hour()-1,epoch.minute(),epoch.second(),
epoch.msec());
QTime jitComp(epoch.hour(),measure.time().minute(),
measure.time().second(),measure.time().msec());
int relTime= jitBase.msecsTo(jitComp);
/*281:*/
#line 7367 "./typica.w"

QTime newTime(0,0,0,0);
newTime= newTime.addMSecs(relTime);
if(newTime.hour()> 0)
{
newTime.setHMS(0,newTime.minute(),newTime.second(),newTime.msec());
}
Measurement rel(measure.temperature(),newTime);
emit measurement(rel);

/*:281*/
#line 7346 "./typica.w"

}
else
{
Measurement rel(measure.temperature(),QTime(0,0,0,0));
emit measurement(rel);
}
}
else
{
int relTime= epoch.msecsTo(measure.time());
/*281:*/
#line 7367 "./typica.w"

QTime newTime(0,0,0,0);
newTime= newTime.addMSecs(relTime);
if(newTime.hour()> 0)
{
newTime.setHMS(0,newTime.minute(),newTime.second(),newTime.msec());
}
Measurement rel(measure.temperature(),newTime);
emit measurement(rel);

/*:281*/
#line 7357 "./typica.w"

}
hasPrevious= true;
previous= measure.time();
}

/*:280*//*282:*/
#line 7379 "./typica.w"

MeasurementTimeOffset::MeasurementTimeOffset(QTime zero):epoch(zero),
previous(0,0,0,0),hasPrevious(false)
{

}

QTime MeasurementTimeOffset::zeroTime()
{
return epoch;
}

void MeasurementTimeOffset::setZeroTime(QTime zero)
{
epoch= zero;
hasPrevious= false;
}

/*:282*/
#line 771 "./typica.w"

/*292:*/
#line 7576 "./typica.w"

ZeroEmitter::ZeroEmitter(int tempcolumn):QObject(NULL),col(tempcolumn),
temp(0)
{

}

int ZeroEmitter::column()
{
return col;
}

double ZeroEmitter::lastTemperature()
{
return temp;
}

void ZeroEmitter::newMeasurement(Measurement measure)
{
temp= measure.temperature();
}

void ZeroEmitter::setColumn(int column)
{
col= column;
}

void ZeroEmitter::emitZero()
{
emit measurement(Measurement(temp,QTime(0,0,0,0)),col);
}

/*:292*/
#line 772 "./typica.w"

/*297:*/
#line 7666 "./typica.w"

MeasurementAdapter::MeasurementAdapter(int tempcolumn):col(tempcolumn)
{

}

int MeasurementAdapter::column()
{
return col;
}

void MeasurementAdapter::newMeasurement(Measurement measure)
{
emit measurement(measure,col);
}

void MeasurementAdapter::setColumn(int column)
{
col= column;
}

/*:297*/
#line 773 "./typica.w"

/*302:*/
#line 7782 "./typica.w"

GraphView::GraphView(QWidget*parent):QGraphicsView(parent),
theScene(new QGraphicsScene),
graphLines(new QMap<int,QList<QGraphicsLineItem*> *> ),
prevPoints(new QMap<int,QPointF> ),
translations(new QMap<int,double> ),
gridLinesF(new QList<QGraphicsItem*> ),
gridLinesC(new QList<QGraphicsItem*> )
{
setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setScene(theScene);
setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
/*303:*/
#line 7810 "./typica.w"

QGraphicsLineItem*tempaxis= new QGraphicsLineItem;
tempaxis->setLine(-10,-500,-10,0);
theScene->addItem(tempaxis);
QGraphicsLineItem*gridLine;
QGraphicsTextItem*label;
for(int y= -100;y> -600;y-= 100)
{
gridLine= new QGraphicsLineItem;
gridLine->setLine(0,y,1200,y);
theScene->addItem(gridLine);
label= new QGraphicsTextItem;
label->setHtml(QString("%1&deg;F").arg(-y));
label->setPos(-55,y-(label->boundingRect().height()/2));
theScene->addItem(label);
gridLinesF->append(gridLine);
gridLinesF->append(label);
}
for(int degC= 50;degC<=250;degC+= 50)
{
gridLine= new QGraphicsLineItem;
int y= -(degC*(9.0/5.0)+32);
gridLine->setLine(0,y,1200,y);
gridLine->hide();
theScene->addItem(gridLine);
gridLinesC->append(gridLine);
label= new QGraphicsTextItem;
label->setHtml(QString("%1&deg;C").arg(degC));
label->setPos(-55,y-(label->boundingRect().height()/2));
label->hide();
theScene->addItem(label);
gridLinesC->append(label);
}

/*:303*/
#line 7795 "./typica.w"
;
/*305:*/
#line 7876 "./typica.w"

QGraphicsLineItem*timeaxis= new QGraphicsLineItem;
timeaxis->setLine(0,10,1200,10);
theScene->addItem(timeaxis);
for(int x= 0;x<1201;x+= 120)
{
QGraphicsLineItem*tick= new QGraphicsLineItem;
tick->setLine(x,0,x,20);
theScene->addItem(tick);
QGraphicsTextItem*label= new QGraphicsTextItem;
label->setPlainText(QString("%1").arg(x/60));
label->setPos(x-(label->boundingRect().width()/2),20);
theScene->addItem(label);
}

/*:305*/
#line 7796 "./typica.w"
;
fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

/*:302*//*304:*/
#line 7846 "./typica.w"

void GraphView::showF()
{
for(int i= 0;i<gridLinesF->size();i++)
{
gridLinesF->at(i)->show();
}
for(int i= 0;i<gridLinesC->size();i++)
{
gridLinesC->at(i)->hide();
}
}

void GraphView::showC()
{
for(int i= 0;i<gridLinesF->size();i++)
{
gridLinesF->at(i)->hide();
}
for(int i= 0;i<gridLinesC->size();i++)
{
gridLinesC->at(i)->show();
}
}

/*:304*//*306:*/
#line 7895 "./typica.w"

void GraphView::resizeEvent(QResizeEvent*)
{
fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

/*:306*//*307:*/
#line 7906 "./typica.w"

void GraphView::newMeasurement(Measurement measure,int tempcolumn)
{
double offset= 0;
if(translations->contains(tempcolumn))
{
offset= translations->value(tempcolumn);
}
if(prevPoints->contains(tempcolumn))
{
/*309:*/
#line 7965 "./typica.w"

QGraphicsLineItem*segment= new QGraphicsLineItem;
QPointF nextPoint(FULLTIMETOINT(measure.time())/1000,measure.temperature());
segment->setLine(prevPoints->value(tempcolumn).x()+offset,
-(prevPoints->value(tempcolumn).y()),
nextPoint.x()+offset,-(nextPoint.y()));
static QColor p[12]= {Qt::yellow,Qt::blue,Qt::cyan,Qt::red,Qt::magenta,
Qt::green,Qt::darkGreen,Qt::darkMagenta,
Qt::darkRed,Qt::darkCyan,Qt::darkBlue,
Qt::darkYellow};
segment->setPen(p[tempcolumn%12]);
theScene->addItem(segment);
prevPoints->insert(tempcolumn,nextPoint);

/*:309*/
#line 7916 "./typica.w"

if(graphLines->contains(tempcolumn))
{

graphLines->value(tempcolumn)->append(segment);
}
else
{

QList<QGraphicsLineItem*> *newLine= 
new QList<QGraphicsLineItem*> ;
newLine->append(segment);
graphLines->insert(tempcolumn,newLine);
}
}
else
{
/*308:*/
#line 7954 "./typica.w"

int x= FULLTIMETOINT(measure.time())/1000;
prevPoints->insert(tempcolumn,QPointF(x,measure.temperature()));

/*:308*/
#line 7933 "./typica.w"

}
}

/*:307*//*310:*/
#line 7982 "./typica.w"

void GraphView::clear()
{
int i;
foreach(i,prevPoints->keys())
{
removeSeries(i);
}
translations->clear();
}

/*:310*//*311:*/
#line 7996 "./typica.w"

void GraphView::removeSeries(int column)
{
if(graphLines->contains(column))
{
QList<QGraphicsLineItem*> *series= graphLines->value(column);
QGraphicsLineItem*segment;
foreach(segment,*series)
{
theScene->removeItem(segment);
}
qDeleteAll(*series);
}
graphLines->remove(column);
prevPoints->remove(column);
}

/*:311*//*312:*/
#line 8015 "./typica.w"

void GraphView::setSeriesTranslation(int column,double offset)
{
if(graphLines->contains(column))
{
QList<QGraphicsLineItem*> *series= graphLines->value(column);
QGraphicsLineItem*segment;
foreach(segment,*series)
{
segment->setPos(segment->pos().x()+offset,segment->pos().y());
}
}
if(translations->contains(column))
{
translations->insert(column,offset+translations->value(column));
}
else
{
translations->insert(column,offset);
}
}

/*:312*/
#line 774 "./typica.w"

/*318:*/
#line 8165 "./typica.w"

void ZoomLog::newMeasurement(Measurement measure,int tempcolumn)
{
model_ms->newMeasurement(measure,tempcolumn);
if(lastMeasurement.contains(tempcolumn))
{
if(measure.time().second()!=
lastMeasurement.value(tempcolumn).time().second())
{
Measurement adjusted(measure.temperature(),
QTime(0,measure.time().minute(),
measure.time().second(),0));
model_1s->newMeasurement(adjusted,tempcolumn);
if(adjusted.time().second()%5==0)
{
model_5s->newMeasurement(adjusted,tempcolumn);
if(adjusted.time().second()%10==0)
{
model_10s->newMeasurement(adjusted,tempcolumn);
}
if(adjusted.time().second()%15==0)
{
model_15s->newMeasurement(adjusted,tempcolumn);
if(adjusted.time().second()%30==0)
{
model_30s->newMeasurement(adjusted,tempcolumn);
if(adjusted.time().second()==0)
{
model_1m->newMeasurement(adjusted,tempcolumn);
}
}
}
}
}
/*321:*/
#line 8243 "./typica.w"

if(currentColumnSet.contains(tempcolumn))
{
int replicationcolumn;
foreach(replicationcolumn,currentColumnSet)
{
if(replicationcolumn!=tempcolumn)
{
if(lastMeasurement.contains(replicationcolumn))
{
if(measure.time()> lastMeasurement.value(replicationcolumn).time())
{
Measurement synthetic(lastMeasurement.value(replicationcolumn).temperature(),
measure.time());
model_ms->newMeasurement(synthetic,replicationcolumn);
if(synthetic.time().second()!=lastMeasurement.value(replicationcolumn).time().second())
{
Measurement adjusted(synthetic.temperature(),QTime(0,synthetic.time().minute(),synthetic.time().second(),0));
model_1s->newMeasurement(adjusted,replicationcolumn);
if(adjusted.time().second()%5==0)
{
model_5s->newMeasurement(adjusted,replicationcolumn);
if(adjusted.time().second()%10==0)
{
model_10s->newMeasurement(adjusted,replicationcolumn);
}
if(adjusted.time().second()%15==0)
{
model_15s->newMeasurement(adjusted,replicationcolumn);
if(adjusted.time().second()%30==0)
{
model_30s->newMeasurement(adjusted,replicationcolumn);
if(adjusted.time().second()==0)
{
model_1m->newMeasurement(adjusted,replicationcolumn);
}
}
}
}
}
lastMeasurement[replicationcolumn]= synthetic;
}
}
}
}
}

/*:321*/
#line 8199 "./typica.w"

}
else
{
/*319:*/
#line 8211 "./typica.w"

MeasurementModel*m;
foreach(m,modelSet)
{
m->newMeasurement(measure,tempcolumn);
}

/*:319*/
#line 8203 "./typica.w"

}
lastMeasurement[tempcolumn]= measure;
}

/*:318*//*320:*/
#line 8229 "./typica.w"

void ZoomLog::addToCurrentColumnSet(int column)
{
currentColumnSet.append(column);
}

void ZoomLog::clearCurrentColumnSet()
{
currentColumnSet.clear();
}

/*:320*//*322:*/
#line 8312 "./typica.w"

void ZoomLog::newAnnotation(QString annotation,int tempcolumn,
int annotationcolumn)
{
model_ms->newAnnotation(annotation,tempcolumn,annotationcolumn);
MeasurementModel*m;
if(lastMeasurement.contains(tempcolumn))
{
foreach(m,modelSet)
{
m->newMeasurement(lastMeasurement.value(tempcolumn),tempcolumn);
}
}
foreach(m,modelSet)
{
m->newAnnotation(annotation,tempcolumn,annotationcolumn);
}
}

/*:322*//*323:*/
#line 8336 "./typica.w"

void ZoomLog::centerOn(int row)
{
scrollTo(currentModel->index(row,0),QAbstractItemView::PositionAtCenter);
}

/*:323*//*324:*/
#line 8346 "./typica.w"

void ZoomLog::clear()
{
MeasurementModel*m;
foreach(m,modelSet)
{
m->clear();
}
lastMeasurement.clear();
saveTempCols.clear();
saveNoteCols.clear();
}

/*:324*//*325:*/
#line 8363 "./typica.w"

QVariant ZoomLog::data(int row,int column)const
{
return model_ms->data(model_ms->index(row,column,QModelIndex()),
Qt::DisplayRole);
}

int ZoomLog::rowCount()
{
return model_ms->rowCount();
}

/*:325*//*326:*/
#line 8386 "./typica.w"

bool ZoomLog::saveXML(QIODevice*device)
{
int prevUnits= model_ms->displayUnits();
if(prevUnits!=10144)
{
model_ms->setDisplayUnits(10144);
}
XMLOutput writer(model_ms,device,0);
int c;
foreach(c,saveTempCols)
{
writer.addTemperatureColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
foreach(c,saveNoteCols)
{
writer.addAnnotationColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
bool retval= writer.output();
if(prevUnits!=10144)
{
model_ms->setDisplayUnits(prevUnits);
}
return retval;
}

/*:326*//*327:*/
#line 8417 "./typica.w"

bool ZoomLog::saveCSV(QIODevice*device)
{
CSVOutput writer(currentModel,device,0);
int c;
foreach(c,saveTempCols)
{
writer.addTemperatureColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
foreach(c,saveNoteCols)
{
writer.addAnnotationColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
return writer.output();
}

/*:327*//*328:*/
#line 8441 "./typica.w"

void ZoomLog::switchLOD(MeasurementModel*m)
{
disconnect(currentModel,SIGNAL(rowChanged(int)),this,0);
setModel(m);
currentModel= m;
connect(currentModel,SIGNAL(rowChanged(int)),this,SLOT(centerOn(int)));
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

/*:328*//*329:*/
#line 8489 "./typica.w"

void ZoomLog::setDisplayUnits(int scale)
{
model_ms->setDisplayUnits(scale);
model_1s->setDisplayUnits(scale);
model_5s->setDisplayUnits(scale);
model_10s->setDisplayUnits(scale);
model_15s->setDisplayUnits(scale);
model_30s->setDisplayUnits(scale);
model_1m->setDisplayUnits(scale);
}

int ZoomLog::displayUnits()
{
return model_ms->displayUnits();
}

/*:329*//*330:*/
#line 8509 "./typica.w"

QString ZoomLog::lastTime(int series)
{
Measurement measure= lastMeasurement.value(series);
QTime time= measure.time();
return time.toString("h:mm:ss.zzz");
}

/*:330*//*331:*/
#line 8519 "./typica.w"

ZoomLog::ZoomLog():QTableView(NULL),model_ms(new MeasurementModel(this)),
model_1s(new MeasurementModel(this)),model_5s(new MeasurementModel(this)),
model_10s(new MeasurementModel(this)),model_15s(new MeasurementModel(this)),
model_30s(new MeasurementModel(this)),model_1m(new MeasurementModel(this))
{
setEditTriggers(QAbstractItemView::NoEditTriggers);
setSelectionMode(QAbstractItemView::NoSelection);
modelSet<<model_ms<<model_1s<<model_5s<<model_10s<<model_15s<<
model_30s<<model_1m;
currentModel= model_30s;
setModel(currentModel);
connect(currentModel,SIGNAL(rowChanged(int)),this,SLOT(centerOn(int)));
connect(horizontalHeader(),SIGNAL(sectionResized(int,int,int)),
this,SLOT(persistColumnResize(int,int,int)));
connect(horizontalHeader(),SIGNAL(sectionCountChanged(int,int)),
this,SLOT(restoreColumnWidths()));
}

/*:331*//*332:*/
#line 8542 "./typica.w"

void ZoomLog::setHeaderData(int section,QString text)
{
MeasurementModel*m;
foreach(m,modelSet)
{
m->setHeaderData(section,Qt::Horizontal,QVariant(text));
}
}

/*:332*//*333:*/
#line 8556 "./typica.w"

void ZoomLog::addOutputTemperatureColumn(int column)
{
saveTempCols.append(column);
}

void ZoomLog::addOutputAnnotationColumn(int column)
{
saveNoteCols.append(column);
}

void ZoomLog::clearOutputColumns()
{
saveTempCols.clear();
saveNoteCols.clear();
}

/*:333*//*334:*/
#line 8576 "./typica.w"

void ZoomLog::persistColumnResize(int column,int,int newsize)
{
/*524:*/
#line 12554 "./typica.w"

QSettings settings;
/*525:*/
#line 12567 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:525*/
#line 12556 "./typica.w"

settings.setValue(QString("columnWidths/%1/%2/%3").
arg(topLevelWidget->objectName()).
arg(objectName()).arg(column),
QVariant(newsize));

/*:524*/
#line 8579 "./typica.w"

}

void ZoomLog::restoreColumnWidths()
{
/*527:*/
#line 12587 "./typica.w"

QSettings settings;
/*525:*/
#line 12567 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:525*/
#line 12589 "./typica.w"

QString baseKey= 
QString("columnWidths/%1/%2").arg(topLevelWidget->objectName()).
arg(objectName());
for(int i= 0;i<model()->columnCount();i++)
{
QString key= QString("%1/%2").arg(baseKey).arg(i);
if(settings.contains(key))
{
setColumnWidth(i,settings.value(key).toInt());
}
}

/*:527*/
#line 8584 "./typica.w"

}

void ZoomLog::setVisible(bool visibility)
{
QTableView::setVisible(visibility);
}

void ZoomLog::showEvent(QShowEvent*)
{
/*527:*/
#line 12587 "./typica.w"

QSettings settings;
/*525:*/
#line 12567 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:525*/
#line 12589 "./typica.w"

QString baseKey= 
QString("columnWidths/%1/%2").arg(topLevelWidget->objectName()).
arg(objectName());
for(int i= 0;i<model()->columnCount();i++)
{
QString key= QString("%1/%2").arg(baseKey).arg(i);
if(settings.contains(key))
{
setColumnWidth(i,settings.value(key).toInt());
}
}

/*:527*/
#line 8594 "./typica.w"

}

/*:334*/
#line 775 "./typica.w"

/*342:*/
#line 8816 "./typica.w"

bool MeasurementList::operator<(const MeasurementList&other)const
{
return this->first().toTime()<other.first().toTime();
}

bool MeasurementList::operator==(const MeasurementList&other)const
{
return this->first().toTime()==other.first().toTime();
}

/*:342*//*343:*/
#line 8832 "./typica.w"

QModelIndex MeasurementModel::parent(const QModelIndex&)const
{
return QModelIndex();
}

/*:343*//*344:*/
#line 8842 "./typica.w"

void MeasurementModel::newMeasurement(Measurement measure,int tempcolumn)
{
MeasurementList*temp;
temp= new MeasurementList;
temp->append(QVariant(measure.time()));
/*345:*/
#line 8893 "./typica.w"

/*346:*/
#line 8938 "./typica.w"

QList<MeasurementList*> ::iterator i= lastInsertion;
bool quickscan= false;
if(entries->size()> 5)
{
if(**i<*temp)
{
i+= 1;
for(int j= 10;j> 0;j--)
{
if(i!=entries->end())
{
if(**i<*temp)
{
i+= 1;
}
else
{
quickscan= true;
break;
}
}
else
{
quickscan= true;
break;
}
}
}
else
{
if(**i==*temp)
{
quickscan= true;
}
}
}

/*:346*/
#line 8894 "./typica.w"

if(quickscan==false)
{
i= entries->begin();
QList<MeasurementList*> ::iterator u= entries->end();
QList<MeasurementList*> ::iterator midpoint;
int n= u-i;
int rA;
while(n> 0)
{
rA= n>>1;
midpoint= i+rA;
if(**midpoint<*temp)
{
i= midpoint+1;
n-= rA+1;
}
else
{
n= rA;
}
}
}

/*:345*/
#line 8848 "./typica.w"

MeasurementList*newEntry;
int insertion;
if(i!=entries->end())
{
insertion= entries->indexOf(*i);
if((*i)->first().toTime()==measure.time())
{
/*347:*/
#line 8980 "./typica.w"

if((*i)->size()<tempcolumn+1)
{
for(int j= (*i)->size()-1;j<tempcolumn+1;j++)
{
(*i)->append(QVariant());
}
}
(*i)->replace(tempcolumn,measure.temperature());
lastInsertion= i;
emit dataChanged(createIndex(insertion,tempcolumn),
createIndex(insertion,tempcolumn));
lastTemperature->insert(tempcolumn,insertion);

/*:347*/
#line 8856 "./typica.w"

}
else
{
/*348:*/
#line 8998 "./typica.w"

beginInsertRows(QModelIndex(),insertion,insertion);
newEntry= new MeasurementList;
newEntry->append(QVariant(measure.time()));
for(int j= 0;j<tempcolumn+1;j++)
{
newEntry->append(QVariant());
}
newEntry->replace(tempcolumn,measure.temperature());
lastInsertion= entries->insert(i,newEntry);
endInsertRows();
lastTemperature->insert(tempcolumn,insertion);

/*:348*/
#line 8860 "./typica.w"

}
}
else
{
/*349:*/
#line 9016 "./typica.w"

insertion= entries->size();
/*348:*/
#line 8998 "./typica.w"

beginInsertRows(QModelIndex(),insertion,insertion);
newEntry= new MeasurementList;
newEntry->append(QVariant(measure.time()));
for(int j= 0;j<tempcolumn+1;j++)
{
newEntry->append(QVariant());
}
newEntry->replace(tempcolumn,measure.temperature());
lastInsertion= entries->insert(i,newEntry);
endInsertRows();
lastTemperature->insert(tempcolumn,insertion);

/*:348*/
#line 9018 "./typica.w"


/*:349*/
#line 8865 "./typica.w"

}
if(tempcolumn>=colcount)
{
colcount= tempcolumn+1;
}
emit rowChanged(insertion);
delete temp;
}

/*:344*//*350:*/
#line 9027 "./typica.w"

void MeasurementModel::newAnnotation(QString annotation,int tempcolumn,
int annotationColumn)
{
int r;
if(lastTemperature->contains(tempcolumn))
{
r= lastTemperature->value(tempcolumn);
}
else
{
r= 0;
}
if(r==0&&entries->size()==0)
{
/*351:*/
#line 9065 "./typica.w"

beginInsertRows(QModelIndex(),0,0);
MeasurementList*newEntry= new MeasurementList;
newEntry->append(QVariant(QTime(0,0,0,0)));
entries->append(newEntry);
endInsertRows();

/*:351*/
#line 9042 "./typica.w"

}
MeasurementList*row= entries->at(r);
if(row->size()<=annotationColumn)
{
for(int i= row->size()-1;i<annotationColumn+1;i++)
{
row->append(QVariant());
}
}
row->replace(annotationColumn,annotation);
emit dataChanged(createIndex(r,annotationColumn),
createIndex(r,annotationColumn));
emit rowChanged(r);
if(annotationColumn> colcount-1)
{
colcount= annotationColumn+1;
}
}

/*:350*//*352:*/
#line 9076 "./typica.w"

void MeasurementModel::clear()
{
beginRemoveRows(QModelIndex(),0,entries->size());
while(entries->size()!=0)
{
MeasurementList*row= entries->takeFirst();
delete row;
}
endRemoveRows();
colcount= hData->size();
lastTemperature->clear();
reset();
}

/*:352*//*353:*/
#line 9102 "./typica.w"

bool MeasurementModel::setData(const QModelIndex&index,
const QVariant&value,int role)
{
if(role!=Qt::EditRole&&role!=Qt::DisplayRole)
{
return false;
}
/*354:*/
#line 9134 "./typica.w"

bool valid= false;
if(index.isValid())
{
if(index.row()<entries->size())
{
if(index.column()<colcount)
{
valid= true;
}
}
}

/*:354*/
#line 9110 "./typica.w"

if(!valid)
{
return false;
}
MeasurementList*row= entries->at(index.row());
if(index.column()>=row->size())
{
/*355:*/
#line 9151 "./typica.w"

for(int i= row->size()-1;i<index.column();i++)
{
row->append(QVariant());
}

/*:355*/
#line 9118 "./typica.w"

}
if(index.column()==0)
{
/*356:*/
#line 9166 "./typica.w"

QTime time;
if(!(time= QTime::fromString(value.toString(),"m:s.z")).isValid())
{
if(!(time= QTime::fromString(value.toString(),"m:s")).isValid())
{
return false;
}
}
row= entries->takeAt(index.row());
row->replace(index.column(),QVariant(time));
MeasurementList*temp= row;
/*345:*/
#line 8893 "./typica.w"

/*346:*/
#line 8938 "./typica.w"

QList<MeasurementList*> ::iterator i= lastInsertion;
bool quickscan= false;
if(entries->size()> 5)
{
if(**i<*temp)
{
i+= 1;
for(int j= 10;j> 0;j--)
{
if(i!=entries->end())
{
if(**i<*temp)
{
i+= 1;
}
else
{
quickscan= true;
break;
}
}
else
{
quickscan= true;
break;
}
}
}
else
{
if(**i==*temp)
{
quickscan= true;
}
}
}

/*:346*/
#line 8894 "./typica.w"

if(quickscan==false)
{
i= entries->begin();
QList<MeasurementList*> ::iterator u= entries->end();
QList<MeasurementList*> ::iterator midpoint;
int n= u-i;
int rA;
while(n> 0)
{
rA= n>>1;
midpoint= i+rA;
if(**midpoint<*temp)
{
i= midpoint+1;
n-= rA+1;
}
else
{
n= rA;
}
}
}

/*:345*/
#line 9178 "./typica.w"

entries->insert(i,row);
int newRow= entries->indexOf(*i);
if(newRow<index.row())
{
emit dataChanged(createIndex(newRow,index.column()),index);
}
else
{
emit dataChanged(index,createIndex(newRow,index.column()));
}

/*:356*/
#line 9122 "./typica.w"

}
else
{
/*357:*/
#line 9192 "./typica.w"

row->replace(index.column(),value);
emit dataChanged(index,index);

/*:357*/
#line 9126 "./typica.w"

}
return true;
}

/*:353*//*358:*/
#line 9200 "./typica.w"

MeasurementModel::MeasurementModel(QObject*parent):QAbstractItemModel(parent),
unit(Fahrenheit),hData(new QStringList),
lastTemperature(new QHash<int,int> )
{
colcount= 1;
entries= new QList<MeasurementList*> ;
lastInsertion= entries->begin();
hData->append(tr("Time"));
}

/*:358*//*359:*/
#line 9213 "./typica.w"

MeasurementModel::~MeasurementModel()
{
clear();
delete entries;
delete hData;
}

/*:359*//*360:*/
#line 9225 "./typica.w"

int MeasurementModel::rowCount(const QModelIndex&parent)const
{
if(parent==QModelIndex())
{
return entries->size();
}
return 0;
}

int MeasurementModel::columnCount(const QModelIndex&parent)const
{
if(parent==QModelIndex())
{
return colcount;
}
return 0;
}

/*:360*//*361:*/
#line 9252 "./typica.w"

bool MeasurementModel::setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int)
{
if(orientation==Qt::Horizontal)
{
if(hData->size()<section+1)
{
for(int i= hData->size();i<section+1;i++)
{
if(colcount<i)
{
beginInsertColumns(QModelIndex(),i,i);
}
hData->append(QString());
if(colcount<i)
{
endInsertColumns();
}
}
}
hData->replace(section,value.toString());
emit headerDataChanged(orientation,section,section);
if(colcount<section+1)
{
colcount= section+1;
}
return true;
}
return false;
}

/*:361*//*362:*/
#line 9292 "./typica.w"

void MeasurementModel::setDisplayUnits(int scale)
{
beginResetModel();
unit= scale;
endResetModel();
}

int MeasurementModel::displayUnits()
{
return unit;
}

/*:362*//*363:*/
#line 9316 "./typica.w"

QVariant MeasurementModel::data(const QModelIndex&index,int role)const
{
/*354:*/
#line 9134 "./typica.w"

bool valid= false;
if(index.isValid())
{
if(index.row()<entries->size())
{
if(index.column()<colcount)
{
valid= true;
}
}
}

/*:354*/
#line 9319 "./typica.w"

if(!valid)
{
return QVariant();
}
if(role==Qt::DisplayRole||role==Qt::EditRole)
{
MeasurementList*row= entries->at(index.row());
if(index.column()> row->size())
{
return QVariant();
}
else
{
if(index.column()==0)
{
return QVariant(row->at(0).toTime().toString("mm:ss.zzz"));
}
else if(lastTemperature->contains(index.column()))
{
if(row->at(index.column()).toString().isEmpty())
{
return QVariant();
}
switch(unit)
{
case Auto:
case Fahrenheit:
return QVariant(row->at(index.column()).toString());
break;
case Celsius:
return QVariant((row->at(index.column()).toDouble()-
32)*5/9);
break;
case Kelvin:
return QVariant((row->at(index.column()).toDouble()+
459.67)*5/9);
break;
case Rankine:
return QVariant(row->at(index.column()).toDouble()+
459.67);
break;
default:
break;
}
}
return QVariant(row->at(index.column()).toString());
}
}
return QVariant();
}

/*:363*//*364:*/
#line 9373 "./typica.w"

QVariant MeasurementModel::headerData(int section,Qt::Orientation orientation,
int role)const
{
if(orientation==Qt::Horizontal)
{
if(role==Qt::DisplayRole)
{
if(section<hData->size())
{
return QVariant(hData->at(section));
}
}
}
return QVariant();
}

/*:364*//*365:*/
#line 9400 "./typica.w"

Qt::ItemFlags MeasurementModel::flags(const QModelIndex&index)const
{
/*354:*/
#line 9134 "./typica.w"

bool valid= false;
if(index.isValid())
{
if(index.row()<entries->size())
{
if(index.column()<colcount)
{
valid= true;
}
}
}

/*:354*/
#line 9403 "./typica.w"

if(valid)
{
return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
}
return 0;
}

/*:365*//*366:*/
#line 9415 "./typica.w"

QModelIndex MeasurementModel::index(int row,int column,
const QModelIndex&parent)const
{
if(parent==QModelIndex())
{
if(row<entries->size()&&entries->isEmpty()==false)
{
if(column<entries->at(row)->size())
{
return createIndex(row,column);
}
}
}
return QModelIndex();
}

/*:366*/
#line 776 "./typica.w"

/*368:*/
#line 9466 "./typica.w"

AnnotationButton::AnnotationButton(const QString&text,QWidget*parent):
QPushButton(text,parent),note(""),tc(0),ac(0),count(0)
{
connect(this,SIGNAL(clicked()),this,SLOT(annotate()));
}

/*:368*//*369:*/
#line 9481 "./typica.w"

void AnnotationButton::annotate()
{
if(note.contains("%1"))
{
count++;
emit annotation(note.arg(count),tc,ac);
}
else
{
emit annotation(note,tc,ac);
}
}

/*:369*//*370:*/
#line 9499 "./typica.w"

void AnnotationButton::setTemperatureColumn(int tempcolumn)
{
tc= tempcolumn;
}

void AnnotationButton::setAnnotationColumn(int annotationcolumn)
{
ac= annotationcolumn;
}

void AnnotationButton::setAnnotation(const QString&annotation)
{
note= annotation;
}

/*:370*//*371:*/
#line 9518 "./typica.w"

void AnnotationButton::resetCount()
{
count= 0;
}

/*:371*/
#line 777 "./typica.w"

/*376:*/
#line 9601 "./typica.w"

AnnotationSpinBox::AnnotationSpinBox(const QString&pret,
const QString&postt,
QWidget*parent)
:QDoubleSpinBox(parent),pretext(pret),posttext(postt)
{
resetChange();
connect(this,SIGNAL(editingFinished()),this,SLOT(annotate()));
connect(this,SIGNAL(valueChanged(double)),this,SLOT(resetChange()));
}

/*:376*//*377:*/
#line 9618 "./typica.w"

void AnnotationSpinBox::resetChange()
{
change= true;
}

/*:377*//*378:*/
#line 9629 "./typica.w"

void AnnotationSpinBox::annotate()
{
if(change)
{
change= false;
emit annotation(QString("%1%2%3").arg(pretext).
arg(value()).arg(posttext),tc,ac);
}
}

/*:378*//*379:*/
#line 9642 "./typica.w"

void AnnotationSpinBox::setTemperatureColumn(int tempcolumn)
{
tc= tempcolumn;
}

void AnnotationSpinBox::setAnnotationColumn(int annotationcolumn)
{
ac= annotationcolumn;
}

void AnnotationSpinBox::setPretext(const QString&pret)
{
pretext= pret;
}

void AnnotationSpinBox::setPosttext(const QString&postt)
{
posttext= postt;
}

/*:379*/
#line 778 "./typica.w"

/*386:*/
#line 9810 "./typica.w"

TimerDisplay::TimerDisplay(QWidget*parent):QLCDNumber(8,parent),
s(QTime(0,0,0)),r(QTime(0,0,0)),clock(NULL),m(TimerDisplay::CountUp),
running(false),ar(false),startAction(new QAction(tr("Start"),NULL)),
stopAction(new QAction(tr("Stop"),NULL)),
resetAction(new QAction(tr("Reset"),NULL)),f(QString("hh:mm:ss")),
relative(QTime::currentTime()),base(QTime(0,0,0))
{
connect(startAction,SIGNAL(triggered(bool)),this,SLOT(startTimer()));
connect(stopAction,SIGNAL(triggered(bool)),this,SLOT(stopTimer()));
connect(resetAction,SIGNAL(triggered(bool)),this,SLOT(reset()));
clock.setInterval(500);
clock.setSingleShot(false);
connect(&clock,SIGNAL(timeout()),this,SLOT(updateTime()));
setSegmentStyle(Filled);
updateDisplay();
}

/*:386*//*387:*/
#line 9831 "./typica.w"

void TimerDisplay::updateTime()
{
QTime time;
int cseconds= 0;
int oseconds= 0;
int r= 0;
QTime nt= QTime(0,0,0);
int n= 0;
int bseconds= 0;
switch(m)
{
case TimerDisplay::CountUp:
/*388:*/
#line 9863 "./typica.w"

/*389:*/
#line 9878 "./typica.w"

time= QTime::currentTime();
cseconds= TIMETOINT(time);
oseconds= TIMETOINT(relative);
r= cseconds-oseconds;

/*:389*/
#line 9864 "./typica.w"

nt= nt.addSecs(r);
if(nt!=s)
{
s= nt;
emit valueChanged(s);
}

/*:388*/
#line 9844 "./typica.w"
;
break;
case TimerDisplay::CountDown:
/*390:*/
#line 9888 "./typica.w"

if(s> QTime(0,0,0))
{
/*389:*/
#line 9878 "./typica.w"

time= QTime::currentTime();
cseconds= TIMETOINT(time);
oseconds= TIMETOINT(relative);
r= cseconds-oseconds;

/*:389*/
#line 9891 "./typica.w"

bseconds= TIMETOINT(base);
n= bseconds-r;
nt= nt.addSecs(n);
if(nt!=s)
{
s= nt;
emit valueChanged(s);
}
}

/*:390*/
#line 9847 "./typica.w"
;
break;
case TimerDisplay::Clock:
/*391:*/
#line 9905 "./typica.w"

time= QTime::currentTime();
if(time!=s)
{
s= time;
emit valueChanged(s);
}

/*:391*/
#line 9850 "./typica.w"
;
break;
default:
Q_ASSERT_X(false,"updateTime","invalid timer mode");
break;
}
updateDisplay();
}

/*:387*//*392:*/
#line 9919 "./typica.w"

void TimerDisplay::startTimer()
{
if(!running)
{
relative= QTime::currentTime();
if(ar)
{
reset();
}
else
{
relative= TIMESUBTRACT(relative,s);
}
if(m==Clock)
{
updateTime();
}
base= s;
clock.start();
running= true;
emit runStateChanged(true);
}
}

/*:392*//*393:*/
#line 9947 "./typica.w"

void TimerDisplay::stopTimer()
{
if(running)
{
clock.stop();
running= false;
emit runStateChanged(false);
}
}

/*:393*//*394:*/
#line 9960 "./typica.w"

TimerDisplay::~TimerDisplay()
{
clock.stop();
}

/*:394*//*395:*/
#line 9969 "./typica.w"

void TimerDisplay::setCountUpMode()
{
m= TimerDisplay::CountUp;
}

void TimerDisplay::setCountDownMode()
{
m= TimerDisplay::CountDown;
}

void TimerDisplay::setClockMode()
{
m= TimerDisplay::Clock;
}

/*:395*//*396:*/
#line 9987 "./typica.w"

QString TimerDisplay::value()
{
return s.toString(f);
}

QTime TimerDisplay::seconds()
{
return s;
}

TimerDisplay::TimerMode TimerDisplay::mode()
{
return m;
}

bool TimerDisplay::isRunning()
{
return running;
}

QTime TimerDisplay::resetValue()
{
return r;
}

QString TimerDisplay::displayFormat()
{
return f;
}

bool TimerDisplay::autoReset()
{
return ar;
}

/*:396*//*397:*/
#line 10025 "./typica.w"

void TimerDisplay::setTimer(QTime value)
{
if(value.isValid())
{
s= value;
updateDisplay();
emit valueChanged(value);
}
}

void TimerDisplay::setMode(TimerDisplay::TimerMode mode)
{
m= mode;
}

void TimerDisplay::setResetValue(QTime value)
{
r= value;
}

void TimerDisplay::setDisplayFormat(QString format)
{
f= format;
setNumDigits(format.length());
}

void TimerDisplay::setAutoReset(bool reset)
{
ar= reset;
}

/*:397*//*398:*/
#line 10060 "./typica.w"

void TimerDisplay::copyTimer()
{
QApplication::clipboard()->setText(value());
}

/*:398*//*399:*/
#line 10069 "./typica.w"

void TimerDisplay::reset()
{
if(!running)
{
s= r;
updateDisplay();
}
}

/*:399*//*400:*/
#line 10082 "./typica.w"

void TimerDisplay::updateDisplay()
{
display(value());
}

/*:400*/
#line 779 "./typica.w"

/*406:*/
#line 10176 "./typica.w"

int PackLayout::doLayout(const QRect&rect,bool testOnly)const
{
int x= rect.x();
int y= rect.y();
QLayoutItem*item;
if(orientation==Qt::Horizontal)
{
/*407:*/
#line 10200 "./typica.w"

foreach(item,itemList)
{
int nextX= x+item->sizeHint().width()+spacing();
int right= x+item->sizeHint().width();
if(item==itemList.last())
{
right= rect.right();
}
int bottom= rect.bottom();
if(!testOnly)
{
item->setGeometry(QRect(QPoint(x,y),QPoint(right,bottom)));
}
x= nextX;
}

/*:407*/
#line 10184 "./typica.w"

}
else
{
/*408:*/
#line 10219 "./typica.w"

foreach(item,itemList)
{
int nextY= y+item->sizeHint().height()+spacing();
int bottom= y+item->sizeHint().height();
if(item==itemList.last())
{
bottom= rect.bottom();
}
int right= rect.right();
if(!testOnly)
{
item->setGeometry(QRect(QPoint(x,y),QPoint(right,bottom)));
}
y= nextY;
}

/*:408*/
#line 10188 "./typica.w"

}
return y;
}

/*:406*//*409:*/
#line 10243 "./typica.w"

QSize PackLayout::minimumSize()const
{
QSize size;
QLayoutItem*item;
foreach(item,itemList)
{
if(orientation==Qt::Horizontal)
{
size+= QSize(item->minimumSize().width(),0);
if(size.height()<item->minimumSize().height())
{
size.setHeight(item->minimumSize().height());
}
}
else
{
size+= QSize(0,item->minimumSize().height());
if(size.width()<item->minimumSize().width())
{
size.setWidth(item->minimumSize().width());
}
}
}
size+= QSize(2*margin(),2*margin());
return size;
}

/*:409*//*410:*/
#line 10275 "./typica.w"

PackLayout::PackLayout(QWidget*parent,int margin,int spacing):
QLayout(parent)
{
setMargin(margin);
setSpacing(spacing);
setOrientation(Qt::Horizontal);
}

PackLayout::PackLayout(int spacing)
{
setSpacing(spacing);
setOrientation(Qt::Horizontal);
}

/*:410*//*411:*/
#line 10293 "./typica.w"

PackLayout::~PackLayout()
{
QLayoutItem*item;
while((item= takeAt(0)))
{
delete item;
}
}

/*:411*//*412:*/
#line 10307 "./typica.w"

QLayoutItem*PackLayout::takeAt(int index)
{
if(index>=0&&index<itemList.size())
{
return itemList.takeAt(index);
}
else
{
return NULL;
}
}

/*:412*//*413:*/
#line 10323 "./typica.w"

QLayoutItem*PackLayout::itemAt(int index)const
{
if(index>=0&&index<itemList.size())
{
return itemList.at(index);
}
else
{
return NULL;
}
}

/*:413*//*414:*/
#line 10346 "./typica.w"

void PackLayout::addItem(QLayoutItem*item)
{
itemList.append(item);
}

/*:414*//*415:*/
#line 10354 "./typica.w"

int PackLayout::count()const
{
return itemList.size();
}

/*:415*//*416:*/
#line 10366 "./typica.w"

Qt::Orientations PackLayout::expandingDirections()const
{
return Qt::Vertical|Qt::Horizontal;
}

bool PackLayout::hasHeightForWidth()const
{
return false;
}

int PackLayout::heightForWidth(int width)const
{
return doLayout(QRect(0,0,width,0),true);
}

void PackLayout::setGeometry(const QRect&rect)
{
QLayout::setGeometry(rect);
doLayout(rect,false);
}

QSize PackLayout::sizeHint()const
{
return minimumSize();
}

/*:416*//*417:*/
#line 10397 "./typica.w"

void PackLayout::setOrientation(Qt::Orientations direction)
{
orientation= direction;
doLayout(geometry(),false);
}

/*:417*/
#line 780 "./typica.w"

/*419:*/
#line 10436 "./typica.w"

SceneButton::SceneButton():QGraphicsScene()
{

}

SceneButton::~SceneButton()
{

}

void SceneButton::mousePressEvent(QGraphicsSceneMouseEvent*mouseEvent)
{
emit clicked(mouseEvent->buttonDownScreenPos(mouseEvent->button()));
}

/*:419*/
#line 781 "./typica.w"

/*421:*/
#line 10482 "./typica.w"

WidgetDecorator::WidgetDecorator(QWidget*widget,const QString&labeltext,
Qt::Orientations orientation,
QWidget*parent,Qt::WindowFlags f):
QWidget(parent,f),label(new QGraphicsView()),
scene(new SceneButton())
{
layout= new PackLayout(this);
layout->setOrientation(orientation);
/*422:*/
#line 10502 "./typica.w"

label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setFrameShape(QFrame::NoFrame);
label->setInteractive(true);

/*:422*/
#line 10491 "./typica.w"

/*423:*/
#line 10513 "./typica.w"

scene->setBackgroundBrush(Qt::cyan);
text= scene->addText(labeltext);
if(orientation==Qt::Horizontal)
{
text->rotate(270.0);
}
label->setScene(scene);

/*:423*/
#line 10492 "./typica.w"

/*424:*/
#line 10531 "./typica.w"

if(orientation==Qt::Horizontal)
{
label->setMaximumWidth((int)(text->boundingRect().height()+1));
}
else
{
label->setMaximumHeight((int)(text->boundingRect().height()+1));
}
label->centerOn(text);

/*:424*/
#line 10493 "./typica.w"

/*425:*/
#line 10546 "./typica.w"

layout->addWidget(label);
layout->addWidget(widget);
if(orientation==Qt::Horizontal)
{
setMinimumSize(widget->sizeHint().width()+label->sizeHint().width(),
widget->sizeHint().height());
}
else
{
setMinimumSize(widget->sizeHint().width(),
widget->sizeHint().height()+label->sizeHint().height());
}

/*:425*/
#line 10494 "./typica.w"

}

/*:421*//*426:*/
#line 10563 "./typica.w"

void WidgetDecorator::setBackgroundBrush(QBrush background)
{
scene->setBackgroundBrush(background);
}

void WidgetDecorator::setTextColor(QColor color)
{
text->setDefaultTextColor(color);
}

/*:426*//*427:*/
#line 10576 "./typica.w"

WidgetDecorator::~WidgetDecorator()
{

}

/*:427*/
#line 782 "./typica.w"

/*432:*/
#line 10675 "./typica.w"

void LogEditWindow::addTheRows()
{
QTime s= startTime->time();
while(s<endTime->time())
{
model->newMeasurement(Measurement(0,s),1);
s= s.addSecs(interval->value());
}
model->newMeasurement(Measurement(0,endTime->time()),1);
}

/*:432*//*433:*/
#line 10689 "./typica.w"

LogEditWindow::LogEditWindow():QMainWindow(NULL),
centralWidget(new QWidget(NULL)),mainLayout(new PackLayout(0)),
addRowsLayout(new QHBoxLayout(NULL)),
startTimeLabel(new QLabel("Start Time")),
startTime(new QTimeEdit(QTime(0,0,0,0))),
endTimeLabel(new QLabel("End Time")),
endTime(new QTimeEdit(QTime(0,20,0,0))),
intervalLabel(new QLabel("Interval (seconds)")),
interval(new QSpinBox()),
addRows(new QPushButton("Add Rows")),
saveXml(new QAction(tr("Save Profile As..."),NULL)),
saveCsv(new QAction(tr("Export CSV"),NULL)),
openXml(new QAction(tr("Load Target Profile..."),NULL)),
model(new MeasurementModel()),
log(new QTableView())
{
/*434:*/
#line 10726 "./typica.w"

QSettings settings;
resize(settings.value("logSize",QSize(620,400)).toSize());
move(settings.value("logPos",QPoint(200,60)).toPoint());

/*:434*/
#line 10706 "./typica.w"

/*435:*/
#line 10739 "./typica.w"

mainLayout->setOrientation(Qt::Vertical);
addRowsLayout->addSpacing(10);
addRowsLayout->addWidget(startTimeLabel);
addRowsLayout->addWidget(startTime);
addRowsLayout->addSpacing(10);
startTime->setDisplayFormat("mm:ss");
addRowsLayout->addWidget(endTimeLabel);
addRowsLayout->addWidget(endTime);
addRowsLayout->addSpacing(10);
endTime->setDisplayFormat("mm:ss");
addRowsLayout->addWidget(intervalLabel);
addRowsLayout->addWidget(interval);
addRowsLayout->addSpacing(10);
interval->setRange(0,60);
interval->setValue(30);
addRowsLayout->addWidget(addRows);
addRowsLayout->addSpacing(10);
connect(addRows,SIGNAL(clicked()),this,SLOT(addTheRows()));

/*:435*/
#line 10707 "./typica.w"

/*436:*/
#line 10762 "./typica.w"

model->setHeaderData(0,Qt::Horizontal,"Time");
model->setHeaderData(1,Qt::Horizontal,"Temperature");
model->setHeaderData(2,Qt::Horizontal,"Annotation");
model->clear();

/*:436*/
#line 10708 "./typica.w"

/*437:*/
#line 10771 "./typica.w"

log->setModel(model);
log->setColumnWidth(0,100);
log->setColumnWidth(1,100);
log->setColumnWidth(2,100);

/*:437*/
#line 10709 "./typica.w"

mainLayout->addItem(addRowsLayout);
mainLayout->addWidget(log);
centralWidget->setLayout(mainLayout);
setCentralWidget(centralWidget);
QMenu*fileMenu= menuBar()->addMenu(tr("&File"));
fileMenu->addAction(openXml);
connect(openXml,SIGNAL(triggered()),this,SLOT(openXML()));
fileMenu->addAction(saveXml);
connect(saveXml,SIGNAL(triggered()),this,SLOT(saveXML()));
fileMenu->addAction(saveCsv);
connect(saveCsv,SIGNAL(triggered()),this,SLOT(saveCSV()));
}

/*:433*//*438:*/
#line 10782 "./typica.w"

void LogEditWindow::saveXML()
{
QSettings settings;
QString lastDir= settings.value("lastDirectory").toString();
QString filename= QFileDialog::getSaveFileName(this,tr("Save Log As..."),
lastDir,"",0);
QFile file(filename);
XMLOutput writer(model,&file,0);
writer.addTemperatureColumn("Temperature",1);
writer.addAnnotationColumn("Annotation",2);
if(writer.output())
{
QFileInfo info(filename);
QDir directory= info.dir();
lastDir= directory.path();
settings.setValue("lastDirectory",lastDir);
}
}

void LogEditWindow::saveCSV()
{
QSettings settings;
QString lastDir= settings.value("lastDirectory").toString();
QString filename= QFileDialog::getSaveFileName(this,tr("Export As..."),
lastDir,"",0);
QFile file(filename);
CSVOutput writer(model,&file,0);
writer.addTemperatureColumn("Temperature",1);
writer.addAnnotationColumn("Annotation",2);
if(writer.output())
{
QFileInfo info(filename);
QDir directory= info.dir();
lastDir= directory.path();
settings.setValue("lastDirectory",lastDir);
}
}

/*:438*//*439:*/
#line 10825 "./typica.w"

void LogEditWindow::openXML()
{
QSettings settings;
QString lastDir= settings.value("lastDirectory").toString();
QString filename= QFileDialog::getOpenFileName(this,tr("Open XML Log..."),
lastDir,"",0);
if(filename.isNull())
{
return;
}
QFile file(filename);
XMLInput reader(&file,1);
connect(&reader,SIGNAL(measure(Measurement,int)),
model,SLOT(newMeasurement(Measurement,int)));
connect(&reader,SIGNAL(annotation(QString,int,int)),
model,SLOT(newAnnotation(QString,int,int)));
if(reader.input())
{
QFileInfo info(filename);
setWindowTitle(QString(tr("%1 - %2")).
arg(QCoreApplication::applicationName()).arg(info.baseName()));
QDir directory= info.dir();
lastDir= directory.path();
settings.setValue("lastDirectory",lastDir);
}
}

/*:439*//*440:*/
#line 10856 "./typica.w"

void LogEditWindow::closeEvent(QCloseEvent*event)
{
QSettings settings;
settings.setValue("logSize",size());
settings.setValue("logPos",pos());
event->accept();
}

/*:440*/
#line 783 "./typica.w"

/*446:*/
#line 10969 "./typica.w"

bool XMLOutput::output()
{
if(!out->open(QIODevice::WriteOnly|QIODevice::Text))
{
return false;
}
QXmlStreamWriter xmlout(out);
xmlout.writeStartDocument("1.0");
xmlout.writeDTD("<!DOCTYPE roastlog2.0>");
xmlout.writeStartElement("roastlog");
/*447:*/
#line 11002 "./typica.w"

foreach(int c,temperatureColumns.keys())
{
xmlout.writeStartElement("tempseries");
xmlout.writeAttribute("name",temperatureColumns.value(c));
xmlout.writeEndElement();
}
foreach(int c,annotationColumns.keys())
{
xmlout.writeStartElement("noteseries");
xmlout.writeAttribute("name",annotationColumns.value(c));
xmlout.writeEndElement();
}

/*:447*/
#line 10980 "./typica.w"

xmlout.writeStartElement("roast");
bool oresult;
for(int i= 0;i<data->rowCount();i++)
{
/*448:*/
#line 11021 "./typica.w"

oresult= false;
foreach(int c,temperatureColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().isEmpty()))
{
oresult= true;
break;
}
}
if(oresult==false)
{
foreach(int c,annotationColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().
isEmpty()))
{
oresult= true;
break;
}
}
}

/*:448*/
#line 10985 "./typica.w"

if(oresult)
{
/*449:*/
#line 11051 "./typica.w"

xmlout.writeStartElement("tuple");
xmlout.writeTextElement("time",data->data(data->index(i,time),
Qt::DisplayRole).toString());
foreach(int c,temperatureColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().isEmpty()))
{
xmlout.writeStartElement("temperature");
xmlout.writeAttribute("series",temperatureColumns.value(c));
xmlout.writeCharacters(data->data(data->index(i,c),Qt::DisplayRole).
toString());
xmlout.writeEndElement();
}
}
foreach(int c,annotationColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().isEmpty()))
{
xmlout.writeStartElement("annotation");
xmlout.writeAttribute("series",annotationColumns.value(c));
xmlout.writeCharacters(data->data(data->index(i,c),Qt::DisplayRole).
toString());
xmlout.writeEndElement();
}
}
xmlout.writeEndElement();

/*:449*/
#line 10988 "./typica.w"

}
}
xmlout.writeEndElement();
xmlout.writeEndElement();
xmlout.writeEndDocument();
out->close();
return true;
}

/*:446*//*450:*/
#line 11083 "./typica.w"

XMLOutput::XMLOutput(MeasurementModel*model,QIODevice*device,int timec)
:QObject(NULL),data(model),out(device),time(timec)
{

}

void XMLOutput::setModel(MeasurementModel*model)
{
data= model;
}

void XMLOutput::setTimeColumn(int column)
{
time= column;
}

void XMLOutput::setDevice(QIODevice*device)
{
out= device;
}

/*:450*//*451:*/
#line 11112 "./typica.w"

void XMLOutput::addTemperatureColumn(const QString&series,int column)
{
temperatureColumns.insert(column,series);
}

void XMLOutput::addAnnotationColumn(const QString&series,int column)
{
annotationColumns.insert(column,series);
}

/*:451*/
#line 784 "./typica.w"

/*453:*/
#line 11164 "./typica.w"

bool XMLInput::input()
{
if(!in->open(QIODevice::ReadOnly|QIODevice::Text))
{
return false;
}
QXmlStreamReader xmlin(in);
QMap<QString,int> temperatureColumns;
QMap<QString,int> annotationColumns;
int nextColumn= firstc;
/*454:*/
#line 11195 "./typica.w"

while(!xmlin.isDTD())
{
xmlin.readNext();
}
if(xmlin.isDTD())
{
if(xmlin.text()=="<!DOCTYPE roastlog>")
{
/*455:*/
#line 11217 "./typica.w"

emit newTemperatureColumn(firstc,"Bean");
emit newAnnotationColumn(firstc+1,"Note");
emit lastColumn(firstc+1);

/*:455*/
#line 11204 "./typica.w"

}
else
{
xmlin.readNext();
/*456:*/
#line 11226 "./typica.w"

while(xmlin.name()!="roast")
{
if(xmlin.isStartElement())
{
if(xmlin.name()=="tempseries")
{
temperatureColumns.insert(xmlin.attributes().value("name").
toString(),
nextColumn);
emit newTemperatureColumn(nextColumn,
xmlin.attributes().value("name").
toString());
nextColumn++;
}
else if(xmlin.name()=="noteseries")
{
annotationColumns.insert(xmlin.attributes().value("name").
toString(),nextColumn);
emit newAnnotationColumn(nextColumn,
xmlin.attributes().value("name").
toString());
nextColumn++;
}
}
xmlin.readNext();
}
emit lastColumn(nextColumn-1);

/*:456*/
#line 11209 "./typica.w"

}
}

/*:454*/
#line 11175 "./typica.w"

QTime timeval= QTime();
double tempval= 0;
QString noteval= QString();
int column;
int counter= 0;
while(!xmlin.atEnd())
{
/*457:*/
#line 11267 "./typica.w"

xmlin.readNext();
if(xmlin.isStartElement())
{
/*458:*/
#line 11293 "./typica.w"

if(xmlin.name()=="time")
{
timeval= QTime::fromString(xmlin.readElementText(),"mm:ss.zzz");
}
else if(xmlin.name()=="temperature")
{
column= xmlin.attributes().value("series").toString().isEmpty()?
firstc:temperatureColumns.value(xmlin.attributes().
value("series").toString());
tempval= xmlin.readElementText().toDouble();
Measurement measurement(tempval,timeval);
emit measure(measurement,column);
}
else if(xmlin.name()=="annotation")
{
column= xmlin.attributes().value("series").toString().isEmpty()?
firstc+1:annotationColumns.value(xmlin.attributes().
value("series").toString());
noteval= xmlin.readElementText();
if(!noteval.isEmpty())
{
emit annotation(noteval,firstc,column);
}
}

/*:458*/
#line 11271 "./typica.w"

}
counter++;
if(counter%100==0)
{
QCoreApplication::processEvents();
}

/*:457*/
#line 11183 "./typica.w"

}
return true;
}

/*:453*//*459:*/
#line 11321 "./typica.w"

XMLInput::XMLInput(QIODevice*input,int c):
firstc(c),in(input)
{

}

void XMLInput::setFirstColumn(int column)
{
firstc= column;
}

void XMLInput::setDevice(QIODevice*device)
{
in= device;
}

/*:459*/
#line 785 "./typica.w"

/*464:*/
#line 11410 "./typica.w"

bool CSVOutput::output()
{
if(!out->open(QIODevice::WriteOnly|QIODevice::Text))
{
return false;
}
QTextStream output(out);
/*465:*/
#line 11434 "./typica.w"

output<<"Time";
foreach(int c,temperatureColumns.keys())
{
output<<','<<temperatureColumns.value(c);
}
foreach(int c,annotationColumns.keys())
{
output<<','<<annotationColumns.value(c);
}
output<<'\n';

/*:465*/
#line 11418 "./typica.w"

bool oresult;
for(int i= 0;i<data->rowCount();i++)
{
/*448:*/
#line 11021 "./typica.w"

oresult= false;
foreach(int c,temperatureColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().isEmpty()))
{
oresult= true;
break;
}
}
if(oresult==false)
{
foreach(int c,annotationColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().
isEmpty()))
{
oresult= true;
break;
}
}
}

/*:448*/
#line 11422 "./typica.w"

if(oresult)
{
/*466:*/
#line 11455 "./typica.w"

output<<data->data(data->index(i,time),Qt::DisplayRole).toString();
foreach(int c,temperatureColumns.keys())
{
output<<','<<data->data(data->index(i,c),Qt::DisplayRole).toString();
}
foreach(int c,annotationColumns.keys())
{
output<<','<<data->data(data->index(i,c),Qt::DisplayRole).toString();
}
output<<'\n';

/*:466*/
#line 11425 "./typica.w"

}
}
out->close();
return true;
}

/*:464*//*467:*/
#line 11470 "./typica.w"

CSVOutput::CSVOutput(MeasurementModel*model,QIODevice*device,int timec):
data(model),out(device),time(timec)
{

}

void CSVOutput::setModel(MeasurementModel*model)
{
data= model;
}

void CSVOutput::setTimeColumn(int column)
{
time= column;
}

void CSVOutput::addTemperatureColumn(const QString&series,int column)
{
temperatureColumns.insert(column,series);
}

void CSVOutput::addAnnotationColumn(const QString&series,int column)
{
annotationColumns.insert(column,series);
}

void CSVOutput::setDevice(QIODevice*device)
{
out= device;
}

/*:467*/
#line 786 "./typica.w"

/*486:*/
#line 11852 "./typica.w"

QString SaltModel::arrayLiteral(int column,int role)const
{
QString literal= "'{";
for(int i= 0;i<rowCount();i++)
{
QString datum= data(index(i,column),role).toString();
if(!datum.isEmpty())
{
literal.append(datum);
literal.append(", ");
}
}
if(literal.size()> 2)
{
literal.chop(2);
}
literal.append("}'");
return literal;
}

QString SaltModel::quotedArrayLiteral(int column,int role)const
{
QString literal= "'{";
for(int i= 0;i<rowCount();i++)
{
QString datum= data(index(i,column),role).toString();
if(!datum.isEmpty())
{
literal.append("\"");
literal.append(datum);
literal.append("\", ");
}
}
if(literal.size()> 2)
{
literal.chop(2);
}
literal.append("}'");
return literal;
}

/*:486*//*487:*/
#line 11896 "./typica.w"

QModelIndex SaltModel::parent(const QModelIndex&)const
{
return QModelIndex();
}

/*:487*//*488:*/
#line 11915 "./typica.w"

bool SaltModel::setData(const QModelIndex&index,const QVariant&value,
int role)
{
/*489:*/
#line 11946 "./typica.w"

bool valid= false;
if(index.isValid())
{
if(index.row()<modelData.size())
{
if(index.column()<colcount)
{
valid= true;
}
}
}

/*:489*/
#line 11919 "./typica.w"

if(!valid)
{
return false;
}
if(index.row()==modelData.size()-1)
{
beginInsertRows(QModelIndex(),modelData.size(),modelData.size());
/*490:*/
#line 11962 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:490*/
#line 11927 "./typica.w"

endInsertRows();
}
QList<QMap<int,QVariant> > row= modelData.at(index.row());
QMap<int,QVariant> cell= row.at(index.column());
cell.insert(role,value);
if(role==Qt::EditRole)
{
cell.insert(Qt::DisplayRole,value);
}
row.replace(index.column(),cell);
modelData.replace(index.row(),row);
emit dataChanged(index,index);
return true;
}

/*:488*//*491:*/
#line 11973 "./typica.w"

SaltModel::SaltModel(int columns):QAbstractItemModel(),colcount(columns)
{
for(int i= 0;i<columns;i++)
{
hData<<"";
}
/*490:*/
#line 11962 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:490*/
#line 11980 "./typica.w"

}

/*:491*//*492:*/
#line 11985 "./typica.w"

SaltModel::~SaltModel()
{

}

/*:492*//*493:*/
#line 11995 "./typica.w"

int SaltModel::rowCount(const QModelIndex&parent)const
{
return(parent==QModelIndex()?modelData.size():0);
}

int SaltModel::columnCount(const QModelIndex&parent)const
{
return(parent==QModelIndex()?colcount:0);
}

/*:493*//*494:*/
#line 12008 "./typica.w"

bool SaltModel::setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int)
{
if(orientation==Qt::Horizontal&&section<colcount)
{
hData.replace(section,value.toString());
emit headerDataChanged(orientation,section,section);
return true;
}
return false;
}

/*:494*//*495:*/
#line 12023 "./typica.w"

QVariant SaltModel::data(const QModelIndex&index,int role)const
{
/*489:*/
#line 11946 "./typica.w"

bool valid= false;
if(index.isValid())
{
if(index.row()<modelData.size())
{
if(index.column()<colcount)
{
valid= true;
}
}
}

/*:489*/
#line 12026 "./typica.w"

if(!valid)
{
return QVariant();
}
QList<QMap<int,QVariant> > row= modelData.at(index.row());
QMap<int,QVariant> cell= row.at(index.column());
return cell.value(role,QVariant());
}

QVariant SaltModel::headerData(int section,Qt::Orientation orientation,
int role)const
{
if(orientation==Qt::Horizontal&&role==Qt::DisplayRole&&
section<colcount)
{
return QVariant(hData.at(section));
}
return QVariant();
}

/*:495*//*496:*/
#line 12050 "./typica.w"

Qt::ItemFlags SaltModel::flags(const QModelIndex&index)const
{
/*489:*/
#line 11946 "./typica.w"

bool valid= false;
if(index.isValid())
{
if(index.row()<modelData.size())
{
if(index.column()<colcount)
{
valid= true;
}
}
}

/*:489*/
#line 12053 "./typica.w"

if(valid)
{
return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
}
return 0;
}

/*:496*//*497:*/
#line 12064 "./typica.w"

QModelIndex SaltModel::index(int row,int column,
const QModelIndex&parent)const
{
if(parent==QModelIndex())
{
if(row<modelData.size()&&column<colcount)
{
return createIndex(row,column);
}
}
return QModelIndex();
}

/*:497*/
#line 787 "./typica.w"

/*499:*/
#line 12119 "./typica.w"

SqlComboBox*SqlComboBox::clone(QWidget*parent)
{
SqlComboBox*widget= new SqlComboBox();
widget->setParent(parent);
for(int i= 0;i<count();i++)
{
widget->addItem(itemText(i),itemData(i));
}
return widget;
}

/*:499*//*500:*/
#line 12136 "./typica.w"

void SqlComboBox::showData(bool show)
{
dataColumnShown= show;
}

/*:500*//*501:*/
#line 12147 "./typica.w"

void SqlComboBox::addNullOption()
{
addItem(tr("Unknown"),QVariant(QVariant::String));
}

/*:501*//*502:*/
#line 12160 "./typica.w"

void SqlComboBox::setDataColumn(int column)
{
dataColumn= column;
}

void SqlComboBox::setDisplayColumn(int column)
{
displayColumn= column;
}

/*:502*//*503:*/
#line 12174 "./typica.w"

void SqlComboBox::addSqlOptions(QString query)
{
SqlQueryConnection*dbquery= new SqlQueryConnection;
if(!dbquery->exec(query))
{
QSqlError error= dbquery->lastError();
qDebug()<<error.databaseText();
qDebug()<<error.driverText();
qDebug()<<error.text();
qDebug()<<dbquery->lastQuery();

}
while(dbquery->next())
{
QString displayValue(dbquery->value(displayColumn).toString());
QString dataValue(dbquery->value(dataColumn).toString());
if(dataColumnShown)
{
displayValue.append(QString(" (%1)").arg(dataValue));
}
addItem(displayValue,dataValue);
}
delete dbquery;
}

/*:503*//*504:*/
#line 12203 "./typica.w"

SqlComboBox::SqlComboBox():
dataColumn(0),displayColumn(0),dataColumnShown(false)
{

}

SqlComboBox::~SqlComboBox()
{

}

/*:504*/
#line 788 "./typica.w"

/*506:*/
#line 12241 "./typica.w"

void SqlComboBoxDelegate::setWidget(SqlComboBox*widget)
{
delegate= widget;
}

/*:506*//*507:*/
#line 12250 "./typica.w"

QWidget*SqlComboBoxDelegate::createEditor(QWidget*parent,
const QStyleOptionViewItem&,
const QModelIndex&)const
{
return delegate->clone(parent);
}

/*:507*//*508:*/
#line 12261 "./typica.w"

void SqlComboBoxDelegate::setEditorData(QWidget*editor,
const QModelIndex&index)const
{
SqlComboBox*self= qobject_cast<SqlComboBox*> (editor);
self->setCurrentIndex(self->findData(
index.model()->data(index,
Qt::UserRole).toString()));
}

/*:508*//*509:*/
#line 12274 "./typica.w"

void SqlComboBoxDelegate::setModelData(QWidget*editor,
QAbstractItemModel*model,
const QModelIndex&index)const
{
SqlComboBox*self= qobject_cast<SqlComboBox*> (editor);
model->setData(index,self->itemData(self->currentIndex(),Qt::UserRole),
Qt::UserRole);
model->setData(index,self->currentText(),Qt::DisplayRole);
}

/*:509*//*510:*/
#line 12287 "./typica.w"

void SqlComboBoxDelegate::updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&)const
{
editor->setGeometry(option.rect);
}

/*:510*//*511:*/
#line 12298 "./typica.w"

QSize SqlComboBoxDelegate::sizeHint()const
{
return delegate->sizeHint();
}

/*:511*//*512:*/
#line 12306 "./typica.w"

SqlComboBoxDelegate::SqlComboBoxDelegate(QObject*parent)
:QItemDelegate(parent)
{

}

/*:512*/
#line 789 "./typica.w"

/*478:*/
#line 11666 "./typica.w"

Application::Application(int&argc,char**argv):QApplication(argc,argv)
{
/*479:*/
#line 11681 "./typica.w"

setOrganizationName("Wilson's Coffee & Tea");
setOrganizationDomain("wilsonscoffee.com");
setApplicationName(PROGRAM_NAME);

/*:479*/
#line 11669 "./typica.w"

/*480:*/
#line 11690 "./typica.w"

QTranslator base;
if(base.load(QString("qt_%1").arg(QLocale::system().name())))
{
installTranslator(&base);
}
QTranslator app;
if(app.load(QString("%1_%2").arg("Typica").arg(QLocale::system().name())))
{
installTranslator(&app);
}

/*:480*/
#line 11670 "./typica.w"

/*218:*/
#line 5725 "./typica.w"

qRegisterMetaType<Measurement> ("Measurement");

/*:218*/
#line 11671 "./typica.w"

/*657:*/
#line 15386 "./typica.w"

NodeInserter*inserter= new NodeInserter(tr("NI DAQmx Base Device"),
tr("NI DAQmx Base"),
"nidaqmxbase",NULL);
topLevelNodeInserters.append(inserter);

/*:657*//*665:*/
#line 15603 "./typica.w"

#ifdef Q_OS_WIN32
inserter= new NodeInserter(tr("NI DAQmx Device"),tr("NI DAQmx"),"nidaqmx",NULL);
topLevelNodeInserters.append(inserter);
#endif

/*:665*//*689:*/
#line 16562 "./typica.w"

#if 0
inserter= new NodeInserter(tr("Modbus RTU Port"),tr("Modbus RTU Port"),"modbusrtuport",NULL);
topLevelNodeInserters.append(inserter);
#endif

/*:689*//*718:*/
#line 18012 "./typica.w"

inserter= new NodeInserter(tr("Modbus RTU Device"),tr("Modbus RTU Device"),"modbusrtu",NULL);
topLevelNodeInserters.append(inserter);

/*:718*/
#line 11672 "./typica.w"

}

/*:478*//*482:*/
#line 11713 "./typica.w"

QDomDocument*Application::configuration()
{
return&conf;
}

/*:482*//*483:*/
#line 11722 "./typica.w"

QSqlDatabase Application::database()
{
QString connectionName;
QSqlDatabase connection= QSqlDatabase::database();
do
{
connectionName= QUuid::createUuid().toString();
}while(QSqlDatabase::connectionNames().contains(connectionName));
return QSqlDatabase::cloneDatabase(connection,connectionName);
}

/*:483*//*593:*/
#line 14041 "./typica.w"

void Application::saveDeviceConfiguration()
{
QSettings settings;
settings.setValue("DeviceConfiguration",
QVariant(deviceConfigurationDocument.toByteArray()));
}

/*:593*//*594:*/
#line 14053 "./typica.w"

QDomDocument Application::deviceConfiguration()
{
if(deviceConfigurationDocument.isNull())
{
/*595:*/
#line 14067 "./typica.w"

QSettings settings;
QByteArray document= settings.value("DeviceConfiguration").toByteArray();
QString etext;
int eline;
int ecol;
if(document.length()==0)
{
qDebug()<<"Loaded settings length is 0. Creating new configuration.";
/*596:*/
#line 14091 "./typica.w"

QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument,false,
&etext,&eline,&ecol))
{
/*597:*/
#line 14108 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:597*/
#line 14097 "./typica.w"

}
else
{
saveDeviceConfiguration();
}

/*:596*/
#line 14076 "./typica.w"

}
else
{
if(!deviceConfigurationDocument.setContent(document,false,
&etext,&eline,&ecol))
{
/*597:*/
#line 14108 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:597*/
#line 14083 "./typica.w"

/*596:*/
#line 14091 "./typica.w"

QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument,false,
&etext,&eline,&ecol))
{
/*597:*/
#line 14108 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:597*/
#line 14097 "./typica.w"

}
else
{
saveDeviceConfiguration();
}

/*:596*/
#line 14084 "./typica.w"

}
}

/*:595*/
#line 14058 "./typica.w"

}
return deviceConfigurationDocument;
}

/*:594*//*625:*/
#line 14709 "./typica.w"

void Application::registerDeviceConfigurationWidget(QString driver,
QMetaObject widget)
{
deviceConfigurationWidgets.insert(driver,widget);
}

/*:625*//*626:*/
#line 14725 "./typica.w"

QWidget*Application::deviceConfigurationWidget(DeviceTreeModel*model,
const QModelIndex&index)
{
QVariant nodeReference= index.data(Qt::UserRole);
QDomElement referenceElement= model->referenceElement(
model->data(index,Qt::UserRole).toString());
QMetaObject metaObject= 
deviceConfigurationWidgets.value(referenceElement.attribute("driver"),
QWidget::staticMetaObject);
QWidget*editor;
if(metaObject.className()==QWidget::staticMetaObject.className())
{
editor= NULL;
}
else
{
editor= qobject_cast<QWidget*> (
metaObject.newInstance(Q_ARG(DeviceTreeModel*,model),
Q_ARG(QModelIndex,index)));
}
return editor;
}

/*:626*/
#line 790 "./typica.w"

/*517:*/
#line 12401 "./typica.w"

SqlConnectionSetup::SqlConnectionSetup():
formLayout(new QFormLayout),driver(new QComboBox),hostname(new QLineEdit),
dbname(new QLineEdit),user(new QLineEdit),password(new QLineEdit),
layout(new QVBoxLayout),buttons(new QHBoxLayout),
cancelButton(new QPushButton(tr("Cancel"))),
connectButton(new QPushButton(tr("Connect")))
{
driver->addItem("PostgreSQL","QPSQL");
formLayout->addRow(tr("Database driver:"),driver);
formLayout->addRow(tr("Host name:"),hostname);
formLayout->addRow(tr("Database name:"),dbname);
formLayout->addRow(tr("User name:"),user);
password->setEchoMode(QLineEdit::Password);
formLayout->addRow(tr("Password:"),password);
layout->addLayout(formLayout);
buttons->addStretch(1);
buttons->addWidget(cancelButton);
connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
buttons->addWidget(connectButton);
layout->addLayout(buttons);
connect(connectButton,SIGNAL(clicked(bool)),this,SLOT(testConnection()));
setLayout(layout);
setModal(true);
}

SqlConnectionSetup::~SqlConnectionSetup()
{

}

/*:517*//*518:*/
#line 12435 "./typica.w"

void SqlConnectionSetup::testConnection()
{
QSqlDatabase database= 
QSqlDatabase::addDatabase(driver->itemData(driver->currentIndex()).
toString());
database.setHostName(hostname->text());
database.setDatabaseName(dbname->text());
database.setUserName(user->text());
database.setPassword(password->text());
if(database.open())
{
QSettings settings;
settings.setValue("database/exists","true");
settings.setValue("database/driver",
driver->itemData(driver->currentIndex()).toString());
settings.setValue("database/hostname",hostname->text());
settings.setValue("database/dbname",dbname->text());
settings.setValue("database/user",user->text());
settings.setValue("database/password",password->text());
accept();
}
else
{
QMessageBox::information(this,tr("Database connection failed"),
tr("Failed to connect to database."));
}
}

/*:518*/
#line 791 "./typica.w"

/*522:*/
#line 12530 "./typica.w"

SqlQueryView::SqlQueryView(QWidget*parent):QTableView(parent)
{
setModel(new QSqlQueryModel);
connect(this,SIGNAL(doubleClicked(QModelIndex)),
this,SLOT(openRow(QModelIndex)));
connect(horizontalHeader(),SIGNAL(sectionResized(int,int,int)),
this,SLOT(persistColumnResize(int,int,int)));
}

/*:522*//*523:*/
#line 12545 "./typica.w"

void SqlQueryView::persistColumnResize(int column,int,int newsize)
{
/*524:*/
#line 12554 "./typica.w"

QSettings settings;
/*525:*/
#line 12567 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:525*/
#line 12556 "./typica.w"

settings.setValue(QString("columnWidths/%1/%2/%3").
arg(topLevelWidget->objectName()).
arg(objectName()).arg(column),
QVariant(newsize));

/*:524*/
#line 12548 "./typica.w"

}

/*:523*//*526:*/
#line 12577 "./typica.w"

void SqlQueryView::showEvent(QShowEvent*event)
{
/*527:*/
#line 12587 "./typica.w"

QSettings settings;
/*525:*/
#line 12567 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:525*/
#line 12589 "./typica.w"

QString baseKey= 
QString("columnWidths/%1/%2").arg(topLevelWidget->objectName()).
arg(objectName());
for(int i= 0;i<model()->columnCount();i++)
{
QString key= QString("%1/%2").arg(baseKey).arg(i);
if(settings.contains(key))
{
setColumnWidth(i,settings.value(key).toInt());
}
}

/*:527*/
#line 12580 "./typica.w"

event->accept();
}

/*:526*//*528:*/
#line 12604 "./typica.w"

void SqlQueryView::openRow(const QModelIndex&index)
{
emit openEntry(((QSqlQueryModel*)model())->record(index.row()).value(0).toString());
emit openEntryRow(index.row());
}

/*:528*//*529:*/
#line 12615 "./typica.w"

void SqlQueryView::setQuery(const QString&query)
{
QSqlDatabase database= AppInstance->database();
database.open();
QSqlQuery q(query,database);
((QSqlQueryModel*)model())->setQuery(q);
}

bool SqlQueryView::setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int role)
{
return model()->setHeaderData(section,orientation,value,role);
}

/*:529*//*530:*/
#line 12632 "./typica.w"

QVariant SqlQueryView::data(int row,int column,int role)
{
return model()->data(model()->index(row,column),role);
}

/*:530*/
#line 792 "./typica.w"

/*135:*/
#line 3270 "./typica.w"

SqlQueryConnection::SqlQueryConnection(const QString&query)
{
QSqlDatabase database= AppInstance->database();
database.open();
q= new QSqlQuery(query,database);
connection= database.connectionName();
}

/*:135*//*136:*/
#line 3283 "./typica.w"

SqlQueryConnection::~SqlQueryConnection()
{
delete q;
{
QSqlDatabase database= QSqlDatabase::database(connection);
database.close();
}
QSqlDatabase::removeDatabase(connection);
}

/*:136*//*137:*/
#line 3297 "./typica.w"

QSqlQuery*SqlQueryConnection::operator->()
{
return q;
}

/*:137*/
#line 793 "./typica.w"

/*549:*/
#line 12981 "./typica.w"

ReportTable::ReportTable(QTextFrame*frame,QDomElement description):
area(frame),configuration(description)
{
refresh();
}

ReportTable::~ReportTable()
{

}

/*:549*//*550:*/
#line 12997 "./typica.w"

void ReportTable::bind(QString placeholder,QVariant value)
{
bindings.insert(placeholder,value);
}

/*:550*//*551:*/
#line 13007 "./typica.w"

void ReportTable::refresh()
{
/*552:*/
#line 13028 "./typica.w"

QTextCursor cursor= area->firstCursorPosition();
while(cursor<area->lastCursorPosition())
{
cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
}
cursor.removeSelectedText();

/*:552*/
#line 13010 "./typica.w"

int rows= 1;
int columns= 1;
int currentRow= 0;
QTextTable*table= cursor.insertTable(rows,columns);
/*553:*/
#line 13041 "./typica.w"

QTextTableFormat format= table->format();
format.setBorderStyle(QTextFrameFormat::BorderStyle_None);
if(configuration.hasAttribute("align"))
{
if(configuration.attribute("align")=="center")
{
format.setAlignment(Qt::AlignHCenter);
}
}
table->setFormat(format);

/*:553*/
#line 13015 "./typica.w"

/*554:*/
#line 13055 "./typica.w"

QDomNodeList children= configuration.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="query")
{
/*555:*/
#line 13082 "./typica.w"

SqlQueryConnection query;
query.prepare(currentElement.text());
foreach(QString key,bindings.uniqueKeys())
{
if(currentElement.text().contains(key))
{
query.bindValue(key,bindings.value(key));
}
}
query.exec();
if(!query.next())
{
continue;
}
if(query.record().count()> columns)
{
table->appendColumns(query.record().count()-columns);
}
do
{
table->appendRows(1);
rows++;
currentRow++;
for(int j= 0;j<query.record().count();j++)
{
QTextTableCell cell= table->cellAt(currentRow,j);
cursor= cell.firstCursorPosition();
cursor.insertText(query.value(j).toString());
}
}while(query.next());

/*:555*/
#line 13067 "./typica.w"

}
else if(currentElement.tagName()=="row")
{
/*556:*/
#line 13121 "./typica.w"

table->appendRows(1);
currentRow++;
rows++;
QDomNodeList rowChildren= currentElement.childNodes();
int currentColumn= 0;
for(int j= 0;j<rowChildren.count();j++)
{
QDomNode node;
QDomElement nodeElement;
node= rowChildren.at(j);
if(node.isElement())
{
nodeElement= node.toElement();
if(nodeElement.tagName()=="cell")
{
if(currentColumn==columns)
{
table->appendColumns(1);
columns++;
}
QTextTableCell cell= table->cellAt(currentRow,currentColumn);
cursor= cell.firstCursorPosition();
cursor.insertText(nodeElement.text());
currentColumn++;
}
}
}

/*:556*/
#line 13071 "./typica.w"

}
}
}

/*:554*/
#line 13016 "./typica.w"

if(rows> 1)
{
table->removeRows(0,1);
}
}

/*:551*/
#line 794 "./typica.w"

/*561:*/
#line 13223 "./typica.w"

FormArray::FormArray(QDomElement description):configuration(description),
maxwidth(-1),maxheight(-1)
{
setWidget(&itemContainer);
itemContainer.setLayout(&itemLayout);
}

/*:561*//*562:*/
#line 13240 "./typica.w"

void FormArray::addElements(int copies)
{
QStack<QWidget*> *widgetStack= new QStack<QWidget*> ;
QStack<QLayout*> *layoutStack= new QStack<QLayout*> ;
QWidget*widget;
for(int i= 0;i<copies;i++)
{
widget= new QWidget;
if(maxwidth> -1)
{
widget->setMaximumWidth(maxwidth);
}
if(maxheight> -1)
{
widget->setMaximumHeight(maxheight);
}
if(configuration.hasChildNodes())
{
widgetStack->push(widget);
populateWidget(configuration,widgetStack,layoutStack);
widgetStack->pop();
widget->setMinimumHeight(widget->sizeHint().height());
itemLayout.addWidget(widget);
if(widget->sizeHint().height()> maxheight&&maxheight> -1)
{
itemContainer.setMinimumHeight(maxheight*elements()+50);
}
else
{
itemContainer.setMinimumHeight(itemContainer.sizeHint().height()
+widget->sizeHint().height());
}
if(maxwidth> -1)
{
itemContainer.setMinimumWidth(maxwidth+50);
}
else
{
itemContainer.setMinimumWidth(widget->sizeHint().width()+50);
}
}
}
}

/*:562*//*563:*/
#line 13290 "./typica.w"

QWidget*FormArray::elementAt(int index)
{
if(index<itemLayout.count())
{
QLayoutItem*item= itemLayout.itemAt(index);
return item->widget();
}
else
{
return NULL;
}
}

/*:563*//*564:*/
#line 13307 "./typica.w"

void FormArray::removeAllElements()
{
while(itemLayout.count()> 0)
{
QLayoutItem*item;
item= itemLayout.itemAt(0);
item->widget()->hide();
itemLayout.removeWidget(item->widget());
}
itemContainer.setMinimumHeight(0);
}

/*:564*//*565:*/
#line 13323 "./typica.w"

int FormArray::elements()
{
return itemLayout.count();
}

/*:565*//*566:*/
#line 13334 "./typica.w"

void FormArray::setMaximumElementWidth(int width)
{
maxwidth= width;
}

void FormArray::setMaximumElementHeight(int height)
{
maxheight= height;
}

/*:566*/
#line 795 "./typica.w"

/*572:*/
#line 13465 "./typica.w"

ScaleControl::ScaleControl():QGraphicsView(NULL,NULL),nonScoredValue(-1),
scoredValue(-1),initialSet(false),finalSet(false),scaleDown(false)
{
left<<QPointF(0,5)<<QPointF(10,0)<<QPointF(10,10)<<
QPointF(0,5);
right<<QPointF(10,5)<<QPointF(0,0)<<QPointF(0,10)<<
QPointF(10,5);
down<<QPointF(0,0)<<QPointF(-5,-10)<<QPointF(5,-10)<<
QPointF(0,0);
up<<QPointF(0,0)<<QPointF(-5,10)<<QPointF(4,10)<<QPointF(0,0);
initialBrush.setColor(QColor(170,170,255));
initialBrush.setStyle(Qt::SolidPattern);
finalBrush.setColor(Qt::blue);
finalBrush.setStyle(Qt::SolidPattern);
initialDecrement.setPolygon(left);
initialDecrement.setBrush(initialBrush);
initialDecrement.setPos(0,0);
scene.addItem(&initialDecrement);
initialIncrement.setPolygon(right);
initialIncrement.setBrush(initialBrush);
initialIncrement.setPos(122,0);
scene.addItem(&initialIncrement);
finalDecrement.setPolygon(left);
finalDecrement.setBrush(finalBrush);
finalDecrement.setPos(0,12);
scene.addItem(&finalDecrement);
finalIncrement.setPolygon(right);
finalIncrement.setBrush(finalBrush);
finalIncrement.setPos(122,12);
scene.addItem(&finalIncrement);
scalePath.moveTo(0,10);
scalePath.lineTo(100,10);
scalePath.moveTo(0,0);
scalePath.lineTo(0,20);
scalePath.moveTo(10,5);
scalePath.lineTo(10,15);
scalePath.moveTo(20,5);
scalePath.lineTo(20,15);
scalePath.moveTo(30,5);
scalePath.lineTo(30,15);
scalePath.moveTo(40,5);
scalePath.lineTo(40,15);
scalePath.moveTo(50,0);
scalePath.lineTo(50,20);
scalePath.moveTo(60,5);
scalePath.lineTo(60,15);
scalePath.moveTo(70,5);
scalePath.lineTo(70,15);
scalePath.moveTo(80,5);
scalePath.lineTo(80,15);
scalePath.moveTo(90,5);
scalePath.lineTo(90,15);
scalePath.moveTo(100,0);
scalePath.lineTo(100,20);
scaleLine.setPath(scalePath);
scaleLine.setPos(16,1);
scene.addItem(&scaleLine);
setScene(&scene);
initialIndicator.setPolygon(down);
initialIndicator.setBrush(initialBrush);
finalIndicator.setPolygon(up);
finalIndicator.setBrush(finalBrush);
setMinimumSize(sizeHint());
setMaximumSize(sizeHint());
setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setMinimumSize(sizeHint());
}

/*:572*//*573:*/
#line 13538 "./typica.w"

QSize ScaleControl::sizeHint()const
{
return QSize(140,30);
}

/*:573*//*574:*/
#line 13547 "./typica.w"

void ScaleControl::setInitialValue(double value)
{
if(value>=0&&value<=10)
{
nonScoredValue= value;
if(!initialSet)
{
scene.addItem(&initialIndicator);
}
initialSet= true;
initialIndicator.setPos(value*10+16,10);
emit initialChanged(value);
if(!finalSet)
{
setFinalValue(value);
}
}
}

void ScaleControl::setFinalValue(double value)
{
if(value>=0&&value<=10)
{
scoredValue= value;
if(!finalSet)
{
scene.addItem(&finalIndicator);
}
finalSet= true;
finalIndicator.setPos(value*10+16,11);
emit finalChanged(value);
}
}

/*:574*//*575:*/
#line 13584 "./typica.w"

double ScaleControl::initialValue(void)
{
return nonScoredValue;
}

double ScaleControl::finalValue(void)
{
return scoredValue;
}

/*:575*//*576:*/
#line 13605 "./typica.w"

void ScaleControl::mousePressEvent(QMouseEvent*event)
{
/*577:*/
#line 13617 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:577*/
#line 13608 "./typica.w"

scaleDown= true;
event->accept();
}

/*:576*//*578:*/
#line 13628 "./typica.w"

void ScaleControl::mouseReleaseEvent(QMouseEvent*event)
{
/*577:*/
#line 13617 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:577*/
#line 13631 "./typica.w"

if(!scaleDown)
{
event->ignore();
return;
}
scaleDown= false;
QPointF sceneCoordinate= mapToScene(event->x(),event->y());
/*579:*/
#line 13653 "./typica.w"

if(sceneCoordinate.x()>=0&&sceneCoordinate.x()<=10)
{
if(sceneCoordinate.y()>=0&&sceneCoordinate.y()<=10)
{
if(initialSet)
{
setInitialValue(nonScoredValue-0.05);
}
event->accept();
return;
}
else if(sceneCoordinate.y()>=12&&sceneCoordinate.y()<=22)
{
if(finalSet)
{
setFinalValue(scoredValue-0.05);
event->accept();
return;
}
}
}

/*:579*/
#line 13639 "./typica.w"

/*580:*/
#line 13679 "./typica.w"

else if(sceneCoordinate.x()>=122&&sceneCoordinate.x()<=132)
{
if(sceneCoordinate.y()>=0&&sceneCoordinate.y()<=10)
{
if(initialSet)
{
setInitialValue(nonScoredValue+0.05);
event->accept();
return;
}
}
else if(sceneCoordinate.y()>=12&&sceneCoordinate.y()<=22)
{
if(finalSet)
{
setFinalValue(scoredValue+0.05);
event->accept();
return;
}
}
}

/*:580*/
#line 13640 "./typica.w"

/*581:*/
#line 13705 "./typica.w"

double relativeX= sceneCoordinate.x()-16;
if(initialSet)
{
if(relativeX>=0&&relativeX<=100)
{
setFinalValue(relativeX/10.0);
event->accept();
return;
}
}
else
{
if(relativeX>=0&&relativeX<=100)
{
setInitialValue(relativeX/10.0);
event->accept();
return;
}
}

/*:581*/
#line 13641 "./typica.w"

event->ignore();
return;
}

/*:578*/
#line 796 "./typica.w"

/*583:*/
#line 13771 "./typica.w"

IntensityControl::IntensityControl():QGraphicsView(NULL,NULL),theValue(-1),
valueSet(false),scaleDown(false)
{
setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
left<<QPointF(0,0)<<QPointF(10,-5)<<QPointF(10,5)<<QPointF(0,0);
down<<QPointF(0,0)<<QPointF(10,0)<<QPointF(5,10)<<QPointF(0,0);
up<<QPointF(0,10)<<QPointF(10,10)<<QPointF(5,0)<<QPointF(0,10);
theBrush.setColor(Qt::blue);
theBrush.setStyle(Qt::SolidPattern);
increment.setPolygon(up);
increment.setBrush(theBrush);
increment.setPos(0,0);
scene.addItem(&increment);
decrement.setPolygon(down);
decrement.setBrush(theBrush);
decrement.setPos(0,122);
scene.addItem(&decrement);
scalePath.moveTo(5,0);
scalePath.lineTo(5,100);
scalePath.moveTo(0,0);
scalePath.lineTo(10,0);
scalePath.moveTo(0,10);
scalePath.lineTo(10,10);
scalePath.moveTo(0,20);
scalePath.lineTo(10,20);
scalePath.moveTo(0,30);
scalePath.lineTo(10,30);
scalePath.moveTo(0,40);
scalePath.lineTo(10,40);
scalePath.moveTo(0,50);
scalePath.lineTo(10,50);
scalePath.moveTo(0,60);
scalePath.lineTo(10,60);
scalePath.moveTo(0,70);
scalePath.lineTo(10,70);
scalePath.moveTo(0,80);
scalePath.lineTo(10,80);
scalePath.moveTo(0,90);
scalePath.lineTo(10,90);
scalePath.moveTo(0,100);
scalePath.lineTo(10,100);
scaleLine.setPath(scalePath);
scaleLine.setPos(0,16);
scene.addItem(&scaleLine);
setScene(&scene);
indicator.setPolygon(left);
indicator.setBrush(theBrush);
setMinimumSize(sizeHint());
setMaximumSize(sizeHint());
}

/*:583*//*584:*/
#line 13826 "./typica.w"

QSize IntensityControl::sizeHint()const
{
return QSize(25,160);
}

/*:584*//*585:*/
#line 13841 "./typica.w"

void IntensityControl::setValue(double val)
{
if(val>=0&&val<=10)
{
theValue= val;
if(!valueSet)
{
scene.addItem(&indicator);
}
valueSet= true;
indicator.setPos(6,(100-(val*10))+16);
emit(valueChanged(val));
}
else if(val<1)
{
setValue(0);
}
else
{
setValue(10);
}
}

double IntensityControl::value()
{
return theValue;
}

/*:585*//*586:*/
#line 13873 "./typica.w"

void IntensityControl::mousePressEvent(QMouseEvent*event)
{
/*577:*/
#line 13617 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:577*/
#line 13876 "./typica.w"

scaleDown= true;
event->accept();
}

/*:586*//*587:*/
#line 13887 "./typica.w"

void IntensityControl::mouseReleaseEvent(QMouseEvent*event)
{
/*577:*/
#line 13617 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:577*/
#line 13890 "./typica.w"

if(!scaleDown)
{
event->ignore();
return;
}
scaleDown= false;
QPointF sceneCoordinate= mapToScene(event->x(),event->y());
if(sceneCoordinate.x()>=0&&sceneCoordinate.x()<=16)
{
if(sceneCoordinate.y()>=0&&sceneCoordinate.y()<=10)
{
if(valueSet)
{
setValue(theValue+0.05);
}
event->accept();
return;
}
else if(sceneCoordinate.y()>=122&&sceneCoordinate.y()<=132)
{
if(valueSet)
{
setValue(theValue-0.05);
}
event->accept();
return;
}
else if(sceneCoordinate.y()>=16&&sceneCoordinate.y()<=116)
{
setValue(10-((sceneCoordinate.y()-16)/10.0));
event->accept();
return;
}
}
}

/*:587*/
#line 797 "./typica.w"

/*287:*/
#line 7475 "./typica.w"

void ThresholdDetector::newMeasurement(Measurement measure)
{
if((currentDirection==Ascending&&previousValue<threshold&&
previousValue>=0)||(currentDirection==Descending&&
previousValue> threshold&&previousValue>=0))
{
if((currentDirection==Ascending&&measure.temperature()>=threshold)||
(currentDirection==Descending&&measure.temperature()<=threshold))
{
double offset= measure.time().hour()*60*60;
offset+= measure.time().minute()*60;
offset+= measure.time().second();
offset+= measure.time().msec()/1000;
emit timeForValue(offset);
}
}
previousValue= measure.temperature();
}

ThresholdDetector::ThresholdDetector(double value):QObject(NULL),
previousValue(-1),threshold(value),currentDirection(Ascending)
{

}

void ThresholdDetector::setThreshold(double value)
{
threshold= value;
}

void ThresholdDetector::setEdgeDirection(EdgeDirection direction)
{
currentDirection= direction;
}

/*:287*/
#line 798 "./typica.w"

/*668:*/
#line 15643 "./typica.w"

PortSelector::PortSelector(QWidget*parent):QComboBox(parent),
lister(new QextSerialEnumerator)
{
QList<QextPortInfo> ports= QextSerialEnumerator::getPorts();
QextPortInfo port;
foreach(port,ports)
{
addItem(port.portName);
}
lister->setUpNotifications();
connect(lister,SIGNAL(deviceDiscovered(QextPortInfo)),
this,SLOT(addDevice(QextPortInfo)));
setEditable(true);
}

void PortSelector::addDevice(QextPortInfo port)
{
addItem(port.portName);
}

/*:668*/
#line 799 "./typica.w"

/*670:*/
#line 15731 "./typica.w"

BaudSelector::BaudSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= BaudSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("BaudRateType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString("%1").arg(type.value(i)));
}
}

/*:670*/
#line 800 "./typica.w"

/*672:*/
#line 15769 "./typica.w"

ParitySelector::ParitySelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= ParitySelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("ParityType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:672*/
#line 801 "./typica.w"

/*674:*/
#line 15799 "./typica.w"

FlowSelector::FlowSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= FlowSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("FlowType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:674*/
#line 802 "./typica.w"

/*676:*/
#line 15834 "./typica.w"

StopSelector::StopSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= StopSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("StopBitsType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:676*/
#line 803 "./typica.w"

/*716:*/
#line 17579 "./typica.w"

ModbusConfigurator::ModbusConfigurator(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
port(new PortSelector),baud(new BaudSelector),parity(new ParitySelector),
flow(new FlowSelector),stop(new StopSelector),station(new QSpinBox),
decimalQuery(new QCheckBox(tr("Enable"))),
decimalAddress(new ShortHexSpinBox),decimalPosition(new QSpinBox),
unitQuery(new QCheckBox(tr("Enable"))),
unitAddress(new ShortHexSpinBox),valueF(new QSpinBox),
valueC(new QSpinBox),fixedUnit(new QComboBox),
pVAddress(new ShortHexSpinBox),
sVEnabled(new QCheckBox(tr("Enable"))),
sVReadAddress(new ShortHexSpinBox),
deviceLimit(new QCheckBox(tr("Enable"))),
sVLowerAddr(new ShortHexSpinBox),sVUpperAddr(new ShortHexSpinBox),
sVLower(new QDoubleSpinBox),sVUpper(new QDoubleSpinBox),
sVWritable(new QCheckBox(tr("Enable"))),
sVOutputAddr(new ShortHexSpinBox),
pVColumnName(new QLineEdit),sVColumnName(new QLineEdit)
{
QHBoxLayout*layout= new QHBoxLayout;
QWidget*form= new QWidget;
QHBoxLayout*masterLayout= new QHBoxLayout;
QVBoxLayout*portAndDeviceLayout= new QVBoxLayout;
QVBoxLayout*seriesLayout= new QVBoxLayout;
QFormLayout*serialSection= new QFormLayout;
serialSection->addRow(QString(tr("Port:")),port);
serialSection->addRow(QString(tr("Baud rate:")),baud);
serialSection->addRow(QString(tr("Parity:")),parity);
serialSection->addRow(QString(tr("Flow control:")),flow);
serialSection->addRow(QString(tr("Stop bits:")),stop);
QGroupBox*serialSectionBox= new QGroupBox(tr("Serial Port Configuration"));
serialSectionBox->setLayout(serialSection);
portAndDeviceLayout->addWidget(serialSectionBox);
QFormLayout*deviceSection= new QFormLayout;
station->setMinimum(1);
station->setMaximum(255);
decimalPosition->setMinimum(0);
decimalPosition->setMaximum(9);
valueF->setMinimum(0);
valueF->setMaximum(0xFFFF);
valueC->setMinimum(0);
valueC->setMaximum(0xFFFF);
fixedUnit->addItem(tr("Fahrenheit"),QVariant(QString("F")));
fixedUnit->addItem(tr("Celsius"),QVariant(QString("C")));
deviceSection->addRow(tr("Station:"),station);
deviceSection->addRow(tr("Decimal position from device:"),decimalQuery);
deviceSection->addRow(tr("Decimal position relative address:"),decimalAddress);
deviceSection->addRow(tr("Fixed decimal position:"),decimalPosition);
deviceSection->addRow(tr("Measurement unit from device:"),unitQuery);
deviceSection->addRow(tr("Current unit relative address:"),unitAddress);
deviceSection->addRow(tr("Value for Fahrenheit:"),valueF);
deviceSection->addRow(tr("Value for Celsius:"),valueC);
deviceSection->addRow(tr("Fixed unit:"),fixedUnit);
QGroupBox*deviceSectionBox= new QGroupBox(tr("Device Configuration"));
deviceSectionBox->setLayout(deviceSection);
portAndDeviceLayout->addWidget(deviceSectionBox);
QFormLayout*pVSection= new QFormLayout;
pVSection->addRow(tr("Value relative address:"),pVAddress);
pVSection->addRow(tr("PV column name:"),pVColumnName);
QGroupBox*processValueBox= new QGroupBox(tr("Process Value"));
processValueBox->setLayout(pVSection);
seriesLayout->addWidget(processValueBox);
QFormLayout*sVSection= new QFormLayout;
sVLower->setDecimals(1);
sVLower->setMinimum(0.0);
sVLower->setMaximum(999.9);
sVUpper->setDecimals(1);
sVUpper->setMinimum(0.0);
sVUpper->setMaximum(999.9);
sVSection->addRow(tr("Set value:"),sVEnabled);
sVSection->addRow(tr("Read relative address:"),sVReadAddress);
sVSection->addRow(tr("SV column name:"),sVColumnName);
sVSection->addRow(tr("Limits from device:"),deviceLimit);
sVSection->addRow(tr("Lower limit relative address:"),sVLowerAddr);
sVSection->addRow(tr("Upper limit relative address:"),sVUpperAddr);
sVSection->addRow(tr("Lower limit:"),sVLower);
sVSection->addRow(tr("Upper limit:"),sVUpper);
sVSection->addRow(tr("Output set value:"),sVWritable);
sVSection->addRow(tr("Output relative address:"),sVOutputAddr);
QGroupBox*setValueBox= new QGroupBox(tr("Set Value"));
setValueBox->setLayout(sVSection);
seriesLayout->addWidget(setValueBox);
masterLayout->addLayout(portAndDeviceLayout);
masterLayout->addLayout(seriesLayout);
form->setLayout(masterLayout);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 17665 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="port")
{
QString portname= node.attribute("value");
int idx= port->findText(portname);
if(idx>=0)
{
port->setCurrentIndex(idx);
}
else
{
port->addItem(portname);
}
}
else if(node.attribute("name")=="baud")
{
baud->setCurrentIndex(baud->findText(node.attribute("value")));
}
else if(node.attribute("name")=="parity")
{
parity->setCurrentIndex(parity->findData(node.attribute("value")));
}
else if(node.attribute("name")=="flow")
{
flow->setCurrentIndex(flow->findData(node.attribute("value")));
}
else if(node.attribute("name")=="stop")
{
stop->setCurrentIndex(stop->findData(node.attribute("value")));
}
else if(node.attribute("name")=="station")
{
station->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="decimalQuery")
{
if(node.attribute("value")=="true")
{
decimalQuery->setChecked(true);
}
else
{
decimalQuery->setChecked(false);
}
}
else if(node.attribute("name")=="decimalAddress")
{
decimalAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="decimalPosition")
{
decimalPosition->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="unitQuery")
{
if(node.attribute("value")=="true")
{
unitQuery->setChecked(true);
}
else
{
unitQuery->setChecked(false);
}
}
else if(node.attribute("name")=="unitAddress")
{
unitAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="valueF")
{
valueF->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="valueC")
{
valueC->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="fixedUnit")
{
fixedUnit->setCurrentIndex(fixedUnit->findText(node.attribute("value")));
}
else if(node.attribute("name")=="pVAddress")
{
pVAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="sVEnabled")
{
if(node.attribute("value")=="true")
{
sVEnabled->setChecked(true);
}
else
{
sVEnabled->setChecked(false);
}
}
else if(node.attribute("name")=="sVReadAddress")
{
sVReadAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="deviceLimit")
{
if(node.attribute("value")=="true")
{
deviceLimit->setChecked(true);
}
else
{
deviceLimit->setChecked(false);
}
}
else if(node.attribute("name")=="sVLowerAddr")
{
sVLowerAddr->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="sVUpperAddr")
{
sVUpperAddr->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="sVLower")
{
sVLower->setValue(node.attribute("value").toDouble());
}
else if(node.attribute("name")=="sVUpper")
{
sVUpper->setValue(node.attribute("value").toDouble());
}
else if(node.attribute("name")=="sVWritable")
{
if(node.attribute("value")=="true")
{
sVWritable->setChecked(true);
}
else
{
sVWritable->setChecked(false);
}
}
else if(node.attribute("name")=="sVOutputAddr")
{
sVOutputAddr->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="pvcolname")
{
pVColumnName->setText(node.attribute("value"));
}
else if(node.attribute("name")=="svcolname")
{
sVColumnName->setText(node.attribute("value"));
}
}
updatePort(port->currentText());
updateBaudRate(baud->currentText());
updateParity(parity->itemData(parity->currentIndex()).toString());
updateFlowControl(flow->itemData(flow->currentIndex()).toString());
updateStopBits(stop->itemData(stop->currentIndex()).toString());
updateStation(station->value());
updateFixedDecimal(decimalQuery->isChecked());
updateDecimalAddress(decimalAddress->value());
updateDecimalPosition(decimalPosition->value());
updateFixedUnit(unitQuery->isChecked());
updateUnitAddress(unitAddress->value());
updateValueForF(valueF->value());
updateValueForC(valueC->value());
updateUnit(fixedUnit->currentText());
updatePVAddress(pVAddress->value());
updateSVEnabled(sVEnabled->isChecked());
updateSVReadAddress(sVReadAddress->value());
updateDeviceLimit(deviceLimit->isChecked());
updateSVLowerAddress(sVLowerAddr->value());
updateSVUpperAddress(sVUpperAddr->value());
updateSVLower(sVLower->value());
updateSVUpper(sVUpper->value());
updateSVWritable(sVWritable->isChecked());
updateSVWriteAddress(sVOutputAddr->value());
updatePVColumnName(pVColumnName->text());
updateSVColumnName(sVColumnName->text());
connect(port,SIGNAL(currentIndexChanged(QString)),this,SLOT(updatePort(QString)));
connect(port,SIGNAL(editTextChanged(QString)),this,SLOT(updatePort(QString)));
connect(baud,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateBaudRate(QString)));
connect(parity,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateParity(QString)));
connect(flow,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFlowControl(QString)));
connect(stop,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateStopBits(QString)));
connect(station,SIGNAL(valueChanged(int)),this,SLOT(updateStation(int)));
connect(decimalQuery,SIGNAL(toggled(bool)),this,SLOT(updateFixedDecimal(bool)));
connect(decimalAddress,SIGNAL(valueChanged(int)),this,SLOT(updateDecimalAddress(int)));
connect(decimalPosition,SIGNAL(valueChanged(int)),this,SLOT(updateDecimalPosition(int)));
connect(unitQuery,SIGNAL(toggled(bool)),this,SLOT(updateFixedUnit(bool)));
connect(unitAddress,SIGNAL(valueChanged(int)),this,SLOT(updateUnitAddress(int)));
connect(valueF,SIGNAL(valueChanged(int)),this,SLOT(updateValueForF(int)));
connect(valueC,SIGNAL(valueChanged(int)),this,SLOT(updateValueForC(int)));
connect(fixedUnit,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateUnit(QString)));
connect(pVAddress,SIGNAL(valueChanged(int)),this,SLOT(updatePVAddress(int)));
connect(sVEnabled,SIGNAL(toggled(bool)),this,SLOT(updateSVEnabled(bool)));
connect(sVReadAddress,SIGNAL(valueChanged(int)),this,SLOT(updateSVReadAddress(int)));
connect(deviceLimit,SIGNAL(toggled(bool)),this,SLOT(updateDeviceLimit(bool)));
connect(sVLowerAddr,SIGNAL(valueChanged(int)),this,SLOT(updateSVLowerAddress(int)));
connect(sVUpperAddr,SIGNAL(valueChanged(int)),this,SLOT(updateSVUpperAddress(int)));
connect(sVLower,SIGNAL(valueChanged(double)),this,SLOT(updateSVLower(double)));
connect(sVUpper,SIGNAL(valueChanged(double)),this,SLOT(updateSVUpper(double)));
connect(sVWritable,SIGNAL(toggled(bool)),this,SLOT(updateSVWritable(bool)));
connect(sVOutputAddr,SIGNAL(valueChanged(int)),this,SLOT(updateSVWriteAddress(int)));
connect(pVColumnName,SIGNAL(textEdited(QString)),this,SLOT(updatePVColumnName(QString)));
connect(sVColumnName,SIGNAL(textEdited(QString)),this,SLOT(updateSVColumnName(QString)));
layout->addWidget(form);
setLayout(layout);
}

void ModbusConfigurator::updatePort(const QString&newPort)
{
updateAttribute("port",newPort);
}

void ModbusConfigurator::updateBaudRate(const QString&newRate)
{
updateAttribute("baud",newRate);
}

void ModbusConfigurator::updateParity(const QString&)
{
updateAttribute("parity",parity->itemData(parity->currentIndex()).toString());
}

void ModbusConfigurator::updateFlowControl(const QString&)
{
updateAttribute("flow",flow->itemData(flow->currentIndex()).toString());
}

void ModbusConfigurator::updateStopBits(const QString&)
{
updateAttribute("stop",stop->itemData(stop->currentIndex()).toString());
}

void ModbusConfigurator::updateStation(int station)
{
updateAttribute("station",QString("%1").arg(station));
}

void ModbusConfigurator::updateFixedDecimal(bool fixed)
{
updateAttribute("decimalQuery",fixed?"true":"false");
}

void ModbusConfigurator::updateDecimalAddress(int address)
{
updateAttribute("decimalAddress",QString("%1").arg(address));
}

void ModbusConfigurator::updateDecimalPosition(int position)
{
updateAttribute("decimalPosition",QString("%1").arg(position));
}

void ModbusConfigurator::updateFixedUnit(bool fixed)
{
updateAttribute("unitQuery",fixed?"true":"false");
}

void ModbusConfigurator::updateUnitAddress(int address)
{
updateAttribute("unitAddress",QString("%1").arg(address));
}

void ModbusConfigurator::updateValueForF(int value)
{
updateAttribute("valueF",QString("%1").arg(value));
}

void ModbusConfigurator::updateValueForC(int value)
{
updateAttribute("valueC",QString("%1").arg(value));
}

void ModbusConfigurator::updateUnit(const QString&newUnit)
{
updateAttribute("fixedUnit",newUnit);
}

void ModbusConfigurator::updatePVAddress(int address)
{
updateAttribute("pVAddress",QString("%1").arg(address));
}

void ModbusConfigurator::updateSVEnabled(bool enabled)
{
updateAttribute("sVEnabled",enabled?"true":"false");
}

void ModbusConfigurator::updateSVReadAddress(int address)
{
updateAttribute("sVReadAddress",QString("%1").arg(address));
}

void ModbusConfigurator::updateDeviceLimit(bool query)
{
updateAttribute("deviceLimit",query?"true":"false");
}

void ModbusConfigurator::updateSVLowerAddress(int address)
{
updateAttribute("sVLowerAddr",QString("%1").arg(address));
}

void ModbusConfigurator::updateSVUpperAddress(int address)
{
updateAttribute("sVUpperAddr",QString("%1").arg(address));
}

void ModbusConfigurator::updateSVLower(double value)
{
updateAttribute("sVLower",QString("%1").arg(value));
}

void ModbusConfigurator::updateSVUpper(double value)
{
updateAttribute("sVUpper",QString("%1").arg(value));
}

void ModbusConfigurator::updateSVWritable(bool canWriteSV)
{
updateAttribute("sVWritable",canWriteSV?"true":"false");
}

void ModbusConfigurator::updateSVWriteAddress(int address)
{
updateAttribute("sVOutputAddr",QString("%1").arg(address));
}

void ModbusConfigurator::updatePVColumnName(const QString&name)
{
updateAttribute("pvcolname",name);
}

void ModbusConfigurator::updateSVColumnName(const QString&name)
{
updateAttribute("svcolname",name);
}

/*:716*/
#line 804 "./typica.w"

/*679:*/
#line 15883 "./typica.w"

ShortHexSpinBox::ShortHexSpinBox(QWidget*parent):QSpinBox(parent)
{
setMinimum(0);
setMaximum(0xFFFF);
setPrefix("0x");
setMinimumWidth(65);
}

QValidator::State ShortHexSpinBox::validate(QString&input,int&)const
{
if(input.size()==2)
{
return QValidator::Intermediate;
}
bool okay;
input.toInt(&okay,16);
if(okay)
{
return QValidator::Acceptable;
}
return QValidator::Invalid;
}

int ShortHexSpinBox::valueFromText(const QString&text)const
{
return text.toInt(NULL,16);
}

QString ShortHexSpinBox::textFromValue(int value)const
{
QString retval;
retval.setNum(value,16);
while(retval.size()<4)
{
retval.prepend("0");
}
return retval.toUpper();
}

/*:679*/
#line 805 "./typica.w"

/*701:*/
#line 16909 "./typica.w"

ModbusRTUDevice::ModbusRTUDevice(DeviceTreeModel*model,const QModelIndex&index)
:QObject(NULL),messageDelayTimer(new QTimer),unitIsF(true),readingsv(false),
waiting(false)
{
QDomElement portReferenceElement= model->referenceElement(model->data(index,
Qt::UserRole).toString());
QDomNodeList portConfigData= portReferenceElement.elementsByTagName("attribute");
QDomElement node;
QVariantMap attributes;
for(int i= 0;i<portConfigData.size();i++)
{
node= portConfigData.at(i).toElement();
attributes.insert(node.attribute("name"),node.attribute("value"));
}
port= new QextSerialPort(attributes.value("port").toString(),
QextSerialPort::EventDriven);
int baudRate= attributes.value("baud").toInt();
port->setBaudRate((BaudRateType)baudRate);
double temp= ((double)(1)/(double)(baudRate))*48;
delayTime= (int)(temp*3000);
messageDelayTimer->setSingleShot(true);
connect(messageDelayTimer,SIGNAL(timeout()),this,SLOT(sendNextMessage()));
port->setDataBits(DATA_8);
port->setParity((ParityType)attributes.value("parity").toInt());
port->setStopBits((StopBitsType)attributes.value("stop").toInt());
port->setFlowControl((FlowType)attributes.value("flow").toInt());
connect(port,SIGNAL(readyRead()),this,SLOT(dataAvailable()));
port->open(QIODevice::ReadWrite);
station= (char)attributes.value("station").toInt();
if(attributes.value("decimalQuery")=="true")
{
decimalPosition= 0;
QByteArray message;
message.append(station);
message.append((char)0x03);
quint16 address= (quint16)attributes.value("decimalAddress").toInt();
char*addressBytes= (char*)&address;
message.append(addressBytes[1]);
message.append(addressBytes[0]);
message.append((char)0x00);
message.append((char)0x01);
queueMessage(message,this,"decimalResponse(QByteArray)");
}
else
{
decimalPosition= attributes.value("decimalPosition").toInt();
}
valueF= attributes.value("valueF").toInt();
valueC= attributes.value("valueC").toInt();
if(attributes.value("unitQuery")=="true")
{
QByteArray message;
message.append(station);
message.append((char)0x03);
quint16 address= (quint16)attributes.value("unitAddress").toInt();
char*addressBytes= (char*)&address;
message.append(addressBytes[1]);
message.append(addressBytes[0]);
message.append((char)0x00);
message.append((char)0x01);
queueMessage(message,this,"unitResponse(QByteArray)");
}
else
{
if(attributes.value("fixedUnit")=="Celsius")
{
unitIsF= false;
}
}
if(attributes.value("sVWritable")=="true")
{
if(attributes.value("deviceLimit")=="true")
{
QByteArray lmessage;
lmessage.append(station);
lmessage.append((char)0x03);
quint16 laddress= (quint16)attributes.value("sVLowerAddr").toInt();
char*addressBytes= (char*)&laddress;
lmessage.append(addressBytes[1]);
lmessage.append(addressBytes[0]);
lmessage.append((char)0x00);
lmessage.append((char)0x01);
queueMessage(lmessage,this,"svlResponse(QByteArray)");
QByteArray umessage;
umessage.append(station);
umessage.append((char)0x03);
quint16 uaddress= (quint16)attributes.value("sVUpperAddr").toInt();
addressBytes= (char*)&uaddress;
umessage.append(addressBytes[1]);
umessage.append(addressBytes[0]);
umessage.append((char)0x00);
umessage.append((char)0x01);
queueMessage(umessage,this,"svuResponse(QByteArray)");
}
else
{
outputSVLower= attributes.value("sVLower").toDouble();
outputSVUpper= attributes.value("sVUpper").toDouble();
}
outputSVStub.append(station);
outputSVStub.append((char)0x06);
quint16 address= (quint16)attributes.value("sVOutputAddr").toInt();
char*addressBytes= (char*)&address;
outputSVStub.append(addressBytes[1]);
outputSVStub.append(addressBytes[0]);
}
Channel*pv= new Channel;
channels.append(pv);
pvStub.append(station);
pvStub.append((char)0x04);
pvaddress= (quint16)attributes.value("pVAddress").toInt();
char*pvac= (char*)&pvaddress;
pvStub.append(pvac[1]);
pvStub.append(pvac[0]);
pvStub.append((char)0x00);
pvStub.append((char)0x01);
svenabled= attributes.value("sVEnabled").toBool();
if(svenabled)
{
Channel*sv= new Channel;
channels.append(sv);
svStub.append(station);
svStub.append((char)0x04);
svaddress= (quint16)attributes.value("sVReadAddress").toInt();
char*svac= (char*)&svaddress;
svStub.append(svac[1]);
svStub.append(svac[0]);
svStub.append((char)0x00);
svStub.append((char)0x01);
if(svaddress-pvaddress==1)
{
mStub.append(station);
mStub.append((char)0x04);
mStub.append(pvac[1]);
mStub.append(pvac[0]);
mStub.append((char)0x00);
mStub.append((char)0x02);
}
}
connect(this,SIGNAL(queueEmpty()),this,SLOT(requestMeasurement()));
requestMeasurement();
}

double ModbusRTUDevice::SVLower()
{
return outputSVLower;
}

double ModbusRTUDevice::SVUpper()
{
return outputSVUpper;
}

int ModbusRTUDevice::decimals()
{
return decimalPosition;
}

void ModbusRTUDevice::decimalResponse(QByteArray response)
{
quint16 temp;
char*tchar= (char*)&temp;
tchar[1]= response.at(3);
tchar[0]= response.at(4);
decimalPosition= temp;
emit SVDecimalChanged(decimalPosition);
qDebug()<<"Received decimal response";
}

void ModbusRTUDevice::unitResponse(QByteArray response)
{
quint16 temp;
char*tchar= (char*)&temp;
tchar[1]= response.at(3);
tchar[0]= response.at(4);
int value= temp;
if(value==valueF)
{
unitIsF= true;
}
else
{
unitIsF= false;
}
}

void ModbusRTUDevice::svlResponse(QByteArray response)
{
quint16 temp;
char*tchar= (char*)&temp;
tchar[1]= response.at(3);
tchar[0]= response.at(4);
outputSVLower= (double)temp;
for(int i= 0;i<decimalPosition;i++)
{
outputSVLower/= 10;
}
emit SVLowerChanged(outputSVLower);
}

void ModbusRTUDevice::svuResponse(QByteArray response)
{
quint16 temp;
char*tchar= (char*)&temp;
tchar[1]= response.at(3);
tchar[0]= response.at(4);
outputSVUpper= (double)temp;
for(int i= 0;i<decimalPosition;i++)
{
outputSVUpper/= 10;
}
emit SVUpperChanged(outputSVUpper);
}

void ModbusRTUDevice::requestMeasurement()
{
if(mStub.length()> 0)
{
queueMessage(mStub,this,"mResponse(QByteArray)");
}
else
{
queueMessage(pvStub,this,"mResponse(QByteArray)");
if(svenabled)
{
queueMessage(svStub,this,"mResponse(QByteArray)");
}
}
}

void ModbusRTUDevice::mResponse(QByteArray response)
{
QTime time= QTime::currentTime();
if(response.at(2)==0x04)
{
/*702:*/
#line 17158 "./typica.w"

quint16 pv;
quint16 sv;
char*pvBytes= (char*)&pv;
char*svBytes= (char*)&sv;
pvBytes[1]= response.at(3);
pvBytes[0]= response.at(4);
svBytes[1]= response.at(5);
svBytes[0]= response.at(6);
double pvOut= (double)pv;
double svOut= (double)sv;
for(int i= 0;i<decimalPosition;i++)
{
pvOut/= 10;
svOut/= 10;
}
if(!unitIsF)
{
pvOut= pvOut*9/5+32;
svOut= svOut*9/5+32;
}
Measurement pvm(pvOut,time,Measurement::Fahrenheit);
Measurement svm(svOut,time,Measurement::Fahrenheit);
channels.at(0)->input(pvm);
channels.at(1)->input(svm);

/*:702*/
#line 17145 "./typica.w"

}
else
{
/*703:*/
#line 17188 "./typica.w"

quint16 value;
char*valueBytes= (char*)&value;
valueBytes[1]= response.at(3);
valueBytes[0]= response.at(4);
double valueOut= (double)value;
for(int i= 0;i<decimalPosition;i++)
{
valueOut/= 10;
}
if(!unitIsF)
{
valueOut= valueOut*9/5+32;
}
if(!svenabled)
{
Measurement vm(valueOut,time,Measurement::Fahrenheit);
channels.at(0)->input(vm);
}
else
{
if(readingsv)
{
Measurement pvm(savedpv,time,Measurement::Fahrenheit);
Measurement svm(valueOut,time,Measurement::Fahrenheit);
channels.at(0)->input(pvm);
channels.at(1)->input(svm);
readingsv= false;
}
else
{
savedpv= valueOut;
readingsv= true;
}
}

/*:703*/
#line 17149 "./typica.w"

}
}

/*:701*//*704:*/
#line 17226 "./typica.w"

ModbusRTUDevice::~ModbusRTUDevice()
{
messageDelayTimer->stop();
port->close();
}

/*:704*//*705:*/
#line 17248 "./typica.w"

void ModbusRTUDevice::dataAvailable()
{
if(messageDelayTimer->isActive())
{
messageDelayTimer->stop();
}
responseBuffer.append(port->readAll());
/*706:*/
#line 17293 "./typica.w"

if(responseBuffer.size()<5)
{
return;
}
switch(responseBuffer.at(1))
{
case 0x01:
case 0x02:
if(responseBuffer.size()<6)
{
return;
}
responseBuffer= responseBuffer.left(6);
break;
case 0x03:
case 0x04:
if(responseBuffer.size()<5+responseBuffer.at(2))
{
return;
}
responseBuffer= responseBuffer.left(5+responseBuffer.at(2));
break;
case 0x05:
case 0x06:
case 0x10:
if(responseBuffer.size()<8)
{
return;
}
responseBuffer= responseBuffer.left(8);
break;
}

/*:706*/
#line 17256 "./typica.w"

if(calculateCRC(responseBuffer)==0)
{
QObject*object= retObjQueue.at(0);
char*method= callbackQueue.at(0);
QMetaMethod metamethod= object->metaObject()->
method(object->metaObject()->
indexOfMethod(QMetaObject::normalizedSignature(method)));
metamethod.invoke(object,Qt::QueuedConnection,
Q_ARG(QByteArray,responseBuffer));
messageQueue.removeAt(0);
retObjQueue.removeAt(0);
callbackQueue.removeAt(0);
messageDelayTimer->start(delayTime);
}
else
{
qDebug()<<"CRC failed";
}
waiting= false;
responseBuffer.clear();
}

/*:705*//*707:*/
#line 17335 "./typica.w"

quint16 ModbusRTUDevice::calculateCRC(QByteArray data)
{
quint16 retval= 0xFFFF;
int i= 0;
while(i<data.size())
{
retval^= 0x00FF&(quint16)data.at(i);
for(int j= 0;j<8;j++)
{
if(retval&1)
{
retval= (retval>>1)^0xA001;
}
else
{
retval>>= 1;
}
}
i++;
}
return retval;
}

/*:707*//*708:*/
#line 17366 "./typica.w"

void ModbusRTUDevice::queueMessage(QByteArray request,QObject*object,
const char*callback)
{
messageQueue.append(request);
retObjQueue.append(object);
callbackQueue.append(const_cast<char*> (callback));
if(messageQueue.size()==1&&!(messageDelayTimer->isActive()))
{
sendNextMessage();
}
}

void ModbusRTUDevice::sendNextMessage()
{
if(messageQueue.size()> 0&&!waiting)
{
QByteArray message= messageQueue.at(0);
quint16 crc= calculateCRC(message);
char*check= (char*)&crc;
message.append(check[0]);
message.append(check[1]);
port->write(message);
messageDelayTimer->start(delayTime);
waiting= true;
}
else
{
emit queueEmpty();
}
}

void ModbusRTUDevice::outputSV(double value)
{
for(int i= 0;i<decimalPosition;i++)
{
value*= 10;
}
quint16 outval= (quint16)value;
QByteArray message(outputSVStub);
char*valBytes= (char*)&outval;
message.append(valBytes[1]);
message.append(valBytes[0]);
queueMessage(message,this,"ignore(QByteArray)");
}

/*:708*//*709:*/
#line 17414 "./typica.w"

void ModbusRTUDevice::ignore(QByteArray)
{
return;
}

/*:709*/
#line 806 "./typica.w"

/*599:*/
#line 14145 "./typica.w"

DeviceTreeModelNode::DeviceTreeModelNode(QDomNode&node,int row,
DeviceTreeModelNode*parent)
:domNode(node),rowNumber(row),parentItem(parent)
{

}

DeviceTreeModelNode::~DeviceTreeModelNode()
{
QHash<int,DeviceTreeModelNode*> ::iterator i;
for(i= children.begin();i!=children.end();i++)
{
delete i.value();
}
}

DeviceTreeModelNode*DeviceTreeModelNode::parent()
{
return parentItem;
}

int DeviceTreeModelNode::row()
{
return rowNumber;
}

QDomNode DeviceTreeModelNode::node()const
{
return domNode;
}

DeviceTreeModelNode*DeviceTreeModelNode::child(int index)
{
if(children.contains(index))
{
return children[index];
}
if(index>=0&&index<domNode.childNodes().count())
{
QDomNode childNode= domNode.childNodes().item(index);
DeviceTreeModelNode*childItem= new DeviceTreeModelNode(childNode,
index,this);
children[index]= childItem;
return childItem;
}
return NULL;
}

/*:599*/
#line 807 "./typica.w"

/*601:*/
#line 14234 "./typica.w"

DeviceTreeModel::DeviceTreeModel(QObject*parent)
:QAbstractItemModel(parent)
{
document= AppInstance->deviceConfiguration();
QDomNodeList elements= document.elementsByTagName("devices");
if(elements.size()!=1)
{
qDebug()<<"Unexpected result when loading device map.";
}
treeRoot= elements.at(0);
root= new DeviceTreeModelNode(treeRoot,0);
elements= document.elementsByTagName("references");
if(elements.size()!=1)
{
qDebug()<<"No references section. Creating.";
referenceSection= document.createElement("references");
document.appendChild(referenceSection);
}
else
{
referenceSection= elements.at(0);
}
connect(this,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
AppInstance,SLOT(saveDeviceConfiguration()));
connect(this,SIGNAL(modelReset()),
AppInstance,SLOT(saveDeviceConfiguration()));
connect(this,SIGNAL(rowsInserted(QModelIndex,int,int)),
AppInstance,SLOT(saveDeviceConfiguration()));
}

/*:601*//*602:*/
#line 14269 "./typica.w"

int DeviceTreeModel::columnCount(const QModelIndex&)const
{
return 1;
}

int DeviceTreeModel::rowCount(const QModelIndex&parent)const
{
if(parent.column()> 0)
{
return 0;
}
/*603:*/
#line 14288 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:603*/
#line 14281 "./typica.w"

return parentItem->node().childNodes().count();
}

/*:602*//*604:*/
#line 14302 "./typica.w"

QModelIndex DeviceTreeModel::index(int row,int column,
const QModelIndex&parent)const
{
if(!hasIndex(row,column,parent))
{
return QModelIndex();
}
/*603:*/
#line 14288 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:603*/
#line 14310 "./typica.w"

DeviceTreeModelNode*childItem= parentItem->child(row);
if(childItem)
{
return createIndex(row,column,childItem);
}
return QModelIndex();
}

/*:604*//*605:*/
#line 14321 "./typica.w"

QModelIndex DeviceTreeModel::parent(const QModelIndex&child)const
{
if(!child.isValid())
{
return QModelIndex();
}
DeviceTreeModelNode*childItem= 
static_cast<DeviceTreeModelNode*> (child.internalPointer());
DeviceTreeModelNode*parentItem= childItem->parent();
if(!parentItem||parentItem==root)
{
return QModelIndex();
}
return createIndex(parentItem->row(),0,parentItem);
}

/*:605*//*606:*/
#line 14340 "./typica.w"

Qt::ItemFlags DeviceTreeModel::flags(const QModelIndex&index)const
{
if(!index.isValid())
{
return 0;
}
return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

/*:606*//*607:*/
#line 14355 "./typica.w"

QVariant DeviceTreeModel::data(const QModelIndex&index,int role)const
{
if(!index.isValid())
{
return QVariant();
}
if(role!=Qt::DisplayRole&&role!=Qt::UserRole&&role!=Qt::EditRole)
{
return QVariant();
}
DeviceTreeModelNode*item= 
static_cast<DeviceTreeModelNode*> (index.internalPointer());
QDomNode node= item->node();
QDomElement element= node.toElement();
switch(role)
{
case Qt::DisplayRole:
case Qt::EditRole:
return QVariant(element.attribute("name"));
case Qt::UserRole:
return QVariant(element.attribute("reference"));
default:
return QVariant();
}
return QVariant();
}

/*:607*//*608:*/
#line 14387 "./typica.w"

bool DeviceTreeModel::setData(const QModelIndex&index,
const QVariant&value,int)
{
if(!index.isValid())
{
return false;
}
DeviceTreeModelNode*item= 
static_cast<DeviceTreeModelNode*> (index.internalPointer());
QDomNode node= item->node();
QDomElement element= node.toElement();
element.setAttribute("name",value.toString());
emit dataChanged(index,index);
return true;
}

/*:608*//*609:*/
#line 14410 "./typica.w"

void DeviceTreeModel::newNode(const QString&name,const QString&driver,
const QModelIndex&parent)
{
QString referenceID= QUuid::createUuid().toString();
/*603:*/
#line 14288 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:603*/
#line 14415 "./typica.w"

QDomNode parentNode= parentItem->node();
int newRowNumber= rowCount(parent);
beginInsertRows(parent,newRowNumber,newRowNumber);
QDomElement deviceElement= document.createElement("node");
deviceElement.setAttribute("name",name);
deviceElement.setAttribute("reference",referenceID);
parentNode.appendChild(deviceElement);
QDomElement referenceElement= document.createElement("reference");
referenceElement.setAttribute("id",referenceID);
referenceElement.setAttribute("driver",driver);
referenceSection.appendChild(referenceElement);
endInsertRows();
}

/*:609*//*610:*/
#line 14433 "./typica.w"

bool DeviceTreeModel::removeRows(int row,int count,const QModelIndex&parent)
{
/*603:*/
#line 14288 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:603*/
#line 14436 "./typica.w"

QDomNode parentNode= parentItem->node();
QDomNodeList childNodes= parentNode.childNodes();
if(childNodes.size()<row+count)
{
return false;
}
beginRemoveRows(parent,row,row+count-1);
QList<QDomElement> removalList;
for(int i= row;i<row+count;i++)
{
removalList.append(childNodes.at(i).toElement());
}
QDomElement element;
QDomElement reference;
for(int i= 0;i<count;i++)
{
element= removalList.at(i);
if(element.hasAttribute("reference"))
{
reference= referenceElement(element.attribute("reference"));
if(!reference.isNull())
{
referenceSection.removeChild(reference);
}
}
parentNode.removeChild(element);
}
endRemoveRows();
beginResetModel();
delete root;
root= new DeviceTreeModelNode(treeRoot,0);
endResetModel();
return true;
}

/*:610*//*611:*/
#line 14475 "./typica.w"

QDomElement DeviceTreeModel::referenceElement(const QString&id)
{
QDomNodeList childNodes= referenceSection.childNodes();
QDomElement element;
for(int i= 0;i<childNodes.size();i++)
{
element= childNodes.at(i).toElement();
if(element.hasAttribute("id"))
{
if(element.attribute("id")==id)
{
return element;
}
}
}
return QDomElement();
}

/*:611*//*612:*/
#line 14496 "./typica.w"

QVariant DeviceTreeModel::headerData(int,Qt::Orientation,int)const
{
return QVariant();
}

/*:612*//*613:*/
#line 14505 "./typica.w"

DeviceTreeModel::~DeviceTreeModel()
{
delete root;
}

/*:613*/
#line 808 "./typica.w"

/*639:*/
#line 14975 "./typica.w"

BasicDeviceConfigurationWidget::BasicDeviceConfigurationWidget(
DeviceTreeModel*model,const QModelIndex&index)
:QWidget(NULL),deviceModel(model),currentNode(index)
{

}

/*:639*//*640:*/
#line 14987 "./typica.w"

void BasicDeviceConfigurationWidget::updateAttribute(const QString&name,
const QString&value)
{
QDomElement referenceElement= deviceModel->referenceElement(
deviceModel->data(currentNode,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;
bool found= false;
for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")==name)
{
node.setAttribute("value",value);
found= true;
break;
}
}
if(!found)
{
node= AppInstance->deviceConfiguration().createElement("attribute");
node.setAttribute("name",name);
node.setAttribute("value",value);
referenceElement.appendChild(node);
}
AppInstance->saveDeviceConfiguration();
}

/*:640*//*641:*/
#line 15021 "./typica.w"

void BasicDeviceConfigurationWidget::insertChildNode(const QString&name,
const QString&driver)
{
deviceModel->newNode(name,driver,currentNode);
}

/*:641*/
#line 809 "./typica.w"

/*631:*/
#line 14843 "./typica.w"

DeviceConfigurationWindow::DeviceConfigurationWindow():QMainWindow(NULL),
view(new QTreeView),configArea(new QScrollArea)
{
QSplitter*splitter= new QSplitter;
QWidget*leftWidget= new QWidget;
leftWidget->setMinimumWidth(200);
QVBoxLayout*left= new QVBoxLayout;
view->setAnimated(true);
view->setSelectionMode(QAbstractItemView::SingleSelection);
document= AppInstance->deviceConfiguration();
model= new DeviceTreeModel;
view->setModel(model);
view->expandAll();
connect(model,SIGNAL(modelReset()),view,SLOT(expandAll()));
QHBoxLayout*treeButtons= new QHBoxLayout;
QToolButton*addDeviceButton= new QToolButton;
addDeviceButton->setIcon(QIcon::fromTheme("list-add"));
addDeviceButton->setToolTip(tr("New Roaster"));
connect(addDeviceButton,SIGNAL(clicked()),
this,SLOT(addDevice()));
QToolButton*removeNodeButton= new QToolButton;
removeNodeButton->setIcon(QIcon::fromTheme("list-remove"));
removeNodeButton->setToolTip(tr("Delete Selection"));
connect(removeNodeButton,SIGNAL(clicked()),this,SLOT(removeNode()));
treeButtons->addWidget(addDeviceButton);
treeButtons->addWidget(removeNodeButton);
left->addWidget(view);
left->addLayout(treeButtons);
leftWidget->setLayout(left);
splitter->addWidget(leftWidget);
configArea->setMinimumWidth(580);
configArea->setMinimumHeight(460);
splitter->addWidget(configArea);
setCentralWidget(splitter);
connect(view,SIGNAL(activated(QModelIndex)),
this,SLOT(newSelection(QModelIndex)));
connect(view,SIGNAL(clicked(QModelIndex)),
this,SLOT(newSelection(QModelIndex)));
connect(model,SIGNAL(rowsInserted(QModelIndex,int,int)),
view,SLOT(expand(QModelIndex)));
}

/*:631*//*632:*/
#line 14889 "./typica.w"

void DeviceConfigurationWindow::addDevice()
{
model->newNode(tr("New Roaster"),"roaster",QModelIndex());
}

/*:632*//*633:*/
#line 14897 "./typica.w"

void DeviceConfigurationWindow::removeNode()
{
QModelIndex index= view->currentIndex();
if(index.isValid())
{
int row= index.row();
QModelIndex parent= index.parent();
model->removeRow(row,parent);
}
}

/*:633*//*634:*/
#line 14913 "./typica.w"

void DeviceConfigurationWindow::newSelection(const QModelIndex&index)
{
QWidget*editor= AppInstance->deviceConfigurationWidget(model,index);
if(editor)
{
configArea->setWidget(editor);
editor->show();
}
}

/*:634*/
#line 810 "./typica.w"

/*654:*/
#line 15317 "./typica.w"

Ni9211TcConfWidget::Ni9211TcConfWidget(DeviceTreeModel*model,
const QModelIndex&index):
BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*columnName= new QLineEdit;
layout->addRow(tr("Column Name:"),columnName);
QComboBox*typeSelector= new QComboBox;
typeSelector->addItem("J");
typeSelector->addItem("K");
typeSelector->addItem("T");
typeSelector->addItem("B");
typeSelector->addItem("E");
typeSelector->addItem("N");
typeSelector->addItem("R");
typeSelector->addItem("S");
layout->addRow(tr("Thermocouple Type:"),typeSelector);
setLayout(layout);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 15336 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="type")
{
typeSelector->setCurrentIndex(
typeSelector->findText(node.attribute("value")));
}
else if(node.attribute("name")=="columnname")
{
columnName->setText(node.attribute("value"));
}
}
updateThermocoupleType(typeSelector->currentText());
updateColumnName(columnName->text());
connect(typeSelector,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateThermocoupleType(QString)));
connect(columnName,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
}

/*:654*//*655:*/
#line 15360 "./typica.w"

void Ni9211TcConfWidget::updateThermocoupleType(const QString&type)
{
updateAttribute("type",type);
}

void Ni9211TcConfWidget::updateColumnName(const QString&name)
{
updateAttribute("columnname",name);
}

/*:655*/
#line 811 "./typica.w"

/*650:*/
#line 15232 "./typica.w"

NiDaqMxBase9211ConfWidget::NiDaqMxBase9211ConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QVBoxLayout*layout= new QVBoxLayout;
QHBoxLayout*deviceIdLayout= new QHBoxLayout;
QLabel*label= new QLabel(tr("Device ID:"));
QLineEdit*deviceId= new QLineEdit;
deviceIdLayout->addWidget(label);
deviceIdLayout->addWidget(deviceId);
QPushButton*addChannelButton= new QPushButton(tr("Add Channel"));
layout->addLayout(deviceIdLayout);
layout->addWidget(addChannelButton);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 15246 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="deviceID")
{
deviceId->setText(node.attribute("value","Dev1"));
break;
}
}
updateDeviceId(deviceId->text());
connect(addChannelButton,SIGNAL(clicked()),
this,SLOT(addChannel()));
connect(deviceId,SIGNAL(textEdited(QString)),
this,SLOT(updateDeviceId(QString)));
setLayout(layout);
}

/*:650*//*651:*/
#line 15268 "./typica.w"

void NiDaqMxBase9211ConfWidget::updateDeviceId(const QString&newId)
{
updateAttribute("deviceID",newId);
}

/*:651*//*652:*/
#line 15276 "./typica.w"

void NiDaqMxBase9211ConfWidget::addChannel()
{
insertChildNode(tr("Thermocouple channel"),"ni9211seriestc");
}

/*:652*/
#line 812 "./typica.w"

/*648:*/
#line 15183 "./typica.w"

NiDaqMxBaseDriverConfWidget::NiDaqMxBaseDriverConfWidget(
DeviceTreeModel*model,const QModelIndex&index):
BasicDeviceConfigurationWidget(model,index)
{
QHBoxLayout*layout= new QHBoxLayout;
QToolButton*addDeviceButton= new QToolButton;
addDeviceButton->setText(tr("Add Device"));
NodeInserter*add9211= new NodeInserter("NI USB 9211","NI USB 9211",
"nidaqmxbase9211series");
NodeInserter*add9211a= new NodeInserter("NI USB 9211A","NI USB 9211A",
"nidaqmxbase9211series");
connect(add9211,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(add9211a,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
QMenu*deviceMenu= new QMenu;
deviceMenu->addAction(add9211);
deviceMenu->addAction(add9211a);
addDeviceButton->setMenu(deviceMenu);
addDeviceButton->setPopupMode(QToolButton::InstantPopup);
layout->addWidget(addDeviceButton);
setLayout(layout);
}

/*:648*/
#line 813 "./typica.w"

/*537:*/
#line 12770 "./typica.w"

ReportAction::ReportAction(const QString&fileName,const QString&reportName,
QObject*parent):
QAction(reportName,parent),reportFile(fileName)
{
connect(this,SIGNAL(triggered()),this,SLOT(createReport()));
}

/*:537*//*538:*/
#line 12786 "./typica.w"

void ReportAction::createReport()
{
QFile file(reportFile);
QDomDocument document;
if(file.open(QIODevice::ReadOnly))
{
document.setContent(&file,true);
QDomElement element= document.documentElement();
QScriptEngine*engine= AppInstance->engine;
QScriptContext*context= engine->pushContext();
QScriptValue object;
QString targetID= reportFile;
/*160:*/
#line 3884 "./typica.w"

ScriptQMainWindow*window= new ScriptQMainWindow;
window->setObjectName(targetID);
object= engine->newQObject(window);
setQMainWindowProperties(object,engine);
QWidget*central= new(QWidget);
central->setParent(window);
central->setObjectName("centralWidget");
window->setCentralWidget(central);
if(element.hasChildNodes())
{
/*161:*/
#line 3925 "./typica.w"

QStack<QWidget*> widgetStack;
QStack<QLayout*> layoutStack;
QString windowScript;
widgetStack.push(central);
QDomNodeList windowChildren= element.childNodes();
int i= 0;
while(i<windowChildren.count())
{
QDomNode current;
QDomElement element;
current= windowChildren.at(i);
if(current.isElement())
{
element= current.toElement();
if(element.tagName()=="program")
{
windowScript.append(element.text());
}
else if(element.tagName()=="layout")
{
addLayoutToWidget(element,&widgetStack,&layoutStack);
}
else if(element.tagName()=="menu")
{
/*162:*/
#line 3972 "./typica.w"

QMenuBar*bar= window->menuBar();
bar->setParent(window);
bar->setObjectName("menuBar");
if(element.hasAttribute("name"))
{
QMenu*menu= bar->addMenu(element.attribute("name"));
menu->setParent(bar);
if(element.hasAttribute("type"))
{
if(element.attribute("type")=="reports")
{
if(element.hasAttribute("src"))
{
/*535:*/
#line 12733 "./typica.w"

QSettings settings;
QDir directory(QString("%1/%2").arg(settings.value("config").toString()).
arg(element.attribute("src")));
directory.setFilter(QDir::Files);
directory.setSorting(QDir::Name);
QStringList nameFilter;
nameFilter<<"*.xml";
directory.setNameFilters(nameFilter);
QFileInfoList reportFiles= directory.entryInfoList();
for(int i= 0;i<reportFiles.size();i++)
{
QFileInfo reportFile= reportFiles.at(i);
/*539:*/
#line 12810 "./typica.w"

QString path= reportFile.absoluteFilePath();
QFile file(path);
if(file.open(QIODevice::ReadOnly))
{
QDomDocument document;
document.setContent(&file,true);
QDomElement root= document.documentElement();
QDomNode titleNode= root.elementsByTagName("reporttitle").at(0);
if(!titleNode.isNull())
{
QDomElement titleElement= titleNode.toElement();
QString title= titleElement.text();
if(!title.isEmpty())
{
QStringList hierarchy= title.split(":->");
QMenu*insertionPoint= menu;
/*540:*/
#line 12837 "./typica.w"

for(int j= 0;j<hierarchy.size()-1;j++)
{
QObjectList menuList= insertionPoint->children();
bool menuFound= false;
for(int k= 0;k<menuList.size();k++)
{
QMenu*currentItem= qobject_cast<QMenu*> (menuList.at(k));
if(currentItem)
{
if(currentItem->title()==hierarchy.at(j))
{
menuFound= true;
insertionPoint= currentItem;
break;
}
}
}
if(!menuFound)
{
insertionPoint= insertionPoint->addMenu(hierarchy.at(j));
}
}

/*:540*/
#line 12827 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:539*/
#line 12746 "./typica.w"

}

/*:535*/
#line 3986 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*163:*/
#line 3999 "./typica.w"

QDomNodeList menuItems= element.childNodes();
int j= 0;
while(j<menuItems.count())
{
QDomNode item= menuItems.at(j);
if(item.isElement())
{
QDomElement itemElement= item.toElement();
if(itemElement.tagName()=="item")
{
QAction*itemAction= new QAction(itemElement.text(),menu);
if(itemElement.hasAttribute("id"))
{
itemAction->setObjectName(itemElement.attribute("id"));
}
if(itemElement.hasAttribute("shortcut"))
{
itemAction->setShortcut(itemElement.attribute("shortcut"));
}
menu->addAction(itemAction);
}
else if(itemElement.tagName()=="separator")
{
menu->addSeparator();
}
}
j++;
}

/*:163*/
#line 3992 "./typica.w"

}
}

/*:162*/
#line 3950 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*155:*/
#line 3733 "./typica.w"

if(engine->hasUncaughtException())
{
int line= engine->uncaughtExceptionLineNumber();
qDebug()<<"Uncaught excpetion at line "<<line<<" : "<<
result.toString();
QString trace;
foreach(trace,engine->uncaughtExceptionBacktrace())
{
qDebug()<<trace;
}
}

/*:155*/
#line 3958 "./typica.w"

context->setThisObject(oldThis);

/*:161*/
#line 3895 "./typica.w"

}
if(window)
{
window->show();
}
else
{
qDebug()<<"Error! Window invalidated";
}

/*:160*/
#line 12799 "./typica.w"

file.close();
engine->popContext();
}
}

/*:538*/
#line 814 "./typica.w"

/*191:*/
#line 5045 "./typica.w"

NumericDelegate::NumericDelegate(QObject*parent):
QItemDelegate(parent)
{

}

/*:191*//*192:*/
#line 5057 "./typica.w"

void NumericDelegate::setEditorData(QWidget*editor,
const QModelIndex&index)const
{
QString value= index.model()->data(index,Qt::EditRole).toString();
QLineEdit*line= static_cast<QLineEdit*> (editor);
line->setText(value);
}

/*:192*//*193:*/
#line 5072 "./typica.w"

void NumericDelegate::setModelData(QWidget*editor,QAbstractItemModel*model,
const QModelIndex&index)const
{
QLineEdit*line= static_cast<QLineEdit*> (editor);
model->setData(index,line->text(),Qt::EditRole);
QScriptEngine*engine= AppInstance->engine;
engine->pushContext();
QString script= QString("Number(%1)").arg(line->text());
QScriptValue result= engine->evaluate(line->text());
if(result.isNumber())
{
model->setData(index,result.toVariant(),Qt::DisplayRole);
}
else
{
model->setData(index,QVariant(),Qt::DisplayRole);
}
engine->popContext();
}

/*:193*//*194:*/
#line 5095 "./typica.w"

QWidget*NumericDelegate::createEditor(QWidget*parent,
const QStyleOptionViewItem&,
const QModelIndex&)const
{
return(new QLineEdit(parent));
}

/*:194*//*195:*/
#line 5106 "./typica.w"

void NumericDelegate::updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&)const
{
editor->setGeometry(option.rect);
}

/*:195*/
#line 815 "./typica.w"

/*659:*/
#line 15414 "./typica.w"

NiDaqMxDriverConfWidget::NiDaqMxDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QHBoxLayout*layout= new QHBoxLayout;
QToolButton*addDeviceButton= new QToolButton;
addDeviceButton->setText(tr("Add Device"));
NodeInserter*add9211a= new NodeInserter("NI USB 9211A","NI USB 9211A",
"nidaqmx9211series");
NodeInserter*addtc01= new NodeInserter("NI USB TC01","NI USB TC01",
"nidaqmxtc01");
connect(add9211a,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(addtc01,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
QMenu*deviceMenu= new QMenu;
deviceMenu->addAction(add9211a);
deviceMenu->addAction(addtc01);
addDeviceButton->setMenu(deviceMenu);
addDeviceButton->setPopupMode(QToolButton::InstantPopup);
layout->addWidget(addDeviceButton);
setLayout(layout);
}

/*:659*/
#line 816 "./typica.w"

/*661:*/
#line 15463 "./typica.w"

NiDaqMx9211ConfWidget::NiDaqMx9211ConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QVBoxLayout*layout= new QVBoxLayout;
QHBoxLayout*deviceIdLayout= new QHBoxLayout;
QLabel*label= new QLabel(tr("Device ID:"));
QLineEdit*deviceId= new QLineEdit;
deviceIdLayout->addWidget(label);
deviceIdLayout->addWidget(deviceId);
QPushButton*addChannelButton= new QPushButton(tr("Add Channel"));
layout->addLayout(deviceIdLayout);
layout->addWidget(addChannelButton);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 15477 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="deviceID")
{
deviceId->setText(node.attribute("value","Dev1"));
break;
}
}
updateDeviceId(deviceId->text());
connect(addChannelButton,SIGNAL(clicked()),this,SLOT(addChannel()));
connect(deviceId,SIGNAL(textEdited(QString)),
this,SLOT(updateDeviceId(QString)));
setLayout(layout);
}

void NiDaqMx9211ConfWidget::updateDeviceId(const QString&newId)
{
updateAttribute("deviceID",newId);
}

void NiDaqMx9211ConfWidget::addChannel()
{
insertChildNode(tr("Thermocouple channel"),"ni9211seriestc");
}

/*:661*/
#line 817 "./typica.w"

/*663:*/
#line 15527 "./typica.w"

NiDaqMxTc01ConfWidget::NiDaqMxTc01ConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*deviceId= new QLineEdit;
layout->addRow(tr("Device ID:"),deviceId);
QLineEdit*columnName= new QLineEdit;
layout->addRow(tr("Column Name:"),columnName);
QComboBox*typeSelector= new QComboBox;
typeSelector->addItem("J");
typeSelector->addItem("K");
typeSelector->addItem("T");
typeSelector->addItem("B");
typeSelector->addItem("E");
typeSelector->addItem("N");
typeSelector->addItem("R");
typeSelector->addItem("S");
layout->addRow(tr("Thermocouple Type:"),typeSelector);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 15547 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="deviceID")
{
deviceId->setText(node.attribute("value"));
}
else if(node.attribute("name")=="type")
{
typeSelector->setCurrentIndex(typeSelector->findText(node.attribute("value")));
}
else if(node.attribute("name")=="columnname")
{
columnName->setText(node.attribute("value"));
}
}
updateDeviceId(deviceId->text());
updateThermocoupleType(typeSelector->currentText());
updateColumnName(columnName->text());
connect(deviceId,SIGNAL(textEdited(QString)),this,SLOT(updateDeviceId(QString)));
connect(typeSelector,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateThermocoupleType(QString)));
connect(columnName,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
setLayout(layout);
}

void NiDaqMxTc01ConfWidget::updateDeviceId(const QString&newId)
{
updateAttribute("deviceID",newId);
}

void NiDaqMxTc01ConfWidget::updateThermocoupleType(const QString&type)
{
updateAttribute("type",type);
}

void NiDaqMxTc01ConfWidget::updateColumnName(const QString&name)
{
updateAttribute("columnname",name);
}

/*:663*/
#line 818 "./typica.w"

/*681:*/
#line 15948 "./typica.w"

ModbusRtuPortConfWidget::ModbusRtuPortConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QToolButton*addDeviceButton= new QToolButton;
addDeviceButton->setText(tr("Add Device"));
NodeInserter*addModbusRtuDevice= new NodeInserter("Modbus RTU Device",
"Modbus RTU Device",
"modbusrtudevice");
connect(addModbusRtuDevice,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
QMenu*deviceMenu= new QMenu;
deviceMenu->addAction(addModbusRtuDevice);
addDeviceButton->setMenu(deviceMenu);
addDeviceButton->setPopupMode(QToolButton::InstantPopup);
layout->addRow(QString(),addDeviceButton);
PortSelector*port= new PortSelector;
layout->addRow(tr("Port:"),port);
connect(port,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updatePort(QString)));
connect(port,SIGNAL(editTextChanged(QString)),
this,SLOT(updatePort(QString)));
BaudSelector*rate= new BaudSelector;
layout->addRow(tr("Baud:"),rate);
connect(rate,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateBaudRate(QString)));
ParitySelector*parity= new ParitySelector;
layout->addRow(tr("Parity:"),parity);
connect(parity,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateParity(QString)));
FlowSelector*flow= new FlowSelector;
layout->addRow(tr("Flow Control:"),flow);
connect(flow,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateFlowControl(QString)));
StopSelector*stop= new StopSelector;
layout->addRow(tr("Stop Bits:"),stop);
connect(stop,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateStopBits(QString)));
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 15988 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="port")
{
int j= port->findText(node.attribute("value"));
if(j>=0)
{
port->setCurrentIndex(j);
}
else
{
port->insertItem(0,node.attribute("value"));
port->setCurrentIndex(0);
}
}
else if(node.attribute("name")=="baudrate")
{
rate->setCurrentIndex(rate->findText(node.attribute("value")));
}
else if(node.attribute("name")=="parity")
{
parity->setCurrentIndex(parity->findText(node.attribute("value")));
}
else if(node.attribute("name")=="flowcontrol")
{
flow->setCurrentIndex(flow->findText(node.attribute("value")));
}
else if(node.attribute("name")=="stopbits")
{
stop->setCurrentIndex(stop->findText(node.attribute("value")));
}
}
updatePort(port->currentText());
updateBaudRate(rate->currentText());
updateParity(parity->currentText());
updateFlowControl(flow->currentText());
updateStopBits(stop->currentText());
setLayout(layout);
}

void ModbusRtuPortConfWidget::updatePort(const QString&newPort)
{
updateAttribute("port",newPort);
}

void ModbusRtuPortConfWidget::updateBaudRate(const QString&newRate)
{
updateAttribute("baudrate",newRate);
}

void ModbusRtuPortConfWidget::updateParity(const QString&newParity)
{
updateAttribute("parity",newParity);
}

void ModbusRtuPortConfWidget::updateFlowControl(const QString&newFlow)
{
updateAttribute("flowcontrol",newFlow);
}

void ModbusRtuPortConfWidget::updateStopBits(const QString&newStopBits)
{
updateAttribute("stopbits",newStopBits);
}

/*:681*/
#line 819 "./typica.w"

/*683:*/
#line 16111 "./typica.w"

ModbusRtuDeviceConfWidget::ModbusRtuDeviceConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
unitSpecificationLayout(new QStackedLayout),
decimalSpecificationLayout(new QStackedLayout)
{
QVBoxLayout*layout= new QVBoxLayout;
QToolButton*addChannelButton= new QToolButton;
addChannelButton->setText(tr("Add Channel"));
NodeInserter*addTemperaturePV= new NodeInserter("Temperature Process Value",
"Temperature Process Value",
"modbustemperaturepv");
NodeInserter*addTemperatureSV= new NodeInserter("Temperature Set Value",
"Temperature Set Value",
"modbustemperaturesv");
connect(addTemperaturePV,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(addTemperatureSV,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
QMenu*channelMenu= new QMenu;
channelMenu->addAction(addTemperaturePV);
channelMenu->addAction(addTemperatureSV);
addChannelButton->setMenu(channelMenu);
addChannelButton->setPopupMode(QToolButton::InstantPopup);
layout->addWidget(addChannelButton);
QHBoxLayout*stationLayout= new QHBoxLayout;
QLabel*stationLabel= new QLabel(tr("Station:"));
QSpinBox*stationNumber= new QSpinBox;
stationNumber->setMinimum(0);
stationNumber->setMaximum(255);
stationLayout->addWidget(stationLabel);
stationLayout->addWidget(stationNumber);
layout->addLayout(stationLayout);
QCheckBox*fixedUnit= new QCheckBox(tr("Fixed Temperature Unit"));
layout->addWidget(fixedUnit);
QWidget*fixedUnitPlaceholder= new QWidget(this);
QHBoxLayout*fixedUnitLayout= new QHBoxLayout;
QLabel*fixedUnitLabel= new QLabel(tr("Temperature Unit:"));
QComboBox*fixedUnitSelector= new QComboBox;
fixedUnitSelector->addItem("Fahrenheit");
fixedUnitSelector->addItem("Celsius");
fixedUnitLayout->addWidget(fixedUnitLabel);
fixedUnitLayout->addWidget(fixedUnitSelector);
fixedUnitPlaceholder->setLayout(fixedUnitLayout);
unitSpecificationLayout->addWidget(fixedUnitPlaceholder);
QWidget*queriedUnitPlaceholder= new QWidget(this);
QFormLayout*queriedUnitLayout= new QFormLayout;
ShortHexSpinBox*unitAddress= new ShortHexSpinBox;
queriedUnitLayout->addRow(tr("Function 0x03 Unit Address:"),unitAddress);
QSpinBox*valueF= new QSpinBox;
valueF->setMinimum(0);
valueF->setMaximum(65535);
queriedUnitLayout->addRow(tr("Value for Fahrenheit"),valueF);
QSpinBox*valueC= new QSpinBox;
valueC->setMinimum(0);
valueC->setMaximum(65535);
queriedUnitLayout->addRow(tr("Value for Celsius"),valueC);
queriedUnitPlaceholder->setLayout(queriedUnitLayout);
unitSpecificationLayout->addWidget(queriedUnitPlaceholder);
layout->addLayout(unitSpecificationLayout);
QCheckBox*fixedPrecision= new QCheckBox(tr("Fixed Precision"));
layout->addWidget(fixedPrecision);
QWidget*fixedPrecisionPlaceholder= new QWidget(this);
QFormLayout*fixedPrecisionLayout= new QFormLayout;
QSpinBox*fixedPrecisionValue= new QSpinBox;
fixedPrecisionValue->setMinimum(0);
fixedPrecisionValue->setMaximum(9);
fixedPrecisionLayout->addRow("Places after the decimal point:",
fixedPrecisionValue);
fixedPrecisionPlaceholder->setLayout(fixedPrecisionLayout);
decimalSpecificationLayout->addWidget(fixedPrecisionPlaceholder);
QWidget*queriedPrecisionPlaceholder= new QWidget(this);
QFormLayout*queriedPrecisionLayout= new QFormLayout;
ShortHexSpinBox*precisionAddress= new ShortHexSpinBox;
queriedPrecisionLayout->addRow("Function 0x03 Decimal Position Address:",
precisionAddress);
queriedPrecisionPlaceholder->setLayout(queriedPrecisionLayout);
decimalSpecificationLayout->addWidget(queriedPrecisionPlaceholder);
layout->addLayout(decimalSpecificationLayout);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 16191 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="station")
{
stationNumber->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="fixedunit")
{
if(node.attribute("value")=="true")
{
fixedUnit->setCheckState(Qt::Checked);
}
else if(node.attribute("value")=="false")
{
fixedUnit->setCheckState(Qt::Unchecked);
}
}
else if(node.attribute("name")=="fixedprecision")
{
fixedPrecisionValue->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="unit")
{
fixedUnitSelector->setCurrentIndex(fixedUnitSelector->findText(node.attribute("value")));
}
else if(node.attribute("name")=="unitaddress")
{
unitAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="fvalue")
{
valueF->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="cvalue")
{
valueC->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="precisionaddress")
{
precisionAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="precision")
{
fixedPrecisionValue->setValue(node.attribute("value").toInt());
}
}
updateStationNumber(stationNumber->value());
updateFixedUnit(fixedUnit->isChecked());
updateFixedDecimal(fixedPrecision->isChecked());
updateUnit(fixedUnitSelector->currentText());
updateUnitAddress(unitAddress->value());
updateValueF(valueF->value());
updateValueC(valueC->value());
updatePrecisionAddress(precisionAddress->value());
updatePrecisionValue(fixedPrecisionValue->value());
connect(stationNumber,SIGNAL(valueChanged(int)),
this,SLOT(updateStationNumber(int)));
connect(fixedUnitSelector,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateUnit(QString)));
connect(unitAddress,SIGNAL(valueChanged(int)),
this,SLOT(updateUnitAddress(int)));
connect(valueF,SIGNAL(valueChanged(int)),
this,SLOT(updateValueF(int)));
connect(valueC,SIGNAL(valueChanged(int)),
this,SLOT(updateValueC(int)));
connect(fixedUnit,SIGNAL(toggled(bool)),
this,SLOT(updateFixedUnit(bool)));
connect(fixedPrecision,SIGNAL(toggled(bool)),
this,SLOT(updateFixedDecimal(bool)));
connect(fixedPrecisionValue,SIGNAL(valueChanged(int)),
this,SLOT(updatePrecisionValue(int)));
connect(precisionAddress,SIGNAL(valueChanged(int)),
this,SLOT(updatePrecisionAddress(int)));
setLayout(layout);
}

void ModbusRtuDeviceConfWidget::updateStationNumber(int newStation)
{
updateAttribute("station",QString("%1").arg(newStation));
}

void ModbusRtuDeviceConfWidget::updateFixedUnit(bool newFixed)
{
if(newFixed)
{
unitSpecificationLayout->setCurrentIndex(0);
updateAttribute("fixedunit","true");
}
else
{
unitSpecificationLayout->setCurrentIndex(1);
updateAttribute("fixedunit","false");
}
}

void ModbusRtuDeviceConfWidget::updateFixedDecimal(bool newFixed)
{
if(newFixed)
{
decimalSpecificationLayout->setCurrentIndex(0);
updateAttribute("fixedprecision","true");
}
else
{
decimalSpecificationLayout->setCurrentIndex(1);
updateAttribute("fixedprecision","false");
}
}

void ModbusRtuDeviceConfWidget::updateUnit(const QString&newUnit)
{
updateAttribute("unit",newUnit);
}

void ModbusRtuDeviceConfWidget::updateUnitAddress(int newAddress)
{
updateAttribute("unitaddress",QString("%1").arg(newAddress));
}

void ModbusRtuDeviceConfWidget::updateValueF(int newValue)
{
updateAttribute("fvalue",QString("%1").arg(newValue));
}

void ModbusRtuDeviceConfWidget::updateValueC(int newValue)
{
updateAttribute("cvalue",QString("%1").arg(newValue));
}

void ModbusRtuDeviceConfWidget::updatePrecisionAddress(int newAddress)
{
updateAttribute("precisionaddress",QString("%1").arg(newAddress));
}

void ModbusRtuDeviceConfWidget::updatePrecisionValue(int newValue)
{
updateAttribute("precision",QString("%1").arg(newValue));
}

/*:683*/
#line 820 "./typica.w"

/*685:*/
#line 16354 "./typica.w"

ModbusRtuDeviceTPvConfWidget::ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
ShortHexSpinBox*address= new ShortHexSpinBox;
layout->addRow(tr("Function 0x04 Process Value Address"),address);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 16362 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="address")
{
address->setValue(node.attribute("value").toInt());
break;
}
}
updateAddress(address->value());
connect(address,SIGNAL(valueChanged(int)),this,SLOT(updateAddress(int)));
setLayout(layout);
}

void ModbusRtuDeviceTPvConfWidget::updateAddress(int newAddress)
{
updateAttribute("address",QString("%1").arg(newAddress));
}

/*:685*/
#line 821 "./typica.w"

/*687:*/
#line 16410 "./typica.w"

ModbusRtuDeviceTSvConfWidget::ModbusRtuDeviceTSvConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),boundsLayout(new QStackedLayout)
{
QVBoxLayout*layout= new QVBoxLayout;
QFormLayout*addressLayout= new QFormLayout;
ShortHexSpinBox*readAddress= new ShortHexSpinBox;
ShortHexSpinBox*writeAddress= new ShortHexSpinBox;
addressLayout->addRow(tr("Function 0x04 Read Set Value Address:"),readAddress);
addressLayout->addRow(tr("Function 0x06 Write Set Value Address:"),writeAddress);
layout->addLayout(addressLayout);
QCheckBox*fixedRange= new QCheckBox(tr("Fixed Set Value Range"));
layout->addWidget(fixedRange);
QWidget*queriedRangePlaceholder= new QWidget(this);
QFormLayout*queriedRangeLayout= new QFormLayout;
ShortHexSpinBox*lowerAddress= new ShortHexSpinBox;
ShortHexSpinBox*upperAddress= new ShortHexSpinBox;
queriedRangeLayout->addRow(tr("Function 0x03 Minimum Set Value Address"),
lowerAddress);
queriedRangeLayout->addRow(tr("Function 0x03 Maximum Set Value Address"),
upperAddress);
queriedRangePlaceholder->setLayout(queriedRangeLayout);
boundsLayout->addWidget(queriedRangePlaceholder);
QWidget*fixedRangePlaceholder= new QWidget(this);
QFormLayout*fixedRangeLayout= new QFormLayout;
QLineEdit*fixedLower= new QLineEdit;
QLineEdit*fixedUpper= new QLineEdit;
fixedRangeLayout->addRow(tr("Minimum Set Value:"),fixedLower);
fixedRangeLayout->addRow(tr("Maximum Set Value:"),fixedUpper);
fixedRangePlaceholder->setLayout(fixedRangeLayout);
boundsLayout->addWidget(fixedRangePlaceholder);
layout->addLayout(boundsLayout);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 16443 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="readaddress")
{
readAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="writeaddress")
{
writeAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="fixedrange")
{
if(node.attribute("value")=="true")
{
fixedRange->setCheckState(Qt::Checked);
}
else if(node.attribute("value")=="false")
{
fixedRange->setCheckState(Qt::Unchecked);
}
}
else if(node.attribute("name")=="fixedlower")
{
fixedLower->setText(node.attribute("value"));
}
else if(node.attribute("name")=="fixedupper")
{
fixedUpper->setText(node.attribute("value"));
}
else if(node.attribute("name")=="loweraddress")
{
lowerAddress->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="upperaddress")
{
upperAddress->setValue(node.attribute("value").toInt());
}
}
updateReadAddress(readAddress->value());
updateWriteAddress(writeAddress->value());
updateFixedRange(fixedRange->isChecked());
updateLower(fixedLower->text());
updateUpper(fixedUpper->text());
updateLowerAddress(lowerAddress->value());
updateUpperAddress(upperAddress->value());
connect(readAddress,SIGNAL(valueChanged(int)),
this,SLOT(updateReadAddress(int)));
connect(writeAddress,SIGNAL(valueChanged(int)),
this,SLOT(updateWriteAddress(int)));
connect(fixedRange,SIGNAL(toggled(bool)),this,SLOT(updateFixedRange(bool)));
connect(fixedLower,SIGNAL(textChanged(QString)),
this,SLOT(updateLower(QString)));
connect(fixedUpper,SIGNAL(textChanged(QString)),
this,SLOT(updateUpper(QString)));
connect(lowerAddress,SIGNAL(valueChanged(int)),
this,SLOT(updateLowerAddress(int)));
connect(upperAddress,SIGNAL(valueChanged(int)),
this,SLOT(updateUpperAddress(int)));
setLayout(layout);
}

void ModbusRtuDeviceTSvConfWidget::updateReadAddress(int newAddress)
{
updateAttribute("readaddress",QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateWriteAddress(int newAddress)
{
updateAttribute("writeaddress",QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateFixedRange(bool fixed)
{
if(fixed)
{
updateAttribute("fixedrange","true");
boundsLayout->setCurrentIndex(1);
}
else
{
updateAttribute("fixedrange","false");
boundsLayout->setCurrentIndex(0);
}
}

void ModbusRtuDeviceTSvConfWidget::updateLower(const QString&lower)
{
updateAttribute("fixedlower",lower);
}

void ModbusRtuDeviceTSvConfWidget::updateUpper(const QString&upper)
{
updateAttribute("fixedupper",upper);
}

void ModbusRtuDeviceTSvConfWidget::updateLowerAddress(int newAddress)
{
updateAttribute("loweraddress",QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateUpperAddress(int newAddress)
{
updateAttribute("upperaddress",QString("%1").arg(newAddress));
}

/*:687*/
#line 822 "./typica.w"

/*643:*/
#line 15057 "./typica.w"

RoasterConfWidget::RoasterConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QVBoxLayout*layout= new QVBoxLayout;
QPushButton*addDeviceButton= new QPushButton(tr("Add Device"));
QMenu*deviceMenu= new QMenu;
NodeInserter*insertAction;
foreach(insertAction,AppInstance->topLevelNodeInserters)
{
connect(insertAction,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
deviceMenu->addAction(insertAction);
}
addDeviceButton->setMenu(deviceMenu);
layout->addWidget(addDeviceButton);
QPushButton*addAnnotationControlButton= new QPushButton(tr("Add Annotation Control"));
QMenu*annotationMenu= new QMenu;
NodeInserter*basicButtonInserter= new NodeInserter(tr("Annotation Button"),tr("Annotation Button"),"annotationbutton");
NodeInserter*countingButtonInserter= new NodeInserter(tr("Counting Button"),tr("Counting Button"),"reconfigurablebutton");
NodeInserter*spinBoxInserter= new NodeInserter(tr("Numeric Entry"),tr("Numeric Entry"),"annotationspinbox");
annotationMenu->addAction(basicButtonInserter);
annotationMenu->addAction(countingButtonInserter);
annotationMenu->addAction(spinBoxInserter);
connect(basicButtonInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(countingButtonInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(spinBoxInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
addAnnotationControlButton->setMenu(annotationMenu);
layout->addWidget(addAnnotationControlButton);
QPushButton*advancedButton= new QPushButton(tr("Advanced Features"));
QMenu*advancedMenu= new QMenu;
NodeInserter*linearsplineinserter= new NodeInserter(tr("Linear Spline Interpolated Series"),tr("Linear Spline Interpolated Series"),"linearspline");
advancedMenu->addAction(linearsplineinserter);
NodeInserter*translationinserter= new NodeInserter(tr("Profile Translation"),tr("Profile Translation"),"translation");
advancedMenu->addAction(translationinserter);
connect(linearsplineinserter,SIGNAL(triggered(QString,QString)),this,SLOT(insertChildNode(QString,QString)));
connect(translationinserter,SIGNAL(triggered(QString,QString)),this,SLOT(insertChildNode(QString,QString)));
advancedButton->setMenu(advancedMenu);
layout->addWidget(advancedButton);
QHBoxLayout*idLayout= new QHBoxLayout;
QLabel*idLabel= new QLabel(tr("Machine ID for database:"));
idLayout->addWidget(idLabel);
QSpinBox*id= new QSpinBox;
idLayout->addWidget(id);
layout->addLayout(idLayout);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 15105 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="databaseid")
{
id->setValue(node.attribute("value").toInt());
break;
}
}
updateRoasterId(id->value());
connect(id,SIGNAL(valueChanged(int)),this,SLOT(updateRoasterId(int)));
setLayout(layout);
}

/*:643*//*645:*/
#line 15137 "./typica.w"

void RoasterConfWidget::updateRoasterId(int id)
{
updateAttribute("databaseid",QString("%1").arg(id));
}

/*:645*/
#line 823 "./typica.w"

/*691:*/
#line 16593 "./typica.w"

AnnotationButtonConfWidget::AnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*buttonTextEdit= new QLineEdit;
QLineEdit*annotationTextEdit= new QLineEdit;
layout->addRow(tr("Button Text:"),buttonTextEdit);
layout->addRow(tr("Annotation Text:"),annotationTextEdit);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 16602 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="buttontext")
{
buttonTextEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="annotationtext")
{
annotationTextEdit->setText(node.attribute("value"));
}
}
updateButtonText(buttonTextEdit->text());
updateAnnotationText(annotationTextEdit->text());
connect(buttonTextEdit,SIGNAL(textEdited(QString)),this,SLOT(updateButtonText(QString)));
connect(annotationTextEdit,SIGNAL(textEdited(QString)),this,SLOT(updateAnnotationText(QString)));
setLayout(layout);
}

/*:691*//*692:*/
#line 16624 "./typica.w"

void AnnotationButtonConfWidget::updateButtonText(const QString&text)
{
updateAttribute("buttontext",text);
}

void AnnotationButtonConfWidget::updateAnnotationText(const QString&text)
{
updateAttribute("annotationtext",text);
}

/*:692*//*695:*/
#line 16662 "./typica.w"

ReconfigurableAnnotationButtonConfWidget::ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*buttonTextEdit= new QLineEdit;
QLineEdit*annotationTextEdit= new QLineEdit;
layout->addRow(tr("Button Text:"),buttonTextEdit);
layout->addRow(tr("Annotation Text:"),annotationTextEdit);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 16671 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="buttontext")
{
buttonTextEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="annotationtext")
{
annotationTextEdit->setText(node.attribute("value"));
}
}
updateButtonText(buttonTextEdit->text());
updateAnnotationText(annotationTextEdit->text());
connect(buttonTextEdit,SIGNAL(textEdited(QString)),this,SLOT(updateButtonText(QString)));
connect(annotationTextEdit,SIGNAL(textEdited(QString)),this,SLOT(updateAnnotationText(QString)));
QTextEdit*documentation= new QTextEdit;
documentation->setHtml(tr("If the <b>Annotation Text</b> contains <tt>%1</tt>, this will be replaced in the annotation with a number that increments each time the button is pressed."));
documentation->setReadOnly(true);
layout->addRow("",documentation);
setLayout(layout);
}

void ReconfigurableAnnotationButtonConfWidget::updateButtonText(const QString&text)
{
updateAttribute("buttontext",text);
}

void ReconfigurableAnnotationButtonConfWidget::updateAnnotationText(const QString&text)
{
updateAttribute("annotationtext",text);
}

/*:695*/
#line 824 "./typica.w"

/*698:*/
#line 16739 "./typica.w"

NoteSpinConfWidget::NoteSpinConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*labelEdit= new QLineEdit;
layout->addRow(tr("Control Label: "),labelEdit);
QLineEdit*minimumEdit= new QLineEdit;
layout->addRow(tr("Minimum Value: "),minimumEdit);
QLineEdit*maximumEdit= new QLineEdit;
layout->addRow(tr("Maximum Value: "),maximumEdit);
QSpinBox*precisionEdit= new QSpinBox;
precisionEdit->setMinimum(0);
precisionEdit->setMaximum(9);
layout->addRow(tr("Precision"),precisionEdit);
QLineEdit*pretext= new QLineEdit;
layout->addRow(tr("Prefix text"),pretext);
QLineEdit*posttext= new QLineEdit;
layout->addRow(tr("Suffix text"),posttext);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 16758 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="label")
{
labelEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="minimum")
{
minimumEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="maximum")
{
maximumEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="precision")
{
precisionEdit->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="pretext")
{
pretext->setText(node.attribute("value"));
}
else if(node.attribute("name")=="posttext")
{
posttext->setText(node.attribute("value"));
}
}
updateLabel(labelEdit->text());
updateMinimum(minimumEdit->text());
updateMaximum(maximumEdit->text());
updatePrecision(precisionEdit->value());
updatePretext(pretext->text());
updatePosttext(posttext->text());
connect(labelEdit,SIGNAL(textEdited(QString)),this,SLOT(updateLabel(QString)));
connect(minimumEdit,SIGNAL(textEdited(QString)),this,SLOT(updateMinimum(QString)));
connect(maximumEdit,SIGNAL(textEdited(QString)),this,SLOT(updateMaximum(QString)));
connect(precisionEdit,SIGNAL(valueChanged(int)),this,SLOT(updatePrecision(int)));
connect(pretext,SIGNAL(textEdited(QString)),this,SLOT(updatePretext(QString)));
connect(posttext,SIGNAL(textEdited(QString)),this,SLOT(updatePosttext(QString)));
setLayout(layout);
}

void NoteSpinConfWidget::updateLabel(const QString&text)
{
updateAttribute("label",text);
}

void NoteSpinConfWidget::updateMinimum(const QString&minimum)
{
updateAttribute("minimum",minimum);
}

void NoteSpinConfWidget::updateMaximum(const QString&maximum)
{
updateAttribute("maximum",maximum);
}

void NoteSpinConfWidget::updatePrecision(int precision)
{
updateAttribute("precision",QString("%1").arg(precision));
}

void NoteSpinConfWidget::updatePretext(const QString&text)
{
updateAttribute("pretext",text);
}

void NoteSpinConfWidget::updatePosttext(const QString&text)
{
updateAttribute("posttext",text);
}

/*:698*/
#line 825 "./typica.w"

/*259:*/
#line 6838 "./typica.w"

LinearCalibrator::LinearCalibrator(QObject*parent):
QObject(parent),Lo1(0),Lo2(0),Up1(1),Up2(1),sensitivitySetting(0.0),clamp(false)
{

}

/*:259*//*260:*/
#line 6852 "./typica.w"

void LinearCalibrator::newMeasurement(Measurement measure)
{
double outval= Lo1+(measure.temperature()-Lo2)*(Up1-Lo1)/(Up2-Lo2);
if(clamp)
{
if(outval<Lo1)
{
outval= Lo1;
}
else if(outval> Up1)
{
outval= Up1;
}
}
if(sensitivitySetting>=0.05)
{
int temp= qRound(outval/sensitivitySetting);
outval= temp*sensitivitySetting;
}
Measurement adjusted(outval,measure.time(),measure.scale());
emit measurement(adjusted);
}

/*:260*//*261:*/
#line 6878 "./typica.w"

double LinearCalibrator::measuredLower()
{
return Lo2;
}

double LinearCalibrator::measuredUpper()
{
return Up2;
}

double LinearCalibrator::mappedLower()
{
return Lo1;
}

double LinearCalibrator::mappedUpper()
{
return Up1;
}

bool LinearCalibrator::isClosedRange()
{
return clamp;
}

void LinearCalibrator::setMeasuredLower(double lower)
{
Lo2= lower;
}

void LinearCalibrator::setMeasuredUpper(double upper)
{
Up2= upper;
}

void LinearCalibrator::setMappedLower(double lower)
{
Lo1= lower;
}

void LinearCalibrator::setMappedUpper(double upper)
{
Up1= upper;
}

void LinearCalibrator::setClosedRange(bool closed)
{
clamp= closed;
}

void LinearCalibrator::setSensitivity(double sensitivity)
{
sensitivitySetting= sensitivity;
}

double LinearCalibrator::sensitivity()
{
return sensitivitySetting;
}

/*:261*/
#line 826 "./typica.w"

/*266:*/
#line 7011 "./typica.w"

void LinearSplineInterpolator::add_pair(double source,double destination)
{
pairs->insert(source,destination);
make_interpolators();
}

void LinearSplineInterpolator::make_interpolators()
{
if(pairs->size()> 1)
{
while(interpolators->size()> 0)
{
LinearCalibrator*removed= interpolators->takeFirst();
removed->deleteLater();
}
QMap<double,double> ::const_iterator i= pairs->constBegin();
QMap<double,double> ::const_iterator j= i+1;
while(j!=pairs->constEnd())
{
LinearCalibrator*segment= new LinearCalibrator();
segment->setMeasuredLower(i.key());
segment->setMappedLower(i.value());
segment->setMeasuredUpper(j.key());
segment->setMappedUpper(j.value());
segment->setClosedRange(false);
interpolators->append(segment);
connect(segment,SIGNAL(measurement(Measurement)),this,SIGNAL(newData(Measurement)));
i++;
j++;
}
}
}

LinearSplineInterpolator::LinearSplineInterpolator(QObject*parent):
QObject(parent),pairs(new QMap<double,double> ),
interpolators(new QList<LinearCalibrator*> )
{

}

void LinearSplineInterpolator::newMeasurement(Measurement measure)
{
QMap<double,double> ::const_iterator i= pairs->constBegin();
int index= -1;
while(i!=pairs->constEnd())
{
if(measure.temperature()<=i.key())
{
break;
}
i++;
index++;
}
if(index<0)
{
index= 0;
}
if(index>=interpolators->size())
{
index= interpolators->size()-1;
}
if(interpolators->at(index)!=NULL)
{
interpolators->at(index)->newMeasurement(measure);
}
}

/*:266*/
#line 827 "./typica.w"

/*720:*/
#line 18040 "./typica.w"

LinearSplineInterpolationConfWidget::LinearSplineInterpolationConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),knotmodel(new SaltModel(2))
{
QFormLayout*layout= new QFormLayout;
QLineEdit*source= new QLineEdit;
layout->addRow(tr("Source column name:"),source);
QLineEdit*destination= new QLineEdit;
layout->addRow(tr("Destination column name:"),destination);
knotmodel->setHeaderData(0,Qt::Horizontal,"Input");
knotmodel->setHeaderData(1,Qt::Horizontal,"Output");
QTableView*mappingTable= new QTableView;
mappingTable->setModel(knotmodel);
NumericDelegate*delegate= new NumericDelegate;
mappingTable->setItemDelegate(delegate);
layout->addRow(tr("Mapping data:"),mappingTable);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 18056 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="source")
{
source->setText(node.attribute("value"));
}
else if(node.attribute("name")=="destination")
{
destination->setText(node.attribute("value"));
}
else if(node.attribute("name")=="sourcevalues")
{
/*721:*/
#line 18095 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:721*/
#line 18070 "./typica.w"

int column= 0;
/*722:*/
#line 18107 "./typica.w"

for(int i= 0;i<itemList.size();i++)
{
knotmodel->setData(knotmodel->index(i,column),
QVariant(itemList.at(i).toDouble()),
Qt::DisplayRole);
}

/*:722*/
#line 18072 "./typica.w"


}
else if(node.attribute("name")=="destinationvalues")
{
/*721:*/
#line 18095 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:721*/
#line 18077 "./typica.w"

int column= 1;
/*722:*/
#line 18107 "./typica.w"

for(int i= 0;i<itemList.size();i++)
{
knotmodel->setData(knotmodel->index(i,column),
QVariant(itemList.at(i).toDouble()),
Qt::DisplayRole);
}

/*:722*/
#line 18079 "./typica.w"

}
}
updateSourceColumn(source->text());
updateDestinationColumn(destination->text());
updateKnots();
connect(source,SIGNAL(textEdited(QString)),this,SLOT(updateSourceColumn(QString)));
connect(destination,SIGNAL(textEdited(QString)),this,SLOT(updateDestinationColumn(QString)));
connect(knotmodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateKnots()));
setLayout(layout);
}

/*:720*//*723:*/
#line 18118 "./typica.w"

void LinearSplineInterpolationConfWidget::updateKnots()
{
updateAttribute("sourcevalues",knotmodel->arrayLiteral(0,Qt::DisplayRole));
updateAttribute("destinationvalues",knotmodel->arrayLiteral(1,Qt::DisplayRole));
}

void LinearSplineInterpolationConfWidget::updateSourceColumn(const QString&source)
{
updateAttribute("source",source);
}

void LinearSplineInterpolationConfWidget::updateDestinationColumn(const QString&dest)
{
updateAttribute("destination",dest);
}

/*:723*/
#line 828 "./typica.w"

/*726:*/
#line 18161 "./typica.w"

TranslationConfWidget::TranslationConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
temperatureValue(new QDoubleSpinBox),unitSelector(new QComboBox)
{
unitSelector->addItem("Fahrenheit");
unitSelector->addItem("Celsius");
temperatureValue->setMinimum(0);
temperatureValue->setMaximum(1000);
QFormLayout*layout= new QFormLayout;
QLineEdit*column= new QLineEdit;
layout->addRow(tr("Column to match:"),column);
layout->addRow(tr("Unit:"),unitSelector);
layout->addRow(tr("Value:"),temperatureValue);
/*644:*/
#line 15127 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:644*/
#line 18175 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="column")
{
column->setText(node.attribute("value"));
}
else if(node.attribute("name")=="unit")
{
unitSelector->setCurrentIndex(unitSelector->findText(node.attribute("value")));
}
else if(node.attribute("name")=="value")
{
temperatureValue->setValue(node.attribute("value").toDouble());
}
}
updateMatchingColumn(column->text());
updateTemperature();
connect(column,SIGNAL(textEdited(QString)),this,SLOT(updateMatchingColumn(QString)));
connect(unitSelector,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateTemperature()));
connect(temperatureValue,SIGNAL(valueChanged(double)),this,SLOT(updateTemperature()));
setLayout(layout);
}

/*:726*//*727:*/
#line 18204 "./typica.w"

void TranslationConfWidget::updateTemperature()
{
updateAttribute("unit",unitSelector->currentText());
updateAttribute("value",QString("%1").arg(temperatureValue->value()));
if(unitSelector->currentText()=="Fahrenheit")
{
updateAttribute("FValue",QString("%1").arg(temperatureValue->value()));
}
else
{
updateAttribute("FValue",QString("%1").arg(temperatureValue->value()*9/5+32));
}
}

void TranslationConfWidget::updateMatchingColumn(const QString&column)
{
updateAttribute("column",column);
}

/*:727*/
#line 829 "./typica.w"


/*:16*/
#line 757 "./typica.w"

/*19:*/
#line 882 "./typica.w"

template<class TYPE> TYPE getself(QScriptContext*context)
{
TYPE self= qobject_cast<TYPE> (context->thisObject().toQObject());
return self;
}

template<> QTime getself(QScriptContext*context)
{
QTime self= context->thisObject().toVariant().toTime();
return self;
}

template<> SqlQueryConnection*getself(QScriptContext*context)
{
SqlQueryConnection*self= 
(SqlQueryConnection*)qscriptvalue_cast<void*> (context->thisObject());
return self;
}

template<> QXmlQuery*getself(QScriptContext*context)
{
QXmlQuery*self= 
(QXmlQuery*)qscriptvalue_cast<void*> (context->thisObject());
return self;
}

template<> QXmlStreamWriter*getself(QScriptContext*context)
{
QXmlStreamWriter*self= 
(QXmlStreamWriter*)qscriptvalue_cast<void*> (context->thisObject());
return self;
}

template<> QXmlStreamReader*getself(QScriptContext*context)
{
QXmlStreamReader*self= 
(QXmlStreamReader*)qscriptvalue_cast<void*> (context->thisObject());
return self;
}

/*:19*//*20:*/
#line 927 "./typica.w"

template<class TYPE> TYPE argument(int arg,QScriptContext*context)
{
TYPE argument= qobject_cast<TYPE> (context->argument(arg).toQObject());
return argument;
}

template<> QString argument(int arg,QScriptContext*context)
{
return context->argument(arg).toString();
}

template<> QVariant argument(int arg,QScriptContext*context)
{
return context->argument(arg).toVariant();
}

template<> int argument(int arg,QScriptContext*context)
{
return context->argument(arg).toInt32();
}

template<> SqlQueryConnection*argument(int arg,QScriptContext*context)
{
return(SqlQueryConnection*)
qscriptvalue_cast<void*> (context->argument(arg));
}

template<> QModelIndex argument(int arg,QScriptContext*context)
{
return qscriptvalue_cast<QModelIndex> (context->argument(arg));
}

/*:20*//*24:*/
#line 1004 "./typica.w"

void setQObjectProperties(QScriptValue,QScriptEngine*)
{

}

/*:24*//*26:*/
#line 1018 "./typica.w"

void setQPaintDeviceProperties(QScriptValue,QScriptEngine*)
{

}

void setQLayoutItemProperties(QScriptValue,QScriptEngine*)
{

}

/*:26*//*29:*/
#line 1057 "./typica.w"

QScriptValue constructQWidget(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QWidget);
setQWidgetProperties(object,engine);
return object;
}

void setQWidgetProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
setQPaintDeviceProperties(value,engine);
value.setProperty("setLayout",engine->newFunction(QWidget_setLayout));
value.setProperty("activateWindow",
engine->newFunction(QWidget_activateWindow));
}

/*:29*//*30:*/
#line 1079 "./typica.w"

QScriptValue QWidget_setLayout(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QWidget*self= getself<QWidget*> (context);
QLayout*layout= argument<QLayout*> (0,context);
if(layout)
{
self->setLayout(layout);
}
else
{
context->throwError("Incorrect argument type passed to "
"QWidget::setLayout(). This method requires "
"a QLayout.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QWidget::setLayout(). This method takes one "
"QLayout as an argument.");
}
return QScriptValue();
}

QScriptValue QWidget_activateWindow(QScriptContext*context,
QScriptEngine*)
{
QWidget*self= getself<QWidget*> (context);
self->activateWindow();
return QScriptValue();
}

/*:30*//*32:*/
#line 1153 "./typica.w"

ScriptQMainWindow::ScriptQMainWindow():QMainWindow(NULL)
{

}

void ScriptQMainWindow::saveSizeAndPosition(const QString&key)
{
QSettings settings;
settings.beginGroup(key);
settings.setValue("pos",pos());
settings.setValue("size",size());
settings.endGroup();
}

void ScriptQMainWindow::restoreSizeAndPosition(const QString&key)
{
QSettings settings;
settings.beginGroup(key);
if(settings.contains("size"))
{
resize(settings.value("size").toSize());
}
if(settings.contains("pos"))
{
move(settings.value("pos").toPoint());
}
settings.endGroup();
}

void ScriptQMainWindow::displayStatus(const QString&message)
{
statusBar()->showMessage(message);
}

void ScriptQMainWindow::showEvent(QShowEvent*event)
{
if(!event->spontaneous())
{
/*34:*/
#line 1227 "./typica.w"

QSettings settings;
restoreGeometry(settings.value(QString("geometries/%1").arg(objectName())).
toByteArray());

/*:34*/
#line 1192 "./typica.w"

event->accept();
}
else
{
event->ignore();
}
}

void ScriptQMainWindow::show()
{
QMainWindow::show();
}

void ScriptQMainWindow::closeEvent(QCloseEvent*event)
{
emit aboutToClose();
/*33:*/
#line 1221 "./typica.w"

QSettings settings;
settings.setValue(QString("geometries/%1").arg(objectName()),saveGeometry());

/*:33*/
#line 1209 "./typica.w"

event->accept();
}

/*:32*//*37:*/
#line 1255 "./typica.w"

QScriptValue constructQMainWindow(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new ScriptQMainWindow);
setQMainWindowProperties(object,engine);
return object;
}

void setQMainWindowProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("setCentralWidget",
engine->newFunction(QMainWindow_setCentralWidget));
value.setProperty("menuBar",engine->newFunction(QMainWindow_menuBar));
}

/*:37*//*38:*/
#line 1277 "./typica.w"

QScriptValue QMainWindow_setCentralWidget(QScriptContext*context,
QScriptEngine*)
{
if(context->argumentCount()==1)
{
QMainWindow*self= getself<QMainWindow*> (context);
QWidget*widget= argument<QWidget*> (0,context);
if(widget)
{
self->setCentralWidget(widget);
}
else
{
context->throwError("Incorrect argument type passed to "
"QMainWindow::setCentralWidget(). This "
"method requires a QWidget.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QMainWindow::setCentralWidget(). This method "
"takes one QWidget as an argument.");
}
return QScriptValue();
}

/*:38*//*39:*/
#line 1311 "./typica.w"

QScriptValue QMainWindow_menuBar(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==0)
{
QMainWindow*self= getself<QMainWindow*> (context);
QMenuBar*bar= self->menuBar();
object= engine->newQObject(bar);
setQMenuBarProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QMainWindow::menuBar(). This method takes no "
"arguments.");
}
return object;
}

/*:39*//*41:*/
#line 1341 "./typica.w"

void setQMenuBarProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("addMenu",engine->newFunction(QMenuBar_addMenu));
}

/*:41*//*42:*/
#line 1356 "./typica.w"

QScriptValue QMenuBar_addMenu(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==1)
{
QMenuBar*self= getself<QMenuBar*> (context);
QString title= argument<QString> (0,context);
object= engine->newQObject(self->addMenu(title));
setQMenuProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QMenuBar::addMenu(). This method takes one "
"string as an argument.");
}
return object;
}

/*:42*//*44:*/
#line 1386 "./typica.w"

void setQMenuProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("addAction",engine->newFunction(QMenu_addAction));
value.setProperty("addSeparator",engine->newFunction(QMenu_addSeparator));
}

/*:44*//*45:*/
#line 1396 "./typica.w"

QScriptValue QMenu_addAction(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QMenu*self= getself<QMenu*> (context);
QAction*action= argument<QAction*> (0,context);
if(action)
{
self->addAction(action);
}
else
{
context->throwError("Incorrect argument type passed to "
"QMenu::addAction(). This method requires a "
"QAction.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QMenu::addAction(). This method takes one "
"QAction as an argument.");
}
return QScriptValue();
}

QScriptValue QMenu_addSeparator(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==0)
{
QMenu*self= getself<QMenu*> (context);
self->addSeparator();
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QMenu::addSeparator(). This method takes no "
"arguments.");
}
return QScriptValue();
}

/*:45*//*48:*/
#line 1458 "./typica.w"

QScriptValue constructQFrame(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QFrame);
setQFrameProperties(object,engine);
return object;
}

void setQFrameProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:48*//*51:*/
#line 1492 "./typica.w"

QScriptValue constructQLabel(QScriptContext*context,QScriptEngine*engine)
{
QString text;
if(context->argumentCount()==1)
{
text= argument<QString> (0,context);
}
QScriptValue object= engine->newQObject(new QLabel(text));
setQLabelProperties(object,engine);
return object;
}

void setQLabelProperties(QScriptValue value,QScriptEngine*engine)
{
setQFrameProperties(value,engine);
}

/*:51*//*54:*/
#line 1538 "./typica.w"

QScriptValue constructQSplitter(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QSplitter);
setQSplitterProperties(object,engine);
return object;
}

void setQSplitterProperties(QScriptValue value,QScriptEngine*engine)
{
setQFrameProperties(value,engine);
value.setProperty("addWidget",engine->newFunction(QSplitter_addWidget));
value.setProperty("saveState",engine->newFunction(QSplitter_saveState));
value.setProperty("restoreState",
engine->newFunction(QSplitter_restoreState));
}

/*:54*//*55:*/
#line 1558 "./typica.w"

QScriptValue QSplitter_addWidget(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QSplitter*self= getself<QSplitter*> (context);
QWidget*widget= argument<QWidget*> (0,context);
if(widget)
{
self->addWidget(widget);
}
else
{
context->throwError("Incorrect argument type passed to "
"QSplitter::addWidget(). This method "
"requires a QWidget.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QSplitter::addWidget(). This method takes one "
"QWidget as an argument.");
}
return QScriptValue();
}

/*:55*//*56:*/
#line 1591 "./typica.w"

QScriptValue QSplitter_saveState(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QSplitter*self= getself<QSplitter*> (context);
QString key= argument<QString> (0,context);
QSettings settings;
settings.setValue(key,self->saveState());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QSplitter::saveState(). This method takes one "
"string as an argument.");
}
return QScriptValue();
}

QScriptValue QSplitter_restoreState(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QSplitter*self= getself<QSplitter*> (context);
QString key= argument<QString> (0,context);
QSettings settings;
self->restoreState(settings.value(key).toByteArray());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QSplitter::restoreState(). This method takes "
"one string as an argument.");
}
return QScriptValue();
}

/*:56*//*58:*/
#line 1644 "./typica.w"

void setQLayoutProperties(QScriptValue value,QScriptEngine*engine)
{
setQLayoutItemProperties(value,engine);
value.setProperty("addWidget",engine->newFunction(QLayout_addWidget));
}

QScriptValue QLayout_addWidget(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QLayout*self= getself<QLayout*> (context);
QWidget*widget= argument<QWidget*> (0,context);
if(widget)
{
self->addWidget(widget);
}
else
{
context->throwError("Incorrect argument type passed to "
"QLayout::addWidget(). This method requires "
"a QWidget.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QLayout::addWidget(). This method takes one "
"QWidget as an argument.");
}
return QScriptValue();
}

/*:58*//*61:*/
#line 1711 "./typica.w"

QScriptValue constructQBoxLayout(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new QBoxLayout(QBoxLayout::LeftToRight));
setQBoxLayoutProperties(object,engine);
return object;
}

void setQBoxLayoutProperties(QScriptValue value,QScriptEngine*engine)
{
setQLayoutProperties(value,engine);
value.setProperty("addLayout",engine->newFunction(QBoxLayout_addLayout));
value.setProperty("addWidget",engine->newFunction(QBoxLayout_addWidget));
}

QScriptValue QBoxLayout_addLayout(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()> 0&&context->argumentCount()<3)
{
QBoxLayout*self= getself<QBoxLayout*> (context);
QLayout*layout= argument<QLayout*> (0,context);
int stretch= 0;
if(context->argumentCount()==2)
{
stretch= argument<int> (1,context);
}
if(layout)
{
self->addLayout(layout,stretch);
}
else
{
context->throwError("Incorrect argument type passed to "
"QLayout::addLayout(). This method requires "
"a QLayout.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QLayout::addLayout(). This method takes one "
"QLayout as an argument and optionally one integer.");
}
return QScriptValue();
}

/*:61*//*62:*/
#line 1762 "./typica.w"

QScriptValue QBoxLayout_addWidget(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()> 0&&context->argumentCount()<4)
{
QBoxLayout*self= getself<QBoxLayout*> (context);
QWidget*widget= argument<QWidget*> (0,context);
int stretch= 0;
Qt::Alignment alignment= 0;
if(context->argumentCount()> 1)
{
stretch= argument<int> (1,context);
}
if(context->argumentCount()> 2)
{
alignment= (Qt::Alignment)(argument<int> (2,context));
}
if(widget)
{
self->addWidget(widget,stretch,alignment);
}
else
{
context->throwError("Incorrect argument type passed to "
"QBoxLayout::addWidget(). This method requires "
"a QWidget.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QBoxLayout::addWidget(). This method takes one "
"QWidget and optionally up to two integers as "
"arguments.");
}
return QScriptValue();
}

/*:62*//*65:*/
#line 1826 "./typica.w"

QScriptValue constructQAction(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QAction(NULL));
setQActionProperties(object,engine);
return object;
}

void setQActionProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("setShortcut",engine->newFunction(QAction_setShortcut));
}

QScriptValue QAction_setShortcut(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==1)
{
QAction*self= getself<QAction*> (context);
self->setShortcut(argument<QString> (0,context));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QAction::setShortcut(). This method takes one "
"string as an argument.");
}
return QScriptValue();
}

/*:65*//*68:*/
#line 1884 "./typica.w"

QScriptValue QFileDialog_getOpenFileName(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==3)
{
QWidget*widget= argument<QWidget*> (0,context);
if(widget)
{
QString caption= argument<QString> (1,context);
QString dir= argument<QString> (2,context);
retval= QScriptValue(engine,
QFileDialog::getOpenFileName(widget,caption,
dir,"",0,0));
setQFileDialogProperties(retval,engine);
}
else
{
context->throwError("Incorrect argument type passed to "
"QFileDialog::getOpenFileName(). The first "
"argument to this method must be a QWidget.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QFileDialog::getOpenFileName(). This method "
"takes one QWidget followed by two strings for a "
"total of three arguments.");
}
return retval;
}

/*:68*//*69:*/
#line 1920 "./typica.w"

QScriptValue QFileDialog_getSaveFileName(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==3)
{
QWidget*widget= argument<QWidget*> (0,context);
if(widget)
{
QString caption= argument<QString> (1,context);
QString dir= argument<QString> (2,context);
retval= QScriptValue(engine,
QFileDialog::getSaveFileName(widget,caption,
dir,"",0,0));

setQFileDialogProperties(retval,engine);
}
else
{
context->throwError("Incorrect argument type passed to "
"QFileDialog::getSaveFileName(). The first "
"argument to this method must be a QWidget.");
}
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QFileDialog::getSaveFileName(). This method "
"takes one QWidget followed by two strings for a "
"total of three arguments.");
}
return retval;
}

/*:69*//*70:*/
#line 1957 "./typica.w"

void setQFileDialogProperties(QScriptValue value,QScriptEngine*engine)
{
setQDialogProperties(value,engine);
}

void setQDialogProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:70*//*73:*/
#line 1992 "./typica.w"

QScriptValue constructQFile(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new QFile(argument<QString> (0,context)));
setQFileProperties(object,engine);
return object;
}

/*:73*//*74:*/
#line 2003 "./typica.w"

void setQFileProperties(QScriptValue value,QScriptEngine*engine)
{
setQIODeviceProperties(value,engine);
value.setProperty("remove",engine->newFunction(QFile_remove));
}

QScriptValue QFile_remove(QScriptContext*context,QScriptEngine*engine)
{
QFile*self= getself<QFile*> (context);
bool retval= self->remove();
return QScriptValue(engine,retval);
}

/*:74*//*75:*/
#line 2025 "./typica.w"

void setQIODeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("open",engine->newFunction(QIODevice_open));
value.setProperty("close",engine->newFunction(QIODevice_close));
value.setProperty("readToString",
engine->newFunction(QIODevice_readToString));
}

/*:75*//*76:*/
#line 2040 "./typica.w"

QScriptValue QIODevice_open(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
if(context->argumentCount()==1)
{
switch(argument<int> (0,context))
{
case 1:
self->open(QIODevice::ReadOnly);
break;
case 2:
self->open(QIODevice::WriteOnly);
break;
case 3:
self->open(QIODevice::ReadWrite);
break;
default:
break;
}
}
else
{
self->open(QIODevice::ReadWrite);
}
return QScriptValue();
}

QScriptValue QIODevice_close(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
self->close();
return QScriptValue();
}

/*:76*//*77:*/
#line 2079 "./typica.w"

QScriptValue QIODevice_readToString(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
self->reset();
return QScriptValue(QString(self->readAll()));
}

/*:77*//*80:*/
#line 2109 "./typica.w"

QScriptValue constructQBuffer(QScriptContext*context,QScriptEngine*engine)
{
QByteArray*array= new QByteArray(argument<QString> (0,context).toAscii());
QScriptValue object= engine->newQObject(new QBuffer(array));
setQBufferProperties(object,engine);
return object;
}

void setQBufferProperties(QScriptValue value,QScriptEngine*engine)
{
setQIODeviceProperties(value,engine);
value.setProperty("setData",engine->newFunction(QBuffer_setData));
}

QScriptValue QBuffer_setData(QScriptContext*context,QScriptEngine*)
{
QBuffer*self= getself<QBuffer*> (context);
self->setData(argument<QString> (0,context).toAscii());
return QScriptValue();
}

/*:80*//*83:*/
#line 2157 "./typica.w"

QScriptValue constructXQuery(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->toScriptValue<void*> (new QXmlQuery);
setXQueryProperties(object,engine);
return object;
}

void setXQueryProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("bind",engine->newFunction(XQuery_bind));
value.setProperty("exec",engine->newFunction(XQuery_exec));
value.setProperty("setQuery",engine->newFunction(XQuery_setQuery));
}

/*:83*//*84:*/
#line 2175 "./typica.w"

QScriptValue XQuery_bind(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
QIODevice*buffer= argument<QIODevice*> (1,context);
self->bindVariable(argument<QString> (0,context),buffer);
return QScriptValue();
}

/*:84*//*85:*/
#line 2186 "./typica.w"

QScriptValue XQuery_setQuery(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
self->setQuery(argument<QString> (0,context));
return QScriptValue();
}

/*:85*//*86:*/
#line 2196 "./typica.w"

QScriptValue XQuery_exec(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
QString result;
self->evaluateTo(&result);
return QScriptValue(result);
}

/*:86*//*89:*/
#line 2251 "./typica.w"

QScriptValue constructXmlWriter(QScriptContext*context,QScriptEngine*engine)
{
QXmlStreamWriter*retval;
if(context->argumentCount()==1)
{
retval= new QXmlStreamWriter(argument<QIODevice*> (0,context));
}
else
{
retval= new QXmlStreamWriter;
}
QScriptValue object= engine->toScriptValue<void*> (retval);
setXmlWriterProperties(object,engine);
return object;
}

void setXmlWriterProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("setDevice",engine->newFunction(XmlWriter_setDevice));
value.setProperty("writeAttribute",
engine->newFunction(XmlWriter_writeAttribute));
value.setProperty("writeCDATA",engine->newFunction(XmlWriter_writeCDATA));
value.setProperty("writeCharacters",
engine->newFunction(XmlWriter_writeCharacters));
value.setProperty("writeDTD",engine->newFunction(XmlWriter_writeDTD));
value.setProperty("writeEmptyElement",
engine->newFunction(XmlWriter_writeEmptyElement));
value.setProperty("writeEndDocument",
engine->newFunction(XmlWriter_writeEndDocument));
value.setProperty("writeEndElement",
engine->newFunction(XmlWriter_writeEndElement));
value.setProperty("writeEntityReference",
engine->newFunction(XmlWriter_writeEntityReference));
value.setProperty("writeProcessingInstruction",
engine->newFunction(XmlWriter_writeProcessingInstruction));
value.setProperty("writeStartDocument",
engine->newFunction(XmlWriter_writeStartDocument));
value.setProperty("writeStartElement",
engine->newFunction(XmlWriter_writeStartElement));
value.setProperty("writeTextElement",
engine->newFunction(XmlWriter_writeTextElement));
}

/*:89*//*90:*/
#line 2298 "./typica.w"

QScriptValue XmlWriter_setDevice(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
QIODevice*device= argument<QIODevice*> (0,context);
self->setDevice(device);
return QScriptValue();
}

/*:90*//*91:*/
#line 2312 "./typica.w"

QScriptValue XmlWriter_writeStartDocument(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeStartDocument(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeEndDocument(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeEndDocument();
return QScriptValue();
}

/*:91*//*92:*/
#line 2331 "./typica.w"

QScriptValue XmlWriter_writeDTD(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeDTD(argument<QString> (0,context));
return QScriptValue();
}

/*:92*//*93:*/
#line 2342 "./typica.w"

QScriptValue XmlWriter_writeStartElement(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeStartElement(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeAttribute(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeAttribute(argument<QString> (0,context),
argument<QString> (1,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeCharacters(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeCharacters(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeEndElement(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeEndElement();
return QScriptValue();
}

/*:93*//*94:*/
#line 2378 "./typica.w"

QScriptValue XmlWriter_writeEmptyElement(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeEmptyElement(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeTextElement(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeTextElement(argument<QString> (0,context),
argument<QString> (1,context));
return QScriptValue();
}

/*:94*//*95:*/
#line 2399 "./typica.w"

QScriptValue XmlWriter_writeCDATA(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeCDATA(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeEntityReference(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeEntityReference(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue XmlWriter_writeProcessingInstruction(QScriptContext*context,
QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeProcessingInstruction(argument<QString> (0,context),
argument<QString> (1,context));
return QScriptValue();
}

/*:95*//*98:*/
#line 2458 "./typica.w"

QScriptValue constructXmlReader(QScriptContext*context,QScriptEngine*engine)
{
QXmlStreamReader*retval= 
new QXmlStreamReader(argument<QIODevice*> (0,context));
QScriptValue object= engine->toScriptValue<void*> (retval);
setXmlReaderProperties(object,engine);
return object;
}

void setXmlReaderProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("atEnd",engine->newFunction(XmlReader_atEnd));
value.setProperty("attribute",engine->newFunction(XmlReader_attribute));
value.setProperty("hasAttribute",
engine->newFunction(XmlReader_hasAttribute));
value.setProperty("isDTD",engine->newFunction(XmlReader_isDTD));
value.setProperty("isStartElement",
engine->newFunction(XmlReader_isStartElement));
value.setProperty("name",engine->newFunction(XmlReader_name));
value.setProperty("readElementText",
engine->newFunction(XmlReader_readElementText));
value.setProperty("readNext",
engine->newFunction(XmlReader_readNext));
value.setProperty("text",engine->newFunction(XmlReader_text));
}

/*:98*//*99:*/
#line 2488 "./typica.w"

QScriptValue XmlReader_attribute(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
QString retval= 
self->attributes().value(argument<QString> (0,context)).toString();
return QScriptValue(retval);
}

QScriptValue XmlReader_hasAttribute(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
bool retval= 
self->attributes().hasAttribute(argument<QString> (0,context));
return QScriptValue(retval);
}

/*:99*//*100:*/
#line 2508 "./typica.w"

QScriptValue XmlReader_atEnd(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
return QScriptValue(self->atEnd());
}

QScriptValue XmlReader_isDTD(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
return QScriptValue(self->isDTD());
}

QScriptValue XmlReader_isStartElement(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
return QScriptValue(self->isStartElement());
}

/*:100*//*101:*/
#line 2529 "./typica.w"

QScriptValue XmlReader_readNext(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
self->readNext();
return QScriptValue();
}

/*:101*//*102:*/
#line 2539 "./typica.w"

QScriptValue XmlReader_name(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
return QScriptValue(self->name().toString());
}

QScriptValue XmlReader_readElementText(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
return QScriptValue(self->readElementText());
}

QScriptValue XmlReader_text(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
return QScriptValue(self->text().toString());
}

/*:102*//*105:*/
#line 2581 "./typica.w"

void setQSettingsProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("value",engine->newFunction(QSettings_value));
value.setProperty("setValue",engine->newFunction(QSettings_setValue));
}

/*:105*//*106:*/
#line 2593 "./typica.w"

QScriptValue QSettings_value(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==1||context->argumentCount()==2)
{
QSettings settings;
QString key= argument<QString> (0,context);
QVariant value;
QVariant retval;
if(context->argumentCount()> 1)
{
value= argument<QVariant> (1,context);
retval= settings.value(key,value);
}
else
{
retval= settings.value(key);
}
object= engine->newVariant(retval);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QSettings::value(). This method takes one "
"string and one optional variant type.");
}
return object;
}

QScriptValue QSettings_setValue(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==2)
{
QSettings settings;
QString key= argument<QString> (0,context);
QVariant value= argument<QVariant> (1,context);
settings.setValue(key,value);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QSettings::setValue(). This method takes one "
"string and one variant type for a total of two "
"arguments.");
}
return QScriptValue();
}

/*:106*//*109:*/
#line 2662 "./typica.w"

QScriptValue constructQLCDNumber(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QLCDNumber());
setQLCDNumberProperties(object,engine);
return object;
}

void setQLCDNumberProperties(QScriptValue value,QScriptEngine*engine)
{
setQFrameProperties(value,engine);
}

/*:109*//*112:*/
#line 2720 "./typica.w"

QScriptValue constructQTime(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==0||
(context->argumentCount()>=2&&context->argumentCount()<=4))
{
int arg1= 0;
int arg2= 0;
int arg3= 0;
int arg4= 0;
switch(context->argumentCount())
{
case 4:
arg4= argument<int> (3,context);
case 3:
arg3= argument<int> (2,context);
case 2:
arg2= argument<int> (1,context);
arg1= argument<int> (0,context);
default:
break;
}
if(context->argumentCount())
{
object= engine->toScriptValue<QTime> (QTime(arg1,arg2,arg3,
arg4));
}
else
{
object= engine->toScriptValue<QTime> (QTime());
}
setQTimeProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::QTime(). This method takes zero, two, "
"three, or four integer arguments.");
}
return object;
}

/*:112*//*113:*/
#line 2768 "./typica.w"

void setQTimeProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("addMSecs",engine->newFunction(QTime_addMSecs));
value.setProperty("addSecs",engine->newFunction(QTime_addSecs));
value.setProperty("elapsed",engine->newFunction(QTime_elapsed));
value.setProperty("hour",engine->newFunction(QTime_hour));
value.setProperty("isNull",engine->newFunction(QTime_isNull));
value.setProperty("isValid",engine->newFunction(QTime_isValid));
value.setProperty("minute",engine->newFunction(QTime_minute));
value.setProperty("msec",engine->newFunction(QTime_msec));
value.setProperty("msecsTo",engine->newFunction(QTime_msecsTo));
value.setProperty("restart",engine->newFunction(QTime_restart));
value.setProperty("second",engine->newFunction(QTime_second));
value.setProperty("secsTo",engine->newFunction(QTime_secsTo));
value.setProperty("setHMS",engine->newFunction(QTime_setHMS));
value.setProperty("start",engine->newFunction(QTime_start));
value.setProperty("toString",engine->newFunction(QTime_toString));
value.setProperty("currentTime",engine->newFunction(QTime_currentTime));
value.setProperty("fromString",engine->newFunction(QTime_fromString));
value.setProperty("valueOf",engine->newFunction(QTime_valueOf));
}

/*:113*//*114:*/
#line 2797 "./typica.w"

QScriptValue QTime_valueOf(QScriptContext*context,QScriptEngine*)
{
QTime self= getself<QTime> (context);
int retval= (self.hour()*60*60*1000)+(self.minute()*60*1000)+
(self.second()*1000)+self.msec();
return QScriptValue(retval);
}

/*:114*//*115:*/
#line 2811 "./typica.w"

QScriptValue QTime_addMSecs(QScriptContext*context,QScriptEngine*engine)
{
QTime time;
QScriptValue retval;
if(context->argumentCount()==1)
{
QTime self= getself<QTime> (context);
time= self.addMSecs(argument<int> (0,context));
retval= engine->toScriptValue<QTime> (time);
setQTimeProperties(retval,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::addMSecs(). This method takes one "
"integer as an argument.");
}
return retval;
}

QScriptValue QTime_addSecs(QScriptContext*context,QScriptEngine*engine)
{
QTime time;
QScriptValue retval;
if(context->argumentCount()==1)
{
QTime self= getself<QTime> (context);
time= self.addSecs(argument<int> (0,context));
retval= engine->toScriptValue<QTime> (time);
setQTimeProperties(retval,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::addSecs(). This method takes one "
"integer as an argument.");
}
return retval;
}

/*:115*//*116:*/
#line 2854 "./typica.w"

QScriptValue QTime_elapsed(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.elapsed());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::elapsed(). This method takes no "
"arguments.");
}
return retval;
}

/*:116*//*117:*/
#line 2875 "./typica.w"

QScriptValue QTime_hour(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.hour());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::hour(). This method takes no "
"arguments.");
}
return retval;
}

/*:117*//*118:*/
#line 2895 "./typica.w"

QScriptValue QTime_minute(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.minute());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::minute(). This method takes no "
"arguments.");
}
return retval;
}

QScriptValue QTime_second(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.second());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::second(). This method takes no "
"arguments.");
}
return retval;
}

QScriptValue QTime_msec(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.msec());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::msec(). This method takes no "
"arguments.");
}
return retval;
}

/*:118*//*119:*/
#line 2951 "./typica.w"

QScriptValue QTime_isNull(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.isNull());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::isNull(). This method takes no "
"arguments.");
}
return retval;
}

QScriptValue QTime_isValid(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.isValid());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::isValid(). This method takes no "
"arguments.");
}
return retval;
}

/*:119*//*120:*/
#line 2989 "./typica.w"

QScriptValue QTime_msecsTo(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==1)
{
QTime self= getself<QTime> (context);
QTime arg= argument<QVariant> (0,context).toTime();
retval= QScriptValue(engine,self.msecsTo(arg));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::msecsTo(). This method takes one QTime.");
}
return retval;
}

QScriptValue QTime_secsTo(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==1)
{
QTime self= getself<QTime> (context);
QTime arg= argument<QVariant> (0,context).toTime();
retval= QScriptValue(engine,self.secsTo(arg));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::secsTo(). This method takes one QTime.");
}
return retval;
}

/*:120*//*121:*/
#line 3028 "./typica.w"

QScriptValue QTime_restart(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.restart());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::restart(). This method takes no "
"arguments.");
}
return retval;
}

QScriptValue QTime_start(QScriptContext*context,QScriptEngine*)
{
if(context->argumentCount()==0)
{
QTime self= getself<QTime> (context);
self.start();
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::start(). This method takes no arguments.");
}
return QScriptValue();
}

/*:121*//*122:*/
#line 3064 "./typica.w"

QScriptValue QTime_setHMS(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==3||context->argumentCount()==4)
{
QTime self= getself<QTime> (context);
int arg1= 0;
int arg2= 0;
int arg3= 0;
int arg4= 0;
switch(context->argumentCount())
{
case 4:
arg4= argument<int> (3,context);
case 3:
arg3= argument<int> (2,context);
arg2= argument<int> (1,context);
arg1= argument<int> (0,context);
default:
break;
}
retval= QScriptValue(engine,self.setHMS(arg1,arg2,arg3,arg4));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::setHMS(). This method takes three or "
"four integer arguments.");
}
return retval;
}

/*:122*//*123:*/
#line 3100 "./typica.w"

QScriptValue QTime_toString(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue retval;
if(context->argumentCount()==1)
{
QTime self= getself<QTime> (context);
retval= QScriptValue(engine,self.toString(argument<QString> (0,context)));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::toString(). This method takes one QString "
"as an argument.");
}
return retval;
}

/*:123*//*124:*/
#line 3121 "./typica.w"

QScriptValue QTime_currentTime(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object;
object= engine->toScriptValue<QTime> (QTime::currentTime());
setQTimeProperties(object,engine);
return object;
}

QScriptValue QTime_fromString(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==2)
{
QString time= argument<QString> (0,context);
QString format= argument<QString> (1,context);
object= engine->toScriptValue<QTime> (QTime::fromString(time,format));
setQTimeProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QTime::fromString(). This method takes two "
"string arguments.");
}
return object;
}

/*:124*//*126:*/
#line 3161 "./typica.w"

void setQAbstractScrollAreaProperties(QScriptValue value,QScriptEngine*engine)
{
setQFrameProperties(value,engine);
}

/*:126*//*128:*/
#line 3175 "./typica.w"

void setQAbstractItemViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
}

/*:128*//*130:*/
#line 3189 "./typica.w"

void setQGraphicsViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
}

void setQTableViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractItemViewProperties(value,engine);
}

/*:130*//*133:*/
#line 3222 "./typica.w"

QScriptValue constructQPushButton(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QPushButton());
setQPushButtonProperties(object,engine);
return object;
}

void setQPushButtonProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractButtonProperties(value,engine);
}

void setQAbstractButtonProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:133*//*140:*/
#line 3334 "./typica.w"

QScriptValue constructQSqlQuery(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= 
engine->toScriptValue<void*> (new SqlQueryConnection());
setQSqlQueryProperties(object,engine);
return object;
}

/*:140*//*141:*/
#line 3346 "./typica.w"

void setQSqlQueryProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("bind",engine->newFunction(QSqlQuery_bind));
value.setProperty("bindFileData",
engine->newFunction(QSqlQuery_bindFileData));
value.setProperty("bindDeviceData",
engine->newFunction(QSqlQuery_bindDeviceData));
value.setProperty("exec",engine->newFunction(QSqlQuery_exec));
value.setProperty("executedQuery",engine->newFunction(QSqlQuery_executedQuery));
value.setProperty("invalidate",engine->newFunction(QSqlQuery_invalidate));
value.setProperty("next",engine->newFunction(QSqlQuery_next));
value.setProperty("prepare",engine->newFunction(QSqlQuery_prepare));
value.setProperty("value",engine->newFunction(QSqlQuery_value));
}

/*:141*//*142:*/
#line 3364 "./typica.w"

QScriptValue QSqlQuery_exec(QScriptContext*context,QScriptEngine*engine)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
QScriptValue retval;
if(context->argumentCount()==1)
{
retval= QScriptValue(engine,
query->exec(argument<QString> (0,context)));
}
else
{
retval= QScriptValue(engine,query->exec());
}
if(query->lastError().isValid())
{
qDebug()<<query->lastQuery();
qDebug()<<query->lastError().text();
}
return retval;
}

QScriptValue QSqlQuery_executedQuery(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
return QScriptValue(query->lastQuery());
}

QScriptValue QSqlQuery_next(QScriptContext*context,QScriptEngine*engine)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
return QScriptValue(engine,query->next());
}

QScriptValue QSqlQuery_value(QScriptContext*context,QScriptEngine*engine)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
return QScriptValue(engine,
query->value(argument<int> (0,context)).toString());
}

/*:142*//*143:*/
#line 3408 "./typica.w"

QScriptValue QSqlQuery_prepare(QScriptContext*context,QScriptEngine*engine)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
return QScriptValue(engine,query->prepare(argument<QString> (0,context)));
}

QScriptValue QSqlQuery_bind(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
query->bindValue(argument<QString> (0,context),
argument<QVariant> (1,context));
return QScriptValue();
}

QScriptValue QSqlQuery_bindFileData(QScriptContext*context,
QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
QString placeholder= argument<QString> (0,context);
QString filename= argument<QString> (1,context);
QFile file(filename);
QByteArray data;
if(file.open(QIODevice::ReadOnly))
{
data= file.readAll();
file.close();
}
query->bindValue(placeholder,data);
return QScriptValue();
}

QScriptValue QSqlQuery_bindDeviceData(QScriptContext*context,
QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
QString placeholder= argument<QString> (0,context);
QIODevice*device= argument<QIODevice*> (1,context);
device->reset();
QByteArray data;
data= device->readAll();
query->bindValue(placeholder,data);
return QScriptValue();
}

/*:143*//*144:*/
#line 3460 "./typica.w"

QScriptValue QSqlQuery_invalidate(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
delete query;
return QScriptValue::UndefinedValue;
}

/*:144*//*147:*/
#line 3501 "./typica.w"

QScriptValue baseName(QScriptContext*context,QScriptEngine*engine)
{
QFileInfo info(argument<QString> (0,context));
QScriptValue retval(engine,info.baseName());
return retval;
}

QScriptValue dir(QScriptContext*context,QScriptEngine*engine)
{
QFileInfo info(argument<QString> (0,context));
QDir dir= info.dir();
QScriptValue retval(engine,dir.path());
return retval;
}

/*:147*//*148:*/
#line 3520 "./typica.w"

QScriptValue sqlToArray(QScriptContext*context,QScriptEngine*engine)
{
QString source= argument<QString> (0,context);
source.remove(0,1);
source.chop(1);
QStringList elements= source.split(",");
QString element;
QScriptValue dest= engine->newArray(elements.size());
int i= 0;
foreach(element,elements)
{
if(element.startsWith("\"")&&element.endsWith("\""))
{
element.chop(1);
element= element.remove(0,1);
}
dest.setProperty(i,QScriptValue(engine,element));
i++;
}
return dest;
}

/*:148*//*149:*/
#line 3546 "./typica.w"

QScriptValue setFont(QScriptContext*context,QScriptEngine*)
{
QString font= argument<QString> (0,context);
QString classname;
if(context->argumentCount()> 1)
{
classname= argument<QString> (1,context);
QApplication::setFont(QFont(font),classname.toLatin1().constData());
}
else
{
QApplication::setFont(QFont(font));
}
return QScriptValue();
}

/*:149*//*150:*/
#line 3566 "./typica.w"

QScriptValue annotationFromRecord(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection query;
QString q= "SELECT file FROM files WHERE id = :file";
query.prepare(q);
query.bindValue(":file",argument<int> (0,context));
query.exec();
query.next();
QByteArray array= query.value(0).toByteArray();
QBuffer buffer(&array);
buffer.open(QIODevice::ReadOnly);
QXmlQuery xquery;
xquery.bindVariable("profile",&buffer);
QString xq;
xq= "for $b in doc($profile) //tuple where exists($b/annotation) return $b";
xquery.setQuery(xq);
QString result;
xquery.evaluateTo(&result);
return QScriptValue(result);
}

/*:150*//*151:*/
#line 3592 "./typica.w"

QScriptValue setTabOrder(QScriptContext*context,QScriptEngine*)
{
QWidget::setTabOrder(argument<QWidget*> (0,context),
argument<QWidget*> (1,context));
return QScriptValue();
}

/*:151*//*158:*/
#line 3831 "./typica.w"

QScriptValue createWindow(QScriptContext*context,QScriptEngine*engine)
{
QString targetID= argument<QString> (0,context);
QDomNode element;
QScriptValue object;
/*159:*/
#line 3852 "./typica.w"

QDomNodeList windows= 
AppInstance->configuration()->documentElement().elementsByTagName("window");
QDomNode nullNode;
int i= 0;
element= nullNode;
while(i<windows.count())
{
element= windows.at(i);
QDomNamedNodeMap attributes= element.attributes();
if(attributes.contains("id"))
{
if(attributes.namedItem("id").toAttr().value()==targetID)
{
break;
}
}
element= nullNode;
i++;
}

/*:159*/
#line 3837 "./typica.w"

if(!element.isNull())
{
/*160:*/
#line 3884 "./typica.w"

ScriptQMainWindow*window= new ScriptQMainWindow;
window->setObjectName(targetID);
object= engine->newQObject(window);
setQMainWindowProperties(object,engine);
QWidget*central= new(QWidget);
central->setParent(window);
central->setObjectName("centralWidget");
window->setCentralWidget(central);
if(element.hasChildNodes())
{
/*161:*/
#line 3925 "./typica.w"

QStack<QWidget*> widgetStack;
QStack<QLayout*> layoutStack;
QString windowScript;
widgetStack.push(central);
QDomNodeList windowChildren= element.childNodes();
int i= 0;
while(i<windowChildren.count())
{
QDomNode current;
QDomElement element;
current= windowChildren.at(i);
if(current.isElement())
{
element= current.toElement();
if(element.tagName()=="program")
{
windowScript.append(element.text());
}
else if(element.tagName()=="layout")
{
addLayoutToWidget(element,&widgetStack,&layoutStack);
}
else if(element.tagName()=="menu")
{
/*162:*/
#line 3972 "./typica.w"

QMenuBar*bar= window->menuBar();
bar->setParent(window);
bar->setObjectName("menuBar");
if(element.hasAttribute("name"))
{
QMenu*menu= bar->addMenu(element.attribute("name"));
menu->setParent(bar);
if(element.hasAttribute("type"))
{
if(element.attribute("type")=="reports")
{
if(element.hasAttribute("src"))
{
/*535:*/
#line 12733 "./typica.w"

QSettings settings;
QDir directory(QString("%1/%2").arg(settings.value("config").toString()).
arg(element.attribute("src")));
directory.setFilter(QDir::Files);
directory.setSorting(QDir::Name);
QStringList nameFilter;
nameFilter<<"*.xml";
directory.setNameFilters(nameFilter);
QFileInfoList reportFiles= directory.entryInfoList();
for(int i= 0;i<reportFiles.size();i++)
{
QFileInfo reportFile= reportFiles.at(i);
/*539:*/
#line 12810 "./typica.w"

QString path= reportFile.absoluteFilePath();
QFile file(path);
if(file.open(QIODevice::ReadOnly))
{
QDomDocument document;
document.setContent(&file,true);
QDomElement root= document.documentElement();
QDomNode titleNode= root.elementsByTagName("reporttitle").at(0);
if(!titleNode.isNull())
{
QDomElement titleElement= titleNode.toElement();
QString title= titleElement.text();
if(!title.isEmpty())
{
QStringList hierarchy= title.split(":->");
QMenu*insertionPoint= menu;
/*540:*/
#line 12837 "./typica.w"

for(int j= 0;j<hierarchy.size()-1;j++)
{
QObjectList menuList= insertionPoint->children();
bool menuFound= false;
for(int k= 0;k<menuList.size();k++)
{
QMenu*currentItem= qobject_cast<QMenu*> (menuList.at(k));
if(currentItem)
{
if(currentItem->title()==hierarchy.at(j))
{
menuFound= true;
insertionPoint= currentItem;
break;
}
}
}
if(!menuFound)
{
insertionPoint= insertionPoint->addMenu(hierarchy.at(j));
}
}

/*:540*/
#line 12827 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:539*/
#line 12746 "./typica.w"

}

/*:535*/
#line 3986 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*163:*/
#line 3999 "./typica.w"

QDomNodeList menuItems= element.childNodes();
int j= 0;
while(j<menuItems.count())
{
QDomNode item= menuItems.at(j);
if(item.isElement())
{
QDomElement itemElement= item.toElement();
if(itemElement.tagName()=="item")
{
QAction*itemAction= new QAction(itemElement.text(),menu);
if(itemElement.hasAttribute("id"))
{
itemAction->setObjectName(itemElement.attribute("id"));
}
if(itemElement.hasAttribute("shortcut"))
{
itemAction->setShortcut(itemElement.attribute("shortcut"));
}
menu->addAction(itemAction);
}
else if(itemElement.tagName()=="separator")
{
menu->addSeparator();
}
}
j++;
}

/*:163*/
#line 3992 "./typica.w"

}
}

/*:162*/
#line 3950 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*155:*/
#line 3733 "./typica.w"

if(engine->hasUncaughtException())
{
int line= engine->uncaughtExceptionLineNumber();
qDebug()<<"Uncaught excpetion at line "<<line<<" : "<<
result.toString();
QString trace;
foreach(trace,engine->uncaughtExceptionBacktrace())
{
qDebug()<<trace;
}
}

/*:155*/
#line 3958 "./typica.w"

context->setThisObject(oldThis);

/*:161*/
#line 3895 "./typica.w"

}
if(window)
{
window->show();
}
else
{
qDebug()<<"Error! Window invalidated";
}

/*:160*/
#line 3840 "./typica.w"

}
return object;
}

/*:158*//*164:*/
#line 4039 "./typica.w"

void addLayoutToWidget(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
if(element.hasAttribute("type"))
{
/*165:*/
#line 4060 "./typica.w"

QLayout*layout;
QString layoutType= element.attribute("type");
if(layoutType=="horizontal")
{
layout= new QHBoxLayout;
layoutStack->push(layout);
populateBoxLayout(element,widgetStack,layoutStack);
}
else if(layoutType=="vertical")
{
layout= new QVBoxLayout;
layoutStack->push(layout);
populateBoxLayout(element,widgetStack,layoutStack);
}
else if(layoutType=="grid")
{
layout= new QGridLayout;
layoutStack->push(layout);
populateGridLayout(element,widgetStack,layoutStack);
}
else if(layoutType=="stack")
{
layout= new QStackedLayout;
layoutStack->push(layout);
populateStackedLayout(element,widgetStack,layoutStack);
}
if(element.hasAttribute("id"))
{
layout->setObjectName(element.attribute("id"));
}

/*:165*/
#line 4045 "./typica.w"

QWidget*widget= widgetStack->top();
if(layout)
{
widget->setLayout(layout);
}
layoutStack->pop();
}
}

/*:164*//*166:*/
#line 4098 "./typica.w"

void populateStackedLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QDomNodeList children= element.childNodes();
QStackedLayout*layout= qobject_cast<QStackedLayout*> (layoutStack->top());
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="page")
{
QWidget*widget= new QWidget;
layout->addWidget(widget);
widgetStack->push(widget);
populateWidget(currentElement,widgetStack,layoutStack);
widgetStack->pop();
}
}
}
}

/*:166*//*167:*/
#line 4130 "./typica.w"

void populateGridLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QDomNodeList children= element.childNodes();
int row= -1;
QGridLayout*layout= qobject_cast<QGridLayout*> (layoutStack->top());
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="row")
{
row++;
if(currentElement.hasAttribute("height"))
{
layout->setRowMinimumHeight(row,
currentElement.attribute("height").toInt());
}
if(currentElement.hasAttribute("stretch"))
{
layout->setRowStretch(row,
currentElement.attribute("stretch").toInt());
}
/*168:*/
#line 4186 "./typica.w"

int column= -1;
QDomNodeList rowChildren= currentElement.childNodes();
for(int j= 0;j<rowChildren.count();j++)
{
QDomNode columnNode;
QDomElement columnElement;
columnNode= rowChildren.at(j);
if(columnNode.isElement())
{
columnElement= columnNode.toElement();
if(columnElement.tagName()=="column")
{
column++;
if(columnElement.hasAttribute("column"))
{
column= columnElement.attribute("column").toInt();
}
if(columnElement.hasAttribute("width"))
{
layout->setColumnMinimumWidth(column,
columnElement.attribute("width").toInt());
}
if(columnElement.hasAttribute("stretch"))
{
layout->setColumnStretch(column,
columnElement.attribute("stretch").toInt());
}
int hspan= 1;
int vspan= 1;
if(columnElement.hasAttribute("rowspan"))
{
vspan= columnElement.attribute("rowspan").toInt();
}
if(columnElement.hasAttribute("colspan"))
{
hspan= columnElement.attribute("colspan").toInt();
}
QHBoxLayout*cell= new QHBoxLayout;
layout->addLayout(cell,row,column,vspan,hspan);
layoutStack->push(cell);
populateBoxLayout(columnElement,widgetStack,layoutStack);
layoutStack->pop();
}
}
}

/*:168*/
#line 4158 "./typica.w"

}
}
}
}

/*:167*//*169:*/
#line 4236 "./typica.w"

void populateBoxLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="button")
{
addButtonToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="calendar")
{
addCalendarToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="decoration")
{
addDecorationToLayout(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="layout")
{
addLayoutToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="splitter")
{
addSplitterToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="label")
{
QBoxLayout*layout= 
qobject_cast<QBoxLayout*> (layoutStack->top());
QLabel*label= new QLabel(currentElement.text());
layout->addWidget(label);
}
else if(currentElement.tagName()=="lcdtemperature")
{
addTemperatureDisplayToLayout(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="lcdtimer")
{
addTimerDisplayToLayout(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="line")
{
addLineToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="report")
{
addReportToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="sqldrop")
{
addSqlDropToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="sqltablearray")
{
addSaltToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="sqlview")
{
addSqlQueryViewToLayout(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="textarea")
{
addTextToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="spinbox")
{
addSpinBoxToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="formarray")
{
addFormArrayToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="hscale")
{
addScaleControlToLayout(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="vscale")
{
addIntensityControlToLayout(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="webview")
{
addWebViewToLayout(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="stretch")
{
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addStretch();
}
}
}
}

/*:169*//*170:*/
#line 4346 "./typica.w"

void addLayoutToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QLayout*targetLayout= layoutStack->pop();
QBoxLayout*boxLayout= qobject_cast<QBoxLayout*> (targetLayout);
if(element.hasAttribute("type"))
{
/*165:*/
#line 4060 "./typica.w"

QLayout*layout;
QString layoutType= element.attribute("type");
if(layoutType=="horizontal")
{
layout= new QHBoxLayout;
layoutStack->push(layout);
populateBoxLayout(element,widgetStack,layoutStack);
}
else if(layoutType=="vertical")
{
layout= new QVBoxLayout;
layoutStack->push(layout);
populateBoxLayout(element,widgetStack,layoutStack);
}
else if(layoutType=="grid")
{
layout= new QGridLayout;
layoutStack->push(layout);
populateGridLayout(element,widgetStack,layoutStack);
}
else if(layoutType=="stack")
{
layout= new QStackedLayout;
layoutStack->push(layout);
populateStackedLayout(element,widgetStack,layoutStack);
}
if(element.hasAttribute("id"))
{
layout->setObjectName(element.attribute("id"));
}

/*:165*/
#line 4354 "./typica.w"

boxLayout->addLayout(layout);
layoutStack->pop();
}
layoutStack->push(targetLayout);
}

/*:170*//*171:*/
#line 4365 "./typica.w"

void addSplitterToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
QSplitter*splitter= new(QSplitter);
layout->addWidget(splitter);
/*172:*/
#line 4378 "./typica.w"

QString orientation= element.attribute("type");
if(orientation=="horizontal")
{
splitter->setOrientation(Qt::Horizontal);
}
else if(orientation=="vertical")
{
splitter->setOrientation(Qt::Vertical);
}
QString id= element.attribute("id");
if(!id.isEmpty())
{
splitter->setObjectName(id);
}
if(element.hasChildNodes())
{
widgetStack->push(splitter);
populateSplitter(element,widgetStack,layoutStack);
widgetStack->pop();
}

/*:172*/
#line 4372 "./typica.w"

}

/*:171*//*173:*/
#line 4404 "./typica.w"

void populateSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="decoration")
{
addDecorationToSplitter(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="graph")
{
addGraphToSplitter(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="splitter")
{
addSplitterToSplitter(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="lcdtemperature")
{
addTemperatureDisplayToSplitter(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="lcdtimer")
{
addTimerDisplayToSplitter(currentElement,widgetStack,
layoutStack);
}
else if(currentElement.tagName()=="measurementtable")
{
addZoomLogToSplitter(currentElement,widgetStack,layoutStack);
}
else if(currentElement.tagName()=="widget")
{
addWidgetToSplitter(currentElement,widgetStack,layoutStack);
}
}
}
}

/*:173*//*174:*/
#line 4454 "./typica.w"

void addSplitterToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QSplitter*parent= qobject_cast<QSplitter*> (widgetStack->top());
QSplitter*splitter= new(QSplitter);
splitter->setParent(parent);
parent->addWidget(splitter);
/*172:*/
#line 4378 "./typica.w"

QString orientation= element.attribute("type");
if(orientation=="horizontal")
{
splitter->setOrientation(Qt::Horizontal);
}
else if(orientation=="vertical")
{
splitter->setOrientation(Qt::Vertical);
}
QString id= element.attribute("id");
if(!id.isEmpty())
{
splitter->setObjectName(id);
}
if(element.hasChildNodes())
{
widgetStack->push(splitter);
populateSplitter(element,widgetStack,layoutStack);
widgetStack->pop();
}

/*:172*/
#line 4462 "./typica.w"

}

/*:174*//*175:*/
#line 4471 "./typica.w"

void addTemperatureDisplayToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
TemperatureDisplay*display= new(TemperatureDisplay);
if(element.hasAttribute("id"))
{
display->setObjectName(element.attribute("id"));
}
QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
splitter->addWidget(display);
}

void addTemperatureDisplayToLayout(QDomElement element,
QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
TemperatureDisplay*display= new(TemperatureDisplay);
if(element.hasAttribute("id"))
{
display->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(display);
}

/*:175*//*176:*/
#line 4502 "./typica.w"

void addTimerDisplayToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
TimerDisplay*display= new(TimerDisplay);
if(element.hasAttribute("id"))
{
display->setObjectName(element.attribute("id"));
}
if(element.hasAttribute("format"))
{
display->setDisplayFormat(element.attribute("format"));
}
QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
splitter->addWidget(display);
}

void addTimerDisplayToLayout(QDomElement element,
QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
TimerDisplay*display= new(TimerDisplay);
if(element.hasAttribute("id"))
{
display->setObjectName(element.attribute("id"));
}
if(element.hasAttribute("format"))
{
display->setDisplayFormat(element.attribute("format"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(display);
}

/*:176*//*177:*/
#line 4540 "./typica.w"

void addDecorationToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
/*178:*/
#line 4561 "./typica.w"

QString labelText= element.attribute("name");
Qt::Orientations orientation= Qt::Horizontal;
if(element.hasAttribute("type"))
{
if(element.attribute("type")=="horizontal")
{
orientation= Qt::Horizontal;
}
else if(element.attribute("type")=="vertical")
{
orientation= Qt::Vertical;
}
}
/*179:*/
#line 4586 "./typica.w"

QWidget*theWidget= NULL;
QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode item= children.at(i);
if(item.isElement())
{
QDomElement itemElement= item.toElement();
if(itemElement.tagName()=="lcdtemperature")
{
TemperatureDisplay*display= new TemperatureDisplay;
if(itemElement.hasAttribute("id"))
{
display->setObjectName(itemElement.attribute("id"));
}
theWidget= display;
}
else if(itemElement.tagName()=="lcdtimer")
{
TimerDisplay*display= new TimerDisplay;
if(itemElement.hasAttribute("id"))
{
display->setObjectName(itemElement.attribute("id"));
}
if(itemElement.hasAttribute("format"))
{
display->setDisplayFormat(itemElement.attribute("format"));
}
theWidget= display;
}
}
}

/*:179*/
#line 4575 "./typica.w"

WidgetDecorator*decoration= new WidgetDecorator(theWidget,labelText,
orientation);
if(element.hasAttribute("id"))
{
decoration->setObjectName(element.attribute("id"));
}

/*:178*/
#line 4544 "./typica.w"

QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(decoration);
}

void addDecorationToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
/*178:*/
#line 4561 "./typica.w"

QString labelText= element.attribute("name");
Qt::Orientations orientation= Qt::Horizontal;
if(element.hasAttribute("type"))
{
if(element.attribute("type")=="horizontal")
{
orientation= Qt::Horizontal;
}
else if(element.attribute("type")=="vertical")
{
orientation= Qt::Vertical;
}
}
/*179:*/
#line 4586 "./typica.w"

QWidget*theWidget= NULL;
QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode item= children.at(i);
if(item.isElement())
{
QDomElement itemElement= item.toElement();
if(itemElement.tagName()=="lcdtemperature")
{
TemperatureDisplay*display= new TemperatureDisplay;
if(itemElement.hasAttribute("id"))
{
display->setObjectName(itemElement.attribute("id"));
}
theWidget= display;
}
else if(itemElement.tagName()=="lcdtimer")
{
TimerDisplay*display= new TimerDisplay;
if(itemElement.hasAttribute("id"))
{
display->setObjectName(itemElement.attribute("id"));
}
if(itemElement.hasAttribute("format"))
{
display->setDisplayFormat(itemElement.attribute("format"));
}
theWidget= display;
}
}
}

/*:179*/
#line 4575 "./typica.w"

WidgetDecorator*decoration= new WidgetDecorator(theWidget,labelText,
orientation);
if(element.hasAttribute("id"))
{
decoration->setObjectName(element.attribute("id"));
}

/*:178*/
#line 4553 "./typica.w"

QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
splitter->addWidget(decoration);
}

/*:177*//*180:*/
#line 4625 "./typica.w"

void addWidgetToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
QWidget*widget= new QWidget;
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
splitter->addWidget(widget);
if(element.hasChildNodes())
{
widgetStack->push(widget);
populateWidget(element,widgetStack,layoutStack);
widgetStack->pop();
}
}

void populateWidget(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="layout")
{
addLayoutToWidget(currentElement,widgetStack,layoutStack);
}
}
}
}

/*:180*//*181:*/
#line 4668 "./typica.w"

void addButtonToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QAbstractButton*button= NULL;
QString text= element.attribute("name");
if(element.hasAttribute("type"))
{
QString type= element.attribute("type");
if(type=="annotation")
{
AnnotationButton*abutton= new AnnotationButton(text);
if(element.hasAttribute("annotation"))
{
abutton->setAnnotation(element.attribute("annotation"));
}
if(element.hasAttribute("series"))
{
abutton->setTemperatureColumn(element.attribute("series").
toInt());
}
if(element.hasAttribute("column"))
{
abutton->setAnnotationColumn(element.attribute("column").
toInt());
}
button= abutton;
}
else if(type=="check")
{
button= new QCheckBox(text);
}
else if(type=="push")
{
button= new QPushButton(text);
}
}
if(element.hasAttribute("id"))
{
button->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(button);
}

/*:181*//*182:*/
#line 4720 "./typica.w"

void addSpinBoxToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
AnnotationSpinBox*box= new AnnotationSpinBox("","",NULL);
if(element.hasAttribute("pretext"))
{
box->setPretext(element.attribute("pretext"));
}
if(element.hasAttribute("posttext"))
{
box->setPosttext(element.attribute("posttext"));
}
if(element.hasAttribute("series"))
{
box->setTemperatureColumn(element.attribute("series").toInt());
}
if(element.hasAttribute("column"))
{
box->setAnnotationColumn(element.attribute("column").toInt());
}
if(element.hasAttribute("min"))
{
box->setMinimum(element.attribute("min").toDouble());
}
if(element.hasAttribute("max"))
{
box->setMaximum(element.attribute("max").toDouble());
}
if(element.hasAttribute("decimals"))
{
box->setDecimals(element.attribute("decimals").toInt());
}
if(element.hasAttribute("step"))
{
box->setSingleStep(element.attribute("step").toDouble());
}
if(element.hasAttribute("id"))
{
box->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(box);
}

/*:182*//*183:*/
#line 4776 "./typica.w"

void addZoomLogToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
ZoomLog*widget= new ZoomLog;
if(!widget)
{
qDebug()<<"Error constructing widget!";
}
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
if(element.hasChildNodes())
{
QDomNodeList children= element.childNodes();
int column= 0;
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="column")
{
QString text= currentElement.text();
widget->setHeaderData(column,text);
column++;
}
}
}
}
QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
if(splitter)
{
splitter->addWidget(widget);
}
else
{
qDebug()<<"Splitter not found at top of widget stack!";
}
}

/*:183*//*184:*/
#line 4824 "./typica.w"

void addGraphToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
GraphView*view= new GraphView;
if(element.hasAttribute("id"))
{
view->setObjectName(element.attribute("id"));
}
QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
splitter->addWidget(view);
}

/*:184*//*185:*/
#line 4841 "./typica.w"

void addSqlDropToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
SqlComboBox*box= new SqlComboBox();
if(element.hasAttribute("data"))
{
box->setDataColumn(element.attribute("data").toInt());
}
if(element.hasAttribute("display"))
{
box->setDisplayColumn(element.attribute("display").toInt());
}
if(element.hasAttribute("showdata"))
{
if(element.attribute("showdata")=="true")
{
box->showData(true);
}
}
if(element.hasAttribute("editable"))
{
if(element.attribute("editable")=="true")
{
box->setEditable(true);
}
}
if(element.hasChildNodes())
{
QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="null")
{
box->addNullOption();
}
else if(currentElement.tagName()=="query")
{
box->addSqlOptions(currentElement.text());
}
}
}
}
if(element.hasAttribute("id"))
{
box->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(box);
}

/*:185*//*186:*/
#line 4920 "./typica.w"

void addSaltToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QTableView*view= new QTableView;
view->setProperty("tabletype",QVariant(QString("SaltTable")));
SaltModel*model= new SaltModel(element.childNodes().count());
if(element.hasAttribute("id"))
{
view->setObjectName(element.attribute("id"));
}
if(element.hasChildNodes())
{
QDomNodeList children= element.childNodes();
int currentColumn= 0;
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
if(currentElement.tagName()=="column")
{
if(currentElement.hasAttribute("name"))
{
model->setHeaderData(currentColumn,Qt::Horizontal,
currentElement.attribute("name"));
}
if(currentElement.hasAttribute("delegate"))
{
/*187:*/
#line 4968 "./typica.w"

if(currentElement.attribute("delegate")=="sql")
{
/*188:*/
#line 4984 "./typica.w"

SqlComboBoxDelegate*delegate= new SqlComboBoxDelegate;
SqlComboBox*widget= new SqlComboBox();
if(currentElement.hasAttribute("null"))
{
if(currentElement.attribute("null")=="true")
{
widget->addNullOption();
}
}
if(currentElement.hasAttribute("showdata"))
{
if(currentElement.attribute("showdata")=="true")
{
widget->showData(true);
}
}
if(currentElement.hasAttribute("data"))
{
widget->setDataColumn(currentElement.attribute("data").toInt());
}
if(currentElement.hasAttribute("display"))
{
widget->setDisplayColumn(currentElement.attribute("display").toInt());
}
widget->addSqlOptions(currentElement.text());
delegate->setWidget(widget);
view->setItemDelegateForColumn(currentColumn,delegate);

/*:188*/
#line 4971 "./typica.w"

}
else if(currentElement.attribute("delegate")=="numeric")
{
/*189:*/
#line 5017 "./typica.w"

NumericDelegate*delegate= new NumericDelegate;
view->setItemDelegateForColumn(currentColumn,delegate);

/*:189*/
#line 4975 "./typica.w"

}

/*:187*/
#line 4952 "./typica.w"

}
currentColumn++;
}
}
}
}
view->setModel(model);
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(view);
}

/*:186*//*196:*/
#line 5127 "./typica.w"

void addLineToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QLineEdit*widget= new QLineEdit(element.text());
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
if(element.hasAttribute("writable"))
{
if(element.attribute("writable")=="false")
{
widget->setReadOnly(true);
}
}
if(element.hasAttribute("validator"))
{
if(element.attribute("validator")=="numeric")
{
widget->setValidator(new QDoubleValidator(NULL));
}
else if(element.attribute("validator")=="integer")
{
widget->setValidator(new QIntValidator(NULL));
}
else if(element.attribute("validator")=="expression"&&
element.hasAttribute("expression"))
{
widget->setValidator(new QRegExpValidator(
QRegExp(element.attribute("expression")),
NULL));
}
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
}

/*:196*//*197:*/
#line 5168 "./typica.w"

void addTextToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QTextEdit*widget= new QTextEdit;
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
}

/*:197*//*198:*/
#line 5185 "./typica.w"

void addSqlQueryViewToLayout(QDomElement element,
QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
SqlQueryView*view= new SqlQueryView;
if(element.hasAttribute("id"))
{
view->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(view);
}

/*:198*//*199:*/
#line 5202 "./typica.w"

void addCalendarToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QDateEdit*widget= new QDateEdit;
widget->setCalendarPopup(true);
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
widget->setDate(QDate::currentDate());
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
}

/*:199*//*200:*/
#line 5220 "./typica.w"

void setQDateEditProperties(QScriptValue value,QScriptEngine*engine)
{
setQDateTimeEditProperties(value,engine);
}

void setQDateTimeEditProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractSpinBoxProperties(value,engine);
value.setProperty("setDate",engine->newFunction(QDateTimeEdit_setDate));
value.setProperty("day",engine->newFunction(QDateTimeEdit_day));
value.setProperty("month",engine->newFunction(QDateTimeEdit_month));
value.setProperty("year",engine->newFunction(QDateTimeEdit_year));
}

/*:200*//*201:*/
#line 5240 "./typica.w"

QScriptValue QDateTimeEdit_setDate(QScriptContext*context,QScriptEngine*)
{
QDateTimeEdit*self= getself<QDateTimeEdit*> (context);
if(context->argumentCount()==3)
{
self->setDate(QDate(argument<int> (0,context),
argument<int> (1,context),
argument<int> (2,context)));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QDateTimeEdit::setDate(). This method takes three integer arguments "
"specifying the year, month, and day.");
}
return QScriptValue();
}

QScriptValue QDateTimeEdit_day(QScriptContext*context,QScriptEngine*)
{
QDateTimeEdit*self= getself<QDateTimeEdit*> (context);
return QScriptValue(self->date().day());
}

QScriptValue QDateTimeEdit_month(QScriptContext*context,QScriptEngine*)
{
QDateTimeEdit*self= getself<QDateTimeEdit*> (context);
return QScriptValue(self->date().month());
}

QScriptValue QDateTimeEdit_year(QScriptContext*context,QScriptEngine*)
{
QDateTimeEdit*self= getself<QDateTimeEdit*> (context);
return QScriptValue(self->date().year());
}

/*:201*//*205:*/
#line 5307 "./typica.w"

QScriptValue findChildObject(QScriptContext*context,QScriptEngine*engine)
{
QObject*parent= argument<QObject*> (0,context);
QString name= argument<QString> (1,context);
QObject*object= parent->findChild<QObject*> (name);
QScriptValue value;
if(object)
{
value= engine->newQObject(object);
QString className= object->metaObject()->className();
/*206:*/
#line 5325 "./typica.w"

if(className=="TemperatureDisplay")
{
setTemperatureDisplayProperties(value,engine);
}
else if(className=="TimerDisplay")
{
setTimerDisplayProperties(value,engine);
}
else if(className=="QAction")
{
setQActionProperties(value,engine);
}
else if(className=="QBoxLayout")
{
setQBoxLayoutProperties(value,engine);
}
else if(className=="QDateEdit")
{
setQDateEditProperties(value,engine);
}
else if(className=="QFrame")
{
setQFrameProperties(value,engine);
}
else if(className=="QHBoxLayout")
{
setQBoxLayoutProperties(value,engine);
}
else if(className=="QLCDNumber")
{
setQLCDNumberProperties(value,engine);
}
else if(className=="QMenu")
{
setQMenuProperties(value,engine);
}
else if(className=="QMenuBar")
{
setQMenuBarProperties(value,engine);
}
else if(className=="QPushButton")
{
setQPushButtonProperties(value,engine);
}
else if(className=="QSplitter")
{
setQSplitterProperties(value,engine);
}
else if(className=="QTableView")
{
if(object->property("tabletype").isValid())
{
if(object->property("tabletype").toString()=="SaltTable")
{
setSaltTableProperties(value,engine);
}
}
}
else if(className=="QVBoxLayout")
{
setQBoxLayoutProperties(value,engine);
}
else if(className=="QWidget")
{
setQWidgetProperties(value,engine);
}
else if(className=="ScriptQMainWindow")
{
setQMainWindowProperties(value,engine);
}
else if(className=="SqlComboBox")
{
setSqlComboBoxProperties(value,engine);
}
else if(className=="SqlQueryView")
{
setSqlQueryViewProperties(value,engine);
}
else if(className=="ZoomLog")
{
setZoomLogProperties(value,engine);
}
else if(className=="QTextEdit")
{
setQTextEditProperties(value,engine);
}
else if(className=="QWebView")
{
setQWebViewProperties(value,engine);
}

/*:206*/
#line 5318 "./typica.w"

}
return value;
}

/*:205*//*208:*/
#line 5443 "./typica.w"

QScriptValue SaltTable_columnSum(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
QString datum;
double total= 0.0;
int column= argument<int> (0,context);
int role= argument<int> (1,context);
for(int i= 0;i<model->rowCount();i++)
{
datum= model->data(model->index(i,column),role).toString();
if(!datum.isEmpty())
{
total+= datum.toDouble();
}
}
return QScriptValue(engine,total);
}

/*:208*//*209:*/
#line 5467 "./typica.w"

QScriptValue SaltTable_columnArray(QScriptContext*context,
QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
int column= argument<int> (0,context);
int role= argument<int> (1,context);
QString literal= model->arrayLiteral(column,role);
return QScriptValue(engine,literal);
}

QScriptValue SaltTable_quotedColumnArray(QScriptContext*context,
QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
int column= argument<int> (0,context);
int role= argument<int> (1,context);
QString literal= model->quotedArrayLiteral(column,role);
return QScriptValue(engine,literal);
}

QScriptValue SaltTable_bindableColumnArray(QScriptContext*context,
QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
int column= argument<int> (0,context);
int role= argument<int> (1,context);
QString literal= model->arrayLiteral(column,role);
literal.chop(1);
literal= literal.remove(0,1);
return QScriptValue(engine,literal);
}

QScriptValue SaltTable_bindableQuotedColumnArray(QScriptContext*context,
QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
int column= argument<int> (0,context);
int role= argument<int> (1,context);
QString literal= model->quotedArrayLiteral(column,role);
literal.chop(1);
literal= literal.remove(0,1);
return QScriptValue(engine,literal);
}

/*:209*//*210:*/
#line 5519 "./typica.w"

QScriptValue SaltTable_model(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
QScriptValue value= engine->newQObject(self->model());
return value;
}

/*:210*//*211:*/
#line 5533 "./typica.w"

QScriptValue SaltTable_setData(QScriptContext*context,QScriptEngine*)
{
QTableView*self= getself<QTableView*> (context);
int row= argument<int> (0,context);
int column= argument<int> (1,context);
QVariant value= argument<QVariant> (2,context);
int role= argument<int> (3,context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
QModelIndex cell= model->index(row,column);
model->setData(cell,value,role);
self->update(cell);
return QScriptValue();
}

/*:211*//*212:*/
#line 5551 "./typica.w"

QScriptValue SaltTable_data(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
int row= argument<int> (0,context);
int column= argument<int> (1,context);
int role= argument<int> (2,context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
QModelIndex cell= model->index(row,column);
QVariant value= model->data(cell,role);
QScriptValue retval= engine->newVariant(value);
retval.setProperty("value",QScriptValue(value.toString()));
return retval;
}

/*:212*//*213:*/
#line 5569 "./typica.w"

void setSaltTableProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("columnArray",
engine->newFunction(SaltTable_columnArray));
value.setProperty("quotedColumnArray",
engine->newFunction(SaltTable_quotedColumnArray));
value.setProperty("bindableColumnArray",
engine->newFunction(SaltTable_bindableColumnArray));
value.setProperty("bindableQuotedColumnArray",
engine->newFunction(SaltTable_bindableQuotedColumnArray));
value.setProperty("columnSum",engine->newFunction(SaltTable_columnSum));
value.setProperty("data",engine->newFunction(SaltTable_data));
value.setProperty("model",engine->newFunction(SaltTable_model));
value.setProperty("setData",engine->newFunction(SaltTable_setData));
}

/*:213*//*215:*/
#line 5602 "./typica.w"

void setSqlComboBoxProperties(QScriptValue value,QScriptEngine*engine)
{
setQComboBoxProperties(value,engine);
}

void setQComboBoxProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("currentData",
engine->newFunction(QComboBox_currentData));
value.setProperty("addItem",engine->newFunction(QComboBox_addItem));
value.setProperty("setModel",engine->newFunction(QComboBox_setModel));
value.setProperty("findText",engine->newFunction(QComboBox_findText));
}

QScriptValue QComboBox_currentData(QScriptContext*context,
QScriptEngine*engine)
{
QComboBox*self= getself<QComboBox*> (context);
return QScriptValue(engine,
self->itemData(self->currentIndex()).toString());
}

QScriptValue QComboBox_addItem(QScriptContext*context,QScriptEngine*)
{
QComboBox*self= getself<QComboBox*> (context);
self->addItem(argument<QString> (0,context));
return QScriptValue();
}

QScriptValue QComboBox_setModel(QScriptContext*context,QScriptEngine*)
{
QComboBox*self= getself<QComboBox*> (context);
self->setModel(argument<QAbstractItemModel*> (0,context));
return QScriptValue();
}

QScriptValue QComboBox_findText(QScriptContext*context,QScriptEngine*engine)
{
QComboBox*self= getself<QComboBox*> (context);
return QScriptValue(engine,self->findText(argument<QString> (0,context)));
}

/*:215*//*244:*/
#line 6484 "./typica.w"

QScriptValue constructDAQ(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==1)
{
object= engine->newQObject(new DAQ(argument<QString> (0,context)),
QScriptEngine::ScriptOwnership);
setDAQProperties(object,engine);
}
else if(context->argumentCount()==2)
{
object= engine->newQObject(new DAQ(argument<QString> (0,context),
argument<QString> (1,context)),
QScriptEngine::ScriptOwnership);
setDAQProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to DAQ"
"constructor. The DAQ constructor takes one"
"string as an argument specifying a device name."
"Example: Dev1");
}
return object;
}

/*:244*//*245:*/
#line 6514 "./typica.w"

void setDAQProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("newChannel",engine->newFunction(DAQ_newChannel));
}

/*:245*//*246:*/
#line 6524 "./typica.w"

QScriptValue DAQ_newChannel(QScriptContext*context,QScriptEngine*engine)
{
DAQ*self= getself<DAQ*> (context);
QScriptValue object;
if(self)
{
object= 
engine->newQObject(self->newChannel(argument<int> (0,context),
argument<int> (1,context)));
setChannelProperties(object,engine);
}
return object;
}

/*:246*//*253:*/
#line 6680 "./typica.w"

QScriptValue constructFakeDAQ(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==1)
{
object= 
engine->newQObject(new FakeDAQ(argument<QString> (0,context)),
QScriptEngine::ScriptOwnership);
setFakeDAQProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to DAQ"
"constructor. The DAQ constructor takes one"
"string as an argument specifying a device name."
"Example: Dev1");
}
return object;
}

void setFakeDAQProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("newChannel",engine->newFunction(FakeDAQ_newChannel));
}

QScriptValue FakeDAQ_newChannel(QScriptContext*context,QScriptEngine*engine)
{
FakeDAQ*self= getself<FakeDAQ*> (context);
QScriptValue object;
if(self)
{
object= 
engine->newQObject(self->newChannel(argument<int> (0,context),
argument<int> (1,context)));
setChannelProperties(object,engine);
}
return object;
}

/*:253*//*257:*/
#line 6771 "./typica.w"

void setChannelProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:257*//*264:*/
#line 6957 "./typica.w"

QScriptValue constructLinearCalibrator(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new LinearCalibrator(NULL));
setLinearCalibratorProperties(object,engine);
return object;
}

void setLinearCalibratorProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:264*//*269:*/
#line 7094 "./typica.w"

QScriptValue constructLinearSplineInterpolator(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new LinearSplineInterpolator(NULL));
setLinearSplineInterpolatorProperties(object,engine);
return object;
}

void setLinearSplineInterpolatorProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}


/*:269*//*278:*/
#line 7278 "./typica.w"

QScriptValue constructTemperatureDisplay(QScriptContext*,
QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new TemperatureDisplay);
setTemperatureDisplayProperties(object,engine);
return object;
}

void setTemperatureDisplayProperties(QScriptValue value,QScriptEngine*engine)
{
setQLCDNumberProperties(value,engine);
}

/*:278*//*285:*/
#line 7419 "./typica.w"

QScriptValue constructMeasurementTimeOffset(QScriptContext*,
QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new MeasurementTimeOffset(QTime::currentTime()));
setMeasurementTimeOffsetProperties(object,engine);
return object;
}

void setMeasurementTimeOffsetProperties(QScriptValue value,
QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:285*//*290:*/
#line 7528 "./typica.w"

QScriptValue constructThresholdDetector(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new ThresholdDetector(300));
return object;
}

void setThresholdDetectorProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:290*//*295:*/
#line 7624 "./typica.w"

QScriptValue constructZeroEmitter(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new ZeroEmitter(argument<int> (0,context)));
setZeroEmitterProperties(object,engine);
return object;
}

void setZeroEmitterProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:295*//*300:*/
#line 7704 "./typica.w"

QScriptValue constructMeasurementAdapter(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new MeasurementAdapter(argument<int> (0,context)));
setMeasurementAdapterProperties(object,engine);
return object;
}

void setMeasurementAdapterProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:300*//*315:*/
#line 8052 "./typica.w"

QScriptValue constructGraphView(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new GraphView);
setGraphViewProperties(object,engine);
return object;
}

void setGraphViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQGraphicsViewProperties(value,engine);
}

/*:315*//*337:*/
#line 8624 "./typica.w"

QScriptValue constructZoomLog(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new ZoomLog);
setZoomLogProperties(object,engine);
return object;
}

void setZoomLogProperties(QScriptValue value,QScriptEngine*engine)
{
setQTableViewProperties(value,engine);
value.setProperty("saveXML",engine->newFunction(ZoomLog_saveXML));
value.setProperty("saveCSV",engine->newFunction(ZoomLog_saveCSV));
value.setProperty("saveState",engine->newFunction(ZoomLog_saveState));
value.setProperty("restoreState",
engine->newFunction(ZoomLog_restoreState));
value.setProperty("lastTime",engine->newFunction(ZoomLog_lastTime));
value.setProperty("saveTemporary",
engine->newFunction(ZoomLog_saveTemporary));
}

/*:337*//*338:*/
#line 8650 "./typica.w"

QScriptValue ZoomLog_saveXML(QScriptContext*context,QScriptEngine*engine)
{
ZoomLog*self= getself<ZoomLog*> (context);
bool retval= self->saveXML(argument<QIODevice*> (0,context));
return QScriptValue(engine,retval);
}

QScriptValue ZoomLog_saveCSV(QScriptContext*context,QScriptEngine*engine)
{
ZoomLog*self= getself<ZoomLog*> (context);
bool retval= self->saveCSV(argument<QIODevice*> (0,context));
return QScriptValue(engine,retval);
}

QScriptValue ZoomLog_saveTemporary(QScriptContext*context,
QScriptEngine*engine)
{
ZoomLog*self= getself<ZoomLog*> (context);
QString filename= QDir::tempPath();
filename.append("/");
filename.append(QUuid::createUuid().toString());
filename.append(".xml");
QFile*file= new QFile(filename);
self->saveXML(file);
file->close();
delete file;
return QScriptValue(engine,filename);
}

/*:338*//*339:*/
#line 8698 "./typica.w"

QScriptValue ZoomLog_saveState(QScriptContext*context,QScriptEngine*)
{
ZoomLog*self= getself<ZoomLog*> (context);
QString key= argument<QString> (0,context);
int columns= argument<int> (1,context);
QSettings settings;
for(int i= 0;i<columns;i++)
{
if(self->columnWidth(i))
{
settings.beginGroup(key);
settings.setValue(QString("%1").arg(i),self->columnWidth(i));
settings.endGroup();
}
}
return QScriptValue();
}

QScriptValue ZoomLog_restoreState(QScriptContext*context,QScriptEngine*)
{
ZoomLog*self= getself<ZoomLog*> (context);
QString key= argument<QString> (0,context);
int columns= argument<int> (1,context);
QSettings settings;
for(int i= 0;i<columns;i++)
{
settings.beginGroup(key);
self->setColumnWidth(i,
settings.value(QString("%1").arg(i),80).toInt());
if(settings.value(QString("%1").arg(i),80).toInt()==0)
{
self->setColumnWidth(i,80);
}
settings.endGroup();
}
return QScriptValue();
}

QScriptValue ZoomLog_lastTime(QScriptContext*context,QScriptEngine*engine)
{
ZoomLog*self= getself<ZoomLog*> (context);
return QScriptValue(engine,self->lastTime(argument<int> (0,context)));
}

/*:339*//*374:*/
#line 9542 "./typica.w"

QScriptValue constructAnnotationButton(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new AnnotationButton(argument<QString> (0,context)));
setAnnotationButtonProperties(object,engine);
return object;
}

void setAnnotationButtonProperties(QScriptValue value,QScriptEngine*engine)
{
setQPushButtonProperties(value,engine);
}

/*:374*//*382:*/
#line 9685 "./typica.w"

QScriptValue constructAnnotationSpinBox(QScriptContext*context,
QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new AnnotationSpinBox(
argument<QString> (0,context),argument<QString> (1,context)));
setAnnotationSpinBoxProperties(object,engine);
return object;
}

void setAnnotationSpinBoxProperties(QScriptValue value,QScriptEngine*engine)
{
setQDoubleSpinBoxProperties(value,engine);
}

void setQDoubleSpinBoxProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractSpinBoxProperties(value,engine);
}

void setQAbstractSpinBoxProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:382*//*403:*/
#line 10104 "./typica.w"

QScriptValue constructTimerDisplay(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new TimerDisplay);
setTimerDisplayProperties(object,engine);
return object;
}

void setTimerDisplayProperties(QScriptValue value,QScriptEngine*engine)
{
setQLCDNumberProperties(value,engine);
}


/*:403*//*430:*/
#line 10599 "./typica.w"

QScriptValue constructWidgetDecorator(QScriptContext*context,
QScriptEngine*engine)
{
QWidget*widget= argument<QWidget*> (0,context);
QString text= argument<QString> (1,context);
Qt::Orientations orientation;
switch(argument<int> (2,context))
{
case 2:
orientation= Qt::Vertical;
break;
default:
orientation= Qt::Horizontal;
break;
}
QScriptValue object= 
engine->newQObject(new WidgetDecorator(widget,text,orientation));
setWidgetDecoratorProperties(object,engine);
return object;
}

void setWidgetDecoratorProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:430*//*443:*/
#line 10880 "./typica.w"

QScriptValue constructLogEditWindow(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new LogEditWindow);
return object;
}

/*:443*//*462:*/
#line 11354 "./typica.w"

QScriptValue constructXMLInput(QScriptContext*context,QScriptEngine*engine)
{
QIODevice*device= argument<QIODevice*> (0,context);
QScriptValue object= engine->newQObject(new XMLInput(&*device,
argument<int> (1,context)));
object.setProperty("input",engine->newFunction(XMLInput_input));
return object;
}

QScriptValue XMLInput_input(QScriptContext*context,QScriptEngine*)
{
XMLInput*self= getself<XMLInput*> (context);
self->input();
return QScriptValue();
}

/*:462*//*469:*/
#line 11522 "./typica.w"

QScriptValue constructWebView(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QWebView());
setQWebViewProperties(object,engine);
return object;
}

void setQWebViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("load",engine->newFunction(WebView_load));
value.setProperty("print",engine->newFunction(WebView_print));
value.setProperty("setHtml",engine->newFunction(WebView_setHtml));
value.setProperty("setContent",engine->newFunction(WebView_setContent));
value.setProperty("saveXml",engine->newFunction(WebView_saveXml));
}

/*:469*//*470:*/
#line 11543 "./typica.w"

QScriptValue WebView_load(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QString file= argument<QString> (0,context);
self->load(QUrl(file));
return QScriptValue();
}

/*:470*//*471:*/
#line 11556 "./typica.w"

QScriptValue WebView_print(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QPrinter*printer= new QPrinter(QPrinter::HighResolution);
QPrintDialog printDialog(printer,NULL);
if(printDialog.exec()==QDialog::Accepted)
{
self->print(printer);
}
return QScriptValue();
}

/*:471*//*472:*/
#line 11572 "./typica.w"

QScriptValue WebView_setHtml(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QString content= argument<QString> (0,context);
self->setHtml(content);
return QScriptValue();
}

/*:472*//*473:*/
#line 11585 "./typica.w"

QScriptValue WebView_setContent(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QIODevice*device= argument<QIODevice*> (0,context);
device->reset();
QByteArray content= device->readAll();
self->setContent(content,"application/xhtml+xml");
return QScriptValue();
}

/*:473*//*474:*/
#line 11599 "./typica.w"

QScriptValue WebView_saveXml(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
return QScriptValue(self->page()->currentFrame()->documentElement().toOuterXml());
}

/*:474*//*475:*/
#line 11609 "./typica.w"

void addWebViewToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QWebView*view= new QWebView;
if(element.hasAttribute("id"))
{
view->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(view);
}

/*:475*//*533:*/
#line 12659 "./typica.w"

QScriptValue constructSqlQueryView(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new SqlQueryView);
setSqlQueryViewProperties(object,engine);
return object;
}

void setSqlQueryViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQTableViewProperties(value,engine);
value.setProperty("setHeaderData",
engine->newFunction(SqlQueryView_setHeaderData));
value.setProperty("setQuery",engine->newFunction(SqlQueryView_setQuery));
}

/*:533*//*534:*/
#line 12677 "./typica.w"

QScriptValue SqlQueryView_setQuery(QScriptContext*context,QScriptEngine*)
{
SqlQueryView*self= getself<SqlQueryView*> (context);
QString query= argument<QString> (0,context);
self->setQuery(query);
self->reset();
return QScriptValue();
}

QScriptValue SqlQueryView_setHeaderData(QScriptContext*context,
QScriptEngine*)
{
SqlQueryView*self= getself<SqlQueryView*> (context);
int section= argument<int> (0,context);
QString data= argument<QString> (1,context);
self->setHeaderData(section,Qt::Horizontal,data,Qt::DisplayRole);
return QScriptValue();
}

/*:534*//*542:*/
#line 12876 "./typica.w"

void addReportToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QTextEdit*widget= new QTextEdit;
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
QTextDocument*document= new QTextDocument;
QFont defaultFont;
defaultFont.setPointSize(11);
document->setDefaultFont(defaultFont);
QTextCursor cursor(document);
/*543:*/
#line 12899 "./typica.w"

QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
/*544:*/
#line 12916 "./typica.w"

if(currentElement.tagName()=="style")
{
document->setDefaultStyleSheet(currentElement.text());
}

/*:544*//*545:*/
#line 12927 "./typica.w"

if(currentElement.tagName()=="html")
{
cursor.insertHtml(currentElement.text());
}

/*:545*//*546:*/
#line 12937 "./typica.w"

if(currentElement.tagName()=="text")
{
cursor.insertText(currentElement.text());
}

/*:546*//*547:*/
#line 12947 "./typica.w"

if(currentElement.tagName()=="table")
{
QTextFrame*frame= cursor.insertFrame(QTextFrameFormat());
ReportTable*table= new ReportTable(frame,currentElement);
table->setParent(widget);
if(currentElement.hasAttribute("id"))
{
table->setObjectName(currentElement.attribute("id"));
}
}

/*:547*/
#line 12909 "./typica.w"

}
}

/*:543*/
#line 12892 "./typica.w"

widget->setDocument(document);
}

/*:542*//*558:*/
#line 13159 "./typica.w"

QScriptValue QTextEdit_print(QScriptContext*context,QScriptEngine*)
{
QTextEdit*self= getself<QTextEdit*> (context);
QTextDocument*document= self->document();
QPrinter printer;

QPrintDialog printwindow(&printer,self);
if(printwindow.exec()!=QDialog::Accepted)
{
return QScriptValue();
}
document->print(&printer);
return QScriptValue();
}

/*:558*//*559:*/
#line 13177 "./typica.w"

void setQTextEditProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
value.setProperty("print",engine->newFunction(QTextEdit_print));
}

/*:559*//*568:*/
#line 13355 "./typica.w"

void addFormArrayToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
FormArray*widget= new FormArray(element);
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
}

/*:568*//*589:*/
#line 13942 "./typica.w"

void addScaleControlToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
ScaleControl*scale= new ScaleControl;
if(element.hasAttribute("id"))
{
scale->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(scale);
}

void addIntensityControlToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
IntensityControl*scale= new IntensityControl;
if(element.hasAttribute("id"))
{
scale->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(scale);
}



/*:589*//*615:*/
#line 14532 "./typica.w"

QScriptValue constructDeviceTreeModel(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new DeviceTreeModel);
setDeviceTreeModelProperties(object,engine);
return object;
}

/*:615*//*617:*/
#line 14555 "./typica.w"

void setDeviceTreeModelProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractItemModelProperties(value,engine);
value.setProperty("referenceElement",
engine->newFunction(DeviceTreeModel_referenceElement));
}

void setQAbstractItemModelProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("data",engine->newFunction(QAbstractItemModel_data));
value.setProperty("index",engine->newFunction(QAbstractItemModel_index));
value.setProperty("rowCount",engine->newFunction(QAbstractItemModel_rowCount));
value.setProperty("hasChildren",engine->newFunction(QAbstractItemModel_hasChildren));
}

/*:617*//*618:*/
#line 14582 "./typica.w"

QScriptValue DeviceTreeModel_referenceElement(QScriptContext*context,
QScriptEngine*engine)
{
DeviceTreeModel*model= getself<DeviceTreeModel*> (context);
QDomElement referenceElement= model->referenceElement(argument<QString> (0,context));
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;
QVariantMap retval;
retval.insert("driver",referenceElement.attribute("driver"));
for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
retval.insert(node.attribute("name"),node.attribute("value"));
}
return engine->toScriptValue(retval);
}

QScriptValue QAbstractItemModel_data(QScriptContext*context,QScriptEngine*engine)
{
QAbstractItemModel*model= getself<QAbstractItemModel*> (context);
QModelIndex index= argument<QModelIndex> (0,context);
int role= argument<int> (1,context);
return engine->toScriptValue(model->data(index,role));
}

QScriptValue QAbstractItemModel_index(QScriptContext*context,QScriptEngine*engine)
{
QAbstractItemModel*model= getself<QAbstractItemModel*> (context);
int row= 0;
int column= 0;
QModelIndex index;
if(context->argumentCount()> 1)
{
row= argument<int> (0,context);
column= argument<int> (1,context);
}
if(context->argumentCount()> 2)
{
index= argument<QModelIndex> (2,context);
}
QModelIndex retval= model->index(row,column,index);
return engine->toScriptValue(retval);
}

QScriptValue QAbstractItemModel_rowCount(QScriptContext*context,
QScriptEngine*)
{
QAbstractItemModel*model= getself<QAbstractItemModel*> (context);
QModelIndex index;
if(context->argumentCount()==1)
{
index= argument<QModelIndex> (0,context);
}
return QScriptValue(model->rowCount(index));
}

QScriptValue QAbstractItemModel_hasChildren(QScriptContext*context,
QScriptEngine*engine)
{
QAbstractItemModel*model= getself<QAbstractItemModel*> (context);
QModelIndex index;
if(context->argumentCount()==1)
{
index= argument<QModelIndex> (0,context);
}
return QScriptValue(engine,model->hasChildren(index));
}

/*:618*//*621:*/
#line 14666 "./typica.w"

QScriptValue QModelIndex_toScriptValue(QScriptEngine*engine,const QModelIndex&index)
{
QVariant var;
var.setValue(index);
QScriptValue object= engine->newVariant(var);
return object;
}

void QModelIndex_fromScriptValue(const QScriptValue&value,QModelIndex&index)
{
index= value.toVariant().value<QModelIndex> ();
}

/*:621*//*636:*/
#line 14934 "./typica.w"

QScriptValue constructDeviceConfigurationWindow(QScriptContext*,
QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new DeviceConfigurationWindow);
return object;
}

/*:636*//*712:*/
#line 17439 "./typica.w"

QScriptValue constructModbusRTUDevice(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==2)
{
object= engine->newQObject(new ModbusRTUDevice(argument<DeviceTreeModel*> (0,context),
argument<QModelIndex> (1,context)),
QScriptEngine::ScriptOwnership);
setModbusRTUDeviceProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"ModbusRTUDevice constructor. This takes the configuration model "
"and an index.");
}
return object;
}

/*:712*//*713:*/
#line 17461 "./typica.w"

QScriptValue ModbusRTUDevice_pVChannel(QScriptContext*context,QScriptEngine*engine)
{
ModbusRTUDevice*self= getself<ModbusRTUDevice*> (context);
QScriptValue object;
if(self)
{
if(self->channels.size()> 0)
{
object= engine->newQObject(self->channels.at(0));
setChannelProperties(object,engine);
}
}
return object;
}

QScriptValue ModbusRTUDevice_sVChannel(QScriptContext*context,QScriptEngine*engine)
{
ModbusRTUDevice*self= getself<ModbusRTUDevice*> (context);
QScriptValue object;
if(self)
{
if(self->channels.size()> 1)
{
object= engine->newQObject(self->channels.at(1));
setChannelProperties(object,engine);
}
}
return object;
}

/*:713*//*714:*/
#line 17494 "./typica.w"

void setModbusRTUDeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("pVChannel",engine->newFunction(ModbusRTUDevice_pVChannel));
value.setProperty("sVChannel",engine->newFunction(ModbusRTUDevice_sVChannel));
}

/*:714*/
#line 758 "./typica.w"

/*513:*/
#line 12321 "./typica.w"

int main(int argc,char**argv)
{
int*c= &argc;
Application app(*c,argv);
/*514:*/
#line 12345 "./typica.w"

QStringList themeSearchPath= QIcon::themeSearchPaths();
themeSearchPath.append(":/resources/icons/tango");
QIcon::setThemeSearchPaths(themeSearchPath);
QIcon::setThemeName(":/resources/icons/tango");
app.setWindowIcon(QIcon(":/resources/icons/appicons/logo.svg"));

/*:514*/
#line 12326 "./typica.w"

QSettings settings;

/*646:*/
#line 15146 "./typica.w"

app.registerDeviceConfigurationWidget("roaster",RoasterConfWidget::staticMetaObject);

/*:646*//*656:*/
#line 15374 "./typica.w"

app.registerDeviceConfigurationWidget("nidaqmxbase",
NiDaqMxBaseDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxbase9211series",
NiDaqMxBase9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("ni9211seriestc",
Ni9211TcConfWidget::staticMetaObject);

/*:656*//*664:*/
#line 15591 "./typica.w"

app.registerDeviceConfigurationWidget("nidaqmx",NiDaqMxDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmx9211series",NiDaqMx9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxtc01",NiDaqMxTc01ConfWidget::staticMetaObject);

/*:664*//*688:*/
#line 16552 "./typica.w"

app.registerDeviceConfigurationWidget("modbusrtuport",ModbusRtuPortConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbusrtudevice",ModbusRtuDeviceConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturepv",ModbusRtuDeviceTPvConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturesv",ModbusRtuDeviceTSvConfWidget::staticMetaObject);

/*:688*//*693:*/
#line 16637 "./typica.w"

app.registerDeviceConfigurationWidget("annotationbutton",AnnotationButtonConfWidget::staticMetaObject);

/*:693*//*696:*/
#line 16707 "./typica.w"

app.registerDeviceConfigurationWidget("reconfigurablebutton",ReconfigurableAnnotationButtonConfWidget::staticMetaObject);

/*:696*//*699:*/
#line 16834 "./typica.w"

app.registerDeviceConfigurationWidget("annotationspinbox",NoteSpinConfWidget::staticMetaObject);

/*:699*//*717:*/
#line 18007 "./typica.w"

app.registerDeviceConfigurationWidget("modbusrtu",ModbusConfigurator::staticMetaObject);

/*:717*//*724:*/
#line 18137 "./typica.w"

app.registerDeviceConfigurationWidget("linearspline",LinearSplineInterpolationConfWidget::staticMetaObject);

/*:724*//*728:*/
#line 18226 "./typica.w"

app.registerDeviceConfigurationWidget("translation",TranslationConfWidget::staticMetaObject);

/*:728*/
#line 12329 "./typica.w"

/*515:*/
#line 12358 "./typica.w"

if(settings.value("database/exists","false").toString()=="true")
{
/*520:*/
#line 12478 "./typica.w"

QSqlDatabase database= 
QSqlDatabase::addDatabase(settings.value("database/driver").toString());
database.setHostName(settings.value("database/hostname").toString());
database.setDatabaseName(settings.value("database/dbname").toString());
database.setUserName(settings.value("database/user").toString());
database.setPassword(settings.value("database/password").toString());
if(!database.open())
{
settings.setValue("database/exists","false");
}

/*:520*/
#line 12361 "./typica.w"

}
if(settings.value("database/exists","false").toString()=="false")
{
/*519:*/
#line 12469 "./typica.w"

SqlConnectionSetup dialog;
dialog.exec();

/*:519*/
#line 12365 "./typica.w"

}


/*:515*/
#line 12330 "./typica.w"

/*152:*/
#line 3626 "./typica.w"

QStringList arguments= QCoreApplication::arguments();
int position= arguments.indexOf("-c");
QString filename= QString();
if(position!=-1)
{
if(arguments.size()>=position+1)
{
filename= arguments.at(position+1);
}
}
if(filename.isEmpty())
{
filename= QFileDialog::getOpenFileName(NULL,"Open Configuration File",
settings.value("config","").toString());
}
QDir directory;
if(!filename.isEmpty())
{
QFile file(filename);
QFileInfo info(filename);
directory= info.dir();
settings.setValue("config",directory.path());
if(file.open(QIODevice::ReadOnly))
{
app.configuration()->setContent(&file,true);
}
}
/*153:*/
#line 3660 "./typica.w"

QDomElement root= app.configuration()->documentElement();
QDomNodeList children= root.childNodes();
QString replacementDoc;
QDomDocument includedDoc;
QDomDocumentFragment fragment;
for(int i= 0;i<children.size();i++)
{
QDomNode currentNode= children.at(i);
QDomElement currentElement;
if(currentNode.nodeName()=="include")
{
currentElement= currentNode.toElement();
if(currentElement.hasAttribute("src"))
{
replacementDoc= directory.path();
replacementDoc.append('/');
replacementDoc.append(currentElement.attribute("src"));
QFile doc(replacementDoc);
if(doc.open(QIODevice::ReadOnly))
{
includedDoc.setContent(&doc,true);
fragment= includedDoc.createDocumentFragment();
fragment.appendChild(includedDoc.documentElement());
root.replaceChild(fragment,currentNode);
doc.close();
}
}
}
}

/*:153*/
#line 3654 "./typica.w"


/*:152*/
#line 12331 "./typica.w"

/*18:*/
#line 870 "./typica.w"

QScriptEngine*engine= new QScriptEngine;
QScriptValue constructor;
QScriptValue value;

/*:18*//*28:*/
#line 1046 "./typica.w"

constructor= engine->newFunction(constructQWidget);
value= engine->newQMetaObject(&QWidget::staticMetaObject,constructor);
engine->globalObject().setProperty("QWidget",value);

/*:28*//*36:*/
#line 1246 "./typica.w"

constructor= engine->newFunction(constructQMainWindow);
value= engine->newQMetaObject(&ScriptQMainWindow::staticMetaObject,
constructor);
engine->globalObject().setProperty("QMainWindow",value);

/*:36*//*47:*/
#line 1451 "./typica.w"

constructor= engine->newFunction(constructQFrame);
value= engine->newQMetaObject(&QFrame::staticMetaObject,constructor);
engine->globalObject().setProperty("QFrame",value);

/*:47*//*50:*/
#line 1484 "./typica.w"

constructor= engine->newFunction(constructQLabel);
value= engine->newQMetaObject(&QLabel::staticMetaObject,constructor);
engine->globalObject().setProperty("QLabel",value);

/*:50*//*53:*/
#line 1531 "./typica.w"

constructor= engine->newFunction(constructQSplitter);
value= engine->newQMetaObject(&QSplitter::staticMetaObject,constructor);
engine->globalObject().setProperty("QSplitter",value);

/*:53*//*60:*/
#line 1702 "./typica.w"

constructor= engine->newFunction(constructQBoxLayout);
value= engine->newQMetaObject(&QBoxLayout::staticMetaObject,constructor);
engine->globalObject().setProperty("QBoxLayout",value);

/*:60*//*64:*/
#line 1814 "./typica.w"

constructor= engine->newFunction(constructQAction);
value= engine->newQMetaObject(&QAction::staticMetaObject,constructor);
engine->globalObject().setProperty("QAction",value);

/*:64*//*67:*/
#line 1873 "./typica.w"

value= engine->newQMetaObject(&QFileDialog::staticMetaObject);
value.setProperty("getOpenFileName",
engine->newFunction(QFileDialog_getOpenFileName));
value.setProperty("getSaveFileName",
engine->newFunction(QFileDialog_getSaveFileName));
engine->globalObject().setProperty("QFileDialog",value);

/*:67*//*72:*/
#line 1985 "./typica.w"

constructor= engine->newFunction(constructQFile);
value= engine->newQMetaObject(&QFile::staticMetaObject,constructor);
engine->globalObject().setProperty("QFile",value);

/*:72*//*79:*/
#line 2102 "./typica.w"

constructor= engine->newFunction(constructQBuffer);
value= engine->newQMetaObject(&QBuffer::staticMetaObject,constructor);
engine->globalObject().setProperty("QBuffer",value);

/*:79*//*82:*/
#line 2150 "./typica.w"

constructor= engine->newFunction(constructXQuery);
engine->globalObject().setProperty("XQuery",constructor);

/*:82*//*88:*/
#line 2244 "./typica.w"

constructor= engine->newFunction(constructXmlWriter);
engine->globalObject().setProperty("XmlWriter",constructor);

/*:88*//*97:*/
#line 2450 "./typica.w"

constructor= engine->newFunction(constructXmlReader);
engine->globalObject().setProperty("XmlReader",constructor);

/*:97*//*104:*/
#line 2574 "./typica.w"

value= engine->newQObject(&settings);
setQSettingsProperties(value,engine);
engine->globalObject().setProperty("QSettings",value);

/*:104*//*108:*/
#line 2655 "./typica.w"

constructor= engine->newFunction(constructQLCDNumber);
value= engine->newQMetaObject(&QLCDNumber::staticMetaObject,constructor);
engine->globalObject().setProperty("QLCDNumber",value);

/*:108*//*111:*/
#line 2711 "./typica.w"

constructor= engine->newFunction(constructQTime);
engine->globalObject().setProperty("QTime",constructor);

/*:111*//*132:*/
#line 3215 "./typica.w"

constructor= engine->newFunction(constructQPushButton);
value= engine->newQMetaObject(&QPushButton::staticMetaObject,constructor);
engine->globalObject().setProperty("QPushButton",value);

/*:132*//*139:*/
#line 3326 "./typica.w"

constructor= engine->newFunction(constructQSqlQuery);
engine->globalObject().setProperty("QSqlQuery",constructor);

/*:139*//*146:*/
#line 3487 "./typica.w"

engine->globalObject().setProperty("baseName",engine->newFunction(baseName));
engine->globalObject().setProperty("dir",engine->newFunction(dir));
engine->globalObject().setProperty("sqlToArray",
engine->newFunction(sqlToArray));
engine->globalObject().setProperty("setFont",engine->newFunction(setFont));
engine->globalObject().setProperty("annotationFromRecord",
engine->newFunction(annotationFromRecord));
engine->globalObject().setProperty("setTabOrder",engine->newFunction(setTabOrder));

/*:146*//*157:*/
#line 3823 "./typica.w"

engine->globalObject().setProperty("createWindow",
engine->newFunction(createWindow));

/*:157*//*204:*/
#line 5299 "./typica.w"

engine->globalObject().setProperty("findChildObject",
engine->newFunction(findChildObject));

/*:204*//*243:*/
#line 6474 "./typica.w"

constructor= engine->newFunction(constructDAQ);
value= engine->newQMetaObject(&DAQ::staticMetaObject,constructor);
engine->globalObject().setProperty("DAQ",value);

/*:243*//*252:*/
#line 6672 "./typica.w"

constructor= engine->newFunction(constructFakeDAQ);
value= engine->newQMetaObject(&FakeDAQ::staticMetaObject,constructor);
engine->globalObject().setProperty("FakeDAQ",value);

/*:252*//*263:*/
#line 6949 "./typica.w"

constructor= engine->newFunction(constructLinearCalibrator);
value= engine->newQMetaObject(&LinearCalibrator::staticMetaObject,
constructor);
engine->globalObject().setProperty("LinearCalibrator",value);

/*:263*//*268:*/
#line 7087 "./typica.w"

constructor= engine->newFunction(constructLinearSplineInterpolator);
value= engine->newQMetaObject(&LinearSplineInterpolator::staticMetaObject,constructor);
engine->globalObject().setProperty("LinearSplineInterpolator",value);

/*:268*//*277:*/
#line 7270 "./typica.w"

constructor= engine->newFunction(constructTemperatureDisplay);
value= engine->newQMetaObject(&TemperatureDisplay::staticMetaObject,
constructor);
engine->globalObject().setProperty("TemperatureDisplay",value);

/*:277*//*284:*/
#line 7408 "./typica.w"

constructor= engine->newFunction(constructMeasurementTimeOffset);
value= engine->newQMetaObject(&MeasurementTimeOffset::staticMetaObject,
constructor);
engine->globalObject().setProperty("MeasurementTimeOffset",value);

/*:284*//*289:*/
#line 7519 "./typica.w"

constructor= engine->newFunction(constructThresholdDetector);
value= engine->newQMetaObject(&ThresholdDetector::staticMetaObject,constructor);
engine->globalObject().setProperty("ThresholdDetector",value);

/*:289*//*294:*/
#line 7617 "./typica.w"

constructor= engine->newFunction(constructZeroEmitter);
value= engine->newQMetaObject(&ZeroEmitter::staticMetaObject,constructor);
engine->globalObject().setProperty("ZeroEmitter",value);

/*:294*//*299:*/
#line 7696 "./typica.w"

constructor= engine->newFunction(constructMeasurementAdapter);
value= engine->newQMetaObject(&MeasurementAdapter::staticMetaObject,
constructor);
engine->globalObject().setProperty("MeasurementAdapter",value);

/*:299*//*314:*/
#line 8045 "./typica.w"

constructor= engine->newFunction(constructGraphView);
value= engine->newQMetaObject(&GraphView::staticMetaObject,constructor);
engine->globalObject().setProperty("GraphView",value);

/*:314*//*336:*/
#line 8616 "./typica.w"

constructor= engine->newFunction(constructZoomLog);
value= engine->newQMetaObject(&ZoomLog::staticMetaObject,constructor);
engine->globalObject().setProperty("ZoomLog",value);

/*:336*//*373:*/
#line 9534 "./typica.w"

constructor= engine->newFunction(constructAnnotationButton);
value= engine->newQMetaObject(&AnnotationButton::staticMetaObject,
constructor);
engine->globalObject().setProperty("AnnotationButton",value);

/*:373*//*381:*/
#line 9676 "./typica.w"

constructor= engine->newFunction(constructAnnotationSpinBox);
value= engine->newQMetaObject(&AnnotationSpinBox::staticMetaObject,
constructor);
engine->globalObject().setProperty("AnnotationSpinBox",value);

/*:381*//*402:*/
#line 10097 "./typica.w"

constructor= engine->newFunction(constructTimerDisplay);
value= engine->newQMetaObject(&TimerDisplay::staticMetaObject,constructor);
engine->globalObject().setProperty("TimerDisplay",value);

/*:402*//*429:*/
#line 10591 "./typica.w"

constructor= engine->newFunction(constructWidgetDecorator);
value= engine->newQMetaObject(&WidgetDecorator::staticMetaObject,constructor);
engine->globalObject().setProperty("WidgetDecorator",value);

/*:429*//*442:*/
#line 10873 "./typica.w"

constructor= engine->newFunction(constructLogEditWindow);
value= engine->newQMetaObject(&LogEditWindow::staticMetaObject,constructor);
engine->globalObject().setProperty("LogEditWindow",value);

/*:442*//*461:*/
#line 11347 "./typica.w"

constructor= engine->newFunction(constructXMLInput);
value= engine->newQMetaObject(&XMLInput::staticMetaObject,constructor);
engine->globalObject().setProperty("XMLInput",value);

/*:461*//*468:*/
#line 11514 "./typica.w"

constructor= engine->newFunction(constructWebView);
value= engine->newQMetaObject(&QWebView::staticMetaObject,constructor);
engine->globalObject().setProperty("WebView",value);

/*:468*//*481:*/
#line 11706 "./typica.w"

value= engine->newQObject(AppInstance);
engine->globalObject().setProperty("Application",value);

/*:481*//*532:*/
#line 12651 "./typica.w"

constructor= engine->newFunction(constructSqlQueryView);
value= engine->newQMetaObject(&SqlQueryView::staticMetaObject,constructor);
engine->globalObject().setProperty("SqlQueryView",value);

/*:532*//*616:*/
#line 14542 "./typica.w"

constructor= engine->newFunction(constructDeviceTreeModel);
value= engine->newQMetaObject(&DeviceTreeModel::staticMetaObject,
constructor);
engine->globalObject().setProperty("DeviceTreeModel",value);

/*:616*//*622:*/
#line 14682 "./typica.w"

qScriptRegisterMetaType(engine,QModelIndex_toScriptValue,QModelIndex_fromScriptValue);

/*:622*//*637:*/
#line 14944 "./typica.w"

constructor= engine->newFunction(constructDeviceConfigurationWindow);
value= engine->newQMetaObject(&DeviceConfigurationWindow::staticMetaObject,
constructor);
engine->globalObject().setProperty("DeviceConfigurationWindow",value);

/*:637*//*711:*/
#line 17430 "./typica.w"

constructor= engine->newFunction(constructModbusRTUDevice);
value= engine->newQMetaObject(&ModbusRTUDevice::staticMetaObject,constructor);
engine->globalObject().setProperty("ModbusRTUDevice",value);

/*:711*/
#line 12332 "./typica.w"

app.engine= engine;
/*154:*/
#line 3708 "./typica.w"

QString styleText;
QString programText;
QDomElement currentElement;
for(int i= 0;i<children.size();i++)
{
QDomNode currentNode= children.at(i);
if(currentNode.nodeName()=="style")
{
currentElement= currentNode.toElement();
styleText.append(currentElement.text());
}
else if(currentNode.nodeName()=="program")
{
currentElement= currentNode.toElement();
programText.append(currentElement.text());
}
}
app.setStyleSheet(styleText);
QScriptValue result= engine->evaluate(programText);
/*155:*/
#line 3733 "./typica.w"

if(engine->hasUncaughtException())
{
int line= engine->uncaughtExceptionLineNumber();
qDebug()<<"Uncaught excpetion at line "<<line<<" : "<<
result.toString();
QString trace;
foreach(trace,engine->uncaughtExceptionBacktrace())
{
qDebug()<<trace;
}
}

/*:155*/
#line 3728 "./typica.w"


/*:154*/
#line 12334 "./typica.w"


int retval= app.exec();
delete engine;
return retval;
}

/*:513*/
#line 759 "./typica.w"

#include "moc_typica.cpp"

/*:15*/
