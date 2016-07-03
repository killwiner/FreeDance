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

#include "root_neck.h"
#include <QDebug>

using namespace std;

namespace root {
Neck::Neck(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : Root(mat_frame_, mat_frame_draw_) {
}

Neck::~Neck() {
}

void Neck::first_search(Vect<float> const &vect_neck_, Vect<float> const &vect_hips, Vect<float> const &vect_head) {
    s = Vect<float>(0.000000, -0.401210, 3.427901);
    p = vect_neck_;
    lenght_neck_hips = vectors_maths::lenght(p, vect_hips);
    lenght_neck_head = vectors_maths::lenght(p, vect_head);
}

// keep lenght between hips and neck
void Neck::bone(Vect<float> const &vect_hips, Vect<float> const &vect_head) {

    // We adjust the lenght bone between hips and neck
    Vect<float> p_to_hips = p - vect_hips;
    float k_hips = lenght_neck_hips / vectors_maths::normal(p_to_hips);

    if(k_hips < 1.0f)
        p = k_hips * p_to_hips + vect_hips;

    // We adjust the lenght bone between head and neck
    Vect<float> p_to_head = p - vect_head;
    float k_head = lenght_neck_head / vectors_maths::normal(p_to_head);
    p = k_head * p_to_head + vect_head;
}

void Neck::new_rot(Vect<float> const &vect_head, Vect<float> const &vect_hips) {

    // export rotation
    try {
        Vect<float> vect_spine = vect_hips;
        vect_spine.y -= model_lenght_hips_spine;
        vect_rot.push_back(Vect<float>(.0f, .0f, 180.0f / PI * vectors_maths::angle_vects(p - vect_spine, vect_head - p)));
        //qDebug() << 180.0f / PI * vectors_maths::angle_vects(p - vect_spine, vect_head - p);
    }
    catch ( const exception &e )
    {
        vect_rot.push_back(Vect<float>(.0f, .0f, .0f));

        cerr << "(Root_neck) Exception caught !!" << endl;
        cerr << e.what() << endl;
        throw;
    }
}
}

