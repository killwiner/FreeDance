#include "vect.h"

template <typename T>
Vect<T>::Vect(T x_, T y_) : x(x_), y(y_), width(640), height(480) {
}

template <typename T>
Vect<T>::Vect() : x(0), y(0), width(640), height(480) {
}

template <typename T>
bool operator==(Vect<T> const& a, Vect<T> const& b) {
    if (a.x == b.x && a.y == b.y)
        return true;
    else
        return false;
}

template <typename T>
bool operator!=(Vect<T> const& a, Vect<T> const& b) {
    if (a == b)
        return false;
    else
        return true;
}

template <typename T>
Vect<T> operator+(Vect<T> const& a, Vect<T> const& b) {

    Vect<T> n(a.width, a.height);
    Vect<T> c(a.x + b.x, a.y + b.y);

    if (c.x >= c.width || c.x < 0)
        return n;

    if (c.y >= c.height || c.y < 0)
        return n;

    return c;
}

template <typename T>
void Vect<T>::operator+=(Vect<T> const& a) {

    Vect<T> c;
    c = a + *this;
    this->x = c.x;
    this->y = c.y;
}

template <typename T>
Vect<T> operator-(Vect<T> const& a, Vect<T> const& b) {

    Vect<T> n(a.width, a.height);

    if (a.x < b.x)
        return n;

    if (a.y < b.y)
        return n;

    Vect<T> c(a.x - b.x, a.y - b.y);

    return c;
}

template <typename T>
void Vect<T>::operator-=(Vect<T> const& a) {

    Vect<T> c;
    c = *this - a;
    this->x = c.x;
    this->y = c.y;
}

template <typename T>
int coord_gbr(Vect<T> const& a) {
    return 3 * (int)a.x + (int)a.y * 640 * 3;
}

template <typename T>
int coord_gray(Vect<T> const& a) {
    return (int)a.x + (int)a.y * 640;
}

template <typename T>
bool is_null(Vect<T> const &a) {
    if (a.x == a.width && a.y == a.height)
        return true;

    return false;
}

template <typename T>
bool control(Vect<T> const &a) {
    if(a.x > a.width || a.y > a.height || a.x < 0 || a.y < 0)
        return true;

    return false;
}
