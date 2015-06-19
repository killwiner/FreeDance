#include "vect_f.h"

Vect_f::Vect_f(float x_, float y_) : x(x_), y(y_), width(640), height(480) {
}

Vect_f::Vect_f() : x(0), y(0), width(640), height(480) {
}

bool operator==(Vect_f const& a, Vect_f const& b) {
    if (a.x == b.x && a.y == b.y)
        return true;
    else
        return false;
}

bool operator!=(Vect_f const& a, Vect_f const& b) {
    if (a == b)
        return false;
    else
        return true;
}

Vect_f operator+(Vect_f const& a, Vect_f const& b) {

    Vect_f n(a.width, a.height);
    Vect_f c(a.x + b.x, a.y + b.y);

    if (c.x >= c.width || c.x < 0)
        return n;

    if (c.y >= c.height || c.y < 0)
        return n;

    return c;
}

void Vect_f::operator+=(Vect_f const& a) {

    Vect_f c;
    c = a + *this;
    this->x = c.x;
    this->y = c.y;
}

Vect_f operator-(Vect_f const& a, Vect_f const& b) {

    Vect_f n(a.width, a.height);

    if (a.x < b.x)
        return n;

    if (a.y < b.y)
        return n;

    Vect_f c(a.x - b.x, a.y - b.y);

    return c;
}

void Vect_f::operator-=(Vect_f const& a) {

    Vect_f c;
    c = *this - a;
    this->x = c.x;
    this->y = c.y;
}

int coord_gbr_f(Vect_f const& a) {
    return 3 * (int)a.x + (int)a.y * 640 * 3;
}

int coord_gray_f(Vect_f const& a) {
    return (int)a.x + (int)a.y * 640;
}

bool is_null_f(Vect_f const &a) {
    if (a.x == (float)a.width && a.y == (float)a.height)
        return true;

    return false;
}

bool control_f(Vect_f const &a) {
    if(a.x > (float)a.width || a.y > (float)a.height || a.x < 0 || a.y < 0)
        return true;

    return false;
}

Vect_f cross(Vect_f const &v1, Vect_f const &w1, Vect_f const &v2, Vect_f const &w2) {

    float a1 = (v1.y - w1.y) / (v1.x - w1.x);
    float b1 = v1.y - v1.x * a1;

    float a2 = (v2.y - w2.y) / (v2.x - w2.x);
    float b2 = v2.y - v2.x * a2;

    float x = (b2 - b1) / (a1 - a2);
    float y = a1 * x + b1;

    return Vect_f(x, y);
}
