/*3:*/
#line 522 "./typica.w"

#define PROGRAM_NAME "Typica"

/*5:*/
#line 616 "./typica.w"

#include <QtCore> 
#include <QtGui> 
#include <QtScript> 
#include <QtScriptTools> 
#include <QtXml> 
#include <QtSql> 
#include <QtDebug> 
#include <QtXmlPatterns> 
#include <QtWebKit> 

/*:5*//*6:*/
#line 631 "./typica.w"

#include "helpmenu.h"

/*:6*//*281:*/
#line 6417 "./typica.w"

#include "units.h"

#line 1 "./measurement.w"
/*:281*//*554:*/
#line 197 "./webview.w"

#include "webview.h"

/*:554*//*567:*/
#line 375 "./webview.w"

#include "webelement.h"

#line 12418 "./typica.w"

/*:567*//*678:*/
#line 487 "./daterangeselector.w"

#include "daterangeselector.h"
#line 14135 "./typica.w"

/*:678*//*786:*/
#line 16655 "./typica.w"

#include "qextserialport.h"
#include "qextserialenumerator.h"

/*:786*//*957:*/
#line 124 "./dataqsdk.w"

#ifdef Q_OS_WIN32
#include <windef.h> 
#else
#define PASCAL
#endif

/*:957*//*981:*/
#line 862 "./dataqsdk.w"

#include <limits> 

/*:981*//*996:*/
#line 62 "./scales.w"

#include "draglabel.h"

/*:996*//*1011:*/
#line 335 "./scales.w"

#include "scale.h"

/*:1011*/
#line 525 "./typica.w"

/*20:*/
#line 946 "./typica.w"

class ScriptQMainWindow:public QMainWindow
{
Q_OBJECT
Q_PROPERTY(QString closePrompt READ closePrompt WRITE setClosePrompt)
public:
ScriptQMainWindow();
QString closePrompt();
public slots:
void show();
void saveSizeAndPosition(const QString&key);
void restoreSizeAndPosition(const QString&key);
void displayStatus(const QString&message= QString());
void setClosePrompt(QString prompt);
protected:
void closeEvent(QCloseEvent*event);
void showEvent(QShowEvent*event);
signals:
void aboutToClose(void);
private:
QString cprompt;
};

/*:20*//*160:*/
#line 3783 "./typica.w"

class SqlQueryConnection:public QSqlQuery
{
public:
SqlQueryConnection(const QString&query= QString());
~SqlQueryConnection();
QSqlQuery*operator->()const;
private:
QString connection;
QSqlQuery*q;
};

/*:160*//*230:*/
#line 5633 "./typica.w"

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

/*:230*//*236:*/
#line 5726 "./typica.w"

class ScriptValidator:public QValidator
{
Q_OBJECT
public:
ScriptValidator(QValidator*validator,QObject*parent= NULL);
void fixup(QString&input)const;
QValidator::State validate(QString&input,int&pos)const;
private:
QValidator*v;
};

/*:236*//*277:*/
#line 438 "./units.w"

Q_DECLARE_METATYPE(Units::Unit)

/*:277*//*282:*/
#line 19 "./measurement.w"

class Measurement:public QVariantMap
{
public:
Measurement(double temperature= 0,QTime time= QTime(),
Units::Unit sc= Units::Fahrenheit);
Measurement(double temperature);
double temperature()const;
QTime time()const;
void setTemperature(double temperature);
void setTime(QTime time);
void setUnit(Units::Unit scale);
Units::Unit scale()const;
Measurement toFahrenheit();
Measurement toCelsius();
Measurement toKelvin();
Measurement toRankine();
};

/*:282*//*286:*/
#line 128 "./measurement.w"

Q_DECLARE_METATYPE(Measurement)

/*:286*//*293:*/
#line 6481 "./typica.w"

class Channel;
class DAQImplementation;

class DAQ:public QObject
{
Q_OBJECT
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

/*:293*//*294:*/
#line 6519 "./typica.w"

class DAQImplementation:public QThread
{
Q_OBJECT
public:
DAQImplementation(const QString&driverinfo);
~DAQImplementation();
void run();
bool measure();
/*296:*/
#line 6550 "./typica.w"

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

/*:296*/
#line 6528 "./typica.w"

/*297:*/
#line 6566 "./typica.w"

bool useBase;
QString device;
QVector<Channel*> channelMap;
unsigned int handle;
int error;
int channels;
bool ready;
bool clockRateSet;
double clockRate;
QLibrary driver;
QVector<Units::Unit> unitMap;
QList<NiChannelSpec*> channelSpecs;

/*:297*/
#line 6529 "./typica.w"

};

/*:294*//*295:*/
#line 6535 "./typica.w"

struct NiChannelSpec
{
char*channelName;
signed long units;
signed long thermocouple;
};

/*:295*//*315:*/
#line 7095 "./typica.w"

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

/*:315*//*322:*/
#line 7282 "./typica.w"

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

/*:322*//*326:*/
#line 7349 "./typica.w"

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
Measurement newMeasurement(Measurement measure);
signals:
void measurement(Measurement measure);
void newData(Measurement measure);
private:
double Lo1;
double Lo2;
double Up1;
double Up2;
double sensitivitySetting;
bool clamp;
};

/*:326*//*333:*/
#line 7545 "./typica.w"

class LinearSplineInterpolator:public QObject
{
Q_OBJECT
public:
LinearSplineInterpolator(QObject*parent= NULL);
Q_INVOKABLE void add_pair(double source,double destination);
public slots:
Measurement newMeasurement(Measurement measure);
signals:
void newData(Measurement measure);
private:
void make_interpolators();
QMap<double,double> *pairs;
QList<LinearCalibrator*> *interpolators;
};

/*:333*//*338:*/
#line 7681 "./typica.w"

class TemperatureDisplay:public QLCDNumber
{
Q_OBJECT
int unit;
bool r;
public:
TemperatureDisplay(QWidget*parent= NULL);
~TemperatureDisplay();
public slots:
void setValue(Measurement temperature);
void invalidate();
void setDisplayUnits(Units::Unit scale);
void setRelativeMode(bool relative);
};

/*:338*//*349:*/
#line 7900 "./typica.w"

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

/*:349*//*356:*/
#line 8052 "./typica.w"

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

/*:356*//*361:*/
#line 8158 "./typica.w"

class ZeroEmitter:public QObject
{
Q_OBJECT
Q_PROPERTY(int column READ column WRITE setColumn)
Measurement cache;
int col;
public:
ZeroEmitter(int tempcolumn= 1);
int column();
double lastTemperature();
public slots:
void newMeasurement(Measurement measure);
void setColumn(int column);
void emitZero();
signals:
void measurement(Measurement measure,int tempcolumn);
};

/*:361*//*366:*/
#line 8252 "./typica.w"

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

/*:366*//*371:*/
#line 8341 "./typica.w"

class GraphView:public QGraphicsView
{
Q_OBJECT
QGraphicsScene*theScene;
QMap<int,QList<QGraphicsLineItem*> *> *graphLines;
QMap<int,QPointF> *prevPoints;
QMap<int,double> *translations;
QList<QGraphicsItem*> *gridLinesF;
QList<QGraphicsItem*> *gridLinesC;
QList<QGraphicsItem*> *relativeGridLines;
bool relativeEnabled;
bool timeIndicatorEnabled;
QGraphicsLineItem*timeLine;
LinearSplineInterpolator*relativeAdjuster;
public:
GraphView(QWidget*parent= NULL);
void removeSeries(int column);
protected:
void resizeEvent(QResizeEvent*event);
public slots:
void newMeasurement(Measurement measure,int tempcolumn);
void setSeriesTranslation(int column,double offset);
void setTimeIndicatorEnabled(bool enabled);
void clear();
void showF();
void showC();
};

/*:371*//*388:*/
#line 8806 "./typica.w"

class MeasurementModel;
class ZoomLog:public QTableView
{
Q_OBJECT
/*389:*/
#line 8855 "./typica.w"

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
QList<int> saveControlCols;
QList<int> saveNoteCols;
QList<int> currentColumnSet;

/*:389*/
#line 8811 "./typica.w"

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
Q_INVOKABLE Units::Unit displayUnits();
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
void addOutputControlColumn(int column);
void addOutputAnnotationColumn(int column);
void clearOutputColumns();
void setDisplayUnits(Units::Unit scale);
void addToCurrentColumnSet(int column);
void clearCurrentColumnSet();
protected:
virtual void showEvent(QShowEvent*event);
};

/*:388*//*414:*/
#line 9551 "./typica.w"

class MeasurementList;
class MeasurementModel:public QAbstractItemModel
{
Q_OBJECT
Units::Unit unit;
QList<MeasurementList*> *entries;
QStringList*hData;
int colcount;
QHash<int,int> *lastTemperature;
QList<MeasurementList*> ::iterator lastInsertion;
QHash<int,bool> *controlColumns;
public:
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
Units::Unit displayUnits();
public slots:
void newMeasurement(Measurement measure,int tempcolumn);
void newAnnotation(QString annotation,int tempcolumn,
int annotationColumn);
void clear();
void setDisplayUnits(Units::Unit scale);
signals:
void rowChanged(int);
};

/*:414*//*415:*/
#line 9595 "./typica.w"

class MeasurementList:public QVariantList
{
public:
bool operator<(const MeasurementList&other)const;
bool operator==(const MeasurementList&other)const;
};

/*:415*//*441:*/
#line 10253 "./typica.w"

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

/*:441*//*449:*/
#line 10378 "./typica.w"

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

/*:449*//*457:*/
#line 10537 "./typica.w"

class TimerDisplay:public QLCDNumber
{
Q_OBJECT
/*458:*/
#line 10587 "./typica.w"

Q_PROPERTY(QTime seconds READ seconds WRITE setTimer)
Q_PROPERTY(TimerMode mode READ mode WRITE setMode)
Q_PROPERTY(bool running READ isRunning)
Q_PROPERTY(QTime resetValue READ resetValue WRITE setResetValue)
Q_PROPERTY(QString displayFormat READ displayFormat WRITE setDisplayFormat)
Q_PROPERTY(bool autoReset READ autoReset WRITE setAutoReset)
Q_PROPERTY(QString value READ value)

/*:458*/
#line 10541 "./typica.w"

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
/*459:*/
#line 10598 "./typica.w"

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

/*:459*/
#line 10578 "./typica.w"

};

/*:457*//*480:*/
#line 10990 "./typica.w"

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

/*:480*//*493:*/
#line 11268 "./typica.w"

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

/*:493*//*495:*/
#line 11310 "./typica.w"

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

/*:495*//*506:*/
#line 11485 "./typica.w"

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

/*:506*//*520:*/
#line 11793 "./typica.w"

class XMLOutput:public QObject
{
Q_OBJECT
MeasurementModel*data;
QIODevice*out;
int time;
QMap<int,QString> temperatureColumns;
QMap<int,QString> controlColumns;
QMap<int,QString> annotationColumns;
public:
XMLOutput(MeasurementModel*model,QIODevice*device,int timec= 0);
void addTemperatureColumn(const QString&series,int column);
void addControlColumn(const QString&series,int column);
void addAnnotationColumn(const QString&series,int column);
void setModel(MeasurementModel*model);
void setTimeColumn(int column);
void setDevice(QIODevice*device);
bool output();
};

/*:520*//*527:*/
#line 12029 "./typica.w"

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

/*:527*//*538:*/
#line 12283 "./typica.w"

class CSVOutput
{
MeasurementModel*data;
QIODevice*out;
int time;
QMap<int,QString> temperatureColumns;
QMap<int,QString> controlColumns;
QMap<int,QString> annotationColumns;
public:
CSVOutput(MeasurementModel*model,QIODevice*device,int timec= 0);
void addTemperatureColumn(const QString&series,int column);
void addControlColumn(const QString&series,int column);
void addAnnotationColumn(const QString&series,int column);
void setModel(MeasurementModel*model);
void setTimeColumn(int column);
void setDevice(QIODevice*device);
bool output();
};

/*:538*//*568:*/
#line 12426 "./typica.w"

#define AppInstance (qobject_cast<Application *> (qApp))

class NodeInserter;
class DeviceTreeModel;
class Application:public QApplication
{
Q_OBJECT
public:
Application(int&argc,char**argv);
QDomDocument*configuration();
/*710:*/
#line 14981 "./typica.w"

QDomDocument deviceConfiguration();

/*:710*//*743:*/
#line 15654 "./typica.w"

void registerDeviceConfigurationWidget(QString driver,QMetaObject widget);
QWidget*deviceConfigurationWidget(DeviceTreeModel*model,
const QModelIndex&index);

/*:743*//*748:*/
#line 15758 "./typica.w"

QList<NodeInserter*> topLevelNodeInserters;

/*:748*/
#line 12437 "./typica.w"

QSqlDatabase database();
QScriptEngine*engine;
public slots:
/*711:*/
#line 14988 "./typica.w"

void saveDeviceConfiguration();

/*:711*/
#line 12441 "./typica.w"

private:
/*709:*/
#line 14972 "./typica.w"

QDomDocument deviceConfigurationDocument;

/*:709*//*742:*/
#line 15648 "./typica.w"

QHash<QString,QMetaObject> deviceConfigurationWidgets;

/*:742*/
#line 12443 "./typica.w"

QDomDocument conf;
};

/*:568*//*576:*/
#line 12569 "./typica.w"

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
void clear();
bool removeRows(int row,int count,
const QModelIndex&parent= QModelIndex());
int findData(const QVariant&value,int column,int role= Qt::UserRole);
};

/*:576*//*592:*/
#line 12954 "./typica.w"

class SqlComboBox:public QComboBox
{
Q_OBJECT
int dataColumn;
int displayColumn;
bool dataColumnShown;
QString specialNullText;
QVariant specialNullData;
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
void setNullText(QString nullText);
void setNullData(QVariant nullData);
};

/*:592*//*599:*/
#line 13101 "./typica.w"

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

/*:599*//*614:*/
#line 13312 "./typica.w"

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

/*:614*//*619:*/
#line 13447 "./typica.w"

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

/*:619*//*634:*/
#line 13702 "./typica.w"

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

/*:634*//*646:*/
#line 13911 "./typica.w"

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

/*:646*//*679:*/
#line 14150 "./typica.w"

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

/*:679*//*689:*/
#line 14366 "./typica.w"

class ScaleControl:public QGraphicsView
{
Q_OBJECT
Q_PROPERTY(double initialValue READ initialValue WRITE setInitialValue)
Q_PROPERTY(double finalValue READ finalValue WRITE setFinalValue)
/*690:*/
#line 14392 "./typica.w"

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

/*:690*/
#line 14372 "./typica.w"

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

/*:689*//*701:*/
#line 14689 "./typica.w"

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

/*:701*//*717:*/
#line 15077 "./typica.w"

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

/*:717*//*719:*/
#line 15152 "./typica.w"

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

/*:719*//*738:*/
#line 15606 "./typica.w"

Q_DECLARE_METATYPE(QModelIndex)

/*:738*//*746:*/
#line 15713 "./typica.w"

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

/*:746*//*749:*/
#line 15768 "./typica.w"

class DeviceConfigurationWindow:public QWidget
{
Q_OBJECT
public:
DeviceConfigurationWindow();
public slots:
void addDevice();
void removeNode();
void newSelection(const QModelIndex&index);
private slots:
void resizeColumn();
private:
QDomDocument document;
DeviceTreeModel*model;
QTreeView*view;
QScrollArea*configArea;
};

/*:749*//*758:*/
#line 15938 "./typica.w"

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

/*:758*//*762:*/
#line 16023 "./typica.w"

class RoasterConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE RoasterConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateRoasterId(int id);
};

/*:762*//*767:*/
#line 16177 "./typica.w"

class NiDaqMxBaseDriverConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxBaseDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
};

/*:767*//*769:*/
#line 16223 "./typica.w"

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

/*:769*//*773:*/
#line 16309 "./typica.w"

class Ni9211TcConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE Ni9211TcConfWidget(DeviceTreeModel*device,
const QModelIndex&index);
private slots:
void updateThermocoupleType(const QString&type);
void updateColumnName(const QString&name);
void updateHidden(bool hidden);
};

/*:773*//*778:*/
#line 16425 "./typica.w"

class NiDaqMxDriverConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
};

/*:778*//*780:*/
#line 16466 "./typica.w"

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

/*:780*//*782:*/
#line 16535 "./typica.w"

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
void updateHidden(bool hidden);
};

/*:782*//*787:*/
#line 16666 "./typica.w"

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

/*:787*//*789:*/
#line 16714 "./typica.w"

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

/*:789*//*791:*/
#line 16785 "./typica.w"

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

/*:791*//*793:*/
#line 16823 "./typica.w"

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

/*:793*//*795:*/
#line 16856 "./typica.w"

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

/*:795*//*798:*/
#line 16909 "./typica.w"

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

/*:798*//*800:*/
#line 16971 "./typica.w"

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

/*:800*//*802:*/
#line 17122 "./typica.w"

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

/*:802*//*804:*/
#line 17381 "./typica.w"

class ModbusRtuDeviceTPvConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateAddress(int newAddress);
};

/*:804*//*806:*/
#line 17427 "./typica.w"

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

/*:806*//*810:*/
#line 17621 "./typica.w"

class AnnotationButtonConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE AnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateButtonText(const QString&text);
void updateAnnotationText(const QString&text);
};

/*:810*//*814:*/
#line 17689 "./typica.w"

class ReconfigurableAnnotationButtonConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateButtonText(const QString&text);
void updateAnnotationText(const QString&text);
};

/*:814*//*817:*/
#line 17763 "./typica.w"

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

/*:817*//*820:*/
#line 12 "./freeannotation.w"

class FreeAnnotationConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE FreeAnnotationConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateLabel(const QString&text);
};

/*:820*//*824:*/
#line 11 "./settings.w"

class SettingsWindow:public QMainWindow
{
Q_OBJECT
public:
SettingsWindow();
};

/*:824*//*829:*/
#line 8 "./graphsettings.w"

class GraphSettingsWidget:public QWidget
{
Q_OBJECT
public:
GraphSettingsWidget();
};

/*:829*//*831:*/
#line 46 "./graphsettings.w"

class GraphSettingsRelativeTab:public QWidget
{
Q_OBJECT
public:
GraphSettingsRelativeTab();
public slots:
void updateEnableSetting(bool enable);
void updateColorSetting(const QString&color);
void updateAxisSetting(const QString&gridList);
void updateUnit(int unit);
void showColorPicker();
private:
QLineEdit*colorEdit;
};

/*:831*//*835:*/
#line 7 "./advancedsettings.w"

class AdvancedSettingsWidget:public QWidget
{
Q_OBJECT
public:
AdvancedSettingsWidget();
public slots:
void enableDiagnosticLogging(bool enabled);
};

/*:835*//*839:*/
#line 17888 "./typica.w"

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
void timeout();
private:
QextSerialPort*port;
QByteArray responseBuffer;
QList<QByteArray> messageQueue;
QList<QObject*> retObjQueue;
QList<char*> callbackQueue;
quint16 calculateCRC(QByteArray data);
QTimer*messageDelayTimer;
QTimer*commTimeout;
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

/*:839*//*855:*/
#line 18591 "./typica.w"

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
void updatePVHidden(bool hidden);
void updateSVHidden(bool hidden);
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

/*:855*//*859:*/
#line 36 "./unsupportedserial.w"

class UnsupportedSerialDeviceConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE UnsupportedSerialDeviceConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateConfiguration();
void saveScript();
void addChannel();
private:
SaltModel*deviceSettingsModel;
QTextEdit*scriptEditor;
};

/*:859*//*864:*/
#line 166 "./unsupportedserial.w"

class UnsupportedDeviceChannelConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE UnsupportedDeviceChannelConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateColumnName(const QString&value);
void updateHidden(bool hidden);
void updateConfiguration();
private:
SaltModel*channelSettingsModel;
};

/*:864*//*869:*/
#line 298 "./unsupportedserial.w"

class JavaScriptDevice:public QObject
{
Q_OBJECT
public:
Q_INVOKABLE JavaScriptDevice(const QModelIndex&deviceIndex,
QScriptEngine*engine);
Q_INVOKABLE int channelCount();
Channel*getChannel(int channel);
Q_INVOKABLE bool isChannelHidden(int channel);
Q_INVOKABLE Units::Unit expectedChannelUnit(int channel);
Q_INVOKABLE QString channelColumnName(int channel);
Q_INVOKABLE QString channelIndicatorText(int channel);
public slots:
void setTemperatureColumn(int tcol);
void setAnnotationColumn(int ncol);
void start();
void stop();
signals:
void annotation(QString note,int tcol,int ncol);
void triggerStartBatch();
void triggerStopBatch();
void deviceStopRequested();
private:
QVariantMap deviceSettings;
QString deviceScript;
QList<Channel*> channelList;
QList<bool> hiddenState;
QList<Units::Unit> channelUnits;
QList<QString> columnNames;
QList<QString> indicatorTexts;
QList<QVariantMap> channelSettings;
int annotationTemperatureColumn;
int annotationNoteColumn;
QScriptEngine*scriptengine;
};

/*:869*//*894:*/
#line 11 "./phidgets.w"

class PhidgetsTemperatureSensorConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE PhidgetsTemperatureSensorConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void addChannel();
void updateRate(int ms);
};

/*:894*//*898:*/
#line 82 "./phidgets.w"

class PhidgetTemperatureSensorChannelConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE PhidgetTemperatureSensorChannelConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateColumnName(const QString&value);
void updateHidden(bool hidden);
void updateTC(int index);
void updateChannel(int channel);
private:
QComboBox*tcType;
};

/*:898*//*903:*/
#line 213 "./phidgets.w"

class PhidgetsTemperatureSensor:public QObject
{
Q_OBJECT
public:
Q_INVOKABLE PhidgetsTemperatureSensor(const QModelIndex&deviceIndex);
Q_INVOKABLE int channelCount();
Channel*getChannel(int channel);
Q_INVOKABLE bool isChannelHidden(int channel);
Q_INVOKABLE QString channelColumnName(int channel);
Q_INVOKABLE QString channelIndicatorText(int channel);
public slots:
void start();
void stop();
private slots:
void getMeasurements();
private:
QList<int> channelIndices;
QList<int> tctypes;
QList<Channel*> channelList;
QMap<int,Channel*> channelMap;
QList<bool> hiddenState;
QList<QString> columnNames;
QList<QString> indicatorTexts;
QLibrary driver;
QTimer sampleTimer;
void*device;
/*907:*/
#line 349 "./phidgets.w"

#ifdef _WIN32
typedef int(__stdcall*PhidgetHandleOnly)(void*);
typedef int(__stdcall*PhidgetHandleInt)(void*,int);
typedef int(__stdcall*PhidgetHandleIntInt)(void*,int,int);
typedef int(__stdcall*PhidgetHandleIntDoubleOut)(void*,int,double*);
#else
typedef int(*PhidgetHandleOnly)(void*);
typedef int(*PhidgetHandleInt)(void*,int);
typedef int(*PhidgetHandleIntInt)(void*,int,int);
typedef int(*PhidgetHandleIntDoubleOut)(void*,int,double*);
#endif
PhidgetHandleOnly createDevice;
PhidgetHandleInt openDevice;
PhidgetHandleInt waitForOpen;
PhidgetHandleIntInt setTCType;
PhidgetHandleIntDoubleOut getTemperature;
PhidgetHandleOnly closeDevice;
PhidgetHandleOnly deleteDevice;

/*:907*/
#line 240 "./phidgets.w"

};

/*:903*//*916:*/
#line 19129 "./typica.w"

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
SaltModel*tablemodel;
};

/*:916*//*922:*/
#line 19259 "./typica.w"

class CoolingTimerConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE CoolingTimerConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateResetTime(QTime time);
};

/*:922*//*926:*/
#line 19325 "./typica.w"

class RangeTimerConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE RangeTimerConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateStartButtonText(const QString&text);
void updateStopButtonText(const QString&text);
void updateStartColumnName(const QString&text);
void updateStopColumnName(const QString&text);
void updateStartValue(const QString&text);
void updateStopValue(const QString&text);
void updateStartTrigger(int option);
void updateStopTrigger(int option);
};

/*:926*//*931:*/
#line 19577 "./typica.w"

class MultiRangeTimerConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE MultiRangeTimerConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateColumnName(const QString&text);
void updateRangeData();
private:
SaltModel*tablemodel;
};

/*:931*//*936:*/
#line 19679 "./typica.w"

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

/*:936*//*940:*/
#line 16 "./rate.w"

class RateOfChange:public QObject
{
Q_OBJECT
public:
RateOfChange(int cachetime= 1,int scaletime= 1);
public slots:
void newMeasurement(Measurement measure);
void setCacheTime(int seconds);
void setScaleTime(int seconds);
signals:
void newData(Measurement measure);
private:
int ct;
int st;
QList<Measurement> cache;
};

/*:940*//*948:*/
#line 177 "./rate.w"

class RateOfChangeConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE RateOfChangeConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateColumn(const QString&column);
void updateCacheTime(const QString&seconds);
void updateScaleTime(const QString&seconds);
};

/*:948*//*954:*/
#line 19 "./dataqsdk.w"

class DataqSdkDeviceImplementation;
class DataqSdkDevice:public QObject
{
Q_OBJECT
DataqSdkDeviceImplementation*imp;
private slots:
void threadFinished();
public:
DataqSdkDevice(QString device);
~DataqSdkDevice();
Channel*newChannel(Units::Unit scale);
Q_INVOKABLE void setClockRate(double Hz);
Q_INVOKABLE void start();
static QStringList detectPorts();
static QStringList detectHardware();
};

/*:954*//*955:*/
#line 49 "./dataqsdk.w"

class DataqSdkDeviceImplementation:public QThread
{
Q_OBJECT
public:
DataqSdkDeviceImplementation();
~DataqSdkDeviceImplementation();
void run();
/*956:*/
#line 70 "./dataqsdk.w"

typedef struct di_inlist_struct{
unsigned short chan;
unsigned short diff;
unsigned short gain;
unsigned short unipolar;
unsigned short dig_out_enable;
unsigned short dig_out;
unsigned short ave;
unsigned short counter;
}DI_INLIST_STRUCT;

typedef int(PASCAL*FPDIOPEN)(unsigned);
typedef int(PASCAL*FPDICLOSE)(void);
typedef double(PASCAL*FPDISAMPLERATE)(double,long*,long*);
typedef double(PASCAL*FPDIMAXIMUMRATE)(double);
typedef int(PASCAL*FPDILISTLENGTH)(unsigned,unsigned);
typedef int(PASCAL*FPDIINLIST)(di_inlist_struct*);
typedef int*(PASCAL*FPDIBUFFERALLOC)(unsigned,unsigned);
typedef int(PASCAL*FPDISTARTSCAN)(void);
typedef unsigned(PASCAL*FPDISTATUSREAD)(short*,unsigned);
typedef unsigned(PASCAL*FPDIBUFFERSTATUS)(unsigned);
typedef int(PASCAL*FPDIBURSTRATE)(unsigned);
typedef int(PASCAL*FPDISTOPSCAN)(void);

FPDIOPEN di_open;
FPDICLOSE di_close;
FPDISAMPLERATE di_sample_rate;
FPDIMAXIMUMRATE di_maximum_rate;
FPDILISTLENGTH di_list_length;
FPDIINLIST di_inlist;
FPDIBUFFERALLOC di_buffer_alloc;
FPDISTARTSCAN di_start_scan;
FPDISTATUSREAD di_status_read;
FPDIBUFFERSTATUS di_buffer_status;
FPDIBURSTRATE di_burst_rate;
FPDISTOPSCAN di_stop_scan;

/*:956*/
#line 57 "./dataqsdk.w"

/*958:*/
#line 134 "./dataqsdk.w"

bool isOpen;
double sampleRate;
long oversample;
long burstDivisor;
QString device;
unsigned deviceNumber;
QVector<Channel*> channelMap;

int error;
int channels;
bool ready;
QLibrary*driver;
QVector<Units::Unit> unitMap;
int*input_buffer;
QTimer*eventClock;
QMultiMap<int,double> smoother;

/*:958*/
#line 58 "./dataqsdk.w"

public slots:
void measure();
private:
qint16*buffer;
};

/*:955*//*975:*/
#line 663 "./dataqsdk.w"

class DataqSdkDeviceConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE DataqSdkDeviceConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateAutoSelect(bool automatic);
void updateDeviceNumber(int deviceNumber);
void updatePort(QString portId);
void addChannel();
private:
QStackedWidget*deviceIdStack;
};

/*:975*//*980:*/
#line 808 "./dataqsdk.w"

class DataqSdkChannelConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE DataqSdkChannelConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateUnits(const QString&unit);
void updateColumnName(const QString&value);
void updateMeasuredLower(const QString&value);
void updateMeasuredUpper(const QString&value);
void updateMappedLower(const QString&value);
void updateMappedUpper(const QString&value);
void updateClosedInterval(bool closed);
void updateSmoothingEnabled(bool enabled);
void updateSensitivity(const QString&value);
void startCalibration();
void stopCalibration();
void resetCalibration();
void updateInput(Measurement measure);
void updateOutput(Measurement measure);
void updateHidden(bool hidden);
private:
QPushButton*startButton;
QPushButton*resetButton;
QPushButton*stopButton;
/*985:*/
#line 1098 "./dataqsdk.w"

bool autoSelect;
QString deviceID;
unsigned int channelOfInterest;

/*:985*/
#line 835 "./dataqsdk.w"

DataqSdkDevice*calibrationDevice;
LinearCalibrator*calibrator;
QLineEdit*currentMeasurement;
QLineEdit*minimumMeasurement;
QLineEdit*maximumMeasurement;
QLineEdit*averageMeasurement;
QLineEdit*currentMapped;
QLineEdit*minimumMapped;
QLineEdit*maximumMapped;
QLineEdit*averageMapped;
int rmCount;
int cmCount;
double rmin;
double rmax;
double rmean;
double cmin;
double cmax;
double cmean;
};

/*:980*//*1007:*/
#line 247 "./scales.w"

Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(FlowType)

/*:1007*//*1014:*/
#line 370 "./scales.w"

class SerialScaleConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE SerialScaleConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updatePort(const QString&newPort);
void updateBaudRate(const QString&rate);
void updateParity(int index);
void updateFlowControl(int index);
void updateStopBits(int index);
private:
PortSelector*port;
BaudSelector*baud;
ParitySelector*parity;
FlowSelector*flow;
StopSelector*stop;
};

/*:1014*//*1019:*/
#line 14 "./valueannotation.w"

class ValueAnnotationConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ValueAnnotationConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateSourceColumn(const QString&source);
void updateAnnotations();
void updateStart(bool noteOnStart);
private:
SaltModel*tablemodel;
};

/*:1019*//*1027:*/
#line 165 "./valueannotation.w"

class ValueAnnotation:public QObject
{
Q_OBJECT
public:
ValueAnnotation();
Q_INVOKABLE void setAnnotation(double value,const QString&annotation);
public slots:
void newMeasurement(Measurement measure);
void annotate();
void setAnnotationColumn(int column);
void setTemperatureColumn(int column);
void setTolerance(double epsilon);
signals:
void annotation(QString annotation,int tempcolumn,int notecolumn);
private:
int lastIndex;
int annotationColumn;
int measurementColumn;
QList<double> values;
QStringList annotations;
double tolerance;
};

/*:1027*/
#line 526 "./typica.w"

/*12:*/
#line 807 "./typica.w"

void setQObjectProperties(QScriptValue value,QScriptEngine*engine);

/*:12*//*14:*/
#line 822 "./typica.w"

void setQPaintDeviceProperties(QScriptValue value,QScriptEngine*engine);
void setQLayoutItemProperties(QScriptValue value,QScriptEngine*engine);

/*:14*//*16:*/
#line 847 "./typica.w"

void setQWidgetProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQWidget(QScriptContext*context,QScriptEngine*engine);
QScriptValue QWidget_setLayout(QScriptContext*context,QScriptEngine*engine);
QScriptValue QWidget_activateWindow(QScriptContext*context,
QScriptEngine*engine);

/*:16*//*27:*/
#line 1091 "./typica.w"

