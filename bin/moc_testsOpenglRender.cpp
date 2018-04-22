/****************************************************************************
** Meta object code from reading C++ file 'testsOpenglRender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/rendering/testsOpenglRender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsOpenglRender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_rendering__TestsOpenglR_t {
    QByteArrayData data[5];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rendering__TestsOpenglR_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rendering__TestsOpenglR_t qt_meta_stringdata_rendering__TestsOpenglR = {
    {
QT_MOC_LITERAL(0, 0, 23), // "rendering::TestsOpenglR"
QT_MOC_LITERAL(1, 24, 12), // "test_timeout"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 12), // "KinectSignal"
QT_MOC_LITERAL(4, 51, 9) // "next_step"

    },
    "rendering::TestsOpenglR\0test_timeout\0"
    "\0KinectSignal\0next_step"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rendering__TestsOpenglR[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void rendering::TestsOpenglR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsOpenglR *_t = static_cast<TestsOpenglR *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->test_timeout(); break;
        case 1: _t->KinectSignal(); break;
        case 2: _t->next_step(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TestsOpenglR::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TestsOpenglR::test_timeout)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TestsOpenglR::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TestsOpenglR::KinectSignal)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject rendering::TestsOpenglR::staticMetaObject = {
    { &Render::staticMetaObject, qt_meta_stringdata_rendering__TestsOpenglR.data,
      qt_meta_data_rendering__TestsOpenglR,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *rendering::TestsOpenglR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rendering::TestsOpenglR::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_rendering__TestsOpenglR.stringdata0))
        return static_cast<void*>(const_cast< TestsOpenglR*>(this));
    return Render::qt_metacast(_clname);
}

int rendering::TestsOpenglR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Render::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void rendering::TestsOpenglR::test_timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void rendering::TestsOpenglR::KinectSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
