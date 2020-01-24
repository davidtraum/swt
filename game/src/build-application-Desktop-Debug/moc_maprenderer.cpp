/****************************************************************************
** Meta object code from reading C++ file 'maprenderer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../application_server/maprenderer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maprenderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapRenderer_t {
    QByteArrayData data[11];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapRenderer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapRenderer_t qt_meta_stringdata_MapRenderer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MapRenderer"
QT_MOC_LITERAL(1, 12, 9), // "tileClick"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "leftclick"
QT_MOC_LITERAL(4, 33, 14), // "positionChange"
QT_MOC_LITERAL(5, 48, 14), // "sendPlayBridge"
QT_MOC_LITERAL(6, 63, 12), // "onTileChange"
QT_MOC_LITERAL(7, 76, 15), // "enableHighlight"
QT_MOC_LITERAL(8, 92, 13), // "setLogicSpeed"
QT_MOC_LITERAL(9, 106, 18), // "onVideoStateChange"
QT_MOC_LITERAL(10, 125, 19) // "QMediaPlayer::State"

    },
    "MapRenderer\0tileClick\0\0leftclick\0"
    "positionChange\0sendPlayBridge\0"
    "onTileChange\0enableHighlight\0setLogicSpeed\0"
    "onVideoStateChange\0QMediaPlayer::State"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapRenderer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       3,    0,   61,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   68,    2, 0x0a /* Public */,
       7,    1,   75,    2, 0x0a /* Public */,
       8,    1,   78,    2, 0x0a /* Public */,
       9,    1,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void MapRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapRenderer *_t = static_cast<MapRenderer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tileClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->leftclick(); break;
        case 2: _t->positionChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->sendPlayBridge(); break;
        case 4: _t->onTileChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->enableHighlight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setLogicSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onVideoStateChange((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MapRenderer::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapRenderer::tileClick)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MapRenderer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapRenderer::leftclick)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MapRenderer::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapRenderer::positionChange)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MapRenderer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapRenderer::sendPlayBridge)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MapRenderer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MapRenderer.data,
      qt_meta_data_MapRenderer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MapRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapRenderer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MapRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MapRenderer::tileClick(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapRenderer::leftclick()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MapRenderer::positionChange(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MapRenderer::sendPlayBridge()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