QScriptValue constructQMainWindow(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QMainWindow_setCentralWidget(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QMainWindow_menuBar(QScriptContext*context,
QScriptEngine*engine);
void setQMainWindowProperties(QScriptValue value,QScriptEngine*engine);

/*:27*//*32:*/
#line 1190 "./typica.w"

void setQMenuBarProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QMenuBar_addMenu(QScriptContext*context,QScriptEngine*engine);

/*:32*//*35:*/
#line 1235 "./typica.w"

void setQMenuProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QMenu_addAction(QScriptContext*context,QScriptEngine*engine);
QScriptValue QMenu_addSeparator(QScriptContext*context,QScriptEngine*engine);

/*:35*//*38:*/
#line 1301 "./typica.w"

void setQFrameProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQFrame(QScriptContext*context,QScriptEngine*engine);

/*:38*//*41:*/
#line 1334 "./typica.w"

void setQLabelProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQLabel(QScriptContext*context,QScriptEngine*engine);

/*:41*//*44:*/
#line 1372 "./typica.w"

void setQLineEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQLineEdit(QScriptContext*context,QScriptEngine*engine);

/*:44*//*48:*/
#line 1411 "./typica.w"

QScriptValue constructQSplitter(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSplitter_addWidget(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_saveState(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_restoreState(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_count(QScriptContext*context,
QScriptEngine*engine);
void setQSplitterProperties(QScriptValue value,QScriptEngine*engine);

/*:48*//*54:*/
#line 1550 "./typica.w"

void setQLayoutProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QLayout_addWidget(QScriptContext*context,QScriptEngine*engine);

/*:54*//*56:*/
#line 1605 "./typica.w"

QScriptValue constructQBoxLayout(QScriptContext*context,
QScriptEngine*engine);
void setQBoxLayoutProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QBoxLayout_addLayout(QScriptContext*context,QScriptEngine*engine);
QScriptValue QBoxLayout_addWidget(QScriptContext*context,QScriptEngine*engine);

/*:56*//*60:*/
#line 1718 "./typica.w"

QScriptValue constructQAction(QScriptContext*context,QScriptEngine*engine);
QScriptValue QAction_setShortcut(QScriptContext*context,
QScriptEngine*engine);
void setQActionProperties(QScriptValue value,QScriptEngine*engine);

/*:60*//*63:*/
#line 1774 "./typica.w"

QScriptValue QFileDialog_getOpenFileName(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QFileDialog_getSaveFileName(QScriptContext*context,
QScriptEngine*engine);
void setQFileDialogProperties(QScriptValue value,QScriptEngine*engine);
void setQDialogProperties(QScriptValue value,QScriptEngine*engine);

/*:63*//*68:*/
#line 1885 "./typica.w"

QScriptValue constructQFile(QScriptContext*context,QScriptEngine*engine);
void setQFileProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QFile_remove(QScriptContext*context,QScriptEngine*engine);
void setQIODeviceProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QIODevice_open(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_close(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_readToString(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QIODevice_putChar(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_writeString(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_writeBytes(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_readBytes(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_peek(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_read(QScriptContext*context,QScriptEngine*engine);

/*:68*//*79:*/
#line 2111 "./typica.w"

QScriptValue constructQProcess(QScriptContext*context,QScriptEngine*engine);
void setQProcessProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QProcess_execute(QScriptContext*context,QScriptEngine*engine);
QScriptValue QProcess_startDetached(QScriptContext*context,QScriptEngine*engine);
QScriptValue QProcess_setWorkingDirectory(QScriptContext*context,QScriptEngine*engine);
QScriptValue QProcess_start(QScriptContext*context,QScriptEngine*engine);

/*:79*//*87:*/
#line 2229 "./typica.w"

QScriptValue QByteArray_toScriptValue(QScriptEngine*engine,const QByteArray&bytes);
void QByteArray_fromScriptValue(const QScriptValue&value,QByteArray&bytes);
QScriptValue constructQByteArray(QScriptContext*context,QScriptEngine*engine);
void setQByteArrayProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QByteArray_fromHex(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_getAt(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_setAt(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_appendBytes(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_appendString(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_size(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_left(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_right(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_mid(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_chop(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_remove(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_toInt8(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_toInt16(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_toInt32(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_toFloat(QScriptContext*context,QScriptEngine*engine);
QScriptValue QByteArray_toDouble(QScriptContext*context,QScriptEngine*engine);

/*:87*//*100:*/
#line 2503 "./typica.w"

QScriptValue bytesFromInt8(QScriptContext*context,QScriptEngine*engine);
QScriptValue bytesFromInt16(QScriptContext*context,QScriptEngine*engine);
QScriptValue bytesFromInt32(QScriptContext*context,QScriptEngine*engine);
QScriptValue bytesFromFloat(QScriptContext*context,QScriptEngine*engine);
QScriptValue bytesFromDouble(QScriptContext*context,QScriptEngine*engine);

/*:100*//*103:*/
#line 2608 "./typica.w"

QScriptValue constructQBuffer(QScriptContext*context,QScriptEngine*engine);
void setQBufferProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QBuffer_setData(QScriptContext*context,QScriptEngine*engine);

/*:103*//*106:*/
#line 2653 "./typica.w"

QScriptValue constructXQuery(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_bind(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_exec(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_setQuery(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_invalidate(QScriptContext*context,QScriptEngine*engine);
void setXQueryProperties(QScriptValue value,QScriptEngine*engine);

/*:106*//*112:*/
#line 2735 "./typica.w"

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

/*:112*//*121:*/
#line 2953 "./typica.w"

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

/*:121*//*128:*/
#line 3088 "./typica.w"

QScriptValue QSettings_value(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSettings_setValue(QScriptContext*context,QScriptEngine*engine);
void setQSettingsProperties(QScriptValue value,QScriptEngine*engine);

/*:128*//*132:*/
#line 3170 "./typica.w"

QScriptValue constructQLCDNumber(QScriptContext*context,
QScriptEngine*engine);
void setQLCDNumberProperties(QScriptValue value,QScriptEngine*engine);

/*:132*//*135:*/
#line 3208 "./typica.w"

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

/*:135*//*151:*/
#line 3686 "./typica.w"

void setQAbstractScrollAreaProperties(QScriptValue value,
QScriptEngine*engine);

/*:151*//*153:*/
#line 3701 "./typica.w"

void setQAbstractItemViewProperties(QScriptValue value,QScriptEngine*engine);

/*:153*//*155:*/
#line 3714 "./typica.w"

void setQGraphicsViewProperties(QScriptValue value,QScriptEngine*engine);
void setQTableViewProperties(QScriptValue value,QScriptEngine*engine);

/*:155*//*157:*/
#line 3738 "./typica.w"

void setQAbstractButtonProperties(QScriptValue value,QScriptEngine*engine);
void setQPushButtonProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQPushButton(QScriptContext*context,
QScriptEngine*engine);

/*:157*//*164:*/
#line 3837 "./typica.w"

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

/*:164*//*171:*/
#line 4008 "./typica.w"

QScriptValue baseName(QScriptContext*context,QScriptEngine*engine);
QScriptValue dir(QScriptContext*context,QScriptEngine*engine);
QScriptValue sqlToArray(QScriptContext*context,QScriptEngine*engine);
QScriptValue setFont(QScriptContext*context,QScriptEngine*engine);
QScriptValue annotationFromRecord(QScriptContext*context,
QScriptEngine*engine);
QScriptValue setTabOrder(QScriptContext*context,QScriptEngine*engine);
QScriptValue saveFileFromDatabase(QScriptContext*context,QScriptEngine*engine);

/*:171*//*183:*/
#line 4321 "./typica.w"

QScriptValue createWindow(QScriptContext*context,QScriptEngine*engine);
QScriptValue createReport(QScriptContext*context,QScriptEngine*engine);
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

/*:183*//*247:*/
#line 5974 "./typica.w"

void setQDateEditProperties(QScriptValue value,QScriptEngine*engine);
void setQDateTimeEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QDateTimeEdit_setDate(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QDateTimeEdit_day(QScriptContext*context,QScriptEngine*engine);
QScriptValue QDateTimeEdit_month(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QDateTimeEdit_year(QScriptContext*context,QScriptEngine*engine);

/*:247*//*248:*/
#line 5989 "./typica.w"

QScriptValue findChildObject(QScriptContext*context,QScriptEngine*engine);

/*:248*//*252:*/
#line 6124 "./typica.w"

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
QScriptValue SaltTable_clear(QScriptContext*context,QScriptEngine*engine);
QScriptValue SaltTable_removeRow(QScriptContext*context,QScriptEngine*engine);
QScriptValue SaltTable_findData(QScriptContext*context,QScriptEngine*engine);

/*:252*//*262:*/
#line 6340 "./typica.w"

void setSqlComboBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQComboBoxProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QComboBox_currentData(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QComboBox_addItem(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_setModel(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_findText(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_findData(QScriptContext*context,QScriptEngine*engine);

/*:262*//*274:*/
#line 379 "./units.w"

QScriptValue Units_convertTemperature(QScriptContext*context,QScriptEngine*engine);
QScriptValue Units_convertRelativeTemperature(QScriptContext*context,
QScriptEngine*engine);
QScriptValue Units_isTemperatureUnit(QScriptContext*context,QScriptEngine*engine);
QScriptValue Units_convertWeight(QScriptContext*context,QScriptEngine*engine);
QScriptValue Units_isWeightUnit(QScriptContext*context,QScriptEngine*engine);

/*:274*//*278:*/
#line 443 "./units.w"

QScriptValue Unit_toScriptValue(QScriptEngine*engine,const Units::Unit&value);
void Unit_fromScriptValue(const QScriptValue&sv,Units::Unit&value);

/*:278*//*287:*/
#line 133 "./measurement.w"

QScriptValue constructMeasurement(QScriptContext*context,QScriptEngine*engine);
void setMeasurementProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue Measurement_toScriptValue(QScriptEngine*engine,const Measurement&measurement);
void Measurement_fromScriptValue(const QScriptValue&value,Measurement&measurement);

/*:287*//*310:*/
#line 7010 "./typica.w"

QScriptValue constructDAQ(QScriptContext*context,QScriptEngine*engine);
QScriptValue DAQ_newChannel(QScriptContext*context,QScriptEngine*engine);
void setDAQProperties(QScriptValue value,QScriptEngine*engine);

/*:310*//*319:*/
#line 7215 "./typica.w"

QScriptValue constructFakeDAQ(QScriptContext*context,QScriptEngine*engine);
QScriptValue FakeDAQ_newChannel(QScriptContext*context,QScriptEngine*engine);
void setFakeDAQProperties(QScriptValue value,QScriptEngine*engine);

/*:319*//*324:*/
#line 7316 "./typica.w"

void setChannelProperties(QScriptValue value,QScriptEngine*engine);

/*:324*//*330:*/
#line 7498 "./typica.w"

QScriptValue constructLinearCalibrator(QScriptContext*context,
QScriptEngine*engine);
void setLinearCalibratorProperties(QScriptValue value,QScriptEngine*engine);

/*:330*//*335:*/
#line 7638 "./typica.w"

QScriptValue constructLinearSplineInterpolator(QScriptContext*context,QScriptEngine*engine);
void setLinearSplineInterpolatorProperties(QScriptValue value,QScriptEngine*engine);

/*:335*//*345:*/
#line 7843 "./typica.w"

QScriptValue constructTemperatureDisplay(QScriptContext*context,
QScriptEngine*engine);
void setTemperatureDisplayProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue TemperatureDisplay_setDisplayUnits(QScriptContext*context,
QScriptEngine*engine);

/*:345*//*353:*/
#line 8002 "./typica.w"

QScriptValue constructMeasurementTimeOffset(QScriptContext*context,
QScriptEngine*engine);
void setMeasurementTimeOffsetProperties(QScriptValue value,
QScriptEngine*engine);

/*:353*//*358:*/
#line 8115 "./typica.w"

QScriptValue constructThresholdDetector(QScriptContext*context,QScriptEngine*engine);
void setThresholdDetectorProperties(QScriptValue value,QScriptEngine*engine);

/*:358*//*363:*/
#line 8213 "./typica.w"

QScriptValue constructZeroEmitter(QScriptContext*context,
QScriptEngine*engine);
void setZeroEmitterProperties(QScriptValue value,QScriptEngine*engine);

/*:363*//*368:*/
#line 8292 "./typica.w"

QScriptValue constructMeasurementAdapter(QScriptContext*context,
QScriptEngine*engine);
void setMeasurementAdapterProperties(QScriptValue value,QScriptEngine*engine);

/*:368*//*385:*/
#line 8756 "./typica.w"

void setGraphViewProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructGraphView(QScriptContext*context,QScriptEngine*engine);

/*:385*//*408:*/
#line 9383 "./typica.w"

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
QScriptValue ZoomLog_setDisplayUnits(QScriptContext*context,
QScriptEngine*engine);

/*:408*//*446:*/
#line 10340 "./typica.w"

QScriptValue constructAnnotationButton(QScriptContext*context,
QScriptEngine*engine);
void setAnnotationButtonProperties(QScriptValue value,QScriptEngine*engine);

/*:446*//*454:*/
#line 10480 "./typica.w"

QScriptValue constructAnnotationSpinBox(QScriptContext*context,
QScriptEngine*engine);
void setAnnotationSpinBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQDoubleSpinBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQAbstractSpinBoxProperties(QScriptValue value,QScriptEngine*engine);

/*:454*//*475:*/
#line 10906 "./typica.w"

QScriptValue constructTimerDisplay(QScriptContext*context,
QScriptEngine*engine);
void setTimerDisplayProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue TimerDisplay_setTimerMode(QScriptContext*context,QScriptEngine*engine);

/*:475*//*503:*/
#line 11431 "./typica.w"

void setWidgetDecoratorProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructWidgetDecorator(QScriptContext*context,
QScriptEngine*engine);

/*:503*//*516:*/
#line 11714 "./typica.w"

QScriptValue constructLogEditWindow(QScriptContext*context,
QScriptEngine*engine);

/*:516*//*535:*/
#line 12241 "./typica.w"

QScriptValue constructXMLInput(QScriptContext*context,QScriptEngine*engine);
QScriptValue XMLInput_input(QScriptContext*context,QScriptEngine*engine);

/*:535*//*553:*/
#line 189 "./webview.w"

QScriptValue constructWebView(QScriptContext*context,QScriptEngine*engine);
void setQWebViewProperties(QScriptValue value,QScriptEngine*engine);
void addWebViewToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:553*//*556:*/
#line 219 "./webview.w"

QScriptValue QWebElement_toScriptValue(QScriptEngine*engine,const QWebElement&element);
void QWebElement_fromScriptValue(const QScriptValue&value,QWebElement&element);

/*:556*//*560:*/
#line 277 "./webview.w"

QScriptValue constructWebElement(QScriptContext*context,
QScriptEngine*engine);

/*:560*//*629:*/
#line 13581 "./typica.w"

void setSqlQueryViewProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructSqlQueryView(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SqlQueryView_setQuery(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SqlQueryView_setHeaderData(QScriptContext*context,
QScriptEngine*engine);

/*:629*//*639:*/
#line 13818 "./typica.w"

void addReportToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:639*//*655:*/
#line 14103 "./typica.w"

void setQTextEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QTextEdit_print(QScriptContext*context,QScriptEngine*engine);

/*:655*//*677:*/
#line 480 "./daterangeselector.w"

void addDateRangeToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:677*//*686:*/
#line 14300 "./typica.w"

void addFormArrayToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:686*//*707:*/
#line 14884 "./typica.w"

void addScaleControlToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addIntensityControlToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:707*//*733:*/
#line 15470 "./typica.w"

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

/*:733*//*739:*/
#line 15612 "./typica.w"

QScriptValue QModelIndex_toScriptValue(QScriptEngine*engine,const QModelIndex&index);
void QModelIndex_fromScriptValue(const QScriptValue&value,QModelIndex&index);

/*:739*//*755:*/
#line 15910 "./typica.w"

QScriptValue constructDeviceConfigurationWindow(QScriptContext*context,
QScriptEngine*engine);

/*:755*//*826:*/
#line 42 "./settings.w"

QScriptValue constructSettingsWindow(QScriptContext*context,QScriptEngine*engine);

/*:826*//*850:*/
#line 18498 "./typica.w"

QScriptValue constructModbusRTUDevice(QScriptContext*context,QScriptEngine*engine);
QScriptValue ModbusRTUDevice_pVChannel(QScriptContext*context,QScriptEngine*engine);
QScriptValue ModbusRTUDevice_sVChannel(QScriptContext*context,QScriptEngine*engine);
void setModbusRTUDeviceProperties(QScriptValue value,QScriptEngine*engine);

/*:850*//*870:*/
#line 345 "./unsupportedserial.w"

QScriptValue createDevice(QScriptContext*context,QScriptEngine*engine);

/*:870*//*876:*/
#line 425 "./unsupportedserial.w"

QScriptValue JavaScriptDevice_getChannel(QScriptContext*context,QScriptEngine*engine);

/*:876*//*882:*/
#line 617 "./unsupportedserial.w"

QScriptValue getMeasurementTimestamp(QScriptContext*context,QScriptEngine*engine);

/*:882*//*886:*/
#line 651 "./unsupportedserial.w"

QScriptValue constructSerialPort(QScriptContext*context,QScriptEngine*engine);
void setSerialPortProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue SerialPort_flush(QScriptContext*context,QScriptEngine*engine);

/*:886*//*913:*/
#line 457 "./phidgets.w"

QScriptValue constructPhidgetsTemperatureSensor(QScriptContext*context,QScriptEngine*engine);
QScriptValue Phidgets_getChannel(QScriptContext*context,QScriptEngine*engine);

/*:913*//*945:*/
#line 138 "./rate.w"

QScriptValue constructRateOfChange(QScriptContext*context,QScriptEngine*engine);
void setRateOfChangeProperties(QScriptValue value,QScriptEngine*engine);

/*:945*//*970:*/
#line 597 "./dataqsdk.w"

QScriptValue constructDataqSdkDevice(QScriptContext*context,QScriptEngine*engine);
QScriptValue DataqSdkDevice_newChannel(QScriptContext*context,QScriptEngine*engine);
void setDataqSdkDeviceProperties(QScriptValue value,QScriptEngine*engine);

/*:970*//*997:*/
#line 67 "./scales.w"

QScriptValue constructDragLabel(QScriptContext*context,QScriptEngine*engine);
void setDragLabelProperties(QScriptValue value,QScriptEngine*engine);

/*:997*//*1005:*/
#line 233 "./scales.w"

QScriptValue constructSerialScale(QScriptContext*context,QScriptEngine*engine);
void setSerialScaleProperties(QScriptValue value,QScriptEngine*engine);

/*:1005*//*1008:*/
#line 258 "./scales.w"

QScriptValue BaudRateType_toScriptValue(QScriptEngine*engine,const BaudRateType&value);
void BaudRateType_fromScriptValue(const QScriptValue&sv,BaudRateType&value);
QScriptValue DataBitsType_toScriptValue(QScriptEngine*engine,const DataBitsType&value);
void DataBitsType_fromScriptValue(const QScriptValue&sv,DataBitsType&value);
QScriptValue ParityType_toScriptValue(QScriptEngine*engine,const ParityType&value);
void ParityType_fromScriptValue(const QScriptValue&sv,ParityType&value);
QScriptValue StopBitsType_toScriptValue(QScriptEngine*engine,const StopBitsType&value);
void StopBitsType_fromScriptValue(const QScriptValue&sv,StopBitsType&value);
QScriptValue FlowType_toScriptValue(QScriptEngine*engine,const FlowType&value);
void FlowType_fromScriptValue(const QScriptValue&sv,FlowType&value);

/*:1008*//*1033:*/
#line 265 "./valueannotation.w"

QScriptValue constructValueAnnotation(QScriptContext*context,QScriptEngine*engine);
void setValueAnnotationProperties(QScriptValue value,QScriptEngine*engine);

/*:1033*/
#line 527 "./typica.w"

/*609:*/
#line 13238 "./typica.w"

void messageFileOutput(QtMsgType type,const char*msg);

/*:609*/
#line 528 "./typica.w"

/*4:*/
#line 537 "./typica.w"

/*747:*/
#line 15733 "./typica.w"

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

/*:747*/
#line 538 "./typica.w"

/*283:*/
#line 40 "./measurement.w"

Measurement::Measurement(double temperature,QTime time,Units::Unit sc)
{
insert("measurement",temperature);
insert("time",time);
insert("unit",sc);
}

Measurement::Measurement(double temperature)
{
insert("measurement",temperature);
insert("time",QTime::currentTime());
insert("unit",Units::Fahrenheit);
}

void Measurement::setTemperature(double temperature)
{
insert("measurement",temperature);
}

void Measurement::setTime(QTime time)
{
insert("time",time);
}

void Measurement::setUnit(Units::Unit scale)
{
insert("unit",scale);
}

double Measurement::temperature()const
{
return value("measurement").toDouble();
}

QTime Measurement::time()const
{
return value("time").toTime();
}

Units::Unit Measurement::scale()const
{
return(Units::Unit)(value("unit").toInt());
}

/*:283*//*284:*/
#line 88 "./measurement.w"

Measurement Measurement::toFahrenheit()
{
return Measurement(Units::convertTemperature(this->temperature(),
this->scale(),Units::Fahrenheit),
this->time(),Units::Fahrenheit);
}

Measurement Measurement::toCelsius()
{
return Measurement(Units::convertTemperature(this->temperature(),
this->scale(),Units::Celsius),
this->time(),Units::Celsius);
}

Measurement Measurement::toKelvin()
{
return Measurement(Units::convertTemperature(this->temperature(),
this->scale(),Units::Kelvin),
this->time(),Units::Kelvin);
}

Measurement Measurement::toRankine()
{
return Measurement(Units::convertTemperature(this->temperature(),
this->scale(),Units::Rankine),
this->time(),Units::Rankine);
}

/*:284*/
#line 539 "./typica.w"

/*298:*/
#line 6597 "./typica.w"

bool DAQImplementation::measure()
{
int samplesRead= 0;
double buffer[channels];
error= read((unsigned int)(handle),(signed long)(1),(double)(10.0),
(unsigned long)(0),buffer,(unsigned long)(channels),
&samplesRead,(signed long)(0));
if(error)
{
ready= false;
return false;
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
double measuredValue= buffer[j+(i*channels)];
Measurement measure(measuredValue,time,unitMap[j]);
channelMap[j]->input(measure);
}
}
}
}
return true;
}

/*:298*//*299:*/
#line 6644 "./typica.w"

void DAQImplementation::run()
{
setPriority(QThread::TimeCriticalPriority);
/*300:*/
#line 6660 "./typica.w"

retry:
error= createTask(device.toAscii().data(),&handle);
if(error)
{
clearTask(handle);
goto retry;
}
NiChannelSpec*currentChannel;
foreach(currentChannel,channelSpecs)
{
if(useBase)
{
error= createChannel(handle,currentChannel.channelName,"",
(double)(-1.0),(double)(100.0),
currentChannel.units,
currentChannel.thermocouple,
(signed long)(10200),(double)(0),"");
}
else
{
error= createChannel(handle,currentChannel.channelName,"",
(double)(50.0),(double)(500.0),
currentChannel.units,
currentChannel.thermocouple,
(signed long)(10200),(double)(0),"");
}
if(error)
{
clearTask(handle);
goto retry;
}
}
if(clockRateSet)
{
error= setClock(handle,"OnboardClock",clockRate,
(signed long)(10280),(unsigned long long)(1));
if(error)
{
clearTask(handle);
goto retry;
}
}
error= startTask(handle);
if(error)
{
clearTask(handle);
goto retry;
}
ready= true;

/*:300*/
#line 6648 "./typica.w"

while(ready)
{
if(!measure())
{
/*301:*/
#line 6714 "./typica.w"

stopTask(handle);
resetDevice(device.toAscii().data());
clearTask(handle);
/*300:*/
#line 6660 "./typica.w"

retry:
error= createTask(device.toAscii().data(),&handle);
if(error)
{
clearTask(handle);
goto retry;
}
NiChannelSpec*currentChannel;
foreach(currentChannel,channelSpecs)
{
if(useBase)
{
error= createChannel(handle,currentChannel.channelName,"",
(double)(-1.0),(double)(100.0),
currentChannel.units,
currentChannel.thermocouple,
(signed long)(10200),(double)(0),"");
}
else
{
error= createChannel(handle,currentChannel.channelName,"",
(double)(50.0),(double)(500.0),
currentChannel.units,
currentChannel.thermocouple,
(signed long)(10200),(double)(0),"");
}
if(error)
{
clearTask(handle);
goto retry;
}
}
if(clockRateSet)
{
error= setClock(handle,"OnboardClock",clockRate,
(signed long)(10280),(unsigned long long)(1));
if(error)
{
clearTask(handle);
goto retry;
}
}
error= startTask(handle);
if(error)
{
clearTask(handle);
goto retry;
}
ready= true;

/*:300*/
#line 6718 "./typica.w"
;

/*:301*/
#line 6653 "./typica.w"

}
}
}

/*:299*//*302:*/
#line 6726 "./typica.w"

void DAQ::threadFinished()
{
if(imp->error)
{
/*303:*/
#line 6777 "./typica.w"

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

/*:303*/
#line 6731 "./typica.w"

}
}

/*:302*//*304:*/
#line 6802 "./typica.w"

void DAQ::start()
{
connect(imp,SIGNAL(finished()),this,SLOT(threadFinished()));
imp->start();
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
/*303:*/
#line 6777 "./typica.w"

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

/*:303*/
#line 6823 "./typica.w"

}
imp->error= imp->clearTask(imp->handle);
if(imp->error)
{
/*303:*/
#line 6777 "./typica.w"

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

/*:303*/
#line 6828 "./typica.w"

}
}
}

/*:304*//*305:*/
#line 6838 "./typica.w"

DAQ::DAQ(QString device,const QString&driver):imp(new DAQImplementation(driver))
{
imp->device= device;
}

/*:305*//*306:*/
#line 6850 "./typica.w"

Channel*DAQ::newChannel(int units,int thermocouple)
{
Channel*retval= new Channel();
imp->channelMap[imp->channels]= retval;
imp->unitMap[imp->channels]= (Units::Unit)units;
NiChannelSpec*channelSpec= new NiChannelSpec;
channelSpec.channelName= QString("%1/ai%2").arg(imp->device).
arg(imp->channels).
toAscii().data();
channelSpec.units= (signed long)(units);
channelSpec.thermocouple= (signed long)(thermocouple);
imp->channelSpecs.append(channelSpec);
imp->channels++;
return retval;
}

/*:306*//*307:*/
#line 6875 "./typica.w"

void DAQ::setClockRate(double Hz)
{
imp->clockRateSet= true;
imp->clockRate= Hz;
}

/*:307*//*308:*/
#line 6887 "./typica.w"

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

/*:308*//*309:*/
#line 6918 "./typica.w"

DAQImplementation::DAQImplementation(const QString&driverinfo)
:QThread(NULL),channelMap(4),handle(0),error(0),channels(0),ready(false),
clockRateSet(false),clockRate(0.0),unitMap(4)
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

/*:309*/
#line 540 "./typica.w"

/*959:*/
#line 197 "./dataqsdk.w"

void DataqSdkDeviceImplementation::measure()
{
unsigned count= channels*40;
di_status_read(buffer,count);
QTime time= QTime::currentTime();
for(unsigned int i= 0;i<count;i++)
{
buffer[i]= buffer[i]&0xFFFC;
}
QList<int> countList;
for(unsigned int i= 0;i<(unsigned)channels;i++)
{
QList<double> channelBuffer;
for(unsigned int j= 0;j<40;j++)
{
channelBuffer<<((double)buffer[i+(channels*j)]*10.0)/32768.0;
if(i==0)
{
countList<<buffer[i+(channels*j)];
}
}
double value= 0.0;
for(unsigned int j= 0;j<40;j++)
{
value+= channelBuffer[j];
}
value/= 40.0;
if(i==0)
{
QList<double> smoothingList;
smoothingList<<value;
QList<int> smoothingKeys= smoother.uniqueKeys();
for(int j= 0;j<smoothingKeys.size();j++)
{
if(countList.contains(smoothingKeys[j]))
{
QList<double> keyValues= smoother.values(smoothingKeys[j]);
for(int k= 0;k<keyValues.size();k++)
{
smoothingList<<keyValues[k];
}
}
else
{
smoother.remove(smoothingKeys[j]);
}
}
qSort(countList);
int lastCount= 0;
for(int j= 0;j<countList.size();j++)
{
if(j==0||countList[j]!=lastCount)
{
smoother.insert(countList[j],value);
lastCount= countList[j];
}
}
value= 0.0;
for(int j= 0;j<smoothingList.size();j++)
{
value+= smoothingList[j];
}
value/= smoothingList.size();
}
Measurement measure(value,time,unitMap[i]);
channelMap[i]->input(measure);
}
}

/*:959*//*960:*/
#line 290 "./dataqsdk.w"

void DataqSdkDeviceImplementation::run()
{
if(!ready)
{
error= 9;
return;
}
driver= new QLibrary(device);
if(!driver->load())
{
error= 1;
qDebug()<<"Failed to load driver: "<<device;
return;
}
di_open= (FPDIOPEN)driver->resolve("di_open");
di_close= (FPDICLOSE)driver->resolve("di_close");
di_sample_rate= (FPDISAMPLERATE)driver->resolve("di_sample_rate");
di_maximum_rate= (FPDIMAXIMUMRATE)driver->resolve("di_maximum_rate");
di_list_length= (FPDILISTLENGTH)driver->resolve("di_list_length");
di_inlist= (FPDIINLIST)driver->resolve("di_inlist");
di_buffer_alloc= (FPDIBUFFERALLOC)driver->resolve("di_buffer_alloc");
di_start_scan= (FPDISTARTSCAN)driver->resolve("di_start_scan");
di_status_read= (FPDISTATUSREAD)driver->resolve("di_status_read");
di_buffer_status= (FPDIBUFFERSTATUS)driver->resolve("di_buffer_status");
di_burst_rate= (FPDIBURSTRATE)driver->resolve("di_burst_rate");
di_stop_scan= (FPDISTOPSCAN)driver->resolve("di_stop_scan");
if((!di_open)||(!di_close)||(!di_sample_rate)||(!di_maximum_rate)||
(!di_list_length)||(!di_inlist)||(!di_buffer_alloc)||
(!di_start_scan)||(!di_status_read)||(!di_buffer_status)||
(!di_burst_rate)||(!di_stop_scan))
{
error= 2;
return;
}
error= di_open(deviceNumber);
if(error)
{
di_close();
error= di_open(deviceNumber);
if(error)
{
error= 3;
di_close();
return;
}
}
isOpen= true;
di_maximum_rate(240.0);
sampleRate= di_sample_rate(sampleRate*channels*40,&oversample,
&burstDivisor);
buffer= new qint16[(int)sampleRate];
di_inlist_struct inlist[16]= {{0,0,0,0,0,0,0,0}};
for(unsigned short i= 0;i<channels;i++)
{
inlist[i].chan= i;
inlist[i].gain= 0;
inlist[i].ave= 1;
inlist[i].counter= (oversample-1);
}
error= di_list_length(channels,0);
if(error)
{
error= 4;
return;
}
error= di_inlist(inlist);
if(error)
{
error= 5;
return;
}
input_buffer= di_buffer_alloc(0,4096);
if(input_buffer==NULL)
{
error= 6;
return;
}
error= di_start_scan();
if(error)
{
error= 7;
return;
}
while(ready)
{
measure();
}
}

/*:960*//*961:*/
#line 386 "./dataqsdk.w"

void DataqSdkDevice::threadFinished()
{
if(imp->error)
{
/*962:*/
#line 400 "./dataqsdk.w"

imp->ready= false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
warning.setInformativeText(tr("An error occurred"));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

/*:962*/
#line 391 "./dataqsdk.w"

}
}

/*:961*//*963:*/
#line 417 "./dataqsdk.w"

void DataqSdkDevice::start()
{
connect(imp,SIGNAL(finished()),this,SLOT(threadFinished()));
imp->start();
}

/*:963*//*964:*/
#line 428 "./dataqsdk.w"

QStringList DataqSdkDevice::detectHardware()
{
QSettings deviceLookup("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\usbser\\Enum",
QSettings::NativeFormat);
QStringList keys= deviceLookup.childKeys();
QStringList devices;
for(int i= 0;i<keys.size();i++)
{
QString value= deviceLookup.value(keys.at(i)).toString();
if(value.startsWith("USB\\VID_0683&PID_1450\\"))
{
devices.append(value.split("\\").at(2));
}
}
QStringList portList;
foreach(QString device,devices)
{
QString deviceKey= QString("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_0683&PID_1450\\%1").arg(device);
QSettings deviceEntry(deviceKey,QSettings::NativeFormat);
portList.append(deviceEntry.value("FriendlyName").toString());
}
return portList;
}

QStringList DataqSdkDevice::detectPorts()
{
QStringList friendlyNames= detectHardware();
QStringList portList;
foreach(QString name,friendlyNames)
{
name.remove(0,name.indexOf("COM"));
name.chop(1);
portList.append(name);
}
return portList;
}

/*:964*//*965:*/
#line 473 "./dataqsdk.w"

DataqSdkDevice::DataqSdkDevice(QString device):imp(new DataqSdkDeviceImplementation)
{
bool usesAuto= false;
int autoIndex= device.toInt(&usesAuto);
QString finalizedPort;
if(usesAuto)
{
QStringList portList= detectPorts();
if(autoIndex> 0&&autoIndex<=portList.size())
{
finalizedPort= portList.at(autoIndex-1);
}
else
{
imp->error= 8;
qDebug()<<"Failed to detect port.";
}
}
else
{
finalizedPort= device;
}
int rstart= finalizedPort.indexOf("COM");
finalizedPort.remove(0,rstart+3);
bool chopFinished= false;
int finalizedPortNumber= 0;
while(finalizedPort.size()> 0&&!chopFinished)
{
finalizedPortNumber= finalizedPort.toInt(&chopFinished);
if(!chopFinished)
{
finalizedPort.chop(1);
}
}
if(finalizedPortNumber<10)
{
imp->device= QString("DI10%1NT.DLL").arg(finalizedPort);
}
else
{
imp->device= QString("DI1%1NT.DLL").arg(finalizedPort);
}
imp->deviceNumber= 0x12C02D00;
imp->deviceNumber+= finalizedPortNumber;
imp->ready= true;
}

/*:965*//*966:*/
#line 523 "./dataqsdk.w"

Channel*DataqSdkDevice::newChannel(Units::Unit scale)
{
Channel*retval= NULL;
if(imp->ready)
{
retval= new Channel();
imp->channelMap[imp->channels]= retval;
imp->unitMap[imp->channels]= scale;
imp->channels++;
}
return retval;
}

/*:966*//*967:*/
#line 547 "./dataqsdk.w"

void DataqSdkDevice::setClockRate(double Hz)
{
imp->sampleRate= Hz;
}

/*:967*//*968:*/
#line 557 "./dataqsdk.w"

DataqSdkDevice::~DataqSdkDevice()
{
if(imp->ready)
{
imp->ready= false;
}
imp->wait(ULONG_MAX);
delete imp;
}

/*:968*//*969:*/
#line 575 "./dataqsdk.w"

DataqSdkDeviceImplementation::DataqSdkDeviceImplementation():QThread(NULL),
channelMap(4),error(0),channels(0),ready(false),unitMap(4)
{

}

DataqSdkDeviceImplementation::~DataqSdkDeviceImplementation()
{
if(isOpen)
{
di_stop_scan();
di_close();
}
if(driver->isLoaded())
{
driver->unload();
}
}

/*:969*/
#line 541 "./typica.w"

/*316:*/
#line 7127 "./typica.w"

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

/*:316*//*317:*/
#line 7141 "./typica.w"

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

/*:317*//*318:*/
#line 7166 "./typica.w"

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

/*:318*/
#line 542 "./typica.w"

/*323:*/
#line 7297 "./typica.w"

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

/*:323*/
#line 543 "./typica.w"

/*339:*/
#line 7702 "./typica.w"

void TemperatureDisplay::setRelativeMode(bool relative)
{
r= relative;
}

/*:339*//*340:*/
#line 7719 "./typica.w"

void TemperatureDisplay::setValue(Measurement temperature)
{
QString number;
switch(unit)
{
case Units::Fahrenheit:
display(QString("%1'F").
arg(number.setNum(temperature.toFahrenheit().temperature(),'f',
2)));
break;
case Units::Celsius:
if(!r){
display(QString("%1'C").
arg(number.setNum(temperature.toCelsius().temperature(),'f',
2)));
}else{
number.setNum(temperature.temperature()*(5.0/9.0),'f',2);
display(QString("%1'C").arg(number));
}
break;
case Units::Kelvin:
if(!r){
display(QString("%1").
arg(number.setNum(temperature.toKelvin().temperature(),'f',
2)));
}else{
number.setNum(temperature.temperature()*(5.0/9.0),'f',2);
display(QString("%1").arg(number));
}
break;
case Units::Rankine:
display(QString("%1'r").
arg(number.setNum(temperature.toRankine().temperature(),'f',
2)));
break;
case Units::Unitless:
display(QString("%1").arg(number.setNum(temperature.temperature(),'f',0)));
break;
default:
switch(temperature.scale())
{
case Units::Fahrenheit:
display(QString("%1'F").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Units::Celsius:
display(QString("%1'C").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Units::Kelvin:
display(QString("%1").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Units::Rankine:
display(QString("%1'r").
arg(number.setNum(temperature.temperature(),'f',2)));
break;
case Units::Unitless:
display(QString("%1").arg(number.setNum(temperature.temperature(),'f',0)));
break;
default:
qDebug()<<"Warning: Attempting to convert a non-temperature unit to a temperature unit";
break;
}
break;
}
}

/*:340*//*341:*/
#line 7798 "./typica.w"

TemperatureDisplay::TemperatureDisplay(QWidget*parent):
QLCDNumber(8,parent),unit(Units::Fahrenheit),r(false)
{
setSegmentStyle(Filled);
display("---.--'F");
}

/*:341*//*342:*/
#line 7814 "./typica.w"

void TemperatureDisplay::invalidate()
{
display("---.--'F");
}

/*:342*//*343:*/
#line 7826 "./typica.w"

void TemperatureDisplay::setDisplayUnits(Units::Unit scale)
{
unit= scale;
}

/*:343*//*344:*/
#line 7834 "./typica.w"

TemperatureDisplay::~TemperatureDisplay()
{

}

/*:344*/
#line 544 "./typica.w"

/*350:*/
#line 7934 "./typica.w"

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
/*351:*/
#line 7968 "./typica.w"

QTime newTime(0,0,0,0);
newTime= newTime.addMSecs(relTime);
if(newTime.hour()> 0)
{
newTime.setHMS(0,newTime.minute(),newTime.second(),newTime.msec());
}
Measurement rel= measure;
rel.setTime(newTime);
emit measurement(rel);

/*:351*/
#line 7946 "./typica.w"

}
else
{
Measurement rel= measure;
rel.setTime(QTime(0,0,0,0));
emit measurement(rel);
}
}
else
{
int relTime= epoch.msecsTo(measure.time());
/*351:*/
#line 7968 "./typica.w"

QTime newTime(0,0,0,0);
newTime= newTime.addMSecs(relTime);
if(newTime.hour()> 0)
{
newTime.setHMS(0,newTime.minute(),newTime.second(),newTime.msec());
}
Measurement rel= measure;
rel.setTime(newTime);
emit measurement(rel);

/*:351*/
#line 7958 "./typica.w"

}
hasPrevious= true;
previous= measure.time();
}

/*:350*//*352:*/
#line 7981 "./typica.w"

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

/*:352*/
#line 545 "./typica.w"

/*362:*/
#line 8179 "./typica.w"

ZeroEmitter::ZeroEmitter(int tempcolumn):QObject(NULL),col(tempcolumn)
{

}

int ZeroEmitter::column()
{
return col;
}

double ZeroEmitter::lastTemperature()
{
return cache.temperature();
}

void ZeroEmitter::newMeasurement(Measurement measure)
{
cache= measure;
}

void ZeroEmitter::setColumn(int column)
{
col= column;
}

void ZeroEmitter::emitZero()
{
cache.setTime(QTime(0,0,0,0));
emit measurement(cache,col);
}

/*:362*/
#line 546 "./typica.w"

/*367:*/
#line 8269 "./typica.w"

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

/*:367*/
#line 547 "./typica.w"

/*372:*/
#line 8391 "./typica.w"

GraphView::GraphView(QWidget*parent):QGraphicsView(parent),
theScene(new QGraphicsScene),
graphLines(new QMap<int,QList<QGraphicsLineItem*> *> ),
prevPoints(new QMap<int,QPointF> ),
translations(new QMap<int,double> ),
gridLinesF(new QList<QGraphicsItem*> ),
gridLinesC(new QList<QGraphicsItem*> ),
relativeGridLines(new QList<QGraphicsItem*> ),
relativeEnabled(false),
timeIndicatorEnabled(false),
timeLine(new QGraphicsLineItem),
relativeAdjuster(new LinearSplineInterpolator)
{
setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setScene(theScene);
setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
QPen timePen;
timePen.setColor(QColor(160,160,164,127));
timeLine->setPen(timePen);
timeLine->setLine(0,0,0,-500);
timeLine->hide();
theScene->addItem(timeLine);
/*373:*/
#line 8431 "./typica.w"

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

/*:373*/
#line 8415 "./typica.w"
;
/*374:*/
#line 8472 "./typica.w"

QSettings settings;
if(settings.contains("settings/graph/relative/enable"))
{
if(settings.value("settings/graph/relative/enable").toBool())
{
relativeEnabled= true;
QColor relativeColor= QColor(settings.value("settings/graph/relative/color").toString());
QString unit= QString(settings.value("settings/graph/relative/unit").toInt()==0?"F":"C");
QMap<double,QString> relativeAxisPairs;
QStringList relativeAxisLabels= settings.value("settings/graph/relative/grid").toString().split(QRegExp("[\\s,]+"),QString::SkipEmptyParts);
foreach(QString item,relativeAxisLabels)
{
relativeAxisPairs.insert(item.toDouble(),item);
}
if(relativeAxisPairs.size()> 1)
{
double skip= 500.0/(relativeAxisPairs.size()-1);
double y= 0;
foreach(double key,relativeAxisPairs.keys())
{
gridLine= new QGraphicsLineItem;
gridLine->setLine(0,y,1205,y);
gridLine->setPen(QPen(relativeColor));
theScene->addItem(gridLine);
relativeGridLines->append(gridLine);
label= new QGraphicsTextItem;
label->setHtml(QString("%1&deg;%2").arg(relativeAxisPairs.value(key)).arg(unit));
label->setPos(1210,y-(label->boundingRect().height()/2));
theScene->addItem(label);
relativeGridLines->append(label);
if(unit=="F")
{
relativeAdjuster->add_pair(key,-y);
}
else
{
relativeAdjuster->add_pair(key*(9.0/5.0),-y);
}
y-= skip;
}
}
}
}

/*:374*/
#line 8416 "./typica.w"

/*376:*/
#line 8549 "./typica.w"

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

/*:376*/
#line 8417 "./typica.w"
;
fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

/*:372*//*375:*/
#line 8519 "./typica.w"

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

/*:375*//*377:*/
#line 8568 "./typica.w"

void GraphView::resizeEvent(QResizeEvent*)
{
fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

/*:377*//*378:*/
#line 8582 "./typica.w"

#define FULLTIMETOINT(t) (t.msec() + (t.second() * 1000) +  (t.minute() * 60 * 1000))

void GraphView::newMeasurement(Measurement measure,int tempcolumn)
{
double offset= 0;
if(measure.contains("relative"))
{
if(measure.value("relative").toBool())
{
if(relativeEnabled)
{
measure.setTemperature(relativeAdjuster->newMeasurement(measure).temperature());
}
else
{
return;
}
}
}
if(translations->contains(tempcolumn))
{
offset= translations->value(tempcolumn);
}
if(prevPoints->contains(tempcolumn))
{
/*380:*/
#line 8659 "./typica.w"

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
if(timeIndicatorEnabled)
{
timeLine->setLine(nextPoint.x()+offset,0,nextPoint.x()+offset,-500);
}

/*:380*/
#line 8608 "./typica.w"

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
/*379:*/
#line 8644 "./typica.w"

int x= FULLTIMETOINT(measure.time())/1000;
prevPoints->insert(tempcolumn,QPointF(x,measure.temperature()));
if(timeIndicatorEnabled)
{
timeLine->setLine(x,0,x,-500);
}

/*:379*/
#line 8625 "./typica.w"

}
}

/*:378*//*381:*/
#line 8680 "./typica.w"

void GraphView::clear()
{
int i;
foreach(i,prevPoints->keys())
{
removeSeries(i);
}
translations->clear();
}

/*:381*//*382:*/
#line 8694 "./typica.w"

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

/*:382*//*383:*/
#line 8713 "./typica.w"

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

/*:383*//*384:*/
#line 8740 "./typica.w"

void GraphView::setTimeIndicatorEnabled(bool enabled)
{
timeIndicatorEnabled= enabled;
if(enabled)
{
timeLine->show();
}
else
{
timeLine->hide();
}
}

/*:384*/
#line 548 "./typica.w"

/*390:*/
#line 8884 "./typica.w"

void ZoomLog::newMeasurement(Measurement measure,int tempcolumn)
{
if(measure.time()!=QTime(0,0,0,0))
{
/*392:*/
#line 8958 "./typica.w"

if(lastMeasurement.contains(tempcolumn))
{
if(lastMeasurement[tempcolumn].time()<measure.time())
{
QList<QTime> timelist;
for(QTime i= lastMeasurement.value(tempcolumn).time().addSecs(1);i<measure.time();i= i.addSecs(1))
{
timelist.append(i);
}
for(int i= 0;i<timelist.size();i++)
{
Measurement synthesized= measure;
synthesized.setTime(timelist[i]);
newMeasurement(synthesized,tempcolumn);
}
}
}

/*:392*/
#line 8889 "./typica.w"

}
model_ms->newMeasurement(measure,tempcolumn);
if(lastMeasurement.contains(tempcolumn))
{
if(measure.time().second()!=
lastMeasurement.value(tempcolumn).time().second())
{
Measurement adjusted= measure;
QTime adjtime(0,measure.time().minute(),measure.time().second(),0);
adjusted.setTime(adjtime);
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
/*394:*/
#line 9002 "./typica.w"

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
Measurement synthetic= lastMeasurement.value(replicationcolumn);
synthetic.setTime(measure.time());
model_ms->newMeasurement(synthetic,replicationcolumn);
if(synthetic.time().second()!=lastMeasurement.value(replicationcolumn).time().second())
{
Measurement adjusted= synthetic;
adjusted.setTime(QTime(0,synthetic.time().minute(),synthetic.time().second(),0));
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

/*:394*/
#line 8922 "./typica.w"

}
else
{
/*391:*/
#line 8934 "./typica.w"

MeasurementModel*m;
foreach(m,modelSet)
{
m->newMeasurement(measure,tempcolumn);
}

/*:391*/
#line 8926 "./typica.w"

}
lastMeasurement.insert(tempcolumn,measure);
}

/*:390*//*393:*/
#line 8988 "./typica.w"

void ZoomLog::addToCurrentColumnSet(int column)
{
currentColumnSet.append(column);
}

void ZoomLog::clearCurrentColumnSet()
{
currentColumnSet.clear();
}

/*:393*//*395:*/
#line 9072 "./typica.w"

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

/*:395*//*396:*/
#line 9096 "./typica.w"

void ZoomLog::centerOn(int row)
{
scrollTo(currentModel->index(row,0),QAbstractItemView::PositionAtCenter);
}

/*:396*//*397:*/
#line 9106 "./typica.w"

void ZoomLog::clear()
{
MeasurementModel*m;
foreach(m,modelSet)
{
m->clear();
}
lastMeasurement.clear();
saveTempCols.clear();
saveControlCols.clear();
saveNoteCols.clear();
}

/*:397*//*398:*/
#line 9124 "./typica.w"

QVariant ZoomLog::data(int row,int column)const
{
return model_ms->data(model_ms->index(row,column,QModelIndex()),
Qt::DisplayRole);
}

int ZoomLog::rowCount()
{
return model_ms->rowCount();
}

/*:398*//*399:*/
#line 9147 "./typica.w"

bool ZoomLog::saveXML(QIODevice*device)
{
Units::Unit prevUnits= model_ms->displayUnits();
if(prevUnits!=Units::Fahrenheit)
{
model_ms->setDisplayUnits(Units::Fahrenheit);
}
XMLOutput writer(model_ms,device,0);
int c;
foreach(c,saveTempCols)
{
writer.addTemperatureColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
foreach(c,saveControlCols)
{
writer.addControlColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
foreach(c,saveNoteCols)
{
writer.addAnnotationColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
bool retval= writer.output();
if(prevUnits!=Units::Fahrenheit)
{
model_ms->setDisplayUnits(prevUnits);
}
return retval;
}

/*:399*//*400:*/
#line 9183 "./typica.w"

bool ZoomLog::saveCSV(QIODevice*device)
{
CSVOutput writer(currentModel,device,0);
int c;
foreach(c,saveTempCols)
{
writer.addTemperatureColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
foreach(c,saveControlCols)
{
writer.addControlColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
foreach(c,saveNoteCols)
{
writer.addAnnotationColumn(model_ms->headerData(c,Qt::Horizontal).
toString(),c);
}
return writer.output();
}

/*:400*//*401:*/
#line 9212 "./typica.w"

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

/*:401*//*402:*/
#line 9260 "./typica.w"

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

/*:402*//*403:*/
#line 9280 "./typica.w"

QString ZoomLog::lastTime(int series)
{
Measurement measure= lastMeasurement.value(series);
QTime time= measure.time();
return time.toString("h:mm:ss.zzz");
}

/*:403*//*404:*/
#line 9290 "./typica.w"

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

/*:404*//*405:*/
#line 9313 "./typica.w"

void ZoomLog::setHeaderData(int section,QString text)
{
MeasurementModel*m;
foreach(m,modelSet)
{
m->setHeaderData(section,Qt::Horizontal,QVariant(text));
}
}

/*:405*//*406:*/
#line 9331 "./typica.w"

void ZoomLog::addOutputTemperatureColumn(int column)
{
saveTempCols.append(column);
}

void ZoomLog::addOutputControlColumn(int column)
{
saveControlCols.append(column);
}

void ZoomLog::addOutputAnnotationColumn(int column)
{
saveNoteCols.append(column);
}

void ZoomLog::clearOutputColumns()
{
saveTempCols.clear();
saveControlCols.clear();
saveNoteCols.clear();
}

/*:406*//*407:*/
#line 9357 "./typica.w"

void ZoomLog::persistColumnResize(int column,int,int newsize)
{
/*622:*/
#line 13496 "./typica.w"

QSettings settings;
/*623:*/
#line 13509 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:623*/
#line 13498 "./typica.w"

settings.setValue(QString("columnWidths/%1/%2/%3").
arg(topLevelWidget->objectName()).
arg(objectName()).arg(column),
QVariant(newsize));

/*:622*/
#line 9360 "./typica.w"

}

void ZoomLog::restoreColumnWidths()
{
/*625:*/
#line 13529 "./typica.w"

QSettings settings;
/*623:*/
#line 13509 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:623*/
#line 13531 "./typica.w"

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

/*:625*/
#line 9365 "./typica.w"

}

void ZoomLog::setVisible(bool visibility)
{
QTableView::setVisible(visibility);
}

void ZoomLog::showEvent(QShowEvent*)
{
/*625:*/
#line 13529 "./typica.w"

QSettings settings;
/*623:*/
#line 13509 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:623*/
#line 13531 "./typica.w"

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

/*:625*/
#line 9375 "./typica.w"

}

/*:407*/
#line 549 "./typica.w"

/*416:*/
#line 9608 "./typica.w"

bool MeasurementList::operator<(const MeasurementList&other)const
{
return this->first().toTime()<other.first().toTime();
}

bool MeasurementList::operator==(const MeasurementList&other)const
{
return this->first().toTime()==other.first().toTime();
}

/*:416*//*417:*/
#line 9624 "./typica.w"

QModelIndex MeasurementModel::parent(const QModelIndex&)const
{
return QModelIndex();
}

/*:417*//*418:*/
#line 9634 "./typica.w"

void MeasurementModel::newMeasurement(Measurement measure,int tempcolumn)
{
if(measure.scale()==Units::Unitless)
{
controlColumns->insert(tempcolumn,true);
}
else
{
controlColumns->insert(tempcolumn,false);
}
MeasurementList*temp;
temp= new MeasurementList;
temp->append(QVariant(measure.time()));
/*419:*/
#line 9693 "./typica.w"

/*420:*/
#line 9738 "./typica.w"

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

/*:420*/
#line 9694 "./typica.w"

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

/*:419*/
#line 9648 "./typica.w"

MeasurementList*newEntry;
int insertion;
if(i!=entries->end())
{
insertion= entries->indexOf(*i);
if((*i)->first().toTime()==measure.time())
{
/*421:*/
#line 9780 "./typica.w"

if((*i)->size()<tempcolumn+1)
{
for(int j= (*i)->size()-1;j<tempcolumn+1;j++)
{
(*i)->append(QVariant());
}
}
(*i)->replace(tempcolumn,measure);
lastInsertion= i;
emit dataChanged(createIndex(insertion,tempcolumn),
createIndex(insertion,tempcolumn));
lastTemperature->insert(tempcolumn,insertion);

/*:421*/
#line 9656 "./typica.w"

}
else
{
/*422:*/
#line 9798 "./typica.w"

beginInsertRows(QModelIndex(),insertion,insertion);
newEntry= new MeasurementList;
newEntry->append(QVariant(measure.time()));
for(int j= 0;j<tempcolumn+1;j++)
{
newEntry->append(QVariant());
}
newEntry->replace(tempcolumn,measure);
lastInsertion= entries->insert(i,newEntry);
endInsertRows();
lastTemperature->insert(tempcolumn,insertion);

/*:422*/
#line 9660 "./typica.w"

}
}
else
{
/*423:*/
#line 9816 "./typica.w"

insertion= entries->size();
/*422:*/
#line 9798 "./typica.w"

beginInsertRows(QModelIndex(),insertion,insertion);
newEntry= new MeasurementList;
newEntry->append(QVariant(measure.time()));
for(int j= 0;j<tempcolumn+1;j++)
{
newEntry->append(QVariant());
}
newEntry->replace(tempcolumn,measure);
lastInsertion= entries->insert(i,newEntry);
endInsertRows();
lastTemperature->insert(tempcolumn,insertion);

/*:422*/
#line 9818 "./typica.w"


/*:423*/
#line 9665 "./typica.w"

}
if(tempcolumn>=colcount)
{
colcount= tempcolumn+1;
}
emit rowChanged(insertion);
delete temp;
}

/*:418*//*424:*/
#line 9828 "./typica.w"

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
/*425:*/
#line 9866 "./typica.w"

beginInsertRows(QModelIndex(),0,0);
MeasurementList*newEntry= new MeasurementList;
newEntry->append(QVariant(QTime(0,0,0,0)));
entries->append(newEntry);
endInsertRows();

/*:425*/
#line 9843 "./typica.w"

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

/*:424*//*426:*/
#line 9877 "./typica.w"

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

/*:426*//*427:*/
#line 9910 "./typica.w"

bool MeasurementModel::setData(const QModelIndex&index,
const QVariant&value,int role)
{
if(role!=Qt::EditRole&&role!=Qt::DisplayRole)
{
return false;
}
/*428:*/
#line 9942 "./typica.w"

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

/*:428*/
#line 9918 "./typica.w"

if(!valid)
{
return false;
}
MeasurementList*row= entries->at(index.row());
if(index.column()>=row->size())
{
/*429:*/
#line 9959 "./typica.w"

for(int i= row->size()-1;i<index.column();i++)
{
row->append(QVariant());
}

/*:429*/
#line 9926 "./typica.w"

}
if(index.column()==0)
{
/*430:*/
#line 9974 "./typica.w"

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
/*419:*/
#line 9693 "./typica.w"

/*420:*/
#line 9738 "./typica.w"

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

/*:420*/
#line 9694 "./typica.w"

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

/*:419*/
#line 9986 "./typica.w"

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

/*:430*/
#line 9930 "./typica.w"

}
else
{
/*431:*/
#line 10000 "./typica.w"

row->replace(index.column(),value);
emit dataChanged(index,index);

/*:431*/
#line 9934 "./typica.w"

}
return true;
}

/*:427*//*432:*/
#line 10008 "./typica.w"

MeasurementModel::MeasurementModel(QObject*parent):QAbstractItemModel(parent),
unit(Units::Fahrenheit),hData(new QStringList),
lastTemperature(new QHash<int,int> ),
controlColumns(new QHash<int,bool> )
{
colcount= 1;
entries= new QList<MeasurementList*> ;
lastInsertion= entries->begin();
hData->append(tr("Time"));
}

/*:432*//*433:*/
#line 10022 "./typica.w"

MeasurementModel::~MeasurementModel()
{
clear();
delete entries;
delete hData;
}

/*:433*//*434:*/
#line 10034 "./typica.w"

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

/*:434*//*435:*/
#line 10061 "./typica.w"

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

/*:435*//*436:*/
#line 10101 "./typica.w"

void MeasurementModel::setDisplayUnits(Units::Unit scale)
{
beginResetModel();
unit= scale;
endResetModel();
}

Units::Unit MeasurementModel::displayUnits()
{
return unit;
}

/*:436*//*437:*/
#line 10127 "./typica.w"

QVariant MeasurementModel::data(const QModelIndex&index,int role)const
{
/*428:*/
#line 9942 "./typica.w"

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

/*:428*/
#line 10130 "./typica.w"

if(!valid)
{
return QVariant();
}
MeasurementList*row= entries->at(index.row());
if(role==Qt::UserRole)
{
return QVariant(row->at(index.column()));
}
if(role==Qt::DisplayRole||role==Qt::EditRole)
{
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
QVariantMap v= row->at(index.column()).toMap();
if(!v.contains("measurement"))
{
return QVariant();
}
if((Units::Unit)(v.value("unit").toInt())==Units::Unitless)
{
return v.value("measurement");
}
else
{
if(v.contains("relative"))
{
if(v.value("relative").toBool())
{
return QVariant(QString("%1").arg(Units::convertRelativeTemperature(v.value("measurement").
toDouble(),(Units::Unit)(v.value("unit").toInt()),unit)));
}
}
return QVariant(QString("%1").
arg(Units::convertTemperature(v.value("measurement").toDouble(),
(Units::Unit)(v.value("unit").toInt()),unit)));
}
}
return QVariant(row->at(index.column()).toString());
}
}
return QVariant();
}

/*:437*//*438:*/
#line 10186 "./typica.w"

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

/*:438*//*439:*/
#line 10213 "./typica.w"

Qt::ItemFlags MeasurementModel::flags(const QModelIndex&index)const
{
/*428:*/
#line 9942 "./typica.w"

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

/*:428*/
#line 10216 "./typica.w"

if(valid)
{
return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
}
return 0;
}

/*:439*//*440:*/
#line 10228 "./typica.w"

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

/*:440*/
#line 550 "./typica.w"

/*442:*/
#line 10279 "./typica.w"

AnnotationButton::AnnotationButton(const QString&text,QWidget*parent):
QPushButton(text,parent),note(""),tc(0),ac(0),count(0)
{
connect(this,SIGNAL(clicked()),this,SLOT(annotate()));
}

/*:442*//*443:*/
#line 10294 "./typica.w"

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

/*:443*//*444:*/
#line 10312 "./typica.w"

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

/*:444*//*445:*/
#line 10331 "./typica.w"

void AnnotationButton::resetCount()
{
count= 0;
}

/*:445*/
#line 551 "./typica.w"

/*450:*/
#line 10414 "./typica.w"

AnnotationSpinBox::AnnotationSpinBox(const QString&pret,
const QString&postt,
QWidget*parent)
:QDoubleSpinBox(parent),pretext(pret),posttext(postt)
{
resetChange();
connect(this,SIGNAL(editingFinished()),this,SLOT(annotate()));
connect(this,SIGNAL(valueChanged(double)),this,SLOT(resetChange()));
}

/*:450*//*451:*/
#line 10431 "./typica.w"

void AnnotationSpinBox::resetChange()
{
change= true;
}

/*:451*//*452:*/
#line 10442 "./typica.w"

void AnnotationSpinBox::annotate()
{
if(change)
{
change= false;
emit annotation(QString("%1%2%3").arg(pretext).
arg(value()).arg(posttext),tc,ac);
}
}

/*:452*//*453:*/
#line 10455 "./typica.w"

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

/*:453*/
#line 552 "./typica.w"

/*460:*/
#line 10624 "./typica.w"

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

/*:460*//*461:*/
#line 10645 "./typica.w"

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
/*462:*/
#line 10677 "./typica.w"

/*463:*/
#line 10690 "./typica.w"

#define TIMETOINT(t) ((t.hour() * 60 * 60) + (t.minute() * 60) + (t.second()))

time= QTime::currentTime();
cseconds= TIMETOINT(time);
oseconds= TIMETOINT(relative);
r= cseconds-oseconds;

/*:463*/
#line 10678 "./typica.w"

nt= nt.addSecs(r);
if(nt!=s)
{
s= nt;
emit valueChanged(s);
}

/*:462*/
#line 10658 "./typica.w"
;
break;
case TimerDisplay::CountDown:
/*464:*/
#line 10702 "./typica.w"

if(s> QTime(0,0,0))
{
/*463:*/
#line 10690 "./typica.w"

#define TIMETOINT(t) ((t.hour() * 60 * 60) + (t.minute() * 60) + (t.second()))

time= QTime::currentTime();
cseconds= TIMETOINT(time);
oseconds= TIMETOINT(relative);
r= cseconds-oseconds;

/*:463*/
#line 10705 "./typica.w"

bseconds= TIMETOINT(base);
n= bseconds-r;
nt= nt.addSecs(n);
if(nt!=s)
{
s= nt;
emit valueChanged(s);
}
}else{
stopTimer();
}

/*:464*/
#line 10661 "./typica.w"
;
break;
case TimerDisplay::Clock:
/*465:*/
#line 10721 "./typica.w"

time= QTime::currentTime();
if(time!=s)
{
s= time;
emit valueChanged(s);
}

/*:465*/
#line 10664 "./typica.w"
;
break;
default:
Q_ASSERT_X(false,"updateTime","invalid timer mode");
break;
}
updateDisplay();
}

/*:461*//*466:*/
#line 10733 "./typica.w"

#define TIMESUBTRACT(t1, t2) (t1.addSecs(-(TIMETOINT(t2))).addSecs(-t2.msec()))

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

/*:466*//*467:*/
#line 10763 "./typica.w"

void TimerDisplay::stopTimer()
{
if(running)
{
clock.stop();
running= false;
emit runStateChanged(false);
}
}

/*:467*//*468:*/
#line 10776 "./typica.w"

TimerDisplay::~TimerDisplay()
{
clock.stop();
}

/*:468*//*469:*/
#line 10785 "./typica.w"

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

/*:469*//*470:*/
#line 10803 "./typica.w"

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

/*:470*//*471:*/
#line 10841 "./typica.w"

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

/*:471*//*472:*/
#line 10876 "./typica.w"

void TimerDisplay::copyTimer()
{
QApplication::clipboard()->setText(value());
}

/*:472*//*473:*/
#line 10885 "./typica.w"

void TimerDisplay::reset()
{
if(!running)
{
s= r;
updateDisplay();
}
}

/*:473*//*474:*/
#line 10898 "./typica.w"

void TimerDisplay::updateDisplay()
{
display(value());
}

/*:474*/
#line 553 "./typica.w"

/*481:*/
#line 11023 "./typica.w"

int PackLayout::doLayout(const QRect&rect,bool testOnly)const
{
int x= rect.x();
int y= rect.y();
QLayoutItem*item;
if(orientation==Qt::Horizontal)
{
/*482:*/
#line 11047 "./typica.w"

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

/*:482*/
#line 11031 "./typica.w"

}
else
{
/*483:*/
#line 11066 "./typica.w"

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

/*:483*/
#line 11035 "./typica.w"

}
return y;
}

/*:481*//*484:*/
#line 11090 "./typica.w"

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

/*:484*//*485:*/
#line 11122 "./typica.w"

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

/*:485*//*486:*/
#line 11140 "./typica.w"

PackLayout::~PackLayout()
{
QLayoutItem*item;
while((item= takeAt(0)))
{
delete item;
}
}

/*:486*//*487:*/
#line 11154 "./typica.w"

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

/*:487*//*488:*/
#line 11170 "./typica.w"

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

/*:488*//*489:*/
#line 11193 "./typica.w"

void PackLayout::addItem(QLayoutItem*item)
{
itemList.append(item);
}

/*:489*//*490:*/
#line 11201 "./typica.w"

int PackLayout::count()const
{
return itemList.size();
}

/*:490*//*491:*/
#line 11213 "./typica.w"

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

/*:491*//*492:*/
#line 11244 "./typica.w"

void PackLayout::setOrientation(Qt::Orientations direction)
{
orientation= direction;
doLayout(geometry(),false);
}

/*:492*/
#line 554 "./typica.w"

/*494:*/
#line 11283 "./typica.w"

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

/*:494*/
#line 555 "./typica.w"

/*496:*/
#line 11329 "./typica.w"

WidgetDecorator::WidgetDecorator(QWidget*widget,const QString&labeltext,
Qt::Orientations orientation,
QWidget*parent,Qt::WindowFlags f):
QWidget(parent,f),label(new QGraphicsView()),
scene(new SceneButton())
{
layout= new PackLayout(this);
layout->setOrientation(orientation);
/*497:*/
#line 11349 "./typica.w"

label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setFrameShape(QFrame::NoFrame);
label->setInteractive(true);

/*:497*/
#line 11338 "./typica.w"

/*498:*/
#line 11360 "./typica.w"

scene->setBackgroundBrush(Qt::cyan);
text= scene->addText(labeltext);
if(orientation==Qt::Horizontal)
{
text->rotate(270.0);
}
label->setScene(scene);

/*:498*/
#line 11339 "./typica.w"

/*499:*/
#line 11378 "./typica.w"

if(orientation==Qt::Horizontal)
{
label->setMaximumWidth((int)(text->boundingRect().height()+1));
}
else
{
label->setMaximumHeight((int)(text->boundingRect().height()+1));
}
label->centerOn(text);

/*:499*/
#line 11340 "./typica.w"

/*500:*/
#line 11393 "./typica.w"

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

/*:500*/
#line 11341 "./typica.w"

}

/*:496*//*501:*/
#line 11410 "./typica.w"

void WidgetDecorator::setBackgroundBrush(QBrush background)
{
scene->setBackgroundBrush(background);
}

void WidgetDecorator::setTextColor(QColor color)
{
text->setDefaultTextColor(color);
}

/*:501*//*502:*/
#line 11423 "./typica.w"

WidgetDecorator::~WidgetDecorator()
{

}

/*:502*/
#line 556 "./typica.w"

/*507:*/
#line 11522 "./typica.w"

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

/*:507*//*508:*/
#line 11536 "./typica.w"

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
/*509:*/
#line 11573 "./typica.w"

QSettings settings;
resize(settings.value("logSize",QSize(620,400)).toSize());
move(settings.value("logPos",QPoint(200,60)).toPoint());

/*:509*/
#line 11553 "./typica.w"

/*510:*/
#line 11586 "./typica.w"

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

/*:510*/
#line 11554 "./typica.w"

/*511:*/
#line 11609 "./typica.w"

model->setHeaderData(0,Qt::Horizontal,"Time");
model->setHeaderData(1,Qt::Horizontal,"Temperature");
model->setHeaderData(2,Qt::Horizontal,"Annotation");
model->clear();

/*:511*/
#line 11555 "./typica.w"

/*512:*/
#line 11618 "./typica.w"

log->setModel(model);
log->setColumnWidth(0,100);
log->setColumnWidth(1,100);
log->setColumnWidth(2,100);

/*:512*/
#line 11556 "./typica.w"

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

/*:508*//*513:*/
#line 11629 "./typica.w"

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

/*:513*//*514:*/
#line 11672 "./typica.w"

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

/*:514*//*515:*/
#line 11703 "./typica.w"

void LogEditWindow::closeEvent(QCloseEvent*event)
{
QSettings settings;
settings.setValue("logSize",size());
settings.setValue("logPos",pos());
event->accept();
}

/*:515*/
#line 557 "./typica.w"

/*521:*/
#line 11818 "./typica.w"

bool XMLOutput::output()
{
if(!out->open(QIODevice::WriteOnly|QIODevice::Text))
{
return false;
}
QXmlStreamWriter xmlout(out);
xmlout.writeStartDocument("1.0");
xmlout.writeDTD("<!DOCTYPE roastlog3.0>");
xmlout.writeStartElement("roastlog");
/*522:*/
#line 11851 "./typica.w"

foreach(int c,temperatureColumns.keys())
{
xmlout.writeStartElement("tempseries");
xmlout.writeAttribute("name",temperatureColumns.value(c));
xmlout.writeEndElement();
}
foreach(int c,controlColumns.keys())
{
xmlout.writeStartElement("controlseries");
xmlout.writeAttribute("name",controlColumns.value(c));
xmlout.writeEndElement();
}
foreach(int c,annotationColumns.keys())
{
xmlout.writeStartElement("noteseries");
xmlout.writeAttribute("name",annotationColumns.value(c));
xmlout.writeEndElement();
}

/*:522*/
#line 11829 "./typica.w"

xmlout.writeStartElement("roast");
bool oresult;
for(int i= 0;i<data->rowCount();i++)
{
/*523:*/
#line 11876 "./typica.w"

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
foreach(int c,controlColumns.keys())
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

/*:523*/
#line 11834 "./typica.w"

if(oresult)
{
/*524:*/
#line 11915 "./typica.w"

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
if(data->data(data->index(i,c),Qt::UserRole).toMap().contains("relative"))
{
if(data->data(data->index(i,c),Qt::UserRole).toMap().value("relative").toBool())
{
xmlout.writeAttribute("relative","true");
}
}
xmlout.writeCharacters(data->data(data->index(i,c),Qt::DisplayRole).
toString());
xmlout.writeEndElement();
}
}
foreach(int c,controlColumns.keys())
{
if(data->data(data->index(i,c),Qt::DisplayRole).isValid()&&
!(data->data(data->index(i,c),Qt::DisplayRole).toString().isEmpty()))
{
xmlout.writeStartElement("control");
xmlout.writeAttribute("series",controlColumns.value(c));
xmlout.writeCharacters(data->data(data->index(i,c),Qt::DisplayRole).toString());
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

/*:524*/
#line 11837 "./typica.w"

}
}
xmlout.writeEndElement();
xmlout.writeEndElement();
xmlout.writeEndDocument();
out->close();
return true;
}

/*:521*//*525:*/
#line 11965 "./typica.w"

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

/*:525*//*526:*/
#line 11994 "./typica.w"

void XMLOutput::addTemperatureColumn(const QString&series,int column)
{
temperatureColumns.insert(column,series);
}

void XMLOutput::addControlColumn(const QString&series,int column)
{
controlColumns.insert(column,series);
}

void XMLOutput::addAnnotationColumn(const QString&series,int column)
{
annotationColumns.insert(column,series);
}

/*:526*/
#line 558 "./typica.w"

/*528:*/
#line 12051 "./typica.w"

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
/*529:*/
#line 12082 "./typica.w"

while(!xmlin.isDTD())
{
xmlin.readNext();
}
if(xmlin.isDTD())
{
if(xmlin.text()=="<!DOCTYPE roastlog>")
{
/*530:*/
#line 12104 "./typica.w"

emit newTemperatureColumn(firstc,"Bean");
emit newAnnotationColumn(firstc+1,"Note");
emit lastColumn(firstc+1);

/*:530*/
#line 12091 "./typica.w"

}
else
{
xmlin.readNext();
/*531:*/
#line 12113 "./typica.w"

while(xmlin.name()!="roast")
{
if(xmlin.isStartElement())
{
if((xmlin.name()=="tempseries")||(xmlin.name()=="controlseries"))
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

/*:531*/
#line 12096 "./typica.w"

}
}

/*:529*/
#line 12062 "./typica.w"

QTime timeval= QTime();
double tempval= 0;
QString noteval= QString();
int column;
int counter= 0;
while(!xmlin.atEnd())
{
/*532:*/
#line 12154 "./typica.w"

xmlin.readNext();
if(xmlin.isStartElement())
{
/*533:*/
#line 12180 "./typica.w"

if(xmlin.name()=="time")
{
timeval= QTime::fromString(xmlin.readElementText(),"mm:ss.zzz");
}
else if(xmlin.name()=="temperature")
{
column= xmlin.attributes().hasAttribute("series")?
temperatureColumns.value(xmlin.attributes().value("series").toString()):firstc;
bool relative= (xmlin.attributes().value("relative")=="true");
tempval= xmlin.readElementText().toDouble();
Measurement measurement(tempval,timeval);
if(relative)
{
measurement.insert("relative",true);
}
emit measure(measurement,column);
}
else if(xmlin.name()=="control")
{
column= xmlin.attributes().value("series").toString().isEmpty()?
firstc:temperatureColumns.value(xmlin.attributes().
value("series").toString());
tempval= xmlin.readElementText().toDouble();
Measurement measurement(tempval,timeval,Units::Unitless);
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

/*:533*/
#line 12158 "./typica.w"

}
counter++;
if(counter%100==0)
{
QCoreApplication::processEvents();
}

/*:532*/
#line 12070 "./typica.w"

}
return true;
}

/*:528*//*534:*/
#line 12221 "./typica.w"

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

/*:534*/
#line 559 "./typica.w"

/*539:*/
#line 12312 "./typica.w"

bool CSVOutput::output()
{
if(!out->open(QIODevice::WriteOnly|QIODevice::Text))
{
return false;
}
QTextStream output(out);
/*540:*/
#line 12336 "./typica.w"

output<<"Time";
foreach(int c,temperatureColumns.keys())
{
output<<','<<temperatureColumns.value(c);
}
foreach(int c,controlColumns.keys())
{
output<<','<<controlColumns.value(c);
}
foreach(int c,annotationColumns.keys())
{
output<<','<<annotationColumns.value(c);
}
output<<'\n';

/*:540*/
#line 12320 "./typica.w"

bool oresult;
for(int i= 0;i<data->rowCount();i++)
{
/*523:*/
#line 11876 "./typica.w"

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
foreach(int c,controlColumns.keys())
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

/*:523*/
#line 12324 "./typica.w"

if(oresult)
{
/*541:*/
#line 12361 "./typica.w"

output<<data->data(data->index(i,time),Qt::DisplayRole).toString();
foreach(int c,temperatureColumns.keys())
{
output<<','<<data->data(data->index(i,c),Qt::DisplayRole).toString();
}
foreach(int c,controlColumns.keys())
{
output<<','<<data->data(data->index(i,c),Qt::DisplayRole).toString();
}
foreach(int c,annotationColumns.keys())
{
output<<','<<data->data(data->index(i,c),Qt::DisplayRole).toString();
}
output<<'\n';

/*:541*/
#line 12327 "./typica.w"

}
}
out->close();
return true;
}

/*:539*//*542:*/
#line 12380 "./typica.w"

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

void CSVOutput::addControlColumn(const QString&series,int column)
{
controlColumns.insert(column,series);
}

void CSVOutput::addAnnotationColumn(const QString&series,int column)
{
annotationColumns.insert(column,series);
}

void CSVOutput::setDevice(QIODevice*device)
{
out= device;
}

#line 1 "./webview.w"
/*:542*/
#line 560 "./typica.w"

/*577:*/
#line 12642 "./typica.w"

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

/*:577*//*578:*/
#line 12686 "./typica.w"

QModelIndex SaltModel::parent(const QModelIndex&)const
{
return QModelIndex();
}

/*:578*//*579:*/
#line 12705 "./typica.w"

bool SaltModel::setData(const QModelIndex&index,const QVariant&value,
int role)
{
/*580:*/
#line 12736 "./typica.w"

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

/*:580*/
#line 12709 "./typica.w"

if(!valid)
{
return false;
}
if(index.row()==modelData.size()-1)
{
beginInsertRows(QModelIndex(),modelData.size(),modelData.size());
/*581:*/
#line 12752 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:581*/
#line 12717 "./typica.w"

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

/*:579*//*582:*/
#line 12763 "./typica.w"

SaltModel::SaltModel(int columns):QAbstractItemModel(),colcount(columns)
{
for(int i= 0;i<columns;i++)
{
hData<<"";
}
/*581:*/
#line 12752 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:581*/
#line 12770 "./typica.w"

}

/*:582*//*583:*/
#line 12775 "./typica.w"

SaltModel::~SaltModel()
{

}

/*:583*//*584:*/
#line 12785 "./typica.w"

int SaltModel::rowCount(const QModelIndex&parent)const
{
return(parent==QModelIndex()?modelData.size():0);
}

int SaltModel::columnCount(const QModelIndex&parent)const
{
return(parent==QModelIndex()?colcount:0);
}

/*:584*//*585:*/
#line 12798 "./typica.w"

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

/*:585*//*586:*/
#line 12813 "./typica.w"

QVariant SaltModel::data(const QModelIndex&index,int role)const
{
/*580:*/
#line 12736 "./typica.w"

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

/*:580*/
#line 12816 "./typica.w"

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

/*:586*//*587:*/
#line 12840 "./typica.w"

Qt::ItemFlags SaltModel::flags(const QModelIndex&index)const
{
/*580:*/
#line 12736 "./typica.w"

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

/*:580*/
#line 12843 "./typica.w"

if(valid)
{
return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsDropEnabled;
}
return 0;
}

/*:587*//*588:*/
#line 12854 "./typica.w"

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

/*:588*//*589:*/
#line 12872 "./typica.w"

void SaltModel::clear()
{
beginResetModel();
modelData.clear();
/*581:*/
#line 12752 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:581*/
#line 12877 "./typica.w"

endResetModel();
}

/*:589*//*590:*/
#line 12886 "./typica.w"

bool SaltModel::removeRows(int row,int count,
const QModelIndex&parent)
{
if(parent==QModelIndex())
{
if(row>=0&&count> 0&&(row+count-1)<modelData.size())
{
beginRemoveRows(parent,row,row+count-1);
for(int i= 0;i<count;i++)
{
modelData.removeAt(row);
}
endRemoveRows();
if(modelData.size()==0)
{
beginInsertRows(parent,0,0);
/*581:*/
#line 12752 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:581*/
#line 12903 "./typica.w"

endInsertRows();
}
return true;
}
}
return false;
}

/*:590*//*591:*/
#line 12917 "./typica.w"

int SaltModel::findData(const QVariant&value,int column,int role)
{
for(int i= 0;i<modelData.size();i++)
{
if(modelData.at(i).size()> column)
{
if(modelData.at(i).at(column).contains(role))
{
if(modelData.at(i).at(column).value(role)==value)
{
return i;
}
}
}
}
return-1;
}

/*:591*/
#line 561 "./typica.w"

/*593:*/
#line 12981 "./typica.w"

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

/*:593*//*594:*/
#line 12998 "./typica.w"

void SqlComboBox::showData(bool show)
{
dataColumnShown= show;
}

/*:594*//*595:*/
#line 13012 "./typica.w"

void SqlComboBox::addNullOption()
{
addItem(specialNullText,specialNullData);
}

void SqlComboBox::setNullText(QString nullText)
{
specialNullText= nullText;
}

void SqlComboBox::setNullData(QVariant nullData)
{
specialNullData= nullData;
}

/*:595*//*596:*/
#line 13035 "./typica.w"

void SqlComboBox::setDataColumn(int column)
{
dataColumn= column;
}

void SqlComboBox::setDisplayColumn(int column)
{
displayColumn= column;
}

/*:596*//*597:*/
#line 13049 "./typica.w"

void SqlComboBox::addSqlOptions(QString query)
{
SqlQueryConnection h;
QSqlQuery*dbquery= h.operator->();
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
}

/*:597*//*598:*/
#line 13085 "./typica.w"

SqlComboBox::SqlComboBox():
dataColumn(0),displayColumn(0),dataColumnShown(false),
specialNullText(tr("Unknown")),specialNullData(QVariant::String)
{
view()->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
}

SqlComboBox::~SqlComboBox()
{

}

/*:598*/
#line 562 "./typica.w"

/*600:*/
#line 13124 "./typica.w"

void SqlComboBoxDelegate::setWidget(SqlComboBox*widget)
{
delegate= widget;
}

/*:600*//*601:*/
#line 13133 "./typica.w"

QWidget*SqlComboBoxDelegate::createEditor(QWidget*parent,
const QStyleOptionViewItem&,
const QModelIndex&)const
{
return delegate->clone(parent);
}

/*:601*//*602:*/
#line 13144 "./typica.w"

void SqlComboBoxDelegate::setEditorData(QWidget*editor,
const QModelIndex&index)const
{
SqlComboBox*self= qobject_cast<SqlComboBox*> (editor);
self->setCurrentIndex(self->findData(
index.model()->data(index,
Qt::UserRole).toString()));
}

/*:602*//*603:*/
#line 13157 "./typica.w"

void SqlComboBoxDelegate::setModelData(QWidget*editor,
QAbstractItemModel*model,
const QModelIndex&index)const
{
SqlComboBox*self= qobject_cast<SqlComboBox*> (editor);
model->setData(index,self->itemData(self->currentIndex(),Qt::UserRole),
Qt::UserRole);
model->setData(index,self->currentText(),Qt::DisplayRole);
}

/*:603*//*604:*/
#line 13170 "./typica.w"

void SqlComboBoxDelegate::updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&)const
{
editor->setGeometry(option.rect);
}

/*:604*//*605:*/
#line 13181 "./typica.w"

QSize SqlComboBoxDelegate::sizeHint()const
{
return delegate->sizeHint();
}

/*:605*//*606:*/
#line 13189 "./typica.w"

SqlComboBoxDelegate::SqlComboBoxDelegate(QObject*parent)
:QItemDelegate(parent)
{

}

/*:606*/
#line 563 "./typica.w"

/*569:*/
#line 12450 "./typica.w"

Application::Application(int&argc,char**argv):QApplication(argc,argv)
{
/*570:*/
#line 12465 "./typica.w"

setOrganizationName("Wilson's Coffee & Tea");
setOrganizationDomain("wilsonscoffee.com");
setApplicationName(PROGRAM_NAME);

/*:570*/
#line 12453 "./typica.w"

/*571:*/
#line 12474 "./typica.w"

QTranslator base;
qDebug()<<"QLocale::system().name()"<<QLocale::system().name();
if(base.load(QString("qt_%1").arg(QLocale::system().name())))
{
installTranslator(&base);
}
QTranslator app;
if(app.load(QString("%1_%2").arg("Typica").arg(QLocale::system().name())))
{
installTranslator(&app);
}

/*:571*/
#line 12454 "./typica.w"

/*285:*/
#line 123 "./measurement.w"

qRegisterMetaType<Measurement> ("Measurement");

/*:285*/
#line 12455 "./typica.w"

/*777:*/
#line 16409 "./typica.w"

NodeInserter*inserter= new NodeInserter(tr("NI DAQmx Base Device"),
tr("NI DAQmx Base"),
"nidaqmxbase",NULL);
topLevelNodeInserters.append(inserter);

/*:777*//*785:*/
#line 16640 "./typica.w"

#ifdef Q_OS_WIN32
inserter= new NodeInserter(tr("NI DAQmx Device"),tr("NI DAQmx"),"nidaqmx",NULL);
topLevelNodeInserters.append(inserter);
#endif

/*:785*//*809:*/
#line 17603 "./typica.w"

#if 0
inserter= new NodeInserter(tr("Modbus RTU Port"),tr("Modbus RTU Port"),"modbusrtuport",NULL);
topLevelNodeInserters.append(inserter);
#endif

/*:809*//*858:*/
#line 19116 "./typica.w"

inserter= new NodeInserter(tr("Modbus RTU Device"),tr("Modbus RTU Device"),"modbusrtu",NULL);
topLevelNodeInserters.append(inserter);

#line 1 "./unsupportedserial.w"
/*:858*//*868:*/
#line 272 "./unsupportedserial.w"

inserter= new NodeInserter(tr("Other Device"),tr("Other Device"),
"unsupporteddevice",NULL);
topLevelNodeInserters.append(inserter);

/*:868*//*902:*/
#line 190 "./phidgets.w"

QLibrary phidgetsCheck("phidget21");
if(phidgetsCheck.load())
{
inserter= new NodeInserter(tr("Phidgets 1048"),tr("Phidgets 1048"),
"phidgets1048",NULL);
topLevelNodeInserters.append(inserter);
phidgetsCheck.unload();
}
else
{
phidgetsCheck.setFileName("Phidget21.framework/Phidget21");
if(phidgetsCheck.load())
{
inserter= new NodeInserter(tr("Phidgets 1048"),tr("Phidgets 1048"),
"phidgets1048",NULL);
topLevelNodeInserters.append(inserter);
phidgetsCheck.unload();
}
}

/*:902*//*993:*/
#line 1241 "./dataqsdk.w"

#ifdef Q_OS_WIN32
inserter= new NodeInserter(tr("DATAQ SDK Device"),tr("DATAQ Device"),
"dataqsdk",NULL);
topLevelNodeInserters.append(inserter);
#endif

#line 19766 "./typica.w"

#line 1 "./scales.w"
/*:993*//*1018:*/
#line 495 "./scales.w"

inserter= new NodeInserter(tr("Serial Scale"),tr("Scale"),"scale",NULL);
topLevelNodeInserters.append(inserter);

#line 19768 "./typica.w"

#line 1 "./valueannotation.w"
/*:1018*/
#line 12456 "./typica.w"

}

/*:569*//*573:*/
#line 12498 "./typica.w"

QDomDocument*Application::configuration()
{
return&conf;
}

/*:573*//*574:*/
#line 12507 "./typica.w"

QSqlDatabase Application::database()
{
QString connectionName;
QSqlDatabase connection= 
QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection),false);
do
{
connectionName= QUuid::createUuid().toString();
}while(QSqlDatabase::connectionNames().contains(connectionName));
return QSqlDatabase::cloneDatabase(connection,QString(connectionName));
}

/*:574*//*712:*/
#line 14993 "./typica.w"

void Application::saveDeviceConfiguration()
{
QSettings settings;
settings.setValue("DeviceConfiguration",
QVariant(deviceConfigurationDocument.toByteArray()));
}

/*:712*//*713:*/
#line 15005 "./typica.w"

QDomDocument Application::deviceConfiguration()
{
if(deviceConfigurationDocument.isNull())
{
/*714:*/
#line 15019 "./typica.w"

QSettings settings;
QByteArray document= settings.value("DeviceConfiguration").toByteArray();
QString etext;
int eline;
int ecol;
if(document.length()==0)
{
qDebug()<<"Loaded settings length is 0. Creating new configuration.";
/*715:*/
#line 15043 "./typica.w"

QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument,false,
&etext,&eline,&ecol))
{
/*716:*/
#line 15060 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:716*/
#line 15049 "./typica.w"

}
else
{
saveDeviceConfiguration();
}

/*:715*/
#line 15028 "./typica.w"

}
else
{
if(!deviceConfigurationDocument.setContent(document,false,
&etext,&eline,&ecol))
{
/*716:*/
#line 15060 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:716*/
#line 15035 "./typica.w"

/*715:*/
#line 15043 "./typica.w"

QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument,false,
&etext,&eline,&ecol))
{
/*716:*/
#line 15060 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:716*/
#line 15049 "./typica.w"

}
else
{
saveDeviceConfiguration();
}

/*:715*/
#line 15036 "./typica.w"

}
}

/*:714*/
#line 15010 "./typica.w"

}
return deviceConfigurationDocument;
}

/*:713*//*744:*/
#line 15661 "./typica.w"

void Application::registerDeviceConfigurationWidget(QString driver,
QMetaObject widget)
{
deviceConfigurationWidgets.insert(driver,widget);
}

/*:744*//*745:*/
#line 15677 "./typica.w"

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

/*:745*/
#line 564 "./typica.w"

/*615:*/
#line 13336 "./typica.w"

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

/*:615*//*616:*/
#line 13370 "./typica.w"

void SqlConnectionSetup::testConnection()
{
QSqlDatabase database= 
QSqlDatabase::addDatabase(driver->itemData(driver->currentIndex()).
toString());
database.setConnectOptions("application_name=Typica");
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
database.close();
accept();
}
else
{
QMessageBox::information(this,tr("Database connection failed"),
tr("Failed to connect to database."));
}
}

/*:616*/
#line 565 "./typica.w"

/*620:*/
#line 13472 "./typica.w"

SqlQueryView::SqlQueryView(QWidget*parent):QTableView(parent)
{
setModel(new QSqlQueryModel);
connect(this,SIGNAL(doubleClicked(QModelIndex)),
this,SLOT(openRow(QModelIndex)));
connect(horizontalHeader(),SIGNAL(sectionResized(int,int,int)),
this,SLOT(persistColumnResize(int,int,int)));
}

/*:620*//*621:*/
#line 13487 "./typica.w"

void SqlQueryView::persistColumnResize(int column,int,int newsize)
{
/*622:*/
#line 13496 "./typica.w"

QSettings settings;
/*623:*/
#line 13509 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:623*/
#line 13498 "./typica.w"

settings.setValue(QString("columnWidths/%1/%2/%3").
arg(topLevelWidget->objectName()).
arg(objectName()).arg(column),
QVariant(newsize));

/*:622*/
#line 13490 "./typica.w"

}

/*:621*//*624:*/
#line 13519 "./typica.w"

void SqlQueryView::showEvent(QShowEvent*event)
{
/*625:*/
#line 13529 "./typica.w"

QSettings settings;
/*623:*/
#line 13509 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:623*/
#line 13531 "./typica.w"

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

/*:625*/
#line 13522 "./typica.w"

event->accept();
}

/*:624*//*626:*/
#line 13546 "./typica.w"

void SqlQueryView::openRow(const QModelIndex&index)
{
emit openEntry(((QSqlQueryModel*)model())->record(index.row()).value(0).toString());
emit openEntryRow(index.row());
}

/*:626*//*627:*/
#line 13555 "./typica.w"

void SqlQueryView::setQuery(const QString&query)
{
QSqlDatabase database= AppInstance->database();
database.open();
QSqlQuery q(query,database);
((QSqlQueryModel*)model())->setQuery(q);
database.close();
}

bool SqlQueryView::setHeaderData(int section,Qt::Orientation orientation,
const QVariant&value,int role)
{
return model()->setHeaderData(section,orientation,value,role);
}

/*:627*//*628:*/
#line 13573 "./typica.w"

QVariant SqlQueryView::data(int row,int column,int role)
{
return model()->data(model()->index(row,column),role);
}

/*:628*/
#line 566 "./typica.w"

/*161:*/
#line 3801 "./typica.w"

SqlQueryConnection::SqlQueryConnection(const QString&query)
{
QSqlDatabase database= AppInstance->database();
database.open();
q= new QSqlQuery(query,database);
connection= database.connectionName();
}

/*:161*//*162:*/
#line 3814 "./typica.w"

SqlQueryConnection::~SqlQueryConnection()
{
delete q;
{
QSqlDatabase database= QSqlDatabase::database(connection);
database.close();
}
QSqlDatabase::removeDatabase(connection);
}

/*:162*//*163:*/
#line 3828 "./typica.w"

QSqlQuery*SqlQueryConnection::operator->()const
{
return q;
}

/*:163*/
#line 567 "./typica.w"

/*647:*/
#line 13930 "./typica.w"

ReportTable::ReportTable(QTextFrame*frame,QDomElement description):
area(frame),configuration(description)
{
refresh();
}

ReportTable::~ReportTable()
{

}

/*:647*//*648:*/
#line 13946 "./typica.w"

void ReportTable::bind(QString placeholder,QVariant value)
{
bindings.insert(placeholder,value);
}

/*:648*//*649:*/
#line 13956 "./typica.w"

void ReportTable::refresh()
{
/*650:*/
#line 13977 "./typica.w"

QTextCursor cursor= area->firstCursorPosition();
while(cursor<area->lastCursorPosition())
{
cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
}
cursor.removeSelectedText();

/*:650*/
#line 13959 "./typica.w"

int rows= 1;
int columns= 1;
int currentRow= 0;
QTextTable*table= cursor.insertTable(rows,columns);
/*651:*/
#line 13990 "./typica.w"

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

/*:651*/
#line 13964 "./typica.w"

/*652:*/
#line 14004 "./typica.w"

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
/*653:*/
#line 14031 "./typica.w"

SqlQueryConnection h;
QSqlQuery*query= h.operator->();
query->prepare(currentElement.text());
foreach(QString key,bindings.uniqueKeys())
{
if(currentElement.text().contains(key))
{
query->bindValue(key,bindings.value(key));
}
}
query->exec();
if(!query->next())
{
continue;
}
if(query->record().count()> columns)
{
table->appendColumns(query->record().count()-columns);
}
do
{
table->appendRows(1);
rows++;
currentRow++;
for(int j= 0;j<query->record().count();j++)
{
QTextTableCell cell= table->cellAt(currentRow,j);
cursor= cell.firstCursorPosition();
cursor.insertText(query->value(j).toString());
}
}while(query->next());

/*:653*/
#line 14016 "./typica.w"

}
else if(currentElement.tagName()=="row")
{
/*654:*/
#line 14071 "./typica.w"

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

/*:654*/
#line 14020 "./typica.w"

}
}
}

/*:652*/
#line 13965 "./typica.w"

if(rows> 1)
{
table->removeRows(0,1);
}
}

/*:649*/
#line 568 "./typica.w"

/*680:*/
#line 14175 "./typica.w"

FormArray::FormArray(QDomElement description):configuration(description),
maxwidth(-1),maxheight(-1)
{
setWidget(&itemContainer);
itemContainer.setLayout(&itemLayout);
}

/*:680*//*681:*/
#line 14192 "./typica.w"

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

/*:681*//*682:*/
#line 14242 "./typica.w"

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

/*:682*//*683:*/
#line 14259 "./typica.w"

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

/*:683*//*684:*/
#line 14275 "./typica.w"

int FormArray::elements()
{
return itemLayout.count();
}

/*:684*//*685:*/
#line 14286 "./typica.w"

void FormArray::setMaximumElementWidth(int width)
{
maxwidth= width;
}

void FormArray::setMaximumElementHeight(int height)
{
maxheight= height;
}

/*:685*/
#line 569 "./typica.w"

/*691:*/
#line 14417 "./typica.w"

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

/*:691*//*692:*/
#line 14490 "./typica.w"

QSize ScaleControl::sizeHint()const
{
return QSize(140,30);
}

/*:692*//*693:*/
#line 14499 "./typica.w"

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

/*:693*//*694:*/
#line 14536 "./typica.w"

double ScaleControl::initialValue(void)
{
return nonScoredValue;
}

double ScaleControl::finalValue(void)
{
return scoredValue;
}

/*:694*//*695:*/
#line 14557 "./typica.w"

void ScaleControl::mousePressEvent(QMouseEvent*event)
{
/*696:*/
#line 14569 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:696*/
#line 14560 "./typica.w"

scaleDown= true;
event->accept();
}

/*:695*//*697:*/
#line 14580 "./typica.w"

void ScaleControl::mouseReleaseEvent(QMouseEvent*event)
{
/*696:*/
#line 14569 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:696*/
#line 14583 "./typica.w"

if(!scaleDown)
{
event->ignore();
return;
}
scaleDown= false;
QPointF sceneCoordinate= mapToScene(event->x(),event->y());
/*698:*/
#line 14605 "./typica.w"

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

/*:698*/
#line 14591 "./typica.w"

/*699:*/
#line 14631 "./typica.w"

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

/*:699*/
#line 14592 "./typica.w"

/*700:*/
#line 14657 "./typica.w"

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

/*:700*/
#line 14593 "./typica.w"

event->ignore();
return;
}

/*:697*/
#line 570 "./typica.w"

/*702:*/
#line 14723 "./typica.w"

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

/*:702*//*703:*/
#line 14778 "./typica.w"

QSize IntensityControl::sizeHint()const
{
return QSize(25,160);
}

/*:703*//*704:*/
#line 14793 "./typica.w"

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

/*:704*//*705:*/
#line 14825 "./typica.w"

void IntensityControl::mousePressEvent(QMouseEvent*event)
{
/*696:*/
#line 14569 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:696*/
#line 14828 "./typica.w"

scaleDown= true;
event->accept();
}

/*:705*//*706:*/
#line 14839 "./typica.w"

void IntensityControl::mouseReleaseEvent(QMouseEvent*event)
{
/*696:*/
#line 14569 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:696*/
#line 14842 "./typica.w"

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

/*:706*/
#line 571 "./typica.w"

/*357:*/
#line 8077 "./typica.w"

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

/*:357*/
#line 572 "./typica.w"

/*788:*/
#line 16680 "./typica.w"

PortSelector::PortSelector(QWidget*parent):QComboBox(parent),
lister(new QextSerialEnumerator)
{
QList<QextPortInfo> ports= QextSerialEnumerator::getPorts();
QextPortInfo port;
foreach(port,ports)
{
#ifdef Q_OS_WIN32
addItem(port.portName);
#else
addItem(port.physName);
#endif
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

/*:788*/
#line 573 "./typica.w"

/*790:*/
#line 16772 "./typica.w"

BaudSelector::BaudSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= BaudSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("BaudRateType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString("%1").arg(type.value(i)));
}
}

/*:790*/
#line 574 "./typica.w"

/*792:*/
#line 16810 "./typica.w"

ParitySelector::ParitySelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= ParitySelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("ParityType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:792*/
#line 575 "./typica.w"

/*794:*/
#line 16840 "./typica.w"

FlowSelector::FlowSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= FlowSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("FlowType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:794*/
#line 576 "./typica.w"

/*796:*/
#line 16875 "./typica.w"

StopSelector::StopSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= StopSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("StopBitsType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:796*/
#line 577 "./typica.w"

/*856:*/
#line 18657 "./typica.w"

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
QCheckBox*pVHideBox= new QCheckBox(tr("Hide this channel"));
pVSection->addRow(pVHideBox);
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
QCheckBox*sVHideBox= new QCheckBox(tr("Hide this channel"));
sVSection->addRow(sVHideBox);
QGroupBox*setValueBox= new QGroupBox(tr("Set Value"));
setValueBox->setLayout(sVSection);
seriesLayout->addWidget(setValueBox);
masterLayout->addLayout(portAndDeviceLayout);
masterLayout->addLayout(seriesLayout);
form->setLayout(masterLayout);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 18747 "./typica.w"

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
else if(node.attribute("name")=="pvhidden")
{
pVHideBox->setChecked(node.attribute("value")=="true");
}
else if(node.attribute("name")=="svhidden")
{
sVHideBox->setChecked(node.attribute("value")=="true");
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
updatePVHidden(pVHideBox->isChecked());
updateSVHidden(sVHideBox->isChecked());
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
connect(pVHideBox,SIGNAL(toggled(bool)),this,SLOT(updatePVHidden(bool)));
connect(sVHideBox,SIGNAL(toggled(bool)),this,SLOT(updateSVHidden(bool)));
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

void ModbusConfigurator::updatePVHidden(bool hidden)
{
updateAttribute("pvhidden",hidden?"true":"false");
}

void ModbusConfigurator::updateSVHidden(bool hidden)
{
updateAttribute("svhidden",hidden?"true":"false");
}

/*:856*/
#line 578 "./typica.w"

/*799:*/
#line 16924 "./typica.w"

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

/*:799*/
#line 579 "./typica.w"

/*840:*/
#line 17956 "./typica.w"

ModbusRTUDevice::ModbusRTUDevice(DeviceTreeModel*model,const QModelIndex&index)
:QObject(NULL),messageDelayTimer(new QTimer),commTimeout(new QTimer),unitIsF(true),readingsv(false),
waiting(false)
{
qDebug()<<"Initializing Modbus RTU Device";
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
commTimeout->setSingleShot(true);
connect(messageDelayTimer,SIGNAL(timeout()),this,SLOT(sendNextMessage()));
connect(commTimeout,SIGNAL(timeout()),this,SLOT(timeout()));
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
qDebug()<<"Received unit response";
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
qDebug()<<"Received set value lower bound response";
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
qDebug()<<"Received set value upper bound response";
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
/*841:*/
#line 18211 "./typica.w"

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
Measurement pvm(pvOut,time,Units::Fahrenheit);
Measurement svm(svOut,time,Units::Fahrenheit);
channels.at(0)->input(pvm);
channels.at(1)->input(svm);

/*:841*/
#line 18198 "./typica.w"

}
else
{
/*842:*/
#line 18241 "./typica.w"

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
Measurement vm(valueOut,time,Units::Fahrenheit);
channels.at(0)->input(vm);
}
else
{
if(readingsv)
{
Measurement pvm(savedpv,time,Units::Fahrenheit);
Measurement svm(valueOut,time,Units::Fahrenheit);
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

/*:842*/
#line 18202 "./typica.w"

}
}

/*:840*//*843:*/
#line 18279 "./typica.w"

ModbusRTUDevice::~ModbusRTUDevice()
{
commTimeout->stop();
messageDelayTimer->stop();
port->close();
}

/*:843*//*844:*/
#line 18306 "./typica.w"

void ModbusRTUDevice::dataAvailable()
{
if(messageDelayTimer->isActive())
{
messageDelayTimer->stop();
}
responseBuffer.append(port->readAll());
/*845:*/
#line 18352 "./typica.w"

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

/*:845*/
#line 18314 "./typica.w"

commTimeout->stop();
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
}
else
{
qDebug()<<"CRC failed";
}
messageDelayTimer->start(delayTime);
waiting= false;
responseBuffer.clear();
}

/*:844*//*846:*/
#line 18394 "./typica.w"

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

/*:846*//*847:*/
#line 18425 "./typica.w"

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
commTimeout->start(2000);
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

/*:847*//*848:*/
#line 18474 "./typica.w"

void ModbusRTUDevice::ignore(QByteArray)
{
return;
}

/*:848*//*849:*/
#line 18487 "./typica.w"

void ModbusRTUDevice::timeout()
{
qDebug()<<"Communications timeout.";
responseBuffer.clear();
waiting= false;
messageDelayTimer->start();
}

/*:849*/
#line 580 "./typica.w"

/*718:*/
#line 15097 "./typica.w"

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

/*:718*/
#line 581 "./typica.w"

/*720:*/
#line 15186 "./typica.w"

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

/*:720*//*721:*/
#line 15221 "./typica.w"

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
/*722:*/
#line 15240 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:722*/
#line 15233 "./typica.w"

return parentItem->node().childNodes().count();
}

/*:721*//*723:*/
#line 15254 "./typica.w"

QModelIndex DeviceTreeModel::index(int row,int column,
const QModelIndex&parent)const
{
if(!hasIndex(row,column,parent))
{
return QModelIndex();
}
/*722:*/
#line 15240 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:722*/
#line 15262 "./typica.w"

DeviceTreeModelNode*childItem= parentItem->child(row);
if(childItem)
{
return createIndex(row,column,childItem);
}
return QModelIndex();
}

/*:723*//*724:*/
#line 15273 "./typica.w"

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

/*:724*//*725:*/
#line 15292 "./typica.w"

Qt::ItemFlags DeviceTreeModel::flags(const QModelIndex&index)const
{
if(!index.isValid())
{
return 0;
}
return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

/*:725*//*726:*/
#line 15307 "./typica.w"

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

/*:726*//*727:*/
#line 15339 "./typica.w"

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

/*:727*//*728:*/
#line 15362 "./typica.w"

void DeviceTreeModel::newNode(const QString&name,const QString&driver,
const QModelIndex&parent)
{
QString referenceID= QUuid::createUuid().toString();
/*722:*/
#line 15240 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:722*/
#line 15367 "./typica.w"

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

/*:728*//*729:*/
#line 15385 "./typica.w"

bool DeviceTreeModel::removeRows(int row,int count,const QModelIndex&parent)
{
/*722:*/
#line 15240 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:722*/
#line 15388 "./typica.w"

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

/*:729*//*730:*/
#line 15427 "./typica.w"

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

/*:730*//*731:*/
#line 15448 "./typica.w"

QVariant DeviceTreeModel::headerData(int,Qt::Orientation,int)const
{
return QVariant();
}

/*:731*//*732:*/
#line 15457 "./typica.w"

DeviceTreeModel::~DeviceTreeModel()
{
delete root;
}

/*:732*/
#line 582 "./typica.w"

/*759:*/
#line 15957 "./typica.w"

BasicDeviceConfigurationWidget::BasicDeviceConfigurationWidget(
DeviceTreeModel*model,const QModelIndex&index)
:QWidget(NULL),deviceModel(model),currentNode(index)
{

}

/*:759*//*760:*/
#line 15969 "./typica.w"

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

/*:760*//*761:*/
#line 16003 "./typica.w"

void BasicDeviceConfigurationWidget::insertChildNode(const QString&name,
const QString&driver)
{
deviceModel->newNode(name,driver,currentNode);
}

/*:761*/
#line 583 "./typica.w"

/*750:*/
#line 15801 "./typica.w"

DeviceConfigurationWindow::DeviceConfigurationWindow():QWidget(NULL),
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
view->setTextElideMode(Qt::ElideNone);
view->expandAll();
view->resizeColumnToContents(0);
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
configArea->setWidgetResizable(true);
splitter->addWidget(configArea);
QVBoxLayout*centralLayout= new QVBoxLayout;
centralLayout->addWidget(splitter);
setLayout(centralLayout);
connect(view,SIGNAL(activated(QModelIndex)),
this,SLOT(newSelection(QModelIndex)));
connect(view,SIGNAL(clicked(QModelIndex)),
this,SLOT(newSelection(QModelIndex)));
connect(model,SIGNAL(rowsInserted(QModelIndex,int,int)),
view,SLOT(expand(QModelIndex)));
connect(model,SIGNAL(rowsInserted(QModelIndex,int,int)),
this,SLOT(resizeColumn()));
connect(model,SIGNAL(rowsRemoved(QModelIndex,int,int)),
this,SLOT(resizeColumn()));
}

/*:750*//*751:*/
#line 15856 "./typica.w"

void DeviceConfigurationWindow::addDevice()
{
model->newNode(tr("New Roaster"),"roaster",QModelIndex());
}

/*:751*//*752:*/
#line 15864 "./typica.w"

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

/*:752*//*753:*/
#line 15880 "./typica.w"

void DeviceConfigurationWindow::newSelection(const QModelIndex&index)
{
QWidget*editor= AppInstance->deviceConfigurationWidget(model,index);
if(editor)
{
configArea->setWidget(editor);
editor->show();
}
}

/*:753*//*754:*/
#line 15897 "./typica.w"

void DeviceConfigurationWindow::resizeColumn()
{
view->resizeColumnToContents(0);
}

/*:754*/
#line 584 "./typica.w"

/*774:*/
#line 16327 "./typica.w"

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
QCheckBox*hideSeries= new QCheckBox("Hide this channel");
layout->addRow(hideSeries);
setLayout(layout);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 16348 "./typica.w"

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
else if(node.attribute("name")=="hidden")
{
hideSeries->setChecked(node.attribute("value")=="true");
}
}
updateThermocoupleType(typeSelector->currentText());
updateColumnName(columnName->text());
updateHidden(hideSeries->isChecked());
connect(typeSelector,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateThermocoupleType(QString)));
connect(columnName,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
connect(hideSeries,SIGNAL(toggled(bool)),this,SLOT(updateHidden(bool)));
}

/*:774*//*775:*/
#line 16378 "./typica.w"

void Ni9211TcConfWidget::updateThermocoupleType(const QString&type)
{
updateAttribute("type",type);
}

void Ni9211TcConfWidget::updateColumnName(const QString&name)
{
updateAttribute("columnname",name);
}

void Ni9211TcConfWidget::updateHidden(bool hidden)
{
updateAttribute("hidden",hidden?"true":"false");
}

/*:775*/
#line 585 "./typica.w"

/*770:*/
#line 16241 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 16255 "./typica.w"

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

/*:770*//*771:*/
#line 16277 "./typica.w"

void NiDaqMxBase9211ConfWidget::updateDeviceId(const QString&newId)
{
updateAttribute("deviceID",newId);
}

/*:771*//*772:*/
#line 16285 "./typica.w"

void NiDaqMxBase9211ConfWidget::addChannel()
{
insertChildNode(tr("Thermocouple channel"),"ni9211seriestc");
}

/*:772*/
#line 586 "./typica.w"

/*768:*/
#line 16192 "./typica.w"

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

/*:768*/
#line 587 "./typica.w"

/*635:*/
#line 13719 "./typica.w"

ReportAction::ReportAction(const QString&fileName,const QString&reportName,
QObject*parent):
QAction(reportName,parent),reportFile(fileName)
{
connect(this,SIGNAL(triggered()),this,SLOT(createReport()));
}

/*:635*//*636:*/
#line 13735 "./typica.w"

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
/*188:*/
#line 4475 "./typica.w"

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
/*189:*/
#line 4510 "./typica.w"

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
/*190:*/
#line 4557 "./typica.w"

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
/*633:*/
#line 13679 "./typica.w"

QSettings settings;
QString reportDirectory= QString("%1/%2").arg(settings.value("config").
toString()).
arg(element.attribute("src"));
QDir::addSearchPath("reports",reportDirectory);
QDir directory(reportDirectory);
directory.setFilter(QDir::Files);
directory.setSorting(QDir::Name);
QStringList nameFilter;
nameFilter<<"*.xml";
directory.setNameFilters(nameFilter);
QFileInfoList reportFiles= directory.entryInfoList();
for(int i= 0;i<reportFiles.size();i++)
{
QFileInfo reportFile= reportFiles.at(i);
/*637:*/
#line 13759 "./typica.w"

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
/*638:*/
#line 13786 "./typica.w"

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

/*:638*/
#line 13776 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:637*/
#line 13695 "./typica.w"

}

/*:633*/
#line 4571 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*191:*/
#line 4584 "./typica.w"

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

#line 1 "./helpmenu.w"
/*:191*/
#line 4577 "./typica.w"

}
}

/*:190*/
#line 4535 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*182:*/
#line 4292 "./typica.w"

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

/*:182*/
#line 4543 "./typica.w"

context->setThisObject(oldThis);

/*:189*/
#line 4486 "./typica.w"

}
/*192:*/
#line 9 "./helpmenu.w"

HelpMenu*helpMenu= new HelpMenu();
window->menuBar()->addMenu(helpMenu);

/*:192*/
#line 4488 "./typica.w"

window->show();

/*:188*/
#line 13748 "./typica.w"

file.close();
engine->popContext();
}
}

/*:636*/
#line 588 "./typica.w"

/*231:*/
#line 5652 "./typica.w"

NumericDelegate::NumericDelegate(QObject*parent):
QItemDelegate(parent)
{

}

/*:231*//*232:*/
#line 5664 "./typica.w"

void NumericDelegate::setEditorData(QWidget*editor,
const QModelIndex&index)const
{
QString value= index.model()->data(index,Qt::EditRole).toString();
QLineEdit*line= static_cast<QLineEdit*> (editor);
line->setText(value);
}

/*:232*//*233:*/
#line 5679 "./typica.w"

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

/*:233*//*234:*/
#line 5702 "./typica.w"

QWidget*NumericDelegate::createEditor(QWidget*parent,
const QStyleOptionViewItem&,
const QModelIndex&)const
{
return(new QLineEdit(parent));
}

/*:234*//*235:*/
#line 5713 "./typica.w"

void NumericDelegate::updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&)const
{
editor->setGeometry(option.rect);
}

/*:235*/
#line 589 "./typica.w"

/*779:*/
#line 16437 "./typica.w"

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

/*:779*/
#line 590 "./typica.w"

/*781:*/
#line 16486 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 16500 "./typica.w"

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

/*:781*/
#line 591 "./typica.w"

/*783:*/
#line 16551 "./typica.w"

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
QCheckBox*hideSeries= new QCheckBox(tr("Hide this channel"));
layout->addRow(hideSeries);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 16573 "./typica.w"

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
else if(node.attribute("name")=="hidden")
{
hideSeries->setChecked(node.attribute("value")=="true");
}
}
updateDeviceId(deviceId->text());
updateThermocoupleType(typeSelector->currentText());
updateColumnName(columnName->text());
updateHidden(hideSeries->isChecked());
connect(deviceId,SIGNAL(textEdited(QString)),this,SLOT(updateDeviceId(QString)));
connect(typeSelector,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateThermocoupleType(QString)));
connect(columnName,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
setLayout(layout);
connect(hideSeries,SIGNAL(toggled(bool)),this,SLOT(updateHidden(bool)));
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

void NiDaqMxTc01ConfWidget::updateHidden(bool hidden)
{
updateAttribute("hidden",hidden?"true":"false");
}

/*:783*/
#line 592 "./typica.w"

/*801:*/
#line 16989 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17029 "./typica.w"

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

/*:801*/
#line 593 "./typica.w"

/*803:*/
#line 17152 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17232 "./typica.w"

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

/*:803*/
#line 594 "./typica.w"

/*805:*/
#line 17395 "./typica.w"

ModbusRtuDeviceTPvConfWidget::ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
ShortHexSpinBox*address= new ShortHexSpinBox;
layout->addRow(tr("Function 0x04 Process Value Address"),address);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17403 "./typica.w"

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

/*:805*/
#line 595 "./typica.w"

/*807:*/
#line 17451 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17484 "./typica.w"

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

/*:807*/
#line 596 "./typica.w"

/*763:*/
#line 16039 "./typica.w"

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
NodeInserter*freeAnnotationInserter= new NodeInserter(tr("Free Text"),
tr("Free Text"),
"freeannotation");
annotationMenu->addAction(basicButtonInserter);
annotationMenu->addAction(countingButtonInserter);
annotationMenu->addAction(spinBoxInserter);
annotationMenu->addAction(freeAnnotationInserter);
connect(basicButtonInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(countingButtonInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(spinBoxInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(freeAnnotationInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
/*1026:*/
#line 144 "./valueannotation.w"

NodeInserter*valueAnnotationInserter= new NodeInserter(tr("Value Annotation"),
tr("Value Annotation"),
"valueannotation");
annotationMenu->addAction(valueAnnotationInserter);
connect(valueAnnotationInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));

/*:1026*/
#line 16075 "./typica.w"

addAnnotationControlButton->setMenu(annotationMenu);
layout->addWidget(addAnnotationControlButton);

QPushButton*timersButton= new QPushButton(tr("Extra Timers"));
QMenu*timersMenu= new QMenu;
NodeInserter*coolingTimerInserter= new NodeInserter(tr("Cooling Timer"),tr("Cooling Timer"),"coolingtimer");
NodeInserter*rangeTimerInserter= new NodeInserter(tr("Range Timer"),tr("Range Timer"),"rangetimer");
NodeInserter*multirangeTimerInserter= new NodeInserter(tr("Multi-Range Timer"),tr("Multi-Range Timer"),"multirangetimer");
timersMenu->addAction(coolingTimerInserter);
timersMenu->addAction(rangeTimerInserter);
timersMenu->addAction(multirangeTimerInserter);
connect(coolingTimerInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(rangeTimerInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
connect(multirangeTimerInserter,SIGNAL(triggered(QString,QString)),
this,SLOT(insertChildNode(QString,QString)));
timersButton->setMenu(timersMenu);
layout->addWidget(timersButton);

QPushButton*advancedButton= new QPushButton(tr("Advanced Features"));
QMenu*advancedMenu= new QMenu;
NodeInserter*linearsplineinserter= new NodeInserter(tr("Linear Spline Interpolated Series"),tr("Linear Spline Interpolated Series"),"linearspline");
advancedMenu->addAction(linearsplineinserter);
NodeInserter*translationinserter= new NodeInserter(tr("Profile Translation"),tr("Profile Translation"),"translation");
advancedMenu->addAction(translationinserter);
connect(linearsplineinserter,SIGNAL(triggered(QString,QString)),this,SLOT(insertChildNode(QString,QString)));
connect(translationinserter,SIGNAL(triggered(QString,QString)),this,SLOT(insertChildNode(QString,QString)));
/*952:*/
#line 258 "./rate.w"

NodeInserter*rateOfChangeInserter= new NodeInserter(tr("Rate of Change"),tr("Rate of Change"),"rate");
connect(rateOfChangeInserter,SIGNAL(triggered(QString,QString)),this,SLOT(insertChildNode(QString,QString)));
advancedMenu->addAction(rateOfChangeInserter);

/*:952*/
#line 16104 "./typica.w"

advancedButton->setMenu(advancedMenu);
layout->addWidget(advancedButton);

QHBoxLayout*idLayout= new QHBoxLayout;
QLabel*idLabel= new QLabel(tr("Machine ID for database:"));
idLayout->addWidget(idLabel);
QSpinBox*id= new QSpinBox;
idLayout->addWidget(id);
layout->addLayout(idLayout);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 16114 "./typica.w"

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

/*:763*//*765:*/
#line 16146 "./typica.w"

void RoasterConfWidget::updateRoasterId(int id)
{
updateAttribute("databaseid",QString("%1").arg(id));
}

/*:765*/
#line 597 "./typica.w"

/*811:*/
#line 17634 "./typica.w"

AnnotationButtonConfWidget::AnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*buttonTextEdit= new QLineEdit;
QLineEdit*annotationTextEdit= new QLineEdit;
layout->addRow(tr("Button Text:"),buttonTextEdit);
layout->addRow(tr("Annotation Text:"),annotationTextEdit);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17643 "./typica.w"

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

/*:811*//*812:*/
#line 17665 "./typica.w"

void AnnotationButtonConfWidget::updateButtonText(const QString&text)
{
updateAttribute("buttontext",text);
}

void AnnotationButtonConfWidget::updateAnnotationText(const QString&text)
{
updateAttribute("annotationtext",text);
}

/*:812*//*815:*/
#line 17703 "./typica.w"

ReconfigurableAnnotationButtonConfWidget::ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*buttonTextEdit= new QLineEdit;
QLineEdit*annotationTextEdit= new QLineEdit;
layout->addRow(tr("Button Text:"),buttonTextEdit);
layout->addRow(tr("Annotation Text:"),annotationTextEdit);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17712 "./typica.w"

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

/*:815*/
#line 598 "./typica.w"

/*818:*/
#line 17780 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 17799 "./typica.w"

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

/*:818*/
#line 599 "./typica.w"

/*327:*/
#line 7393 "./typica.w"

LinearCalibrator::LinearCalibrator(QObject*parent):
QObject(parent),Lo1(0),Lo2(0),Up1(1),Up2(1),sensitivitySetting(0.0),clamp(false)
{
connect(this,SIGNAL(measurement(Measurement)),this,SIGNAL(newData(Measurement)));
}

/*:327*//*328:*/
#line 7407 "./typica.w"

Measurement LinearCalibrator::newMeasurement(Measurement measure)
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
return adjusted;
}

/*:328*//*329:*/
#line 7434 "./typica.w"

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

/*:329*/
#line 600 "./typica.w"

/*334:*/
#line 7567 "./typica.w"

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

Measurement LinearSplineInterpolator::newMeasurement(Measurement measure)
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
return interpolators->at(index)->newMeasurement(measure);
}
return Measurement();
}

/*:334*/
#line 601 "./typica.w"

/*917:*/
#line 19148 "./typica.w"

LinearSplineInterpolationConfWidget::LinearSplineInterpolationConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),tablemodel(new SaltModel(2))
{
QFormLayout*layout= new QFormLayout;
QLineEdit*source= new QLineEdit;
layout->addRow(tr("Source column name:"),source);
QLineEdit*destination= new QLineEdit;
layout->addRow(tr("Destination column name:"),destination);
tablemodel->setHeaderData(0,Qt::Horizontal,"Input");
tablemodel->setHeaderData(1,Qt::Horizontal,"Output");
QTableView*mappingTable= new QTableView;
mappingTable->setModel(tablemodel);
NumericDelegate*delegate= new NumericDelegate;
mappingTable->setItemDelegate(delegate);
layout->addRow(tr("Mapping data:"),mappingTable);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 19164 "./typica.w"

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
/*918:*/
#line 19203 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:918*/
#line 19178 "./typica.w"

int column= 0;
/*919:*/
#line 19215 "./typica.w"

for(int j= 0;j<itemList.size();j++)
{
tablemodel->setData(tablemodel->index(j,column),
QVariant(itemList.at(j).toDouble()),
Qt::DisplayRole);
}

/*:919*/
#line 19180 "./typica.w"


}
else if(node.attribute("name")=="destinationvalues")
{
/*918:*/
#line 19203 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:918*/
#line 19185 "./typica.w"

int column= 1;
/*919:*/
#line 19215 "./typica.w"

for(int j= 0;j<itemList.size();j++)
{
tablemodel->setData(tablemodel->index(j,column),
QVariant(itemList.at(j).toDouble()),
Qt::DisplayRole);
}

/*:919*/
#line 19187 "./typica.w"

}
}
updateSourceColumn(source->text());
updateDestinationColumn(destination->text());
updateKnots();
connect(source,SIGNAL(textEdited(QString)),this,SLOT(updateSourceColumn(QString)));
connect(destination,SIGNAL(textEdited(QString)),this,SLOT(updateDestinationColumn(QString)));
connect(tablemodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateKnots()));
setLayout(layout);
}

/*:917*//*920:*/
#line 19226 "./typica.w"

void LinearSplineInterpolationConfWidget::updateKnots()
{
updateAttribute("sourcevalues",tablemodel->arrayLiteral(0,Qt::DisplayRole));
updateAttribute("destinationvalues",tablemodel->arrayLiteral(1,Qt::DisplayRole));
}

void LinearSplineInterpolationConfWidget::updateSourceColumn(const QString&source)
{
updateAttribute("source",source);
}

void LinearSplineInterpolationConfWidget::updateDestinationColumn(const QString&dest)
{
updateAttribute("destination",dest);
}

/*:920*/
#line 602 "./typica.w"

/*937:*/
#line 19695 "./typica.w"

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
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 19709 "./typica.w"

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

/*:937*//*938:*/
#line 19738 "./typica.w"

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

/*:938*/
#line 603 "./typica.w"

/*821:*/
#line 24 "./freeannotation.w"

FreeAnnotationConfWidget::FreeAnnotationConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*labelEdit= new QLineEdit;
layout->addRow(tr("Label Text:"),labelEdit);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 32 "./freeannotation.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="labeltext")
{
labelEdit->setText(node.attribute("value"));
}
}
updateLabel(labelEdit->text());
connect(labelEdit,SIGNAL(textEdited(QString)),
this,SLOT(updateLabel(QString)));
setLayout(layout);
}

/*:821*//*822:*/
#line 49 "./freeannotation.w"

void FreeAnnotationConfWidget::updateLabel(const QString&text)
{
updateAttribute("labeltext",text);
}

/*:822*/
#line 604 "./typica.w"

/*941:*/
#line 39 "./rate.w"

void RateOfChange::newMeasurement(Measurement measure)
{
cache.append(measure);
/*942:*/
#line 64 "./rate.w"

if(cache.size()> 2)
{
bool done= false;
while(!done)
{
if(cache.front().time().secsTo(cache.back().time())> ct)
{
cache.removeFirst();
}
else if(cache.back().time()<cache.front().time())
{
cache.removeFirst();
done= true;
}
else
{
done= true;
}
if(cache.size()<3)
{
done= true;
}
}
}

/*:942*/
#line 43 "./rate.w"

if(cache.size()>=2)
{
/*943:*/
#line 96 "./rate.w"

int N= cache.size();
double SXY= 0;
double SX= 0;
double SXX= 0;
double SY= 0;
double y;
double x;
for(int i= 0;i<N;i++)
{
y= cache.at(i).temperature();
SY+= y;
x= cache.at(0).time().msecsTo(cache.at(i).time())/1000.0;
SX+= x;
SXX+= (x*x);
SXY+= (x*y);
}
double M= ((N*SXY)-(SX*SY))/((N*SXX)-(SX*SX));
Measurement value(M*st,cache.back().time(),cache.back().scale());
value.insert("relative",true);
emit newData(value);

/*:943*/
#line 46 "./rate.w"

}
}

/*:941*//*944:*/
#line 120 "./rate.w"

RateOfChange::RateOfChange(int cachetime,int scaletime):ct(cachetime),st(1)
{
setScaleTime(scaletime);
}

void RateOfChange::setCacheTime(int seconds)
{
ct= seconds;
}

void RateOfChange::setScaleTime(int seconds)
{
st= (seconds> 0?seconds:1);
}

/*:944*/
#line 605 "./typica.w"

/*825:*/
#line 26 "./settings.w"

SettingsWindow::SettingsWindow():QMainWindow(NULL)
{
QTabWidget*settingsTab= new QTabWidget;
DeviceConfigurationWindow*deviceSettings= new DeviceConfigurationWindow;
settingsTab->addTab(deviceSettings,tr("Roasters"));
GraphSettingsWidget*graphSettings= new GraphSettingsWidget;
settingsTab->addTab(graphSettings,tr("Graph"));
AdvancedSettingsWidget*advancedSettings= new AdvancedSettingsWidget;
settingsTab->addTab(advancedSettings,tr("Advanced"));
setCentralWidget(settingsTab);
}

/*:825*/
#line 606 "./typica.w"

/*830:*/
#line 27 "./graphsettings.w"

GraphSettingsWidget::GraphSettingsWidget():QWidget(NULL)
{
QTabWidget*graphCategories= new QTabWidget;
GraphSettingsRelativeTab*relative= new GraphSettingsRelativeTab;
graphCategories->addTab(relative,tr("Relative Temperatures"));
QVBoxLayout*layout= new QVBoxLayout;
layout->addWidget(graphCategories);
setLayout(layout);
}

/*:830*//*832:*/
#line 65 "./graphsettings.w"

GraphSettingsRelativeTab::GraphSettingsRelativeTab():QWidget(NULL),
colorEdit(new QLineEdit)
{
QSettings settings;
QVBoxLayout*layout= new QVBoxLayout;
QCheckBox*enable= new QCheckBox(tr("Graph relative temperatures"));
enable->setChecked(settings.value("settings/graph/relative/enable",true).toBool());
updateEnableSetting(enable->isChecked());
connect(enable,SIGNAL(toggled(bool)),this,SLOT(updateEnableSetting(bool)));
layout->addWidget(enable);
QHBoxLayout*colorLayout= new QHBoxLayout;
QLabel*colorLabel= new QLabel(tr("Axis color:"));
colorEdit->setText(settings.value("settings/graph/relative/color","#000000").toString());
updateColorSetting(colorEdit->text());
connect(colorEdit,SIGNAL(textChanged(QString)),this,SLOT(updateColorSetting(QString)));
QToolButton*colorPickerButton= new QToolButton();
colorPickerButton->setIcon(QIcon::fromTheme("applications-graphics"));
connect(colorPickerButton,SIGNAL(clicked()),this,SLOT(showColorPicker()));
colorLayout->addWidget(colorLabel);
colorLayout->addWidget(colorEdit);
colorLayout->addWidget(colorPickerButton);
colorLayout->addStretch();
layout->addLayout(colorLayout);
QHBoxLayout*unitLayout= new QHBoxLayout;
QLabel*unitLabel= new QLabel(tr("Unit"));
QComboBox*unitSelector= new QComboBox;
unitSelector->addItem(tr("Fahrenheit"));
unitSelector->addItem(tr("Celsius"));
unitSelector->setCurrentIndex(settings.value("settings/graph/relative/unit",0).toInt());
updateUnit(unitSelector->currentIndex());
connect(unitSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(updateUnit(int)));
unitLayout->addWidget(unitLabel);
unitLayout->addWidget(unitSelector);
unitLayout->addStretch();
layout->addLayout(unitLayout);
QHBoxLayout*axisLayout= new QHBoxLayout;
QLabel*axisLabel= new QLabel(tr("Grid line positions (comma separated):"));
QLineEdit*axisEdit= new QLineEdit;
axisEdit->setText(settings.value("settings/graph/relative/grid","-300, -100, -10, 0, 10, 30, 50").toString());
updateAxisSetting(axisEdit->text());
connect(axisEdit,SIGNAL(textChanged(QString)),this,SLOT(updateAxisSetting(QString)));
axisLayout->addWidget(axisLabel);
axisLayout->addWidget(axisEdit);
layout->addLayout(axisLayout);
layout->addStretch();
setLayout(layout);
}

/*:832*//*833:*/
#line 116 "./graphsettings.w"

void GraphSettingsRelativeTab::updateEnableSetting(bool enabled)
{
QSettings settings;
settings.setValue("settings/graph/relative/enable",enabled);
}

void GraphSettingsRelativeTab::updateColorSetting(const QString&color)
{
QSettings settings;
settings.setValue("settings/graph/relative/color",color);
}

void GraphSettingsRelativeTab::updateAxisSetting(const QString&gridList)
{
QSettings settings;
QString settingValue;
QStringList points= gridList.split(QRegExp("[\\s,]+"),QString::SkipEmptyParts);
QStringList numbers;
foreach(QString text,points)
{
bool okay= false;
text.toDouble(&okay);
if(okay)
{
numbers.append(text);
}
}
numbers.removeDuplicates();
settings.setValue("settings/graph/relative/grid",numbers.join(","));
}

void GraphSettingsRelativeTab::updateUnit(int unit)
{
QSettings settings;
settings.setValue("settings/graph/relative/unit",unit);
}

/*:833*//*834:*/
#line 159 "./graphsettings.w"

void GraphSettingsRelativeTab::showColorPicker()
{
QColor color= QColorDialog::getColor(QColor(colorEdit->text()),this);
colorEdit->setText(color.name());
}
#line 62 "./settings.w"

#line 1 "./advancedsettings.w"
/*:834*/
#line 607 "./typica.w"

/*976:*/
#line 682 "./dataqsdk.w"

DataqSdkDeviceConfWidget::DataqSdkDeviceConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
deviceIdStack(new QStackedWidget)
{
QVBoxLayout*layout= new QVBoxLayout;
QCheckBox*autoDetect= new QCheckBox("Automatically select device");
layout->addWidget(autoDetect);
QWidget*autoLayerWidget= new QWidget;
QHBoxLayout*autoLayerLayout= new QHBoxLayout;
QLabel*autoLabel= new QLabel(tr("Device number"));
QSpinBox*autoNumber= new QSpinBox;
autoNumber->setMinimum(1);
autoNumber->setMaximum(99);
autoLayerLayout->addWidget(autoLabel);
autoLayerLayout->addWidget(autoNumber);
autoLayerWidget->setLayout(autoLayerLayout);
QWidget*fixedLayerWidget= new QWidget;
QHBoxLayout*fixedLayerLayout= new QHBoxLayout;
QLabel*fixedLabel= new QLabel(tr("Device port"));
QComboBox*portSelection= new QComboBox;
portSelection->setEditable(true);
portSelection->addItems(DataqSdkDevice::detectHardware());
fixedLayerLayout->addWidget(fixedLabel);
fixedLayerLayout->addWidget(portSelection);
fixedLayerWidget->setLayout(fixedLayerLayout);
deviceIdStack->addWidget(autoLayerWidget);
deviceIdStack->addWidget(fixedLayerWidget);
layout->addWidget(deviceIdStack);
QPushButton*addChannelButton= new QPushButton(tr("Add Channel"));
layout->addWidget(addChannelButton);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 714 "./dataqsdk.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="autoSelect")
{
autoDetect->setChecked(node.attribute("value")=="true"?true:false);
}
else if(node.attribute("name")=="deviceNumber")
{
autoNumber->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="port")
{
int index= portSelection->findText(node.attribute("value"));
if(index> -1)
{
portSelection->setCurrentIndex(index);
}
else
{
portSelection->setEditText(node.attribute("value"));
}
}
}
updateAutoSelect(autoDetect->isChecked());
updateDeviceNumber(autoNumber->value());
updatePort(portSelection->currentText());
connect(autoDetect,SIGNAL(toggled(bool)),this,SLOT(updateAutoSelect(bool)));
connect(autoNumber,SIGNAL(valueChanged(int)),this,SLOT(updateDeviceNumber(int)));
connect(portSelection,SIGNAL(currentIndexChanged(QString)),this,SLOT(updatePort(QString)));
connect(addChannelButton,SIGNAL(clicked()),this,SLOT(addChannel()));
setLayout(layout);
}

/*:976*//*977:*/
#line 758 "./dataqsdk.w"

void DataqSdkDeviceConfWidget::updateAutoSelect(bool automatic)
{
if(automatic)
{
updateAttribute("autoSelect","true");
deviceIdStack->setCurrentIndex(0);
}
else
{
updateAttribute("autoSelect","false");
deviceIdStack->setCurrentIndex(1);
}
}

/*:977*//*978:*/
#line 775 "./dataqsdk.w"

void DataqSdkDeviceConfWidget::updateDeviceNumber(int deviceNumber)
{
updateAttribute("deviceNumber",QString("%1").arg(deviceNumber));
}

void DataqSdkDeviceConfWidget::updatePort(QString portId)
{
updateAttribute("port",portId);
}

/*:978*//*979:*/
#line 788 "./dataqsdk.w"

void DataqSdkDeviceConfWidget::addChannel()
{
insertChildNode(tr("Channel"),"dataqsdkchannel");
}

/*:979*//*982:*/
#line 868 "./dataqsdk.w"

DataqSdkChannelConfWidget::DataqSdkChannelConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
startButton(new QPushButton(tr("Start"))),
resetButton(new QPushButton(tr("Reset"))),
stopButton(new QPushButton(tr("Stop"))),
calibrator(new LinearCalibrator),
currentMeasurement(new QLineEdit),minimumMeasurement(new QLineEdit),
maximumMeasurement(new QLineEdit),averageMeasurement(new QLineEdit),
currentMapped(new QLineEdit),minimumMapped(new QLineEdit),
maximumMapped(new QLineEdit),averageMapped(new QLineEdit),
rmCount(0),cmCount(0),
rmin(std::numeric_limits<double> ::max()),
rmax(std::numeric_limits<double> ::min()),rmean(0),
cmin(std::numeric_limits<double> ::max()),
cmax(std::numeric_limits<double> ::min()),cmean(0)
{
/*986:*/
#line 1107 "./dataqsdk.w"

QDomElement parentReference= model->referenceElement(model->data(index.parent(),Qt::UserRole).toString());
QDomNodeList deviceConfigData= parentReference.elementsByTagName("attribute");
QDomElement deviceNode;
QString configPort;
QString configAuto;
for(int i= 0;i<deviceConfigData.size();i++)
{
deviceNode= deviceConfigData.at(i).toElement();
if(deviceNode.attribute("name")=="autoSelect")
{
autoSelect= (deviceNode.attribute("value")=="true");
}
else if(deviceNode.attribute("name")=="deviceNumber")
{
configAuto= deviceNode.attribute("value");
}
else if(deviceNode.attribute("name")=="port")
{
configPort= deviceNode.attribute("value");
}
}
deviceID= autoSelect?configAuto:configPort;
channelOfInterest= index.row();

/*:986*/
#line 886 "./dataqsdk.w"

resetButton->setEnabled(false);
stopButton->setEnabled(false);
connect(startButton,SIGNAL(clicked()),this,SLOT(startCalibration()));
connect(resetButton,SIGNAL(clicked()),this,SLOT(resetCalibration()));
connect(stopButton,SIGNAL(clicked()),this,SLOT(stopCalibration()));
QVBoxLayout*layout= new QVBoxLayout;
QFormLayout*topLayout= new QFormLayout;
QLineEdit*columnEdit= new QLineEdit;
topLayout->addRow(tr("Column name"),columnEdit);
QComboBox*unitSelector= new QComboBox;
unitSelector->addItem(tr("Temperature"));
unitSelector->addItem(tr("Control"));
topLayout->addRow(tr("Measurement type"),unitSelector);
QCheckBox*smoothingBox= new QCheckBox(tr("Enable smoothing"));
topLayout->addRow(smoothingBox);
layout->addLayout(topLayout);
QCheckBox*hideSeries= new QCheckBox(tr("Hide this channel"));
topLayout->addRow(hideSeries);
QLabel*calibrationLabel= new QLabel(tr("Calibration settings"));
layout->addWidget(calibrationLabel);
QHBoxLayout*calibrationLayout= new QHBoxLayout;
QFormLayout*calibrationControlsLayout= new QFormLayout;
QLineEdit*measuredLowerEdit= new QLineEdit;
measuredLowerEdit->setText("0");
QLineEdit*measuredUpperEdit= new QLineEdit;
measuredUpperEdit->setText("10");
QLineEdit*mappedLowerEdit= new QLineEdit;
mappedLowerEdit->setText("0");
QLineEdit*mappedUpperEdit= new QLineEdit;
mappedUpperEdit->setText("10");
calibrationControlsLayout->addRow(tr("Measured lower value"),measuredLowerEdit);
calibrationControlsLayout->addRow(tr("Mapped lower value"),mappedLowerEdit);
calibrationControlsLayout->addRow(tr("Measured upper value"),measuredUpperEdit);
calibrationControlsLayout->addRow(tr("Mapped upper value"),mappedUpperEdit);
QCheckBox*closedBox= new QCheckBox(tr("Closed range"));
calibrationControlsLayout->addRow(closedBox);
QLineEdit*sensitivityEdit= new QLineEdit;
sensitivityEdit->setText("0");
calibrationControlsLayout->addRow(tr("Discrete interval skip"),sensitivityEdit);
QVBoxLayout*calibrationTestLayout= new QVBoxLayout;
QHBoxLayout*deviceControlLayout= new QHBoxLayout;
deviceControlLayout->addWidget(startButton);
deviceControlLayout->addWidget(resetButton);
deviceControlLayout->addWidget(stopButton);
QFormLayout*indicatorLayout= new QFormLayout;
currentMeasurement->setReadOnly(true);
minimumMeasurement->setReadOnly(true);
maximumMeasurement->setReadOnly(true);
averageMeasurement->setReadOnly(true);
currentMapped->setReadOnly(true);
minimumMapped->setReadOnly(true);
maximumMapped->setReadOnly(true);
averageMapped->setReadOnly(true);
indicatorLayout->addRow(tr("Measured Values"),new QWidget);
indicatorLayout->addRow(tr("Current"),currentMeasurement);
indicatorLayout->addRow(tr("Minimum"),minimumMeasurement);
indicatorLayout->addRow(tr("Maximum"),maximumMeasurement);
indicatorLayout->addRow(tr("Mean"),averageMeasurement);
indicatorLayout->addRow(tr("Mapped Values"),new QWidget);
indicatorLayout->addRow(tr("Current Mapped"),currentMapped);
indicatorLayout->addRow(tr("Minimum Mapped"),minimumMapped);
indicatorLayout->addRow(tr("Maximum Mapped"),maximumMapped);
indicatorLayout->addRow(tr("Mean Mapped"),averageMapped);
calibrationTestLayout->addLayout(deviceControlLayout);
calibrationTestLayout->addLayout(indicatorLayout);
calibrationLayout->addLayout(calibrationControlsLayout);
calibrationLayout->addLayout(calibrationTestLayout);
layout->addLayout(calibrationLayout);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 955 "./dataqsdk.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="column")
{
columnEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="type")
{
unitSelector->setCurrentIndex(unitSelector->findText(node.attribute("value")));
}
else if(node.attribute("name")=="smoothing")
{
smoothingBox->setChecked(node.attribute("value")=="true");
}
else if(node.attribute("name")=="calibrationMeasuredLower")
{
measuredLowerEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="calibrationMeasuredUpper")
{
measuredUpperEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="calibrationMappedLower")
{
mappedLowerEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="calibrationMappedUpper")
{
mappedUpperEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="calibrationClosedInterval")
{
closedBox->setChecked(node.attribute("value")=="true");
}
else if(node.attribute("name")=="calibrationSensitivity")
{
sensitivityEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="hidden")
{
hideSeries->setChecked(node.attribute("value")=="true");
}
}
updateColumnName(columnEdit->text());
updateUnits(unitSelector->currentText());
updateSmoothingEnabled(smoothingBox->isChecked());
updateMeasuredLower(measuredLowerEdit->text());
updateMeasuredUpper(measuredUpperEdit->text());
updateMappedLower(mappedLowerEdit->text());
updateMappedUpper(mappedUpperEdit->text());
updateClosedInterval(closedBox->isChecked());
updateSensitivity(sensitivityEdit->text());
updateHidden(hideSeries->isChecked());
connect(columnEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateColumnName(QString)));
connect(unitSelector,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateUnits(QString)));
connect(smoothingBox,SIGNAL(toggled(bool)),
this,SLOT(updateSmoothingEnabled(bool)));
connect(measuredLowerEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateMeasuredLower(QString)));
connect(mappedLowerEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateMappedLower(QString)));
connect(measuredUpperEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateMeasuredUpper(QString)));
connect(mappedUpperEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateMappedUpper(QString)));
connect(closedBox,SIGNAL(toggled(bool)),
this,SLOT(updateClosedInterval(bool)));
connect(sensitivityEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateSensitivity(QString)));
connect(hideSeries,SIGNAL(toggled(bool)),this,SLOT(updateHidden(bool)));
setLayout(layout);
}

/*:982*//*983:*/
#line 1038 "./dataqsdk.w"

void DataqSdkChannelConfWidget::updateUnits(const QString&unit)
{
updateAttribute("type",unit);
}

/*:983*//*984:*/
#line 1047 "./dataqsdk.w"

void DataqSdkChannelConfWidget::updateMeasuredLower(const QString&value)
{
updateAttribute("calibrationMeasuredLower",value);
calibrator->setMeasuredLower(value.toDouble());
}

void DataqSdkChannelConfWidget::updateMeasuredUpper(const QString&value)
{
updateAttribute("calibrationMeasuredUpper",value);
calibrator->setMeasuredUpper(value.toDouble());
}

void DataqSdkChannelConfWidget::updateMappedLower(const QString&value)
{
updateAttribute("calibrationMappedLower",value);
calibrator->setMappedLower(value.toDouble());
}

void DataqSdkChannelConfWidget::updateMappedUpper(const QString&value)
{
updateAttribute("calibrationMappedUpper",value);
calibrator->setMappedUpper(value.toDouble());
}

void DataqSdkChannelConfWidget::updateClosedInterval(bool closed)
{
updateAttribute("calibrationClosedInterval",closed?"true":"false");
calibrator->setClosedRange(closed);
}

void DataqSdkChannelConfWidget::updateSmoothingEnabled(bool enabled)
{
updateAttribute("smoothing",enabled?"true":"false");
}

void DataqSdkChannelConfWidget::updateSensitivity(const QString&value)
{
updateAttribute("calibrationSensitivity",value);
calibrator->setSensitivity(value.toDouble());
}

void DataqSdkChannelConfWidget::updateHidden(bool hidden)
{
updateAttribute("hidden",hidden?"true":"false");
}

/*:984*//*987:*/
#line 1136 "./dataqsdk.w"

void DataqSdkChannelConfWidget::startCalibration()
{
startButton->setEnabled(false);
stopButton->setEnabled(true);
resetButton->setEnabled(true);
calibrationDevice= new DataqSdkDevice(deviceID);
Channel*channel;
for(unsigned int i= 0;i<=channelOfInterest;i++)
{
channel= calibrationDevice->newChannel(Units::Unitless);
}
connect(channel,SIGNAL(newData(Measurement)),this,SLOT(updateInput(Measurement)));
connect(channel,SIGNAL(newData(Measurement)),calibrator,SLOT(newMeasurement(Measurement)));
connect(calibrator,SIGNAL(newData(Measurement)),this,SLOT(updateOutput(Measurement)));
calibrationDevice->setClockRate(6.0/(1.0+channelOfInterest));
calibrationDevice->start();
}

void DataqSdkChannelConfWidget::stopCalibration()
{
startButton->setEnabled(true);
stopButton->setEnabled(false);
resetButton->setEnabled(false);
calibrationDevice->deleteLater();
/*989:*/
#line 1181 "./dataqsdk.w"

rmCount= 0;
cmCount= 0;
rmin= std::numeric_limits<double> ::max();
rmax= std::numeric_limits<double> ::min();
rmean= 0;
cmin= std::numeric_limits<double> ::max();
cmax= std::numeric_limits<double> ::min();
cmean= 0;

/*:989*/
#line 1161 "./dataqsdk.w"

}

/*:987*//*988:*/
#line 1172 "./dataqsdk.w"

void DataqSdkChannelConfWidget::resetCalibration()
{
/*989:*/
#line 1181 "./dataqsdk.w"

rmCount= 0;
cmCount= 0;
rmin= std::numeric_limits<double> ::max();
rmax= std::numeric_limits<double> ::min();
rmean= 0;
cmin= std::numeric_limits<double> ::max();
cmax= std::numeric_limits<double> ::min();
cmean= 0;

/*:989*/
#line 1175 "./dataqsdk.w"

}

/*:988*//*990:*/
#line 1195 "./dataqsdk.w"

void DataqSdkChannelConfWidget::updateInput(Measurement measure)
{
double nv= measure.temperature();
currentMeasurement->setText(QString("%1").arg(nv));
rmin= qMin(nv,rmin);
minimumMeasurement->setText(QString("%1").arg(rmin));
rmax= qMax(nv,rmax);
maximumMeasurement->setText(QString("%1").arg(rmax));
rmean= ((rmean*rmCount)+nv)/(rmCount+1);
rmCount++;
averageMeasurement->setText(QString("%1").arg(rmean));
}

void DataqSdkChannelConfWidget::updateOutput(Measurement measure)
{
double nv= measure.temperature();
currentMapped->setText(QString("%1").arg(nv));
cmin= qMin(nv,cmin);
minimumMapped->setText(QString("%1").arg(cmin));
cmax= qMax(nv,cmax);
maximumMapped->setText(QString("%1").arg(cmax));
cmean= ((cmean*cmCount)+nv)/(cmCount+1);
cmCount++;
averageMapped->setText(QString("%1").arg(cmean));
}

/*:990*//*991:*/
#line 1224 "./dataqsdk.w"

void DataqSdkChannelConfWidget::updateColumnName(const QString&value)
{
updateAttribute("column",value);
}


/*:991*/
#line 608 "./typica.w"

/*1015:*/
#line 393 "./scales.w"

SerialScaleConfWidget::SerialScaleConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
port(new PortSelector),baud(new BaudSelector),parity(new ParitySelector),
flow(new FlowSelector),stop(new StopSelector)
{
QFormLayout*layout= new QFormLayout;
layout->addRow(tr("Port:"),port);
connect(port,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updatePort(QString)));
connect(port,SIGNAL(editTextChanged(QString)),
this,SLOT(updatePort(QString)));
layout->addRow(tr("Baud:"),baud);
connect(baud,SIGNAL(currentIndexChanged(QString)),
this,SLOT(updateBaudRate(QString)));
layout->addRow(tr("Parity:"),parity);
connect(parity,SIGNAL(currentIndexChanged(int)),
this,SLOT(updateParity(int)));
layout->addRow(tr("Flow Control:"),flow);
connect(flow,SIGNAL(currentIndexChanged(int)),
this,SLOT(updateFlowControl(int)));
layout->addRow(tr("Stop Bits:"),stop);
connect(stop,SIGNAL(currentIndexChanged(int)),
this,SLOT(updateStopBits(int)));
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 418 "./scales.w"

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
baud->setCurrentIndex(baud->findText(node.attribute("value")));
}
else if(node.attribute("name")=="parity")
{
parity->setCurrentIndex(parity->findData(node.attribute("value")));
}
else if(node.attribute("name")=="flowcontrol")
{
flow->setCurrentIndex(flow->findData(node.attribute("value")));
}
else if(node.attribute("name")=="stopbits")
{
stop->setCurrentIndex(stop->findData(node.attribute("value")));
}
}
updatePort(port->currentText());
updateBaudRate(baud->currentText());
updateParity(parity->currentIndex());
updateFlowControl(flow->currentIndex());
updateStopBits(stop->currentIndex());
setLayout(layout);
}

/*:1015*//*1016:*/
#line 462 "./scales.w"

void SerialScaleConfWidget::updatePort(const QString&newPort)
{
updateAttribute("port",newPort);
}

void SerialScaleConfWidget::updateBaudRate(const QString&rate)
{
updateAttribute("baudrate",rate);
}

void SerialScaleConfWidget::updateParity(int index)
{
updateAttribute("parity",parity->itemData(index).toString());
}

void SerialScaleConfWidget::updateFlowControl(int index)
{
updateAttribute("flowcontrol",flow->itemData(index).toString());
}

void SerialScaleConfWidget::updateStopBits(int index)
{
updateAttribute("stopbits",stop->itemData(index).toString());
}

/*:1016*/
#line 609 "./typica.w"

/*1028:*/
#line 195 "./valueannotation.w"

void ValueAnnotation::newMeasurement(Measurement measure)
{
for(int i= 0;i<values.size();i++)
{
if(measure.temperature()> values.at(i)-tolerance&&
measure.temperature()<values.at(i)+tolerance)
{
if(i!=lastIndex)
{
lastIndex= i;
emit annotation(annotations.at(i),measurementColumn,annotationColumn);
}
}
}
}

/*:1028*//*1029:*/
#line 216 "./valueannotation.w"

void ValueAnnotation::annotate()
{
if(lastIndex> -1)
{
emit annotation(annotations.at(lastIndex),measurementColumn,annotationColumn);
}
}

/*:1029*//*1030:*/
#line 228 "./valueannotation.w"

void ValueAnnotation::setAnnotation(double value,const QString&annotation)
{
values.append(value);
annotations.append(annotation);
}

/*:1030*//*1031:*/
#line 237 "./valueannotation.w"

void ValueAnnotation::setAnnotationColumn(int column)
{
annotationColumn= column;
}

void ValueAnnotation::setTemperatureColumn(int column)
{
measurementColumn= column;
}

void ValueAnnotation::setTolerance(double epsilon)
{
tolerance= epsilon;
}

/*:1031*//*1032:*/
#line 255 "./valueannotation.w"

ValueAnnotation::ValueAnnotation():QObject(),
lastIndex(-1),annotationColumn(2),measurementColumn(1),tolerance(0.05)
{

}

/*:1032*/
#line 610 "./typica.w"

/*1020:*/
#line 33 "./valueannotation.w"

ValueAnnotationConfWidget::ValueAnnotationConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
tablemodel(new SaltModel(2))
{
QFormLayout*layout= new QFormLayout;
QLineEdit*source= new QLineEdit;
layout->addRow(tr("Source column name:"),source);
QCheckBox*noteOnStart= new QCheckBox(tr("Produce Start State Annotation"));
noteOnStart->setChecked(true);
layout->addRow(noteOnStart);
tablemodel->setHeaderData(0,Qt::Horizontal,"Value");
tablemodel->setHeaderData(1,Qt::Horizontal,"Annotation");
QTableView*annotationTable= new QTableView;
annotationTable->setModel(tablemodel);
NumericDelegate*delegate= new NumericDelegate;
annotationTable->setItemDelegateForColumn(0,delegate);
layout->addRow(tr("Annotations for values:"),annotationTable);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 52 "./valueannotation.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="source")
{
source->setText(node.attribute("value"));
}
else if(node.attribute("name")=="emitOnStart")
{
noteOnStart->setChecked(node.attribute("value")=="true"?true:false);
}
else if(node.attribute("name")=="measuredValues")
{
/*918:*/
#line 19203 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:918*/
#line 66 "./valueannotation.w"

int column= 0;
/*919:*/
#line 19215 "./typica.w"

for(int j= 0;j<itemList.size();j++)
{
tablemodel->setData(tablemodel->index(j,column),
QVariant(itemList.at(j).toDouble()),
Qt::DisplayRole);
}

/*:919*/
#line 68 "./valueannotation.w"

}
else if(node.attribute("name")=="annotations")
{
/*1021:*/
#line 89 "./valueannotation.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");
for(int i= 0;i<itemList.size();i++)
{
itemList[i]= itemList[i].simplified();
}

/*:1021*/
#line 72 "./valueannotation.w"

int column= 1;
/*1022:*/
#line 104 "./valueannotation.w"

for(int i= 0;i<itemList.size();i++)
{
tablemodel->setData(tablemodel->index(i,column),
QVariant(itemList.at(i)),
Qt::DisplayRole);
}

/*:1022*/
#line 74 "./valueannotation.w"

}
}
updateSourceColumn(source->text());
updateStart(noteOnStart->isChecked());
updateAnnotations();
connect(source,SIGNAL(textEdited(QString)),this,SLOT(updateSourceColumn(QString)));
connect(noteOnStart,SIGNAL(toggled(bool)),this,SLOT(updateStart(bool)));
connect(tablemodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateAnnotations()));
setLayout(layout);
}

/*:1020*//*1023:*/
#line 115 "./valueannotation.w"

void ValueAnnotationConfWidget::updateAnnotations()
{
updateAttribute("measuredValues",tablemodel->arrayLiteral(0,Qt::DisplayRole));
updateAttribute("annotations",tablemodel->arrayLiteral(1,Qt::DisplayRole));
}

/*:1023*//*1024:*/
#line 125 "./valueannotation.w"

void ValueAnnotationConfWidget::updateSourceColumn(const QString&source)
{
updateAttribute("source",source);
}

void ValueAnnotationConfWidget::updateStart(bool noteOnStart)
{
updateAttribute("emitOnStart",noteOnStart?"true":"false");
}

/*:1024*/
#line 611 "./typica.w"


/*:4*//*240:*/
#line 5778 "./typica.w"

/*237:*/
#line 5741 "./typica.w"

void ScriptValidator::fixup(QString&input)const
{
QScriptEngine*engine= AppInstance->engine;
engine->pushContext();
input= engine->evaluate(input).toString();
engine->popContext();
}

/*:237*//*238:*/
#line 5754 "./typica.w"

QValidator::State ScriptValidator::validate(QString&input,int&pos)const
{
if(v)
{
if(v->validate(input,pos)==QValidator::Acceptable)
{
return QValidator::Acceptable;
}
}
return QValidator::Intermediate;
}

/*:238*//*239:*/
#line 5769 "./typica.w"

ScriptValidator::ScriptValidator(QValidator*validator,QObject*parent)
:QValidator(parent),v(validator)
{

}

/*:239*/
#line 5779 "./typica.w"


/*:240*//*838:*/
#line 60 "./advancedsettings.w"

/*836:*/
#line 26 "./advancedsettings.w"

AdvancedSettingsWidget::AdvancedSettingsWidget():QWidget(NULL)
{
QSettings settings;
QFormLayout*layout= new QFormLayout;
QCheckBox*logDiagnostics= new QCheckBox;
logDiagnostics->setCheckState(
settings.value("settings/advanced/logging",false).toBool()?
Qt::Checked:Qt::Unchecked);
connect(logDiagnostics,SIGNAL(toggled(bool)),this,SLOT(enableDiagnosticLogging(bool)));
layout->addRow(tr("Enable diagnostic logging"),logDiagnostics);
setLayout(layout);
}

/*:836*//*837:*/
#line 43 "./advancedsettings.w"

void AdvancedSettingsWidget::enableDiagnosticLogging(bool enabled)
{
QSettings settings;
settings.setValue("settings/advanced/logging",enabled);
if(enabled)
{
qInstallMsgHandler(messageFileOutput);
}
else
{
qInstallMsgHandler(0);
}
}

/*:837*/
#line 61 "./advancedsettings.w"

#line 17881 "./typica.w"

/*:838*//*885:*/
#line 639 "./unsupportedserial.w"

/*860:*/
#line 58 "./unsupportedserial.w"

UnsupportedSerialDeviceConfWidget::UnsupportedSerialDeviceConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
deviceSettingsModel(new SaltModel(2)),
scriptEditor(new QTextEdit)
{
scriptEditor->setTabStopWidth(20);
QVBoxLayout*dummyLayout= new QVBoxLayout;
QTabWidget*central= new QTabWidget;
QWidget*deviceConfigurationWidget= new QWidget;
QVBoxLayout*deviceConfigurationLayout= new QVBoxLayout;
QPushButton*addChannelButton= new QPushButton(tr("Add Channel"));
deviceConfigurationLayout->addWidget(addChannelButton);
connect(addChannelButton,SIGNAL(clicked()),this,SLOT(addChannel()));
QLabel*deviceSettingsLabel= new QLabel(tr("Device Settings:"));
deviceConfigurationLayout->addWidget(deviceSettingsLabel);
QTableView*deviceSettingsView= new QTableView;
deviceSettingsModel->setHeaderData(0,Qt::Horizontal,tr("Key"));
deviceSettingsModel->setHeaderData(1,Qt::Horizontal,tr("Value"));
deviceSettingsView->setModel(deviceSettingsModel);
deviceConfigurationLayout->addWidget(deviceSettingsView);

deviceConfigurationWidget->setLayout(deviceConfigurationLayout);
central->addTab(deviceConfigurationWidget,tr("Configuration"));
central->addTab(scriptEditor,tr("Script"));
dummyLayout->addWidget(central);

/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 86 "./unsupportedserial.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="keys"||node.attribute("name")=="values")
{
int column= 0;
if(node.attribute("name")=="values")
{
column= 1;
}
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList keyList= data.split(", ");
for(int j= 0;j<keyList.size();j++)
{
deviceSettingsModel->setData(deviceSettingsModel->index(j,column),
QVariant(keyList.at(j)),
Qt::EditRole);
}
}
else if(node.attribute("name")=="script")
{
scriptEditor->setPlainText(node.attribute("value"));
}
}

connect(deviceSettingsModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
this,SLOT(updateConfiguration()));
connect(scriptEditor,SIGNAL(textChanged()),this,SLOT(saveScript()));
setLayout(dummyLayout);
}

/*:860*//*861:*/
#line 131 "./unsupportedserial.w"

void UnsupportedSerialDeviceConfWidget::updateConfiguration()
{
updateAttribute("keys",deviceSettingsModel->arrayLiteral(0,Qt::DisplayRole));
updateAttribute("values",deviceSettingsModel->arrayLiteral(1,Qt::DisplayRole));
}

/*:861*//*862:*/
#line 144 "./unsupportedserial.w"

void UnsupportedSerialDeviceConfWidget::saveScript()
{
updateAttribute("script",scriptEditor->toPlainText());
}

/*:862*//*863:*/
#line 155 "./unsupportedserial.w"

void UnsupportedSerialDeviceConfWidget::addChannel()
{
insertChildNode(tr("Channel"),"unsupporteddevicechannel");
}

/*:863*//*865:*/
#line 183 "./unsupportedserial.w"

UnsupportedDeviceChannelConfWidget::UnsupportedDeviceChannelConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
channelSettingsModel(new SaltModel(2))
{
QFormLayout*layout= new QFormLayout;
QLineEdit*columnName= new QLineEdit;
layout->addRow(tr("Column Name:"),columnName);
QCheckBox*hideSeries= new QCheckBox("Hide this channel");
layout->addRow(hideSeries);
QTableView*channelSettings= new QTableView;
channelSettingsModel->setHeaderData(0,Qt::Horizontal,"Key");
channelSettingsModel->setHeaderData(1,Qt::Horizontal,"Value");
channelSettings->setModel(channelSettingsModel);
layout->addRow(channelSettings);
setLayout(layout);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 200 "./unsupportedserial.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="columnname")
{
columnName->setText(node.attribute("value"));
}
else if(node.attribute("name")=="hidden")
{
hideSeries->setChecked(node.attribute("value")=="true");
}
else if(node.attribute("name")=="keys"||node.attribute("name")=="values")
{
int column= 0;
if(node.attribute("name")=="values")
{
column= 1;
}
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList keyList= data.split(", ");
for(int j= 0;j<keyList.size();j++)
{
channelSettingsModel->setData(channelSettingsModel->index(j,column),
QVariant(keyList.at(j)),
Qt::EditRole);
}
}
}
connect(columnName,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
connect(hideSeries,SIGNAL(toggled(bool)),this,SLOT(updateHidden(bool)));
connect(channelSettingsModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
this,SLOT(updateConfiguration()));
}

/*:865*//*866:*/
#line 244 "./unsupportedserial.w"

void UnsupportedDeviceChannelConfWidget::updateColumnName(const QString&value)
{
updateAttribute("columnname",value);
}

void UnsupportedDeviceChannelConfWidget::updateHidden(bool hidden)
{
updateAttribute("hidden",hidden?"true":"false");
}

void UnsupportedDeviceChannelConfWidget::updateConfiguration()
{
updateAttribute("keys",channelSettingsModel->arrayLiteral(0,Qt::DisplayRole));
updateAttribute("values",channelSettingsModel->arrayLiteral(1,Qt::DisplayRole));
}

/*:866*/
#line 640 "./unsupportedserial.w"

/*873:*/
#line 371 "./unsupportedserial.w"

void JavaScriptDevice::start()
{
QScriptValue object= scriptengine->newQObject(this);
/*874:*/
#line 390 "./unsupportedserial.w"

QScriptValue settingsObject= scriptengine->newObject();
QVariantMap::const_iterator i= deviceSettings.constBegin();
while(i!=deviceSettings.constEnd())
{
settingsObject.setProperty(i.key(),i.value().toString());
i++;
}
object.setProperty("settings",settingsObject);

/*:874*/
#line 375 "./unsupportedserial.w"

/*875:*/
#line 405 "./unsupportedserial.w"

QScriptValue channelsArray= scriptengine->newArray(channelCount());
for(int i= 0;i<channelCount();i++)
{
QScriptValue channelObject= scriptengine->newQObject(getChannel(i));
QScriptValue channelSettingsObject= scriptengine->newObject();
QVariantMap::const_iterator j= channelSettings.at(i).constBegin();
while(j!=channelSettings.at(i).constEnd())
{
channelSettingsObject.setProperty(j.key(),j.value().toString());
j++;
}
channelObject.setProperty("settings",channelSettingsObject);
channelsArray.setProperty(i,channelObject);
}
object.setProperty("channels",channelsArray);

/*:875*/
#line 376 "./unsupportedserial.w"

QScriptContext*context= scriptengine->currentContext();
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= scriptengine->evaluate(deviceScript);
QScriptEngine*engine= scriptengine;
/*182:*/
#line 4292 "./typica.w"

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

/*:182*/
#line 382 "./unsupportedserial.w"

context->setThisObject(oldThis);
}

/*:873*//*878:*/
#line 446 "./unsupportedserial.w"

void JavaScriptDevice::stop()
{
emit deviceStopRequested();
}

/*:878*//*879:*/
#line 459 "./unsupportedserial.w"

JavaScriptDevice::JavaScriptDevice(const QModelIndex&index,
QScriptEngine*engine):
QObject(NULL),scriptengine(engine)
{
DeviceTreeModel*model= (DeviceTreeModel*)(index.model());
QDomElement deviceReferenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList deviceConfigData= deviceReferenceElement.elementsByTagName("attribute");
QDomElement node;
QStringList deviceKeys;
QStringList deviceValues;
for(int i= 0;i<deviceConfigData.size();i++)
{
node= deviceConfigData.at(i).toElement();
if(node.attribute("name")=="keys")
{
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
deviceKeys= data.split(", ");
}
else if(node.attribute("name")=="values")
{
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
deviceValues= data.split(", ");
}
else if(node.attribute("name")=="script")
{
deviceScript= node.attribute("value");
}
deviceSettings.insert(node.attribute("name"),node.attribute("value"));
}
for(int i= 0;i<qMin(deviceKeys.length(),deviceValues.length());i++)
{
deviceSettings.insert(deviceKeys[i],deviceValues[i]);
}
if(model->hasChildren(index))
{
for(int i= 0;i<model->rowCount(index);i++)
{
QModelIndex channelIndex= model->index(i,0,index);
QDomElement channelReference= model->referenceElement(model->data(channelIndex,32).toString());
channelList.append(new Channel);
QDomElement channelReferenceElement= 
model->referenceElement(model->data(channelIndex,Qt::UserRole).toString());
QDomNodeList channelConfigData= 
channelReferenceElement.elementsByTagName("attribute");
QStringList channelKeys;
QStringList channelValues;
for(int j= 0;j<channelConfigData.size();j++)
{
node= channelConfigData.at(j).toElement();
if(node.attribute("name")=="keys")
{
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
channelKeys= data.split(", ");
}
else if(node.attribute("name")=="values")
{
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
channelValues= data.split(", ");
}
else if(node.attribute("name")=="hidden")
{
hiddenState.append(node.attribute("value")=="true");
}
else if(node.attribute("name")=="columnname")
{
columnNames.append(node.attribute("value"));
}
}
QVariantMap cs;
for(int j= 0;j<qMin(channelKeys.length(),channelValues.length());j++)
{
cs.insert(channelKeys[j],channelValues[j]);
}
channelSettings.append(cs);
indicatorTexts.append(model->data(channelIndex,Qt::DisplayRole).toString());
channelUnits.append(Units::Fahrenheit);
}
}
}

/*:879*//*880:*/
#line 564 "./unsupportedserial.w"

int JavaScriptDevice::channelCount()
{
return channelList.length();
}

Channel*JavaScriptDevice::getChannel(int channel)
{
return channelList.at(channel);
}

bool JavaScriptDevice::isChannelHidden(int channel)
{
return hiddenState.at(channel);
}

Units::Unit JavaScriptDevice::expectedChannelUnit(int channel)
{
return channelUnits.at(channel);
}

QString JavaScriptDevice::channelColumnName(int channel)
{
if(channel>=0&&channel<columnNames.length())
{
return columnNames.at(channel);
}
return QString();
}

QString JavaScriptDevice::channelIndicatorText(int channel)
{
return indicatorTexts.at(channel);
}

/*:880*//*881:*/
#line 601 "./unsupportedserial.w"

void JavaScriptDevice::setTemperatureColumn(int tcol)
{
annotationTemperatureColumn= tcol;
}

void JavaScriptDevice::setAnnotationColumn(int ncol)
{
annotationNoteColumn= ncol;
}

/*:881*/
#line 641 "./unsupportedserial.w"


/*:885*//*911:*/
#line 444 "./phidgets.w"

/*895:*/
#line 31 "./phidgets.w"

PhidgetsTemperatureSensorConfWidget::PhidgetsTemperatureSensorConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QPushButton*addChannelButton= new QPushButton(tr("Add Channel"));
QSpinBox*sampleRate= new QSpinBox;
sampleRate->setMinimum(40);
sampleRate->setMaximum(600);
sampleRate->setSingleStep(40);
sampleRate->setValue(360);

/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 44 "./phidgets.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="sampleRate")
{
sampleRate->setValue(node.attribute("value").toInt());
}
}
updateRate(sampleRate->value());

connect(sampleRate,SIGNAL(valueChanged(int)),this,SLOT(updateRate(int)));
connect(addChannelButton,SIGNAL(clicked()),this,SLOT(addChannel()));

layout->addRow(addChannelButton);
layout->addRow(tr("Sample rate:"),sampleRate);
setLayout(layout);
}

/*:895*//*896:*/
#line 66 "./phidgets.w"

void PhidgetsTemperatureSensorConfWidget::addChannel()
{
insertChildNode(tr("Channel"),"phidgets1048channel");
}

/*:896*//*897:*/
#line 74 "./phidgets.w"

void PhidgetsTemperatureSensorConfWidget::updateRate(int ms)
{
updateAttribute("sampleRate",QString("%1").arg(ms));
}

/*:897*//*899:*/
#line 103 "./phidgets.w"

PhidgetTemperatureSensorChannelConfWidget::PhidgetTemperatureSensorChannelConfWidget(
DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),
tcType(new QComboBox)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*columnName= new QLineEdit;
layout->addRow(tr("Column Name:"),columnName);
QCheckBox*hideSeries= new QCheckBox("Hide this channel");
layout->addRow(hideSeries);
layout->addRow(tr("Thermocouple Type:"),tcType);
tcType->addItem("Type K","1");
tcType->addItem("Type J","2");
tcType->addItem("Type E","3");
tcType->addItem("Type T","4");
QSpinBox*channel= new QSpinBox;
layout->addRow(tr("Channel:"),channel);
channel->setMinimum(0);
channel->setMaximum(3);
setLayout(layout);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 124 "./phidgets.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="columnname")
{
columnName->setText(node.attribute("value"));
}
else if(node.attribute("name")=="hidden")
{
hideSeries->setChecked(node.attribute("value")=="true");
}
else if(node.attribute("name")=="tctype")
{
tcType->setCurrentIndex(tcType->findData(node.attribute("value")));
}
else if(node.attribute("name")=="channel")
{
channel->setValue(node.attribute("value").toInt());
}
}
updateColumnName(columnName->text());
updateHidden(hideSeries->isChecked());
updateTC(tcType->currentIndex());
updateChannel(channel->value());
connect(columnName,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
connect(hideSeries,SIGNAL(toggled(bool)),this,SLOT(updateHidden(bool)));
connect(tcType,SIGNAL(currentIndexChanged(int)),this,SLOT(updateTC(int)));
connect(channel,SIGNAL(valueChanged(int)),this,SLOT(updateChannel(int)));
}

/*:899*//*900:*/
#line 157 "./phidgets.w"

void PhidgetTemperatureSensorChannelConfWidget::updateColumnName(const QString&value)
{
updateAttribute("columnname",value);
}

void PhidgetTemperatureSensorChannelConfWidget::updateHidden(bool hidden)
{
updateAttribute("hidden",hidden?"true":"false");
}

void PhidgetTemperatureSensorChannelConfWidget::updateTC(int index)
{
updateAttribute("tctype",tcType->itemData(index).toString());
}

void PhidgetTemperatureSensorChannelConfWidget::updateChannel(int channel)
{
updateAttribute("channel",QString("%1").arg(channel));
}

/*:900*//*904:*/
#line 246 "./phidgets.w"

PhidgetsTemperatureSensor::PhidgetsTemperatureSensor(const QModelIndex&index)
:QObject(NULL),driver("phidget21"),device(NULL)
{
DeviceTreeModel*model= (DeviceTreeModel*)(index.model());
QDomElement deviceReferenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList deviceConfigData= deviceReferenceElement.elementsByTagName("attribute");
QDomElement node;
for(int i= 0;i<deviceConfigData.size();i++)
{
node= deviceConfigData.at(i).toElement();
if(node.attribute("name")=="sampleRate")
{
sampleTimer.setInterval(node.attribute("value").toInt());
}
}
if(model->hasChildren(index))
{
for(int i= 0;i<model->rowCount(index);i++)
{
QModelIndex channelIndex= model->index(i,0,index);
QDomElement channelReference= model->referenceElement(model->data(channelIndex,32).toString());
QDomElement channelReferenceElement= model->referenceElement(model->data(channelIndex,Qt::UserRole).toString());
QDomNodeList channelConfigData= channelReferenceElement.elementsByTagName("attribute");
for(int j= 0;j<channelConfigData.size();j++)
{
node= channelConfigData.at(j).toElement();
if(node.attribute("name")=="channel")
{
int channelID= node.attribute("value").toInt();
channelIndices.append(channelID);
Channel*channel= new Channel;
channelList.append(channel);
channelMap.insert(channelID,channel);
}
else if(node.attribute("name")=="hidden")
{
hiddenState.append(node.attribute("value")=="true");
}
else if(node.attribute("name")=="columnname")
{
columnNames.append(node.attribute("value"));
}
else if(node.attribute("name")=="tctype")
{
tctypes.append(node.attribute("value").toInt());
}
}
indicatorTexts.append(model->data(channelIndex,Qt::DisplayRole).toString());
}
}
}

/*:904*//*905:*/
#line 306 "./phidgets.w"

int PhidgetsTemperatureSensor::channelCount()
{
return channelList.length();
}

Channel*PhidgetsTemperatureSensor::getChannel(int channel)
{
return channelList.at(channel);
}

/*:905*//*906:*/
#line 319 "./phidgets.w"

bool PhidgetsTemperatureSensor::isChannelHidden(int channel)
{
return hiddenState.at(channel);
}

QString PhidgetsTemperatureSensor::channelColumnName(int channel)
{
if(channel>=0&&channel<columnNames.length())
{
return columnNames.at(channel);
}
return QString();
}

QString PhidgetsTemperatureSensor::channelIndicatorText(int channel)
{
if(channel>=0&&channel<indicatorTexts.length())
{
return indicatorTexts.at(channel);
}
return QString();
}

/*:906*//*908:*/
#line 371 "./phidgets.w"

void PhidgetsTemperatureSensor::start()
{
if(!driver.load())
{
driver.setFileName("Phidget21.framework/Phidget21");
if(!driver.load())
{
QMessageBox::critical(NULL,tr("Typica: Driver not found"),
tr("Failed to find phidget21. Please install it."));
return;
}
}
if((createDevice= (PhidgetHandleOnly)driver.resolve("CPhidgetTemperatureSensor_create"))==0||
(openDevice= (PhidgetHandleInt)driver.resolve("CPhidget_open"))==0||
(waitForOpen= (PhidgetHandleInt)driver.resolve("CPhidget_waitForAttachment"))==0||
(setTCType= (PhidgetHandleIntInt)driver.resolve("CPhidgetTemperatureSensor_setThermocoupleType"))==0||
(getTemperature= (PhidgetHandleIntDoubleOut)driver.resolve("CPhidgetTemperatureSensor_getTemperature"))==0||
(closeDevice= (PhidgetHandleOnly)driver.resolve("CPhidget_close"))==0||
(deleteDevice= (PhidgetHandleOnly)driver.resolve("CPhidget_delete"))==0)
{
QMessageBox::critical(NULL,tr("Typica: Link error"),
tr("Failed to link a required symbol in phidget21."));
return;
}
createDevice(&device);
openDevice(device,-1);
int error;
if((error= waitForOpen(device,10000)))
{
closeDevice(device);
deleteDevice(device);
QMessageBox::critical(NULL,tr("Typica: Failed to Open Device"),
tr("CPhidget_waitForAttachment returns error %n",0,error));
return;
}
for(int i= 0;i<channelIndices.length();i++)
{
setTCType(device,channelIndices.at(i),tctypes.at(i));
}
connect(&sampleTimer,SIGNAL(timeout()),this,SLOT(getMeasurements()));
sampleTimer.start();
}

/*:908*//*909:*/
#line 418 "./phidgets.w"

void PhidgetsTemperatureSensor::getMeasurements()
{
double value= 0.0;
QTime time= QTime::currentTime();
foreach(int i,channelIndices)
{
getTemperature(device,i,&value);
Measurement measure(value*9.0/5.0+32.0,time);
channelMap[i]->input(measure);
}
}

/*:909*//*910:*/
#line 433 "./phidgets.w"

void PhidgetsTemperatureSensor::stop()
{
sampleTimer.stop();
closeDevice(device);
deleteDevice(device);
driver.unload();
}

/*:910*/
#line 445 "./phidgets.w"


/*:911*//*925:*/
#line 19311 "./typica.w"

/*923:*/
#line 19273 "./typica.w"

CoolingTimerConfWidget::CoolingTimerConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QHBoxLayout*layout= new QHBoxLayout;
QLabel*label= new QLabel(tr("Cooling Time: "));
QTimeEdit*editor= new QTimeEdit;
editor->setDisplayFormat("mm:ss");
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 19282 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="reset")
{
editor->setTime(QTime::fromString(node.attribute("value"),"mm:ss"));
}
}
updateResetTime(editor->time());
connect(editor,SIGNAL(timeChanged(QTime)),
this,SLOT(updateResetTime(QTime)));
layout->addWidget(label);
layout->addWidget(editor);
setLayout(layout);
}

void CoolingTimerConfWidget::updateResetTime(QTime time)
{
updateAttribute("reset",time.toString("mm:ss"));
}

/*:923*/
#line 19312 "./typica.w"


/*:925*//*930:*/
#line 19570 "./typica.w"

/*927:*/
#line 19344 "./typica.w"

RangeTimerConfWidget::RangeTimerConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QVBoxLayout*layout= new QVBoxLayout;

QGroupBox*startConfigurationGroup= new QGroupBox(tr("Start trigger"));
QRadioButton*startBatchOption= new QRadioButton(tr("Start of batch"));
QRadioButton*buttonOption= new QRadioButton(tr("Manual"));
QRadioButton*thresholdOption= new QRadioButton(tr("At temperature"));
QButtonGroup*startOptionGroup= new QButtonGroup;
startOptionGroup->addButton(startBatchOption,1);
startOptionGroup->addButton(buttonOption,2);
startOptionGroup->addButton(thresholdOption,3);
startBatchOption->setChecked(true);
QGridLayout*startOptions= new QGridLayout;
startOptions->addWidget(startBatchOption,0,0);
startOptions->addWidget(buttonOption,1,0);
startOptions->addWidget(thresholdOption,2,0);
QLabel*buttonTextLabel= new QLabel(tr("Button Text: "));
QLineEdit*buttonTextEdit= new QLineEdit;
QHBoxLayout*buttonTextOptions= new QHBoxLayout;
buttonTextOptions->addWidget(buttonTextLabel);
buttonTextOptions->addWidget(buttonTextEdit);
startOptions->addLayout(buttonTextOptions,1,1);
QFormLayout*thresholdOptions= new QFormLayout;
QLineEdit*startColumnName= new QLineEdit;
QLineEdit*startValue= new QLineEdit;
thresholdOptions->addRow(tr("Column Name: "),startColumnName);
thresholdOptions->addRow(tr("Value: "),startValue);
startOptions->addLayout(thresholdOptions,2,1);
startConfigurationGroup->setLayout(startOptions);
layout->addWidget(startConfigurationGroup);

QGroupBox*stopConfigurationGroup= new QGroupBox(tr("Stop trigger"));
QRadioButton*stopBatchOption= new QRadioButton(tr("End of batch"));
QRadioButton*stopButtonOption= new QRadioButton(tr("Manual"));
QRadioButton*stopThresholdOption= new QRadioButton(tr("At temperature"));
QButtonGroup*stopOptionGroup= new QButtonGroup;
stopOptionGroup->addButton(stopBatchOption,1);
stopOptionGroup->addButton(stopButtonOption,2);
stopOptionGroup->addButton(stopThresholdOption,3);
stopBatchOption->setChecked(true);
QGridLayout*stopOptions= new QGridLayout;
stopOptions->addWidget(stopBatchOption,0,0);
stopOptions->addWidget(stopButtonOption,1,0);
stopOptions->addWidget(stopThresholdOption,2,0);
QLabel*stopButtonLabel= new QLabel(tr("Button Text: "));
QLineEdit*stopButtonEdit= new QLineEdit;
QHBoxLayout*stopButtonTextOptions= new QHBoxLayout;
stopButtonTextOptions->addWidget(stopButtonLabel);
stopButtonTextOptions->addWidget(stopButtonEdit);
stopOptions->addLayout(stopButtonTextOptions,1,1);
QLineEdit*stopColumnName= new QLineEdit;
QLineEdit*stopValue= new QLineEdit;
QFormLayout*stopThresholdOptions= new QFormLayout;
stopThresholdOptions->addRow(tr("Column Name: "),stopColumnName);
stopThresholdOptions->addRow(tr("Value: "),stopValue);
stopOptions->addLayout(stopThresholdOptions,2,1);
stopConfigurationGroup->setLayout(stopOptions);
layout->addWidget(stopConfigurationGroup);

/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 19406 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="startbuttontext")
{
buttonTextEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="stopbuttontext")
{
stopButtonEdit->setText(node.attribute("value"));
}
else if(node.attribute("name")=="startcolumnname")
{
startColumnName->setText(node.attribute("value"));
}
else if(node.attribute("name")=="stopcolumnname")
{
stopColumnName->setText(node.attribute("value"));
}
else if(node.attribute("name")=="startvalue")
{
startValue->setText(node.attribute("value"));
}
else if(node.attribute("name")=="stopvalue")
{
stopValue->setText(node.attribute("value"));
}
else if(node.attribute("name")=="starttrigger")
{
if(node.attribute("value")=="batch")
{
startBatchOption->setChecked(true);
}
else if(node.attribute("value")=="manual")
{
buttonOption->setChecked(true);
}
else if(node.attribute("value")=="value")
{
thresholdOption->setChecked(true);
}
}
else if(node.attribute("name")=="stoptrigger")
{
if(node.attribute("value")=="batch")
{
stopBatchOption->setChecked(true);
}
else if(node.attribute("value")=="manual")
{
stopButtonOption->setChecked(true);
}
else if(node.attribute("value")=="value")
{
stopThresholdOption->setChecked(true);
}
}
}
updateStartButtonText(buttonTextEdit->text());
updateStopButtonText(stopButtonEdit->text());
updateStartColumnName(startColumnName->text());
updateStopColumnName(stopColumnName->text());
updateStartValue(startValue->text());
updateStopValue(stopValue->text());
updateStartTrigger(startOptionGroup->checkedId());
updateStopTrigger(stopOptionGroup->checkedId());

setLayout(layout);

connect(buttonTextEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateStartButtonText(QString)));
connect(stopButtonEdit,SIGNAL(textChanged(QString)),
this,SLOT(updateStopButtonText(QString)));
connect(startColumnName,SIGNAL(textChanged(QString)),
this,SLOT(updateStartColumnName(QString)));
connect(stopColumnName,SIGNAL(textChanged(QString)),
this,SLOT(updateStopColumnName(QString)));
connect(startValue,SIGNAL(textChanged(QString)),
this,SLOT(updateStartValue(QString)));
connect(stopValue,SIGNAL(textChanged(QString)),
this,SLOT(updateStopValue(QString)));
connect(startOptionGroup,SIGNAL(buttonClicked(int)),
this,SLOT(updateStartTrigger(int)));
connect(stopOptionGroup,SIGNAL(buttonClicked(int)),
this,SLOT(updateStopTrigger(int)));
}

/*:927*//*928:*/
#line 19496 "./typica.w"

void RangeTimerConfWidget::updateStartButtonText(const QString&text)
{
updateAttribute("startbuttontext",text);
}

void RangeTimerConfWidget::updateStopButtonText(const QString&text)
{
updateAttribute("stopbuttontext",text);
}

void RangeTimerConfWidget::updateStartColumnName(const QString&text)
{
updateAttribute("startcolumnname",text);
}

void RangeTimerConfWidget::updateStopColumnName(const QString&text)
{
updateAttribute("stopcolumnname",text);
}

void RangeTimerConfWidget::updateStartValue(const QString&text)
{
updateAttribute("startvalue",text);
}

void RangeTimerConfWidget::updateStopValue(const QString&text)
{
updateAttribute("stopvalue",text);
}

void RangeTimerConfWidget::updateStartTrigger(int option)
{
switch(option)
{
case 1:
updateAttribute("starttrigger","batch");
break;
case 2:
updateAttribute("starttrigger","manual");
break;
case 3:
updateAttribute("starttrigger","value");
break;
default:
break;
}
}

void RangeTimerConfWidget::updateStopTrigger(int option)
{
switch(option)
{
case 1:
updateAttribute("stoptrigger","batch");
break;
case 2:
updateAttribute("stoptrigger","manual");
break;
case 3:
updateAttribute("stoptrigger","value");
break;
default:
break;
}
}

/*:928*/
#line 19571 "./typica.w"


/*:930*//*935:*/
#line 19671 "./typica.w"

/*932:*/
#line 19595 "./typica.w"

MultiRangeTimerConfWidget::MultiRangeTimerConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index),tablemodel(new SaltModel(2))
{
QFormLayout*layout= new QFormLayout;
QLineEdit*trigger= new QLineEdit;
layout->addRow(tr("Trigger column name:"),trigger);
tablemodel->setHeaderData(0,Qt::Horizontal,"Range Name");
tablemodel->setHeaderData(1,Qt::Horizontal,"End Temperature");
QTableView*rangeTable= new QTableView;
rangeTable->setModel(tablemodel);
layout->addRow(tr("Range data:"),rangeTable);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 19608 "./typica.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="trigger")
{
trigger->setText(node.attribute("value"));
}
else if(node.attribute("name")=="rangenames")
{
QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(", ");
for(int j= 0;j<itemList.size();j++)
{
QString item= itemList.at(j);
item.chop(1);
item= item.remove(0,1);
tablemodel->setData(tablemodel->index(j,0),
QVariant(item),Qt::DisplayRole);
}
}
else if(node.attribute("name")=="endtemps")
{
/*918:*/
#line 19203 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:918*/
#line 19636 "./typica.w"

int column= 1;
/*919:*/
#line 19215 "./typica.w"

for(int j= 0;j<itemList.size();j++)
{
tablemodel->setData(tablemodel->index(j,column),
QVariant(itemList.at(j).toDouble()),
Qt::DisplayRole);
}

/*:919*/
#line 19638 "./typica.w"

}
}
updateColumnName(trigger->text());
updateRangeData();
connect(trigger,SIGNAL(textEdited(QString)),this,SLOT(updateColumnName(QString)));
connect(tablemodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateRangeData()));
setLayout(layout);
}

/*:932*//*933:*/
#line 19652 "./typica.w"

void MultiRangeTimerConfWidget::updateRangeData()
{
updateAttribute("rangenames",tablemodel->quotedArrayLiteral(0,Qt::DisplayRole));
updateAttribute("endtemps",tablemodel->arrayLiteral(1,Qt::DisplayRole));
}

void MultiRangeTimerConfWidget::updateColumnName(const QString&text)
{
updateAttribute("trigger",text);
}

/*:933*/
#line 19672 "./typica.w"


/*:935*//*953:*/
#line 265 "./rate.w"

/*949:*/
#line 191 "./rate.w"

RateOfChangeConfWidget::RateOfChangeConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*column= new QLineEdit;
layout->addRow(tr("Primary series column name:"),column);
QSpinBox*cacheTime= new QSpinBox;
cacheTime->setMinimum(0);
cacheTime->setMaximum(300);
layout->addRow(tr("Cache time:"),cacheTime);
QSpinBox*scaleTime= new QSpinBox;
scaleTime->setMinimum(1);
scaleTime->setMaximum(300);
layout->addRow(tr("Scale time:"),scaleTime);
/*764:*/
#line 16136 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:764*/
#line 206 "./rate.w"

for(int i= 0;i<configData.size();i++)
{
node= configData.at(i).toElement();
if(node.attribute("name")=="column")
{
column->setText(node.attribute("value"));
}
else if(node.attribute("name")=="cache")
{
cacheTime->setValue(node.attribute("value").toInt());
}
else if(node.attribute("name")=="scale")
{
scaleTime->setValue(node.attribute("value").toInt());
}
}
updateColumn(column->text());
updateCacheTime(cacheTime->text());
updateScaleTime(scaleTime->text());
connect(column,SIGNAL(textEdited(QString)),this,SLOT(updateColumn(QString)));
connect(cacheTime,SIGNAL(valueChanged(QString)),this,SLOT(updateCacheTime(QString)));
connect(scaleTime,SIGNAL(valueChanged(QString)),this,SLOT(updateScaleTime(QString)));
setLayout(layout);
}

