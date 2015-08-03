#ifndef MATHS_VECT_H
#define MATHS_VECT_H

#include "vect.h"
#include <math.h>

#define PI 3.141592654

Vect<float> cross(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);
float dist(Vect<float> const &u, Vect<float> const &v);
float normal(Vect<float> const &u);

#endif // MATHS_VECT_H
