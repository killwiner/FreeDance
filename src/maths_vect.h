#ifndef MATHS_VECT_H
#define MATHS_VECT_H

#include "vect.h"
#include <cmath>

#define PI 3.141592654

// return the intersection point between two vectors (v1, v2) and (w1, w2)
// retourne l'intersection entre deux vecteurs (v1, v2) et (w1, w2)
Vect<float> cross_2D(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);


float lenght(Vect<float> const &u, Vect<float> const &v);
float normal(Vect<float> const &u);
Vect<float> cross_product(Vect<float> const &u, Vect<float> const &v);
Vect<float> matrix_3_3_product_1_3(Vect< Vect<float> > const &u, Vect<float> const &v);
float angle_vects(Vect<float> const &u, Vect<float> const &v);

#endif // MATHS_VECT_H