/*:949*//*950:*/
#line 235 "./rate.w"

void RateOfChangeConfWidget::updateColumn(const QString&column)
{
updateAttribute("column",column);
}

void RateOfChangeConfWidget::updateCacheTime(const QString&seconds)
{
updateAttribute("cache",seconds);
}

void RateOfChangeConfWidget::updateScaleTime(const QString&seconds)
{
updateAttribute("scale",seconds);
}

/*:950*/
#line 266 "./rate.w"

#line 19764 "./typica.w"

#line 1 "./dataqsdk.w"
/*:953*/
#line 529 "./typica.w"

/*8:*/
#line 671 "./typica.w"

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

template<> QByteArray getself(QScriptContext*context)
{
QByteArray self= context->thisObject().toVariant().toByteArray();
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

/*:8*//*9:*/
#line 722 "./typica.w"

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

template<> double argument(int arg,QScriptContext*context)
{
return(double)(context->argument(arg).toNumber());
}

template<> Units::Unit argument(int arg,QScriptContext*context)
{
return(Units::Unit)(context->argument(arg).toInt32());
}

template<> QByteArray argument(int arg,QScriptContext*context)
{
return qscriptvalue_cast<QByteArray> (context->argument(arg));
}

/*:9*//*13:*/
#line 814 "./typica.w"

void setQObjectProperties(QScriptValue,QScriptEngine*)
{

}

/*:13*//*15:*/
#line 828 "./typica.w"

void setQPaintDeviceProperties(QScriptValue,QScriptEngine*)
{

}

void setQLayoutItemProperties(QScriptValue,QScriptEngine*)
{

}

/*:15*//*18:*/
#line 867 "./typica.w"

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

/*:18*//*19:*/
#line 889 "./typica.w"

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

/*:19*//*21:*/
#line 971 "./typica.w"

ScriptQMainWindow::ScriptQMainWindow():QMainWindow(NULL),
cprompt(tr("Closing this window may result in loss of data. Continue?"))
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
/*26:*/
#line 1083 "./typica.w"

QSettings settings;
restoreGeometry(settings.value(QString("geometries/%1").arg(objectName())).
toByteArray());

/*:26*/
#line 1011 "./typica.w"

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

/*:21*//*22:*/
#line 1032 "./typica.w"

void ScriptQMainWindow::closeEvent(QCloseEvent*event)
{
if(isWindowModified()){
/*23:*/
#line 1046 "./typica.w"

QMessageBox::StandardButton result;
result= QMessageBox::warning(this,"Typica",closePrompt(),
QMessageBox::Ok|QMessageBox::Cancel);
if(result==QMessageBox::Cancel)
{
event->ignore();
return;
}

/*:23*/
#line 1036 "./typica.w"

}
emit aboutToClose();
/*25:*/
#line 1077 "./typica.w"

QSettings settings;
settings.setValue(QString("geometries/%1").arg(objectName()),saveGeometry());

/*:25*/
#line 1039 "./typica.w"

event->accept();
}

/*:22*//*24:*/
#line 1058 "./typica.w"

QString ScriptQMainWindow::closePrompt()
{
return cprompt;
}

void ScriptQMainWindow::setClosePrompt(QString prompt)
{
cprompt= prompt;
}

/*:24*//*29:*/
#line 1111 "./typica.w"

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

/*:29*//*30:*/
#line 1133 "./typica.w"

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

/*:30*//*31:*/
#line 1167 "./typica.w"

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

/*:31*//*33:*/
#line 1197 "./typica.w"

void setQMenuBarProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("addMenu",engine->newFunction(QMenuBar_addMenu));
}

