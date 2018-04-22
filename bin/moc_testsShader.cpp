/****************************************************************************
** Meta object code from reading C++ file 'testsShader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/shader/testsShader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsShader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_shader__TestsShader_t {
    QByteArrayData data[12];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_shader__TestsShader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_shader__TestsShader_t qt_meta_stringdata_shader__TestsShader = {
    {
QT_MOC_LITERAL(0, 0, 19), // "shader::TestsShader"
QT_MOC_LITERAL(1, 20, 16), // "testLoadFileFail"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 18), // "testLoadFileSucces"
QT_MOC_LITERAL(4, 57, 13), // "testBuildFail"
QT_MOC_LITERAL(5, 71, 15), // "testBuildSucces"
QT_MOC_LITERAL(6, 87, 20), // "testControlBuildFail"
QT_MOC_LITERAL(7, 108, 22), // "testControlBuildSucces"
QT_MOC_LITERAL(8, 131, 19), // "testControlLinkFail"
QT_MOC_LITERAL(9, 151, 21), // "testControlLinkSucces"
QT_MOC_LITERAL(10, 173, 13), // "testAffichage"
QT_MOC_LITERAL(11, 187, 13) // "testTutorials"

    },
    "shader::TestsShader\0testLoadFileFail\0"
    "\0testLoadFileSucces\0testBuildFail\0"
    "testBuildSucces\0testControlBuildFail\0"
    "testControlBuildSucces\0testControlLinkFail\0"
    "testControlLinkSucces\0testAffichage\0"
    "testTutorials"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_shader__TestsShader[] = {

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

void shader::TestsShader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsShader *_t = static_cast<TestsShader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testLoadFileFail(); break;
        case 1: _t->testLoadFileSucces(); break;
        case 2: _t->testBuildFail(); break;
        case 3: _t->testBuildSucces(); break;
        case 4: _t->testControlBuildFail(); break;
        case 5: _t->testControlBuildSucces(); break;
        case 6: _t->testControlLinkFail(); break;
        case 7: _t->testControlLinkSucces(); break;
        case 8: _t->testAffichage(); break;
        case 9: _t->testTutorials(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject shader::TestsShader::staticMetaObject = {
    { &QTestSuite::staticMetaObject, qt_meta_stringdata_shader__TestsShader.data,
      qt_meta_data_shader__TestsShader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *shader::TestsShader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *shader::TestsShader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_shader__TestsShader.stringdata0))
        return static_cast<void*>(const_cast< TestsShader*>(this));
    return QTestSuite::qt_metacast(_clname);
}

int shader::TestsShader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
