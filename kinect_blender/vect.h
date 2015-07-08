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

Vect<float> operator/(Vect<float> const& a, float const& s);
Vect<int> operator+(Vect<int> const& a, Vect<int> const& b);
Vect<float> operator+(Vect<float> const& a, Vect<float> const& b);
Vect<int> operator-(Vect<int> const& a, Vect<int> const& b);
Vect<float> operator-(Vect<float> const& a, Vect<float> const& b);

#include "vect.tpp"
#endif // VECT_H
