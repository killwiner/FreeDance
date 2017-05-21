/****************************************************************************
** Meta object code from reading C++ file 'testsHumanShape.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/armature/testsHumanShape.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsHumanShape.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_armature__TestsHumanShape_t {
    QByteArrayData data[12];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_armature__TestsHumanShape_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_armature__TestsHumanShape_t qt_meta_stringdata_armature__TestsHumanShape = {
    {
QT_MOC_LITERAL(0, 0, 25), // "armature::TestsHumanShape"
QT_MOC_LITERAL(1, 26, 25), // "affichage_image_a_traiter"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 12), // "pixelOutTest"
QT_MOC_LITERAL(4, 66, 23), // "affichage_image_filtree"
QT_MOC_LITERAL(5, 90, 10), // "linkIdTest"
QT_MOC_LITERAL(6, 101, 12), // "changeIdTest"
QT_MOC_LITERAL(7, 114, 21), // "searchAroundPixelTest"
QT_MOC_LITERAL(8, 136, 14), // "connectIdsTest"
QT_MOC_LITERAL(9, 151, 16), // "affichage_objets"
QT_MOC_LITERAL(10, 168, 16), // "largestPartition"
QT_MOC_LITERAL(11, 185, 26) // "erazePixelsSmallPartitions"

    },
    "armature::TestsHumanShape\0"
    "affichage_image_a_traiter\0\0pixelOutTest\0"
    "affichage_image_filtree\0linkIdTest\0"
    "changeIdTest\0searchAroundPixelTest\0"
    "connectIdsTest\0affichage_objets\0"
    "largestPartition\0erazePixelsSmallPartitions"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_armature__TestsHumanShape[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void armature::TestsHumanShape::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsHumanShape *_t = static_cast<TestsHumanShape *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->affichage_image_a_traiter(); break;
        case 1: _t->pixelOutTest(); break;
        case 2: _t->affichage_image_filtree(); break;
        case 3: _t->linkIdTest(); break;
        case 4: _t->changeIdTest(); break;
        case 5: _t->searchAroundPixelTest(); break;
        case 6: _t->connectIdsTest(); break;
        case 7: _t->affichage_objets(); break;
        case 8: _t->largestPartition(); break;
        case 9: _t->erazePixelsSmallPartitions(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject armature::TestsHumanShape::staticMetaObject = {
    { &QTestSuite::staticMetaObject, qt_meta_stringdata_armature__TestsHumanShape.data,
      qt_meta_data_armature__TestsHumanShape,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *armature::TestsHumanShape::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *armature::TestsHumanShape::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_armature__TestsHumanShape.stringdata0))
        return static_cast<void*>(const_cast< TestsHumanShape*>(this));
    return QTestSuite::qt_metacast(_clname);
}

int armature::TestsHumanShape::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTestSuite::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
