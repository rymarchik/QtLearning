/****************************************************************************
** Meta object code from reading C++ file 'editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RefInfoEditor/editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Editor_t {
    QByteArrayData data[14];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Editor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Editor_t qt_meta_stringdata_Editor = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Editor"
QT_MOC_LITERAL(1, 7, 21), // "slotShowDirectoryInfo"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 47, 22), // "slotShowLowerFireTable"
QT_MOC_LITERAL(5, 70, 28), // "slotActivateEditDeleteButton"
QT_MOC_LITERAL(6, 99, 26), // "slotAddDialChangeComboBox1"
QT_MOC_LITERAL(7, 126, 26), // "slotAddDialChangeComboBox2"
QT_MOC_LITERAL(8, 153, 27), // "slotEditDialChangeComboBox1"
QT_MOC_LITERAL(9, 181, 27), // "slotEditDialChangeComboBox2"
QT_MOC_LITERAL(10, 209, 27), // "slotEditDialChangeComboBox3"
QT_MOC_LITERAL(11, 237, 7), // "slotAdd"
QT_MOC_LITERAL(12, 245, 8), // "slotEdit"
QT_MOC_LITERAL(13, 254, 10) // "slotDelete"

    },
    "Editor\0slotShowDirectoryInfo\0\0"
    "QListWidgetItem*\0slotShowLowerFireTable\0"
    "slotActivateEditDeleteButton\0"
    "slotAddDialChangeComboBox1\0"
    "slotAddDialChangeComboBox2\0"
    "slotEditDialChangeComboBox1\0"
    "slotEditDialChangeComboBox2\0"
    "slotEditDialChangeComboBox3\0slotAdd\0"
    "slotEdit\0slotDelete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Editor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    0,   72,    2, 0x08 /* Private */,
       5,    0,   73,    2, 0x08 /* Private */,
       6,    1,   74,    2, 0x08 /* Private */,
       7,    1,   77,    2, 0x08 /* Private */,
       8,    1,   80,    2, 0x08 /* Private */,
       9,    1,   83,    2, 0x08 /* Private */,
      10,    1,   86,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Editor *_t = static_cast<Editor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotShowDirectoryInfo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->slotShowLowerFireTable(); break;
        case 2: _t->slotActivateEditDeleteButton(); break;
        case 3: _t->slotAddDialChangeComboBox1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotAddDialChangeComboBox2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotEditDialChangeComboBox1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotEditDialChangeComboBox2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotEditDialChangeComboBox3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotAdd(); break;
        case 9: _t->slotEdit(); break;
        case 10: _t->slotDelete(); break;
        default: ;
        }
    }
}

const QMetaObject Editor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Editor.data,
      qt_meta_data_Editor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Editor.stringdata0))
        return static_cast<void*>(const_cast< Editor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
