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

#ifndef ROOT_HAND_H
#define ROOT_HAND_H

#include "root.h"

namespace root {
    class Hand : public Root {
    public:
        explicit Hand(cv::Mat const &, QSharedPointer<cv::Mat> &);
        ~Hand();
        void first_search(Vect<float>, Vect<float>, bool const &);
        void z_axis(float const&);
        void search(float const &, int const &, Vect<float>, Vect<float> elbow);
        void new_rot(Vect<float> const&, Vect<float> const&);

        std::vector< Vect <float> > vect_rot;

        Vect<float> s;

    private:
        bool get_hand(int const &, int const &, Vect<float> const &, Vect<float> const &);
        void values_2D(Vect<float> const &, Vect<float> const &, Vect<float> &, Vect<float> &, Vect<float> &, Vect<float> &);
        float init_angle_x_y, init_angle_y_z;
        bool l_r;
    };

    inline void Hand::z_axis(const float &z) {
        p.z = z;
    }
}
#endif // ROOT_HAND_H
