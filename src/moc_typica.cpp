/****************************************************************************
** Meta object code from reading C++ file 'typica.cpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'typica.cpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptQMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       1,   59, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      34,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   18,   18,   18, 0x0a,
      59,   55,   18,   18, 0x0a,
      88,   55,   18,   18, 0x0a,
     128,  120,   18,   18, 0x0a,
     151,   18,   18,   18, 0x2a,
     174,  167,   18,   18, 0x0a,
     198,   18,   18,   18, 0x0a,

 // properties: name, type, flags
     222,  214, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_ScriptQMainWindow[] = {
    "ScriptQMainWindow\0\0aboutToClose()\0"
    "windowReady()\0show()\0key\0"
    "saveSizeAndPosition(QString)\0"
    "restoreSizeAndPosition(QString)\0message\0"
    "displayStatus(QString)\0displayStatus()\0"
    "prompt\0setClosePrompt(QString)\0"
    "setupFinished()\0QString\0closePrompt\0"
};

void ScriptQMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScriptQMainWindow *_t = static_cast<ScriptQMainWindow *>(_o);
        switch (_id) {
        case 0: _t->aboutToClose(); break;
        case 1: _t->windowReady(); break;
        case 2: _t->show(); break;
        case 3: _t->saveSizeAndPosition((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->restoreSizeAndPosition((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->displayStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->displayStatus(); break;
        case 7: _t->setClosePrompt((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setupFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScriptQMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScriptQMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ScriptQMainWindow,
      qt_meta_data_ScriptQMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptQMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptQMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptQMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptQMainWindow))
        return static_cast<void*>(const_cast< ScriptQMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ScriptQMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = closePrompt(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setClosePrompt(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ScriptQMainWindow::aboutToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ScriptQMainWindow::windowReady()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_NumericDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_NumericDelegate[] = {
    "NumericDelegate\0"
};

void NumericDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NumericDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NumericDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_NumericDelegate,
      qt_meta_data_NumericDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NumericDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NumericDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NumericDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NumericDelegate))
        return static_cast<void*>(const_cast< NumericDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int NumericDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ScriptValidator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ScriptValidator[] = {
    "ScriptValidator\0"
};

void ScriptValidator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ScriptValidator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScriptValidator::staticMetaObject = {
    { &QValidator::staticMetaObject, qt_meta_stringdata_ScriptValidator,
      qt_meta_data_ScriptValidator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptValidator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptValidator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptValidator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptValidator))
        return static_cast<void*>(const_cast< ScriptValidator*>(this));
    return QValidator::qt_metacast(_clname);
}

int ScriptValidator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QValidator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_DAQ[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       1,   34, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,

 // methods: signature, parameters, type, tag, flags
      25,   22,    4,    4, 0x02,
      46,    4,    4,    4, 0x02,
      54,    4,    4,    4, 0x02,

 // enums: name, flags, count, data
      61, 0x0,    8,   38,

 // enum data: key, value
      78, uint(DAQ::TypeJ),
      84, uint(DAQ::TypeK),
      90, uint(DAQ::TypeN),
      96, uint(DAQ::TypeR),
     102, uint(DAQ::TypeS),
     108, uint(DAQ::TypeT),
     114, uint(DAQ::TypeB),
     120, uint(DAQ::TypeE),

       0        // eod
};

static const char qt_meta_stringdata_DAQ[] = {
    "DAQ\0\0threadFinished()\0Hz\0setClockRate(double)\0"
    "start()\0stop()\0ThermocoupleType\0TypeJ\0"
    "TypeK\0TypeN\0TypeR\0TypeS\0TypeT\0TypeB\0"
    "TypeE\0"
};

void DAQ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DAQ *_t = static_cast<DAQ *>(_o);
        switch (_id) {
        case 0: _t->threadFinished(); break;
        case 1: _t->setClockRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        case 3: _t->stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DAQ::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DAQ::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DAQ,
      qt_meta_data_DAQ, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DAQ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DAQ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DAQ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DAQ))
        return static_cast<void*>(const_cast< DAQ*>(this));
    return QObject::qt_metacast(_clname);
}

int DAQ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_DAQImplementation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DAQImplementation[] = {
    "DAQImplementation\0"
};

void DAQImplementation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DAQImplementation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DAQImplementation::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DAQImplementation,
      qt_meta_data_DAQImplementation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DAQImplementation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DAQImplementation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DAQImplementation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DAQImplementation))
        return static_cast<void*>(const_cast< DAQImplementation*>(this));
    return QThread::qt_metacast(_clname);
}

int DAQImplementation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FakeDAQImplementation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_FakeDAQImplementation[] = {
    "FakeDAQImplementation\0"
};

void FakeDAQImplementation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FakeDAQImplementation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FakeDAQImplementation::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FakeDAQImplementation,
      qt_meta_data_FakeDAQImplementation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FakeDAQImplementation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FakeDAQImplementation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FakeDAQImplementation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FakeDAQImplementation))
        return static_cast<void*>(const_cast< FakeDAQImplementation*>(this));
    return QThread::qt_metacast(_clname);
}

int FakeDAQImplementation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FakeDAQ[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      12,    9,    8,    8, 0x02,
      33,    8,    8,    8, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_FakeDAQ[] = {
    "FakeDAQ\0\0Hz\0setClockRate(double)\0"
    "start()\0"
};

void FakeDAQ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FakeDAQ *_t = static_cast<FakeDAQ *>(_o);
        switch (_id) {
        case 0: _t->setClockRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->start(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FakeDAQ::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FakeDAQ::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FakeDAQ,
      qt_meta_data_FakeDAQ, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FakeDAQ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FakeDAQ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FakeDAQ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FakeDAQ))
        return static_cast<void*>(const_cast< FakeDAQ*>(this));
    return QObject::qt_metacast(_clname);
}

int FakeDAQ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_Channel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   30,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Channel[] = {
    "Channel\0\0newData(Measurement)\0measurement\0"
    "input(Measurement)\0"
};

void Channel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Channel *_t = static_cast<Channel *>(_o);
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: _t->input((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Channel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Channel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Channel,
      qt_meta_data_Channel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Channel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Channel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Channel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Channel))
        return static_cast<void*>(const_cast< Channel*>(this));
    return QObject::qt_metacast(_clname);
}

int Channel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Channel::newData(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_LinearCalibrator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       6,   59, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   18,   17,   17, 0x05,
      51,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   72,   17,   17, 0x0a,
     109,  103,   17,   17, 0x0a,
     134,   72,   17,   17, 0x0a,
     157,  103,   17,   17, 0x0a,
     187,  180,   17,   17, 0x0a,
     220,  208,   17,   17, 0x0a,
     255,   18,  243,   17, 0x0a,

 // properties: name, type, flags
     290,  283, 0x06095103,
     304,  283, 0x06095103,
     318,  283, 0x06095103,
     330,  283, 0x06095103,
     347,  342, 0x01095103,
     208,  283, 0x06095103,

       0        // eod
};

static const char qt_meta_stringdata_LinearCalibrator[] = {
    "LinearCalibrator\0\0measure\0"
    "measurement(Measurement)\0newData(Measurement)\0"
    "lower\0setMeasuredLower(double)\0upper\0"
    "setMeasuredUpper(double)\0"
    "setMappedLower(double)\0setMappedUpper(double)\0"
    "closed\0setClosedRange(bool)\0sensitivity\0"
    "setSensitivity(double)\0Measurement\0"
    "newMeasurement(Measurement)\0double\0"
    "measuredLower\0measuredUpper\0mappedLower\0"
    "mappedUpper\0bool\0closedRange\0"
};

void LinearCalibrator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LinearCalibrator *_t = static_cast<LinearCalibrator *>(_o);
        switch (_id) {
        case 0: _t->measurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: _t->newData((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->setMeasuredLower((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setMeasuredUpper((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setMappedLower((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setMappedUpper((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setClosedRange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setSensitivity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: { Measurement _r = _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Measurement*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LinearCalibrator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LinearCalibrator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LinearCalibrator,
      qt_meta_data_LinearCalibrator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LinearCalibrator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LinearCalibrator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LinearCalibrator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LinearCalibrator))
        return static_cast<void*>(const_cast< LinearCalibrator*>(this));
    return QObject::qt_metacast(_clname);
}

int LinearCalibrator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = measuredLower(); break;
        case 1: *reinterpret_cast< double*>(_v) = measuredUpper(); break;
        case 2: *reinterpret_cast< double*>(_v) = mappedLower(); break;
        case 3: *reinterpret_cast< double*>(_v) = mappedUpper(); break;
        case 4: *reinterpret_cast< bool*>(_v) = isClosedRange(); break;
        case 5: *reinterpret_cast< double*>(_v) = sensitivity(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMeasuredLower(*reinterpret_cast< double*>(_v)); break;
        case 1: setMeasuredUpper(*reinterpret_cast< double*>(_v)); break;
        case 2: setMappedLower(*reinterpret_cast< double*>(_v)); break;
        case 3: setMappedUpper(*reinterpret_cast< double*>(_v)); break;
        case 4: setClosedRange(*reinterpret_cast< bool*>(_v)); break;
        case 5: setSensitivity(*reinterpret_cast< double*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void LinearCalibrator::measurement(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LinearCalibrator::newData(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_LinearSplineInterpolator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   26,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   26,   55,   25, 0x0a,

 // methods: signature, parameters, type, tag, flags
     114,   95,   25,   25, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_LinearSplineInterpolator[] = {
    "LinearSplineInterpolator\0\0measure\0"
    "newData(Measurement)\0Measurement\0"
    "newMeasurement(Measurement)\0"
    "source,destination\0add_pair(double,double)\0"
};

void LinearSplineInterpolator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LinearSplineInterpolator *_t = static_cast<LinearSplineInterpolator *>(_o);
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: { Measurement _r = _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Measurement*>(_a[0]) = _r; }  break;
        case 2: _t->add_pair((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LinearSplineInterpolator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LinearSplineInterpolator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LinearSplineInterpolator,
      qt_meta_data_LinearSplineInterpolator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LinearSplineInterpolator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LinearSplineInterpolator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LinearSplineInterpolator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LinearSplineInterpolator))
        return static_cast<void*>(const_cast< LinearSplineInterpolator*>(this));
    return QObject::qt_metacast(_clname);
}

int LinearSplineInterpolator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void LinearSplineInterpolator::newData(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_TemperatureDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x0a,
      54,   19,   19,   19, 0x0a,
      73,   67,   19,   19, 0x0a,
     111,  102,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TemperatureDisplay[] = {
    "TemperatureDisplay\0\0temperature\0"
    "setValue(Measurement)\0invalidate()\0"
    "scale\0setDisplayUnits(Units::Unit)\0"
    "relative\0setRelativeMode(bool)\0"
};

void TemperatureDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TemperatureDisplay *_t = static_cast<TemperatureDisplay *>(_o);
        switch (_id) {
        case 0: _t->setValue((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: _t->invalidate(); break;
        case 2: _t->setDisplayUnits((*reinterpret_cast< Units::Unit(*)>(_a[1]))); break;
        case 3: _t->setRelativeMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TemperatureDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TemperatureDisplay::staticMetaObject = {
    { &QLCDNumber::staticMetaObject, qt_meta_stringdata_TemperatureDisplay,
      qt_meta_data_TemperatureDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TemperatureDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TemperatureDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TemperatureDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TemperatureDisplay))
        return static_cast<void*>(const_cast< TemperatureDisplay*>(this));
    return QLCDNumber::qt_metacast(_clname);
}

int TemperatureDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_MeasurementTimeOffset[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   23,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      56,   23,   22,   22, 0x0a,
      89,   84,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MeasurementTimeOffset[] = {
    "MeasurementTimeOffset\0\0measure\0"
    "measurement(Measurement)\0"
    "newMeasurement(Measurement)\0zero\0"
    "setZeroTime(QTime)\0"
};

void MeasurementTimeOffset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MeasurementTimeOffset *_t = static_cast<MeasurementTimeOffset *>(_o);
        switch (_id) {
        case 0: _t->measurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->setZeroTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MeasurementTimeOffset::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MeasurementTimeOffset::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MeasurementTimeOffset,
      qt_meta_data_MeasurementTimeOffset, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MeasurementTimeOffset::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MeasurementTimeOffset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MeasurementTimeOffset::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeasurementTimeOffset))
        return static_cast<void*>(const_cast< MeasurementTimeOffset*>(this));
    return QObject::qt_metacast(_clname);
}

int MeasurementTimeOffset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MeasurementTimeOffset::measurement(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ThresholdDetector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       1,   34, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   40,   18,   18, 0x0a,
      82,   76,   18,   18, 0x0a,
     113,  103,   18,   18, 0x0a,

 // enums: name, flags, count, data
     145, 0x0,    2,   38,

 // enum data: key, value
     159, uint(ThresholdDetector::Ascending),
     169, uint(ThresholdDetector::Descending),

       0        // eod
};

static const char qt_meta_stringdata_ThresholdDetector[] = {
    "ThresholdDetector\0\0timeForValue(double)\0"
    "measure\0newMeasurement(Measurement)\0"
    "value\0setThreshold(double)\0direction\0"
    "setEdgeDirection(EdgeDirection)\0"
    "EdgeDirection\0Ascending\0Descending\0"
};

void ThresholdDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ThresholdDetector *_t = static_cast<ThresholdDetector *>(_o);
        switch (_id) {
        case 0: _t->timeForValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->setThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setEdgeDirection((*reinterpret_cast< EdgeDirection(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ThresholdDetector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ThresholdDetector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ThresholdDetector,
      qt_meta_data_ThresholdDetector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ThresholdDetector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ThresholdDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ThresholdDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThresholdDetector))
        return static_cast<void*>(const_cast< ThresholdDetector*>(this));
    return QObject::qt_metacast(_clname);
}

int ThresholdDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ThresholdDetector::timeForValue(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ZeroEmitter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   61,   12,   12, 0x0a,
     104,   97,   12,   12, 0x0a,
     119,   12,   12,   12, 0x0a,

 // properties: name, type, flags
      97,  130, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_ZeroEmitter[] = {
    "ZeroEmitter\0\0measure,tempcolumn\0"
    "measurement(Measurement,int)\0measure\0"
    "newMeasurement(Measurement)\0column\0"
    "setColumn(int)\0emitZero()\0int\0"
};

void ZeroEmitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ZeroEmitter *_t = static_cast<ZeroEmitter *>(_o);
        switch (_id) {
        case 0: _t->measurement((*reinterpret_cast< Measurement(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->setColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->emitZero(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ZeroEmitter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ZeroEmitter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ZeroEmitter,
      qt_meta_data_ZeroEmitter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ZeroEmitter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ZeroEmitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ZeroEmitter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZeroEmitter))
        return static_cast<void*>(const_cast< ZeroEmitter*>(this));
    return QObject::qt_metacast(_clname);
}

int ZeroEmitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = column(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setColumn(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ZeroEmitter::measurement(Measurement _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_MeasurementAdapter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   68,   19,   19, 0x0a,
     111,  104,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MeasurementAdapter[] = {
    "MeasurementAdapter\0\0measure,tempcolumn\0"
    "measurement(Measurement,int)\0measure\0"
    "newMeasurement(Measurement)\0column\0"
    "setColumn(int)\0"
};

void MeasurementAdapter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MeasurementAdapter *_t = static_cast<MeasurementAdapter *>(_o);
        switch (_id) {
        case 0: _t->measurement((*reinterpret_cast< Measurement(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->setColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MeasurementAdapter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MeasurementAdapter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MeasurementAdapter,
      qt_meta_data_MeasurementAdapter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MeasurementAdapter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MeasurementAdapter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MeasurementAdapter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeasurementAdapter))
        return static_cast<void*>(const_cast< MeasurementAdapter*>(this));
    return QObject::qt_metacast(_clname);
}

int MeasurementAdapter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MeasurementAdapter::measurement(Measurement _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_GraphView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   11,   10,   10, 0x0a,
      76,   62,   10,   10, 0x0a,
     117,  109,   10,   10, 0x0a,
     147,   10,   10,   10, 0x0a,
     155,   10,   10,   10, 0x0a,
     163,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphView[] = {
    "GraphView\0\0measure,tempcolumn\0"
    "newMeasurement(Measurement,int)\0"
    "column,offset\0setSeriesTranslation(int,double)\0"
    "enabled\0setTimeIndicatorEnabled(bool)\0"
    "clear()\0showF()\0showC()\0"
};

void GraphView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GraphView *_t = static_cast<GraphView *>(_o);
        switch (_id) {
        case 0: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setSeriesTranslation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->setTimeIndicatorEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->clear(); break;
        case 4: _t->showF(); break;
        case 5: _t->showC(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GraphView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GraphView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphView,
      qt_meta_data_GraphView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphView))
        return static_cast<void*>(const_cast< GraphView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_ZoomLog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x08,
      50,   27,    8,    8, 0x08,
      83,    8,    8,    8, 0x08,
     116,  105,    8,    8, 0x0a,
     146,  133,    8,    8, 0x0a,
     173,    8,    8,    8, 0x0a,
     182,    8,    8,    8, 0x0a,
     191,    8,    8,    8, 0x0a,
     200,    8,    8,    8, 0x0a,
     210,    8,    8,    8, 0x0a,
     220,    8,    8,    8, 0x0a,
     230,    8,    8,    8, 0x0a,
     258,  239,    8,    8, 0x0a,
     329,  290,    8,    8, 0x0a,
     360,    8,    8,    8, 0x0a,
     375,  368,    8,    8, 0x0a,
     407,  368,    8,    8, 0x0a,
     435,  368,    8,    8, 0x0a,
     466,    8,    8,    8, 0x0a,
     493,  487,    8,    8, 0x0a,
     522,  368,    8,    8, 0x0a,
     549,    8,    8,    8, 0x0a,

 // methods: signature, parameters, type, tag, flags
     577,    8,  573,    8, 0x02,
     600,    8,  588,    8, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ZoomLog[] = {
    "ZoomLog\0\0row\0centerOn(int)\0"
    "column,oldsize,newsize\0"
    "persistColumnResize(int,int,int)\0"
    "restoreColumnWidths()\0visibility\0"
    "setVisible(bool)\0section,text\0"
    "setHeaderData(int,QString)\0LOD_ms()\0"
    "LOD_1s()\0LOD_5s()\0LOD_10s()\0LOD_15s()\0"
    "LOD_30s()\0LOD_1m()\0measure,tempcolumn\0"
    "newMeasurement(Measurement,int)\0"
    "annotation,tempcolumn,annotationcolumn\0"
    "newAnnotation(QString,int,int)\0clear()\0"
    "column\0addOutputTemperatureColumn(int)\0"
    "addOutputControlColumn(int)\0"
    "addOutputAnnotationColumn(int)\0"
    "clearOutputColumns()\0scale\0"
    "setDisplayUnits(Units::Unit)\0"
    "addToCurrentColumnSet(int)\0"
    "clearCurrentColumnSet()\0int\0rowCount()\0"
    "Units::Unit\0displayUnits()\0"
};

void ZoomLog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ZoomLog *_t = static_cast<ZoomLog *>(_o);
        switch (_id) {
        case 0: _t->centerOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->persistColumnResize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->restoreColumnWidths(); break;
        case 3: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setHeaderData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->LOD_ms(); break;
        case 6: _t->LOD_1s(); break;
        case 7: _t->LOD_5s(); break;
        case 8: _t->LOD_10s(); break;
        case 9: _t->LOD_15s(); break;
        case 10: _t->LOD_30s(); break;
        case 11: _t->LOD_1m(); break;
        case 12: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->newAnnotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 14: _t->clear(); break;
        case 15: _t->addOutputTemperatureColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->addOutputControlColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->addOutputAnnotationColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->clearOutputColumns(); break;
        case 19: _t->setDisplayUnits((*reinterpret_cast< Units::Unit(*)>(_a[1]))); break;
        case 20: _t->addToCurrentColumnSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->clearCurrentColumnSet(); break;
        case 22: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 23: { Units::Unit _r = _t->displayUnits();
            if (_a[0]) *reinterpret_cast< Units::Unit*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ZoomLog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ZoomLog::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_ZoomLog,
      qt_meta_data_ZoomLog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ZoomLog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ZoomLog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ZoomLog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZoomLog))
        return static_cast<void*>(const_cast< ZoomLog*>(this));
    return QTableView::qt_metacast(_clname);
}

int ZoomLog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
static const uint qt_meta_data_MeasurementModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   34,   17,   17, 0x0a,
     124,   85,   17,   17, 0x0a,
     155,   17,   17,   17, 0x0a,
     169,  163,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MeasurementModel[] = {
    "MeasurementModel\0\0rowChanged(int)\0"
    "measure,tempcolumn\0newMeasurement(Measurement,int)\0"
    "annotation,tempcolumn,annotationColumn\0"
    "newAnnotation(QString,int,int)\0clear()\0"
    "scale\0setDisplayUnits(Units::Unit)\0"
};

void MeasurementModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MeasurementModel *_t = static_cast<MeasurementModel *>(_o);
        switch (_id) {
        case 0: _t->rowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->newAnnotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->clear(); break;
        case 4: _t->setDisplayUnits((*reinterpret_cast< Units::Unit(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MeasurementModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MeasurementModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_MeasurementModel,
      qt_meta_data_MeasurementModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MeasurementModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MeasurementModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MeasurementModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeasurementModel))
        return static_cast<void*>(const_cast< MeasurementModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int MeasurementModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MeasurementModel::rowChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_AnnotationButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      51,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      90,   79,   17,   17, 0x0a,
     124,  113,   17,   17, 0x0a,
     167,  150,   17,   17, 0x0a,
     192,   17,   17,   17, 0x0a,
     203,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AnnotationButton[] = {
    "AnnotationButton\0\0annotation,tempcolumn,notecolumn\0"
    "annotation(QString,int,int)\0annotation\0"
    "setAnnotation(QString)\0tempcolumn\0"
    "setTemperatureColumn(int)\0annotationcolumn\0"
    "setAnnotationColumn(int)\0annotate()\0"
    "resetCount()\0"
};

void AnnotationButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnnotationButton *_t = static_cast<AnnotationButton *>(_o);
        switch (_id) {
        case 0: _t->annotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->setAnnotation((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setTemperatureColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setAnnotationColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->annotate(); break;
        case 5: _t->resetCount(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AnnotationButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnnotationButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_AnnotationButton,
      qt_meta_data_AnnotationButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnnotationButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnnotationButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnnotationButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnnotationButton))
        return static_cast<void*>(const_cast< AnnotationButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int AnnotationButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AnnotationButton::annotation(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_AnnotationSpinBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      52,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   80,   18,   18, 0x0a,
     111,  105,   18,   18, 0x0a,
     143,  132,   18,   18, 0x0a,
     186,  169,   18,   18, 0x0a,
     211,   18,   18,   18, 0x0a,
     222,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AnnotationSpinBox[] = {
    "AnnotationSpinBox\0\0annotation,tempcolumn,notecolumn\0"
    "annotation(QString,int,int)\0pret\0"
    "setPretext(QString)\0postt\0"
    "setPosttext(QString)\0tempcolumn\0"
    "setTemperatureColumn(int)\0annotationcolumn\0"
    "setAnnotationColumn(int)\0annotate()\0"
    "resetChange()\0"
};

void AnnotationSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnnotationSpinBox *_t = static_cast<AnnotationSpinBox *>(_o);
        switch (_id) {
        case 0: _t->annotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->setPretext((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setPosttext((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setTemperatureColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setAnnotationColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->annotate(); break;
        case 6: _t->resetChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AnnotationSpinBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnnotationSpinBox::staticMetaObject = {
    { &QDoubleSpinBox::staticMetaObject, qt_meta_stringdata_AnnotationSpinBox,
      qt_meta_data_AnnotationSpinBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnnotationSpinBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnnotationSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnnotationSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnnotationSpinBox))
        return static_cast<void*>(const_cast< AnnotationSpinBox*>(this));
    return QDoubleSpinBox::qt_metacast(_clname);
}

int AnnotationSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDoubleSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void AnnotationSpinBox::annotation(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_TimerDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       7,  104, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      34,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      56,   13,   13,   13, 0x08,
      69,   13,   13,   13, 0x08,
      86,   13,   13,   13, 0x08,
     105,   13,   13,   13, 0x08,
     126,  120,   13,   13, 0x0a,
     142,   13,   13,   13, 0x2a,
     158,  153,   13,   13, 0x0a,
     177,   13,   13,   13, 0x0a,
     190,   13,   13,   13, 0x0a,
     202,   13,   13,   13, 0x0a,
     214,  120,   13,   13, 0x0a,
     235,   13,   13,   13, 0x2a,
     251,   13,   13,   13, 0x0a,
     266,  259,   13,   13, 0x0a,
     298,  292,   13,   13, 0x0a,
     317,   13,   13,   13, 0x0a,

 // properties: name, type, flags
     339,  333, 0x0f095003,
     153,  347, 0x0009510b,
     362,  357, 0x01095001,
     370,  333, 0x0f095103,
     389,  381, 0x0a095103,
     403,  357, 0x01095103,
     120,  381, 0x0a095001,

       0        // eod
};

static const char qt_meta_stringdata_TimerDisplay[] = {
    "TimerDisplay\0\0valueChanged(QTime)\0"
    "runStateChanged(bool)\0updateTime()\0"
    "setCountUpMode()\0setCountDownMode()\0"
    "setClockMode()\0value\0setTimer(QTime)\0"
    "setTimer()\0mode\0setMode(TimerMode)\0"
    "startTimer()\0stopTimer()\0copyTimer()\0"
    "setResetValue(QTime)\0setResetValue()\0"
    "reset()\0format\0setDisplayFormat(QString)\0"
    "reset\0setAutoReset(bool)\0updateDisplay()\0"
    "QTime\0seconds\0TimerMode\0bool\0running\0"
    "resetValue\0QString\0displayFormat\0"
    "autoReset\0"
};

void TimerDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TimerDisplay *_t = static_cast<TimerDisplay *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 1: _t->runStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateTime(); break;
        case 3: _t->setCountUpMode(); break;
        case 4: _t->setCountDownMode(); break;
        case 5: _t->setClockMode(); break;
        case 6: _t->setTimer((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 7: _t->setTimer(); break;
        case 8: _t->setMode((*reinterpret_cast< TimerMode(*)>(_a[1]))); break;
        case 9: _t->startTimer(); break;
        case 10: _t->stopTimer(); break;
        case 11: _t->copyTimer(); break;
        case 12: _t->setResetValue((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 13: _t->setResetValue(); break;
        case 14: _t->reset(); break;
        case 15: _t->setDisplayFormat((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->setAutoReset((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->updateDisplay(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TimerDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TimerDisplay::staticMetaObject = {
    { &QLCDNumber::staticMetaObject, qt_meta_stringdata_TimerDisplay,
      qt_meta_data_TimerDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TimerDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TimerDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TimerDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TimerDisplay))
        return static_cast<void*>(const_cast< TimerDisplay*>(this));
    return QLCDNumber::qt_metacast(_clname);
}

int TimerDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QTime*>(_v) = seconds(); break;
        case 1: *reinterpret_cast< TimerMode*>(_v) = mode(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isRunning(); break;
        case 3: *reinterpret_cast< QTime*>(_v) = resetValue(); break;
        case 4: *reinterpret_cast< QString*>(_v) = displayFormat(); break;
        case 5: *reinterpret_cast< bool*>(_v) = autoReset(); break;
        case 6: *reinterpret_cast< QString*>(_v) = value(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTimer(*reinterpret_cast< QTime*>(_v)); break;
        case 1: setMode(*reinterpret_cast< TimerMode*>(_v)); break;
        case 3: setResetValue(*reinterpret_cast< QTime*>(_v)); break;
        case 4: setDisplayFormat(*reinterpret_cast< QString*>(_v)); break;
        case 5: setAutoReset(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TimerDisplay::valueChanged(QTime _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TimerDisplay::runStateChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_SceneButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   13,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SceneButton[] = {
    "SceneButton\0\0pos\0clicked(QPoint)\0"
};

void SceneButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SceneButton *_t = static_cast<SceneButton *>(_o);
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SceneButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SceneButton::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_SceneButton,
      qt_meta_data_SceneButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneButton))
        return static_cast<void*>(const_cast< SceneButton*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int SceneButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SceneButton::clicked(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_WidgetDecorator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_WidgetDecorator[] = {
    "WidgetDecorator\0"
};

void WidgetDecorator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WidgetDecorator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetDecorator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetDecorator,
      qt_meta_data_WidgetDecorator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetDecorator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetDecorator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetDecorator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetDecorator))
        return static_cast<void*>(const_cast< WidgetDecorator*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetDecorator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_LogEditWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      28,   14,   14,   14, 0x08,
      38,   14,   14,   14, 0x08,
      48,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LogEditWindow[] = {
    "LogEditWindow\0\0addTheRows()\0saveXML()\0"
    "saveCSV()\0openXML()\0"
};

void LogEditWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LogEditWindow *_t = static_cast<LogEditWindow *>(_o);
        switch (_id) {
        case 0: _t->addTheRows(); break;
        case 1: _t->saveXML(); break;
        case 2: _t->saveCSV(); break;
        case 3: _t->openXML(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LogEditWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LogEditWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LogEditWindow,
      qt_meta_data_LogEditWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LogEditWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LogEditWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LogEditWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogEditWindow))
        return static_cast<void*>(const_cast< LogEditWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LogEditWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_XMLOutput[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_XMLOutput[] = {
    "XMLOutput\0"
};

void XMLOutput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData XMLOutput::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XMLOutput::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XMLOutput,
      qt_meta_data_XMLOutput, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XMLOutput::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XMLOutput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XMLOutput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XMLOutput))
        return static_cast<void*>(const_cast< XMLOutput*>(this));
    return QObject::qt_metacast(_clname);
}

int XMLOutput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_XMLInput[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x05,
      40,   37,    9,    9, 0x05,
      68,   10,    9,    9, 0x05,
     102,   10,    9,    9, 0x05,
     135,    9,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_XMLInput[] = {
    "XMLInput\0\0,\0measure(Measurement,int)\0"
    ",,\0annotation(QString,int,int)\0"
    "newTemperatureColumn(int,QString)\0"
    "newAnnotationColumn(int,QString)\0"
    "lastColumn(int)\0"
};

void XMLInput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XMLInput *_t = static_cast<XMLInput *>(_o);
        switch (_id) {
        case 0: _t->measure((*reinterpret_cast< Measurement(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->annotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->newTemperatureColumn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->newAnnotationColumn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->lastColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XMLInput::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XMLInput::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XMLInput,
      qt_meta_data_XMLInput, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XMLInput::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XMLInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XMLInput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XMLInput))
        return static_cast<void*>(const_cast< XMLInput*>(this));
    return QObject::qt_metacast(_clname);
}

int XMLInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void XMLInput::measure(Measurement _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XMLInput::annotation(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XMLInput::newTemperatureColumn(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XMLInput::newAnnotationColumn(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XMLInput::lastColumn(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
static const uint qt_meta_data_Application[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   39,   12,   12, 0x0a,
      73,   13,   12,   12, 0x0a,
     103,   12,   12,   12, 0x0a,

 // methods: signature, parameters, type, tag, flags
     134,   12,  129,   12, 0x02,
     162,   12,  154,   12, 0x02,
     196,  182,  129,   12, 0x02,
     219,   12,  129,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Application[] = {
    "Application\0\0user\0userChanged(QString)\0"
    "status\0setDatabaseConnected(bool)\0"
    "setCurrentTypicaUser(QString)\0"
    "saveDeviceConfiguration()\0bool\0"
    "databaseConnected()\0QString\0"
    "currentTypicaUser()\0user,password\0"
    "login(QString,QString)\0autoLogin()\0"
};

void Application::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Application *_t = static_cast<Application *>(_o);
        switch (_id) {
        case 0: _t->userChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setDatabaseConnected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setCurrentTypicaUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->saveDeviceConfiguration(); break;
        case 4: { bool _r = _t->databaseConnected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->currentTypicaUser();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->login((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->autoLogin();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Application::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Application::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_Application,
      qt_meta_data_Application, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Application::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Application))
        return static_cast<void*>(const_cast< Application*>(this));
    return QApplication::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Application::userChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_SaltModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SaltModel[] = {
    "SaltModel\0"
};

void SaltModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SaltModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SaltModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_SaltModel,
      qt_meta_data_SaltModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SaltModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SaltModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SaltModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SaltModel))
        return static_cast<void*>(const_cast< SaltModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int SaltModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SqlComboBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      35,   29,   12,   12, 0x0a,
      65,   58,   12,   12, 0x0a,
      84,   58,   12,   12, 0x0a,
     111,  106,   12,   12, 0x0a,
     135,  126,   12,   12, 0x0a,
     165,  156,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SqlComboBox[] = {
    "SqlComboBox\0\0addNullOption()\0query\0"
    "addSqlOptions(QString)\0column\0"
    "setDataColumn(int)\0setDisplayColumn(int)\0"
    "show\0showData(bool)\0nullText\0"
    "setNullText(QString)\0nullData\0"
    "setNullData(QVariant)\0"
};

void SqlComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SqlComboBox *_t = static_cast<SqlComboBox *>(_o);
        switch (_id) {
        case 0: _t->addNullOption(); break;
        case 1: _t->addSqlOptions((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setDataColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setDisplayColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->showData((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setNullText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setNullData((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SqlComboBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SqlComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_SqlComboBox,
      qt_meta_data_SqlComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SqlComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SqlComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SqlComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlComboBox))
        return static_cast<void*>(const_cast< SqlComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int SqlComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_SqlComboBoxDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SqlComboBoxDelegate[] = {
    "SqlComboBoxDelegate\0"
};

void SqlComboBoxDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SqlComboBoxDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SqlComboBoxDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_SqlComboBoxDelegate,
      qt_meta_data_SqlComboBoxDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SqlComboBoxDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SqlComboBoxDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SqlComboBoxDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlComboBoxDelegate))
        return static_cast<void*>(const_cast< SqlComboBoxDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int SqlComboBoxDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SqlConnectionSetup[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SqlConnectionSetup[] = {
    "SqlConnectionSetup\0\0testConnection()\0"
};

void SqlConnectionSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SqlConnectionSetup *_t = static_cast<SqlConnectionSetup *>(_o);
        switch (_id) {
        case 0: _t->testConnection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SqlConnectionSetup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SqlConnectionSetup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SqlConnectionSetup,
      qt_meta_data_SqlConnectionSetup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SqlConnectionSetup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SqlConnectionSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SqlConnectionSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlConnectionSetup))
        return static_cast<void*>(const_cast< SqlConnectionSetup*>(this));
    return QDialog::qt_metacast(_clname);
}

int SqlConnectionSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_SqlQueryView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   14,   13,   13, 0x05,
      41,   37,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   59,   13,   13, 0x08,
     109,   86,   13,   13, 0x08,

 // methods: signature, parameters, type, tag, flags
     167,  151,  142,   13, 0x02,
     196,  185,  142,   13, 0x22,

       0        // eod
};

static const char qt_meta_stringdata_SqlQueryView[] = {
    "SqlQueryView\0\0key\0openEntry(QString)\0"
    "row\0openEntryRow(int)\0index\0"
    "openRow(QModelIndex)\0column,oldsize,newsize\0"
    "persistColumnResize(int,int,int)\0"
    "QVariant\0row,column,role\0data(int,int,int)\0"
    "row,column\0data(int,int)\0"
};

void SqlQueryView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SqlQueryView *_t = static_cast<SqlQueryView *>(_o);
        switch (_id) {
        case 0: _t->openEntry((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->openEntryRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->openRow((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->persistColumnResize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SqlQueryView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SqlQueryView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_SqlQueryView,
      qt_meta_data_SqlQueryView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SqlQueryView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SqlQueryView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SqlQueryView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlQueryView))
        return static_cast<void*>(const_cast< SqlQueryView*>(this));
    return QTableView::qt_metacast(_clname);
}

int SqlQueryView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SqlQueryView::openEntry(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SqlQueryView::openEntryRow(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ReportAction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ReportAction[] = {
    "ReportAction\0\0createReport()\0"
};

void ReportAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReportAction *_t = static_cast<ReportAction *>(_o);
        switch (_id) {
        case 0: _t->createReport(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ReportAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReportAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_ReportAction,
      qt_meta_data_ReportAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportAction))
        return static_cast<void*>(const_cast< ReportAction*>(this));
    return QAction::qt_metacast(_clname);
}

int ReportAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ReportTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

 // methods: signature, parameters, type, tag, flags
      41,   23,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ReportTable[] = {
    "ReportTable\0\0refresh()\0placeholder,value\0"
    "bind(QString,QVariant)\0"
};

void ReportTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReportTable *_t = static_cast<ReportTable *>(_o);
        switch (_id) {
        case 0: _t->refresh(); break;
        case 1: _t->bind((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReportTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReportTable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReportTable,
      qt_meta_data_ReportTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportTable))
        return static_cast<void*>(const_cast< ReportTable*>(this));
    return QObject::qt_metacast(_clname);
}

int ReportTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_PluginAction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       2,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x0a,
      40,   14,   13,   13, 0x0a,
      60,   13,   13,   13, 0x08,

 // properties: name, type, flags
      80,   72, 0x0a095103,
      87,   72, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_PluginAction[] = {
    "PluginAction\0\0script\0setPreRun(QString)\0"
    "setPostRun(QString)\0runScript()\0QString\0"
    "preRun\0postRun\0"
};

void PluginAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PluginAction *_t = static_cast<PluginAction *>(_o);
        switch (_id) {
        case 0: _t->setPreRun((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setPostRun((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->runScript(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PluginAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PluginAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_PluginAction,
      qt_meta_data_PluginAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PluginAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PluginAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PluginAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PluginAction))
        return static_cast<void*>(const_cast< PluginAction*>(this));
    return QAction::qt_metacast(_clname);
}

int PluginAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = preRun(); break;
        case 1: *reinterpret_cast< QString*>(_v) = postRun(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setPreRun(*reinterpret_cast< QString*>(_v)); break;
        case 1: setPostRun(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
static const uint qt_meta_data_FormArray[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   11,   10,   10, 0x0a,
      35,   10,   10,   10, 0x2a,
      49,   10,   10,   10, 0x0a,
      75,   69,   10,   10, 0x0a,
     110,  103,   10,   10, 0x0a,

 // methods: signature, parameters, type, tag, flags
     154,  148,  139,   10, 0x02,
     173,   10,  169,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_FormArray[] = {
    "FormArray\0\0copies\0addElements(int)\0"
    "addElements()\0removeAllElements()\0"
    "width\0setMaximumElementWidth(int)\0"
    "height\0setMaximumElementHeight(int)\0"
    "QWidget*\0index\0elementAt(int)\0int\0"
    "elements()\0"
};

void FormArray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormArray *_t = static_cast<FormArray *>(_o);
        switch (_id) {
        case 0: _t->addElements((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->addElements(); break;
        case 2: _t->removeAllElements(); break;
        case 3: _t->setMaximumElementWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setMaximumElementHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { QWidget* _r = _t->elementAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->elements();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormArray::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormArray::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_FormArray,
      qt_meta_data_FormArray, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormArray::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormArray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormArray::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormArray))
        return static_cast<void*>(const_cast< FormArray*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int FormArray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_ScaleControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      37,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   58,   13,   13, 0x0a,
      88,   58,   13,   13, 0x0a,

 // properties: name, type, flags
     117,  110, 0x06095103,
     130,  110, 0x06095103,

       0        // eod
};

static const char qt_meta_stringdata_ScaleControl[] = {
    "ScaleControl\0\0initialChanged(double)\0"
    "finalChanged(double)\0value\0"
    "setInitialValue(double)\0setFinalValue(double)\0"
    "double\0initialValue\0finalValue\0"
};

void ScaleControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScaleControl *_t = static_cast<ScaleControl *>(_o);
        switch (_id) {
        case 0: _t->initialChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->finalChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setInitialValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setFinalValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScaleControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScaleControl::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_ScaleControl,
      qt_meta_data_ScaleControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScaleControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScaleControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScaleControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScaleControl))
        return static_cast<void*>(const_cast< ScaleControl*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int ScaleControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = initialValue(); break;
        case 1: *reinterpret_cast< double*>(_v) = finalValue(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setInitialValue(*reinterpret_cast< double*>(_v)); break;
        case 1: setFinalValue(*reinterpret_cast< double*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ScaleControl::initialChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScaleControl::finalChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_IntensityControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   39,   17,   17, 0x0a,

 // properties: name, type, flags
      67,   60, 0x06095103,

       0        // eod
};

static const char qt_meta_stringdata_IntensityControl[] = {
    "IntensityControl\0\0valueChanged(double)\0"
    "val\0setValue(double)\0double\0value\0"
};

void IntensityControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IntensityControl *_t = static_cast<IntensityControl *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IntensityControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IntensityControl::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_IntensityControl,
      qt_meta_data_IntensityControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IntensityControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IntensityControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IntensityControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IntensityControl))
        return static_cast<void*>(const_cast< IntensityControl*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int IntensityControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = value(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setValue(*reinterpret_cast< double*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void IntensityControl::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_DeviceTreeModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   17,   16,   16, 0x0a,

 // methods: signature, parameters, type, tag, flags
      84,   77,   73,   16, 0x02,
     106,   16,   73,   16, 0x22,

       0        // eod
};

static const char qt_meta_stringdata_DeviceTreeModel[] = {
    "DeviceTreeModel\0\0name,driver,parent\0"
    "newNode(QString,QString,QModelIndex)\0"
    "int\0parent\0rowCount(QModelIndex)\0"
    "rowCount()\0"
};

void DeviceTreeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DeviceTreeModel *_t = static_cast<DeviceTreeModel *>(_o);
        switch (_id) {
        case 0: _t->newNode((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QModelIndex(*)>(_a[3]))); break;
        case 1: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DeviceTreeModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DeviceTreeModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_DeviceTreeModel,
      qt_meta_data_DeviceTreeModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeviceTreeModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeviceTreeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeviceTreeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceTreeModel))
        return static_cast<void*>(const_cast< DeviceTreeModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int DeviceTreeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_NodeInserter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NodeInserter[] = {
    "NodeInserter\0\0name,driver\0"
    "triggered(QString,QString)\0onTriggered()\0"
};

void NodeInserter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NodeInserter *_t = static_cast<NodeInserter *>(_o);
        switch (_id) {
        case 0: _t->triggered((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->onTriggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NodeInserter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NodeInserter::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_NodeInserter,
      qt_meta_data_NodeInserter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NodeInserter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NodeInserter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NodeInserter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NodeInserter))
        return static_cast<void*>(const_cast< NodeInserter*>(this));
    return QAction::qt_metacast(_clname);
}

int NodeInserter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NodeInserter::triggered(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_DeviceConfigurationWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,
      39,   26,   26,   26, 0x0a,
      58,   52,   26,   26, 0x0a,
      84,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DeviceConfigurationWindow[] = {
    "DeviceConfigurationWindow\0\0addDevice()\0"
    "removeNode()\0index\0newSelection(QModelIndex)\0"
    "resizeColumn()\0"
};

void DeviceConfigurationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DeviceConfigurationWindow *_t = static_cast<DeviceConfigurationWindow *>(_o);
        switch (_id) {
        case 0: _t->addDevice(); break;
        case 1: _t->removeNode(); break;
        case 2: _t->newSelection((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->resizeColumn(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DeviceConfigurationWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DeviceConfigurationWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DeviceConfigurationWindow,
      qt_meta_data_DeviceConfigurationWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeviceConfigurationWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeviceConfigurationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeviceConfigurationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceConfigurationWindow))
        return static_cast<void*>(const_cast< DeviceConfigurationWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int DeviceConfigurationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_BasicDeviceConfigurationWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      44,   32,   31,   31, 0x0a,
      88,   77,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BasicDeviceConfigurationWidget[] = {
    "BasicDeviceConfigurationWidget\0\0"
    "name,driver\0insertChildNode(QString,QString)\0"
    "name,value\0updateAttribute(QString,QString)\0"
};

void BasicDeviceConfigurationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BasicDeviceConfigurationWidget *_t = static_cast<BasicDeviceConfigurationWidget *>(_o);
        switch (_id) {
        case 0: _t->insertChildNode((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->updateAttribute((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BasicDeviceConfigurationWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BasicDeviceConfigurationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BasicDeviceConfigurationWidget,
      qt_meta_data_BasicDeviceConfigurationWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BasicDeviceConfigurationWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BasicDeviceConfigurationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BasicDeviceConfigurationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicDeviceConfigurationWidget))
        return static_cast<void*>(const_cast< BasicDeviceConfigurationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BasicDeviceConfigurationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_RoasterConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   34, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   19,   18,   18, 0x08,
      49,   43,   18,   18, 0x08,
      74,   43,   18,   18, 0x08,
      98,   43,   18,   18, 0x08,

 // constructors: signature, parameters, type, tag, flags
     138,  126,   18,   18, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_RoasterConfWidget[] = {
    "RoasterConfWidget\0\0id\0updateRoasterId(int)\0"
    "value\0updateCapacityCheck(int)\0"
    "updateCapacity(QString)\0"
    "updateCapacityUnit(QString)\0model,index\0"
    "RoasterConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void RoasterConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { RoasterConfWidget *_r = new RoasterConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RoasterConfWidget *_t = static_cast<RoasterConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateRoasterId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateCapacityCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateCapacity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateCapacityUnit((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RoasterConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RoasterConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_RoasterConfWidget,
      qt_meta_data_RoasterConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RoasterConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RoasterConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RoasterConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RoasterConfWidget))
        return static_cast<void*>(const_cast< RoasterConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int RoasterConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_NiDaqMxBaseDriverConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   14, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: signature, parameters, type, tag, flags
      41,   29,   28,   28, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_NiDaqMxBaseDriverConfWidget[] = {
    "NiDaqMxBaseDriverConfWidget\0\0model,index\0"
    "NiDaqMxBaseDriverConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void NiDaqMxBaseDriverConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { NiDaqMxBaseDriverConfWidget *_r = new NiDaqMxBaseDriverConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    }
    Q_UNUSED(_o);
}

const QMetaObjectExtraData NiDaqMxBaseDriverConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NiDaqMxBaseDriverConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_NiDaqMxBaseDriverConfWidget,
      qt_meta_data_NiDaqMxBaseDriverConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NiDaqMxBaseDriverConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NiDaqMxBaseDriverConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NiDaqMxBaseDriverConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NiDaqMxBaseDriverConfWidget))
        return static_cast<void*>(const_cast< NiDaqMxBaseDriverConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int NiDaqMxBaseDriverConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_NiDaqMxBase9211ConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x08,
      46,   40,   26,   26, 0x08,

 // constructors: signature, parameters, type, tag, flags
      83,   70,   26,   26, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_NiDaqMxBase9211ConfWidget[] = {
    "NiDaqMxBase9211ConfWidget\0\0addChannel()\0"
    "newId\0updateDeviceId(QString)\0"
    "device,index\0"
    "NiDaqMxBase9211ConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void NiDaqMxBase9211ConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { NiDaqMxBase9211ConfWidget *_r = new NiDaqMxBase9211ConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NiDaqMxBase9211ConfWidget *_t = static_cast<NiDaqMxBase9211ConfWidget *>(_o);
        switch (_id) {
        case 0: _t->addChannel(); break;
        case 1: _t->updateDeviceId((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NiDaqMxBase9211ConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NiDaqMxBase9211ConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_NiDaqMxBase9211ConfWidget,
      qt_meta_data_NiDaqMxBase9211ConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NiDaqMxBase9211ConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NiDaqMxBase9211ConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NiDaqMxBase9211ConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NiDaqMxBase9211ConfWidget))
        return static_cast<void*>(const_cast< NiDaqMxBase9211ConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int NiDaqMxBase9211ConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_Ni9211TcConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x08,
      62,   57,   19,   19, 0x08,
      95,   88,   19,   19, 0x08,

 // constructors: signature, parameters, type, tag, flags
     127,  114,   19,   19, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_Ni9211TcConfWidget[] = {
    "Ni9211TcConfWidget\0\0type\0"
    "updateThermocoupleType(QString)\0name\0"
    "updateColumnName(QString)\0hidden\0"
    "updateHidden(bool)\0device,index\0"
    "Ni9211TcConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void Ni9211TcConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Ni9211TcConfWidget *_r = new Ni9211TcConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Ni9211TcConfWidget *_t = static_cast<Ni9211TcConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateThermocoupleType((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Ni9211TcConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Ni9211TcConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_Ni9211TcConfWidget,
      qt_meta_data_Ni9211TcConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Ni9211TcConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Ni9211TcConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Ni9211TcConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ni9211TcConfWidget))
        return static_cast<void*>(const_cast< Ni9211TcConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int Ni9211TcConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_NiDaqMxDriverConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   14, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: signature, parameters, type, tag, flags
      37,   25,   24,   24, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_NiDaqMxDriverConfWidget[] = {
    "NiDaqMxDriverConfWidget\0\0model,index\0"
    "NiDaqMxDriverConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void NiDaqMxDriverConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { NiDaqMxDriverConfWidget *_r = new NiDaqMxDriverConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    }
    Q_UNUSED(_o);
}

const QMetaObjectExtraData NiDaqMxDriverConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NiDaqMxDriverConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_NiDaqMxDriverConfWidget,
      qt_meta_data_NiDaqMxDriverConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NiDaqMxDriverConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NiDaqMxDriverConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NiDaqMxDriverConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NiDaqMxDriverConfWidget))
        return static_cast<void*>(const_cast< NiDaqMxDriverConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int NiDaqMxDriverConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_NiDaqMx9211ConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      42,   36,   22,   22, 0x08,

 // constructors: signature, parameters, type, tag, flags
      78,   66,   22,   22, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_NiDaqMx9211ConfWidget[] = {
    "NiDaqMx9211ConfWidget\0\0addChannel()\0"
    "newId\0updateDeviceId(QString)\0model,index\0"
    "NiDaqMx9211ConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void NiDaqMx9211ConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { NiDaqMx9211ConfWidget *_r = new NiDaqMx9211ConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NiDaqMx9211ConfWidget *_t = static_cast<NiDaqMx9211ConfWidget *>(_o);
        switch (_id) {
        case 0: _t->addChannel(); break;
        case 1: _t->updateDeviceId((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NiDaqMx9211ConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NiDaqMx9211ConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_NiDaqMx9211ConfWidget,
      qt_meta_data_NiDaqMx9211ConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NiDaqMx9211ConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NiDaqMx9211ConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NiDaqMx9211ConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NiDaqMx9211ConfWidget))
        return static_cast<void*>(const_cast< NiDaqMx9211ConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int NiDaqMx9211ConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_NiDaqMxTc01ConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   34, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x08,
      58,   53,   22,   22, 0x08,
      95,   90,   22,   22, 0x08,
     128,  121,   22,   22, 0x08,

 // constructors: signature, parameters, type, tag, flags
     159,  147,   22,   22, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_NiDaqMxTc01ConfWidget[] = {
    "NiDaqMxTc01ConfWidget\0\0newId\0"
    "updateDeviceId(QString)\0type\0"
    "updateThermocoupleType(QString)\0name\0"
    "updateColumnName(QString)\0hidden\0"
    "updateHidden(bool)\0model,index\0"
    "NiDaqMxTc01ConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void NiDaqMxTc01ConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { NiDaqMxTc01ConfWidget *_r = new NiDaqMxTc01ConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NiDaqMxTc01ConfWidget *_t = static_cast<NiDaqMxTc01ConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateDeviceId((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateThermocoupleType((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NiDaqMxTc01ConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NiDaqMxTc01ConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_NiDaqMxTc01ConfWidget,
      qt_meta_data_NiDaqMxTc01ConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NiDaqMxTc01ConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NiDaqMxTc01ConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NiDaqMxTc01ConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NiDaqMxTc01ConfWidget))
        return static_cast<void*>(const_cast< NiDaqMxTc01ConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int NiDaqMxTc01ConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_PortSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PortSelector[] = {
    "PortSelector\0\0port\0addDevice(QextPortInfo)\0"
};

void PortSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PortSelector *_t = static_cast<PortSelector *>(_o);
        switch (_id) {
        case 0: _t->addDevice((*reinterpret_cast< QextPortInfo(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PortSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PortSelector::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_PortSelector,
      qt_meta_data_PortSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PortSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PortSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PortSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PortSelector))
        return static_cast<void*>(const_cast< PortSelector*>(this));
    return QComboBox::qt_metacast(_clname);
}

int PortSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_BaudSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      13, 0x0,   11,   18,

 // enum data: key, value
      26, uint(BaudSelector::BAUD110),
      34, uint(BaudSelector::BAUD300),
      42, uint(BaudSelector::BAUD600),
      50, uint(BaudSelector::BAUD1200),
      59, uint(BaudSelector::BAUD2400),
      68, uint(BaudSelector::BAUD4800),
      77, uint(BaudSelector::BAUD9600),
      86, uint(BaudSelector::BAUD19200),
      96, uint(BaudSelector::BAUD38400),
     106, uint(BaudSelector::BAUD57600),
     116, uint(BaudSelector::BAUD115200),

       0        // eod
};

static const char qt_meta_stringdata_BaudSelector[] = {
    "BaudSelector\0BaudRateType\0BAUD110\0"
    "BAUD300\0BAUD600\0BAUD1200\0BAUD2400\0"
    "BAUD4800\0BAUD9600\0BAUD19200\0BAUD38400\0"
    "BAUD57600\0BAUD115200\0"
};

void BaudSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BaudSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BaudSelector::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_BaudSelector,
      qt_meta_data_BaudSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BaudSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BaudSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BaudSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BaudSelector))
        return static_cast<void*>(const_cast< BaudSelector*>(this));
    return QComboBox::qt_metacast(_clname);
}

int BaudSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ParitySelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      15, 0x0,    4,   18,

 // enum data: key, value
      26, uint(ParitySelector::PAR_NONE),
      35, uint(ParitySelector::PAR_ODD),
      43, uint(ParitySelector::PAR_EVEN),
      52, uint(ParitySelector::PAR_SPACE),

       0        // eod
};

static const char qt_meta_stringdata_ParitySelector[] = {
    "ParitySelector\0ParityType\0PAR_NONE\0"
    "PAR_ODD\0PAR_EVEN\0PAR_SPACE\0"
};

void ParitySelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ParitySelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParitySelector::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_ParitySelector,
      qt_meta_data_ParitySelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParitySelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParitySelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParitySelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParitySelector))
        return static_cast<void*>(const_cast< ParitySelector*>(this));
    return QComboBox::qt_metacast(_clname);
}

int ParitySelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FlowSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      13, 0x0,    3,   18,

 // enum data: key, value
      22, uint(FlowSelector::FLOW_OFF),
      31, uint(FlowSelector::FLOW_HARDWARE),
      45, uint(FlowSelector::FLOW_XONXOFF),

       0        // eod
};

static const char qt_meta_stringdata_FlowSelector[] = {
    "FlowSelector\0FlowType\0FLOW_OFF\0"
    "FLOW_HARDWARE\0FLOW_XONXOFF\0"
};

void FlowSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FlowSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FlowSelector::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_FlowSelector,
      qt_meta_data_FlowSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FlowSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FlowSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FlowSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FlowSelector))
        return static_cast<void*>(const_cast< FlowSelector*>(this));
    return QComboBox::qt_metacast(_clname);
}

int FlowSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_StopSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      13, 0x0,    2,   18,

 // enum data: key, value
      26, uint(StopSelector::STOP_1),
      33, uint(StopSelector::STOP_2),

       0        // eod
};

static const char qt_meta_stringdata_StopSelector[] = {
    "StopSelector\0StopBitsType\0STOP_1\0"
    "STOP_2\0"
};

void StopSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData StopSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StopSelector::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_StopSelector,
      qt_meta_data_StopSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StopSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StopSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StopSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StopSelector))
        return static_cast<void*>(const_cast< StopSelector*>(this));
    return QComboBox::qt_metacast(_clname);
}

int StopSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ShortHexSpinBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ShortHexSpinBox[] = {
    "ShortHexSpinBox\0"
};

void ShortHexSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ShortHexSpinBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShortHexSpinBox::staticMetaObject = {
    { &QSpinBox::staticMetaObject, qt_meta_stringdata_ShortHexSpinBox,
      qt_meta_data_ShortHexSpinBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShortHexSpinBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShortHexSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShortHexSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShortHexSpinBox))
        return static_cast<void*>(const_cast< ShortHexSpinBox*>(this));
    return QSpinBox::qt_metacast(_clname);
}

int ShortHexSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ModbusRtuPortConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   39, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   25,   24,   24, 0x08,
      61,   53,   24,   24, 0x08,
      95,   85,   24,   24, 0x08,
     125,  117,   24,   24, 0x08,
     164,  152,   24,   24, 0x08,

 // constructors: signature, parameters, type, tag, flags
     200,  188,   24,   24, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusRtuPortConfWidget[] = {
    "ModbusRtuPortConfWidget\0\0newPort\0"
    "updatePort(QString)\0newRate\0"
    "updateBaudRate(QString)\0newParity\0"
    "updateParity(QString)\0newFlow\0"
    "updateFlowControl(QString)\0newStopBits\0"
    "updateStopBits(QString)\0model,index\0"
    "ModbusRtuPortConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusRtuPortConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusRtuPortConfWidget *_r = new ModbusRtuPortConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusRtuPortConfWidget *_t = static_cast<ModbusRtuPortConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updatePort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateBaudRate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateParity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateFlowControl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateStopBits((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusRtuPortConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusRtuPortConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusRtuPortConfWidget,
      qt_meta_data_ModbusRtuPortConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusRtuPortConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusRtuPortConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusRtuPortConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusRtuPortConfWidget))
        return static_cast<void*>(const_cast< ModbusRtuPortConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusRtuPortConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_ModbusRtuDeviceConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   59, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      38,   27,   26,   26, 0x08,
      72,   63,   26,   26, 0x08,
      94,   63,   26,   26, 0x08,
     127,  119,   26,   26, 0x08,
     158,  147,   26,   26, 0x08,
     190,  181,   26,   26, 0x08,
     208,  181,   26,   26, 0x08,
     226,  147,   26,   26, 0x08,
     254,  181,   26,   26, 0x08,

 // constructors: signature, parameters, type, tag, flags
     292,  280,   26,   26, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusRtuDeviceConfWidget[] = {
    "ModbusRtuDeviceConfWidget\0\0newStation\0"
    "updateStationNumber(int)\0newFixed\0"
    "updateFixedUnit(bool)\0updateFixedDecimal(bool)\0"
    "newUnit\0updateUnit(QString)\0newAddress\0"
    "updateUnitAddress(int)\0newValue\0"
    "updateValueF(int)\0updateValueC(int)\0"
    "updatePrecisionAddress(int)\0"
    "updatePrecisionValue(int)\0model,index\0"
    "ModbusRtuDeviceConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusRtuDeviceConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusRtuDeviceConfWidget *_r = new ModbusRtuDeviceConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusRtuDeviceConfWidget *_t = static_cast<ModbusRtuDeviceConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateStationNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateFixedUnit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateFixedDecimal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->updateUnit((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateUnitAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateValueF((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateValueC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->updatePrecisionAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->updatePrecisionValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusRtuDeviceConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusRtuDeviceConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusRtuDeviceConfWidget,
      qt_meta_data_ModbusRtuDeviceConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusRtuDeviceConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusRtuDeviceConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusRtuDeviceConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusRtuDeviceConfWidget))
        return static_cast<void*>(const_cast< ModbusRtuDeviceConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusRtuDeviceConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
static const uint qt_meta_data_ModbusRtuDeviceTPvConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   19, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   30,   29,   29, 0x08,

 // constructors: signature, parameters, type, tag, flags
      72,   60,   29,   29, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusRtuDeviceTPvConfWidget[] = {
    "ModbusRtuDeviceTPvConfWidget\0\0newAddress\0"
    "updateAddress(int)\0model,index\0"
    "ModbusRtuDeviceTPvConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusRtuDeviceTPvConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusRtuDeviceTPvConfWidget *_r = new ModbusRtuDeviceTPvConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusRtuDeviceTPvConfWidget *_t = static_cast<ModbusRtuDeviceTPvConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusRtuDeviceTPvConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusRtuDeviceTPvConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusRtuDeviceTPvConfWidget,
      qt_meta_data_ModbusRtuDeviceTPvConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusRtuDeviceTPvConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusRtuDeviceTPvConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusRtuDeviceTPvConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusRtuDeviceTPvConfWidget))
        return static_cast<void*>(const_cast< ModbusRtuDeviceTPvConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusRtuDeviceTPvConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ModbusRtuDeviceTSvConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   49, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   30,   29,   29, 0x08,
      64,   30,   29,   29, 0x08,
      94,   88,   29,   29, 0x08,
     123,  117,   29,   29, 0x08,
     150,  144,   29,   29, 0x08,
     171,   30,   29,   29, 0x08,
     195,   30,   29,   29, 0x08,

 // constructors: signature, parameters, type, tag, flags
     231,  219,   29,   29, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusRtuDeviceTSvConfWidget[] = {
    "ModbusRtuDeviceTSvConfWidget\0\0newAddress\0"
    "updateReadAddress(int)\0updateWriteAddress(int)\0"
    "fixed\0updateFixedRange(bool)\0lower\0"
    "updateLower(QString)\0upper\0"
    "updateUpper(QString)\0updateLowerAddress(int)\0"
    "updateUpperAddress(int)\0model,index\0"
    "ModbusRtuDeviceTSvConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusRtuDeviceTSvConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusRtuDeviceTSvConfWidget *_r = new ModbusRtuDeviceTSvConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusRtuDeviceTSvConfWidget *_t = static_cast<ModbusRtuDeviceTSvConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateReadAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateWriteAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateFixedRange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->updateLower((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateUpper((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateLowerAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateUpperAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusRtuDeviceTSvConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusRtuDeviceTSvConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusRtuDeviceTSvConfWidget,
      qt_meta_data_ModbusRtuDeviceTSvConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusRtuDeviceTSvConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusRtuDeviceTSvConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusRtuDeviceTSvConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusRtuDeviceTSvConfWidget))
        return static_cast<void*>(const_cast< ModbusRtuDeviceTSvConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusRtuDeviceTSvConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_AnnotationButtonConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   28,   27,   27, 0x08,
      59,   28,   27,   27, 0x08,

 // constructors: signature, parameters, type, tag, flags
     101,   89,   27,   27, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_AnnotationButtonConfWidget[] = {
    "AnnotationButtonConfWidget\0\0text\0"
    "updateButtonText(QString)\0"
    "updateAnnotationText(QString)\0model,index\0"
    "AnnotationButtonConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void AnnotationButtonConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { AnnotationButtonConfWidget *_r = new AnnotationButtonConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnnotationButtonConfWidget *_t = static_cast<AnnotationButtonConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateButtonText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateAnnotationText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AnnotationButtonConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnnotationButtonConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_AnnotationButtonConfWidget,
      qt_meta_data_AnnotationButtonConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnnotationButtonConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnnotationButtonConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnnotationButtonConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnnotationButtonConfWidget))
        return static_cast<void*>(const_cast< AnnotationButtonConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int AnnotationButtonConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_ReconfigurableAnnotationButtonConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      47,   42,   41,   41, 0x08,
      73,   42,   41,   41, 0x08,

 // constructors: signature, parameters, type, tag, flags
     115,  103,   41,   41, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ReconfigurableAnnotationButtonConfWidget[] = {
    "ReconfigurableAnnotationButtonConfWidget\0"
    "\0text\0updateButtonText(QString)\0"
    "updateAnnotationText(QString)\0model,index\0"
    "ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ReconfigurableAnnotationButtonConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ReconfigurableAnnotationButtonConfWidget *_r = new ReconfigurableAnnotationButtonConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReconfigurableAnnotationButtonConfWidget *_t = static_cast<ReconfigurableAnnotationButtonConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateButtonText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateAnnotationText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReconfigurableAnnotationButtonConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReconfigurableAnnotationButtonConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ReconfigurableAnnotationButtonConfWidget,
      qt_meta_data_ReconfigurableAnnotationButtonConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReconfigurableAnnotationButtonConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReconfigurableAnnotationButtonConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReconfigurableAnnotationButtonConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReconfigurableAnnotationButtonConfWidget))
        return static_cast<void*>(const_cast< ReconfigurableAnnotationButtonConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ReconfigurableAnnotationButtonConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_NoteSpinConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   44, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x08,
      54,   46,   19,   19, 0x08,
      85,   77,   19,   19, 0x08,
     118,  108,   19,   19, 0x08,
     139,   20,   19,   19, 0x08,
     162,   20,   19,   19, 0x08,

 // constructors: signature, parameters, type, tag, flags
     198,  186,   19,   19, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_NoteSpinConfWidget[] = {
    "NoteSpinConfWidget\0\0text\0updateLabel(QString)\0"
    "minimum\0updateMinimum(QString)\0maximum\0"
    "updateMaximum(QString)\0precision\0"
    "updatePrecision(int)\0updatePretext(QString)\0"
    "updatePosttext(QString)\0model,index\0"
    "NoteSpinConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void NoteSpinConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { NoteSpinConfWidget *_r = new NoteSpinConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NoteSpinConfWidget *_t = static_cast<NoteSpinConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateMinimum((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateMaximum((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updatePrecision((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updatePretext((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updatePosttext((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NoteSpinConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NoteSpinConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_NoteSpinConfWidget,
      qt_meta_data_NoteSpinConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NoteSpinConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NoteSpinConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NoteSpinConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NoteSpinConfWidget))
        return static_cast<void*>(const_cast< NoteSpinConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int NoteSpinConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_FreeAnnotationConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   19, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   26,   25,   25, 0x08,

 // constructors: signature, parameters, type, tag, flags
      64,   52,   25,   25, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_FreeAnnotationConfWidget[] = {
    "FreeAnnotationConfWidget\0\0text\0"
    "updateLabel(QString)\0model,index\0"
    "FreeAnnotationConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void FreeAnnotationConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { FreeAnnotationConfWidget *_r = new FreeAnnotationConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FreeAnnotationConfWidget *_t = static_cast<FreeAnnotationConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FreeAnnotationConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FreeAnnotationConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_FreeAnnotationConfWidget,
      qt_meta_data_FreeAnnotationConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FreeAnnotationConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FreeAnnotationConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FreeAnnotationConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FreeAnnotationConfWidget))
        return static_cast<void*>(const_cast< FreeAnnotationConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int FreeAnnotationConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_SettingsWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SettingsWindow[] = {
    "SettingsWindow\0"
};

void SettingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SettingsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SettingsWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SettingsWindow,
      qt_meta_data_SettingsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsWindow))
        return static_cast<void*>(const_cast< SettingsWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SettingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_GraphSettingsWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_GraphSettingsWidget[] = {
    "GraphSettingsWidget\0"
};

void GraphSettingsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GraphSettingsWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GraphSettingsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GraphSettingsWidget,
      qt_meta_data_GraphSettingsWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphSettingsWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphSettingsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphSettingsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphSettingsWidget))
        return static_cast<void*>(const_cast< GraphSettingsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GraphSettingsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_GraphSettingsRelativeTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   26,   25,   25, 0x0a,
      65,   59,   25,   25, 0x0a,
     102,   93,   25,   25, 0x0a,
     134,  129,   25,   25, 0x0a,
     150,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphSettingsRelativeTab[] = {
    "GraphSettingsRelativeTab\0\0enable\0"
    "updateEnableSetting(bool)\0color\0"
    "updateColorSetting(QString)\0gridList\0"
    "updateAxisSetting(QString)\0unit\0"
    "updateUnit(int)\0showColorPicker()\0"
};

void GraphSettingsRelativeTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GraphSettingsRelativeTab *_t = static_cast<GraphSettingsRelativeTab *>(_o);
        switch (_id) {
        case 0: _t->updateEnableSetting((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateColorSetting((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateAxisSetting((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateUnit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->showColorPicker(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GraphSettingsRelativeTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GraphSettingsRelativeTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GraphSettingsRelativeTab,
      qt_meta_data_GraphSettingsRelativeTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphSettingsRelativeTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphSettingsRelativeTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphSettingsRelativeTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphSettingsRelativeTab))
        return static_cast<void*>(const_cast< GraphSettingsRelativeTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int GraphSettingsRelativeTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_AdvancedSettingsWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   24,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AdvancedSettingsWidget[] = {
    "AdvancedSettingsWidget\0\0enabled\0"
    "enableDiagnosticLogging(bool)\0"
};

void AdvancedSettingsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AdvancedSettingsWidget *_t = static_cast<AdvancedSettingsWidget *>(_o);
        switch (_id) {
        case 0: _t->enableDiagnosticLogging((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AdvancedSettingsWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AdvancedSettingsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AdvancedSettingsWidget,
      qt_meta_data_AdvancedSettingsWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AdvancedSettingsWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AdvancedSettingsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AdvancedSettingsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AdvancedSettingsWidget))
        return static_cast<void*>(const_cast< AdvancedSettingsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AdvancedSettingsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ModbusRTUDevice[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      40,   16,   16,   16, 0x05,
      63,   16,   16,   16, 0x05,
      85,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     101,   98,   16,   16, 0x0a,
     118,   16,   16,   16, 0x08,
     134,   16,   16,   16, 0x08,
     161,  152,   16,   16, 0x08,
     189,  152,   16,   16, 0x08,
     214,  152,   16,   16, 0x08,
     238,  152,   16,   16, 0x08,
     262,   16,   16,   16, 0x08,
     283,  152,   16,   16, 0x08,
     305,  152,   16,   16, 0x08,
     324,   16,   16,   16, 0x08,

 // methods: signature, parameters, type, tag, flags
     341,   16,  334,   16, 0x02,
     351,   16,  334,   16, 0x02,
     365,   16,  361,   16, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModbusRTUDevice[] = {
    "ModbusRTUDevice\0\0SVLowerChanged(double)\0"
    "SVUpperChanged(double)\0SVDecimalChanged(int)\0"
    "queueEmpty()\0sv\0outputSV(double)\0"
    "dataAvailable()\0sendNextMessage()\0"
    "response\0decimalResponse(QByteArray)\0"
    "unitResponse(QByteArray)\0"
    "svlResponse(QByteArray)\0svuResponse(QByteArray)\0"
    "requestMeasurement()\0mResponse(QByteArray)\0"
    "ignore(QByteArray)\0timeout()\0double\0"
    "SVLower()\0SVUpper()\0int\0decimals()\0"
};

void ModbusRTUDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusRTUDevice *_t = static_cast<ModbusRTUDevice *>(_o);
        switch (_id) {
        case 0: _t->SVLowerChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->SVUpperChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->SVDecimalChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->queueEmpty(); break;
        case 4: _t->outputSV((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->dataAvailable(); break;
        case 6: _t->sendNextMessage(); break;
        case 7: _t->decimalResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->unitResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 9: _t->svlResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->svuResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->requestMeasurement(); break;
        case 12: _t->mResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 13: _t->ignore((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: _t->timeout(); break;
        case 15: { double _r = _t->SVLower();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 16: { double _r = _t->SVUpper();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 17: { int _r = _t->decimals();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusRTUDevice::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusRTUDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModbusRTUDevice,
      qt_meta_data_ModbusRTUDevice, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusRTUDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusRTUDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusRTUDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusRTUDevice))
        return static_cast<void*>(const_cast< ModbusRTUDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int ModbusRTUDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ModbusRTUDevice::SVLowerChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModbusRTUDevice::SVUpperChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModbusRTUDevice::SVDecimalChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ModbusRTUDevice::queueEmpty()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_ModbusConfigurator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,  154, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   20,   19,   19, 0x08,
      56,   48,   19,   19, 0x08,
      90,   80,   19,   19, 0x08,
     120,  112,   19,   19, 0x08,
     159,  147,   19,   19, 0x08,
     191,  183,   19,   19, 0x08,
     216,  210,   19,   19, 0x08,
     249,  241,   19,   19, 0x08,
     284,  275,   19,   19, 0x08,
     311,  210,   19,   19, 0x08,
     333,  241,   19,   19, 0x08,
     362,  356,   19,   19, 0x08,
     383,  356,   19,   19, 0x08,
     412,  404,   19,   19, 0x08,
     432,  241,   19,   19, 0x08,
     461,  453,   19,   19, 0x08,
     483,  241,   19,   19, 0x08,
     514,  508,   19,   19, 0x08,
     538,  241,   19,   19, 0x08,
     564,  241,   19,   19, 0x08,
     590,  356,   19,   19, 0x08,
     612,  356,   19,   19, 0x08,
     645,  634,   19,   19, 0x08,
     668,  241,   19,   19, 0x08,
     699,  694,   19,   19, 0x08,
     727,  694,   19,   19, 0x08,
     762,  755,   19,   19, 0x08,
     783,  755,   19,   19, 0x08,

 // constructors: signature, parameters, type, tag, flags
     816,  804,   19,   19, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusConfigurator[] = {
    "ModbusConfigurator\0\0newPort\0"
    "updatePort(QString)\0newRate\0"
    "updateBaudRate(QString)\0newParity\0"
    "updateParity(QString)\0newFlow\0"
    "updateFlowControl(QString)\0newStopBits\0"
    "updateStopBits(QString)\0station\0"
    "updateStation(int)\0fixed\0"
    "updateFixedDecimal(bool)\0address\0"
    "updateDecimalAddress(int)\0position\0"
    "updateDecimalPosition(int)\0"
    "updateFixedUnit(bool)\0updateUnitAddress(int)\0"
    "value\0updateValueForF(int)\0"
    "updateValueForC(int)\0newUnit\0"
    "updateUnit(QString)\0updatePVAddress(int)\0"
    "enabled\0updateSVEnabled(bool)\0"
    "updateSVReadAddress(int)\0query\0"
    "updateDeviceLimit(bool)\0"
    "updateSVLowerAddress(int)\0"
    "updateSVUpperAddress(int)\0"
    "updateSVLower(double)\0updateSVUpper(double)\0"
    "canWriteSV\0updateSVWritable(bool)\0"
    "updateSVWriteAddress(int)\0name\0"
    "updatePVColumnName(QString)\0"
    "updateSVColumnName(QString)\0hidden\0"
    "updatePVHidden(bool)\0updateSVHidden(bool)\0"
    "model,index\0"
    "ModbusConfigurator(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusConfigurator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusConfigurator *_r = new ModbusConfigurator((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusConfigurator *_t = static_cast<ModbusConfigurator *>(_o);
        switch (_id) {
        case 0: _t->updatePort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateBaudRate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateParity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateFlowControl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateStopBits((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateStation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateFixedDecimal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->updateDecimalAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->updateDecimalPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->updateFixedUnit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->updateUnitAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateValueForF((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateValueForC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->updateUnit((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->updatePVAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateSVEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->updateSVReadAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->updateDeviceLimit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->updateSVLowerAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->updateSVUpperAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->updateSVLower((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->updateSVUpper((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->updateSVWritable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->updateSVWriteAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->updatePVColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: _t->updateSVColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->updatePVHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->updateSVHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusConfigurator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusConfigurator::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusConfigurator,
      qt_meta_data_ModbusConfigurator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusConfigurator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusConfigurator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusConfigurator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusConfigurator))
        return static_cast<void*>(const_cast< ModbusConfigurator*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusConfigurator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}
static const uint qt_meta_data_ModbusNGConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   44, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x08,
      46,   20,   19,   19, 0x08,
      70,   20,   19,   19, 0x08,
      88,   20,   19,   19, 0x08,
     111,   20,   19,   19, 0x08,
     131,   19,   19,   19, 0x08,

 // constructors: signature, parameters, type, tag, flags
     154,  142,   19,   19, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusNGConfWidget[] = {
    "ModbusNGConfWidget\0\0value\0updatePort(QString)\0"
    "updateBaudRate(QString)\0updateParity(int)\0"
    "updateFlowControl(int)\0updateStopBits(int)\0"
    "addInput()\0model,index\0"
    "ModbusNGConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusNGConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusNGConfWidget *_r = new ModbusNGConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusNGConfWidget *_t = static_cast<ModbusNGConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updatePort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateBaudRate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateParity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateFlowControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateStopBits((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->addInput(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusNGConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusNGConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusNGConfWidget,
      qt_meta_data_ModbusNGConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusNGConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusNGConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusNGConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusNGConfWidget))
        return static_cast<void*>(const_cast< ModbusNGConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusNGConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_ModbusNGInputConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   54, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   25,   24,   24, 0x08,
      50,   25,   24,   24, 0x08,
      69,   25,   24,   24, 0x08,
      89,   25,   24,   24, 0x08,
     107,   25,   24,   24, 0x08,
     127,   25,   24,   24, 0x08,
     143,   25,   24,   24, 0x08,
     169,   25,   24,   24, 0x08,

 // constructors: signature, parameters, type, tag, flags
     200,  188,   24,   24, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ModbusNGInputConfWidget[] = {
    "ModbusNGInputConfWidget\0\0value\0"
    "updateStation(int)\0updateAddress(int)\0"
    "updateFunction(int)\0updateFormat(int)\0"
    "updateDecimals(int)\0updateUnit(int)\0"
    "updateColumnName(QString)\0updateHidden(bool)\0"
    "model,index\0"
    "ModbusNGInputConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ModbusNGInputConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ModbusNGInputConfWidget *_r = new ModbusNGInputConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusNGInputConfWidget *_t = static_cast<ModbusNGInputConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateStation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateFunction((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateFormat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateDecimals((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateUnit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->updateHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusNGInputConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusNGInputConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ModbusNGInputConfWidget,
      qt_meta_data_ModbusNGInputConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusNGInputConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusNGInputConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusNGInputConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusNGInputConfWidget))
        return static_cast<void*>(const_cast< ModbusNGInputConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ModbusNGInputConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
static const uint qt_meta_data_ModbusNG[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      28,    9,    9,    9, 0x08,
      38,    9,    9,    9, 0x08,
      54,    9,    9,    9, 0x08,

 // methods: signature, parameters, type, tag, flags
      77,    9,   73,    9, 0x02,
     100,    9,   92,    9, 0x02,
     123,    9,   92,    9, 0x02,
     154,    9,  149,    9, 0x02,
     175,    9,   92,    9, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ModbusNG[] = {
    "ModbusNG\0\0sendNextMessage()\0timeout()\0"
    "dataAvailable()\0rateLimitTimeout()\0"
    "int\0channelCount()\0QString\0"
    "channelColumnName(int)\0channelIndicatorText(int)\0"
    "bool\0isChannelHidden(int)\0channelType(int)\0"
};

void ModbusNG::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModbusNG *_t = static_cast<ModbusNG *>(_o);
        switch (_id) {
        case 0: _t->sendNextMessage(); break;
        case 1: _t->timeout(); break;
        case 2: _t->dataAvailable(); break;
        case 3: _t->rateLimitTimeout(); break;
        case 4: { int _r = _t->channelCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->channelColumnName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->channelIndicatorText((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->isChannelHidden((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->channelType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModbusNG::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModbusNG::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModbusNG,
      qt_meta_data_ModbusNG, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModbusNG::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModbusNG::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModbusNG::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusNG))
        return static_cast<void*>(const_cast< ModbusNG*>(this));
    return QObject::qt_metacast(_clname);
}

int ModbusNG::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
static const uint qt_meta_data_UnsupportedSerialDeviceConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   34,   34,   34, 0x08,
      57,   34,   34,   34, 0x08,
      70,   34,   34,   34, 0x08,

 // constructors: signature, parameters, type, tag, flags
      95,   83,   34,   34, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_UnsupportedSerialDeviceConfWidget[] = {
    "UnsupportedSerialDeviceConfWidget\0\0"
    "updateConfiguration()\0saveScript()\0"
    "addChannel()\0model,index\0"
    "UnsupportedSerialDeviceConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void UnsupportedSerialDeviceConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { UnsupportedSerialDeviceConfWidget *_r = new UnsupportedSerialDeviceConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UnsupportedSerialDeviceConfWidget *_t = static_cast<UnsupportedSerialDeviceConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateConfiguration(); break;
        case 1: _t->saveScript(); break;
        case 2: _t->addChannel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UnsupportedSerialDeviceConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UnsupportedSerialDeviceConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_UnsupportedSerialDeviceConfWidget,
      qt_meta_data_UnsupportedSerialDeviceConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UnsupportedSerialDeviceConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UnsupportedSerialDeviceConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UnsupportedSerialDeviceConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UnsupportedSerialDeviceConfWidget))
        return static_cast<void*>(const_cast< UnsupportedSerialDeviceConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int UnsupportedSerialDeviceConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_UnsupportedDeviceChannelConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      42,   36,   35,   35, 0x08,
      75,   68,   35,   35, 0x08,
      94,   35,   35,   35, 0x08,

 // constructors: signature, parameters, type, tag, flags
     128,  116,   35,   35, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_UnsupportedDeviceChannelConfWidget[] = {
    "UnsupportedDeviceChannelConfWidget\0\0"
    "value\0updateColumnName(QString)\0hidden\0"
    "updateHidden(bool)\0updateConfiguration()\0"
    "model,index\0"
    "UnsupportedDeviceChannelConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void UnsupportedDeviceChannelConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { UnsupportedDeviceChannelConfWidget *_r = new UnsupportedDeviceChannelConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UnsupportedDeviceChannelConfWidget *_t = static_cast<UnsupportedDeviceChannelConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateConfiguration(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UnsupportedDeviceChannelConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UnsupportedDeviceChannelConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_UnsupportedDeviceChannelConfWidget,
      qt_meta_data_UnsupportedDeviceChannelConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UnsupportedDeviceChannelConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UnsupportedDeviceChannelConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UnsupportedDeviceChannelConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UnsupportedDeviceChannelConfWidget))
        return static_cast<void*>(const_cast< UnsupportedDeviceChannelConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int UnsupportedDeviceChannelConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_JavaScriptDevice[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   79, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   18,   17,   17, 0x05,
      61,   17,   17,   17, 0x05,
      81,   17,   17,   17, 0x05,
     100,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     127,  122,   17,   17, 0x0a,
     158,  153,   17,   17, 0x0a,
     183,   17,   17,   17, 0x0a,
     191,   17,   17,   17, 0x0a,

 // methods: signature, parameters, type, tag, flags
     202,   17,  198,   17, 0x02,
     230,  222,  217,   17, 0x02,
     263,  222,  251,   17, 0x02,
     296,  222,  288,   17, 0x02,
     319,  222,  288,   17, 0x02,

 // constructors: signature, parameters, type, tag, flags
     364,  345,   17,   17, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_JavaScriptDevice[] = {
    "JavaScriptDevice\0\0note,tcol,ncol\0"
    "annotation(QString,int,int)\0"
    "triggerStartBatch()\0triggerStopBatch()\0"
    "deviceStopRequested()\0tcol\0"
    "setTemperatureColumn(int)\0ncol\0"
    "setAnnotationColumn(int)\0start()\0"
    "stop()\0int\0channelCount()\0bool\0channel\0"
    "isChannelHidden(int)\0Units::Unit\0"
    "expectedChannelUnit(int)\0QString\0"
    "channelColumnName(int)\0channelIndicatorText(int)\0"
    "deviceIndex,engine\0"
    "JavaScriptDevice(QModelIndex,QScriptEngine*)\0"
};

void JavaScriptDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { JavaScriptDevice *_r = new JavaScriptDevice((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< QScriptEngine*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        JavaScriptDevice *_t = static_cast<JavaScriptDevice *>(_o);
        switch (_id) {
        case 0: _t->annotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->triggerStartBatch(); break;
        case 2: _t->triggerStopBatch(); break;
        case 3: _t->deviceStopRequested(); break;
        case 4: _t->setTemperatureColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setAnnotationColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->start(); break;
        case 7: _t->stop(); break;
        case 8: { int _r = _t->channelCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->isChannelHidden((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { Units::Unit _r = _t->expectedChannelUnit((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Units::Unit*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->channelColumnName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->channelIndicatorText((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData JavaScriptDevice::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject JavaScriptDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JavaScriptDevice,
      qt_meta_data_JavaScriptDevice, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JavaScriptDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JavaScriptDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JavaScriptDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JavaScriptDevice))
        return static_cast<void*>(const_cast< JavaScriptDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int JavaScriptDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void JavaScriptDevice::annotation(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JavaScriptDevice::triggerStartBatch()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void JavaScriptDevice::triggerStopBatch()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void JavaScriptDevice::deviceStopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_PhidgetsTemperatureSensorConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   36,   36,   36, 0x08,
      53,   50,   36,   36, 0x08,

 // constructors: signature, parameters, type, tag, flags
      81,   69,   36,   36, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_PhidgetsTemperatureSensorConfWidget[] = {
    "PhidgetsTemperatureSensorConfWidget\0"
    "\0addChannel()\0ms\0updateRate(int)\0"
    "model,index\0"
    "PhidgetsTemperatureSensorConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void PhidgetsTemperatureSensorConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { PhidgetsTemperatureSensorConfWidget *_r = new PhidgetsTemperatureSensorConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PhidgetsTemperatureSensorConfWidget *_t = static_cast<PhidgetsTemperatureSensorConfWidget *>(_o);
        switch (_id) {
        case 0: _t->addChannel(); break;
        case 1: _t->updateRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PhidgetsTemperatureSensorConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhidgetsTemperatureSensorConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_PhidgetsTemperatureSensorConfWidget,
      qt_meta_data_PhidgetsTemperatureSensorConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhidgetsTemperatureSensorConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhidgetsTemperatureSensorConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhidgetsTemperatureSensorConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhidgetsTemperatureSensorConfWidget))
        return static_cast<void*>(const_cast< PhidgetsTemperatureSensorConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int PhidgetsTemperatureSensorConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_PhidgetTemperatureSensorChannelConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   34, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      49,   43,   42,   42, 0x08,
      82,   75,   42,   42, 0x08,
     107,  101,   42,   42, 0x08,
     129,  121,   42,   42, 0x08,

 // constructors: signature, parameters, type, tag, flags
     160,  148,   42,   42, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_PhidgetTemperatureSensorChannelConfWidget[] = {
    "PhidgetTemperatureSensorChannelConfWidget\0"
    "\0value\0updateColumnName(QString)\0"
    "hidden\0updateHidden(bool)\0index\0"
    "updateTC(int)\0channel\0updateChannel(int)\0"
    "model,index\0"
    "PhidgetTemperatureSensorChannelConfWidget(DeviceTreeModel*,QModelIndex"
    ")\0"
};

void PhidgetTemperatureSensorChannelConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { PhidgetTemperatureSensorChannelConfWidget *_r = new PhidgetTemperatureSensorChannelConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PhidgetTemperatureSensorChannelConfWidget *_t = static_cast<PhidgetTemperatureSensorChannelConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateTC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PhidgetTemperatureSensorChannelConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhidgetTemperatureSensorChannelConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_PhidgetTemperatureSensorChannelConfWidget,
      qt_meta_data_PhidgetTemperatureSensorChannelConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhidgetTemperatureSensorChannelConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhidgetTemperatureSensorChannelConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhidgetTemperatureSensorChannelConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhidgetTemperatureSensorChannelConfWidget))
        return static_cast<void*>(const_cast< PhidgetTemperatureSensorChannelConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int PhidgetTemperatureSensorChannelConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_PhidgetsTemperatureSensor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   49, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,
      35,   26,   26,   26, 0x0a,
      42,   26,   26,   26, 0x08,

 // methods: signature, parameters, type, tag, flags
      64,   26,   60,   26, 0x02,
      92,   84,   79,   26, 0x02,
     121,   84,  113,   26, 0x02,
     144,   84,  113,   26, 0x02,

 // constructors: signature, parameters, type, tag, flags
     182,  170,   26,   26, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_PhidgetsTemperatureSensor[] = {
    "PhidgetsTemperatureSensor\0\0start()\0"
    "stop()\0getMeasurements()\0int\0"
    "channelCount()\0bool\0channel\0"
    "isChannelHidden(int)\0QString\0"
    "channelColumnName(int)\0channelIndicatorText(int)\0"
    "deviceIndex\0PhidgetsTemperatureSensor(QModelIndex)\0"
};

void PhidgetsTemperatureSensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { PhidgetsTemperatureSensor *_r = new PhidgetsTemperatureSensor((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PhidgetsTemperatureSensor *_t = static_cast<PhidgetsTemperatureSensor *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop(); break;
        case 2: _t->getMeasurements(); break;
        case 3: { int _r = _t->channelCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->isChannelHidden((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->channelColumnName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->channelIndicatorText((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PhidgetsTemperatureSensor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhidgetsTemperatureSensor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PhidgetsTemperatureSensor,
      qt_meta_data_PhidgetsTemperatureSensor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhidgetsTemperatureSensor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhidgetsTemperatureSensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhidgetsTemperatureSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhidgetsTemperatureSensor))
        return static_cast<void*>(const_cast< PhidgetsTemperatureSensor*>(this));
    return QObject::qt_metacast(_clname);
}

int PhidgetsTemperatureSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_PhidgetConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   19, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,

 // constructors: signature, parameters, type, tag, flags
      44,   32,   18,   18, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_PhidgetConfWidget[] = {
    "PhidgetConfWidget\0\0addChannel()\0"
    "model,index\0PhidgetConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void PhidgetConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { PhidgetConfWidget *_r = new PhidgetConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PhidgetConfWidget *_t = static_cast<PhidgetConfWidget *>(_o);
        switch (_id) {
        case 0: _t->addChannel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PhidgetConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhidgetConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_PhidgetConfWidget,
      qt_meta_data_PhidgetConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhidgetConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhidgetConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhidgetConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhidgetConfWidget))
        return static_cast<void*>(const_cast< PhidgetConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int PhidgetConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_PhidgetChannelSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_PhidgetChannelSelector[] = {
    "PhidgetChannelSelector\0"
};

void PhidgetChannelSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PhidgetChannelSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhidgetChannelSelector::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_PhidgetChannelSelector,
      qt_meta_data_PhidgetChannelSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhidgetChannelSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhidgetChannelSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhidgetChannelSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhidgetChannelSelector))
        return static_cast<void*>(const_cast< PhidgetChannelSelector*>(this));
    return QComboBox::qt_metacast(_clname);
}

int PhidgetChannelSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PhidgetChannelConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   64, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   26,   25,   25, 0x0a,
      65,   59,   25,   25, 0x0a,
      93,   59,   25,   25, 0x0a,
     116,   59,   25,   25, 0x0a,
     139,   59,   25,   25, 0x0a,
     165,   59,   25,   25, 0x0a,
     188,   59,   25,   25, 0x0a,
     206,   59,   25,   25, 0x0a,
     225,   59,   25,   25, 0x0a,
     246,   59,   25,   25, 0x0a,

 // constructors: signature, parameters, type, tag, flags
     276,  264,   25,   25, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_PhidgetChannelConfWidget[] = {
    "PhidgetChannelConfWidget\0\0index\0"
    "changeSelectedChannel(int)\0value\0"
    "updateSerialNumber(QString)\0"
    "updateChannel(QString)\0updateHubPort(QString)\0"
    "updateColumnName(QString)\0"
    "updateChannelType(int)\0updateTCType(int)\0"
    "updateRTDType(int)\0updateRTDWiring(int)\0"
    "updateHidden(int)\0model,index\0"
    "PhidgetChannelConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void PhidgetChannelConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { PhidgetChannelConfWidget *_r = new PhidgetChannelConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PhidgetChannelConfWidget *_t = static_cast<PhidgetChannelConfWidget *>(_o);
        switch (_id) {
        case 0: _t->changeSelectedChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateSerialNumber((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateChannel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateHubPort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateChannelType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateTCType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->updateRTDType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->updateRTDWiring((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->updateHidden((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PhidgetChannelConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhidgetChannelConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_PhidgetChannelConfWidget,
      qt_meta_data_PhidgetChannelConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhidgetChannelConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhidgetChannelConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhidgetChannelConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhidgetChannelConfWidget))
        return static_cast<void*>(const_cast< PhidgetChannelConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int PhidgetChannelConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
static const uint qt_meta_data_Phidget22[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   44, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      19,   10,   10,   10, 0x0a,

 // methods: signature, parameters, type, tag, flags
      30,   10,   26,   10, 0x02,
      58,   50,   45,   10, 0x02,
      87,   50,   79,   10, 0x02,
     110,   50,   79,   10, 0x02,

 // constructors: signature, parameters, type, tag, flags
     148,  136,   10,   10, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_Phidget22[] = {
    "Phidget22\0\0start()\0stop()\0int\0"
    "channelCount()\0bool\0channel\0"
    "isChannelHidden(int)\0QString\0"
    "channelColumnName(int)\0channelIndicatorText(int)\0"
    "deviceIndex\0Phidget22(QModelIndex)\0"
};

void Phidget22::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Phidget22 *_r = new Phidget22((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Phidget22 *_t = static_cast<Phidget22 *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop(); break;
        case 2: { int _r = _t->channelCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->isChannelHidden((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->channelColumnName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->channelIndicatorText((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Phidget22::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Phidget22::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Phidget22,
      qt_meta_data_Phidget22, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Phidget22::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Phidget22::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Phidget22::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Phidget22))
        return static_cast<void*>(const_cast< Phidget22*>(this));
    return QObject::qt_metacast(_clname);
}

int Phidget22::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_LinearSplineInterpolationConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      44,   37,   36,   36, 0x08,
      77,   72,   36,   36, 0x08,
     110,   36,   36,   36, 0x08,

 // constructors: signature, parameters, type, tag, flags
     136,  124,   36,   36, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_LinearSplineInterpolationConfWidget[] = {
    "LinearSplineInterpolationConfWidget\0"
    "\0source\0updateSourceColumn(QString)\0"
    "dest\0updateDestinationColumn(QString)\0"
    "updateKnots()\0model,index\0"
    "LinearSplineInterpolationConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void LinearSplineInterpolationConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { LinearSplineInterpolationConfWidget *_r = new LinearSplineInterpolationConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LinearSplineInterpolationConfWidget *_t = static_cast<LinearSplineInterpolationConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateSourceColumn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateDestinationColumn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateKnots(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LinearSplineInterpolationConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LinearSplineInterpolationConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_LinearSplineInterpolationConfWidget,
      qt_meta_data_LinearSplineInterpolationConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LinearSplineInterpolationConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LinearSplineInterpolationConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LinearSplineInterpolationConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LinearSplineInterpolationConfWidget))
        return static_cast<void*>(const_cast< LinearSplineInterpolationConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int LinearSplineInterpolationConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CoolingTimerConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   19, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   24,   23,   23, 0x08,

 // constructors: signature, parameters, type, tag, flags
      64,   52,   23,   23, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_CoolingTimerConfWidget[] = {
    "CoolingTimerConfWidget\0\0time\0"
    "updateResetTime(QTime)\0model,index\0"
    "CoolingTimerConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void CoolingTimerConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { CoolingTimerConfWidget *_r = new CoolingTimerConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CoolingTimerConfWidget *_t = static_cast<CoolingTimerConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateResetTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CoolingTimerConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CoolingTimerConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_CoolingTimerConfWidget,
      qt_meta_data_CoolingTimerConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CoolingTimerConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CoolingTimerConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CoolingTimerConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoolingTimerConfWidget))
        return static_cast<void*>(const_cast< CoolingTimerConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int CoolingTimerConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_RangeTimerConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   54, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   22,   21,   21, 0x08,
      58,   22,   21,   21, 0x08,
      88,   22,   21,   21, 0x08,
     119,   22,   21,   21, 0x08,
     149,   22,   21,   21, 0x08,
     175,   22,   21,   21, 0x08,
     207,  200,   21,   21, 0x08,
     231,  200,   21,   21, 0x08,

 // constructors: signature, parameters, type, tag, flags
     266,  254,   21,   21, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_RangeTimerConfWidget[] = {
    "RangeTimerConfWidget\0\0text\0"
    "updateStartButtonText(QString)\0"
    "updateStopButtonText(QString)\0"
    "updateStartColumnName(QString)\0"
    "updateStopColumnName(QString)\0"
    "updateStartValue(QString)\0"
    "updateStopValue(QString)\0option\0"
    "updateStartTrigger(int)\0updateStopTrigger(int)\0"
    "model,index\0"
    "RangeTimerConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void RangeTimerConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { RangeTimerConfWidget *_r = new RangeTimerConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RangeTimerConfWidget *_t = static_cast<RangeTimerConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateStartButtonText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateStopButtonText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateStartColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateStopColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateStartValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateStopValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updateStartTrigger((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->updateStopTrigger((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RangeTimerConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RangeTimerConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_RangeTimerConfWidget,
      qt_meta_data_RangeTimerConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RangeTimerConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RangeTimerConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RangeTimerConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RangeTimerConfWidget))
        return static_cast<void*>(const_cast< RangeTimerConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int RangeTimerConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
static const uint qt_meta_data_MultiRangeTimerConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   27,   26,   26, 0x08,
      58,   26,   26,   26, 0x08,

 // constructors: signature, parameters, type, tag, flags
      88,   76,   26,   26, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_MultiRangeTimerConfWidget[] = {
    "MultiRangeTimerConfWidget\0\0text\0"
    "updateColumnName(QString)\0updateRangeData()\0"
    "model,index\0"
    "MultiRangeTimerConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void MultiRangeTimerConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { MultiRangeTimerConfWidget *_r = new MultiRangeTimerConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultiRangeTimerConfWidget *_t = static_cast<MultiRangeTimerConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateRangeData(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultiRangeTimerConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultiRangeTimerConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_MultiRangeTimerConfWidget,
      qt_meta_data_MultiRangeTimerConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultiRangeTimerConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultiRangeTimerConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultiRangeTimerConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultiRangeTimerConfWidget))
        return static_cast<void*>(const_cast< MultiRangeTimerConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int MultiRangeTimerConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_TranslationConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   23,   22,   22, 0x08,
      60,   22,   22,   22, 0x08,
      80,   22,   22,   22, 0x08,

 // constructors: signature, parameters, type, tag, flags
     106,   94,   22,   22, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_TranslationConfWidget[] = {
    "TranslationConfWidget\0\0column\0"
    "updateMatchingColumn(QString)\0"
    "updateTemperature()\0updateDelay()\0"
    "model,index\0"
    "TranslationConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void TranslationConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { TranslationConfWidget *_r = new TranslationConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TranslationConfWidget *_t = static_cast<TranslationConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateMatchingColumn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateTemperature(); break;
        case 2: _t->updateDelay(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TranslationConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TranslationConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_TranslationConfWidget,
      qt_meta_data_TranslationConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TranslationConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TranslationConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TranslationConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TranslationConfWidget))
        return static_cast<void*>(const_cast< TranslationConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int TranslationConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_RateOfChange[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   14,   13,   13, 0x0a,
      79,   71,   13,   13, 0x0a,
      97,   71,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RateOfChange[] = {
    "RateOfChange\0\0measure\0newData(Measurement)\0"
    "newMeasurement(Measurement)\0seconds\0"
    "setCacheTime(int)\0setScaleTime(int)\0"
};

void RateOfChange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RateOfChange *_t = static_cast<RateOfChange *>(_o);
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->setCacheTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setScaleTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RateOfChange::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RateOfChange::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RateOfChange,
      qt_meta_data_RateOfChange, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RateOfChange::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RateOfChange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RateOfChange::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RateOfChange))
        return static_cast<void*>(const_cast< RateOfChange*>(this));
    return QObject::qt_metacast(_clname);
}

int RateOfChange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RateOfChange::newData(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_RateOfChangeConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   24,   23,   23, 0x08,
      61,   53,   23,   23, 0x08,
      86,   53,   23,   23, 0x08,

 // constructors: signature, parameters, type, tag, flags
     123,  111,   23,   23, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_RateOfChangeConfWidget[] = {
    "RateOfChangeConfWidget\0\0column\0"
    "updateColumn(QString)\0seconds\0"
    "updateCacheTime(QString)\0"
    "updateScaleTime(QString)\0model,index\0"
    "RateOfChangeConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void RateOfChangeConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { RateOfChangeConfWidget *_r = new RateOfChangeConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RateOfChangeConfWidget *_t = static_cast<RateOfChangeConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateColumn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateCacheTime((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateScaleTime((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RateOfChangeConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RateOfChangeConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_RateOfChangeConfWidget,
      qt_meta_data_RateOfChangeConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RateOfChangeConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RateOfChangeConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RateOfChangeConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RateOfChangeConfWidget))
        return static_cast<void*>(const_cast< RateOfChangeConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int RateOfChangeConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_MergeSeries[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   13,   12,   12, 0x0a,
      59,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MergeSeries[] = {
    "MergeSeries\0\0measure\0newData(Measurement)\0"
    "in1(Measurement)\0in2(Measurement)\0"
};

void MergeSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MergeSeries *_t = static_cast<MergeSeries *>(_o);
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 1: _t->in1((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->in2((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MergeSeries::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MergeSeries::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MergeSeries,
      qt_meta_data_MergeSeries, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MergeSeries::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MergeSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MergeSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MergeSeries))
        return static_cast<void*>(const_cast< MergeSeries*>(this));
    return QObject::qt_metacast(_clname);
}

int MergeSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MergeSeries::newData(Measurement _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_DifferenceSeries[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DifferenceSeries[] = {
    "DifferenceSeries\0"
};

void DifferenceSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DifferenceSeries::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DifferenceSeries::staticMetaObject = {
    { &MergeSeries::staticMetaObject, qt_meta_stringdata_DifferenceSeries,
      qt_meta_data_DifferenceSeries, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DifferenceSeries::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DifferenceSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DifferenceSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DifferenceSeries))
        return static_cast<void*>(const_cast< DifferenceSeries*>(this));
    return MergeSeries::qt_metacast(_clname);
}

int DifferenceSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MergeSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_MeanSeries[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_MeanSeries[] = {
    "MeanSeries\0"
};

void MeanSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MeanSeries::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MeanSeries::staticMetaObject = {
    { &MergeSeries::staticMetaObject, qt_meta_stringdata_MeanSeries,
      qt_meta_data_MeanSeries, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MeanSeries::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MeanSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MeanSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeanSeries))
        return static_cast<void*>(const_cast< MeanSeries*>(this));
    return MergeSeries::qt_metacast(_clname);
}

int MeanSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MergeSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_MergeSeriesConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   34, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   23,   22,   22, 0x08,
      53,   23,   22,   22, 0x08,
      76,   23,   22,   22, 0x08,
     103,   98,   22,   22, 0x08,

 // constructors: signature, parameters, type, tag, flags
     131,  119,   22,   22, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_MergeSeriesConfWidget[] = {
    "MergeSeriesConfWidget\0\0column\0"
    "updateColumn1(QString)\0updateColumn2(QString)\0"
    "updateOutput(QString)\0type\0updateType(int)\0"
    "model,index\0"
    "MergeSeriesConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void MergeSeriesConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { MergeSeriesConfWidget *_r = new MergeSeriesConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MergeSeriesConfWidget *_t = static_cast<MergeSeriesConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateColumn1((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateColumn2((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateOutput((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MergeSeriesConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MergeSeriesConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_MergeSeriesConfWidget,
      qt_meta_data_MergeSeriesConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MergeSeriesConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MergeSeriesConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MergeSeriesConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MergeSeriesConfWidget))
        return static_cast<void*>(const_cast< MergeSeriesConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int MergeSeriesConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_DataqSdkDevice[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,

 // methods: signature, parameters, type, tag, flags
      36,   33,   15,   15, 0x02,
      57,   15,   15,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_DataqSdkDevice[] = {
    "DataqSdkDevice\0\0threadFinished()\0Hz\0"
    "setClockRate(double)\0start()\0"
};

void DataqSdkDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataqSdkDevice *_t = static_cast<DataqSdkDevice *>(_o);
        switch (_id) {
        case 0: _t->threadFinished(); break;
        case 1: _t->setClockRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataqSdkDevice::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataqSdkDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataqSdkDevice,
      qt_meta_data_DataqSdkDevice, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataqSdkDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataqSdkDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataqSdkDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataqSdkDevice))
        return static_cast<void*>(const_cast< DataqSdkDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int DataqSdkDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_DataqSdkDeviceImplementation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DataqSdkDeviceImplementation[] = {
    "DataqSdkDeviceImplementation\0\0measure()\0"
};

void DataqSdkDeviceImplementation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataqSdkDeviceImplementation *_t = static_cast<DataqSdkDeviceImplementation *>(_o);
        switch (_id) {
        case 0: _t->measure(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DataqSdkDeviceImplementation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataqSdkDeviceImplementation::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DataqSdkDeviceImplementation,
      qt_meta_data_DataqSdkDeviceImplementation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataqSdkDeviceImplementation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataqSdkDeviceImplementation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataqSdkDeviceImplementation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataqSdkDeviceImplementation))
        return static_cast<void*>(const_cast< DataqSdkDeviceImplementation*>(this));
    return QThread::qt_metacast(_clname);
}

int DataqSdkDeviceImplementation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_DataqSdkDeviceConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   34, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   26,   25,   25, 0x08,
      72,   59,   25,   25, 0x08,
     103,   96,   25,   25, 0x08,
     123,   25,   25,   25, 0x08,

 // constructors: signature, parameters, type, tag, flags
     148,  136,   25,   25, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_DataqSdkDeviceConfWidget[] = {
    "DataqSdkDeviceConfWidget\0\0automatic\0"
    "updateAutoSelect(bool)\0deviceNumber\0"
    "updateDeviceNumber(int)\0portId\0"
    "updatePort(QString)\0addChannel()\0"
    "model,index\0"
    "DataqSdkDeviceConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void DataqSdkDeviceConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { DataqSdkDeviceConfWidget *_r = new DataqSdkDeviceConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataqSdkDeviceConfWidget *_t = static_cast<DataqSdkDeviceConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateAutoSelect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateDeviceNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updatePort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->addChannel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataqSdkDeviceConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataqSdkDeviceConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_DataqSdkDeviceConfWidget,
      qt_meta_data_DataqSdkDeviceConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataqSdkDeviceConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataqSdkDeviceConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataqSdkDeviceConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataqSdkDeviceConfWidget))
        return static_cast<void*>(const_cast< DataqSdkDeviceConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int DataqSdkDeviceConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_DataqSdkChannelConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   89, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   27,   26,   26, 0x08,
      59,   53,   26,   26, 0x08,
      85,   53,   26,   26, 0x08,
     114,   53,   26,   26, 0x08,
     143,   53,   26,   26, 0x08,
     170,   53,   26,   26, 0x08,
     204,  197,   26,   26, 0x08,
     239,  231,   26,   26, 0x08,
     268,   53,   26,   26, 0x08,
     295,   26,   26,   26, 0x08,
     314,   26,   26,   26, 0x08,
     332,   26,   26,   26, 0x08,
     359,  351,   26,   26, 0x08,
     384,  351,   26,   26, 0x08,
     417,  410,   26,   26, 0x08,

 // constructors: signature, parameters, type, tag, flags
     448,  436,   26,   26, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_DataqSdkChannelConfWidget[] = {
    "DataqSdkChannelConfWidget\0\0unit\0"
    "updateUnits(QString)\0value\0"
    "updateColumnName(QString)\0"
    "updateMeasuredLower(QString)\0"
    "updateMeasuredUpper(QString)\0"
    "updateMappedLower(QString)\0"
    "updateMappedUpper(QString)\0closed\0"
    "updateClosedInterval(bool)\0enabled\0"
    "updateSmoothingEnabled(bool)\0"
    "updateSensitivity(QString)\0"
    "startCalibration()\0stopCalibration()\0"
    "resetCalibration()\0measure\0"
    "updateInput(Measurement)\0"
    "updateOutput(Measurement)\0hidden\0"
    "updateHidden(bool)\0model,index\0"
    "DataqSdkChannelConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void DataqSdkChannelConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { DataqSdkChannelConfWidget *_r = new DataqSdkChannelConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataqSdkChannelConfWidget *_t = static_cast<DataqSdkChannelConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateUnits((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateColumnName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateMeasuredLower((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateMeasuredUpper((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateMappedLower((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateMappedUpper((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updateClosedInterval((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->updateSmoothingEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->updateSensitivity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->startCalibration(); break;
        case 10: _t->stopCalibration(); break;
        case 11: _t->resetCalibration(); break;
        case 12: _t->updateInput((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 13: _t->updateOutput((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 14: _t->updateHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataqSdkChannelConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataqSdkChannelConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_DataqSdkChannelConfWidget,
      qt_meta_data_DataqSdkChannelConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataqSdkChannelConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataqSdkChannelConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataqSdkChannelConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataqSdkChannelConfWidget))
        return static_cast<void*>(const_cast< DataqSdkChannelConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int DataqSdkChannelConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
static const uint qt_meta_data_SerialScaleConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   49, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   23,   22,   22, 0x08,
      56,   51,   22,   22, 0x08,
      86,   80,   22,   22, 0x08,
     104,   80,   22,   22, 0x08,
     127,   80,   22,   22, 0x08,
     155,  147,   22,   22, 0x08,
     194,  183,   22,   22, 0x08,

 // constructors: signature, parameters, type, tag, flags
     239,  227,   22,   22, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_SerialScaleConfWidget[] = {
    "SerialScaleConfWidget\0\0newPort\0"
    "updatePort(QString)\0rate\0"
    "updateBaudRate(QString)\0index\0"
    "updateParity(int)\0updateFlowControl(int)\0"
    "updateStopBits(int)\0command\0"
    "updateWeighCommand(QString)\0terminator\0"
    "updateCommandTerminator(QString)\0"
    "model,index\0"
    "SerialScaleConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void SerialScaleConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { SerialScaleConfWidget *_r = new SerialScaleConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialScaleConfWidget *_t = static_cast<SerialScaleConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updatePort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateBaudRate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateParity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateFlowControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateStopBits((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateWeighCommand((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updateCommandTerminator((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialScaleConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialScaleConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_SerialScaleConfWidget,
      qt_meta_data_SerialScaleConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialScaleConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialScaleConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialScaleConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialScaleConfWidget))
        return static_cast<void*>(const_cast< SerialScaleConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int SerialScaleConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_ValueAnnotationConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   29, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   27,   26,   26, 0x08,
      62,   26,   26,   26, 0x08,
      94,   82,   26,   26, 0x08,

 // constructors: signature, parameters, type, tag, flags
     124,  112,   26,   26, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ValueAnnotationConfWidget[] = {
    "ValueAnnotationConfWidget\0\0source\0"
    "updateSourceColumn(QString)\0"
    "updateAnnotations()\0noteOnStart\0"
    "updateStart(bool)\0model,index\0"
    "ValueAnnotationConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ValueAnnotationConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ValueAnnotationConfWidget *_r = new ValueAnnotationConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ValueAnnotationConfWidget *_t = static_cast<ValueAnnotationConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateSourceColumn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateAnnotations(); break;
        case 2: _t->updateStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ValueAnnotationConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ValueAnnotationConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ValueAnnotationConfWidget,
      qt_meta_data_ValueAnnotationConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ValueAnnotationConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ValueAnnotationConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ValueAnnotationConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ValueAnnotationConfWidget))
        return static_cast<void*>(const_cast< ValueAnnotationConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ValueAnnotationConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_ValueAnnotation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      50,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,   78,   16,   16, 0x0a,
     114,   16,   16,   16, 0x0a,
     132,  125,   16,   16, 0x0a,
     157,  125,   16,   16, 0x0a,
     191,  183,   16,   16, 0x0a,

 // methods: signature, parameters, type, tag, flags
     229,  212,   16,   16, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ValueAnnotation[] = {
    "ValueAnnotation\0\0annotation,tempcolumn,notecolumn\0"
    "annotation(QString,int,int)\0measure\0"
    "newMeasurement(Measurement)\0annotate()\0"
    "column\0setAnnotationColumn(int)\0"
    "setTemperatureColumn(int)\0epsilon\0"
    "setTolerance(double)\0value,annotation\0"
    "setAnnotation(double,QString)\0"
};

void ValueAnnotation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ValueAnnotation *_t = static_cast<ValueAnnotation *>(_o);
        switch (_id) {
        case 0: _t->annotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->newMeasurement((*reinterpret_cast< Measurement(*)>(_a[1]))); break;
        case 2: _t->annotate(); break;
        case 3: _t->setAnnotationColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setTemperatureColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setTolerance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setAnnotation((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ValueAnnotation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ValueAnnotation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ValueAnnotation,
      qt_meta_data_ValueAnnotation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ValueAnnotation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ValueAnnotation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ValueAnnotation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ValueAnnotation))
        return static_cast<void*>(const_cast< ValueAnnotation*>(this));
    return QObject::qt_metacast(_clname);
}

int ValueAnnotation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ValueAnnotation::annotation(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ThresholdAnnotationConfWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   34, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      38,   31,   30,   30, 0x08,
      72,   66,   30,   30, 0x08,
     102,   96,   30,   30, 0x08,
     128,  123,   30,   30, 0x08,

 // constructors: signature, parameters, type, tag, flags
     166,  154,   30,   30, 0x0e,

       0        // eod
};

static const char qt_meta_stringdata_ThresholdAnnotationConfWidget[] = {
    "ThresholdAnnotationConfWidget\0\0source\0"
    "updateSourceColumn(QString)\0value\0"
    "updateThreshold(double)\0index\0"
    "updateDirection(int)\0note\0"
    "updateAnnotation(QString)\0model,index\0"
    "ThresholdAnnotationConfWidget(DeviceTreeModel*,QModelIndex)\0"
};

void ThresholdAnnotationConfWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ThresholdAnnotationConfWidget *_r = new ThresholdAnnotationConfWidget((*reinterpret_cast< DeviceTreeModel*(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ThresholdAnnotationConfWidget *_t = static_cast<ThresholdAnnotationConfWidget *>(_o);
        switch (_id) {
        case 0: _t->updateSourceColumn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->updateDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateAnnotation((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ThresholdAnnotationConfWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ThresholdAnnotationConfWidget::staticMetaObject = {
    { &BasicDeviceConfigurationWidget::staticMetaObject, qt_meta_stringdata_ThresholdAnnotationConfWidget,
      qt_meta_data_ThresholdAnnotationConfWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ThresholdAnnotationConfWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ThresholdAnnotationConfWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ThresholdAnnotationConfWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThresholdAnnotationConfWidget))
        return static_cast<void*>(const_cast< ThresholdAnnotationConfWidget*>(this));
    return BasicDeviceConfigurationWidget::qt_metacast(_clname);
}

int ThresholdAnnotationConfWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicDeviceConfigurationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_Annotator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      44,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   72,   10,   10, 0x0a,
     117,  106,   10,   10, 0x0a,
     160,  143,   10,   10, 0x0a,
     185,   10,   10,   10, 0x0a,
     196,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Annotator[] = {
    "Annotator\0\0annotation,tempcolumn,notecolumn\0"
    "annotation(QString,int,int)\0annotation\0"
    "setAnnotation(QString)\0tempcolumn\0"
    "setTemperatureColumn(int)\0annotationcolumn\0"
    "setAnnotationColumn(int)\0annotate()\0"
    "catchTimer()\0"
};

void Annotator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Annotator *_t = static_cast<Annotator *>(_o);
        switch (_id) {
        case 0: _t->annotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->setAnnotation((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setTemperatureColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setAnnotationColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->annotate(); break;
        case 5: _t->catchTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Annotator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Annotator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Annotator,
      qt_meta_data_Annotator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Annotator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Annotator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Annotator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Annotator))
        return static_cast<void*>(const_cast< Annotator*>(this));
    return QObject::qt_metacast(_clname);
}

int Annotator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Annotator::annotation(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_LoginDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoginDialog[] = {
    "LoginDialog\0\0attemptLogin()\0"
};

void LoginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginDialog *_t = static_cast<LoginDialog *>(_o);
        switch (_id) {
        case 0: _t->attemptLogin(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LoginDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoginDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoginDialog,
      qt_meta_data_LoginDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginDialog))
        return static_cast<void*>(const_cast< LoginDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_UserLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserLabel[] = {
    "UserLabel\0\0user\0updateLabel(QString)\0"
};

void UserLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UserLabel *_t = static_cast<UserLabel *>(_o);
        switch (_id) {
        case 0: _t->updateLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UserLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UserLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_UserLabel,
      qt_meta_data_UserLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UserLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UserLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UserLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserLabel))
        return static_cast<void*>(const_cast< UserLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int UserLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_NewTypicaUser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      32,   14,   14,   14, 0x0a,
      49,   14,   14,   14, 0x0a,
      60,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewTypicaUser[] = {
    "NewTypicaUser\0\0createAndReset()\0"
    "createAndClose()\0validate()\0"
    "cancelValidate()\0"
};

void NewTypicaUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewTypicaUser *_t = static_cast<NewTypicaUser *>(_o);
        switch (_id) {
        case 0: _t->createAndReset(); break;
        case 1: _t->createAndClose(); break;
        case 2: _t->validate(); break;
        case 3: _t->cancelValidate(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NewTypicaUser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewTypicaUser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewTypicaUser,
      qt_meta_data_NewTypicaUser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewTypicaUser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewTypicaUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewTypicaUser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewTypicaUser))
        return static_cast<void*>(const_cast< NewTypicaUser*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewTypicaUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
