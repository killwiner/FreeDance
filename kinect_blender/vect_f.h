#ifndef VECT_F_H
#define VECT_F_H

class Vect_f {
public:
    explicit Vect_f(float, float);
    explicit Vect_f();
    float x, y;

    void operator+=(Vect_f const& a);
    void operator-=(Vect_f const& a);

    float width, height;

};

bool operator==(Vect_f const& a, Vect_f const& b);
bool operator!=(Vect_f const& a, Vect_f const& b);
Vect_f operator+(Vect_f const& a, Vect_f const& b);
Vect_f operator-(Vect_f const& a, Vect_f const& b);
int coord_gbr_f(Vect_f const& a);
int coord_gray_f(Vect_f const& a);
bool is_null_f(Vect_f const &a);
bool control_f(Vect_f const &a);

Vect_f cross(Vect_f const &v1, Vect_f const &w1, Vect_f const &v2, Vect_f const &w2);

#endif // VECT_F_H
