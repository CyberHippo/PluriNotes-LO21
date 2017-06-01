/****************************************************************************
** Meta object code from reading C++ file 'fenetres.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Projet_LO21Actuel/fenetres.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetres.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Principale_t {
    QByteArrayData data[3];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Principale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Principale_t qt_meta_stringdata_Principale = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Principale"
QT_MOC_LITERAL(1, 11, 21), // "ouverture_fen_edition"
QT_MOC_LITERAL(2, 33, 0) // ""

    },
    "Principale\0ouverture_fen_edition\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Principale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Principale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Principale *_t = static_cast<Principale *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ouverture_fen_edition(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Principale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Principale.data,
      qt_meta_data_Principale,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Principale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Principale::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Principale.stringdata0))
        return static_cast<void*>(const_cast< Principale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Principale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_fen_Note_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fen_Note_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fen_Note_t qt_meta_stringdata_fen_Note = {
    {
QT_MOC_LITERAL(0, 0, 8) // "fen_Note"

    },
    "fen_Note"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fen_Note[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void fen_Note::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject fen_Note::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fen_Note.data,
      qt_meta_data_fen_Note,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fen_Note::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fen_Note::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fen_Note.stringdata0))
        return static_cast<void*>(const_cast< fen_Note*>(this));
    return QWidget::qt_metacast(_clname);
}

int fen_Note::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
