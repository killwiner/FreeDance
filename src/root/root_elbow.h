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

#ifndef ROOT_ELBOW_H
#define ROOT_ELBOW_H

#include "root.h"

namespace root {
    class Elbow : public Root {
    public:
        explicit Elbow(cv::Mat const &, QSharedPointer<cv::Mat> &);
        ~Elbow();
        void first_search(Vect<float> const &, Vect<float> const &, bool const &);
        void search(Vect<float> const &, Vect<float> const &);
        void new_rot(Vect<float> const &, Vect<float> const &);

        std::vector< Vect <float> > vect_rot;

    private:
        float lenght_shoulder_elbow;
        bool l_r;
    };

}
#endif // ROOT_ELBOW_H
