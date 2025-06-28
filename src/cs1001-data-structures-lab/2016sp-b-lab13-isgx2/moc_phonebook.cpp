/****************************************************************************
** Meta object code from reading C++ file 'phonebook.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phonebook.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'phonebook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PhoneBook[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   10,   10,   10, 0x08,
      44,   10,   10,   10, 0x08,
      51,   10,   10,   10, 0x08,
      64,   58,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PhoneBook[] = {
    "PhoneBook\0\0fileName\0useFile(QString)\0"
    "save()\0open()\0quit()\0entry\0addNumber(Entry*)\0"
};

void PhoneBook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PhoneBook *_t = static_cast<PhoneBook *>(_o);
        switch (_id) {
        case 0: _t->useFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->save(); break;
        case 2: _t->open(); break;
        case 3: _t->quit(); break;
        case 4: _t->addNumber((*reinterpret_cast< Entry*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PhoneBook::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PhoneBook::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PhoneBook,
      qt_meta_data_PhoneBook, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhoneBook::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhoneBook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhoneBook::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhoneBook))
        return static_cast<void*>(const_cast< PhoneBook*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PhoneBook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PhoneBook::useFile(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
