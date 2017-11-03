/****************************************************************************
** Meta object code from reading C++ file 'daterangeselector.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "daterangeselector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'daterangeselector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomDateRangePopup[] = {

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
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   21,   21,   21, 0x0a,
      49,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CustomDateRangePopup[] = {
    "CustomDateRangePopup\0\0hidingPopup()\0"
    "applyRange()\0validateRange()\0"
};

void CustomDateRangePopup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CustomDateRangePopup *_t = static_cast<CustomDateRangePopup *>(_o);
        switch (_id) {
        case 0: _t->hidingPopup(); break;
        case 1: _t->applyRange(); break;
        case 2: _t->validateRange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CustomDateRangePopup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CustomDateRangePopup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CustomDateRangePopup,
      qt_meta_data_CustomDateRangePopup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomDateRangePopup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomDateRangePopup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomDateRangePopup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomDateRangePopup))
        return static_cast<void*>(const_cast< CustomDateRangePopup*>(this));
    return QWidget::qt_metacast(_clname);
}

int CustomDateRangePopup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void CustomDateRangePopup::hidingPopup()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_DateRangeSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       1,   54, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   42,   18,   18, 0x0a,
      87,   69,   18,   18, 0x0a,
     121,   42,   18,   18, 0x0a,
     138,   18,   18,   18, 0x08,
     153,   18,   18,   18, 0x08,
     167,   42,   18,   18, 0x08,

 // methods: signature, parameters, type, tag, flags
     193,   18,  184,   18, 0x02,

 // properties: name, type, flags
     212,  208, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_DateRangeSelector[] = {
    "DateRangeSelector\0\0rangeUpdated(QVariant)\0"
    "index\0setCurrentIndex(int)\0startDate,endDate\0"
    "setLifetimeRange(QString,QString)\0"
    "removeIndex(int)\0toggleCustom()\0"
    "popupHidden()\0updateRange(int)\0QVariant\0"
    "currentRange()\0int\0currentIndex\0"
};

void DateRangeSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DateRangeSelector *_t = static_cast<DateRangeSelector *>(_o);
        switch (_id) {
        case 0: _t->rangeUpdated((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setLifetimeRange((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->removeIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->toggleCustom(); break;
        case 5: _t->popupHidden(); break;
        case 6: _t->updateRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { QVariant _r = _t->currentRange();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DateRangeSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DateRangeSelector::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DateRangeSelector,
      qt_meta_data_DateRangeSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DateRangeSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DateRangeSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DateRangeSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DateRangeSelector))
        return static_cast<void*>(const_cast< DateRangeSelector*>(this));
    return QWidget::qt_metacast(_clname);
}

int DateRangeSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = currentIndex(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setCurrentIndex(*reinterpret_cast< int*>(_v)); break;
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
void DateRangeSelector::rangeUpdated(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