/*:33*//*34:*/
#line 1212 "./typica.w"

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

/*:34*//*36:*/
#line 1242 "./typica.w"

void setQMenuProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("addAction",engine->newFunction(QMenu_addAction));
value.setProperty("addSeparator",engine->newFunction(QMenu_addSeparator));
}

/*:36*//*37:*/
#line 1252 "./typica.w"

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

/*:37*//*40:*/
#line 1314 "./typica.w"

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

/*:40*//*43:*/
#line 1348 "./typica.w"

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

/*:43*//*46:*/
#line 1385 "./typica.w"

QScriptValue constructQLineEdit(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QLineEdit());
setQLineEditProperties(object,engine);
return object;
}

/*:46*//*47:*/
#line 1396 "./typica.w"

void setQLineEditProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:47*//*50:*/
#line 1432 "./typica.w"

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
value.setProperty("count",engine->newFunction(QSplitter_count));
}

/*:50*//*51:*/
#line 1453 "./typica.w"

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

/*:51*//*52:*/
#line 1490 "./typica.w"

QScriptValue QSplitter_count(QScriptContext*context,QScriptEngine*)
{
QSplitter*self= getself<QSplitter*> (context);
return QScriptValue(self->count());
}

/*:52*//*53:*/
#line 1503 "./typica.w"

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

