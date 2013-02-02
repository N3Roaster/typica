/*16:*/
#line 757 "./typica.w"

#define PROGRAM_NAME "Typica"

/*18:*/
#line 840 "./typica.w"

#include <QtCore> 
#include <QtGui> 
#include <QtScript> 
#include <QtScriptTools> 
#include <QtXml> 
#include <QtSql> 
#include <QtDebug> 
#include <QtXmlPatterns> 
#include <QtWebKit> 

/*:18*//*19:*/
#line 855 "./typica.w"

#include "helpmenu.h"

/*:19*//*677:*/
#line 15661 "./typica.w"

#include "qextserialport.h"
#include "qextserialenumerator.h"

/*:677*/
#line 760 "./typica.w"

/*33:*/
#line 1146 "./typica.w"

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

/*:33*//*136:*/
#line 3265 "./typica.w"

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

/*:136*//*197:*/
#line 5035 "./typica.w"

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

/*:197*//*226:*/
#line 5675 "./typica.w"

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

/*:226*//*238:*/
#line 5977 "./typica.w"

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

/*:238*//*239:*/
#line 6023 "./typica.w"

class DAQImplementation:public QThread
{
Q_OBJECT
public:
DAQImplementation(const QString&driverinfo);
~DAQImplementation();
void run();
void measure();
/*240:*/
#line 6043 "./typica.w"

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

/*:240*/
#line 6032 "./typica.w"

/*241:*/
#line 6059 "./typica.w"

bool useBase;
QString device;
QVector<Channel*> channelMap;
unsigned int handle;
int error;
int channels;
bool ready;
QLibrary driver;
QVector<Measurement::TemperatureUnits> unitMap;

/*:241*/
#line 6033 "./typica.w"

};

/*:239*//*257:*/
#line 6556 "./typica.w"

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

/*:257*//*264:*/
#line 6743 "./typica.w"

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

/*:264*//*268:*/
#line 6806 "./typica.w"

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

/*:268*//*275:*/
#line 7000 "./typica.w"

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

/*:275*//*280:*/
#line 7135 "./typica.w"

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

/*:280*//*289:*/
#line 7311 "./typica.w"

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

/*:289*//*296:*/
#line 7461 "./typica.w"

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

/*:296*//*301:*/
#line 7567 "./typica.w"

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

/*:301*//*306:*/
#line 7660 "./typica.w"

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

/*:306*//*311:*/
#line 7749 "./typica.w"

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

/*:311*//*326:*/
#line 8100 "./typica.w"

class MeasurementModel;
class ZoomLog:public QTableView
{
Q_OBJECT
/*327:*/
#line 8148 "./typica.w"

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

/*:327*/
#line 8105 "./typica.w"

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

/*:326*//*351:*/
#line 8794 "./typica.w"

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

/*:351*//*352:*/
#line 8846 "./typica.w"

class MeasurementList:public QVariantList
{
public:
bool operator<(const MeasurementList&other)const;
bool operator==(const MeasurementList&other)const;
};

/*:352*//*378:*/
#line 9483 "./typica.w"

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

/*:378*//*386:*/
#line 9608 "./typica.w"

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

/*:386*//*394:*/
#line 9767 "./typica.w"

class TimerDisplay:public QLCDNumber
{
Q_OBJECT
/*395:*/
#line 9817 "./typica.w"

Q_PROPERTY(QTime seconds READ seconds WRITE setTimer)
Q_PROPERTY(TimerMode mode READ mode WRITE setMode)
Q_PROPERTY(bool running READ isRunning)
Q_PROPERTY(QTime resetValue READ resetValue WRITE setResetValue)
Q_PROPERTY(QString displayFormat READ displayFormat WRITE setDisplayFormat)
Q_PROPERTY(bool autoReset READ autoReset WRITE setAutoReset)

/*:395*/
#line 9771 "./typica.w"

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
/*396:*/
#line 9827 "./typica.w"

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

/*:396*/
#line 9808 "./typica.w"

};

/*:394*//*416:*/
#line 10186 "./typica.w"

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

/*:416*//*429:*/
#line 10464 "./typica.w"

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

/*:429*//*431:*/
#line 10506 "./typica.w"

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

/*:431*//*442:*/
#line 10681 "./typica.w"

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

/*:442*//*456:*/
#line 10989 "./typica.w"

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

/*:456*//*463:*/
#line 11185 "./typica.w"

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

/*:463*//*474:*/
#line 11426 "./typica.w"

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

/*:474*//*488:*/
#line 11685 "./typica.w"

#define AppInstance (qobject_cast<Application *> (qApp))

class NodeInserter;
class DeviceTreeModel;
class Application:public QApplication
{
Q_OBJECT
public:
Application(int&argc,char**argv);
QDomDocument*configuration();
/*602:*/
#line 14072 "./typica.w"

QDomDocument deviceConfiguration();

/*:602*//*635:*/
#line 14745 "./typica.w"

void registerDeviceConfigurationWidget(QString driver,QMetaObject widget);
QWidget*deviceConfigurationWidget(DeviceTreeModel*model,
const QModelIndex&index);

/*:635*//*640:*/
#line 14849 "./typica.w"

QList<NodeInserter*> topLevelNodeInserters;

/*:640*/
#line 11696 "./typica.w"

QSqlDatabase database();
QScriptEngine*engine;
public slots:
/*603:*/
#line 14079 "./typica.w"

void saveDeviceConfiguration();

/*:603*/
#line 11700 "./typica.w"

private:
/*601:*/
#line 14063 "./typica.w"

QDomDocument deviceConfigurationDocument;

/*:601*//*634:*/
#line 14739 "./typica.w"

QHash<QString,QMetaObject> deviceConfigurationWidgets;

/*:634*/
#line 11702 "./typica.w"

QDomDocument conf;
};

/*:488*//*496:*/
#line 11826 "./typica.w"

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

/*:496*//*509:*/
#line 12139 "./typica.w"

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

/*:509*//*516:*/
#line 12261 "./typica.w"

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

/*:516*//*527:*/
#line 12420 "./typica.w"

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

/*:527*//*532:*/
#line 12548 "./typica.w"

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

/*:532*//*547:*/
#line 12796 "./typica.w"

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

/*:547*//*559:*/
#line 13005 "./typica.w"

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

/*:559*//*571:*/
#line 13241 "./typica.w"

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

/*:571*//*581:*/
#line 13457 "./typica.w"

class ScaleControl:public QGraphicsView
{
Q_OBJECT
Q_PROPERTY(double initialValue READ initialValue WRITE setInitialValue)
Q_PROPERTY(double finalValue READ finalValue WRITE setFinalValue)
/*582:*/
#line 13483 "./typica.w"

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

/*:582*/
#line 13463 "./typica.w"

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

/*:581*//*593:*/
#line 13780 "./typica.w"

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

/*:593*//*609:*/
#line 14168 "./typica.w"

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

/*:609*//*611:*/
#line 14243 "./typica.w"

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

/*:611*//*630:*/
#line 14697 "./typica.w"

Q_DECLARE_METATYPE(QModelIndex)

/*:630*//*638:*/
#line 14804 "./typica.w"

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

/*:638*//*641:*/
#line 14855 "./typica.w"

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

/*:641*//*649:*/
#line 14999 "./typica.w"

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

/*:649*//*653:*/
#line 15084 "./typica.w"

class RoasterConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE RoasterConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateRoasterId(int id);
};

/*:653*//*658:*/
#line 15211 "./typica.w"

class NiDaqMxBaseDriverConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxBaseDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
};

/*:658*//*660:*/
#line 15257 "./typica.w"

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

/*:660*//*664:*/
#line 15343 "./typica.w"

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

/*:664*//*669:*/
#line 15445 "./typica.w"

class NiDaqMxDriverConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE NiDaqMxDriverConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
};

/*:669*//*671:*/
#line 15486 "./typica.w"

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

/*:671*//*673:*/
#line 15555 "./typica.w"

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

/*:673*//*678:*/
#line 15672 "./typica.w"

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

/*:678*//*680:*/
#line 15716 "./typica.w"

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

/*:680*//*682:*/
#line 15787 "./typica.w"

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

/*:682*//*684:*/
#line 15825 "./typica.w"

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

/*:684*//*686:*/
#line 15858 "./typica.w"

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

/*:686*//*689:*/
#line 15911 "./typica.w"

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

/*:689*//*691:*/
#line 15973 "./typica.w"

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

/*:691*//*693:*/
#line 16124 "./typica.w"

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

/*:693*//*695:*/
#line 16383 "./typica.w"

class ModbusRtuDeviceTPvConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*model,
const QModelIndex&index);
private slots:
void updateAddress(int newAddress);
};

/*:695*//*697:*/
#line 16429 "./typica.w"

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

/*:697*//*701:*/
#line 16623 "./typica.w"

class AnnotationButtonConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE AnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateButtonText(const QString&text);
void updateAnnotationText(const QString&text);
};

/*:701*//*705:*/
#line 16691 "./typica.w"

class ReconfigurableAnnotationButtonConfWidget:public BasicDeviceConfigurationWidget
{
Q_OBJECT
public:
Q_INVOKABLE ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index);
private slots:
void updateButtonText(const QString&text);
void updateAnnotationText(const QString&text);
};

/*:705*//*708:*/
#line 16765 "./typica.w"

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

/*:708*//*711:*/
#line 16886 "./typica.w"

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

/*:711*//*726:*/
#line 17558 "./typica.w"

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

/*:726*//*730:*/
#line 18064 "./typica.w"

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

/*:730*//*736:*/
#line 18188 "./typica.w"

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

/*:736*/
#line 761 "./typica.w"

/*25:*/
#line 1010 "./typica.w"

void setQObjectProperties(QScriptValue value,QScriptEngine*engine);

/*:25*//*27:*/
#line 1025 "./typica.w"

void setQPaintDeviceProperties(QScriptValue value,QScriptEngine*engine);
void setQLayoutItemProperties(QScriptValue value,QScriptEngine*engine);

/*:27*//*29:*/
#line 1050 "./typica.w"

void setQWidgetProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQWidget(QScriptContext*context,QScriptEngine*engine);
QScriptValue QWidget_setLayout(QScriptContext*context,QScriptEngine*engine);
QScriptValue QWidget_activateWindow(QScriptContext*context,
QScriptEngine*engine);

/*:29*//*37:*/
#line 1248 "./typica.w"

