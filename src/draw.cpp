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

#include "draw.h"

void draw_square(const int &ray, const int &x_, const int &y_, QSharedPointer<cv::Mat> &SP_mat) {

    Vect<int> v;

    for (v.x = x_ - ray; v.x < x_ + ray; ++v.x)
        for (v.y = y_ - ray; v.y < y_ + ray; ++v.y)
            if (!control<int>(v)) {
                SP_mat->PIXEL_COLOR_BLUE_VECT(v) = 255;
                SP_mat->PIXEL_COLOR_GREEN_VECT(v) = 255;
                SP_mat->PIXEL_COLOR_RED_VECT(v) = 255;
            }
}
