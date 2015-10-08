#ifndef MATHS_VECT_H
#define MATHS_VECT_H

#include "vect.h"
#include <math.h>

#define PI 3.141592654

Vect<float> cross_2D(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);
float lenght(Vect<float> const &u, Vect<float> const &v);
float normal(Vect<float> const &u);
Vect<float> cross_product(Vect<float> const &u, Vect<float> const &v);
Vect<float> matrix_3_3_product_1_3(Vect< Vect<float> > const &u, Vect<float> const &v);

#endif // MATHS_VECT_H