QScriptValue constructQMainWindow(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QMainWindow_setCentralWidget(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QMainWindow_menuBar(QScriptContext*context,
QScriptEngine*engine);
void setQMainWindowProperties(QScriptValue value,QScriptEngine*engine);

/*:37*//*42:*/
#line 1347 "./typica.w"

void setQMenuBarProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QMenuBar_addMenu(QScriptContext*context,QScriptEngine*engine);

/*:42*//*45:*/
#line 1392 "./typica.w"

void setQMenuProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QMenu_addAction(QScriptContext*context,QScriptEngine*engine);
QScriptValue QMenu_addSeparator(QScriptContext*context,QScriptEngine*engine);

/*:45*//*48:*/
#line 1458 "./typica.w"

void setQFrameProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQFrame(QScriptContext*context,QScriptEngine*engine);

/*:48*//*51:*/
#line 1491 "./typica.w"

void setQLabelProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQLabel(QScriptContext*context,QScriptEngine*engine);

/*:51*//*54:*/
#line 1532 "./typica.w"

QScriptValue constructQSplitter(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSplitter_addWidget(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_saveState(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QSplitter_restoreState(QScriptContext*context,
QScriptEngine*engine);
void setQSplitterProperties(QScriptValue value,QScriptEngine*engine);

/*:54*//*59:*/
#line 1651 "./typica.w"

void setQLayoutProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QLayout_addWidget(QScriptContext*context,QScriptEngine*engine);

/*:59*//*61:*/
#line 1706 "./typica.w"

QScriptValue constructQBoxLayout(QScriptContext*context,
QScriptEngine*engine);
void setQBoxLayoutProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QBoxLayout_addLayout(QScriptContext*context,QScriptEngine*engine);
QScriptValue QBoxLayout_addWidget(QScriptContext*context,QScriptEngine*engine);

/*:61*//*65:*/
#line 1819 "./typica.w"

QScriptValue constructQAction(QScriptContext*context,QScriptEngine*engine);
QScriptValue QAction_setShortcut(QScriptContext*context,
QScriptEngine*engine);
void setQActionProperties(QScriptValue value,QScriptEngine*engine);

/*:65*//*68:*/
#line 1875 "./typica.w"

QScriptValue QFileDialog_getOpenFileName(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QFileDialog_getSaveFileName(QScriptContext*context,
QScriptEngine*engine);
void setQFileDialogProperties(QScriptValue value,QScriptEngine*engine);
void setQDialogProperties(QScriptValue value,QScriptEngine*engine);

/*:68*//*73:*/
#line 1986 "./typica.w"

QScriptValue constructQFile(QScriptContext*context,QScriptEngine*engine);
void setQFileProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QFile_remove(QScriptContext*context,QScriptEngine*engine);
void setQIODeviceProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QIODevice_open(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_close(QScriptContext*context,QScriptEngine*engine);
QScriptValue QIODevice_readToString(QScriptContext*context,
QScriptEngine*engine);

/*:73*//*80:*/
#line 2108 "./typica.w"

QScriptValue constructQBuffer(QScriptContext*context,QScriptEngine*engine);
void setQBufferProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QBuffer_setData(QScriptContext*context,QScriptEngine*engine);

/*:80*//*83:*/
#line 2153 "./typica.w"

QScriptValue constructXQuery(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_bind(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_exec(QScriptContext*context,QScriptEngine*engine);
QScriptValue XQuery_setQuery(QScriptContext*context,QScriptEngine*engine);
void setXQueryProperties(QScriptValue value,QScriptEngine*engine);

/*:83*//*89:*/
#line 2226 "./typica.w"

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

/*:89*//*98:*/
#line 2444 "./typica.w"

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

/*:98*//*105:*/
#line 2579 "./typica.w"

QScriptValue QSettings_value(QScriptContext*context,QScriptEngine*engine);
QScriptValue QSettings_setValue(QScriptContext*context,QScriptEngine*engine);
void setQSettingsProperties(QScriptValue value,QScriptEngine*engine);

/*:105*//*109:*/
#line 2661 "./typica.w"

QScriptValue constructQLCDNumber(QScriptContext*context,
QScriptEngine*engine);
void setQLCDNumberProperties(QScriptValue value,QScriptEngine*engine);

/*:109*//*112:*/
#line 2699 "./typica.w"

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

/*:112*//*127:*/
#line 3168 "./typica.w"

void setQAbstractScrollAreaProperties(QScriptValue value,
QScriptEngine*engine);

/*:127*//*129:*/
#line 3183 "./typica.w"

void setQAbstractItemViewProperties(QScriptValue value,QScriptEngine*engine);

/*:129*//*131:*/
#line 3196 "./typica.w"

void setQGraphicsViewProperties(QScriptValue value,QScriptEngine*engine);
void setQTableViewProperties(QScriptValue value,QScriptEngine*engine);

/*:131*//*133:*/
#line 3220 "./typica.w"

void setQAbstractButtonProperties(QScriptValue value,QScriptEngine*engine);
void setQPushButtonProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructQPushButton(QScriptContext*context,
QScriptEngine*engine);

/*:133*//*140:*/
#line 3319 "./typica.w"

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

/*:140*//*147:*/
#line 3489 "./typica.w"

QScriptValue baseName(QScriptContext*context,QScriptEngine*engine);
QScriptValue dir(QScriptContext*context,QScriptEngine*engine);
QScriptValue sqlToArray(QScriptContext*context,QScriptEngine*engine);
QScriptValue setFont(QScriptContext*context,QScriptEngine*engine);
QScriptValue annotationFromRecord(QScriptContext*context,
QScriptEngine*engine);
QScriptValue setTabOrder(QScriptContext*context,QScriptEngine*engine);

/*:147*//*158:*/
#line 3772 "./typica.w"

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

/*:158*//*209:*/
#line 5288 "./typica.w"

void setQDateEditProperties(QScriptValue value,QScriptEngine*engine);
void setQDateTimeEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QDateTimeEdit_setDate(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QDateTimeEdit_day(QScriptContext*context,QScriptEngine*engine);
QScriptValue QDateTimeEdit_month(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QDateTimeEdit_year(QScriptContext*context,QScriptEngine*engine);

/*:209*//*210:*/
#line 5303 "./typica.w"

QScriptValue findChildObject(QScriptContext*context,QScriptEngine*engine);

/*:210*//*214:*/
#line 5430 "./typica.w"

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

/*:214*//*221:*/
#line 5600 "./typica.w"

void setSqlComboBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQComboBoxProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QComboBox_currentData(QScriptContext*context,
QScriptEngine*engine);
QScriptValue QComboBox_addItem(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_setModel(QScriptContext*context,QScriptEngine*engine);
QScriptValue QComboBox_findText(QScriptContext*context,QScriptEngine*engine);

/*:221*//*252:*/
#line 6478 "./typica.w"

QScriptValue constructDAQ(QScriptContext*context,QScriptEngine*engine);
QScriptValue DAQ_newChannel(QScriptContext*context,QScriptEngine*engine);
void setDAQProperties(QScriptValue value,QScriptEngine*engine);

/*:252*//*261:*/
#line 6676 "./typica.w"

QScriptValue constructFakeDAQ(QScriptContext*context,QScriptEngine*engine);
QScriptValue FakeDAQ_newChannel(QScriptContext*context,QScriptEngine*engine);
void setFakeDAQProperties(QScriptValue value,QScriptEngine*engine);

/*:261*//*266:*/
#line 6777 "./typica.w"

void setChannelProperties(QScriptValue value,QScriptEngine*engine);

/*:266*//*272:*/
#line 6953 "./typica.w"

QScriptValue constructLinearCalibrator(QScriptContext*context,
QScriptEngine*engine);
void setLinearCalibratorProperties(QScriptValue value,QScriptEngine*engine);

/*:272*//*277:*/
#line 7092 "./typica.w"

QScriptValue constructLinearSplineInterpolator(QScriptContext*context,QScriptEngine*engine);
void setLinearSplineInterpolatorProperties(QScriptValue value,QScriptEngine*engine);

/*:277*//*286:*/
#line 7274 "./typica.w"

QScriptValue constructTemperatureDisplay(QScriptContext*context,
QScriptEngine*engine);
void setTemperatureDisplayProperties(QScriptValue value,QScriptEngine*engine);

/*:286*//*293:*/
#line 7411 "./typica.w"

QScriptValue constructMeasurementTimeOffset(QScriptContext*context,
QScriptEngine*engine);
void setMeasurementTimeOffsetProperties(QScriptValue value,
QScriptEngine*engine);

/*:293*//*298:*/
#line 7524 "./typica.w"

QScriptValue constructThresholdDetector(QScriptContext*context,QScriptEngine*engine);
void setThresholdDetectorProperties(QScriptValue value,QScriptEngine*engine);

/*:298*//*303:*/
#line 7621 "./typica.w"

QScriptValue constructZeroEmitter(QScriptContext*context,
QScriptEngine*engine);
void setZeroEmitterProperties(QScriptValue value,QScriptEngine*engine);

/*:303*//*308:*/
#line 7700 "./typica.w"

QScriptValue constructMeasurementAdapter(QScriptContext*context,
QScriptEngine*engine);
void setMeasurementAdapterProperties(QScriptValue value,QScriptEngine*engine);

/*:308*//*323:*/
#line 8050 "./typica.w"

void setGraphViewProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructGraphView(QScriptContext*context,QScriptEngine*engine);

/*:323*//*346:*/
#line 8645 "./typica.w"

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

/*:346*//*383:*/
#line 9570 "./typica.w"

QScriptValue constructAnnotationButton(QScriptContext*context,
QScriptEngine*engine);
void setAnnotationButtonProperties(QScriptValue value,QScriptEngine*engine);

/*:383*//*391:*/
#line 9710 "./typica.w"

QScriptValue constructAnnotationSpinBox(QScriptContext*context,
QScriptEngine*engine);
void setAnnotationSpinBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQDoubleSpinBoxProperties(QScriptValue value,QScriptEngine*engine);
void setQAbstractSpinBoxProperties(QScriptValue value,QScriptEngine*engine);

/*:391*//*412:*/
#line 10133 "./typica.w"

QScriptValue constructTimerDisplay(QScriptContext*context,
QScriptEngine*engine);
void setTimerDisplayProperties(QScriptValue value,QScriptEngine*engine);

/*:412*//*439:*/
#line 10627 "./typica.w"

void setWidgetDecoratorProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructWidgetDecorator(QScriptContext*context,
QScriptEngine*engine);

/*:439*//*452:*/
#line 10910 "./typica.w"

QScriptValue constructLogEditWindow(QScriptContext*context,
QScriptEngine*engine);

/*:452*//*471:*/
#line 11384 "./typica.w"

QScriptValue constructXMLInput(QScriptContext*context,QScriptEngine*engine);
QScriptValue XMLInput_input(QScriptContext*context,QScriptEngine*engine);

/*:471*//*487:*/
#line 11667 "./typica.w"

QScriptValue constructWebView(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_load(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_print(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_setContent(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_setHtml(QScriptContext*context,QScriptEngine*engine);
QScriptValue WebView_saveXml(QScriptContext*context,QScriptEngine*);
void addWebViewToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void setQWebViewProperties(QScriptValue value,QScriptEngine*engine);

/*:487*//*542:*/
#line 12683 "./typica.w"

void setSqlQueryViewProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue constructSqlQueryView(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SqlQueryView_setQuery(QScriptContext*context,
QScriptEngine*engine);
QScriptValue SqlQueryView_setHeaderData(QScriptContext*context,
QScriptEngine*engine);

/*:542*//*552:*/
#line 12912 "./typica.w"

void addReportToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:552*//*568:*/
#line 13196 "./typica.w"

void setQTextEditProperties(QScriptValue value,QScriptEngine*engine);
QScriptValue QTextEdit_print(QScriptContext*context,QScriptEngine*engine);

/*:568*//*578:*/
#line 13391 "./typica.w"

void addFormArrayToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:578*//*599:*/
#line 13975 "./typica.w"

void addScaleControlToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);
void addIntensityControlToLayout(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack);

/*:599*//*625:*/
#line 14561 "./typica.w"

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

/*:625*//*631:*/
#line 14703 "./typica.w"

QScriptValue QModelIndex_toScriptValue(QScriptEngine*engine,const QModelIndex&index);
void QModelIndex_fromScriptValue(const QScriptValue&value,QModelIndex&index);

/*:631*//*646:*/
#line 14971 "./typica.w"

QScriptValue constructDeviceConfigurationWindow(QScriptContext*context,
QScriptEngine*engine);

/*:646*//*721:*/
#line 17465 "./typica.w"

QScriptValue constructModbusRTUDevice(QScriptContext*context,QScriptEngine*engine);
QScriptValue ModbusRTUDevice_pVChannel(QScriptContext*context,QScriptEngine*engine);
QScriptValue ModbusRTUDevice_sVChannel(QScriptContext*context,QScriptEngine*engine);
void setModbusRTUDeviceProperties(QScriptValue value,QScriptEngine*engine);

/*:721*/
#line 762 "./typica.w"

/*17:*/
#line 770 "./typica.w"

/*639:*/
#line 14824 "./typica.w"

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

/*:639*/
#line 771 "./typica.w"

/*227:*/
#line 5715 "./typica.w"

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

/*:227*//*229:*/
#line 5743 "./typica.w"

Measurement::Measurement(const Measurement&x):
theTemperature(x.temperature()),theTime(x.time()),
unit(x.unit)
{

}

Measurement::~Measurement()
{

}

/*:229*//*230:*/
#line 5759 "./typica.w"

Measurement&Measurement::operator= (Measurement&x)
{
theTemperature= x.temperature();
theTime= x.time();
unit= x.unit;
return*this;
}

/*:230*//*231:*/
#line 5773 "./typica.w"

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

/*:231*//*232:*/
#line 5799 "./typica.w"

void Measurement::setUnit(TemperatureUnits scale)
{
unit= scale;
}

Measurement::TemperatureUnits Measurement::scale()
{
return unit;
}

/*:232*//*233:*/
#line 5819 "./typica.w"

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

/*:233*//*234:*/
#line 5844 "./typica.w"

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

/*:234*//*235:*/
#line 5870 "./typica.w"

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

/*:235*//*236:*/
#line 5895 "./typica.w"

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

/*:236*/
#line 772 "./typica.w"

/*242:*/
#line 6084 "./typica.w"

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

/*:242*//*243:*/
#line 6126 "./typica.w"

void DAQImplementation::run()
{
setPriority(QThread::TimeCriticalPriority);
while(ready)
{
measure();
}
}

/*:243*//*244:*/
#line 6142 "./typica.w"

void DAQ::threadFinished()
{
if(imp->error)
{
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6147 "./typica.w"

}
}

/*:244*//*246:*/
#line 6218 "./typica.w"

void DAQ::start()
{
if(imp->ready)
{
imp->error= imp->startTask(imp->handle);
if(imp->error)
{
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6226 "./typica.w"

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
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6250 "./typica.w"

}
imp->error= imp->clearTask(imp->handle);
if(imp->error)
{
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6255 "./typica.w"

}
}
}

/*:246*//*247:*/
#line 6265 "./typica.w"

DAQ::DAQ(QString device,const QString&driver):imp(new DAQImplementation(driver))
{
imp->device= device;
imp->error= imp->createTask(device.toAscii().data(),&(imp->handle));
if(imp->error)
{
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6272 "./typica.w"

}
else
{
imp->ready= true;
}
}

/*:247*//*248:*/
#line 6286 "./typica.w"

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
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6321 "./typica.w"

}
}
return retval;
}

/*:248*//*249:*/
#line 6335 "./typica.w"

void DAQ::setClockRate(double Hz)
{
if(imp->ready)
{
imp->error= imp->setClock(imp->handle,"OnboardClock",Hz,
(signed long)(10280),(signed long)(10123),
(unsigned long long)(1));
if(imp->error)
{
/*245:*/
#line 6193 "./typica.w"

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

/*:245*/
#line 6345 "./typica.w"

}
}
}

/*:249*//*250:*/
#line 6355 "./typica.w"

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

/*:250*//*251:*/
#line 6386 "./typica.w"

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

/*:251*/
#line 773 "./typica.w"

/*258:*/
#line 6588 "./typica.w"

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

/*:258*//*259:*/
#line 6602 "./typica.w"

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

/*:259*//*260:*/
#line 6627 "./typica.w"

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

/*:260*/
#line 774 "./typica.w"

/*265:*/
#line 6758 "./typica.w"

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

/*:265*/
#line 775 "./typica.w"

/*281:*/
#line 7169 "./typica.w"

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

/*:281*//*282:*/
#line 7229 "./typica.w"

TemperatureDisplay::TemperatureDisplay(QWidget*parent):
QLCDNumber(8,parent),unit(Auto)
{
setSegmentStyle(Filled);
display("---.--'F");
}

/*:282*//*283:*/
#line 7245 "./typica.w"

void TemperatureDisplay::invalidate()
{
display("---.--'F");
}

/*:283*//*284:*/
#line 7257 "./typica.w"

void TemperatureDisplay::setDisplayUnits(DisplayUnits scale)
{
unit= scale;
}

/*:284*//*285:*/
#line 7265 "./typica.w"

TemperatureDisplay::~TemperatureDisplay()
{

}

/*:285*/
#line 776 "./typica.w"

/*290:*/
#line 7345 "./typica.w"

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
/*291:*/
#line 7378 "./typica.w"

QTime newTime(0,0,0,0);
newTime= newTime.addMSecs(relTime);
if(newTime.hour()> 0)
{
newTime.setHMS(0,newTime.minute(),newTime.second(),newTime.msec());
}
Measurement rel(measure.temperature(),newTime);
emit measurement(rel);

/*:291*/
#line 7357 "./typica.w"

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
/*291:*/
#line 7378 "./typica.w"

QTime newTime(0,0,0,0);
newTime= newTime.addMSecs(relTime);
if(newTime.hour()> 0)
{
newTime.setHMS(0,newTime.minute(),newTime.second(),newTime.msec());
}
Measurement rel(measure.temperature(),newTime);
emit measurement(rel);

/*:291*/
#line 7368 "./typica.w"

}
hasPrevious= true;
previous= measure.time();
}

/*:290*//*292:*/
#line 7390 "./typica.w"

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

/*:292*/
#line 777 "./typica.w"

/*302:*/
#line 7587 "./typica.w"

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

/*:302*/
#line 778 "./typica.w"

/*307:*/
#line 7677 "./typica.w"

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

/*:307*/
#line 779 "./typica.w"

/*312:*/
#line 7793 "./typica.w"

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
/*313:*/
#line 7821 "./typica.w"

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

/*:313*/
#line 7806 "./typica.w"
;
/*315:*/
#line 7887 "./typica.w"

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

/*:315*/
#line 7807 "./typica.w"
;
fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

/*:312*//*314:*/
#line 7857 "./typica.w"

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

/*:314*//*316:*/
#line 7906 "./typica.w"

void GraphView::resizeEvent(QResizeEvent*)
{
fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

/*:316*//*317:*/
#line 7917 "./typica.w"

#define FULLTIMETOINT(t) (t.msec() + (t.second() * 1000) +  (t.minute() * 60 * 1000))

void GraphView::newMeasurement(Measurement measure,int tempcolumn)
{
double offset= 0;
if(translations->contains(tempcolumn))
{
offset= translations->value(tempcolumn);
}
if(prevPoints->contains(tempcolumn))
{
/*319:*/
#line 7976 "./typica.w"

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

/*:319*/
#line 7929 "./typica.w"

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
/*318:*/
#line 7965 "./typica.w"

int x= FULLTIMETOINT(measure.time())/1000;
prevPoints->insert(tempcolumn,QPointF(x,measure.temperature()));

/*:318*/
#line 7946 "./typica.w"

}
}

/*:317*//*320:*/
#line 7993 "./typica.w"

void GraphView::clear()
{
int i;
foreach(i,prevPoints->keys())
{
removeSeries(i);
}
translations->clear();
}

/*:320*//*321:*/
#line 8007 "./typica.w"

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

/*:321*//*322:*/
#line 8026 "./typica.w"

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

/*:322*/
#line 780 "./typica.w"

/*328:*/
#line 8176 "./typica.w"

void ZoomLog::newMeasurement(Measurement measure,int tempcolumn)
{
/*330:*/
#line 8247 "./typica.w"

if(lastMeasurement[tempcolumn].time()<measure.time())
{
QList<QTime> timelist;
for(QTime i= lastMeasurement[tempcolumn].time().addSecs(1);i<measure.time();i= i.addSecs(1))
{
timelist.append(i);
}
for(int i= 0;i<timelist.size();i++)
{
newMeasurement(Measurement(measure.temperature(),timelist[i],measure.scale()),tempcolumn);
}
}

/*:330*/
#line 8179 "./typica.w"

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
/*332:*/
#line 8286 "./typica.w"

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

/*:332*/
#line 8211 "./typica.w"

}
else
{
/*329:*/
#line 8223 "./typica.w"

MeasurementModel*m;
foreach(m,modelSet)
{
m->newMeasurement(measure,tempcolumn);
}

/*:329*/
#line 8215 "./typica.w"

}
lastMeasurement[tempcolumn]= measure;
}

/*:328*//*331:*/
#line 8272 "./typica.w"

void ZoomLog::addToCurrentColumnSet(int column)
{
currentColumnSet.append(column);
}

void ZoomLog::clearCurrentColumnSet()
{
currentColumnSet.clear();
}

/*:331*//*333:*/
#line 8355 "./typica.w"

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

/*:333*//*334:*/
#line 8379 "./typica.w"

void ZoomLog::centerOn(int row)
{
scrollTo(currentModel->index(row,0),QAbstractItemView::PositionAtCenter);
}

/*:334*//*335:*/
#line 8389 "./typica.w"

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

/*:335*//*336:*/
#line 8406 "./typica.w"

QVariant ZoomLog::data(int row,int column)const
{
return model_ms->data(model_ms->index(row,column,QModelIndex()),
Qt::DisplayRole);
}

int ZoomLog::rowCount()
{
return model_ms->rowCount();
}

/*:336*//*337:*/
#line 8429 "./typica.w"

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

/*:337*//*338:*/
#line 8460 "./typica.w"

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

/*:338*//*339:*/
#line 8484 "./typica.w"

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

/*:339*//*340:*/
#line 8532 "./typica.w"

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

/*:340*//*341:*/
#line 8552 "./typica.w"

QString ZoomLog::lastTime(int series)
{
Measurement measure= lastMeasurement.value(series);
QTime time= measure.time();
return time.toString("h:mm:ss.zzz");
}

/*:341*//*342:*/
#line 8562 "./typica.w"

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

/*:342*//*343:*/
#line 8585 "./typica.w"

void ZoomLog::setHeaderData(int section,QString text)
{
MeasurementModel*m;
foreach(m,modelSet)
{
m->setHeaderData(section,Qt::Horizontal,QVariant(text));
}
}

/*:343*//*344:*/
#line 8599 "./typica.w"

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

/*:344*//*345:*/
#line 8619 "./typica.w"

void ZoomLog::persistColumnResize(int column,int,int newsize)
{
/*535:*/
#line 12597 "./typica.w"

QSettings settings;
/*536:*/
#line 12610 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:536*/
#line 12599 "./typica.w"

settings.setValue(QString("columnWidths/%1/%2/%3").
arg(topLevelWidget->objectName()).
arg(objectName()).arg(column),
QVariant(newsize));

/*:535*/
#line 8622 "./typica.w"

}

void ZoomLog::restoreColumnWidths()
{
/*538:*/
#line 12630 "./typica.w"

QSettings settings;
/*536:*/
#line 12610 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:536*/
#line 12632 "./typica.w"

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

/*:538*/
#line 8627 "./typica.w"

}

void ZoomLog::setVisible(bool visibility)
{
QTableView::setVisible(visibility);
}

void ZoomLog::showEvent(QShowEvent*)
{
/*538:*/
#line 12630 "./typica.w"

QSettings settings;
/*536:*/
#line 12610 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:536*/
#line 12632 "./typica.w"

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

/*:538*/
#line 8637 "./typica.w"

}

/*:345*/
#line 781 "./typica.w"

/*353:*/
#line 8859 "./typica.w"

bool MeasurementList::operator<(const MeasurementList&other)const
{
return this->first().toTime()<other.first().toTime();
}

bool MeasurementList::operator==(const MeasurementList&other)const
{
return this->first().toTime()==other.first().toTime();
}

/*:353*//*354:*/
#line 8875 "./typica.w"

QModelIndex MeasurementModel::parent(const QModelIndex&)const
{
return QModelIndex();
}

/*:354*//*355:*/
#line 8885 "./typica.w"

void MeasurementModel::newMeasurement(Measurement measure,int tempcolumn)
{
MeasurementList*temp;
temp= new MeasurementList;
temp->append(QVariant(measure.time()));
/*356:*/
#line 8936 "./typica.w"

/*357:*/
#line 8981 "./typica.w"

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

/*:357*/
#line 8937 "./typica.w"

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

/*:356*/
#line 8891 "./typica.w"

MeasurementList*newEntry;
int insertion;
if(i!=entries->end())
{
insertion= entries->indexOf(*i);
if((*i)->first().toTime()==measure.time())
{
/*358:*/
#line 9023 "./typica.w"

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

/*:358*/
#line 8899 "./typica.w"

}
else
{
/*359:*/
#line 9041 "./typica.w"

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

/*:359*/
#line 8903 "./typica.w"

}
}
else
{
/*360:*/
#line 9059 "./typica.w"

insertion= entries->size();
/*359:*/
#line 9041 "./typica.w"

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

/*:359*/
#line 9061 "./typica.w"


/*:360*/
#line 8908 "./typica.w"

}
if(tempcolumn>=colcount)
{
colcount= tempcolumn+1;
}
emit rowChanged(insertion);
delete temp;
}

/*:355*//*361:*/
#line 9070 "./typica.w"

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
/*362:*/
#line 9108 "./typica.w"

beginInsertRows(QModelIndex(),0,0);
MeasurementList*newEntry= new MeasurementList;
newEntry->append(QVariant(QTime(0,0,0,0)));
entries->append(newEntry);
endInsertRows();

/*:362*/
#line 9085 "./typica.w"

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

/*:361*//*363:*/
#line 9119 "./typica.w"

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

/*:363*//*364:*/
#line 9145 "./typica.w"

bool MeasurementModel::setData(const QModelIndex&index,
const QVariant&value,int role)
{
if(role!=Qt::EditRole&&role!=Qt::DisplayRole)
{
return false;
}
/*365:*/
#line 9177 "./typica.w"

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

/*:365*/
#line 9153 "./typica.w"

if(!valid)
{
return false;
}
MeasurementList*row= entries->at(index.row());
if(index.column()>=row->size())
{
/*366:*/
#line 9194 "./typica.w"

for(int i= row->size()-1;i<index.column();i++)
{
row->append(QVariant());
}

/*:366*/
#line 9161 "./typica.w"

}
if(index.column()==0)
{
/*367:*/
#line 9209 "./typica.w"

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
/*356:*/
#line 8936 "./typica.w"

/*357:*/
#line 8981 "./typica.w"

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

/*:357*/
#line 8937 "./typica.w"

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

/*:356*/
#line 9221 "./typica.w"

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

/*:367*/
#line 9165 "./typica.w"

}
else
{
/*368:*/
#line 9235 "./typica.w"

row->replace(index.column(),value);
emit dataChanged(index,index);

/*:368*/
#line 9169 "./typica.w"

}
return true;
}

/*:364*//*369:*/
#line 9243 "./typica.w"

MeasurementModel::MeasurementModel(QObject*parent):QAbstractItemModel(parent),
unit(Fahrenheit),hData(new QStringList),
lastTemperature(new QHash<int,int> )
{
colcount= 1;
entries= new QList<MeasurementList*> ;
lastInsertion= entries->begin();
hData->append(tr("Time"));
}

/*:369*//*370:*/
#line 9256 "./typica.w"

MeasurementModel::~MeasurementModel()
{
clear();
delete entries;
delete hData;
}

/*:370*//*371:*/
#line 9268 "./typica.w"

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

/*:371*//*372:*/
#line 9295 "./typica.w"

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

/*:372*//*373:*/
#line 9335 "./typica.w"

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

/*:373*//*374:*/
#line 9359 "./typica.w"

QVariant MeasurementModel::data(const QModelIndex&index,int role)const
{
/*365:*/
#line 9177 "./typica.w"

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

/*:365*/
#line 9362 "./typica.w"

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

/*:374*//*375:*/
#line 9416 "./typica.w"

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

/*:375*//*376:*/
#line 9443 "./typica.w"

Qt::ItemFlags MeasurementModel::flags(const QModelIndex&index)const
{
/*365:*/
#line 9177 "./typica.w"

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

/*:365*/
#line 9446 "./typica.w"

if(valid)
{
return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
}
return 0;
}

/*:376*//*377:*/
#line 9458 "./typica.w"

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

/*:377*/
#line 782 "./typica.w"

/*379:*/
#line 9509 "./typica.w"

AnnotationButton::AnnotationButton(const QString&text,QWidget*parent):
QPushButton(text,parent),note(""),tc(0),ac(0),count(0)
{
connect(this,SIGNAL(clicked()),this,SLOT(annotate()));
}

/*:379*//*380:*/
#line 9524 "./typica.w"

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

/*:380*//*381:*/
#line 9542 "./typica.w"

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

/*:381*//*382:*/
#line 9561 "./typica.w"

void AnnotationButton::resetCount()
{
count= 0;
}

/*:382*/
#line 783 "./typica.w"

/*387:*/
#line 9644 "./typica.w"

AnnotationSpinBox::AnnotationSpinBox(const QString&pret,
const QString&postt,
QWidget*parent)
:QDoubleSpinBox(parent),pretext(pret),posttext(postt)
{
resetChange();
connect(this,SIGNAL(editingFinished()),this,SLOT(annotate()));
connect(this,SIGNAL(valueChanged(double)),this,SLOT(resetChange()));
}

/*:387*//*388:*/
#line 9661 "./typica.w"

void AnnotationSpinBox::resetChange()
{
change= true;
}

/*:388*//*389:*/
#line 9672 "./typica.w"

void AnnotationSpinBox::annotate()
{
if(change)
{
change= false;
emit annotation(QString("%1%2%3").arg(pretext).
arg(value()).arg(posttext),tc,ac);
}
}

/*:389*//*390:*/
#line 9685 "./typica.w"

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

/*:390*/
#line 784 "./typica.w"

/*397:*/
#line 9853 "./typica.w"

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

/*:397*//*398:*/
#line 9874 "./typica.w"

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
/*399:*/
#line 9906 "./typica.w"

/*400:*/
#line 9919 "./typica.w"

#define TIMETOINT(t) ((t.hour() * 60 * 60) + (t.minute() * 60) + (t.second()))

time= QTime::currentTime();
cseconds= TIMETOINT(time);
oseconds= TIMETOINT(relative);
r= cseconds-oseconds;

/*:400*/
#line 9907 "./typica.w"

nt= nt.addSecs(r);
if(nt!=s)
{
s= nt;
emit valueChanged(s);
}

/*:399*/
#line 9887 "./typica.w"
;
break;
case TimerDisplay::CountDown:
/*401:*/
#line 9931 "./typica.w"

if(s> QTime(0,0,0))
{
/*400:*/
#line 9919 "./typica.w"

#define TIMETOINT(t) ((t.hour() * 60 * 60) + (t.minute() * 60) + (t.second()))

time= QTime::currentTime();
cseconds= TIMETOINT(time);
oseconds= TIMETOINT(relative);
r= cseconds-oseconds;

/*:400*/
#line 9934 "./typica.w"

bseconds= TIMETOINT(base);
n= bseconds-r;
nt= nt.addSecs(n);
if(nt!=s)
{
s= nt;
emit valueChanged(s);
}
}

/*:401*/
#line 9890 "./typica.w"
;
break;
case TimerDisplay::Clock:
/*402:*/
#line 9948 "./typica.w"

time= QTime::currentTime();
if(time!=s)
{
s= time;
emit valueChanged(s);
}

/*:402*/
#line 9893 "./typica.w"
;
break;
default:
Q_ASSERT_X(false,"updateTime","invalid timer mode");
break;
}
updateDisplay();
}

/*:398*//*403:*/
#line 9960 "./typica.w"

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

/*:403*//*404:*/
#line 9990 "./typica.w"

void TimerDisplay::stopTimer()
{
if(running)
{
clock.stop();
running= false;
emit runStateChanged(false);
}
}

/*:404*//*405:*/
#line 10003 "./typica.w"

TimerDisplay::~TimerDisplay()
{
clock.stop();
}

/*:405*//*406:*/
#line 10012 "./typica.w"

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

/*:406*//*407:*/
#line 10030 "./typica.w"

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

/*:407*//*408:*/
#line 10068 "./typica.w"

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

/*:408*//*409:*/
#line 10103 "./typica.w"

void TimerDisplay::copyTimer()
{
QApplication::clipboard()->setText(value());
}

/*:409*//*410:*/
#line 10112 "./typica.w"

void TimerDisplay::reset()
{
if(!running)
{
s= r;
updateDisplay();
}
}

/*:410*//*411:*/
#line 10125 "./typica.w"

void TimerDisplay::updateDisplay()
{
display(value());
}

/*:411*/
#line 785 "./typica.w"

/*417:*/
#line 10219 "./typica.w"

int PackLayout::doLayout(const QRect&rect,bool testOnly)const
{
int x= rect.x();
int y= rect.y();
QLayoutItem*item;
if(orientation==Qt::Horizontal)
{
/*418:*/
#line 10243 "./typica.w"

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

/*:418*/
#line 10227 "./typica.w"

}
else
{
/*419:*/
#line 10262 "./typica.w"

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

/*:419*/
#line 10231 "./typica.w"

}
return y;
}

/*:417*//*420:*/
#line 10286 "./typica.w"

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

/*:420*//*421:*/
#line 10318 "./typica.w"

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

/*:421*//*422:*/
#line 10336 "./typica.w"

PackLayout::~PackLayout()
{
QLayoutItem*item;
while((item= takeAt(0)))
{
delete item;
}
}

/*:422*//*423:*/
#line 10350 "./typica.w"

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

/*:423*//*424:*/
#line 10366 "./typica.w"

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

/*:424*//*425:*/
#line 10389 "./typica.w"

void PackLayout::addItem(QLayoutItem*item)
{
itemList.append(item);
}

/*:425*//*426:*/
#line 10397 "./typica.w"

int PackLayout::count()const
{
return itemList.size();
}

/*:426*//*427:*/
#line 10409 "./typica.w"

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

/*:427*//*428:*/
#line 10440 "./typica.w"

void PackLayout::setOrientation(Qt::Orientations direction)
{
orientation= direction;
doLayout(geometry(),false);
}

/*:428*/
#line 786 "./typica.w"

/*430:*/
#line 10479 "./typica.w"

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

/*:430*/
#line 787 "./typica.w"

/*432:*/
#line 10525 "./typica.w"

WidgetDecorator::WidgetDecorator(QWidget*widget,const QString&labeltext,
Qt::Orientations orientation,
QWidget*parent,Qt::WindowFlags f):
QWidget(parent,f),label(new QGraphicsView()),
scene(new SceneButton())
{
layout= new PackLayout(this);
layout->setOrientation(orientation);
/*433:*/
#line 10545 "./typica.w"

label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setFrameShape(QFrame::NoFrame);
label->setInteractive(true);

/*:433*/
#line 10534 "./typica.w"

/*434:*/
#line 10556 "./typica.w"

scene->setBackgroundBrush(Qt::cyan);
text= scene->addText(labeltext);
if(orientation==Qt::Horizontal)
{
text->rotate(270.0);
}
label->setScene(scene);

/*:434*/
#line 10535 "./typica.w"

/*435:*/
#line 10574 "./typica.w"

if(orientation==Qt::Horizontal)
{
label->setMaximumWidth((int)(text->boundingRect().height()+1));
}
else
{
label->setMaximumHeight((int)(text->boundingRect().height()+1));
}
label->centerOn(text);

/*:435*/
#line 10536 "./typica.w"

/*436:*/
#line 10589 "./typica.w"

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

/*:436*/
#line 10537 "./typica.w"

}

/*:432*//*437:*/
#line 10606 "./typica.w"

void WidgetDecorator::setBackgroundBrush(QBrush background)
{
scene->setBackgroundBrush(background);
}

void WidgetDecorator::setTextColor(QColor color)
{
text->setDefaultTextColor(color);
}

/*:437*//*438:*/
#line 10619 "./typica.w"

WidgetDecorator::~WidgetDecorator()
{

}

/*:438*/
#line 788 "./typica.w"

/*443:*/
#line 10718 "./typica.w"

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

/*:443*//*444:*/
#line 10732 "./typica.w"

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
/*445:*/
#line 10769 "./typica.w"

QSettings settings;
resize(settings.value("logSize",QSize(620,400)).toSize());
move(settings.value("logPos",QPoint(200,60)).toPoint());

/*:445*/
#line 10749 "./typica.w"

/*446:*/
#line 10782 "./typica.w"

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

/*:446*/
#line 10750 "./typica.w"

/*447:*/
#line 10805 "./typica.w"

model->setHeaderData(0,Qt::Horizontal,"Time");
model->setHeaderData(1,Qt::Horizontal,"Temperature");
model->setHeaderData(2,Qt::Horizontal,"Annotation");
model->clear();

/*:447*/
#line 10751 "./typica.w"

/*448:*/
#line 10814 "./typica.w"

log->setModel(model);
log->setColumnWidth(0,100);
log->setColumnWidth(1,100);
log->setColumnWidth(2,100);

/*:448*/
#line 10752 "./typica.w"

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

/*:444*//*449:*/
#line 10825 "./typica.w"

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

/*:449*//*450:*/
#line 10868 "./typica.w"

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

/*:450*//*451:*/
#line 10899 "./typica.w"

void LogEditWindow::closeEvent(QCloseEvent*event)
{
QSettings settings;
settings.setValue("logSize",size());
settings.setValue("logPos",pos());
event->accept();
}

/*:451*/
#line 789 "./typica.w"

/*457:*/
#line 11012 "./typica.w"

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
/*458:*/
#line 11045 "./typica.w"

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

/*:458*/
#line 11023 "./typica.w"

xmlout.writeStartElement("roast");
bool oresult;
for(int i= 0;i<data->rowCount();i++)
{
/*459:*/
#line 11064 "./typica.w"

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

/*:459*/
#line 11028 "./typica.w"

if(oresult)
{
/*460:*/
#line 11094 "./typica.w"

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

/*:460*/
#line 11031 "./typica.w"

}
}
xmlout.writeEndElement();
xmlout.writeEndElement();
xmlout.writeEndDocument();
out->close();
return true;
}

/*:457*//*461:*/
#line 11126 "./typica.w"

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

/*:461*//*462:*/
#line 11155 "./typica.w"

void XMLOutput::addTemperatureColumn(const QString&series,int column)
{
temperatureColumns.insert(column,series);
}

void XMLOutput::addAnnotationColumn(const QString&series,int column)
{
annotationColumns.insert(column,series);
}

/*:462*/
#line 790 "./typica.w"

/*464:*/
#line 11207 "./typica.w"

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
/*465:*/
#line 11238 "./typica.w"

while(!xmlin.isDTD())
{
xmlin.readNext();
}
if(xmlin.isDTD())
{
if(xmlin.text()=="<!DOCTYPE roastlog>")
{
/*466:*/
#line 11260 "./typica.w"

emit newTemperatureColumn(firstc,"Bean");
emit newAnnotationColumn(firstc+1,"Note");
emit lastColumn(firstc+1);

/*:466*/
#line 11247 "./typica.w"

}
else
{
xmlin.readNext();
/*467:*/
#line 11269 "./typica.w"

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

/*:467*/
#line 11252 "./typica.w"

}
}

/*:465*/
#line 11218 "./typica.w"

QTime timeval= QTime();
double tempval= 0;
QString noteval= QString();
int column;
int counter= 0;
while(!xmlin.atEnd())
{
/*468:*/
#line 11310 "./typica.w"

xmlin.readNext();
if(xmlin.isStartElement())
{
/*469:*/
#line 11336 "./typica.w"

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

/*:469*/
#line 11314 "./typica.w"

}
counter++;
if(counter%100==0)
{
QCoreApplication::processEvents();
}

/*:468*/
#line 11226 "./typica.w"

}
return true;
}

/*:464*//*470:*/
#line 11364 "./typica.w"

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

/*:470*/
#line 791 "./typica.w"

/*475:*/
#line 11453 "./typica.w"

bool CSVOutput::output()
{
if(!out->open(QIODevice::WriteOnly|QIODevice::Text))
{
return false;
}
QTextStream output(out);
/*476:*/
#line 11477 "./typica.w"

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

/*:476*/
#line 11461 "./typica.w"

bool oresult;
for(int i= 0;i<data->rowCount();i++)
{
/*459:*/
#line 11064 "./typica.w"

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

/*:459*/
#line 11465 "./typica.w"

if(oresult)
{
/*477:*/
#line 11498 "./typica.w"

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

/*:477*/
#line 11468 "./typica.w"

}
}
out->close();
return true;
}

/*:475*//*478:*/
#line 11513 "./typica.w"

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

/*:478*/
#line 792 "./typica.w"

/*497:*/
#line 11895 "./typica.w"

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

/*:497*//*498:*/
#line 11939 "./typica.w"

QModelIndex SaltModel::parent(const QModelIndex&)const
{
return QModelIndex();
}

/*:498*//*499:*/
#line 11958 "./typica.w"

bool SaltModel::setData(const QModelIndex&index,const QVariant&value,
int role)
{
/*500:*/
#line 11989 "./typica.w"

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

/*:500*/
#line 11962 "./typica.w"

if(!valid)
{
return false;
}
if(index.row()==modelData.size()-1)
{
beginInsertRows(QModelIndex(),modelData.size(),modelData.size());
/*501:*/
#line 12005 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:501*/
#line 11970 "./typica.w"

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

/*:499*//*502:*/
#line 12016 "./typica.w"

SaltModel::SaltModel(int columns):QAbstractItemModel(),colcount(columns)
{
for(int i= 0;i<columns;i++)
{
hData<<"";
}
/*501:*/
#line 12005 "./typica.w"

QList<QMap<int,QVariant> > newRow;
QMap<int,QVariant> defaults;
for(int i= 0;i<colcount;i++)
{
newRow.append(defaults);
}
modelData.append(newRow);

/*:501*/
#line 12023 "./typica.w"

}

/*:502*//*503:*/
#line 12028 "./typica.w"

SaltModel::~SaltModel()
{

}

/*:503*//*504:*/
#line 12038 "./typica.w"

int SaltModel::rowCount(const QModelIndex&parent)const
{
return(parent==QModelIndex()?modelData.size():0);
}

int SaltModel::columnCount(const QModelIndex&parent)const
{
return(parent==QModelIndex()?colcount:0);
}

/*:504*//*505:*/
#line 12051 "./typica.w"

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

/*:505*//*506:*/
#line 12066 "./typica.w"

QVariant SaltModel::data(const QModelIndex&index,int role)const
{
/*500:*/
#line 11989 "./typica.w"

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

/*:500*/
#line 12069 "./typica.w"

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

/*:506*//*507:*/
#line 12093 "./typica.w"

Qt::ItemFlags SaltModel::flags(const QModelIndex&index)const
{
/*500:*/
#line 11989 "./typica.w"

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

/*:500*/
#line 12096 "./typica.w"

if(valid)
{
return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
}
return 0;
}

/*:507*//*508:*/
#line 12107 "./typica.w"

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

/*:508*/
#line 793 "./typica.w"

/*510:*/
#line 12162 "./typica.w"

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

/*:510*//*511:*/
#line 12179 "./typica.w"

void SqlComboBox::showData(bool show)
{
dataColumnShown= show;
}

/*:511*//*512:*/
#line 12190 "./typica.w"

void SqlComboBox::addNullOption()
{
addItem(tr("Unknown"),QVariant(QVariant::String));
}

/*:512*//*513:*/
#line 12203 "./typica.w"

void SqlComboBox::setDataColumn(int column)
{
dataColumn= column;
}

void SqlComboBox::setDisplayColumn(int column)
{
displayColumn= column;
}

/*:513*//*514:*/
#line 12217 "./typica.w"

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

/*:514*//*515:*/
#line 12246 "./typica.w"

SqlComboBox::SqlComboBox():
dataColumn(0),displayColumn(0),dataColumnShown(false)
{

}

SqlComboBox::~SqlComboBox()
{

}

/*:515*/
#line 794 "./typica.w"

/*517:*/
#line 12284 "./typica.w"

void SqlComboBoxDelegate::setWidget(SqlComboBox*widget)
{
delegate= widget;
}

/*:517*//*518:*/
#line 12293 "./typica.w"

QWidget*SqlComboBoxDelegate::createEditor(QWidget*parent,
const QStyleOptionViewItem&,
const QModelIndex&)const
{
return delegate->clone(parent);
}

/*:518*//*519:*/
#line 12304 "./typica.w"

void SqlComboBoxDelegate::setEditorData(QWidget*editor,
const QModelIndex&index)const
{
SqlComboBox*self= qobject_cast<SqlComboBox*> (editor);
self->setCurrentIndex(self->findData(
index.model()->data(index,
Qt::UserRole).toString()));
}

/*:519*//*520:*/
#line 12317 "./typica.w"

void SqlComboBoxDelegate::setModelData(QWidget*editor,
QAbstractItemModel*model,
const QModelIndex&index)const
{
SqlComboBox*self= qobject_cast<SqlComboBox*> (editor);
model->setData(index,self->itemData(self->currentIndex(),Qt::UserRole),
Qt::UserRole);
model->setData(index,self->currentText(),Qt::DisplayRole);
}

/*:520*//*521:*/
#line 12330 "./typica.w"

void SqlComboBoxDelegate::updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&)const
{
editor->setGeometry(option.rect);
}

/*:521*//*522:*/
#line 12341 "./typica.w"

QSize SqlComboBoxDelegate::sizeHint()const
{
return delegate->sizeHint();
}

/*:522*//*523:*/
#line 12349 "./typica.w"

SqlComboBoxDelegate::SqlComboBoxDelegate(QObject*parent)
:QItemDelegate(parent)
{

}

/*:523*/
#line 795 "./typica.w"

/*489:*/
#line 11709 "./typica.w"

Application::Application(int&argc,char**argv):QApplication(argc,argv)
{
/*490:*/
#line 11724 "./typica.w"

setOrganizationName("Wilson's Coffee & Tea");
setOrganizationDomain("wilsonscoffee.com");
setApplicationName(PROGRAM_NAME);

/*:490*/
#line 11712 "./typica.w"

/*491:*/
#line 11733 "./typica.w"

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

/*:491*/
#line 11713 "./typica.w"

/*228:*/
#line 5736 "./typica.w"

qRegisterMetaType<Measurement> ("Measurement");

/*:228*/
#line 11714 "./typica.w"

/*668:*/
#line 15429 "./typica.w"

NodeInserter*inserter= new NodeInserter(tr("NI DAQmx Base Device"),
tr("NI DAQmx Base"),
"nidaqmxbase",NULL);
topLevelNodeInserters.append(inserter);

/*:668*//*676:*/
#line 15646 "./typica.w"

#ifdef Q_OS_WIN32
inserter= new NodeInserter(tr("NI DAQmx Device"),tr("NI DAQmx"),"nidaqmx",NULL);
topLevelNodeInserters.append(inserter);
#endif

/*:676*//*700:*/
#line 16605 "./typica.w"

#if 0
inserter= new NodeInserter(tr("Modbus RTU Port"),tr("Modbus RTU Port"),"modbusrtuport",NULL);
topLevelNodeInserters.append(inserter);
#endif

/*:700*//*729:*/
#line 18055 "./typica.w"

inserter= new NodeInserter(tr("Modbus RTU Device"),tr("Modbus RTU Device"),"modbusrtu",NULL);
topLevelNodeInserters.append(inserter);

/*:729*/
#line 11715 "./typica.w"

}

/*:489*//*493:*/
#line 11756 "./typica.w"

QDomDocument*Application::configuration()
{
return&conf;
}

/*:493*//*494:*/
#line 11765 "./typica.w"

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

/*:494*//*604:*/
#line 14084 "./typica.w"

void Application::saveDeviceConfiguration()
{
QSettings settings;
settings.setValue("DeviceConfiguration",
QVariant(deviceConfigurationDocument.toByteArray()));
}

/*:604*//*605:*/
#line 14096 "./typica.w"

QDomDocument Application::deviceConfiguration()
{
if(deviceConfigurationDocument.isNull())
{
/*606:*/
#line 14110 "./typica.w"

QSettings settings;
QByteArray document= settings.value("DeviceConfiguration").toByteArray();
QString etext;
int eline;
int ecol;
if(document.length()==0)
{
qDebug()<<"Loaded settings length is 0. Creating new configuration.";
/*607:*/
#line 14134 "./typica.w"

QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument,false,
&etext,&eline,&ecol))
{
/*608:*/
#line 14151 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:608*/
#line 14140 "./typica.w"

}
else
{
saveDeviceConfiguration();
}

/*:607*/
#line 14119 "./typica.w"

}
else
{
if(!deviceConfigurationDocument.setContent(document,false,
&etext,&eline,&ecol))
{
/*608:*/
#line 14151 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:608*/
#line 14126 "./typica.w"

/*607:*/
#line 14134 "./typica.w"

QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument,false,
&etext,&eline,&ecol))
{
/*608:*/
#line 14151 "./typica.w"

qDebug()<<QString(tr("An error occurred loading device configuration."));
qDebug()<<QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug()<<etext;

/*:608*/
#line 14140 "./typica.w"

}
else
{
saveDeviceConfiguration();
}

/*:607*/
#line 14127 "./typica.w"

}
}

/*:606*/
#line 14101 "./typica.w"

}
return deviceConfigurationDocument;
}

/*:605*//*636:*/
#line 14752 "./typica.w"

void Application::registerDeviceConfigurationWidget(QString driver,
QMetaObject widget)
{
deviceConfigurationWidgets.insert(driver,widget);
}

/*:636*//*637:*/
#line 14768 "./typica.w"

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

/*:637*/
#line 796 "./typica.w"

/*528:*/
#line 12444 "./typica.w"

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

/*:528*//*529:*/
#line 12478 "./typica.w"

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

/*:529*/
#line 797 "./typica.w"

/*533:*/
#line 12573 "./typica.w"

SqlQueryView::SqlQueryView(QWidget*parent):QTableView(parent)
{
setModel(new QSqlQueryModel);
connect(this,SIGNAL(doubleClicked(QModelIndex)),
this,SLOT(openRow(QModelIndex)));
connect(horizontalHeader(),SIGNAL(sectionResized(int,int,int)),
this,SLOT(persistColumnResize(int,int,int)));
}

/*:533*//*534:*/
#line 12588 "./typica.w"

void SqlQueryView::persistColumnResize(int column,int,int newsize)
{
/*535:*/
#line 12597 "./typica.w"

QSettings settings;
/*536:*/
#line 12610 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:536*/
#line 12599 "./typica.w"

settings.setValue(QString("columnWidths/%1/%2/%3").
arg(topLevelWidget->objectName()).
arg(objectName()).arg(column),
QVariant(newsize));

/*:535*/
#line 12591 "./typica.w"

}

/*:534*//*537:*/
#line 12620 "./typica.w"

void SqlQueryView::showEvent(QShowEvent*event)
{
/*538:*/
#line 12630 "./typica.w"

QSettings settings;
/*536:*/
#line 12610 "./typica.w"

QWidget*topLevelWidget= this;
while(topLevelWidget->parentWidget())
{
topLevelWidget= topLevelWidget->parentWidget();
}

/*:536*/
#line 12632 "./typica.w"

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

/*:538*/
#line 12623 "./typica.w"

event->accept();
}

/*:537*//*539:*/
#line 12647 "./typica.w"

void SqlQueryView::openRow(const QModelIndex&index)
{
emit openEntry(((QSqlQueryModel*)model())->record(index.row()).value(0).toString());
emit openEntryRow(index.row());
}

/*:539*//*540:*/
#line 12658 "./typica.w"

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

/*:540*//*541:*/
#line 12675 "./typica.w"

QVariant SqlQueryView::data(int row,int column,int role)
{
return model()->data(model()->index(row,column),role);
}

/*:541*/
#line 798 "./typica.w"

/*137:*/
#line 3283 "./typica.w"

SqlQueryConnection::SqlQueryConnection(const QString&query)
{
QSqlDatabase database= AppInstance->database();
database.open();
q= new QSqlQuery(query,database);
connection= database.connectionName();
}

/*:137*//*138:*/
#line 3296 "./typica.w"

SqlQueryConnection::~SqlQueryConnection()
{
delete q;
{
QSqlDatabase database= QSqlDatabase::database(connection);
database.close();
}
QSqlDatabase::removeDatabase(connection);
}

/*:138*//*139:*/
#line 3310 "./typica.w"

QSqlQuery*SqlQueryConnection::operator->()
{
return q;
}

/*:139*/
#line 799 "./typica.w"

/*560:*/
#line 13024 "./typica.w"

ReportTable::ReportTable(QTextFrame*frame,QDomElement description):
area(frame),configuration(description)
{
refresh();
}

ReportTable::~ReportTable()
{

}

/*:560*//*561:*/
#line 13040 "./typica.w"

void ReportTable::bind(QString placeholder,QVariant value)
{
bindings.insert(placeholder,value);
}

/*:561*//*562:*/
#line 13050 "./typica.w"

void ReportTable::refresh()
{
/*563:*/
#line 13071 "./typica.w"

QTextCursor cursor= area->firstCursorPosition();
while(cursor<area->lastCursorPosition())
{
cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
}
cursor.removeSelectedText();

/*:563*/
#line 13053 "./typica.w"

int rows= 1;
int columns= 1;
int currentRow= 0;
QTextTable*table= cursor.insertTable(rows,columns);
/*564:*/
#line 13084 "./typica.w"

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

/*:564*/
#line 13058 "./typica.w"

/*565:*/
#line 13098 "./typica.w"

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
/*566:*/
#line 13125 "./typica.w"

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

/*:566*/
#line 13110 "./typica.w"

}
else if(currentElement.tagName()=="row")
{
/*567:*/
#line 13164 "./typica.w"

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

/*:567*/
#line 13114 "./typica.w"

}
}
}

/*:565*/
#line 13059 "./typica.w"

if(rows> 1)
{
table->removeRows(0,1);
}
}

/*:562*/
#line 800 "./typica.w"

/*572:*/
#line 13266 "./typica.w"

FormArray::FormArray(QDomElement description):configuration(description),
maxwidth(-1),maxheight(-1)
{
setWidget(&itemContainer);
itemContainer.setLayout(&itemLayout);
}

/*:572*//*573:*/
#line 13283 "./typica.w"

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

/*:573*//*574:*/
#line 13333 "./typica.w"

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

/*:574*//*575:*/
#line 13350 "./typica.w"

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

/*:575*//*576:*/
#line 13366 "./typica.w"

int FormArray::elements()
{
return itemLayout.count();
}

/*:576*//*577:*/
#line 13377 "./typica.w"

void FormArray::setMaximumElementWidth(int width)
{
maxwidth= width;
}

void FormArray::setMaximumElementHeight(int height)
{
maxheight= height;
}

/*:577*/
#line 801 "./typica.w"

/*583:*/
#line 13508 "./typica.w"

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

/*:583*//*584:*/
#line 13581 "./typica.w"

QSize ScaleControl::sizeHint()const
{
return QSize(140,30);
}

/*:584*//*585:*/
#line 13590 "./typica.w"

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

/*:585*//*586:*/
#line 13627 "./typica.w"

double ScaleControl::initialValue(void)
{
return nonScoredValue;
}

double ScaleControl::finalValue(void)
{
return scoredValue;
}

/*:586*//*587:*/
#line 13648 "./typica.w"

void ScaleControl::mousePressEvent(QMouseEvent*event)
{
/*588:*/
#line 13660 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:588*/
#line 13651 "./typica.w"

scaleDown= true;
event->accept();
}

/*:587*//*589:*/
#line 13671 "./typica.w"

void ScaleControl::mouseReleaseEvent(QMouseEvent*event)
{
/*588:*/
#line 13660 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:588*/
#line 13674 "./typica.w"

if(!scaleDown)
{
event->ignore();
return;
}
scaleDown= false;
QPointF sceneCoordinate= mapToScene(event->x(),event->y());
/*590:*/
#line 13696 "./typica.w"

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

/*:590*/
#line 13682 "./typica.w"

/*591:*/
#line 13722 "./typica.w"

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

/*:591*/
#line 13683 "./typica.w"

/*592:*/
#line 13748 "./typica.w"

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

/*:592*/
#line 13684 "./typica.w"

event->ignore();
return;
}

/*:589*/
#line 802 "./typica.w"

/*594:*/
#line 13814 "./typica.w"

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

/*:594*//*595:*/
#line 13869 "./typica.w"

QSize IntensityControl::sizeHint()const
{
return QSize(25,160);
}

/*:595*//*596:*/
#line 13884 "./typica.w"

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

/*:596*//*597:*/
#line 13916 "./typica.w"

void IntensityControl::mousePressEvent(QMouseEvent*event)
{
/*588:*/
#line 13660 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:588*/
#line 13919 "./typica.w"

scaleDown= true;
event->accept();
}

/*:597*//*598:*/
#line 13930 "./typica.w"

void IntensityControl::mouseReleaseEvent(QMouseEvent*event)
{
/*588:*/
#line 13660 "./typica.w"

if(event->button()!=Qt::LeftButton)
{
event->ignore();
return;
}

/*:588*/
#line 13933 "./typica.w"

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

/*:598*/
#line 803 "./typica.w"

/*297:*/
#line 7486 "./typica.w"

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

/*:297*/
#line 804 "./typica.w"

/*679:*/
#line 15686 "./typica.w"

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

/*:679*/
#line 805 "./typica.w"

/*681:*/
#line 15774 "./typica.w"

BaudSelector::BaudSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= BaudSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("BaudRateType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString("%1").arg(type.value(i)));
}
}

/*:681*/
#line 806 "./typica.w"

/*683:*/
#line 15812 "./typica.w"

ParitySelector::ParitySelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= ParitySelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("ParityType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:683*/
#line 807 "./typica.w"

/*685:*/
#line 15842 "./typica.w"

FlowSelector::FlowSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= FlowSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("FlowType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:685*/
#line 808 "./typica.w"

/*687:*/
#line 15877 "./typica.w"

StopSelector::StopSelector(QWidget*parent):QComboBox(parent)
{
QMetaObject meta= StopSelector::staticMetaObject;
QMetaEnum type= meta.enumerator(meta.indexOfEnumerator("StopBitsType"));
for(int i= 0;i<type.keyCount();i++)
{
addItem(QString(type.key(i)),QVariant(type.value(i)));
}
}

/*:687*/
#line 809 "./typica.w"

/*727:*/
#line 17622 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 17708 "./typica.w"

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

/*:727*/
#line 810 "./typica.w"

/*690:*/
#line 15926 "./typica.w"

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

/*:690*/
#line 811 "./typica.w"

/*712:*/
#line 16952 "./typica.w"

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
/*713:*/
#line 17201 "./typica.w"

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

/*:713*/
#line 17188 "./typica.w"

}
else
{
/*714:*/
#line 17231 "./typica.w"

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

/*:714*/
#line 17192 "./typica.w"

}
}

/*:712*//*715:*/
#line 17269 "./typica.w"

ModbusRTUDevice::~ModbusRTUDevice()
{
messageDelayTimer->stop();
port->close();
}

/*:715*//*716:*/
#line 17291 "./typica.w"

void ModbusRTUDevice::dataAvailable()
{
if(messageDelayTimer->isActive())
{
messageDelayTimer->stop();
}
responseBuffer.append(port->readAll());
/*717:*/
#line 17336 "./typica.w"

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

/*:717*/
#line 17299 "./typica.w"

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

/*:716*//*718:*/
#line 17378 "./typica.w"

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

/*:718*//*719:*/
#line 17409 "./typica.w"

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

/*:719*//*720:*/
#line 17457 "./typica.w"

void ModbusRTUDevice::ignore(QByteArray)
{
return;
}

/*:720*/
#line 812 "./typica.w"

/*610:*/
#line 14188 "./typica.w"

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

/*:610*/
#line 813 "./typica.w"

/*612:*/
#line 14277 "./typica.w"

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

/*:612*//*613:*/
#line 14312 "./typica.w"

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
/*614:*/
#line 14331 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:614*/
#line 14324 "./typica.w"

return parentItem->node().childNodes().count();
}

/*:613*//*615:*/
#line 14345 "./typica.w"

QModelIndex DeviceTreeModel::index(int row,int column,
const QModelIndex&parent)const
{
if(!hasIndex(row,column,parent))
{
return QModelIndex();
}
/*614:*/
#line 14331 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:614*/
#line 14353 "./typica.w"

DeviceTreeModelNode*childItem= parentItem->child(row);
if(childItem)
{
return createIndex(row,column,childItem);
}
return QModelIndex();
}

/*:615*//*616:*/
#line 14364 "./typica.w"

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

/*:616*//*617:*/
#line 14383 "./typica.w"

Qt::ItemFlags DeviceTreeModel::flags(const QModelIndex&index)const
{
if(!index.isValid())
{
return 0;
}
return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

/*:617*//*618:*/
#line 14398 "./typica.w"

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

/*:618*//*619:*/
#line 14430 "./typica.w"

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

/*:619*//*620:*/
#line 14453 "./typica.w"

void DeviceTreeModel::newNode(const QString&name,const QString&driver,
const QModelIndex&parent)
{
QString referenceID= QUuid::createUuid().toString();
/*614:*/
#line 14331 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:614*/
#line 14458 "./typica.w"

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

/*:620*//*621:*/
#line 14476 "./typica.w"

bool DeviceTreeModel::removeRows(int row,int count,const QModelIndex&parent)
{
/*614:*/
#line 14331 "./typica.w"

DeviceTreeModelNode*parentItem;
if(!parent.isValid())
{
parentItem= root;
}
else
{
parentItem= static_cast<DeviceTreeModelNode*> (parent.internalPointer());
}

/*:614*/
#line 14479 "./typica.w"

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

/*:621*//*622:*/
#line 14518 "./typica.w"

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

/*:622*//*623:*/
#line 14539 "./typica.w"

QVariant DeviceTreeModel::headerData(int,Qt::Orientation,int)const
{
return QVariant();
}

/*:623*//*624:*/
#line 14548 "./typica.w"

DeviceTreeModel::~DeviceTreeModel()
{
delete root;
}

/*:624*/
#line 814 "./typica.w"

/*650:*/
#line 15018 "./typica.w"

BasicDeviceConfigurationWidget::BasicDeviceConfigurationWidget(
DeviceTreeModel*model,const QModelIndex&index)
:QWidget(NULL),deviceModel(model),currentNode(index)
{

}

/*:650*//*651:*/
#line 15030 "./typica.w"

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

/*:651*//*652:*/
#line 15064 "./typica.w"

void BasicDeviceConfigurationWidget::insertChildNode(const QString&name,
const QString&driver)
{
deviceModel->newNode(name,driver,currentNode);
}

/*:652*/
#line 815 "./typica.w"

/*642:*/
#line 14886 "./typica.w"

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

/*:642*//*643:*/
#line 14932 "./typica.w"

void DeviceConfigurationWindow::addDevice()
{
model->newNode(tr("New Roaster"),"roaster",QModelIndex());
}

/*:643*//*644:*/
#line 14940 "./typica.w"

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

/*:644*//*645:*/
#line 14956 "./typica.w"

void DeviceConfigurationWindow::newSelection(const QModelIndex&index)
{
QWidget*editor= AppInstance->deviceConfigurationWidget(model,index);
if(editor)
{
configArea->setWidget(editor);
editor->show();
}
}

/*:645*/
#line 816 "./typica.w"

/*665:*/
#line 15360 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 15379 "./typica.w"

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

/*:665*//*666:*/
#line 15403 "./typica.w"

void Ni9211TcConfWidget::updateThermocoupleType(const QString&type)
{
updateAttribute("type",type);
}

void Ni9211TcConfWidget::updateColumnName(const QString&name)
{
updateAttribute("columnname",name);
}

/*:666*/
#line 817 "./typica.w"

/*661:*/
#line 15275 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 15289 "./typica.w"

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

/*:661*//*662:*/
#line 15311 "./typica.w"

void NiDaqMxBase9211ConfWidget::updateDeviceId(const QString&newId)
{
updateAttribute("deviceID",newId);
}

/*:662*//*663:*/
#line 15319 "./typica.w"

void NiDaqMxBase9211ConfWidget::addChannel()
{
insertChildNode(tr("Thermocouple channel"),"ni9211seriestc");
}

/*:663*/
#line 818 "./typica.w"

/*659:*/
#line 15226 "./typica.w"

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

/*:659*/
#line 819 "./typica.w"

/*548:*/
#line 12813 "./typica.w"

ReportAction::ReportAction(const QString&fileName,const QString&reportName,
QObject*parent):
QAction(reportName,parent),reportFile(fileName)
{
connect(this,SIGNAL(triggered()),this,SLOT(createReport()));
}

/*:548*//*549:*/
#line 12829 "./typica.w"

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
/*162:*/
#line 3897 "./typica.w"

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
/*163:*/
#line 3932 "./typica.w"

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
/*164:*/
#line 3979 "./typica.w"

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
/*546:*/
#line 12776 "./typica.w"

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
/*550:*/
#line 12853 "./typica.w"

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
/*551:*/
#line 12880 "./typica.w"

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

/*:551*/
#line 12870 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:550*/
#line 12789 "./typica.w"

}

/*:546*/
#line 3993 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*165:*/
#line 4006 "./typica.w"

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
/*:165*/
#line 3999 "./typica.w"

}
}

/*:164*/
#line 3957 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*157:*/
#line 3746 "./typica.w"

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

/*:157*/
#line 3965 "./typica.w"

context->setThisObject(oldThis);

/*:163*/
#line 3908 "./typica.w"

}
/*166:*/
#line 9 "./helpmenu.w"

HelpMenu*helpMenu= new HelpMenu();
window->menuBar()->addMenu(helpMenu);

/*:166*/
#line 3910 "./typica.w"

window->show();

/*:162*/
#line 12842 "./typica.w"

file.close();
engine->popContext();
}
}

