/****************************************************************************
** Meta object code from reading C++ file 'CountlyQueueProcessor.hpp'
**
** Created: Fri Jan 25 19:51:28 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/CountlyQueueProcessor.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CountlyQueueProcessor.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_countly__CountlyQueueProcessor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x05,
      54,   31,   31,   31, 0x05,
     102,   83,   31,   31, 0x05,
     148,   31,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
     171,  165,   31,   31, 0x0a,
     208,  203,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_countly__CountlyQueueProcessor[] = {
    "countly::CountlyQueueProcessor\0\0"
    "networkInaccessible()\0"
    "delivered(CountlyQueuedUrl*)\0"
    ",willRetry,message\0"
    "deliveryError(CountlyQueuedUrl*,bool,QString)\0"
    "flushCompleted()\0reply\0"
    "requestFinished(QNetworkReply*)\0code\0"
    "requestError(QNetworkReply::NetworkError)\0"
};

void countly::CountlyQueueProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountlyQueueProcessor *_t = static_cast<CountlyQueueProcessor *>(_o);
        switch (_id) {
        case 0: _t->networkInaccessible(); break;
        case 1: _t->delivered((*reinterpret_cast< CountlyQueuedUrl*(*)>(_a[1]))); break;
        case 2: _t->deliveryError((*reinterpret_cast< CountlyQueuedUrl*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 3: _t->flushCompleted(); break;
        case 4: _t->requestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->requestError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData countly::CountlyQueueProcessor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject countly::CountlyQueueProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_countly__CountlyQueueProcessor,
      qt_meta_data_countly__CountlyQueueProcessor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &countly::CountlyQueueProcessor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *countly::CountlyQueueProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *countly::CountlyQueueProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_countly__CountlyQueueProcessor))
        return static_cast<void*>(const_cast< CountlyQueueProcessor*>(this));
    return QObject::qt_metacast(_clname);
}

int countly::CountlyQueueProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void countly::CountlyQueueProcessor::networkInaccessible()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void countly::CountlyQueueProcessor::delivered(CountlyQueuedUrl * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void countly::CountlyQueueProcessor::deliveryError(CountlyQueuedUrl * _t1, bool _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void countly::CountlyQueueProcessor::flushCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