/*:53*//*55:*/
#line 1556 "./typica.w"

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

/*:55*//*58:*/
#line 1623 "./typica.w"

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

/*:58*//*59:*/
#line 1674 "./typica.w"

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

/*:59*//*62:*/
#line 1738 "./typica.w"

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

/*:62*//*65:*/
#line 1796 "./typica.w"

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

/*:65*//*66:*/
#line 1832 "./typica.w"

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

/*:66*//*67:*/
#line 1869 "./typica.w"

void setQFileDialogProperties(QScriptValue value,QScriptEngine*engine)
{
setQDialogProperties(value,engine);
}

void setQDialogProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:67*//*70:*/
#line 1910 "./typica.w"

QScriptValue constructQFile(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new QFile(argument<QString> (0,context)));
setQFileProperties(object,engine);
return object;
}

/*:70*//*71:*/
#line 1921 "./typica.w"

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

/*:71*//*72:*/
#line 1943 "./typica.w"

void setQIODeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("open",engine->newFunction(QIODevice_open));
value.setProperty("close",engine->newFunction(QIODevice_close));
value.setProperty("readToString",
engine->newFunction(QIODevice_readToString));
value.setProperty("putChar",engine->newFunction(QIODevice_putChar));
value.setProperty("writeString",engine->newFunction(QIODevice_writeString));
value.setProperty("writeBytes",engine->newFunction(QIODevice_writeBytes));
value.setProperty("readBytes",engine->newFunction(QIODevice_readBytes));
value.setProperty("peek",engine->newFunction(QIODevice_peek));
value.setProperty("read",engine->newFunction(QIODevice_read));
}