/*:549*/
#line 820 "./typica.w"

/*198:*/
#line 5054 "./typica.w"

NumericDelegate::NumericDelegate(QObject*parent):
QItemDelegate(parent)
{

}

/*:198*//*199:*/
#line 5066 "./typica.w"

void NumericDelegate::setEditorData(QWidget*editor,
const QModelIndex&index)const
{
QString value= index.model()->data(index,Qt::EditRole).toString();
QLineEdit*line= static_cast<QLineEdit*> (editor);
line->setText(value);
}

/*:199*//*200:*/
#line 5081 "./typica.w"

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

/*:200*//*201:*/
#line 5104 "./typica.w"

QWidget*NumericDelegate::createEditor(QWidget*parent,
const QStyleOptionViewItem&,
const QModelIndex&)const
{
return(new QLineEdit(parent));
}

/*:201*//*202:*/
#line 5115 "./typica.w"

void NumericDelegate::updateEditorGeometry(QWidget*editor,
const QStyleOptionViewItem&option,
const QModelIndex&)const
{
editor->setGeometry(option.rect);
}

/*:202*/
#line 821 "./typica.w"

/*670:*/
#line 15457 "./typica.w"

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

/*:670*/
#line 822 "./typica.w"

/*672:*/
#line 15506 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 15520 "./typica.w"

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

