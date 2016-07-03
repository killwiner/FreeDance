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

#ifndef ROOT_H
#define ROOT_H

#include <QSharedPointer>
#include "../vectors_maths/maths_vect.h"
#include "../vectors_maths/bezier.h"
#include "win_size.h"
#include "../bvh.h"
#include <opencv2/opencv.hpp>

#define PIXEL_COLOR_BLUE(X, Y) data[coord_gbr(Vect<int>(X, Y, 0))]
#define PIXEL_COLOR_GREEN(X, Y) data[coord_gbr(Vect<int>(X, Y, 0)) + 1]
#define PIXEL_COLOR_RED(X, Y) data[coord_gbr(Vect<int>(X, Y, 0)) + 2]

#define PIXEL_COLOR_BLUE_VECT(V) data[coord_gbr(V)]
#define PIXEL_COLOR_GREEN_VECT(V) data[coord_gbr(V) + 1]
#define PIXEL_COLOR_RED_VECT(V) data[coord_gbr(V) + 2]

#define NBR_RAYS 32
#define SCAL_BLENDER_KINECT 24.0f

namespace root {
    class Root {
    public:
        explicit Root(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &SP_frame_draw_);
        ~Root();
        virtual void search(float const &, int const &, Vect<float> const &);
        void bezier_curve(const int &);
        bool smoth(const float&);

        Vect<float> get_coord();

        std::vector< Vect <float> > vect_offset;
        std::vector< Vect <float> > vect_rot;

    protected:

        // coordinates of the root
        // coordonnées du noeud
        Vect<float> p;

        // frame to stude
        // référence à l'image qu'on étudie
        cv::Mat mat_frame;
        // the frame with draw of roots
        // l'image avec les dessins des noeuds
        QSharedPointer<cv::Mat> mat_frame_draw;

        float model_lenght_hips_spine;

    private:

        void move_the_circle(bool const &,  Vect<float> const &, float const &, int const &nbr_ray, int &);
        void weight(int const &, std::vector<int> &);
        void reverse(int const &, std::vector<int> &, std::vector<int> const &);
        bool ray_vs_arc(bool &, int const &black_arc, int const &, bool &, float &, float const &);
        void draw_rays(int const &, bool &, std::vector<int> &, Vect<float> &);
        void out_of_the_zone(int const&, int &, bool &, std::vector<int> &, std::vector<int> &, Vect<float> &);
        bool out_of_window(int &, std::vector<int> &, Vect<float> &, int const &);
        void explore_rays(bool &, int const &, int const &, float &, int &, bool &, std::vector<int> &, std::vector<int> &v, float &, float const &);
        // We explore all points along the ray
        // Nous testons tous les points situés sur le rayon
        void explore_circle(bool &, int const &, float const &, int const &, std::vector<int> &, std::vector<int> &, int &);

    };
}
#endif // ROOT_H
