/****************************************************************************
** Meta object code from reading C++ file 'feedback.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "feedback.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'feedback.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FeedbackWizard[] = {

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
      22,   16,   15,   15, 0x08,
      50,   15,   15,   15, 0x08,
      70,   15,   15,   15, 0x08,
      91,   15,   15,   15, 0x08,
     107,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FeedbackWizard[] = {
    "FeedbackWizard\0\0index\0setCommentInstructions(int)\0"
    "updateMessageText()\0printButtonPressed()\0"
    "printAccepted()\0copyButtonPressed()\0"
};

void FeedbackWizard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FeedbackWizard *_t = static_cast<FeedbackWizard *>(_o);
        switch (_id) {
        case 0: _t->setCommentInstructions((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateMessageText(); break;
        case 2: _t->printButtonPressed(); break;
        case 3: _t->printAccepted(); break;
        case 4: _t->copyButtonPressed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FeedbackWizard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FeedbackWizard::staticMetaObject = {
    { &QWizard::staticMetaObject, qt_meta_stringdata_FeedbackWizard,
      qt_meta_data_FeedbackWizard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FeedbackWizard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FeedbackWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FeedbackWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FeedbackWizard))
        return static_cast<void*>(const_cast< FeedbackWizard*>(this));
    return QWizard::qt_metacast(_clname);
}

int FeedbackWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