/*:672*/
#line 823 "./typica.w"

/*674:*/
#line 15570 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 15590 "./typica.w"

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

/*:674*/
#line 824 "./typica.w"

/*692:*/
#line 15991 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16031 "./typica.w"

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

/*:692*/
#line 825 "./typica.w"

/*694:*/
#line 16154 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16234 "./typica.w"

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

/*:694*/
#line 826 "./typica.w"

/*696:*/
#line 16397 "./typica.w"

ModbusRtuDeviceTPvConfWidget::ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*model,
const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
ShortHexSpinBox*address= new ShortHexSpinBox;
layout->addRow(tr("Function 0x04 Process Value Address"),address);
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16405 "./typica.w"

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

/*:696*/
#line 827 "./typica.w"

/*698:*/
#line 16453 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16486 "./typica.w"

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

/*:698*/
#line 828 "./typica.w"

/*654:*/
#line 15100 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 15148 "./typica.w"

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

/*:654*//*656:*/
#line 15180 "./typica.w"

void RoasterConfWidget::updateRoasterId(int id)
{
updateAttribute("databaseid",QString("%1").arg(id));
}

/*:656*/
#line 829 "./typica.w"

/*702:*/
#line 16636 "./typica.w"

AnnotationButtonConfWidget::AnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*buttonTextEdit= new QLineEdit;
QLineEdit*annotationTextEdit= new QLineEdit;
layout->addRow(tr("Button Text:"),buttonTextEdit);
layout->addRow(tr("Annotation Text:"),annotationTextEdit);
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16645 "./typica.w"

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

