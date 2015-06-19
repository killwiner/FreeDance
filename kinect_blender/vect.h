#ifndef VECT_H
#define VECT_H

class Vect {
public:
    explicit Vect(int, int);
    explicit Vect();
    int x, y;

    void operator+=(Vect const& a);
    void operator-=(Vect const& a);

    int width, height;

};

bool operator==(Vect const& a, Vect const& b);
bool operator!=(Vect const& a, Vect const& b);
Vect operator+(Vect const& a, Vect const& b);
Vect operator-(Vect const& a, Vect const& b);
int coord_gbr(Vect const& a);
int coord_gray(Vect const& a);
bool is_null(Vect const &a);
bool control(Vect const &a);

#endif // VECT_H
