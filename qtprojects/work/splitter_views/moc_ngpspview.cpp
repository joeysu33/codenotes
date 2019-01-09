/****************************************************************************
** Meta object code from reading C++ file 'ngpspview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ngpspview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ngpspview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NGPSPView_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NGPSPView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NGPSPView_t qt_meta_stringdata_NGPSPView = {
    {
QT_MOC_LITERAL(0, 0, 9) // "NGPSPView"

    },
    "NGPSPView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NGPSPView[] = {

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

void NGPSPView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject NGPSPView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NGPSPView.data,
      qt_meta_data_NGPSPView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NGPSPView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NGPSPView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NGPSPView.stringdata0))
        return static_cast<void*>(const_cast< NGPSPView*>(this));
    return QWidget::qt_metacast(_clname);
}

int NGPSPView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_NGPSPViewOrSplitter_t {
    QByteArrayData data[10];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NGPSPViewOrSplitter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NGPSPViewOrSplitter_t qt_meta_stringdata_NGPSPViewOrSplitter = {
    {
QT_MOC_LITERAL(0, 0, 19), // "NGPSPViewOrSplitter"
QT_MOC_LITERAL(1, 20, 10), // "aboutToAdd"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "QWidget*"
QT_MOC_LITERAL(4, 41, 7), // "content"
QT_MOC_LITERAL(5, 49, 11), // "finishToAdd"
QT_MOC_LITERAL(6, 61, 10), // "NGPSPView*"
QT_MOC_LITERAL(7, 72, 4), // "view"
QT_MOC_LITERAL(8, 77, 13), // "aboutToRemove"
QT_MOC_LITERAL(9, 91, 14) // "finishToRemove"

    },
    "NGPSPViewOrSplitter\0aboutToAdd\0\0"
    "QWidget*\0content\0finishToAdd\0NGPSPView*\0"
    "view\0aboutToRemove\0finishToRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NGPSPViewOrSplitter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,
       9,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void NGPSPViewOrSplitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NGPSPViewOrSplitter *_t = static_cast<NGPSPViewOrSplitter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->aboutToAdd((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->finishToAdd((*reinterpret_cast< NGPSPView*(*)>(_a[1]))); break;
        case 2: _t->aboutToRemove((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->finishToRemove((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NGPSPView* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NGPSPViewOrSplitter::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NGPSPViewOrSplitter::aboutToAdd)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (NGPSPViewOrSplitter::*_t)(NGPSPView * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NGPSPViewOrSplitter::finishToAdd)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (NGPSPViewOrSplitter::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NGPSPViewOrSplitter::aboutToRemove)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (NGPSPViewOrSplitter::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NGPSPViewOrSplitter::finishToRemove)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject NGPSPViewOrSplitter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NGPSPViewOrSplitter.data,
      qt_meta_data_NGPSPViewOrSplitter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NGPSPViewOrSplitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NGPSPViewOrSplitter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NGPSPViewOrSplitter.stringdata0))
        return static_cast<void*>(const_cast< NGPSPViewOrSplitter*>(this));
    return QWidget::qt_metacast(_clname);
}

int NGPSPViewOrSplitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NGPSPViewOrSplitter::aboutToAdd(QWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NGPSPViewOrSplitter::finishToAdd(NGPSPView * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NGPSPViewOrSplitter::aboutToRemove(QWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NGPSPViewOrSplitter::finishToRemove(QWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
