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

#include "root_shoulder.h"

using namespace std;

namespace root {
    Shoulder::Shoulder(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : Root(mat_frame_, mat_frame_draw_) {
    }

    Shoulder::~Shoulder() {
    }

    void Shoulder::first_search(Vect<float> const &vect_neck, Vect<float> const &vect_hips, bool l_r_) {

        l_r = l_r_;
        Vect<float> v(0, 0, 0);

        Vect<float> neck_to_hips = vect_hips - vect_neck;

        if(vectors_maths::normal(neck_to_hips) == 0.0f)
            return;

        if(vect_hips.x == vect_neck.x || vect_hips.y == vect_neck.y)
            try {
                throw std::string("Division by 0 in root_shoulder.");
            }
            catch(std::string const& str) {
                std::cerr << str << std::endl;
                return;
            }

        // is it the left shoulder or the right shoulder ?
        // s'agit-il de l'épaule droite ou de l'épaule gauche ?
        // nous pivotons le vecteur de PI/2 dans le sens direct ou indirect, suivant s'il s'agit de l'épaule gauche ou droite
        // we rotate the vector of PI / 2 in the direct or indirect way, following the case of the left or right shoulder
        if(!l_r)
            v = quick_rot(neck_to_hips, 0);
        else
            v = quick_rot(neck_to_hips, 1);

        Vect<float> i = v / vectors_maths::normal(v);
        Vect<float> u = vect_neck;

        u += neck_to_hips / (float)14.0;

        // A partir du point u, nous cherchons à sortir de la zone rouge, une fois la zone noire trouvée, nous sommes alors sur l'épaule
        // From the point u, we try to exit from the red area, once found the black area, then we are on the shoulder
        while(!control<float>(u)) {
            if (!(mat_frame.PIXEL_COLOR_RED_VECT(u)))
                break;
            u += i;
        }

        p = u;

        lenght_neck_shoulder = vectors_maths::lenght(p, vect_neck);
        init_angle = vectors_maths::angle_vects(vect_hips - vect_neck, p - vect_neck);

    }

    void Shoulder::bone(Vect<float> const &vect_neck) {

        //Vect<float>t = vect_neck;
        //t += neck_to_hips / (float)14.0;
        Vect<float> u = p - vect_neck;
        try {
            if(p.x - vect_neck.x == 0.0f && p.y - vect_neck.y == 0.0f)
                throw "division by 0";
            float k = lenght_neck_shoulder / vectors_maths::normal(u);

            p = k * u + vect_neck;

        }
        catch ( const exception &e )
        {
            cerr << "(Root Shoulder) Exception caught !!" << endl;
            cerr << e.what() << endl;
        }

    }

    void Shoulder::search(float const &radius, int const &black_arc, Vect<float> vec_black_arc, Vect<float> neck, Vect<float> hips) {

        Root::search(radius, black_arc, vec_black_arc);

    }

    void Shoulder::new_rot(Vect<float> const &hips, Vect<float> const &neck) {

        Vect<float> neck_to_hips = hips - neck;
        Vect<float> neck_to_shoulder = p - neck;
        float angle = vectors_maths::angle_vects(neck_to_hips, neck_to_shoulder) * 180.0f / PI;

        if(l_r)
            vect_rot.push_back(Vect<float>(.0f, .0f, angle - 30.0f));
        else
            vect_rot.push_back(Vect<float>(.0f, .0f, angle + 30.0f));

    }

}
