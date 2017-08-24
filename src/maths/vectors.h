/*************************************************************************/
/* This file is part of FreeDance.                                       */
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

#ifndef VECTORS_H
#define VECTORS_H

#include "espace.h"
#include <iostream>

namespace maths {

// notes : A null vector is a vector out from the vectors space
// the nill vector is always the vector : V_NILL with width = 0, height = 0, deep = 0
// notes : On considère un vecteur comme null, un vecteur en dehors de l'espace vectoriel
// le vecteur null est toujours rammené au vecteur : V_NILL with width = 0, height = 0, deep = 0

// template T_Scalar is a scalar for the vector's parameters
// template  is like float, int ...
// template T_Scalar est un scalaire pour les paramètres du vecteur
// template  est du type float, int ...
template <typename T_Scalar>

class Vector {
public:

    // constructor to define the vector
    // constructeur pour déterminer le vecteur
    Vector(const components<T_Scalar> &comp, const QSPEspace &espace);
    Vector(const T_Scalar &x, const T_Scalar &y, const T_Scalar &z, const QSPEspace &e);
    Vector(const Vector<T_Scalar> &vx, const Vector<T_Scalar> &vy, const Vector<T_Scalar> &vz);
    Vector(const Vector<T_Scalar> &v);
    Vector();
    ~Vector();

    // accesseurs
    void get_max(components<quint16> &size) const;

    // incrementals operators
    void operator+=(const Vector &vector);
    void operator-=(const Vector &vector);
    void operator*=(const T_Scalar &scalar);
    void operator/=(const T_Scalar &scalar);

    // accesseurs
    QSPEspace get_espace() const;
    void get_comp(components<T_Scalar> &comp) const;
    void get_comp(T_Scalar &x, T_Scalar &y, T_Scalar &z) const;
    void get_comp(Vector<T_Scalar> &x, Vector<T_Scalar> &y, Vector<T_Scalar> &z) const;
    T_Scalar get_X() const;
    T_Scalar get_Y() const;
    T_Scalar get_Z() const;
    void set(const components<T_Scalar> &comp);
    void set(const T_Scalar &x, const T_Scalar &y, const T_Scalar &z);
    bool isNull() const;
    void Null();
    void swap(Vector<T_Scalar> &vector);

private:
    // components of the vector
    // composantes du vecteur
    components<T_Scalar> comp_;

    QSPEspace espace_;

    QSharedPointer<Vector<T_Scalar> > PVectorX, PVectorY, PVectorZ;

    bool nil;
};

// return true if vectors are the same
// retourne vrai si les vecteurs sont équivalents
template <typename T_Scalar>
bool operator==(const Vector<T_Scalar>& vector_a, const Vector<T_Scalar> &vector_b);

// return true if vectors are not the same
// retourne vrai si les vecteurs ne sont pas équivalents
template <typename T_Scalar>
bool operator!=(Vector<T_Scalar> const& vector_a, const Vector<T_Scalar> &vector_b);

// operator /
template <typename T_Scalar1, typename T_Scalar2>
Vector<T_Scalar1> operator/(const Vector<T_Scalar1> &v, const T_Scalar2 &s);

// operator * between a vector and a scalar
// opérateur * entre un vecteur et un scalaire
template <typename T_Scalar>
Vector<T_Scalar> operator*(const T_Scalar& s, Vector<T_Scalar> const& vector);
template <typename T_Scalar>
Vector<T_Scalar> operator*(Vector<T_Scalar> const &vector, const T_Scalar &s);

// operator * between two vectors
// opérateur * entre deux vecteurs
template <typename T_Scalar>
T_Scalar operator*(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b);

// operator + between two vectors
// opérateur + entre dex vecteurs
template <typename T_Scalar>
Vector<T_Scalar> operator+(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b);

// operator - between two vectors
// opérateur - entre deux vecteurs
template <typename T_Scalar>
Vector<T_Scalar> operator-(Vector<T_Scalar> const& vector_a, Vector<T_Scalar> const& vector_b);

// operator ^, cross product
// produit vectoriel
template <typename T_Scalar>
Vector<T_Scalar> operator^(const Vector<T_Scalar>& vector_a, const Vector<T_Scalar>& vector_b);

#include "vectors.tpp"

}
#endif // VECTORS_H
