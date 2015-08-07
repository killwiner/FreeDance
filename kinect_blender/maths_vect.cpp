#include "maths_vect.h"

Vect<float> cross(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2) {

    float a1 = (v1.y - w1.y) / (v1.x - w1.x);
    float b1 = v1.y - v1.x * a1;

    float a2 = (v2.y - w2.y) / (v2.x - w2.x);
    float b2 = v2.y - v2.x * a2;

    float x = (b2 - b1) / (a1 - a2);
    float y = a1 * x + b1;

    return Vect<float>(x, y, 0);
}

float dist(Vect<float> const &u, Vect<float> const &v) {
    return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}

float normal(Vect<float> const &u) {
    return sqrt(u.x * u.x + u.y * u.y);
}
