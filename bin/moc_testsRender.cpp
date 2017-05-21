/****************************************************************************
** Meta object code from reading C++ file 'testsRender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/rendering/testsRender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsRender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_rendering__TestsRender_t {
    QByteArrayData data[8];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rendering__TestsRender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rendering__TestsRender_t qt_meta_stringdata_rendering__TestsRender = {
    {
QT_MOC_LITERAL(0, 0, 22), // "rendering::TestsRender"
QT_MOC_LITERAL(1, 23, 15), // "affiche_fenetre"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 14), // "fenetre_active"
QT_MOC_LITERAL(4, 55, 5), // "timer"
QT_MOC_LITERAL(5, 61, 24), // "generation_d_un_triangle"
QT_MOC_LITERAL(6, 86, 21), // "affichage_d_une_image"
QT_MOC_LITERAL(7, 108, 21) // "affichage_d_une_video"

    },
    "rendering::TestsRender\0affiche_fenetre\0"
    "\0fenetre_active\0timer\0generation_d_un_triangle\0"
    "affichage_d_une_image\0affichage_d_une_video"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rendering__TestsRender[] = {

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

void rendering::TestsRender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestsRender *_t = static_cast<TestsRender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->affiche_fenetre(); break;
        case 1: _t->fenetre_active(); break;
        case 2: _t->timer(); break;
        case 3: _t->generation_d_un_triangle(); break;
        case 4: _t->affichage_d_une_image(); break;
        case 5: _t->affichage_d_une_video(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject rendering::TestsRender::staticMetaObject = {
    { &QTestSuite::staticMetaObject, qt_meta_stringdata_rendering__TestsRender.data,
      qt_meta_data_rendering__TestsRender,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *rendering::TestsRender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rendering::TestsRender::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_rendering__TestsRender.stringdata0))
        return static_cast<void*>(const_cast< TestsRender*>(this));
    return QTestSuite::qt_metacast(_clname);
}

int rendering::TestsRender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
