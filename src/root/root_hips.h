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

#ifndef ROOT_HIPS_H
#define ROOT_HIPS_H

#include "root.h"

namespace root {
    class Hips : public Root {
    public:
        explicit Hips(cv::Mat const &, QSharedPointer<cv::Mat> &);
        ~Hips();
        void first_search();
        void search(float const &, int const &, Vect<float>);
        void new_rot(Vect<float> const &);

        Vect<float> s;

    private:
        void first_pixel_l2r(int &);
        void first_pixel_r2l(int &);
        bool x_l_move_to_x_r(int const &, int &, int const &);
        bool x_r_move_to_x_l(int const &, int &, int const &);
        int along_lenght(int &, int &);
        void all_rays(int const &, float &, float &, float const &);
        Vect<float> init_offset;
    };
}
#endif // ROOT_HIPS_H