/*:702*//*703:*/
#line 16667 "./typica.w"

void AnnotationButtonConfWidget::updateButtonText(const QString&text)
{
updateAttribute("buttontext",text);
}

void AnnotationButtonConfWidget::updateAnnotationText(const QString&text)
{
updateAttribute("annotationtext",text);
}

/*:703*//*706:*/
#line 16705 "./typica.w"

ReconfigurableAnnotationButtonConfWidget::ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*model,const QModelIndex&index)
:BasicDeviceConfigurationWidget(model,index)
{
QFormLayout*layout= new QFormLayout;
QLineEdit*buttonTextEdit= new QLineEdit;
QLineEdit*annotationTextEdit= new QLineEdit;
layout->addRow(tr("Button Text:"),buttonTextEdit);
layout->addRow(tr("Annotation Text:"),annotationTextEdit);
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16714 "./typica.w"

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

/*:706*/
#line 830 "./typica.w"

/*709:*/
#line 16782 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 16801 "./typica.w"

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

/*:709*/
#line 831 "./typica.w"

/*269:*/
#line 6849 "./typica.w"

LinearCalibrator::LinearCalibrator(QObject*parent):
QObject(parent),Lo1(0),Lo2(0),Up1(1),Up2(1),sensitivitySetting(0.0),clamp(false)
{

}

/*:269*//*270:*/
#line 6863 "./typica.w"

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

/*:270*//*271:*/
#line 6889 "./typica.w"

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

/*:271*/
#line 832 "./typica.w"

/*276:*/
#line 7022 "./typica.w"

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

/*:276*/
#line 833 "./typica.w"

/*731:*/
#line 18083 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 18099 "./typica.w"

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
/*732:*/
#line 18138 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:732*/
#line 18113 "./typica.w"

int column= 0;
/*733:*/
#line 18150 "./typica.w"

for(int i= 0;i<itemList.size();i++)
{
knotmodel->setData(knotmodel->index(i,column),
QVariant(itemList.at(i).toDouble()),
Qt::DisplayRole);
}

/*:733*/
#line 18115 "./typica.w"


}
else if(node.attribute("name")=="destinationvalues")
{
/*732:*/
#line 18138 "./typica.w"

QString data= node.attribute("value");
if(data.length()> 3)
{
data.chop(2);
data= data.remove(0,2);
}
QStringList itemList= data.split(",");

/*:732*/
#line 18120 "./typica.w"

int column= 1;
/*733:*/
#line 18150 "./typica.w"

for(int i= 0;i<itemList.size();i++)
{
knotmodel->setData(knotmodel->index(i,column),
QVariant(itemList.at(i).toDouble()),
Qt::DisplayRole);
}

/*:733*/
#line 18122 "./typica.w"

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

/*:731*//*734:*/
#line 18161 "./typica.w"

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

/*:734*/
#line 834 "./typica.w"

/*737:*/
#line 18204 "./typica.w"

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
/*655:*/
#line 15170 "./typica.w"

QDomElement referenceElement= 
model->referenceElement(model->data(index,Qt::UserRole).toString());
QDomNodeList configData= referenceElement.elementsByTagName("attribute");
QDomElement node;

/*:655*/
#line 18218 "./typica.w"

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

/*:737*//*738:*/
#line 18247 "./typica.w"

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

/*:738*/
#line 835 "./typica.w"


/*:17*/
#line 763 "./typica.w"

/*21:*/
#line 895 "./typica.w"

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

/*:21*//*22:*/
#line 940 "./typica.w"

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

/*:22*//*26:*/
#line 1017 "./typica.w"

void setQObjectProperties(QScriptValue,QScriptEngine*)
{

}

/*:26*//*28:*/
#line 1031 "./typica.w"

void setQPaintDeviceProperties(QScriptValue,QScriptEngine*)
{

}

void setQLayoutItemProperties(QScriptValue,QScriptEngine*)
{

}

/*:28*//*31:*/
#line 1070 "./typica.w"

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

/*:31*//*32:*/
#line 1092 "./typica.w"

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

/*:32*//*34:*/
#line 1166 "./typica.w"

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
/*36:*/
#line 1240 "./typica.w"

QSettings settings;
restoreGeometry(settings.value(QString("geometries/%1").arg(objectName())).
toByteArray());

/*:36*/
#line 1205 "./typica.w"

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
/*35:*/
#line 1234 "./typica.w"

QSettings settings;
settings.setValue(QString("geometries/%1").arg(objectName()),saveGeometry());

/*:35*/
#line 1222 "./typica.w"

event->accept();
}

