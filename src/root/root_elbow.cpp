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

#include "root_elbow.h"
#include <stdio.h>

using namespace std;

namespace root {

Elbow::Elbow(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : Root(mat_frame_, mat_frame_draw_) {
}

Elbow::~Elbow() {
}

void Elbow::first_search(Vect<float> const &shoulder, Vect<float> const &hand, bool const &l_r_) {
    l_r = l_r_;
    search(shoulder, hand);
    lenght_shoulder_elbow = vectors_maths::lenght(shoulder, p);

}

void Elbow::search(Vect<float> const &shoulder, Vect<float> const &hand) {

    Vect<float> a = shoulder - hand;
    Vect<float> n = a / vectors_maths::normal(a);

    l_r ? n = quick_rot(n, 0) : n = quick_rot(n, 1);

    Vect<float> v = shoulder - a / 2;

    while(!control<float>(v)) {
        if(mat_frame.PIXEL_COLOR_RED_VECT(v))
            p = v;
        v += n;
    }

    Vect<float>l = shoulder - p;

    if(vectors_maths::lenght(shoulder, p) < lenght_shoulder_elbow)
        p.z = -sqrt(lenght_shoulder_elbow * lenght_shoulder_elbow - l.x * l.x - l.y * l.y);

}

void Elbow::new_rot(Vect<float> const &neck, Vect<float> const &shoulder) {

    Vect<float> neck_to_shoulder = shoulder - neck;
    Vect<float> shoulder_to_elbow = p - shoulder;
    float angle = vectors_maths::angle_vects(shoulder_to_elbow, neck_to_shoulder) * 180.0f / PI;

    if(l_r)
        vect_rot.push_back(Vect<float>(.0f, .0f, angle - 45.0f));
    else
        vect_rot.push_back(Vect<float>(.0f, .0f, angle + 45.0f));
}
}
