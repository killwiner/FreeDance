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

#include "vect.h"

template <typename T>
Vect<T>::Vect(T x_, T y_, T z_) : x(x_), y(y_), z(z_), width(640), height(480) {
}

template <typename T>
Vect<T>::Vect() : x(0), y(0), z(0), width(640), height(480) {
}

template <typename T>
bool operator==(Vect<T> const& a, Vect<T> const& b) {
    if (a.x == b.x && a.y == b.y, a.z == b.z)
        return true;
    else
        return false;
}

template <typename T>
bool operator!=(Vect<T> const& a, Vect<T> const& b) {
    if (a == b)
        return false;
    else
        return true;
}

template <typename T>
void Vect<T>::operator+=(Vect<T> const& a) {

    Vect<T> c;
    c = a + *this;
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
}


template <typename T>
void Vect<T>::operator-=(Vect<T> const& a) {

    Vect<T> c;
    c = *this - a;
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
}

template <typename T>
int coord_gbr(Vect<T> const& a) {
    return 3 * (int)a.x + (int)a.y * 640 * 3;
}

template <typename T>
int coord_gray(Vect<T> const& a) {
    return (int)a.x + (int)a.y * 640;
}

template <typename T>
bool is_null(Vect<T> const &a) {
    if (a.x == a.width && a.y == a.height)
        return true;

    return false;
}

template <typename T>
bool control(Vect<T> const &a) {
    if(a.x >= a.width || a.y >= a.height || a.x < 0 || a.y < 0)
        return true;

    return false;
}

template <typename T>
Vect<T> quick_rot(Vect<T> v, int r) {

    Vect<T> u = v;

    switch(r) {
    case 0:
        v.x = u.y;
        v.y = -u.x;
        break;
    case 1:
        v.x = -u.y;
        v.y = u.x;
        break;
    default:
        v.x = -u.x;
        v.y = -u.y;
    }
    return v;
}

template <typename T>
void Vect<T>::clone(Vect<T> &a) {
    a.x = this->x;
    a.y = this->y;
    a.z = this->z;
}
