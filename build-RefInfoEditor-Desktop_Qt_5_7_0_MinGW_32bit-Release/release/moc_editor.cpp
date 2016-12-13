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
    QByteArrayData data[12];
    char stringdata0[201];
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
QT_MOC_LITERAL(5, 70, 24), // "slotActivateDeleteButton"
QT_MOC_LITERAL(6, 95, 23), // "slotChangeRootItemValue"
QT_MOC_LITERAL(7, 119, 26), // "slotChange2ndRootItemValue"
QT_MOC_LITERAL(8, 146, 26), // "slotChange3rdRootItemValue"
QT_MOC_LITERAL(9, 173, 7), // "slotAdd"
QT_MOC_LITERAL(10, 181, 8), // "slotEdit"
QT_MOC_LITERAL(11, 190, 10) // "slotDelete"

    },
    "Editor\0slotShowDirectoryInfo\0\0"
    "QListWidgetItem*\0slotShowLowerFireTable\0"
    "slotActivateDeleteButton\0"
    "slotChangeRootItemValue\0"
    "slotChange2ndRootItemValue\0"
    "slotChange3rdRootItemValue\0slotAdd\0"
    "slotEdit\0slotDelete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Editor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    0,   62,    2, 0x08 /* Private */,
       5,    0,   63,    2, 0x08 /* Private */,
       6,    1,   64,    2, 0x08 /* Private */,
       7,    1,   67,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
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
        case 2: _t->slotActivateDeleteButton(); break;
        case 3: _t->slotChangeRootItemValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotChange2ndRootItemValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotChange3rdRootItemValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotAdd(); break;
        case 7: _t->slotEdit(); break;
        case 8: _t->slotDelete(); break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
