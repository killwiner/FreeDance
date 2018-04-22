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
    QByteArrayData data[15];
    char stringdata0[234];
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
QT_MOC_LITERAL(3, 53, 12), // "testFiltrage"
QT_MOC_LITERAL(4, 66, 17), // "test_Erode_Dilate"
QT_MOC_LITERAL(5, 84, 9), // "test_Blur"
QT_MOC_LITERAL(6, 94, 7), // "contour"
QT_MOC_LITERAL(7, 102, 19), // "testGetP_cannyImage"
QT_MOC_LITERAL(8, 122, 14), // "testFollowPath"
QT_MOC_LITERAL(9, 137, 19), // "testStartFollowPath"
QT_MOC_LITERAL(10, 157, 11), // "testTangent"
QT_MOC_LITERAL(11, 169, 21), // "testNormalizedVectors"
QT_MOC_LITERAL(12, 191, 15), // "testShowNormals"
QT_MOC_LITERAL(13, 207, 12), // "testCutImage"
QT_MOC_LITERAL(14, 220, 13) // "testKinectImg"

    },
    "armature::TestsHumanShape\0"
    "affichage_image_a_traiter\0\0testFiltrage\0"
    "test_Erode_Dilate\0test_Blur\0contour\0"
    "testGetP_cannyImage\0testFollowPath\0"
    "testStartFollowPath\0testTangent\0"
    "testNormalizedVectors\0testShowNormals\0"
    "testCutImage\0testKinectImg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_armature__TestsHumanShape[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

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
        case 1: _t->testFiltrage(); break;
        case 2: _t->test_Erode_Dilate(); break;
        case 3: _t->test_Blur(); break;
        case 4: _t->contour(); break;
        case 5: _t->testGetP_cannyImage(); break;
        case 6: _t->testFollowPath(); break;
        case 7: _t->testStartFollowPath(); break;
        case 8: _t->testTangent(); break;
        case 9: _t->testNormalizedVectors(); break;
        case 10: _t->testShowNormals(); break;
        case 11: _t->testCutImage(); break;
        case 12: _t->testKinectImg(); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
