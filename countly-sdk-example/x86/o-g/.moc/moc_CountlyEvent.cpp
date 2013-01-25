/****************************************************************************
** Meta object code from reading C++ file 'CountlyEvent.hpp'
**
** Created: Fri Jan 25 19:51:25 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/CountlyEvent.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CountlyEvent.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_countly__CountlyEvent[] = {

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

 // methods: signature, parameters, type, tag, flags
      27,   23,   22,   22, 0x02,
      49,   43,   22,   22, 0x02,
      63,   43,   22,   22, 0x02,
      86,   82,   22,   22, 0x02,
     101,   82,   22,   22, 0x02,
     128,  118,   22,   22, 0x02,
     150,   22,   22,   22, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_countly__CountlyEvent[] = {
    "countly::CountlyEvent\0\0key\0setKey(QString)\0"
    "count\0setCount(int)\0setCount(QVariant)\0"
    "sum\0setSum(double)\0setSum(QVariant)\0"
    "key,value\0set(QString,QVariant)\0send()\0"
};

void countly::CountlyEvent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountlyEvent *_t = static_cast<CountlyEvent *>(_o);
        switch (_id) {
        case 0: _t->setKey((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setCount((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 3: _t->setSum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setSum((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 5: _t->set((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 6: _t->send(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData countly::CountlyEvent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject countly::CountlyEvent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_countly__CountlyEvent,
      qt_meta_data_countly__CountlyEvent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &countly::CountlyEvent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *countly::CountlyEvent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *countly::CountlyEvent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_countly__CountlyEvent))
        return static_cast<void*>(const_cast< CountlyEvent*>(this));
    return QObject::qt_metacast(_clname);
}

int countly::CountlyEvent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