/*:34*//*39:*/
#line 1268 "./typica.w"

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

/*:39*//*40:*/
#line 1290 "./typica.w"

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

/*:40*//*41:*/
#line 1324 "./typica.w"

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

/*:41*//*43:*/
#line 1354 "./typica.w"

void setQMenuBarProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("addMenu",engine->newFunction(QMenuBar_addMenu));
}

/*:43*//*44:*/
#line 1369 "./typica.w"

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

/*:44*//*46:*/
#line 1399 "./typica.w"

void setQMenuProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
value.setProperty("addAction",engine->newFunction(QMenu_addAction));
value.setProperty("addSeparator",engine->newFunction(QMenu_addSeparator));
}

/*:46*//*47:*/
#line 1409 "./typica.w"

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

/*:47*//*50:*/
#line 1471 "./typica.w"

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

/*:50*//*53:*/
#line 1505 "./typica.w"

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

/*:53*//*56:*/
#line 1551 "./typica.w"

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

/*:56*//*57:*/
#line 1571 "./typica.w"

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

/*:57*//*58:*/
#line 1604 "./typica.w"

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

/*:58*//*60:*/
#line 1657 "./typica.w"

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

/*:60*//*63:*/
#line 1724 "./typica.w"

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

/*:63*//*64:*/
#line 1775 "./typica.w"

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

/*:64*//*67:*/
#line 1839 "./typica.w"

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

/*:67*//*70:*/
#line 1897 "./typica.w"

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

/*:70*//*71:*/
#line 1933 "./typica.w"

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

/*:71*//*72:*/
#line 1970 "./typica.w"

void setQFileDialogProperties(QScriptValue value,QScriptEngine*engine)
{
setQDialogProperties(value,engine);
}

void setQDialogProperties(QScriptValue value,QScriptEngine*engine)
{
setQWidgetProperties(value,engine);
}

/*:72*//*75:*/
#line 2005 "./typica.w"

QScriptValue constructQFile(QScriptContext*context,QScriptEngine*engine)
{
QScriptValue object= 
engine->newQObject(new QFile(argument<QString> (0,context)));
setQFileProperties(object,engine);
return object;
}

/*:75*//*76:*/
#line 2016 "./typica.w"

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

/*:76*//*77:*/
#line 2038 "./typica.w"

void setQIODeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("open",engine->newFunction(QIODevice_open));
value.setProperty("close",engine->newFunction(QIODevice_close));
value.setProperty("readToString",
engine->newFunction(QIODevice_readToString));
}

/*:77*//*78:*/
#line 2053 "./typica.w"

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

/*:78*//*79:*/
#line 2092 "./typica.w"

QScriptValue QIODevice_readToString(QScriptContext*context,QScriptEngine*)
{
QIODevice*self= getself<QIODevice*> (context);
self->reset();
return QScriptValue(QString(self->readAll()));
}

/*:79*//*82:*/
#line 2122 "./typica.w"

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

/*:82*//*85:*/
#line 2170 "./typica.w"

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

/*:85*//*86:*/
#line 2188 "./typica.w"

QScriptValue XQuery_bind(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
QIODevice*buffer= argument<QIODevice*> (1,context);
self->bindVariable(argument<QString> (0,context),buffer);
return QScriptValue();
}

/*:86*//*87:*/
#line 2199 "./typica.w"

QScriptValue XQuery_setQuery(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
self->setQuery(argument<QString> (0,context));
return QScriptValue();
}

/*:87*//*88:*/
#line 2209 "./typica.w"

QScriptValue XQuery_exec(QScriptContext*context,QScriptEngine*)
{
QXmlQuery*self= getself<QXmlQuery*> (context);
QString result;
self->evaluateTo(&result);
return QScriptValue(result);
}

/*:88*//*91:*/
#line 2264 "./typica.w"

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

/*:91*//*92:*/
#line 2311 "./typica.w"

QScriptValue XmlWriter_setDevice(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
QIODevice*device= argument<QIODevice*> (0,context);
self->setDevice(device);
return QScriptValue();
}

/*:92*//*93:*/
#line 2325 "./typica.w"

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

/*:93*//*94:*/
#line 2344 "./typica.w"

QScriptValue XmlWriter_writeDTD(QScriptContext*context,QScriptEngine*)
{
QXmlStreamWriter*self= getself<QXmlStreamWriter*> (context);
self->writeDTD(argument<QString> (0,context));
return QScriptValue();
}

/*:94*//*95:*/
#line 2355 "./typica.w"

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

/*:95*//*96:*/
#line 2391 "./typica.w"

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

/*:96*//*97:*/
#line 2412 "./typica.w"

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

/*:97*//*100:*/
#line 2471 "./typica.w"

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

/*:100*//*101:*/
#line 2501 "./typica.w"

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

/*:101*//*102:*/
#line 2521 "./typica.w"

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

/*:102*//*103:*/
#line 2542 "./typica.w"

QScriptValue XmlReader_readNext(QScriptContext*context,QScriptEngine*)
{
QXmlStreamReader*self= getself<QXmlStreamReader*> (context);
self->readNext();
return QScriptValue();
}

/*:103*//*104:*/
#line 2552 "./typica.w"

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

/*:104*//*107:*/
#line 2594 "./typica.w"

void setQSettingsProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("value",engine->newFunction(QSettings_value));
value.setProperty("setValue",engine->newFunction(QSettings_setValue));
}

/*:107*//*108:*/
#line 2606 "./typica.w"

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

/*:108*//*111:*/
#line 2675 "./typica.w"

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

/*:111*//*114:*/
#line 2733 "./typica.w"

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

/*:114*//*115:*/
#line 2781 "./typica.w"

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

/*:115*//*116:*/
#line 2810 "./typica.w"

QScriptValue QTime_valueOf(QScriptContext*context,QScriptEngine*)
{
QTime self= getself<QTime> (context);
int retval= (self.hour()*60*60*1000)+(self.minute()*60*1000)+
(self.second()*1000)+self.msec();
return QScriptValue(retval);
}

/*:116*//*117:*/
#line 2824 "./typica.w"

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

/*:117*//*118:*/
#line 2867 "./typica.w"

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

/*:118*//*119:*/
#line 2888 "./typica.w"

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

/*:119*//*120:*/
#line 2908 "./typica.w"

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

/*:120*//*121:*/
#line 2964 "./typica.w"

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

/*:121*//*122:*/
#line 3002 "./typica.w"

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

/*:122*//*123:*/
#line 3041 "./typica.w"

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

/*:123*//*124:*/
#line 3077 "./typica.w"

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

/*:124*//*125:*/
#line 3113 "./typica.w"

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

/*:125*//*126:*/
#line 3134 "./typica.w"

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

/*:126*//*128:*/
#line 3174 "./typica.w"

void setQAbstractScrollAreaProperties(QScriptValue value,QScriptEngine*engine)
{
setQFrameProperties(value,engine);
}

/*:128*//*130:*/
#line 3188 "./typica.w"

void setQAbstractItemViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
}

