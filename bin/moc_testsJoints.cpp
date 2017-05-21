/****************************************************************************
** Meta object code from reading C++ file 'testsJoints.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/armature/testsJoints.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsJoints.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_armature__TestsJoints_t {
    QByteArrayData data[8];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_armature__TestsJoints_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_armature__TestsJoints_t qt_meta_stringdata_armature__TestsJoints = {
    {
QT_MOC_LITERAL(0, 0, 21), // "armature::TestsJoints"
QT_MOC_LITERAL(1, 22, 7), // "contour"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 19), // "testGetP_cannyImage"
QT_MOC_LITERAL(4, 51, 17), // "testGetP_idObject"
QT_MOC_LITERAL(5, 69, 14), // "testFollowPath"
QT_MOC_LITERAL(6, 84, 19), // "testStartFollowPath"
QT_MOC_LITERAL(7, 104, 13) // "testTangeante"

    },
    "armature::TestsJoints\0contour\0\0"
    "testGetP_cannyImage\0testGetP_idObject\0"
    "testFollowPath\0testStartFollowPath\0"
    "testTangeante"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_armature__TestsJoints[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void armature::TestsJoints::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsJoints *_t = static_cast<TestsJoints *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->contour(); break;
        case 1: _t->testGetP_cannyImage(); break;
        case 2: _t->testGetP_idObject(); break;
        case 3: _t->testFollowPath(); break;
        case 4: _t->testStartFollowPath(); break;
        case 5: _t->testTangeante(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject armature::TestsJoints::staticMetaObject = {
    { &QTestSuite::staticMetaObject, qt_meta_stringdata_armature__TestsJoints.data,
      qt_meta_data_armature__TestsJoints,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *armature::TestsJoints::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *armature::TestsJoints::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_armature__TestsJoints.stringdata0))
        return static_cast<void*>(const_cast< TestsJoints*>(this));
    return QTestSuite::qt_metacast(_clname);
}

int armature::TestsJoints::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTestSuite::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
