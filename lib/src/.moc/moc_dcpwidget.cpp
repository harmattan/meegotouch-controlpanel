/****************************************************************************
** Meta object code from reading C++ file 'dcpwidget.h'
**
** Created: Mon Mar 30 15:31:20 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../appletif/dcpwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dcpwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DcpWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DcpWidget[] = {
    "DcpWidget\0\0refresh()\0"
};

const QMetaObject DcpWidget::staticMetaObject = {
    { &DuiWidget::staticMetaObject, qt_meta_stringdata_DcpWidget,
      qt_meta_data_DcpWidget, 0 }
};

const QMetaObject *DcpWidget::metaObject() const
{
    return &staticMetaObject;
}

void *DcpWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DcpWidget))
        return static_cast<void*>(const_cast< DcpWidget*>(this));
    return DuiWidget::qt_metacast(_clname);
}

int DcpWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DuiWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refresh(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DcpWidget::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
