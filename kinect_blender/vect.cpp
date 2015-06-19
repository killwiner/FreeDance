#include "vect.h"

Vect::Vect(int x_, int y_) : x(x_), y(y_), width(640), height(480) {
}

Vect::Vect() : x(0), y(0), width(640), height(480) {
}

bool operator==(Vect const& a, Vect const& b) {
    if (a.x == b.x && a.y == b.y)
        return true;
    else
        return false;
}

bool operator!=(Vect const& a, Vect const& b) {
    if (a == b)
        return false;
    else
        return true;
}

Vect operator+(Vect const& a, Vect const& b) {

    Vect n(a.width, a.height);
    Vect c(a.x + b.x, a.y + b.y);

    if (c.x >= c.width || c.x < 0)
        return n;

    if (c.y >= c.height || c.y < 0)
        return n;

    return c;
}

void Vect::operator+=(Vect const& a) {

    Vect c;
    c = a + *this;
    this->x = c.x;
    this->y = c.y;
}

Vect operator-(Vect const& a, Vect const& b) {

    Vect n(a.width, a.height);

    if (a.x < b.x)
        return n;

    if (a.y < b.y)
        return n;

    Vect c(a.x - b.x, a.y - b.y);

    return c;
}

void Vect::operator-=(Vect const& a) {

    Vect c;
    c = *this - a;
    this->x = c.x;
    this->y = c.y;
}

int coord_gbr(Vect const& a) {
    return 3 * a.x + a.y * 640 * 3;
}

int coord_gray(Vect const& a) {
    return a.x + a.y * 640;
}

bool is_null(Vect const &a) {
    if (a.x == a.width && a.y == a.height)
        return true;

    return false;
}

bool control(Vect const &a) {
    if(a.x > a.width || a.y > a.height || a.x < 0 || a.y < 0)
        return true;

    return false;
}