/*:72*//*73:*/
#line 1964 "./typica.w"

QScriptValue QIODevice_open(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
bool retval= false;
if(context->argumentCount()==1)
{
switch(argument<int> (0,context))
{
case 1:
retval= self->open(QIODevice::ReadOnly);
break;
case 2:
retval= self->open(QIODevice::WriteOnly);
break;
case 3:
retval= self->open(QIODevice::ReadWrite);
break;
default:
break;
}
}
else
{
retval= self->open(QIODevice::ReadWrite);
}
return QScriptValue(retval);
}

QScriptValue QIODevice_close(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
self->close();
return QScriptValue();
}

/*:73*//*74:*/
#line 2004 "./typica.w"

QScriptValue QIODevice_readToString(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
self->reset();
return QScriptValue(QString(self->readAll()));
}

/*:74*//*75:*/
#line 2020 "./typica.w"

QScriptValue QIODevice_putChar(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
if(context->argumentCount()==1)
{
return QScriptValue(self->putChar(argument<QString> (0,context).toUtf8().at(0)));
}
context->throwError("Incorrect number of arguments passed to "
"QIODevice::putChar()");
return QScriptValue();
}

/*:75*//*76:*/
#line 2038 "./typica.w"

QScriptValue QIODevice_writeString(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
if(context->argumentCount()==1)
{
self->write(argument<QString> (0,context).toUtf8());
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QIODevice::writeString()");
}
return QScriptValue();
}

QScriptValue QIODevice_writeBytes(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
if(context->argumentCount()==1)
{
self->write(argument<QByteArray> (0,context));
}
else
{
context->throwError("Incorrect number of arguments passed to "
"QIODevice::writeBytes()");
}
return QScriptValue();
}

/*:76*//*77:*/
#line 2072 "./typica.w"

QScriptValue QIODevice_readBytes(QScriptContext*context,QScriptEngine*engine)
{
QIODevice*self= getself<QIODevice*> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (self->readAll());
setQByteArrayProperties(value,engine);
return value;
}

/*:77*//*78:*/
#line 2083 "./typica.w"

QScriptValue QIODevice_peek(QScriptContext*context,QScriptEngine*engine)
{
QIODevice*self= getself<QIODevice*> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (
self->peek(argument<int> (0,context)));
setQByteArrayProperties(value,engine);
return value;
}

