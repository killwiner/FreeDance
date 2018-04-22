/****************************************************************************
** Meta object code from reading C++ file 'testscircularvector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/tools/testscircularvector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testscircularvector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tools__TestsCircularVector_t {
    QByteArrayData data[6];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tools__TestsCircularVector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tools__TestsCircularVector_t qt_meta_stringdata_tools__TestsCircularVector = {
    {
QT_MOC_LITERAL(0, 0, 26), // "tools::TestsCircularVector"
QT_MOC_LITERAL(1, 27, 12), // "testPushBack"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 6), // "testAt"
QT_MOC_LITERAL(4, 48, 10), // "testLength"
QT_MOC_LITERAL(5, 59, 7) // "testPtr"

    },
    "tools::TestsCircularVector\0testPushBack\0"
    "\0testAt\0testLength\0testPtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tools__TestsCircularVector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tools::TestsCircularVector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsCircularVector *_t = static_cast<TestsCircularVector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testPushBack(); break;
        case 1: _t->testAt(); break;
        case 2: _t->testLength(); break;
        case 3: _t->testPtr(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tools::TestsCircularVector::staticMetaObject = {
    { &QTestSuite::staticMetaObject, qt_meta_stringdata_tools__TestsCircularVector.data,
      qt_meta_data_tools__TestsCircularVector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *tools::TestsCircularVector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tools::TestsCircularVector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_tools__TestsCircularVector.stringdata0))
        return static_cast<void*>(const_cast< TestsCircularVector*>(this));
    return QTestSuite::qt_metacast(_clname);
}

int tools::TestsCircularVector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTestSuite::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
