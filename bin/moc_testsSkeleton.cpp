/****************************************************************************
** Meta object code from reading C++ file 'testsSkeleton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/armature/testsSkeleton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsSkeleton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_armature__TestsSkeleton_t {
    QByteArrayData data[6];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_armature__TestsSkeleton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_armature__TestsSkeleton_t qt_meta_stringdata_armature__TestsSkeleton = {
    {
QT_MOC_LITERAL(0, 0, 23), // "armature::TestsSkeleton"
QT_MOC_LITERAL(1, 24, 14), // "testSearchTips"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 14), // "testCenterTips"
QT_MOC_LITERAL(4, 55, 14), // "testLocateTips"
QT_MOC_LITERAL(5, 70, 8) // "showTips"

    },
    "armature::TestsSkeleton\0testSearchTips\0"
    "\0testCenterTips\0testLocateTips\0showTips"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_armature__TestsSkeleton[] = {

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

void armature::TestsSkeleton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsSkeleton *_t = static_cast<TestsSkeleton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testSearchTips(); break;
        case 1: _t->testCenterTips(); break;
        case 2: _t->testLocateTips(); break;
        case 3: _t->showTips(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject armature::TestsSkeleton::staticMetaObject = {
    { &QTestSuite::staticMetaObject, qt_meta_stringdata_armature__TestsSkeleton.data,
      qt_meta_data_armature__TestsSkeleton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *armature::TestsSkeleton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *armature::TestsSkeleton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_armature__TestsSkeleton.stringdata0))
        return static_cast<void*>(const_cast< TestsSkeleton*>(this));
    return QTestSuite::qt_metacast(_clname);
}

int armature::TestsSkeleton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