QScriptValue QIODevice_read(QScriptContext*context,QScriptEngine*engine)
{
QIODevice*self= getself<QIODevice*> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (
self->read(argument<int> (0,context)));
setQByteArrayProperties(value,engine);
return value;
}

/*:78*//*81:*/
#line 2128 "./typica.w"

QScriptValue constructQProcess(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QProcess);
setQProcessProperties(object,engine);
return object;
}

/*:81*//*82:*/
#line 2139 "./typica.w"

void setQProcessProperties(QScriptValue value,QScriptEngine*engine)
{
setQIODeviceProperties(value,engine);
value.setProperty("execute",engine->newFunction(QProcess_execute));
value.setProperty("startDetached",engine->newFunction(QProcess_startDetached));
value.setProperty("setWorkingDirectory",engine->newFunction(QProcess_setWorkingDirectory));
value.setProperty("start",engine->newFunction(QProcess_start));
}

/*:82*//*83:*/
#line 2153 "./typica.w"

QScriptValue QProcess_execute(QScriptContext*context,QScriptEngine*)
{
QProcess*self= getself<QProcess*> (context);
QString program= argument<QString> (0,context);
QStringList arguments= QStringList();
if(context->argumentCount()> 1){
arguments= argument<QVariant> (1,context).toStringList();
}
int retval= self->execute(program,arguments);
return QScriptValue(retval);
}

/*:83*//*84:*/
#line 2168 "./typica.w"

QScriptValue QProcess_startDetached(QScriptContext*context,QScriptEngine*)
{
QProcess*self= getself<QProcess*> (context);
QString program= argument<QString> (0,context);
QStringList arguments= QStringList();
if(context->argumentCount()> 1){
arguments= argument<QVariant> (1,context).toStringList();
}
QString workingDirectory= "";
if(context->argumentCount()> 2){
workingDirectory= argument<QString> (2,context);
}
bool retval;
switch(context->argumentCount())
{
case 1:
retval= self->startDetached(program);
break;
case 2:
retval= self->startDetached(program,arguments);
break;
case 3:
retval= self->startDetached(program,arguments,workingDirectory);
break;
default:
retval= false;
}
return QScriptValue(retval);
}

/*:84*//*85:*/
#line 2201 "./typica.w"

QScriptValue QProcess_setWorkingDirectory(QScriptContext*context,QScriptEngine*)
{
QProcess*self= getself<QProcess*> (context);
QString directory= argument<QString> (0,context);
self->setWorkingDirectory(directory);
return QScriptValue();
}

/*:85*//*86:*/
#line 2213 "./typica.w"

QScriptValue QProcess_start(QScriptContext*context,QScriptEngine*)
{
QProcess*self= getself<QProcess*> (context);
QString program= argument<QString> (0,context);
QStringList arguments= QStringList();
if(context->argumentCount()> 1){
arguments= argument<QVariant> (1,context).toStringList();
}
self->start(program,arguments);
return QScriptValue();
}

/*:86*//*88:*/
#line 2254 "./typica.w"

QScriptValue QByteArray_toScriptValue(QScriptEngine*engine,const QByteArray&bytes)
{
QScriptValue object= engine->newVariant(QVariant(bytes));
setQByteArrayProperties(object,engine);
return object;
}

void QByteArray_fromScriptValue(const QScriptValue&value,QByteArray&bytes)
{
bytes= value.toVariant().toByteArray();
}

/*:88*//*90:*/
#line 2277 "./typica.w"

QScriptValue constructQByteArray(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->toScriptValue<QByteArray> (QByteArray());
setQByteArrayProperties(object,engine);
return object;
}

/*:90*//*91:*/
#line 2288 "./typica.w"

void setQByteArrayProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("fromHex",engine->newFunction(QByteArray_fromHex));
value.setProperty("getAt",engine->newFunction(QByteArray_getAt));
value.setProperty("setAt",engine->newFunction(QByteArray_setAt));
value.setProperty("appendBytes",engine->newFunction(QByteArray_appendBytes));
value.setProperty("appendString",engine->newFunction(QByteArray_appendString));
value.setProperty("size",engine->newFunction(QByteArray_size));
value.setProperty("left",engine->newFunction(QByteArray_left));
value.setProperty("right",engine->newFunction(QByteArray_right));
value.setProperty("mid",engine->newFunction(QByteArray_mid));
value.setProperty("chop",engine->newFunction(QByteArray_chop));
value.setProperty("remove",engine->newFunction(QByteArray_remove));
value.setProperty("toInt8",engine->newFunction(QByteArray_toInt8));
value.setProperty("toInt16",engine->newFunction(QByteArray_toInt16));
value.setProperty("toInt32",engine->newFunction(QByteArray_toInt32));
value.setProperty("toFloat",engine->newFunction(QByteArray_toFloat));
value.setProperty("toDouble",engine->newFunction(QByteArray_toDouble));
}

/*:91*//*92:*/
#line 2312 "./typica.w"

QScriptValue QByteArray_fromHex(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
QByteArray retval;
retval= self.fromHex(argument<QString> (0,context).toUtf8());
QScriptValue value= engine->toScriptValue<QByteArray> (retval);
setQByteArrayProperties(value,engine);
return value;
}

/*:92*//*93:*/
#line 2326 "./typica.w"

QScriptValue QByteArray_getAt(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
return QScriptValue((int)(self.at(argument<int> (0,context))));
}

QScriptValue QByteArray_setAt(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
self[argument<int> (0,context)]= (char)(argument<int> (1,context));
return QScriptValue();
}

/*:93*//*94:*/
#line 2344 "./typica.w"

QScriptValue QByteArray_appendBytes(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
QScriptValue value= 
engine->toScriptValue<QByteArray> (
self.append(argument<QByteArray> (0,context)));
setQByteArrayProperties(value,engine);
return value;
}

QScriptValue QByteArray_appendString(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (
self.append(argument<QString> (0,context)));
setQByteArrayProperties(value,engine);
return value;
}

/*:94*//*95:*/
#line 2366 "./typica.w"

QScriptValue QByteArray_size(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
return QScriptValue(self.size());
}

/*:95*//*96:*/
#line 2376 "./typica.w"

QScriptValue QByteArray_left(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (
self.left(argument<int> (0,context)));
setQByteArrayProperties(value,engine);
return value;
}

QScriptValue QByteArray_right(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (
self.right(argument<int> (0,context)));
setQByteArrayProperties(value,engine);
return value;
}

QScriptValue QByteArray_mid(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
int length= -1;
if(context->argumentCount()> 1)
{
length= argument<int> (1,context);
}
QScriptValue value= engine->toScriptValue<QByteArray> (
self.mid(argument<int> (0,context),length));
setQByteArrayProperties(value,engine);
return value;
}

/*:96*//*97:*/
#line 2411 "./typica.w"

QScriptValue QByteArray_chop(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
self.chop(argument<int> (0,context));
return QScriptValue();
}

QScriptValue QByteArray_remove(QScriptContext*context,QScriptEngine*engine)
{
QByteArray self= getself<QByteArray> (context);
QScriptValue value= engine->toScriptValue<QByteArray> (
self.remove(argument<int> (0,context),argument<int> (1,context)));
setQByteArrayProperties(value,engine);
return value;
}

/*:97*//*98:*/
#line 2434 "./typica.w"

QScriptValue QByteArray_toInt8(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
int value= 0;
char*bytes= (char*)&value;
bytes[0]= self[0];
return QScriptValue(value);
}

QScriptValue QByteArray_toInt16(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
int value= 0;
char*bytes= (char*)&value;
bytes[0]= self[0];
bytes[1]= self[1];
return QScriptValue(value);
}

QScriptValue QByteArray_toInt32(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
int value= 0;
char*bytes= (char*)&value;
bytes[0]= self[0];
bytes[1]= self[1];
bytes[2]= self[2];
bytes[3]= self[3];
return QScriptValue(value);
}

/*:98*//*99:*/
#line 2470 "./typica.w"

QScriptValue QByteArray_toFloat(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
float value= 0.0;
char*bytes= (char*)&value;
bytes[0]= self[0];
bytes[1]= self[1];
bytes[2]= self[2];
bytes[3]= self[3];
return QScriptValue(value);
}

QScriptValue QByteArray_toDouble(QScriptContext*context,QScriptEngine*)
{
QByteArray self= getself<QByteArray> (context);
double value= 0.0;
char*bytes= (char*)&value;
bytes[0]= self[0];
bytes[1]= self[1];
bytes[2]= self[2];
bytes[3]= self[3];
bytes[4]= self[4];
bytes[5]= self[5];
bytes[6]= self[6];
bytes[7]= self[7];
return QScriptValue(value);
}

/*:99*//*102:*/
#line 2525 "./typica.w"

QScriptValue bytesFromInt8(QScriptContext*context,QScriptEngine*engine)
{
qint8 value= (qint8)(argument<int> (0,context));
char*bytes= (char*)&value;
QByteArray retval;
retval.resize(1);
retval[0]= bytes[0];
QScriptValue v= engine->toScriptValue<QByteArray> (retval);
setQByteArrayProperties(v,engine);
return v;
}

QScriptValue bytesFromInt16(QScriptContext*context,QScriptEngine*engine)
{
qint16 value= (qint16)(argument<int> (0,context));
char*bytes= (char*)&value;
QByteArray retval;
retval.resize(2);
retval[0]= bytes[0];
retval[1]= bytes[1];
QScriptValue v= engine->toScriptValue<QByteArray> (retval);
setQByteArrayProperties(v,engine);
return v;
}

QScriptValue bytesFromInt32(QScriptContext*context,QScriptEngine*engine)
{
qint32 value= (qint32)(argument<int> (0,context));
char*bytes= (char*)&value;
QByteArray retval;
retval.resize(4);
retval[0]= bytes[0];
retval[1]= bytes[1];
retval[2]= bytes[2];
retval[3]= bytes[3];
QScriptValue v= engine->toScriptValue<QByteArray> (retval);
setQByteArrayProperties(v,engine);
return v;
}

QScriptValue bytesFromFloat(QScriptContext*context,QScriptEngine*engine)
{
float value= (float)(argument<double> (0,context));
char*bytes= (char*)&value;
QByteArray retval;
retval.resize(4);
retval[0]= bytes[0];
retval[1]= bytes[1];
retval[2]= bytes[2];
retval[3]= bytes[3];
QScriptValue v= engine->toScriptValue<QByteArray> (retval);
setQByteArrayProperties(v,engine);
return v;
}

QScriptValue bytesFromDouble(QScriptContext*context,QScriptEngine*engine)
{
double value= (double)(argument<double> (0,context));
char*bytes= (char*)&value;
QByteArray retval;
retval.resize(8);
retval[0]= bytes[0];
retval[1]= bytes[1];
retval[2]= bytes[2];
retval[3]= bytes[3];
retval[4]= bytes[4];
retval[5]= bytes[5];
retval[6]= bytes[6];
retval[7]= bytes[7];
QScriptValue v= engine->toScriptValue<QByteArray> (retval);
setQByteArrayProperties(v,engine);
return v;
}

/*:102*//*105:*/
#line 2622 "./typica.w"

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

/*:105*//*108:*/
#line 2671 "./typica.w"

QScriptValue constructXQuery(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->toScriptValue<void*> (new QXmlQuery);
setXQueryProperties(object,engine);
return object;
}

QScriptValue XQuery_invalidate(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
delete self;
return QScriptValue();
}

void setXQueryProperties(QScriptValue value,QScriptEngine*engine)
{
value.setProperty("bind",engine->newFunction(XQuery_bind));
value.setProperty("exec",engine->newFunction(XQuery_exec));
value.setProperty("setQuery",engine->newFunction(XQuery_setQuery));
value.setProperty("invalidate",engine->newFunction(XQuery_invalidate));
}

/*:108*//*109:*/
#line 2697 "./typica.w"

QScriptValue XQuery_bind(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
QIODevice*buffer= argument<QIODevice*> (1,context);
self->bindVariable(argument<QString> (0,context),buffer);
return QScriptValue();
}

/*:109*//*110:*/
#line 2708 "./typica.w"

QScriptValue XQuery_setQuery(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
self->setQuery(argument<QString> (0,context));
return QScriptValue();
}

/*:110*//*111:*/
#line 2718 "./typica.w"

QScriptValue XQuery_exec(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
QString result;
self->evaluateTo(&result);
return QScriptValue(result);
}

/*:111*//*114:*/
#line 2773 "./typica.w"

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

/*:114*//*115:*/
#line 2820 "./typica.w"

QScriptValue XmlWriter_setDevice(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
QIODevice*device= argument<QIODevice*> (0,context);
self->setDevice(device);
return QScriptValue();
}

/*:115*//*116:*/
#line 2834 "./typica.w"

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

/*:116*//*117:*/
#line 2853 "./typica.w"

QScriptValue XmlWriter_writeDTD(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeDTD(argument<QString> (0,context));
return QScriptValue();
}

/*:117*//*118:*/
#line 2864 "./typica.w"

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

/*:118*//*119:*/
#line 2900 "./typica.w"

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

/*:119*//*120:*/
#line 2921 "./typica.w"

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

/*:120*//*123:*/
#line 2980 "./typica.w"

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

/*:123*//*124:*/
#line 3010 "./typica.w"

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

/*:124*//*125:*/
#line 3030 "./typica.w"

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

/*:125*//*126:*/
#line 3051 "./typica.w"

QScriptValue XmlReader_readNext(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
self->readNext();
return QScriptValue();
}

/*:126*//*127:*/
#line 3061 "./typica.w"

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

/*:127*//*130:*/
#line 3103 "./typica.w"

void setQSettingsProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("value",engine->newFunction(QSettings_value));
value.setProperty("setValue",engine->newFunction(QSettings_setValue));
}

/*:130*//*131:*/
#line 3115 "./typica.w"

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

/*:131*//*134:*/
#line 3184 "./typica.w"

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

/*:134*//*137:*/
#line 3242 "./typica.w"

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

/*:137*//*138:*/
#line 3290 "./typica.w"

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

/*:138*//*139:*/
#line 3319 "./typica.w"

QScriptValue QTime_valueOf(QScriptContext*context,QScriptEngine*)
{
QTime self= getself<QTime> (context);
int retval= (self.hour()*60*60*1000)+(self.minute()*60*1000)+
(self.second()*1000)+self.msec();
return QScriptValue(retval);
}

/*:139*//*140:*/
#line 3333 "./typica.w"

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

/*:140*//*141:*/
#line 3376 "./typica.w"

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

/*:141*//*142:*/
#line 3397 "./typica.w"

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

/*:142*//*143:*/
#line 3417 "./typica.w"

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

/*:143*//*144:*/
#line 3473 "./typica.w"

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

/*:144*//*145:*/
#line 3511 "./typica.w"

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

/*:145*//*146:*/
#line 3550 "./typica.w"

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

/*:146*//*147:*/
#line 3586 "./typica.w"

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

/*:147*//*148:*/
#line 3622 "./typica.w"

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

/*:148*//*149:*/
#line 3643 "./typica.w"

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

/*:149*//*150:*/
#line 3674 "./typica.w"

template<> QTime argument(int arg,QScriptContext*context)
{
return qscriptvalue_cast<QTime> (context->argument(arg));
}

/*:150*//*152:*/
#line 3692 "./typica.w"

void setQAbstractScrollAreaProperties(QScriptValue value,QScriptEngine*engine)
{
setQFrameProperties(value,engine);
}

/*:152*//*154:*/
#line 3706 "./typica.w"

void setQAbstractItemViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
}

/*:154*//*156:*/
#line 3720 "./typica.w"

void setQGraphicsViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
}

void setQTableViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractItemViewProperties(value,engine);
}

/*:156*//*159:*/
#line 3753 "./typica.w"

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

/*:159*//*166:*/
#line 3865 "./typica.w"

QScriptValue constructQSqlQuery(QScriptContext*,QScriptEngine*engine)
{
SqlQueryConnection*obj= new SqlQueryConnection();
QScriptValue object= 
engine->toScriptValue<void*> (obj);
setQSqlQueryProperties(object,engine);
return object;
}

/*:166*//*167:*/
#line 3878 "./typica.w"

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

/*:167*//*168:*/
#line 3896 "./typica.w"

QScriptValue QSqlQuery_exec(QScriptContext*context,QScriptEngine*engine)
{
QSqlQuery*q= getself<SqlQueryConnection*> (context)->operator->();
QScriptValue retval;
if(context->argumentCount()==1)
{
retval= QScriptValue(engine,
q->exec(argument<QString> (0,context)));
}
else
{
retval= QScriptValue(engine,q->exec());
}
if(q->lastError().isValid())
{
qDebug()<<q->lastQuery();
qDebug()<<q->lastError().text();
}
return retval;
}

QScriptValue QSqlQuery_executedQuery(QScriptContext*context,QScriptEngine*)
{
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
return QScriptValue(query->lastQuery());
}

QScriptValue QSqlQuery_next(QScriptContext*context,QScriptEngine*engine)
{
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
return QScriptValue(engine,query->next());
}

QScriptValue QSqlQuery_value(QScriptContext*context,QScriptEngine*engine)
{
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
return QScriptValue(engine,
query->value(argument<int> (0,context)).toString());
}

/*:168*//*169:*/
#line 3940 "./typica.w"

QScriptValue QSqlQuery_prepare(QScriptContext*context,QScriptEngine*engine)
{
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
return QScriptValue(engine,query->prepare(argument<QString> (0,context)));
}

QScriptValue QSqlQuery_bind(QScriptContext*context,QScriptEngine*)
{
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
query->bindValue(argument<QString> (0,context),
argument<QVariant> (1,context));
return QScriptValue();
}

QScriptValue QSqlQuery_bindFileData(QScriptContext*context,
QScriptEngine*)
{
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
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
QSqlQuery*query= getself<SqlQueryConnection*> (context)->operator->();
QString placeholder= argument<QString> (0,context);
QIODevice*device= argument<QIODevice*> (1,context);
device->reset();
QByteArray data;
data= device->readAll();
query->bindValue(placeholder,data);
return QScriptValue();
}

/*:169*//*170:*/
#line 3992 "./typica.w"

QScriptValue QSqlQuery_invalidate(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
delete query;
return QScriptValue::UndefinedValue;
}

/*:170*//*173:*/
#line 4037 "./typica.w"

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

/*:173*//*174:*/
#line 4056 "./typica.w"

QScriptValue saveFileFromDatabase(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection h;
QSqlQuery*query= h.operator->();
QString q= "SELECT file FROM files WHERE id = :file";
query->prepare(q);
query->bindValue(":file",argument<int> (0,context));
query->exec();
query->next();
QByteArray array= query->value(0).toByteArray();
QFile file(argument<QString> (1,context));
file.open(QIODevice::WriteOnly);
file.write(array);
file.close();
return QScriptValue();
}

/*:174*//*175:*/
#line 4077 "./typica.w"

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

/*:175*//*176:*/
#line 4103 "./typica.w"

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

/*:176*//*177:*/
#line 4123 "./typica.w"

QScriptValue annotationFromRecord(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection h;
QSqlQuery*query= h.operator->();
QString q= "SELECT file FROM files WHERE id = :file";
query->prepare(q);
query->bindValue(":file",argument<int> (0,context));
query->exec();
query->next();
QByteArray array= query->value(0).toByteArray();
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

/*:177*//*178:*/
#line 4150 "./typica.w"

QScriptValue setTabOrder(QScriptContext*context,QScriptEngine*)
{
QWidget::setTabOrder(argument<QWidget*> (0,context),
argument<QWidget*> (1,context));
return QScriptValue();
}


/*:178*//*185:*/
#line 4396 "./typica.w"

QScriptValue createWindow(QScriptContext*context,QScriptEngine*engine)
{
QString targetID= argument<QString> (0,context);
QDomNode element;
QScriptValue object;
/*187:*/
#line 4443 "./typica.w"

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

/*:187*/
#line 4402 "./typica.w"

if(!element.isNull())
{
/*188:*/
#line 4475 "./typica.w"

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
/*189:*/
#line 4510 "./typica.w"

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
/*190:*/
#line 4557 "./typica.w"

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
/*633:*/
#line 13679 "./typica.w"

QSettings settings;
QString reportDirectory= QString("%1/%2").arg(settings.value("config").
toString()).
arg(element.attribute("src"));
QDir::addSearchPath("reports",reportDirectory);
QDir directory(reportDirectory);
directory.setFilter(QDir::Files);
directory.setSorting(QDir::Name);
QStringList nameFilter;
nameFilter<<"*.xml";
directory.setNameFilters(nameFilter);
QFileInfoList reportFiles= directory.entryInfoList();
for(int i= 0;i<reportFiles.size();i++)
{
QFileInfo reportFile= reportFiles.at(i);
/*637:*/
#line 13759 "./typica.w"

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
/*638:*/
#line 13786 "./typica.w"

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

/*:638*/
#line 13776 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:637*/
#line 13695 "./typica.w"

}

/*:633*/
#line 4571 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*191:*/
#line 4584 "./typica.w"

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

#line 1 "./helpmenu.w"
/*:191*/
#line 4577 "./typica.w"

}
}

/*:190*/
#line 4535 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*182:*/
#line 4292 "./typica.w"

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

/*:182*/
#line 4543 "./typica.w"

context->setThisObject(oldThis);

/*:189*/
#line 4486 "./typica.w"

}
/*192:*/
#line 9 "./helpmenu.w"

HelpMenu*helpMenu= new HelpMenu();
window->menuBar()->addMenu(helpMenu);

/*:192*/
#line 4488 "./typica.w"

window->show();

/*:188*/
#line 4405 "./typica.w"

}
return object;
}

/*:185*//*186:*/
#line 4416 "./typica.w"

QScriptValue createReport(QScriptContext*context,QScriptEngine*engine)
{
QString targetID= argument<QString> (0,context);
QFile file(QString("reports:%1").arg(targetID));
QScriptValue object;
if(file.open(QIODevice::ReadOnly))
{
QDomDocument document;
document.setContent(&file,true);
QDomElement element= document.documentElement();
if(!element.isNull())
{
/*188:*/
#line 4475 "./typica.w"

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
/*189:*/
#line 4510 "./typica.w"

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
/*190:*/
#line 4557 "./typica.w"

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
/*633:*/
#line 13679 "./typica.w"

QSettings settings;
QString reportDirectory= QString("%1/%2").arg(settings.value("config").
toString()).
arg(element.attribute("src"));
QDir::addSearchPath("reports",reportDirectory);
QDir directory(reportDirectory);
directory.setFilter(QDir::Files);
directory.setSorting(QDir::Name);
QStringList nameFilter;
nameFilter<<"*.xml";
directory.setNameFilters(nameFilter);
QFileInfoList reportFiles= directory.entryInfoList();
for(int i= 0;i<reportFiles.size();i++)
{
QFileInfo reportFile= reportFiles.at(i);
/*637:*/
#line 13759 "./typica.w"

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
/*638:*/
#line 13786 "./typica.w"

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

/*:638*/
#line 13776 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:637*/
#line 13695 "./typica.w"

}

/*:633*/
#line 4571 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*191:*/
#line 4584 "./typica.w"

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

#line 1 "./helpmenu.w"
/*:191*/
#line 4577 "./typica.w"

}
}

/*:190*/
#line 4535 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*182:*/
#line 4292 "./typica.w"

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

/*:182*/
#line 4543 "./typica.w"

context->setThisObject(oldThis);

/*:189*/
#line 4486 "./typica.w"

}
/*192:*/
#line 9 "./helpmenu.w"

HelpMenu*helpMenu= new HelpMenu();
window->menuBar()->addMenu(helpMenu);

/*:192*/
#line 4488 "./typica.w"

window->show();

/*:188*/
#line 4429 "./typica.w"

}
file.close();
}
return object;
}

/*:186*//*204:*/
#line 4628 "./typica.w"

void addLayoutToWidget(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
if(element.hasAttribute("type"))
{
/*205:*/
#line 4649 "./typica.w"

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
if(element.hasAttribute("spacing"))
{
layout->setSpacing(element.attribute("spacing").toInt());
}
if(element.hasAttribute("margin"))
{
int m= element.attribute("margin").toInt();
layout->setContentsMargins(m,m,m,m);
}

/*:205*/
#line 4634 "./typica.w"

QWidget*widget= widgetStack->top();
if(layout)
{
widget->setLayout(layout);
}
layoutStack->pop();
}
}

/*:204*//*206:*/
#line 4696 "./typica.w"

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

/*:206*//*207:*/
#line 4728 "./typica.w"

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
/*208:*/
#line 4784 "./typica.w"

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

/*:208*/
#line 4756 "./typica.w"

}
}
}
}

/*:207*//*209:*/
#line 4834 "./typica.w"

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
/*675:*/
#line 451 "./daterangeselector.w"

else if(currentElement.tagName()=="daterange")
{
addDateRangeToLayout(currentElement,widgetStack,layoutStack);
}

/*:675*/
#line 4937 "./typica.w"

}
}
}

/*:209*//*210:*/
#line 4945 "./typica.w"

void addLayoutToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QLayout*targetLayout= layoutStack->pop();
QBoxLayout*boxLayout= qobject_cast<QBoxLayout*> (targetLayout);
if(element.hasAttribute("type"))
{
/*205:*/
#line 4649 "./typica.w"

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
if(element.hasAttribute("spacing"))
{
layout->setSpacing(element.attribute("spacing").toInt());
}
if(element.hasAttribute("margin"))
{
int m= element.attribute("margin").toInt();
layout->setContentsMargins(m,m,m,m);
}

/*:205*/
#line 4953 "./typica.w"

boxLayout->addLayout(layout);
layoutStack->pop();
}
layoutStack->push(targetLayout);
}

/*:210*//*211:*/
#line 4964 "./typica.w"

void addSplitterToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
QSplitter*splitter= new(QSplitter);
layout->addWidget(splitter);
/*212:*/
#line 4977 "./typica.w"

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

/*:212*/
#line 4971 "./typica.w"

}

/*:211*//*213:*/
#line 5003 "./typica.w"

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

/*:213*//*214:*/
#line 5053 "./typica.w"

void addSplitterToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QSplitter*parent= qobject_cast<QSplitter*> (widgetStack->top());
QSplitter*splitter= new(QSplitter);
splitter->setParent(parent);
parent->addWidget(splitter);
/*212:*/
#line 4977 "./typica.w"

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

/*:212*/
#line 5061 "./typica.w"

}

/*:214*//*215:*/
#line 5070 "./typica.w"

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

/*:215*//*216:*/
#line 5101 "./typica.w"

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

/*:216*//*217:*/
#line 5139 "./typica.w"

void addDecorationToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
/*218:*/
#line 5160 "./typica.w"

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
/*219:*/
#line 5185 "./typica.w"

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

/*:219*/
#line 5174 "./typica.w"

WidgetDecorator*decoration= new WidgetDecorator(theWidget,labelText,
orientation);
if(element.hasAttribute("id"))
{
decoration->setObjectName(element.attribute("id"));
}

/*:218*/
#line 5143 "./typica.w"

QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(decoration);
}

void addDecorationToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
/*218:*/
#line 5160 "./typica.w"

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
/*219:*/
#line 5185 "./typica.w"

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

/*:219*/
#line 5174 "./typica.w"

WidgetDecorator*decoration= new WidgetDecorator(theWidget,labelText,
orientation);
if(element.hasAttribute("id"))
{
decoration->setObjectName(element.attribute("id"));
}

/*:218*/
#line 5152 "./typica.w"

QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
splitter->addWidget(decoration);
}

/*:217*//*220:*/
#line 5224 "./typica.w"

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

/*:220*//*221:*/
#line 5267 "./typica.w"

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

/*:221*//*222:*/
#line 5319 "./typica.w"

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

/*:222*//*223:*/
#line 5375 "./typica.w"

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

/*:223*//*224:*/
#line 5423 "./typica.w"

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

/*:224*//*225:*/
#line 5440 "./typica.w"

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

/*:225*//*226:*/
#line 5519 "./typica.w"

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
/*227:*/
#line 5567 "./typica.w"

if(currentElement.attribute("delegate")=="sql")
{
/*228:*/
#line 5583 "./typica.w"

SqlComboBoxDelegate*delegate= new SqlComboBoxDelegate;
SqlComboBox*widget= new SqlComboBox();
if(currentElement.hasAttribute("nulltext"))
{
widget->setNullText(currentElement.attribute("nulltext"));
}
if(currentElement.hasAttribute("nulldata"))
{
widget->setNullData(QVariant(currentElement.attribute("nulldata")));
}
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

/*:228*/
#line 5570 "./typica.w"

}
else if(currentElement.attribute("delegate")=="numeric")
{
/*229:*/
#line 5624 "./typica.w"

NumericDelegate*delegate= new NumericDelegate;
view->setItemDelegateForColumn(currentColumn,delegate);

/*:229*/
#line 5574 "./typica.w"

}

/*:227*/
#line 5551 "./typica.w"

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

/*:226*//*241:*/
#line 5797 "./typica.w"

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
widget->setValidator(new ScriptValidator(new QDoubleValidator));
}
else if(element.attribute("validator")=="integer")
{
widget->setValidator(new ScriptValidator(new QIntValidator));
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

/*:241*//*242:*/
#line 5838 "./typica.w"

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

/*:242*//*243:*/
#line 5855 "./typica.w"

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

/*:243*//*244:*/
#line 5872 "./typica.w"

void addCalendarToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
QWidget*widget;
if(element.hasAttribute("time"))
{
if(element.attribute("time")=="true")
{
QDateTimeEdit*edit= new QDateTimeEdit;
edit->setDateTime(QDateTime::currentDateTime());
edit->setCalendarPopup(true);
edit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
widget= qobject_cast<QWidget*> (edit);
}
else
{
QDateEdit*edit= new QDateEdit;
edit->setDate(QDate::currentDate());
edit->setCalendarPopup(true);
edit->setDisplayFormat("yyyy-MM-dd");
widget= qobject_cast<QWidget*> (edit);
}
}
else
{
QDateEdit*edit= new QDateEdit;
edit->setDate(QDate::currentDate());
edit->setCalendarPopup(true);
edit->setDisplayFormat("yyyy-MM-dd");
widget= qobject_cast<QWidget*> (edit);
}
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
}

/*:244*//*245:*/
#line 5915 "./typica.w"

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

/*:245*//*246:*/
#line 5935 "./typica.w"

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

/*:246*//*250:*/
#line 6002 "./typica.w"

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
/*251:*/
#line 6020 "./typica.w"

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
else if(className=="QDateTimeEdit")
{
setQDateTimeEditProperties(value,engine);
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
else if(className=="QLineEdit")
{
setQLineEditProperties(value,engine);
}

/*:251*/
#line 6013 "./typica.w"

}
return value;
}

/*:250*//*253:*/
#line 6149 "./typica.w"

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

/*:253*//*254:*/
#line 6173 "./typica.w"

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

/*:254*//*255:*/
#line 6225 "./typica.w"

QScriptValue SaltTable_model(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
QScriptValue value= engine->newQObject(self->model());
return value;
}

/*:255*//*256:*/
#line 6239 "./typica.w"

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

/*:256*//*257:*/
#line 6257 "./typica.w"

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

/*:257*//*258:*/
#line 6277 "./typica.w"

QScriptValue SaltTable_clear(QScriptContext*context,QScriptEngine*)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
model->clear();
return QScriptValue();
}

/*:258*//*259:*/
#line 6289 "./typica.w"

QScriptValue SaltTable_removeRow(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
int row= argument<int> (0,context);
return engine->newVariant(model->removeRow(row));
}

/*:259*//*260:*/
#line 6302 "./typica.w"

QScriptValue SaltTable_findData(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
SaltModel*model= qobject_cast<SaltModel*> (self->model());
QVariant value= argument<QVariant> (0,context);
int column= argument<int> (1,context);
return engine->newVariant(model->findData(value,column));
}

/*:260*//*261:*/
#line 6315 "./typica.w"

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
value.setProperty("clear",engine->newFunction(SaltTable_clear));
value.setProperty("removeRow",engine->newFunction(SaltTable_removeRow));
value.setProperty("findData",engine->newFunction(SaltTable_findData));
}

/*:261*//*263:*/
#line 6352 "./typica.w"

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
value.setProperty("findData",engine->newFunction(QComboBox_findData));
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

QScriptValue QComboBox_findData(QScriptContext*context,QScriptEngine*engine)
{
QComboBox*self= getself<QComboBox*> (context);
return QScriptValue(engine,self->findData(argument<QVariant> (0,context)));
}

#line 1 "./abouttypica.w"
/*:263*//*276:*/
#line 401 "./units.w"

QScriptValue Units_convertTemperature(QScriptContext*context,QScriptEngine*)
{
return QScriptValue(Units::convertTemperature(argument<double> (0,context),
argument<Units::Unit> (1,context),
argument<Units::Unit> (2,context)));
}

QScriptValue Units_convertRelativeTemperature(QScriptContext*context,
QScriptEngine*)
{
return QScriptValue(Units::convertRelativeTemperature(
argument<double> (0,context),
argument<Units::Unit> (1,context),
argument<Units::Unit> (2,context)));
}

QScriptValue Units_isTemperatureUnit(QScriptContext*context,QScriptEngine*)
{
return QScriptValue(Units::isTemperatureUnit(argument<Units::Unit> (0,context)));
}

QScriptValue Units_convertWeight(QScriptContext*context,QScriptEngine*)
{
return QScriptValue(Units::convertWeight(argument<double> (0,context),
argument<Units::Unit> (1,context),
argument<Units::Unit> (2,context)));
}

QScriptValue Units_isWeightUnit(QScriptContext*context,QScriptEngine*)
{
return QScriptValue(Units::isWeightUnit(argument<Units::Unit> (0,context)));
}

/*:276*//*279:*/
#line 449 "./units.w"

QScriptValue Unit_toScriptValue(QScriptEngine*engine,const Units::Unit&value)
{
return engine->newVariant(QVariant(value));
}

void Unit_fromScriptValue(const QScriptValue&sv,Units::Unit&value)
{
value= sv.toVariant().value<Units::Unit> ();
}

/*:279*//*289:*/
#line 149 "./measurement.w"

QScriptValue constructMeasurement(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==2||context->argumentCount()==3)
{
double measurement= argument<double> (0,context);
QTime timestamp= argument<QTime> (1,context);
Units::Unit unit= Units::Fahrenheit;
if(context->argumentCount()==3)
{
unit= argument<Units::Unit> (2,context);
}
object= engine->toScriptValue<Measurement> (Measurement(measurement,timestamp,unit));
setMeasurementProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"Measurement::Measurement(). This method takes two "
"or three arguments.");
}
return object;
}

/*:289*//*290:*/
#line 176 "./measurement.w"

void setMeasurementProperties(QScriptValue,QScriptEngine*)
{

}

/*:290*//*291:*/
#line 184 "./measurement.w"

QScriptValue Measurement_toScriptValue(QScriptEngine*engine,const Measurement&measurement)
{
QVariant var;
var.setValue(measurement);
return engine->newVariant(var);
}

void Measurement_fromScriptValue(const QScriptValue&value,Measurement&measurement)
{
measurement= value.toVariant().value<Measurement> ();
}
#line 6421 "./typica.w"

/*:291*//*312:*/
#line 7034 "./typica.w"

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

/*:312*//*313:*/
#line 7064 "./typica.w"

void setDAQProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("newChannel",engine->newFunction(DAQ_newChannel));
}

/*:313*//*314:*/
#line 7074 "./typica.w"

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

/*:314*//*321:*/
#line 7230 "./typica.w"

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

/*:321*//*325:*/
#line 7321 "./typica.w"

void setChannelProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:325*//*332:*/
#line 7513 "./typica.w"

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

/*:332*//*337:*/
#line 7651 "./typica.w"

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


/*:337*//*347:*/
#line 7860 "./typica.w"

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
value.setProperty("setDisplayUnits",
engine->newFunction(TemperatureDisplay_setDisplayUnits));
}

/*:347*//*348:*/
#line 7884 "./typica.w"

QScriptValue TemperatureDisplay_setDisplayUnits(QScriptContext*context,QScriptEngine*)
{
TemperatureDisplay*self= getself<TemperatureDisplay*> (context);
self->setDisplayUnits((Units::Unit)argument<int> (0,context));
return QScriptValue();
}

/*:348*//*355:*/
#line 8021 "./typica.w"

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

/*:355*//*360:*/
#line 8130 "./typica.w"

QScriptValue constructThresholdDetector(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new ThresholdDetector(300));
return object;
}

void setThresholdDetectorProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:360*//*365:*/
#line 8227 "./typica.w"

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

/*:365*//*370:*/
#line 8307 "./typica.w"

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

/*:370*//*387:*/
#line 8769 "./typica.w"

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

/*:387*//*410:*/
#line 9407 "./typica.w"

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
value.setProperty("setDisplayUnits",engine->newFunction(ZoomLog_setDisplayUnits));
}

/*:410*//*411:*/
#line 9434 "./typica.w"

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

/*:411*//*412:*/
#line 9482 "./typica.w"

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

/*:412*//*413:*/
#line 9535 "./typica.w"

QScriptValue ZoomLog_setDisplayUnits(QScriptContext*context,QScriptEngine*)
{
ZoomLog*self= getself<ZoomLog*> (context);
self->setDisplayUnits((Units::Unit)argument<int> (0,context));
return QScriptValue();
}

/*:413*//*448:*/
#line 10355 "./typica.w"

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

/*:448*//*456:*/
#line 10498 "./typica.w"

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

/*:456*//*477:*/
#line 10921 "./typica.w"

QScriptValue constructTimerDisplay(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new TimerDisplay);
setTimerDisplayProperties(object,engine);
return object;
}

void setTimerDisplayProperties(QScriptValue value,QScriptEngine*engine)
{
setQLCDNumberProperties(value,engine);
value.setProperty("setTimerMode",engine->newFunction(TimerDisplay_setTimerMode));
}

/*:477*//*478:*/
#line 10940 "./typica.w"

