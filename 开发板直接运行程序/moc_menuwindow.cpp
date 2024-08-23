/****************************************************************************
** Meta object code from reading C++ file 'menuwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ParkingManagementSystem/menuwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuWindow_t {
    QByteArrayData data[17];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuWindow_t qt_meta_stringdata_MenuWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MenuWindow"
QT_MOC_LITERAL(1, 11, 9), // "loginshow"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "addUserShow"
QT_MOC_LITERAL(4, 34, 11), // "parkpole_on"
QT_MOC_LITERAL(5, 46, 12), // "parkpole_off"
QT_MOC_LITERAL(6, 59, 8), // "getFrame"
QT_MOC_LITERAL(7, 68, 9), // "playAudio"
QT_MOC_LITERAL(8, 78, 3), // "str"
QT_MOC_LITERAL(9, 82, 20), // "min_price_dsbox_slot"
QT_MOC_LITERAL(10, 103, 1), // "d"
QT_MOC_LITERAL(11, 105, 12), // "isHaveCarOut"
QT_MOC_LITERAL(12, 118, 6), // "cardId"
QT_MOC_LITERAL(13, 125, 11), // "isHaveCarIn"
QT_MOC_LITERAL(14, 137, 5), // "carId"
QT_MOC_LITERAL(15, 143, 8), // "menuShow"
QT_MOC_LITERAL(16, 152, 17) // "addUserToDatabase"

    },
    "MenuWindow\0loginshow\0\0addUserShow\0"
    "parkpole_on\0parkpole_off\0getFrame\0"
    "playAudio\0str\0min_price_dsbox_slot\0d\0"
    "isHaveCarOut\0cardId\0isHaveCarIn\0carId\0"
    "menuShow\0addUserToDatabase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   77,    2, 0x0a /* Public */,
      11,    1,   80,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,
      15,    0,   86,    2, 0x0a /* Public */,
      16,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MenuWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MenuWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginshow(); break;
        case 1: _t->addUserShow(); break;
        case 2: _t->parkpole_on(); break;
        case 3: _t->parkpole_off(); break;
        case 4: _t->getFrame(); break;
        case 5: _t->playAudio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->min_price_dsbox_slot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->isHaveCarOut((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->isHaveCarIn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->menuShow(); break;
        case 10: _t->addUserToDatabase(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MenuWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::loginshow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MenuWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::addUserShow)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MenuWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::parkpole_on)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MenuWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::parkpole_off)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MenuWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::getFrame)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MenuWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::playAudio)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MenuWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MenuWindow.data,
    qt_meta_data_MenuWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MenuWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MenuWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MenuWindow::loginshow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MenuWindow::addUserShow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MenuWindow::parkpole_on()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MenuWindow::parkpole_off()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MenuWindow::getFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MenuWindow::playAudio(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
