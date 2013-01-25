/****************************************************************************
** Meta object code from reading C++ file 'Countly.hpp'
**
** Created: Fri Jan 25 19:51:23 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Countly.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Countly.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_countly__Countly[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      30,   17,   17,   17, 0x0a,
      43,   17,   17,   17, 0x0a,
      55,   17,   17,   17, 0x0a,
      64,   17,   17,   17, 0x0a,
      72,   17,   17,   17, 0x0a,
      86,   17,   17,   17, 0x0a,
     112,   99,   17,   17, 0x0a,
     156,   17,   17,   17, 0x0a,
     172,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_countly__Countly[] = {
    "countly::Countly\0\0thumbnail()\0"
    "fullscreen()\0invisible()\0asleep()\0"
    "awake()\0aboutToQuit()\0manualExit()\0"
    "processState\0processStateChanged(bb::ProcessState::Type)\0"
    "unixSignal(int)\0timerTimeout()\0"
};

void countly::Countly::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Countly *_t = static_cast<Countly *>(_o);
        switch (_id) {
        case 0: _t->thumbnail(); break;
        case 1: _t->fullscreen(); break;
        case 2: _t->invisible(); break;
        case 3: _t->asleep(); break;
        case 4: _t->awake(); break;
        case 5: _t->aboutToQuit(); break;
        case 6: _t->manualExit(); break;
        case 7: _t->processStateChanged((*reinterpret_cast< bb::ProcessState::Type(*)>(_a[1]))); break;
        case 8: _t->unixSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->timerTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData countly::Countly::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject countly::Countly::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_countly__Countly,
      qt_meta_data_countly__Countly, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &countly::Countly::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *countly::Countly::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *countly::Countly::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_countly__Countly))
        return static_cast<void*>(const_cast< Countly*>(this));
    return QObject::qt_metacast(_clname);
}

int countly::Countly::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
