/****************************************************************************
** Meta object code from reading C++ file 'CountlyQueue.hpp'
**
** Created: Fri Jan 25 19:51:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/CountlyQueue.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CountlyQueue.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_countly__CountlyQueue[] = {

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
      23,   22,   22,   22, 0x0a,
      54,   22,   22,   22, 0x0a,
     111,   92,   22,   22, 0x0a,
     166,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_countly__CountlyQueue[] = {
    "countly::CountlyQueue\0\0"
    "processorNetworkInaccessible()\0"
    "processorDelivered(CountlyQueuedUrl*)\0"
    ",willRetry,message\0"
    "processorDeliveryError(CountlyQueuedUrl*,bool,QString)\0"
    "processorFlushCompleted()\0"
};

void countly::CountlyQueue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountlyQueue *_t = static_cast<CountlyQueue *>(_o);
        switch (_id) {
        case 0: _t->processorNetworkInaccessible(); break;
        case 1: _t->processorDelivered((*reinterpret_cast< CountlyQueuedUrl*(*)>(_a[1]))); break;
        case 2: _t->processorDeliveryError((*reinterpret_cast< CountlyQueuedUrl*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 3: _t->processorFlushCompleted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData countly::CountlyQueue::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject countly::CountlyQueue::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_countly__CountlyQueue,
      qt_meta_data_countly__CountlyQueue, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &countly::CountlyQueue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *countly::CountlyQueue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *countly::CountlyQueue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_countly__CountlyQueue))
        return static_cast<void*>(const_cast< CountlyQueue*>(this));
    return QObject::qt_metacast(_clname);
}

int countly::CountlyQueue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
