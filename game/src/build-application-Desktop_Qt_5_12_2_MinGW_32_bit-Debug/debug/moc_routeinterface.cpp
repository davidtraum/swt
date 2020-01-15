/****************************************************************************
** Meta object code from reading C++ file 'routeinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../application_server/routeinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'routeinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RouteInterface_t {
    QByteArrayData data[9];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RouteInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RouteInterface_t qt_meta_stringdata_RouteInterface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RouteInterface"
QT_MOC_LITERAL(1, 15, 16), // "sendConfirmRoute"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "toggle"
QT_MOC_LITERAL(4, 40, 14), // "onTileInteract"
QT_MOC_LITERAL(5, 55, 8), // "addWagon"
QT_MOC_LITERAL(6, 64, 8), // "QString*"
QT_MOC_LITERAL(7, 73, 12), // "confirmRoute"
QT_MOC_LITERAL(8, 86, 11) // "removeWagon"

    },
    "RouteInterface\0sendConfirmRoute\0\0"
    "toggle\0onTileInteract\0addWagon\0QString*\0"
    "confirmRoute\0removeWagon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RouteInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   47,    2, 0x0a /* Public */,
       4,    3,   48,    2, 0x0a /* Public */,
       5,    1,   55,    2, 0x0a /* Public */,
       7,    0,   58,    2, 0x0a /* Public */,
       8,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RouteInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RouteInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendConfirmRoute((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->toggle(); break;
        case 2: _t->onTileInteract((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->addWagon((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 4: _t->confirmRoute(); break;
        case 5: _t->removeWagon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RouteInterface::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteInterface::sendConfirmRoute)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RouteInterface::staticMetaObject = { {
    &QDockWidget::staticMetaObject,
    qt_meta_stringdata_RouteInterface.data,
    qt_meta_data_RouteInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RouteInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RouteInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RouteInterface.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int RouteInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void RouteInterface::sendConfirmRoute(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
