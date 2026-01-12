/****************************************************************************
** Meta object code from reading C++ file 'placa.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../placa.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'placa.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN5PlacaE_t {};
} // unnamed namespace

template <> constexpr inline auto Placa::qt_create_metaobjectdata<qt_meta_tag_ZN5PlacaE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Placa",
        "portaVerificada",
        "",
        "portaNome",
        "PlacaConectada",
        "execucaoIniciada",
        "statusChanged",
        "conectar",
        "executar",
        "inicia_testemunho",
        "onTimerTimeout",
        "status",
        "Status",
        "emStandBy",
        "emFuncionamento",
        "erroOcorrido"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'portaVerificada'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'PlacaConectada'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'execucaoIniciada'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'conectar'
        QtMocHelpers::SlotData<void(QString)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'executar'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'inicia_testemunho'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerTimeout'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'status'
        QtMocHelpers::PropertyData<enum Status>(11, 0x80000000 | 12, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 3),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Status'
        QtMocHelpers::EnumData<enum Status>(12, 12, QMC::EnumFlags{}).add({
            {   13, Status::emStandBy },
            {   14, Status::emFuncionamento },
            {   15, Status::erroOcorrido },
        }),
    };
    return QtMocHelpers::metaObjectData<Placa, qt_meta_tag_ZN5PlacaE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Placa::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5PlacaE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5PlacaE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5PlacaE_t>.metaTypes,
    nullptr
} };

void Placa::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Placa *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->portaVerificada((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->PlacaConectada(); break;
        case 2: _t->execucaoIniciada(); break;
        case 3: _t->statusChanged(); break;
        case 4: _t->conectar((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->executar(); break;
        case 6: _t->inicia_testemunho(); break;
        case 7: _t->onTimerTimeout(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Placa::*)(QString )>(_a, &Placa::portaVerificada, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Placa::*)()>(_a, &Placa::PlacaConectada, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Placa::*)()>(_a, &Placa::execucaoIniciada, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Placa::*)()>(_a, &Placa::statusChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<enum Status*>(_v) = _t->getStatus(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setStatus(*reinterpret_cast<enum Status*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Placa::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Placa::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5PlacaE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Placa::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Placa::portaVerificada(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Placa::PlacaConectada()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Placa::execucaoIniciada()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Placa::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
