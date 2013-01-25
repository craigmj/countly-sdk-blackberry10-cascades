/****************************************************************************
** Meta object code from reading C++ file 'CountlyLog.hpp'
**
** Created: Fri Jan 25 19:51:25 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/CountlyLog.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CountlyLog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_countly__CountlyLog[] = {

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

 // methods: signature, parameters, type, tag, flags
      25,   21,   20,   20, 0x02,
      40,   21,   20,   20, 0x02,
      55,   21,   20,   20, 0x02,
      69,   21,   20,   20, 0x02,
      83,   21,   20,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_countly__CountlyLog[] = {
    "countly::CountlyLog\0\0msg\0trace(QString)\0"
    "debug(QString)\0info(QString)\0warn(QString)\0"
    "severe(QString)\0"
};

void countly::CountlyLog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountlyLog *_t = static_cast<CountlyLog *>(_o);
        switch (_id) {
        case 0: _t->trace((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->debug((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->info((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->warn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->severe((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData countly::CountlyLog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject countly::CountlyLog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_countly__CountlyLog,
      qt_meta_data_countly__CountlyLog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &countly::CountlyLog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *countly::CountlyLog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *countly::CountlyLog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_countly__CountlyLog))
        return static_cast<void*>(const_cast< CountlyLog*>(this));
    return QObject::qt_metacast(_clname);
}

int countly::CountlyLog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