QScriptValue TimerDisplay_setTimerMode(QScriptContext*context,QScriptEngine*)
{
TimerDisplay*self= getself<TimerDisplay*> (context);
if(self)
{
switch(argument<int> (0,context))
{
case 0:
self->setMode(TimerDisplay::CountUp);
break;
case 1:
self->setMode(TimerDisplay::CountDown);
break;
case 2:
self->setMode(TimerDisplay::Clock);
break;
default:
break;
}
}
return QScriptValue();
}


/*:478*//*505:*/
#line 11446 "./typica.w"

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

/*:505*//*518:*/
#line 11727 "./typica.w"

QScriptValue constructLogEditWindow(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new LogEditWindow);
return object;
}

/*:518*//*537:*/
#line 12254 "./typica.w"

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

/*:537*//*551:*/
#line 157 "./webview.w"

QScriptValue constructWebView(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new TypicaWebView);
setQWebViewProperties(object,engine);
return object;
}

void setQWebViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:551*//*552:*/
#line 174 "./webview.w"

void addWebViewToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
TypicaWebView*view= new TypicaWebView;
if(element.hasAttribute("id"))
{
view->setObjectName(element.attribute("id"));
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(view);
}

/*:552*//*557:*/
#line 225 "./webview.w"

QScriptValue QWebElement_toScriptValue(QScriptEngine*engine,const QWebElement&element)
{
QVariant var;
var.setValue(element);
QScriptValue object= engine->newVariant(var);
return object;
}

void QWebElement_fromScriptValue(const QScriptValue&value,QWebElement&element)
{
element= value.toVariant().value<QWebElement> ();
}

/*:557*//*562:*/
#line 290 "./webview.w"

template<> QWebElement argument(int arg,QScriptContext*context)
{
return qscriptvalue_cast<QWebElement> (context->argument(arg));
}

/*:562*//*563:*/
#line 299 "./webview.w"

QScriptValue constructWebElement(QScriptContext*context,
QScriptEngine*engine)
{
QWebElement element= argument<QWebElement> (0,context);
QScriptValue object= engine->newQObject(new TypicaWebElement(element));
return object;
}

/*:563*//*631:*/
#line 13600 "./typica.w"

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

/*:631*//*632:*/
#line 13618 "./typica.w"

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

/*:632*//*640:*/
#line 13825 "./typica.w"

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
/*641:*/
#line 13848 "./typica.w"

QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
/*642:*/
#line 13865 "./typica.w"

if(currentElement.tagName()=="style")
{
document->setDefaultStyleSheet(currentElement.text());
}

/*:642*//*643:*/
#line 13876 "./typica.w"

if(currentElement.tagName()=="html")
{
cursor.insertHtml(currentElement.text());
}

/*:643*//*644:*/
#line 13886 "./typica.w"

if(currentElement.tagName()=="text")
{
cursor.insertText(currentElement.text());
}

/*:644*//*645:*/
#line 13896 "./typica.w"

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

/*:645*/
#line 13858 "./typica.w"

}
}

/*:641*/
#line 13841 "./typica.w"

widget->setDocument(document);
}

/*:640*//*656:*/
#line 14109 "./typica.w"

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

/*:656*//*657:*/
#line 14127 "./typica.w"

void setQTextEditProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
value.setProperty("print",engine->newFunction(QTextEdit_print));
}

#line 1 "./daterangeselector.w"
/*:657*//*676:*/
#line 461 "./daterangeselector.w"

void addDateRangeToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
DateRangeSelector*widget= new DateRangeSelector;
if(element.hasAttribute("id"))
{
widget->setObjectName(element.attribute("id"));
}
if(element.hasAttribute("initial"))
{
widget->setCurrentIndex(element.attribute("initial").toInt());
}
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(widget);
}

/*:676*//*687:*/
#line 14307 "./typica.w"

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

/*:687*//*708:*/
#line 14894 "./typica.w"

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



/*:708*//*734:*/
#line 15484 "./typica.w"

QScriptValue constructDeviceTreeModel(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new DeviceTreeModel);
setDeviceTreeModelProperties(object,engine);
return object;
}

/*:734*//*736:*/
#line 15507 "./typica.w"

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

/*:736*//*737:*/
#line 15534 "./typica.w"

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

/*:737*//*740:*/
#line 15618 "./typica.w"

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

/*:740*//*756:*/
#line 15916 "./typica.w"

QScriptValue constructDeviceConfigurationWindow(QScriptContext*,
QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new DeviceConfigurationWindow);
return object;
}

/*:756*//*827:*/
#line 47 "./settings.w"

QScriptValue constructSettingsWindow(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new SettingsWindow);
return object;
}

/*:827*//*852:*/
#line 18515 "./typica.w"

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

/*:852*//*853:*/
#line 18537 "./typica.w"

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

/*:853*//*854:*/
#line 18570 "./typica.w"

void setModbusRTUDeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("pVChannel",engine->newFunction(ModbusRTUDevice_pVChannel));
value.setProperty("sVChannel",engine->newFunction(ModbusRTUDevice_sVChannel));
}

/*:854*//*872:*/
#line 357 "./unsupportedserial.w"

QScriptValue createDevice(QScriptContext*context,QScriptEngine*engine)
{
QModelIndex deviceIndex= argument<QModelIndex> (0,context);
JavaScriptDevice*device= new JavaScriptDevice(deviceIndex,engine);
QScriptValue object= engine->newQObject(device);
setQObjectProperties(object,engine);
object.setProperty("getChannel",engine->newFunction(JavaScriptDevice_getChannel));
return object;
}

/*:872*//*877:*/
#line 430 "./unsupportedserial.w"

QScriptValue JavaScriptDevice_getChannel(QScriptContext*context,QScriptEngine*engine)
{
JavaScriptDevice*self= getself<JavaScriptDevice*> (context);
QScriptValue object;
if(self)
{
object= engine->newQObject(self->getChannel(argument<int> (0,context)));
setChannelProperties(object,engine);
}
return object;
}

/*:877*//*884:*/
#line 630 "./unsupportedserial.w"

QScriptValue getMeasurementTimestamp(QScriptContext*,QScriptEngine*engine)
{
return engine->toScriptValue<QTime> (QTime::currentTime());
}

/*:884*//*888:*/
#line 667 "./unsupportedserial.w"

QScriptValue constructSerialPort(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QextSerialPort());
setSerialPortProperties(object,engine);
return object;
}

/*:888*//*889:*/
#line 678 "./unsupportedserial.w"

void setSerialPortProperties(QScriptValue value,QScriptEngine*engine)
{
setQIODeviceProperties(value,engine);
value.setProperty("flush",engine->newFunction(SerialPort_flush));
}

/*:889*//*890:*/
#line 687 "./unsupportedserial.w"

QScriptValue SerialPort_flush(QScriptContext*context,QScriptEngine*)
{
QextSerialPort*self= getself<QextSerialPort*> (context);
self->flush();
return QScriptValue();
}

/*:890*//*893:*/
#line 721 "./unsupportedserial.w"

void setQTimerProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

QScriptValue constructQTimer(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new QTimer);
setQTimerProperties(object,engine);
return object;
}




#line 19121 "./typica.w"

#line 1 "./phidgets.w"
/*:893*//*914:*/
#line 463 "./phidgets.w"

QScriptValue constructPhidgetsTemperatureSensor(QScriptContext*context,QScriptEngine*engine)
{
if(context->argumentCount()!=1)
{
context->throwError("Incorrect number of arguments passed to "
"PhidgetsTemperatureSensor constructor. This takes "
"a QModelIndex.");
}
QScriptValue object= engine->newQObject(new PhidgetsTemperatureSensor(argument<QModelIndex> (0,context)),QScriptEngine::ScriptOwnership);
setQObjectProperties(object,engine);
object.setProperty("getChannel",engine->newFunction(Phidgets_getChannel));
return object;
}

/*:914*//*915:*/
#line 480 "./phidgets.w"

QScriptValue Phidgets_getChannel(QScriptContext*context,QScriptEngine*engine)
{
PhidgetsTemperatureSensor*self= getself<PhidgetsTemperatureSensor*> (context);
QScriptValue object;
if(self)
{
object= engine->newQObject(self->getChannel(argument<int> (0,context)));
setChannelProperties(object,engine);
}
return object;
}
#line 19123 "./typica.w"

/*:915*//*947:*/
#line 151 "./rate.w"

QScriptValue constructRateOfChange(QScriptContext*context,QScriptEngine*engine)
{
int cachetime= 1;
int scaletime= 1;
if(context->argumentCount()> 0)
{
cachetime= argument<int> (0,context);
if(context->argumentCount()> 1)
{
scaletime= argument<int> (1,context);
}
}
QScriptValue object= engine->newQObject(new RateOfChange(cachetime,scaletime));
setRateOfChangeProperties(object,engine);
return object;
}

void setRateOfChangeProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:947*//*972:*/
#line 614 "./dataqsdk.w"

QScriptValue constructDataqSdkDevice(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==1)
{
object= engine->newQObject(new DataqSdkDevice(argument<QString> (0,context)),
QScriptEngine::ScriptOwnership);
setDataqSdkDeviceProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"DataqSdkDevice. The constructor takes one string "
"as an argument specifying a device name. "
"Example: Dev1");
}
return object;
}

/*:972*//*973:*/
#line 637 "./dataqsdk.w"

void setDataqSdkDeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("newChannel",engine->newFunction(DataqSdkDevice_newChannel));
}

/*:973*//*974:*/
#line 647 "./dataqsdk.w"

QScriptValue DataqSdkDevice_newChannel(QScriptContext*context,QScriptEngine*engine)
{
DataqSdkDevice*self= getself<DataqSdkDevice*> (context);
QScriptValue object;
if(self)
{
object= engine->newQObject(self->newChannel((Units::Unit)argument<int> (0,context)));
setChannelProperties(object,engine);
}
return object;
}

/*:974*//*999:*/
#line 80 "./scales.w"

QScriptValue constructDragLabel(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
QString labelText= "";
if(context->argumentCount()==1)
{
labelText= argument<QString> (0,context);
}
object= engine->newQObject(new DragLabel(labelText));
setDragLabelProperties(object,engine);
return object;
}

void setDragLabelProperties(QScriptValue value,QScriptEngine*engine)
{
setQLabelProperties(value,engine);
}

/*:999*//*1009:*/
#line 272 "./scales.w"

QScriptValue BaudRateType_toScriptValue(QScriptEngine*engine,const BaudRateType&value)
{
return engine->newVariant(QVariant((int)(value)));
}

void BaudRateType_fromScriptValue(const QScriptValue&sv,BaudRateType&value)
{
value= (BaudRateType)(sv.toVariant().toInt());
}

QScriptValue DataBitsType_toScriptValue(QScriptEngine*engine,const DataBitsType&value)
{
return engine->newVariant(QVariant((int)(value)));
}

void DataBitsType_fromScriptValue(const QScriptValue&sv,DataBitsType&value)
{
value= (DataBitsType)(sv.toVariant().toInt());
}

QScriptValue ParityType_toScriptValue(QScriptEngine*engine,const ParityType&value)
{
return engine->newVariant(QVariant((int)(value)));
}

void ParityType_fromScriptValue(const QScriptValue&sv,ParityType&value)
{
value= (ParityType)(sv.toVariant().toInt());
}

QScriptValue StopBitsType_toScriptValue(QScriptEngine*engine,const StopBitsType&value)
{
return engine->newVariant(QVariant((int)(value)));
}

void StopBitsType_fromScriptValue(const QScriptValue&sv,StopBitsType&value)
{
value= (StopBitsType)(sv.toVariant().toInt());
}

QScriptValue FlowType_toScriptValue(QScriptEngine*engine,const FlowType&value)
{
return engine->newVariant(QVariant((int)(value)));
}

void FlowType_fromScriptValue(const QScriptValue&sv,FlowType&value)
{
value= (FlowType)(sv.toVariant().toInt());
}

/*:1009*//*1012:*/
#line 341 "./scales.w"

void setSerialScaleProperties(QScriptValue value,QScriptEngine*engine)
{
setQIODeviceProperties(value,engine);
}

/*:1012*//*1013:*/
#line 349 "./scales.w"

QScriptValue constructSerialScale(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object;
if(context->argumentCount()==1)
{
object= engine->newQObject(new SerialScale(argument<QString> (0,context)));
setSerialScaleProperties(object,engine);
}
else
{
context->throwError("Incorrect number of arguments passed to "
"SerialScale. The constructor takes one string "
"as an argument specifying a port name.");
}
return object;
}

/*:1013*//*1035:*/
#line 278 "./valueannotation.w"

QScriptValue constructValueAnnotation(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new ValueAnnotation);
setValueAnnotationProperties(object,engine);
return object;
}

void setValueAnnotationProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}
#line 19770 "./typica.w"

/*:1035*/
#line 530 "./typica.w"

/*610:*/
#line 13243 "./typica.w"

void messageFileOutput(QtMsgType,const char*msg)
{
QFile output("Typica-"+QDate::currentDate().toString("yyyy-MM-dd")+".log");
output.open(QIODevice::WriteOnly|QIODevice::Append);
QTextStream outstream(&output);
outstream<<msg<<"\r\n";
}

/*:610*/
#line 531 "./typica.w"

/*607:*/
#line 13204 "./typica.w"

int main(int argc,char**argv)
{
int*c= &argc;
Application app(*c,argv);
QSettings settings;
/*608:*/
#line 13230 "./typica.w"

if(settings.value("settings/advanced/logging",false).toBool())
{
qInstallMsgHandler(messageFileOutput);
}

/*:608*/
#line 13210 "./typica.w"

/*611:*/
#line 13256 "./typica.w"

QStringList themeSearchPath= QIcon::themeSearchPaths();
themeSearchPath.append(":/resources/icons/tango");
QIcon::setThemeSearchPaths(themeSearchPath);
QIcon::setThemeName(":/resources/icons/tango");
app.setWindowIcon(QIcon(":/resources/icons/appicons/logo.svg"));

/*:611*/
#line 13211 "./typica.w"

/*612:*/
#line 13276 "./typica.w"

QFile entypo(":/resources/fonts/entypo.ttf");
entypo.open(QIODevice::ReadOnly);
QFontDatabase::addApplicationFontFromData(entypo.readAll());
entypo.close();
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-regular.otf");
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-bold.otf");
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-bolditalic.otf");
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-italic.otf");
QWebSettings::globalSettings()->setFontFamily(QWebSettings::StandardFont,"Tex Gyre Pagella");

/*:612*/
#line 13212 "./typica.w"


/*766:*/
#line 16155 "./typica.w"

app.registerDeviceConfigurationWidget("roaster",RoasterConfWidget::staticMetaObject);

/*:766*//*776:*/
#line 16397 "./typica.w"

app.registerDeviceConfigurationWidget("nidaqmxbase",
NiDaqMxBaseDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxbase9211series",
NiDaqMxBase9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("ni9211seriestc",
Ni9211TcConfWidget::staticMetaObject);

/*:776*//*784:*/
#line 16628 "./typica.w"

app.registerDeviceConfigurationWidget("nidaqmx",NiDaqMxDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmx9211series",NiDaqMx9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxtc01",NiDaqMxTc01ConfWidget::staticMetaObject);

/*:784*//*808:*/
#line 17593 "./typica.w"

app.registerDeviceConfigurationWidget("modbusrtuport",ModbusRtuPortConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbusrtudevice",ModbusRtuDeviceConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturepv",ModbusRtuDeviceTPvConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturesv",ModbusRtuDeviceTSvConfWidget::staticMetaObject);

/*:808*//*813:*/
#line 17678 "./typica.w"

app.registerDeviceConfigurationWidget("annotationbutton",AnnotationButtonConfWidget::staticMetaObject);

/*:813*//*816:*/
#line 17748 "./typica.w"

app.registerDeviceConfigurationWidget("reconfigurablebutton",ReconfigurableAnnotationButtonConfWidget::staticMetaObject);

/*:816*//*819:*/
#line 17875 "./typica.w"

app.registerDeviceConfigurationWidget("annotationspinbox",NoteSpinConfWidget::staticMetaObject);

#line 1 "./freeannotation.w"
/*:819*//*823:*/
#line 57 "./freeannotation.w"

app.registerDeviceConfigurationWidget("freeannotation",
FreeAnnotationConfWidget::staticMetaObject);
#line 17879 "./typica.w"

#line 1 "./settings.w"
/*:823*//*857:*/
#line 19111 "./typica.w"

app.registerDeviceConfigurationWidget("modbusrtu",ModbusConfigurator::staticMetaObject);

/*:857*//*867:*/
#line 264 "./unsupportedserial.w"

app.registerDeviceConfigurationWidget("unsupporteddevicechannel",
UnsupportedDeviceChannelConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("unsupporteddevice",
UnsupportedSerialDeviceConfWidget::staticMetaObject);

/*:867*//*901:*/
#line 181 "./phidgets.w"

app.registerDeviceConfigurationWidget("phidgets1048",
PhidgetsTemperatureSensorConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("phidgets1048channel",
PhidgetTemperatureSensorChannelConfWidget::staticMetaObject);

/*:901*//*921:*/
#line 19245 "./typica.w"

app.registerDeviceConfigurationWidget("linearspline",LinearSplineInterpolationConfWidget::staticMetaObject);

/*:921*//*924:*/
#line 19305 "./typica.w"

app.registerDeviceConfigurationWidget("coolingtimer",
CoolingTimerConfWidget::staticMetaObject);

/*:924*//*929:*/
#line 19564 "./typica.w"

app.registerDeviceConfigurationWidget("rangetimer",
RangeTimerConfWidget::staticMetaObject);

/*:929*//*934:*/
#line 19665 "./typica.w"

app.registerDeviceConfigurationWidget("multirangetimer",
MultiRangeTimerConfWidget::staticMetaObject);

/*:934*//*939:*/
#line 19760 "./typica.w"

app.registerDeviceConfigurationWidget("translation",TranslationConfWidget::staticMetaObject);

#line 1 "./rate.w"
/*:939*//*951:*/
#line 253 "./rate.w"

app.registerDeviceConfigurationWidget("rate",RateOfChangeConfWidget::staticMetaObject);

/*:951*//*992:*/
#line 1233 "./dataqsdk.w"

app.registerDeviceConfigurationWidget("dataqsdk",DataqSdkDeviceConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("dataqsdkchannel",
DataqSdkChannelConfWidget::staticMetaObject);

/*:992*//*1017:*/
#line 490 "./scales.w"

app.registerDeviceConfigurationWidget("scale",SerialScaleConfWidget::staticMetaObject);

/*:1017*//*1025:*/
#line 138 "./valueannotation.w"

app.registerDeviceConfigurationWidget("valueannotation",
ValueAnnotationConfWidget::staticMetaObject);

/*:1025*/
#line 13214 "./typica.w"

/*613:*/
#line 13293 "./typica.w"

if(settings.value("database/exists","false").toString()=="true")
{
/*618:*/
#line 13415 "./typica.w"

QSqlDatabase database= 
QSqlDatabase::addDatabase(settings.value("database/driver").toString());
database.setConnectOptions("application_name=Typica");
database.setHostName(settings.value("database/hostname").toString());
database.setDatabaseName(settings.value("database/dbname").toString());
database.setUserName(settings.value("database/user").toString());
database.setPassword(settings.value("database/password").toString());
if(!database.open())
{
settings.setValue("database/exists","false");
}
else
{
database.close();
}

/*:618*/
#line 13296 "./typica.w"

}
if(settings.value("database/exists","false").toString()=="false")
{
/*617:*/
#line 13406 "./typica.w"

SqlConnectionSetup dialog;
dialog.exec();

/*:617*/
#line 13300 "./typica.w"

}


/*:613*/
#line 13215 "./typica.w"

/*179:*/
#line 4185 "./typica.w"

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
/*180:*/
#line 4219 "./typica.w"

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

/*:180*/
#line 4213 "./typica.w"


/*:179*/
#line 13216 "./typica.w"

/*7:*/
#line 659 "./typica.w"

QScriptEngine*engine= new QScriptEngine;
QScriptValue constructor;
QScriptValue value;

/*:7*//*17:*/
#line 856 "./typica.w"

constructor= engine->newFunction(constructQWidget);
value= engine->newQMetaObject(&QWidget::staticMetaObject,constructor);
engine->globalObject().setProperty("QWidget",value);

/*:17*//*28:*/
#line 1102 "./typica.w"

constructor= engine->newFunction(constructQMainWindow);
value= engine->newQMetaObject(&ScriptQMainWindow::staticMetaObject,
constructor);
engine->globalObject().setProperty("QMainWindow",value);

/*:28*//*39:*/
#line 1307 "./typica.w"

constructor= engine->newFunction(constructQFrame);
value= engine->newQMetaObject(&QFrame::staticMetaObject,constructor);
engine->globalObject().setProperty("QFrame",value);

/*:39*//*42:*/
#line 1340 "./typica.w"

constructor= engine->newFunction(constructQLabel);
value= engine->newQMetaObject(&QLabel::staticMetaObject,constructor);
engine->globalObject().setProperty("QLabel",value);

/*:42*//*45:*/
#line 1378 "./typica.w"

constructor= engine->newFunction(constructQLineEdit);
value= engine->newQMetaObject(&QLineEdit::staticMetaObject,constructor);
engine->globalObject().setProperty("QLineEdit",value);

/*:45*//*49:*/
#line 1425 "./typica.w"

constructor= engine->newFunction(constructQSplitter);
value= engine->newQMetaObject(&QSplitter::staticMetaObject,constructor);
engine->globalObject().setProperty("QSplitter",value);

/*:49*//*57:*/
#line 1614 "./typica.w"

constructor= engine->newFunction(constructQBoxLayout);
value= engine->newQMetaObject(&QBoxLayout::staticMetaObject,constructor);
engine->globalObject().setProperty("QBoxLayout",value);

/*:57*//*61:*/
#line 1726 "./typica.w"

constructor= engine->newFunction(constructQAction);
value= engine->newQMetaObject(&QAction::staticMetaObject,constructor);
engine->globalObject().setProperty("QAction",value);

/*:61*//*64:*/
#line 1785 "./typica.w"

value= engine->newQMetaObject(&QFileDialog::staticMetaObject);
value.setProperty("getOpenFileName",
engine->newFunction(QFileDialog_getOpenFileName));
value.setProperty("getSaveFileName",
engine->newFunction(QFileDialog_getSaveFileName));
engine->globalObject().setProperty("QFileDialog",value);

/*:64*//*69:*/
#line 1903 "./typica.w"

constructor= engine->newFunction(constructQFile);
value= engine->newQMetaObject(&QFile::staticMetaObject,constructor);
engine->globalObject().setProperty("QFile",value);

/*:69*//*80:*/
#line 2121 "./typica.w"

constructor= engine->newFunction(constructQProcess);
value= engine->newQMetaObject(&QProcess::staticMetaObject,constructor);
engine->globalObject().setProperty("QProcess",value);

/*:80*//*89:*/
#line 2270 "./typica.w"

qScriptRegisterMetaType(engine,QByteArray_toScriptValue,QByteArray_fromScriptValue);
constructor= engine->newFunction(constructQByteArray);
engine->globalObject().setProperty("QByteArray",constructor);

/*:89*//*101:*/
#line 2512 "./typica.w"

engine->globalObject().setProperty("bytesFromInt8",engine->newFunction(bytesFromInt8));
engine->globalObject().setProperty("bytesFromInt16",engine->newFunction(bytesFromInt16));
engine->globalObject().setProperty("bytesFromInt32",engine->newFunction(bytesFromInt32));
engine->globalObject().setProperty("bytesFromFloat",engine->newFunction(bytesFromFloat));
engine->globalObject().setProperty("bytesFromDouble",engine->newFunction(bytesFromDouble));

/*:101*//*104:*/
#line 2615 "./typica.w"

constructor= engine->newFunction(constructQBuffer);
value= engine->newQMetaObject(&QBuffer::staticMetaObject,constructor);
engine->globalObject().setProperty("QBuffer",value);

/*:104*//*107:*/
#line 2664 "./typica.w"

constructor= engine->newFunction(constructXQuery);
engine->globalObject().setProperty("XQuery",constructor);

/*:107*//*113:*/
#line 2766 "./typica.w"

constructor= engine->newFunction(constructXmlWriter);
engine->globalObject().setProperty("XmlWriter",constructor);

/*:113*//*122:*/
#line 2972 "./typica.w"

constructor= engine->newFunction(constructXmlReader);
engine->globalObject().setProperty("XmlReader",constructor);

/*:122*//*129:*/
#line 3096 "./typica.w"

value= engine->newQObject(&settings);
setQSettingsProperties(value,engine);
engine->globalObject().setProperty("QSettings",value);

/*:129*//*133:*/
#line 3177 "./typica.w"

constructor= engine->newFunction(constructQLCDNumber);
value= engine->newQMetaObject(&QLCDNumber::staticMetaObject,constructor);
engine->globalObject().setProperty("QLCDNumber",value);

/*:133*//*136:*/
#line 3233 "./typica.w"

constructor= engine->newFunction(constructQTime);
engine->globalObject().setProperty("QTime",constructor);

/*:136*//*158:*/
#line 3746 "./typica.w"

constructor= engine->newFunction(constructQPushButton);
value= engine->newQMetaObject(&QPushButton::staticMetaObject,constructor);
engine->globalObject().setProperty("QPushButton",value);

/*:158*//*165:*/
#line 3857 "./typica.w"

constructor= engine->newFunction(constructQSqlQuery);
engine->globalObject().setProperty("QSqlQuery",constructor);

/*:165*//*172:*/
#line 4020 "./typica.w"

engine->globalObject().setProperty("baseName",engine->newFunction(baseName));
engine->globalObject().setProperty("dir",engine->newFunction(dir));
engine->globalObject().setProperty("sqlToArray",
engine->newFunction(sqlToArray));
engine->globalObject().setProperty("setFont",engine->newFunction(setFont));
engine->globalObject().setProperty("annotationFromRecord",
engine->newFunction(annotationFromRecord));
engine->globalObject().setProperty("setTabOrder",
engine->newFunction(setTabOrder));
engine->globalObject().setProperty("saveFileFromDatabase",
engine->newFunction(saveFileFromDatabase));

/*:172*//*184:*/
#line 4386 "./typica.w"

engine->globalObject().setProperty("createWindow",
engine->newFunction(createWindow));
engine->globalObject().setProperty("createReport",
engine->newFunction(createReport));

/*:184*//*249:*/
#line 5994 "./typica.w"

engine->globalObject().setProperty("findChildObject",
engine->newFunction(findChildObject));

/*:249*//*275:*/
#line 389 "./units.w"

value= engine->newQMetaObject(&Units::staticMetaObject);
value.setProperty("convertTemperature",engine->newFunction(Units_convertTemperature));
value.setProperty("convertRelativeTemperature",
engine->newFunction(Units_convertRelativeTemperature));
value.setProperty("isTemperatureUnit",engine->newFunction(Units_isTemperatureUnit));
value.setProperty("convertWeight",engine->newFunction(Units_convertWeight));
value.setProperty("isWeightUnit",engine->newFunction(Units_isWeightUnit));
engine->globalObject().setProperty("Units",value);

/*:275*//*280:*/
#line 462 "./units.w"

qScriptRegisterMetaType(engine,Unit_toScriptValue,Unit_fromScriptValue);

#line 6414 "./typica.w"

/*:280*//*288:*/
#line 141 "./measurement.w"

constructor= engine->newFunction(constructMeasurement);
engine->globalObject().setProperty("Measurement",constructor);
qScriptRegisterMetaType(engine,Measurement_toScriptValue,Measurement_fromScriptValue);

/*:288*//*311:*/
#line 7020 "./typica.w"

constructor= engine->newFunction(constructDAQ);
value= engine->newQMetaObject(&DAQ::staticMetaObject,constructor);
value.setProperty("Fahrenheit",Units::Fahrenheit);
value.setProperty("Celsius",Units::Celsius);
value.setProperty("Kelvin",Units::Kelvin);
value.setProperty("Rankine",Units::Rankine);
engine->globalObject().setProperty("DAQ",value);

/*:311*//*320:*/
#line 7222 "./typica.w"

constructor= engine->newFunction(constructFakeDAQ);
value= engine->newQMetaObject(&FakeDAQ::staticMetaObject,constructor);
engine->globalObject().setProperty("FakeDAQ",value);

/*:320*//*331:*/
#line 7505 "./typica.w"

constructor= engine->newFunction(constructLinearCalibrator);
value= engine->newQMetaObject(&LinearCalibrator::staticMetaObject,
constructor);
engine->globalObject().setProperty("LinearCalibrator",value);

/*:331*//*336:*/
#line 7644 "./typica.w"

constructor= engine->newFunction(constructLinearSplineInterpolator);
value= engine->newQMetaObject(&LinearSplineInterpolator::staticMetaObject,constructor);
engine->globalObject().setProperty("LinearSplineInterpolator",value);

/*:336*//*346:*/
#line 7852 "./typica.w"

constructor= engine->newFunction(constructTemperatureDisplay);
value= engine->newQMetaObject(&TemperatureDisplay::staticMetaObject,
constructor);
engine->globalObject().setProperty("TemperatureDisplay",value);

/*:346*//*354:*/
#line 8010 "./typica.w"

constructor= engine->newFunction(constructMeasurementTimeOffset);
value= engine->newQMetaObject(&MeasurementTimeOffset::staticMetaObject,
constructor);
engine->globalObject().setProperty("MeasurementTimeOffset",value);

/*:354*//*359:*/
#line 8121 "./typica.w"

constructor= engine->newFunction(constructThresholdDetector);
value= engine->newQMetaObject(&ThresholdDetector::staticMetaObject,constructor);
engine->globalObject().setProperty("ThresholdDetector",value);

/*:359*//*364:*/
#line 8220 "./typica.w"

constructor= engine->newFunction(constructZeroEmitter);
value= engine->newQMetaObject(&ZeroEmitter::staticMetaObject,constructor);
engine->globalObject().setProperty("ZeroEmitter",value);

/*:364*//*369:*/
#line 8299 "./typica.w"

constructor= engine->newFunction(constructMeasurementAdapter);
value= engine->newQMetaObject(&MeasurementAdapter::staticMetaObject,
constructor);
engine->globalObject().setProperty("MeasurementAdapter",value);

/*:369*//*386:*/
#line 8762 "./typica.w"

constructor= engine->newFunction(constructGraphView);
value= engine->newQMetaObject(&GraphView::staticMetaObject,constructor);
engine->globalObject().setProperty("GraphView",value);

/*:386*//*409:*/
#line 9399 "./typica.w"

constructor= engine->newFunction(constructZoomLog);
value= engine->newQMetaObject(&ZoomLog::staticMetaObject,constructor);
engine->globalObject().setProperty("ZoomLog",value);

/*:409*//*447:*/
#line 10347 "./typica.w"

constructor= engine->newFunction(constructAnnotationButton);
value= engine->newQMetaObject(&AnnotationButton::staticMetaObject,
constructor);
engine->globalObject().setProperty("AnnotationButton",value);

/*:447*//*455:*/
#line 10489 "./typica.w"

constructor= engine->newFunction(constructAnnotationSpinBox);
value= engine->newQMetaObject(&AnnotationSpinBox::staticMetaObject,
constructor);
engine->globalObject().setProperty("AnnotationSpinBox",value);

/*:455*//*476:*/
#line 10914 "./typica.w"

constructor= engine->newFunction(constructTimerDisplay);
value= engine->newQMetaObject(&TimerDisplay::staticMetaObject,constructor);
engine->globalObject().setProperty("TimerDisplay",value);

/*:476*//*504:*/
#line 11438 "./typica.w"

constructor= engine->newFunction(constructWidgetDecorator);
value= engine->newQMetaObject(&WidgetDecorator::staticMetaObject,constructor);
engine->globalObject().setProperty("WidgetDecorator",value);

/*:504*//*517:*/
#line 11720 "./typica.w"

constructor= engine->newFunction(constructLogEditWindow);
value= engine->newQMetaObject(&LogEditWindow::staticMetaObject,constructor);
engine->globalObject().setProperty("LogEditWindow",value);

/*:517*//*536:*/
#line 12247 "./typica.w"

constructor= engine->newFunction(constructXMLInput);
value= engine->newQMetaObject(&XMLInput::staticMetaObject,constructor);
engine->globalObject().setProperty("XMLInput",value);

/*:536*//*550:*/
#line 149 "./webview.w"

constructor= engine->newFunction(constructWebView);
value= engine->newQMetaObject(&TypicaWebView::staticMetaObject,constructor);
engine->globalObject().setProperty("WebView",value);

/*:550*//*558:*/
#line 241 "./webview.w"

qScriptRegisterMetaType(engine,QWebElement_toScriptValue,QWebElement_fromScriptValue);

/*:558*//*561:*/
#line 283 "./webview.w"

constructor= engine->newFunction(constructWebElement);
engine->globalObject().setProperty("WebElement",constructor);

/*:561*//*572:*/
#line 12491 "./typica.w"

value= engine->newQObject(AppInstance);
engine->globalObject().setProperty("Application",value);

/*:572*//*630:*/
#line 13592 "./typica.w"

constructor= engine->newFunction(constructSqlQueryView);
value= engine->newQMetaObject(&SqlQueryView::staticMetaObject,constructor);
engine->globalObject().setProperty("SqlQueryView",value);

/*:630*//*735:*/
#line 15494 "./typica.w"

constructor= engine->newFunction(constructDeviceTreeModel);
value= engine->newQMetaObject(&DeviceTreeModel::staticMetaObject,
constructor);
engine->globalObject().setProperty("DeviceTreeModel",value);

/*:735*//*741:*/
#line 15634 "./typica.w"

qScriptRegisterMetaType(engine,QModelIndex_toScriptValue,QModelIndex_fromScriptValue);

/*:741*//*757:*/
#line 15926 "./typica.w"

constructor= engine->newFunction(constructDeviceConfigurationWindow);
value= engine->newQMetaObject(&DeviceConfigurationWindow::staticMetaObject,
constructor);
engine->globalObject().setProperty("DeviceConfigurationWindow",value);

/*:757*//*828:*/
#line 56 "./settings.w"

constructor= engine->newFunction(constructSettingsWindow);
value= engine->newQMetaObject(&DeviceConfigurationWindow::staticMetaObject,constructor);
engine->globalObject().setProperty("SettingsWindow",value);

#line 1 "./graphsettings.w"
/*:828*//*851:*/
#line 18506 "./typica.w"

constructor= engine->newFunction(constructModbusRTUDevice);
value= engine->newQMetaObject(&ModbusRTUDevice::staticMetaObject,constructor);
engine->globalObject().setProperty("ModbusRTUDevice",value);

/*:851*//*871:*/
#line 350 "./unsupportedserial.w"

engine->globalObject().setProperty("createDevice",
engine->newFunction(createDevice));

/*:871*//*883:*/
#line 622 "./unsupportedserial.w"

engine->globalObject().setProperty("getMeasurementTimestamp",
engine->newFunction(getMeasurementTimestamp));

/*:883*//*887:*/
#line 658 "./unsupportedserial.w"

constructor= engine->newFunction(constructSerialPort);
value= engine->newQMetaObject(&QextSerialPort::staticMetaObject,constructor);
engine->globalObject().setProperty("SerialPort",value);

/*:887*//*892:*/
#line 713 "./unsupportedserial.w"

constructor= engine->newFunction(constructQTimer);
value= engine->newQMetaObject(&QTimer::staticMetaObject,constructor);
engine->globalObject().setProperty("Timer",value);

/*:892*//*912:*/
#line 450 "./phidgets.w"

constructor= engine->newFunction(constructPhidgetsTemperatureSensor);
value= engine->newQMetaObject(&PhidgetsTemperatureSensor::staticMetaObject,constructor);
engine->globalObject().setProperty("PhidgetsTemperatureSensor",value);

/*:912*//*946:*/
#line 144 "./rate.w"

constructor= engine->newFunction(constructRateOfChange);
value= engine->newQMetaObject(&RateOfChange::staticMetaObject,constructor);
engine->globalObject().setProperty("RateOfChange",value);

/*:946*//*971:*/
#line 604 "./dataqsdk.w"

constructor= engine->newFunction(constructDataqSdkDevice);
value= engine->newQMetaObject(&DataqSdkDevice::staticMetaObject,constructor);
engine->globalObject().setProperty("DataqSdkDevice",value);

/*:971*//*998:*/
#line 73 "./scales.w"

constructor= engine->newFunction(constructDragLabel);
value= engine->newQMetaObject(&DragLabel::staticMetaObject,constructor);
engine->globalObject().setProperty("DragLabel",value);

/*:998*//*1006:*/
#line 239 "./scales.w"

constructor= engine->newFunction(constructSerialScale);
value= engine->newQMetaObject(&SerialScale::staticMetaObject,constructor);
engine->globalObject().setProperty("SerialScale",value);

/*:1006*//*1010:*/
#line 325 "./scales.w"

qScriptRegisterMetaType(engine,BaudRateType_toScriptValue,BaudRateType_fromScriptValue);
qScriptRegisterMetaType(engine,DataBitsType_toScriptValue,DataBitsType_fromScriptValue);
qScriptRegisterMetaType(engine,ParityType_toScriptValue,ParityType_fromScriptValue);
qScriptRegisterMetaType(engine,StopBitsType_toScriptValue,StopBitsType_fromScriptValue);
qScriptRegisterMetaType(engine,FlowType_toScriptValue,FlowType_fromScriptValue);

/*:1010*//*1034:*/
#line 271 "./valueannotation.w"

constructor= engine->newFunction(constructValueAnnotation);
value= engine->newQMetaObject(&ValueAnnotation::staticMetaObject,constructor);
engine->globalObject().setProperty("ValueAnnotation",value);

/*:1034*/
#line 13217 "./typica.w"

app.engine= engine;
/*181:*/
#line 4267 "./typica.w"

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
/*182:*/
#line 4292 "./typica.w"

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

/*:182*/
#line 4287 "./typica.w"


/*:181*/
#line 13219 "./typica.w"


int retval= app.exec();
delete engine;
return retval;
}

/*:607*/
#line 532 "./typica.w"

#include "moc_typica.cpp"

/*:3*/
