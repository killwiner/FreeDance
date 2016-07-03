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

#include <vect.h>

Vect<float> operator/(Vect<float> const& a, float const& s) {

    Vect<float> c = a;

    if(s == 0.0) {
        c.x = 0;
        c.y = 0;
        c.z = 0;
    }
    else {
        c.x = a.x / s;
        c.y = a.y / s;
        c.z = a.z / s;
    }
    return c;
}

Vect<float> operator*(float const& s, Vect<float> const& a) {

    Vect<float> c = a;

    c.x = a.x * s;
    c.y = a.y * s;
    c.z = a.z * s;

    return c;
}

Vect<float> operator*(Vect<float> const& a, float const& s) {

    Vect<float> c = a;

    c.x = a.x * s;
    c.y = a.y * s;
    c.z = a.z * s;

    return c;
}

Vect<int> operator+(Vect<int> const& a, Vect<int> const& b) {

    Vect<int> n(a.width, a.height, 0);
    Vect<int> c(a.x + b.x, a.y + b.y, a.z + b.z);

    if (c.x >= c.width || c.x < 0)
        return n;

    if (c.y >= c.height || c.y < 0)
        return n;

    return c;
}

Vect<float> operator+(Vect<float> const& a, Vect<float> const& b) {

    Vect<float> c(a.x + b.x, a.y + b.y, a.z + b.z);

    return c;
}

Vect<double> operator+(Vect<double> const& a, Vect<double> const& b) {

    Vect<double> c(a.x + b.x, a.y + b.y, a.z + b.z);

    return c;
}

Vect<int> operator-(Vect<int> const& a, Vect<int> const& b) {

    Vect<int> n(a.width, a.height, 0);

    if (a.x < b.x)
        return n;

    if (a.y < b.y)
        return n;

    Vect<int> c(a.x - b.x, a.y - b.y, a.z - b.z);

    return c;
}

Vect<float> operator-(Vect<float> const& a, Vect<float> const& b) {

    Vect<float> c(a.x - b.x, a.y - b.y, a.z - b.z);

    return c;
}
