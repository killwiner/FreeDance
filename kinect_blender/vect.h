#ifndef VECT_H
#define VECT_H

template <typename T>

class Vect {
public:
    explicit Vect(T, T);
    explicit Vect();
    T x, y;

    void operator+=(Vect const& a);
    void operator-=(Vect const& a);

    int width, height;

};

/*
template <typename T>
bool operator==(Vect<T> const& a, Vect<T> const& b);
template <typename T>
bool operator!=(Vect<T> const& a, Vect<T> const& b);
template <typename T>
Vect<T> operator+(Vect<T> const& a, Vect<T> const& b);
template <typename T>
Vect<T> operator-(Vect<T> const& a, Vect<T> const& b);
template <typename T>
int coord_gbr(Vect<T> const& a);
template <typename T>
int coord_gray(Vect<T> const& a);
template <typename T>
bool is_null(Vect<T> const &a);
template <typename T>
bool control(Vect<T> const &a);

Vect<float> cross(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);
*/

#include "vect.tpp"
#endif // VECT_H
