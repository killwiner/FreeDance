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

#ifndef ROOT_HEAD_H
#define ROOT_HEAD_H

#include "root.h"
#include <vector>

namespace root {
    class Head : public Root {
    public:
        explicit Head(cv::Mat const &, QSharedPointer<cv::Mat> &);
        ~Head();
        Vect<float> first_search();
        //void new_rot(Vect<float> const&, Vect<float> const&);

        Vect<float> s;
        std::vector< Vect <float> > vect_rot;
        void search(float const &, int const &, Vect<float> const &);
        //void bone(Vect<float> const&);

    private:
        bool web(Vect<float> &, float &, float const &, float const &, float &, float &, Vect<float> &, float const &, Vect<float> &, Vect<float> &, Vect<float> &);
        bool every_m_lines(Vect<float> &, float &, float const &, float &, float &, bool const &, bool &, Vect<float> &, Vect<float> &, float const &, float const &,
                           float &, float &, Vect<float> &, float &, Vect<float> &);
        void along_line(bool const &, bool &, float &, Vect<float> &, float const &, float &, float &,
                        Vect<float> &, float &, Vect<float> &, float &, float &);
        bool search_from_up_to_down(Vect<float> &neck);
        float lenght_neck_head;

        int m_lines; // every m_lines lines, ch_y turn to true
    };
}
#endif // ROOT_HEAD_H
