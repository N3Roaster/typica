/****************************************************************************
** Meta object code from reading C++ file 'webelement.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "webelement.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webelement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TypicaWebElement[] = {

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

 // methods: signature, parameters, type, tag, flags
      25,   18,   17,   17, 0x02,
      47,   18,   17,   17, 0x02,
      70,   18,   17,   17, 0x02,
      93,   18,   17,   17, 0x02,
     117,   17,   17,   17, 0x02,
     138,   18,   17,   17, 0x02,
     155,   18,   17,   17, 0x02,
     176,   18,   17,   17, 0x02,
     202,  197,   17,   17, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_TypicaWebElement[] = {
    "TypicaWebElement\0\0markup\0appendInside(QString)\0"
    "appendOutside(QString)\0prependInside(QString)\0"
    "prependOutside(QString)\0removeFromDocument()\0"
    "replace(QString)\0setInnerXml(QString)\0"
    "setOuterXml(QString)\0text\0"
    "setPlainText(QString)\0"
};

void TypicaWebElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TypicaWebElement *_t = static_cast<TypicaWebElement *>(_o);
        switch (_id) {
        case 0: _t->appendInside((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->appendOutside((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->prependInside((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->prependOutside((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->removeFromDocument(); break;
        case 5: _t->replace((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setInnerXml((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setOuterXml((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setPlainText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TypicaWebElement::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TypicaWebElement::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TypicaWebElement,
      qt_meta_data_TypicaWebElement, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TypicaWebElement::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TypicaWebElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TypicaWebElement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TypicaWebElement))
        return static_cast<void*>(const_cast< TypicaWebElement*>(this));
    return QObject::qt_metacast(_clname);
}

int TypicaWebElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
