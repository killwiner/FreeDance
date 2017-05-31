/*************************************************************************/
/* This file is part of Tron.                                            */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define COMP(X, Y, P) std::abs((qint32)(((X) - (Y)) * (P)))
#define PI 3.141593

#include "vectors.h"
#include <typeinfo>

namespace maths {

// return the intersection point between two vectors
// retourne l'intersection entre deux vecteurs
template <typename T_Scalar>
Vector<T_Scalar> cross_2Dxy(const Vector<T_Scalar>&, const Vector<T_Scalar>&);

// return the normal of a vector
// retourne la normale d'un vecteur
template <typename T_Scalar>
T_Scalar normal(const Vector<T_Scalar> &);

// return the lenght between two vectors
// retourne la longeur entre deux vecteurs
template <typename T_Scalar>
T_Scalar lenght(const Vector<T_Scalar>&, const Vector<T_Scalar>&);

// operator * between two matrix 3x3 and 3x1
// opérateur * entre deux matrices 3x3 and 3x1
template <typename T_Scalar>
Vector<T_Scalar> prod_mat_3x3_3x1(const Vector<T_Scalar>& vector_a, const Vector<T_Scalar>& vector_b);

// angle between two vectors
// angle entre deux vecteurs
template <typename T_Scalar>
T_Scalar angle_vectors(Vector<T_Scalar> const &a, Vector<T_Scalar> const &b);

// convert a vector from 3D to 2D, eraze one of axis
// convertit un vecteur 3D en 2D en supprimant l'un des axes
template <typename T_Scalar>
Vector<T_Scalar> _3D_to_2D_xy(const Vector<T_Scalar> &v); // eraze z axis

// rotate the vector in a direct rotation with steps, each step on an angle PI/2 on plan XY
// rotation du vecteur dans le sens direct avec un nombre de pas, chaque pas fait un angle de PI/2 sur le plan XY
template <typename T_Scalar>
Vector<T_Scalar> quick_rotation(const Vector<T_Scalar> &vector, const qint32 &number_of_steps);

// rotate the vector with an angle
//rotation du vector par rapport a un angle
template <typename T_Scalar>
Vector<T_Scalar> angle_rotation(const Vector<T_Scalar> &vector, const T_Scalar &angle);

#include "functions.tpp"

}

#endif // FUNCTIONS_H