/*:130*//*132:*/
#line 3202 "./typica.w"

void setQGraphicsViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
}

void setQTableViewProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractItemViewProperties(value,engine);
}

/*:132*//*135:*/
#line 3235 "./typica.w"

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

/*:135*//*142:*/
#line 3347 "./typica.w"

QScriptValue constructQSqlQuery(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= 
engine->toScriptValue<void*> (new SqlQueryConnection());
setQSqlQueryProperties(object,engine);
return object;
}

/*:142*//*143:*/
#line 3359 "./typica.w"

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

/*:143*//*144:*/
#line 3377 "./typica.w"

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

/*:144*//*145:*/
#line 3421 "./typica.w"

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

/*:145*//*146:*/
#line 3473 "./typica.w"

QScriptValue QSqlQuery_invalidate(QScriptContext*context,QScriptEngine*)
{
SqlQueryConnection*query= getself<SqlQueryConnection*> (context);
delete query;
return QScriptValue::UndefinedValue;
}

/*:146*//*149:*/
#line 3514 "./typica.w"

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

/*:149*//*150:*/
#line 3533 "./typica.w"

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

/*:150*//*151:*/
#line 3559 "./typica.w"

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

/*:151*//*152:*/
#line 3579 "./typica.w"

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

/*:152*//*153:*/
#line 3605 "./typica.w"

QScriptValue setTabOrder(QScriptContext*context,QScriptEngine*)
{
QWidget::setTabOrder(argument<QWidget*> (0,context),
argument<QWidget*> (1,context));
return QScriptValue();
}

/*:153*//*160:*/
#line 3844 "./typica.w"

QScriptValue createWindow(QScriptContext*context,QScriptEngine*engine)
{
QString targetID= argument<QString> (0,context);
QDomNode element;
QScriptValue object;
/*161:*/
#line 3865 "./typica.w"

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

/*:161*/
#line 3850 "./typica.w"

if(!element.isNull())
{
/*162:*/
#line 3897 "./typica.w"

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
/*163:*/
#line 3932 "./typica.w"

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
/*164:*/
#line 3979 "./typica.w"

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
/*546:*/
#line 12776 "./typica.w"

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
/*550:*/
#line 12853 "./typica.w"

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
/*551:*/
#line 12880 "./typica.w"

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

/*:551*/
#line 12870 "./typica.w"

ReportAction*action= new ReportAction(path,hierarchy.last());
insertionPoint->addAction(action);
}
}
}

/*:550*/
#line 12789 "./typica.w"

}

/*:546*/
#line 3993 "./typica.w"

}
}
}
if(element.hasChildNodes())
{
/*165:*/
#line 4006 "./typica.w"

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
/*:165*/
#line 3999 "./typica.w"

}
}

/*:164*/
#line 3957 "./typica.w"

}
}
i++;
}
QScriptValue oldThis= context->thisObject();
context->setThisObject(object);
QScriptValue result= engine->evaluate(windowScript);
/*157:*/
#line 3746 "./typica.w"

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

/*:157*/
#line 3965 "./typica.w"

context->setThisObject(oldThis);

/*:163*/
#line 3908 "./typica.w"

}
/*166:*/
#line 9 "./helpmenu.w"

HelpMenu*helpMenu= new HelpMenu();
window->menuBar()->addMenu(helpMenu);

/*:166*/
#line 3910 "./typica.w"

window->show();

/*:162*/
#line 3853 "./typica.w"

}
return object;
}

/*:160*//*171:*/
#line 4048 "./typica.w"

void addLayoutToWidget(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
if(element.hasAttribute("type"))
{
/*172:*/
#line 4069 "./typica.w"

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

/*:172*/
#line 4054 "./typica.w"

QWidget*widget= widgetStack->top();
if(layout)
{
widget->setLayout(layout);
}
layoutStack->pop();
}
}

/*:171*//*173:*/
#line 4107 "./typica.w"

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

/*:173*//*174:*/
#line 4139 "./typica.w"

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
/*175:*/
#line 4195 "./typica.w"

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

/*:175*/
#line 4167 "./typica.w"

}
}
}
}

/*:174*//*176:*/
#line 4245 "./typica.w"

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

/*:176*//*177:*/
#line 4355 "./typica.w"

void addLayoutToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QLayout*targetLayout= layoutStack->pop();
QBoxLayout*boxLayout= qobject_cast<QBoxLayout*> (targetLayout);
if(element.hasAttribute("type"))
{
/*172:*/
#line 4069 "./typica.w"

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

/*:172*/
#line 4363 "./typica.w"

boxLayout->addLayout(layout);
layoutStack->pop();
}
layoutStack->push(targetLayout);
}

/*:177*//*178:*/
#line 4374 "./typica.w"

void addSplitterToLayout(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
QSplitter*splitter= new(QSplitter);
layout->addWidget(splitter);
/*179:*/
#line 4387 "./typica.w"

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

/*:179*/
#line 4381 "./typica.w"

}

/*:178*//*180:*/
#line 4413 "./typica.w"

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

/*:180*//*181:*/
#line 4463 "./typica.w"

void addSplitterToSplitter(QDomElement element,QStack<QWidget*> *widgetStack,
QStack<QLayout*> *layoutStack)
{
QSplitter*parent= qobject_cast<QSplitter*> (widgetStack->top());
QSplitter*splitter= new(QSplitter);
splitter->setParent(parent);
parent->addWidget(splitter);
/*179:*/
#line 4387 "./typica.w"

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

/*:179*/
#line 4471 "./typica.w"

}

/*:181*//*182:*/
#line 4480 "./typica.w"

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

/*:182*//*183:*/
#line 4511 "./typica.w"

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

/*:183*//*184:*/
#line 4549 "./typica.w"

void addDecorationToLayout(QDomElement element,QStack<QWidget*> *,
QStack<QLayout*> *layoutStack)
{
/*185:*/
#line 4570 "./typica.w"

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
/*186:*/
#line 4595 "./typica.w"

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

/*:186*/
#line 4584 "./typica.w"

WidgetDecorator*decoration= new WidgetDecorator(theWidget,labelText,
orientation);
if(element.hasAttribute("id"))
{
decoration->setObjectName(element.attribute("id"));
}

/*:185*/
#line 4553 "./typica.w"

QBoxLayout*layout= qobject_cast<QBoxLayout*> (layoutStack->top());
layout->addWidget(decoration);
}

void addDecorationToSplitter(QDomElement element,
QStack<QWidget*> *widgetStack,
QStack<QLayout*> *)
{
/*185:*/
#line 4570 "./typica.w"

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
/*186:*/
#line 4595 "./typica.w"

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

/*:186*/
#line 4584 "./typica.w"

WidgetDecorator*decoration= new WidgetDecorator(theWidget,labelText,
orientation);
if(element.hasAttribute("id"))
{
decoration->setObjectName(element.attribute("id"));
}

/*:185*/
#line 4562 "./typica.w"

QSplitter*splitter= qobject_cast<QSplitter*> (widgetStack->top());
splitter->addWidget(decoration);
}

/*:184*//*187:*/
#line 4634 "./typica.w"

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

/*:187*//*188:*/
#line 4677 "./typica.w"

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

/*:188*//*189:*/
#line 4729 "./typica.w"

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

/*:189*//*190:*/
#line 4785 "./typica.w"

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

/*:190*//*191:*/
#line 4833 "./typica.w"

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

/*:191*//*192:*/
#line 4850 "./typica.w"

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

/*:192*//*193:*/
#line 4929 "./typica.w"

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
/*194:*/
#line 4977 "./typica.w"

if(currentElement.attribute("delegate")=="sql")
{
/*195:*/
#line 4993 "./typica.w"

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

/*:195*/
#line 4980 "./typica.w"

}
else if(currentElement.attribute("delegate")=="numeric")
{
/*196:*/
#line 5026 "./typica.w"

NumericDelegate*delegate= new NumericDelegate;
view->setItemDelegateForColumn(currentColumn,delegate);

/*:196*/
#line 4984 "./typica.w"

}

/*:194*/
#line 4961 "./typica.w"

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

/*:193*//*203:*/
#line 5136 "./typica.w"

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

/*:203*//*204:*/
#line 5177 "./typica.w"

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

/*:204*//*205:*/
#line 5194 "./typica.w"

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

/*:205*//*206:*/
#line 5211 "./typica.w"

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

/*:206*//*207:*/
#line 5229 "./typica.w"

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

/*:207*//*208:*/
#line 5249 "./typica.w"

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

/*:208*//*212:*/
#line 5316 "./typica.w"

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
/*213:*/
#line 5334 "./typica.w"

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

/*:213*/
#line 5327 "./typica.w"

}
return value;
}

/*:212*//*215:*/
#line 5452 "./typica.w"

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

/*:215*//*216:*/
#line 5476 "./typica.w"

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

/*:216*//*217:*/
#line 5528 "./typica.w"

QScriptValue SaltTable_model(QScriptContext*context,QScriptEngine*engine)
{
QTableView*self= getself<QTableView*> (context);
QScriptValue value= engine->newQObject(self->model());
return value;
}

/*:217*//*218:*/
#line 5542 "./typica.w"

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

/*:218*//*219:*/
#line 5560 "./typica.w"

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

/*:219*//*220:*/
#line 5578 "./typica.w"

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

/*:220*//*222:*/
#line 5611 "./typica.w"

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

#line 1 "./abouttypica.w"
/*:222*//*254:*/
#line 6495 "./typica.w"

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

/*:254*//*255:*/
#line 6525 "./typica.w"

void setDAQProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("newChannel",engine->newFunction(DAQ_newChannel));
}

/*:255*//*256:*/
#line 6535 "./typica.w"

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

/*:256*//*263:*/
#line 6691 "./typica.w"

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

/*:263*//*267:*/
#line 6782 "./typica.w"

void setChannelProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:267*//*274:*/
#line 6968 "./typica.w"

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

/*:274*//*279:*/
#line 7105 "./typica.w"

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


/*:279*//*288:*/
#line 7289 "./typica.w"

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

/*:288*//*295:*/
#line 7430 "./typica.w"

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

/*:295*//*300:*/
#line 7539 "./typica.w"

QScriptValue constructThresholdDetector(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new ThresholdDetector(300));
return object;
}

void setThresholdDetectorProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
}

/*:300*//*305:*/
#line 7635 "./typica.w"

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

/*:305*//*310:*/
#line 7715 "./typica.w"

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

/*:310*//*325:*/
#line 8063 "./typica.w"

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

/*:325*//*348:*/
#line 8667 "./typica.w"

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

/*:348*//*349:*/
#line 8693 "./typica.w"

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

/*:349*//*350:*/
#line 8741 "./typica.w"

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

/*:350*//*385:*/
#line 9585 "./typica.w"

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

/*:385*//*393:*/
#line 9728 "./typica.w"

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

/*:393*//*414:*/
#line 10147 "./typica.w"

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


/*:414*//*441:*/
#line 10642 "./typica.w"

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

/*:441*//*454:*/
#line 10923 "./typica.w"

QScriptValue constructLogEditWindow(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new LogEditWindow);
return object;
}

/*:454*//*473:*/
#line 11397 "./typica.w"

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

/*:473*//*480:*/
#line 11565 "./typica.w"

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

/*:480*//*481:*/
#line 11586 "./typica.w"

QScriptValue WebView_load(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QString file= argument<QString> (0,context);
self->load(QUrl(file));
return QScriptValue();
}

/*:481*//*482:*/
#line 11599 "./typica.w"

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

/*:482*//*483:*/
#line 11615 "./typica.w"

QScriptValue WebView_setHtml(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QString content= argument<QString> (0,context);
self->setHtml(content);
return QScriptValue();
}

/*:483*//*484:*/
#line 11628 "./typica.w"

QScriptValue WebView_setContent(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
QIODevice*device= argument<QIODevice*> (0,context);
device->reset();
QByteArray content= device->readAll();
self->setContent(content,"application/xhtml+xml");
return QScriptValue();
}

/*:484*//*485:*/
#line 11642 "./typica.w"

QScriptValue WebView_saveXml(QScriptContext*context,QScriptEngine*)
{
QWebView*self= getself<QWebView*> (context);
return QScriptValue(self->page()->currentFrame()->documentElement().toOuterXml());
}

/*:485*//*486:*/
#line 11652 "./typica.w"

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

/*:486*//*544:*/
#line 12702 "./typica.w"

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

/*:544*//*545:*/
#line 12720 "./typica.w"

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

/*:545*//*553:*/
#line 12919 "./typica.w"

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
/*554:*/
#line 12942 "./typica.w"

QDomNodeList children= element.childNodes();
for(int i= 0;i<children.count();i++)
{
QDomNode current;
QDomElement currentElement;
current= children.at(i);
if(current.isElement())
{
currentElement= current.toElement();
/*555:*/
#line 12959 "./typica.w"

if(currentElement.tagName()=="style")
{
document->setDefaultStyleSheet(currentElement.text());
}

/*:555*//*556:*/
#line 12970 "./typica.w"

if(currentElement.tagName()=="html")
{
cursor.insertHtml(currentElement.text());
}

/*:556*//*557:*/
#line 12980 "./typica.w"

if(currentElement.tagName()=="text")
{
cursor.insertText(currentElement.text());
}

/*:557*//*558:*/
#line 12990 "./typica.w"

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

/*:558*/
#line 12952 "./typica.w"

}
}

/*:554*/
#line 12935 "./typica.w"

widget->setDocument(document);
}

/*:553*//*569:*/
#line 13202 "./typica.w"

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

/*:569*//*570:*/
#line 13220 "./typica.w"

void setQTextEditProperties(QScriptValue value,QScriptEngine*engine)
{
setQAbstractScrollAreaProperties(value,engine);
value.setProperty("print",engine->newFunction(QTextEdit_print));
}

/*:570*//*579:*/
#line 13398 "./typica.w"

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

/*:579*//*600:*/
#line 13985 "./typica.w"

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



/*:600*//*626:*/
#line 14575 "./typica.w"

QScriptValue constructDeviceTreeModel(QScriptContext*,QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new DeviceTreeModel);
setDeviceTreeModelProperties(object,engine);
return object;
}

/*:626*//*628:*/
#line 14598 "./typica.w"

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

/*:628*//*629:*/
#line 14625 "./typica.w"

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

/*:629*//*632:*/
#line 14709 "./typica.w"

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

/*:632*//*647:*/
#line 14977 "./typica.w"

QScriptValue constructDeviceConfigurationWindow(QScriptContext*,
QScriptEngine*engine)
{
QScriptValue object= engine->newQObject(new DeviceConfigurationWindow);
return object;
}

/*:647*//*723:*/
#line 17482 "./typica.w"

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

/*:723*//*724:*/
#line 17504 "./typica.w"

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

/*:724*//*725:*/
#line 17537 "./typica.w"

void setModbusRTUDeviceProperties(QScriptValue value,QScriptEngine*engine)
{
setQObjectProperties(value,engine);
value.setProperty("pVChannel",engine->newFunction(ModbusRTUDevice_pVChannel));
value.setProperty("sVChannel",engine->newFunction(ModbusRTUDevice_sVChannel));
}

/*:725*/
#line 764 "./typica.w"

/*524:*/
#line 12364 "./typica.w"

