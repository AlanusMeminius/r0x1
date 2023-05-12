#pragma once
#include <QMetaType>
#include <QVariant>

#define QVARIANTMACRO \
   public:            \
    inline operator QVariant() const { return QVariant::fromValue(*this); }
