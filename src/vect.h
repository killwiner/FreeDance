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

#ifndef VECT_H
#define VECT_H

template <typename T>

class Vect {
public:
    explicit Vect(T, T, T);
    explicit Vect();
    T x, y, z;

    void operator+=(Vect const& a);
    void operator-=(Vect const& a);

    void clone(Vect<T> &);

    int width, height;

};

Vect<float> operator/(Vect<float> const& a, float const& s);
Vect<float> operator*(float const& s, Vect<float> const& a);
Vect<float> operator*(Vect<float> const& a, float const& s);
Vect<int> operator+(Vect<int> const& a, Vect<int> const& b);
Vect<double> operator+(Vect<double> const& a, Vect<double> const& b);
Vect<float> operator+(Vect<float> const& a, Vect<float> const& b);
Vect<int> operator-(Vect<int> const& a, Vect<int> const& b);
Vect<float> operator-(Vect<float> const& a, Vect<float> const& b);

#include "vect.tpp"
#endif // VECT_H
