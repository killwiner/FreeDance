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

#include "maths_vect.h"

using namespace std;

namespace vectors_maths {

    Vect<float> cross_2D(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2) {

        float a1 = (v1.y - w1.y) / (v1.x - w1.x);
        float b1 = v1.y - v1.x * a1;

        float a2 = (v2.y - w2.y) / (v2.x - w2.x);
        float b2 = v2.y - v2.x * a2;

        float x = (b2 - b1) / (a1 - a2);
        float y = a1 * x + b1;

        return Vect<float>(x, y, 0);
    }

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

        float angle;

        try {
            if(normal(u) * normal(v) == .0f)
                throw "(maths_vect) division by 0";

            angle = acosf((u.x*v.x + u.y*v.y + u.z*v.z) / (normal(u) * normal(v)));
            if(cross_product(u, v).z < 0)
                angle *= -1.0f;

        }
        catch ( const exception &e )
        {
            cerr << "(angle_vects function) Exception caught !!" << endl;
            cerr << e.what() << endl;
            throw;
        }

        return angle;
    }

    Vect<float> _3D_to_2D_xy(Vect<float> u) {
        u.z = .0f;
        return u;
    }

    Vect<float> _3D_to_2D_yz(Vect<float> u) {
        u.x = .0f;
        return u;
    }
}
