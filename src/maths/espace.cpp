#include "espace.h"

namespace maths {

Espace::Espace(const quint16 &width, const quint16 &height, const quint16 &deep, const qint32 &precision) : precision_(precision) {
    size_.x = width;
    size_.y = height;
    size_.z = deep;
}
Espace::Espace() {}
Espace::~Espace() {}

void Espace::get_max(components<quint16> &size) const {
    size = size_;
}

qint16 Espace::get_prec() const
{
    return precision_;
}

void Espace::set(const quint16 &width, const quint16 &height, const quint16 &deep)
{
    size_.x = width;
    size_.y = height;
    size_.z = deep;
}

}

