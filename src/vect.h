#ifndef VECT_H
#define VECT_H

template <typename T>

class Vect {
public:
    explicit Vect(T, T, T);
    explicit Vect();
    T x, y, z;

    void operator+=(Vect const& a);
    void operator-=(Vect const& a);

    Vect<T> clone();

    int width, height;

};

Vect<float> operator/(Vect<float> const& a, float const& s);
Vect<float> operator*(float const& s, Vect<float> const& a);
Vect<float> operator*(Vect<float> const& a, float const& s);
Vect<int> operator+(Vect<int> const& a, Vect<int> const& b);
Vect<float> operator+(Vect<float> const& a, Vect<float> const& b);
Vect<int> operator-(Vect<int> const& a, Vect<int> const& b);
Vect<float> operator-(Vect<float> const& a, Vect<float> const& b);

#include "vect.tpp"
#endif // VECT_H