int main(int argc,char**argv)
{
int*c= &argc;
Application app(*c,argv);
/*525:*/
#line 12388 "./typica.w"

QStringList themeSearchPath= QIcon::themeSearchPaths();
themeSearchPath.append(":/resources/icons/tango");
QIcon::setThemeSearchPaths(themeSearchPath);
QIcon::setThemeName(":/resources/icons/tango");
app.setWindowIcon(QIcon(":/resources/icons/appicons/logo.svg"));

/*:525*/
#line 12369 "./typica.w"

QSettings settings;

/*657:*/
#line 15189 "./typica.w"

app.registerDeviceConfigurationWidget("roaster",RoasterConfWidget::staticMetaObject);

/*:657*//*667:*/
#line 15417 "./typica.w"

app.registerDeviceConfigurationWidget("nidaqmxbase",
NiDaqMxBaseDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxbase9211series",
NiDaqMxBase9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("ni9211seriestc",
Ni9211TcConfWidget::staticMetaObject);

/*:667*//*675:*/
#line 15634 "./typica.w"

app.registerDeviceConfigurationWidget("nidaqmx",NiDaqMxDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmx9211series",NiDaqMx9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxtc01",NiDaqMxTc01ConfWidget::staticMetaObject);

/*:675*//*699:*/
#line 16595 "./typica.w"

app.registerDeviceConfigurationWidget("modbusrtuport",ModbusRtuPortConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbusrtudevice",ModbusRtuDeviceConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturepv",ModbusRtuDeviceTPvConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturesv",ModbusRtuDeviceTSvConfWidget::staticMetaObject);

/*:699*//*704:*/
#line 16680 "./typica.w"

app.registerDeviceConfigurationWidget("annotationbutton",AnnotationButtonConfWidget::staticMetaObject);

/*:704*//*707:*/
#line 16750 "./typica.w"

app.registerDeviceConfigurationWidget("reconfigurablebutton",ReconfigurableAnnotationButtonConfWidget::staticMetaObject);

/*:707*//*710:*/
#line 16877 "./typica.w"

app.registerDeviceConfigurationWidget("annotationspinbox",NoteSpinConfWidget::staticMetaObject);

/*:710*//*728:*/
#line 18050 "./typica.w"

app.registerDeviceConfigurationWidget("modbusrtu",ModbusConfigurator::staticMetaObject);

/*:728*//*735:*/
#line 18180 "./typica.w"

app.registerDeviceConfigurationWidget("linearspline",LinearSplineInterpolationConfWidget::staticMetaObject);

/*:735*//*739:*/
#line 18269 "./typica.w"

app.registerDeviceConfigurationWidget("translation",TranslationConfWidget::staticMetaObject);

/*:739*/
#line 12372 "./typica.w"

/*526:*/
#line 12401 "./typica.w"

if(settings.value("database/exists","false").toString()=="true")
{
/*531:*/
#line 12521 "./typica.w"

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

/*:531*/
#line 12404 "./typica.w"

}
if(settings.value("database/exists","false").toString()=="false")
{
/*530:*/
#line 12512 "./typica.w"

SqlConnectionSetup dialog;
dialog.exec();

/*:530*/
#line 12408 "./typica.w"

}


/*:526*/
#line 12373 "./typica.w"

/*154:*/
#line 3639 "./typica.w"

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
/*155:*/
#line 3673 "./typica.w"

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

/*:155*/
#line 3667 "./typica.w"


/*:154*/
#line 12374 "./typica.w"

/*20:*/
#line 883 "./typica.w"

QScriptEngine*engine= new QScriptEngine;
QScriptValue constructor;
QScriptValue value;

/*:20*//*30:*/
#line 1059 "./typica.w"

constructor= engine->newFunction(constructQWidget);
value= engine->newQMetaObject(&QWidget::staticMetaObject,constructor);
engine->globalObject().setProperty("QWidget",value);

/*:30*//*38:*/
#line 1259 "./typica.w"

constructor= engine->newFunction(constructQMainWindow);
value= engine->newQMetaObject(&ScriptQMainWindow::staticMetaObject,
constructor);
engine->globalObject().setProperty("QMainWindow",value);

/*:38*//*49:*/
#line 1464 "./typica.w"

constructor= engine->newFunction(constructQFrame);
value= engine->newQMetaObject(&QFrame::staticMetaObject,constructor);
engine->globalObject().setProperty("QFrame",value);

/*:49*//*52:*/
#line 1497 "./typica.w"

constructor= engine->newFunction(constructQLabel);
value= engine->newQMetaObject(&QLabel::staticMetaObject,constructor);
engine->globalObject().setProperty("QLabel",value);

/*:52*//*55:*/
#line 1544 "./typica.w"

constructor= engine->newFunction(constructQSplitter);
value= engine->newQMetaObject(&QSplitter::staticMetaObject,constructor);
engine->globalObject().setProperty("QSplitter",value);

/*:55*//*62:*/
#line 1715 "./typica.w"

constructor= engine->newFunction(constructQBoxLayout);
value= engine->newQMetaObject(&QBoxLayout::staticMetaObject,constructor);
engine->globalObject().setProperty("QBoxLayout",value);

/*:62*//*66:*/
#line 1827 "./typica.w"

constructor= engine->newFunction(constructQAction);
value= engine->newQMetaObject(&QAction::staticMetaObject,constructor);
engine->globalObject().setProperty("QAction",value);

/*:66*//*69:*/
#line 1886 "./typica.w"

value= engine->newQMetaObject(&QFileDialog::staticMetaObject);
value.setProperty("getOpenFileName",
engine->newFunction(QFileDialog_getOpenFileName));
value.setProperty("getSaveFileName",
engine->newFunction(QFileDialog_getSaveFileName));
engine->globalObject().setProperty("QFileDialog",value);

/*:69*//*74:*/
#line 1998 "./typica.w"

constructor= engine->newFunction(constructQFile);
value= engine->newQMetaObject(&QFile::staticMetaObject,constructor);
engine->globalObject().setProperty("QFile",value);

/*:74*//*81:*/
#line 2115 "./typica.w"

constructor= engine->newFunction(constructQBuffer);
value= engine->newQMetaObject(&QBuffer::staticMetaObject,constructor);
engine->globalObject().setProperty("QBuffer",value);

/*:81*//*84:*/
#line 2163 "./typica.w"

constructor= engine->newFunction(constructXQuery);
engine->globalObject().setProperty("XQuery",constructor);

/*:84*//*90:*/
#line 2257 "./typica.w"

constructor= engine->newFunction(constructXmlWriter);
engine->globalObject().setProperty("XmlWriter",constructor);

/*:90*//*99:*/
#line 2463 "./typica.w"

constructor= engine->newFunction(constructXmlReader);
engine->globalObject().setProperty("XmlReader",constructor);

/*:99*//*106:*/
#line 2587 "./typica.w"

value= engine->newQObject(&settings);
setQSettingsProperties(value,engine);
engine->globalObject().setProperty("QSettings",value);

/*:106*//*110:*/
#line 2668 "./typica.w"

constructor= engine->newFunction(constructQLCDNumber);
value= engine->newQMetaObject(&QLCDNumber::staticMetaObject,constructor);
engine->globalObject().setProperty("QLCDNumber",value);

/*:110*//*113:*/
#line 2724 "./typica.w"

constructor= engine->newFunction(constructQTime);
engine->globalObject().setProperty("QTime",constructor);

/*:113*//*134:*/
#line 3228 "./typica.w"

constructor= engine->newFunction(constructQPushButton);
value= engine->newQMetaObject(&QPushButton::staticMetaObject,constructor);
engine->globalObject().setProperty("QPushButton",value);

/*:134*//*141:*/
#line 3339 "./typica.w"

constructor= engine->newFunction(constructQSqlQuery);
engine->globalObject().setProperty("QSqlQuery",constructor);

/*:141*//*148:*/
#line 3500 "./typica.w"

engine->globalObject().setProperty("baseName",engine->newFunction(baseName));
engine->globalObject().setProperty("dir",engine->newFunction(dir));
engine->globalObject().setProperty("sqlToArray",
engine->newFunction(sqlToArray));
engine->globalObject().setProperty("setFont",engine->newFunction(setFont));
engine->globalObject().setProperty("annotationFromRecord",
engine->newFunction(annotationFromRecord));
engine->globalObject().setProperty("setTabOrder",engine->newFunction(setTabOrder));

/*:148*//*159:*/
#line 3836 "./typica.w"

engine->globalObject().setProperty("createWindow",
engine->newFunction(createWindow));

/*:159*//*211:*/
#line 5308 "./typica.w"

engine->globalObject().setProperty("findChildObject",
engine->newFunction(findChildObject));

/*:211*//*253:*/
#line 6485 "./typica.w"

constructor= engine->newFunction(constructDAQ);
value= engine->newQMetaObject(&DAQ::staticMetaObject,constructor);
engine->globalObject().setProperty("DAQ",value);

/*:253*//*262:*/
#line 6683 "./typica.w"

constructor= engine->newFunction(constructFakeDAQ);
value= engine->newQMetaObject(&FakeDAQ::staticMetaObject,constructor);
engine->globalObject().setProperty("FakeDAQ",value);

/*:262*//*273:*/
#line 6960 "./typica.w"

constructor= engine->newFunction(constructLinearCalibrator);
value= engine->newQMetaObject(&LinearCalibrator::staticMetaObject,
constructor);
engine->globalObject().setProperty("LinearCalibrator",value);

/*:273*//*278:*/
#line 7098 "./typica.w"

constructor= engine->newFunction(constructLinearSplineInterpolator);
value= engine->newQMetaObject(&LinearSplineInterpolator::staticMetaObject,constructor);
engine->globalObject().setProperty("LinearSplineInterpolator",value);

/*:278*//*287:*/
#line 7281 "./typica.w"

constructor= engine->newFunction(constructTemperatureDisplay);
value= engine->newQMetaObject(&TemperatureDisplay::staticMetaObject,
constructor);
engine->globalObject().setProperty("TemperatureDisplay",value);

/*:287*//*294:*/
#line 7419 "./typica.w"

constructor= engine->newFunction(constructMeasurementTimeOffset);
value= engine->newQMetaObject(&MeasurementTimeOffset::staticMetaObject,
constructor);
engine->globalObject().setProperty("MeasurementTimeOffset",value);

/*:294*//*299:*/
#line 7530 "./typica.w"

constructor= engine->newFunction(constructThresholdDetector);
value= engine->newQMetaObject(&ThresholdDetector::staticMetaObject,constructor);
engine->globalObject().setProperty("ThresholdDetector",value);

/*:299*//*304:*/
#line 7628 "./typica.w"

constructor= engine->newFunction(constructZeroEmitter);
value= engine->newQMetaObject(&ZeroEmitter::staticMetaObject,constructor);
engine->globalObject().setProperty("ZeroEmitter",value);

/*:304*//*309:*/
#line 7707 "./typica.w"

constructor= engine->newFunction(constructMeasurementAdapter);
value= engine->newQMetaObject(&MeasurementAdapter::staticMetaObject,
constructor);
engine->globalObject().setProperty("MeasurementAdapter",value);

/*:309*//*324:*/
#line 8056 "./typica.w"

constructor= engine->newFunction(constructGraphView);
value= engine->newQMetaObject(&GraphView::staticMetaObject,constructor);
engine->globalObject().setProperty("GraphView",value);

/*:324*//*347:*/
#line 8659 "./typica.w"

constructor= engine->newFunction(constructZoomLog);
value= engine->newQMetaObject(&ZoomLog::staticMetaObject,constructor);
engine->globalObject().setProperty("ZoomLog",value);

/*:347*//*384:*/
#line 9577 "./typica.w"

constructor= engine->newFunction(constructAnnotationButton);
value= engine->newQMetaObject(&AnnotationButton::staticMetaObject,
constructor);
engine->globalObject().setProperty("AnnotationButton",value);

/*:384*//*392:*/
#line 9719 "./typica.w"

constructor= engine->newFunction(constructAnnotationSpinBox);
value= engine->newQMetaObject(&AnnotationSpinBox::staticMetaObject,
constructor);
engine->globalObject().setProperty("AnnotationSpinBox",value);

/*:392*//*413:*/
#line 10140 "./typica.w"

constructor= engine->newFunction(constructTimerDisplay);
value= engine->newQMetaObject(&TimerDisplay::staticMetaObject,constructor);
engine->globalObject().setProperty("TimerDisplay",value);

/*:413*//*440:*/
#line 10634 "./typica.w"

constructor= engine->newFunction(constructWidgetDecorator);
value= engine->newQMetaObject(&WidgetDecorator::staticMetaObject,constructor);
engine->globalObject().setProperty("WidgetDecorator",value);

/*:440*//*453:*/
#line 10916 "./typica.w"

constructor= engine->newFunction(constructLogEditWindow);
value= engine->newQMetaObject(&LogEditWindow::staticMetaObject,constructor);
engine->globalObject().setProperty("LogEditWindow",value);

/*:453*//*472:*/
#line 11390 "./typica.w"

constructor= engine->newFunction(constructXMLInput);
value= engine->newQMetaObject(&XMLInput::staticMetaObject,constructor);
engine->globalObject().setProperty("XMLInput",value);

/*:472*//*479:*/
#line 11557 "./typica.w"

constructor= engine->newFunction(constructWebView);
value= engine->newQMetaObject(&QWebView::staticMetaObject,constructor);
engine->globalObject().setProperty("WebView",value);

/*:479*//*492:*/
#line 11749 "./typica.w"

value= engine->newQObject(AppInstance);
engine->globalObject().setProperty("Application",value);

/*:492*//*543:*/
#line 12694 "./typica.w"

constructor= engine->newFunction(constructSqlQueryView);
value= engine->newQMetaObject(&SqlQueryView::staticMetaObject,constructor);
engine->globalObject().setProperty("SqlQueryView",value);

/*:543*//*627:*/
#line 14585 "./typica.w"

constructor= engine->newFunction(constructDeviceTreeModel);
value= engine->newQMetaObject(&DeviceTreeModel::staticMetaObject,
constructor);
engine->globalObject().setProperty("DeviceTreeModel",value);

/*:627*//*633:*/
#line 14725 "./typica.w"

qScriptRegisterMetaType(engine,QModelIndex_toScriptValue,QModelIndex_fromScriptValue);

/*:633*//*648:*/
#line 14987 "./typica.w"

constructor= engine->newFunction(constructDeviceConfigurationWindow);
value= engine->newQMetaObject(&DeviceConfigurationWindow::staticMetaObject,
constructor);
engine->globalObject().setProperty("DeviceConfigurationWindow",value);

/*:648*//*722:*/
#line 17473 "./typica.w"

constructor= engine->newFunction(constructModbusRTUDevice);
value= engine->newQMetaObject(&ModbusRTUDevice::staticMetaObject,constructor);
engine->globalObject().setProperty("ModbusRTUDevice",value);

/*:722*/
#line 12375 "./typica.w"

app.engine= engine;
/*156:*/
#line 3721 "./typica.w"

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
/*157:*/
#line 3746 "./typica.w"

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

/*:157*/
#line 3741 "./typica.w"


/*:156*/
#line 12377 "./typica.w"


int retval= app.exec();
delete engine;
return retval;
}

/*:524*/
#line 765 "./typica.w"

#include "moc_typica.cpp"

/*:16*/
