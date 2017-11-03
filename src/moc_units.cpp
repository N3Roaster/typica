/****************************************************************************
** Meta object code from reading C++ file 'units.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "units.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'units.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Units[] = {

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
       6, 0x0,    9,   18,

 // enum data: key, value
      11, uint(Units::Unitless),
      20, uint(Units::Fahrenheit),
      31, uint(Units::Celsius),
      39, uint(Units::Kelvin),
      46, uint(Units::Rankine),
      54, uint(Units::Pound),
      60, uint(Units::Kilogram),
      69, uint(Units::Ounce),
      75, uint(Units::Gram),

       0        // eod
};

static const char qt_meta_stringdata_Units[] = {
    "Units\0Unit\0Unitless\0Fahrenheit\0Celsius\0"
    "Kelvin\0Rankine\0Pound\0Kilogram\0Ounce\0"
    "Gram\0"
};

void Units::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Units::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Units::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Units,
      qt_meta_data_Units, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Units::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Units::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Units::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Units))
        return static_cast<void*>(const_cast< Units*>(this));
    return QObject::qt_metacast(_clname);
}

int Units::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
