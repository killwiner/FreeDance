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

#include "bezier.h"

using namespace std;

// convert 3 points into 3 points along the bezier curve
// convertit 3 points en 3 points le long de la courbe de bézier
void bezier_deg_3(Vect<float> &a, Vect<float> &b, Vect<float> &c, Vect<float> &d) {

    float t0 = 1.0f/3.0f;
    float t1 = 2.0f/3.0f;

    Vect<float>p0 = a * pow(1.0f - t0, 3) + 3 * b * t0 * (1.0f - t0) * (1.0f - t0) + 3 * c * t0 * t0 * (1 - t0) + d * pow(t0, 3);
    Vect<float>p1 = a * pow(1.0f - t1, 3) + 3 * b * t1 * (1.0f - t1) * (1.0f - t1) + 3 * c * t1 * t1 * (1 - t1) + d * pow(t1, 3);

    b = p0;
    c = p1;
}

// create a bezier curve from vectors of points
// crée une courbe de bézier à partir d'un vecteur de points
void bezier(vector< Vect<float> > &points) {

    for (vector< Vect<float> >::iterator it = points.begin(); ; it+=3) {

        if(it == points.end())
            break;
        if(it+1 == points.end())
            break;
        if(it+2 == points.end())
            break;
        if(it+3 == points.end())
            break;

        bezier_deg_3(it[0], it[1], it[2], it[3]);
    }
}
