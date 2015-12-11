#include "maths_vect.h"

Vect<float> cross_2D(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2) {

    float a1 = (v1.y - w1.y) / (v1.x - w1.x);
    float b1 = v1.y - v1.x * a1;

    float a2 = (v2.y - w2.y) / (v2.x - w2.x);
    float b2 = v2.y - v2.x * a2;

    float x = (b2 - b1) / (a1 - a2);
    float y = a1 * x + b1;

    return Vect<float>(x, y, 0);
}

// return the lenght between two vectors
float lenght(Vect<float> const &u, Vect<float> const &v) {
    return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y) + (u.z - v.z) * (u.z - v.z));
}

float normal(Vect<float> const &u) {
    return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

Vect<float> cross_product(Vect<float> const &u, Vect<float> const &v) {
    return Vect<float>(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
}

Vect<float> matrix_3_3_product_1_3(Vect< Vect<float> > const &u, Vect<float> const &v) {
    Vect<float> r;
    r.x = u.x.x * v.x + u.x.y * v.y + u.x.z * v.z;
    r.y = u.y.x * v.x + u.y.y * v.y + u.y.z * v.z;
    r.z = u.z.x * v.x + u.z.y * v.y + u.z.z * v.z;
    return r;
}

float angle_vects(Vect<float> const &u, Vect<float> const &v) {

    if(normal(u) * normal(v) == .0f)
        return .0f;

    float angle = acosf((u.x*v.x + u.y*v.y + u.z*v.z) / (normal(u) * normal(v)));
    if(cross_product(u, v).z < 0)
        angle *= -1.0f;
    return angle;
}
