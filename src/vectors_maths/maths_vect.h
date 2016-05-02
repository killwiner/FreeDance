#ifndef MATHS_VECT_H
#define MATHS_VECT_H

#include "../vect.h"
#include <cmath>

#define PI 3.141592654f
#define EPSILONE .001f
#define V_NULL (Vect<float>(0, 0, 0))

namespace vectors_maths {

    // return the intersection point between two vectors (v1, v2) and (w1, w2)
    // retourne l'intersection entre deux vecteurs (v1, v2) et (w1, w2)
    Vect<float> cross_2D(Vect<float> const &, Vect<float> const &, Vect<float> const &, Vect<float> const &);

    // return the lenght between two vectors
    // retourne la longeur entre deux vecteurs
    float lenght(Vect<float> const &, Vect<float> const &);

    // return the normal of a vector
    // returoune la normale d'un vecteur
    float normal(Vect<float> const &);

    // cross product
    // produit vectoriel
    Vect<float> cross_product(Vect<float> const &, Vect<float> const &);

    // product between a 3x3 matrix and a 1x3 matrix
    // produit entre une matrice 3x3 et une matrice 1x3
    Vect<float> matrix_3_3_product_1_3(Vect< Vect<float> > const &, Vect<float> const &);

    // angle between two vectors
    // angle entre deux vecteurs
    float angle_vects(Vect<float> const &, Vect<float> const &);

    // convert a vector from 3D to 2D, eraze one of axis
    // convertit un vecteur 3D en 2D en supprimant l'un des axes
    Vect<float> _3D_to_2D_xy(Vect<float>);
    Vect<float> _3D_to_2D_yz(Vect<float>);

}

#endif // MATHS_VECT_H
