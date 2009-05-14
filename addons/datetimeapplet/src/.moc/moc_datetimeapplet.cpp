/****************************************************************************
** Meta object code from reading C++ file 'datetimeapplet.h'
**
** Created: Wed May 13 21:27:08 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../datetimeapplet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datetimeapplet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DateTimeApplet[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_DateTimeApplet[] = {
    "DateTimeApplet\0"
};

const QMetaObject DateTimeApplet::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DateTimeApplet,
      qt_meta_data_DateTimeApplet, 0 }
};

const QMetaObject *DateTimeApplet::metaObject() const
{
    return &staticMetaObject;
}

void *DateTimeApplet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DateTimeApplet))
        return static_cast<void*>(const_cast< DateTimeApplet*>(this));
    if (!strcmp(_clname, "DcpAppletIf"))
        return static_cast< DcpAppletIf*>(const_cast< DateTimeApplet*>(this));
    if (!strcmp(_clname, "com.nokia.dui.core.DcpAppletIf/1.0"))
        return static_cast< DcpAppletIf*>(const_cast< DateTimeApplet*>(this));
    return QObject::qt_metacast(_clname);
}

int DateTimeApplet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
