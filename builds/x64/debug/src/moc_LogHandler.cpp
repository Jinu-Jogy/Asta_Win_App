/****************************************************************************
** Meta object code from reading C++ file 'LogHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Logger/Handler/LogHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LogHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_logging__handler__LogHandler_t {
    QByteArrayData data[7];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_logging__handler__LogHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_logging__handler__LogHandler_t qt_meta_stringdata_logging__handler__LogHandler = {
    {
QT_MOC_LITERAL(0, 0, 28), // "logging::handler::LogHandler"
QT_MOC_LITERAL(1, 29, 10), // "publish_TS"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 18), // "logging::LogRecord"
QT_MOC_LITERAL(4, 60, 6), // "record"
QT_MOC_LITERAL(5, 67, 7), // "publish"
QT_MOC_LITERAL(6, 75, 7) // "message"

    },
    "logging::handler::LogHandler\0publish_TS\0"
    "\0logging::LogRecord\0record\0publish\0"
    "message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_logging__handler__LogHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,
       1,    1,   40,    2, 0x09 /* Protected */,
       5,    1,   43,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QStringList,    6,
    QMetaType::Void, QMetaType::QStringList,    6,

       0        // eod
};

void logging::handler::LogHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LogHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->publish_TS((*reinterpret_cast< const logging::LogRecord(*)>(_a[1]))); break;
        case 1: _t->publish((*reinterpret_cast< const logging::LogRecord(*)>(_a[1]))); break;
        case 2: _t->publish_TS((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 3: _t->publish((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< logging::LogRecord >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< logging::LogRecord >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject logging::handler::LogHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_logging__handler__LogHandler.data,
    qt_meta_data_logging__handler__LogHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *logging::handler::LogHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *logging::handler::LogHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_logging__handler__LogHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int logging::handler::LogHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
