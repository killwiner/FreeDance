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

#include "root_hips.h"
#include <QDebug>

using namespace std;

namespace root {

    Hips::Hips(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : Root(mat_frame_, mat_frame_draw_) {
    }

    Hips::~Hips() {
    }

    void Hips::first_pixel_l2r(int &x_l) {

        int x;

        // nous cherchons à partir de la ligne la plus basse le premier pixel rouge en partant de la gauche vers la droite
        // We seek from the lowest line the first red pixel from left to right
        for(x = 0; x < WIDTH; ++x)
            if (mat_frame.PIXEL_COLOR_RED(x, HEIGHT - 1))

                // nous continuons dans la zone rouge jusqu'à la zone noire. x_l prend alors la valeur des coordonnées horizontales du dernier point
                // We continue in the red zone until the black area. x_l then takes the value of the horizontal coordinates of the last point
                for(;x < WIDTH;++x)
                    if (mat_frame.PIXEL_COLOR_RED(x, HEIGHT - 1)) {
                        x_l = x;
                        // sortie de boulce
                        // exit the loop
                        x= WIDTH;
                    }
    }

    void Hips::first_pixel_r2l(int &x_r) {

        int x;

        // nous cherchons à partir de la ligne la plus basse le premier pixel rouge en partant de la droite vers la gauche
        // We seek from the lowest line the first red pixel from right to left
        for(x = WIDTH - 1; x >= 0; --x)
            if (mat_frame.PIXEL_COLOR_RED(x, HEIGHT - 1))

                // nous continuons dans la zone rouge jusqu'à la zone noire. x_l prend alors la valeur des coordonnées horizontales du dernier point
                // We continue in the red zone until the black area. x_l then takes the value of the horizontal coordinates of the last point
                for(; x > 0; --x)
                    if (mat_frame.PIXEL_COLOR_RED(x, HEIGHT - 1)) {
                        x_r = x;
                        // sortie de boulce
                        // exit the loop
                        x= 0;
                    }
    }

    bool Hips::x_l_move_to_x_r(const int &y, int &x_l, int const &x_r) {
        // nous approchons d'avantage x_l vers x_r tant que l'on est dans la zone rouge
        // we are approaching x_l to x_r as it is in the red zone
        for(int cursor = x_l; cursor <= x_r; ++cursor) {
            if (!mat_frame.PIXEL_COLOR_RED(cursor, y)) {

                x_l = cursor;
                return true;
            }
        }
        return false;
    }

    bool Hips::x_r_move_to_x_l(const int &y, int &x_r, int const &x_l) {

        // nous approchons d'avantage x_r vers x_l tant que l'on est dans la zone rouge
        // we are approaching x_r to x_l as it is in the red zone
        for(int cursor = x_r; cursor >= x_l; --cursor) {
            if (!mat_frame.PIXEL_COLOR_RED(cursor, y)) {

                x_r = cursor;
                return true;
            }
        }
        return false;
    }

    int Hips::along_lenght(int &x_l, int &x_r) {

        int y;

        // nous continuons à remonter l'image
        // we keep up the image
        for(y = HEIGHT - 2; y >= 0; --y) {

            bool found_l = false;
            bool found_r = false;

            found_l = x_l_move_to_x_r(y, x_l, x_r);
            found_r = x_r_move_to_x_l(y, x_r, x_l);

            // il n'y a plus de pixels rougles entre les deux jambes, nous sommes situés au niveau du bassin
            // we can't find red pixels between the two legs, we are located in the pelvis
            if(!found_l && !found_r)
                return y;
        }
    }

    void Hips::all_rays(int const &nbr_rays, float &x1, float &x2, float const &radius) {
        // We explore all rays
        // Nous testons tous les rayons
        for(int j = 0; j < nbr_rays; ++j) {

            float teta = (float)j * 2 * PI / (float)nbr_rays;

            // the point v is exploring all top of rays
            // Le point v explore tous les sommets des rayons
            Vect<float> v(p.x + radius * cosf(teta), p.y + radius * sinf(teta), 0);

            if(!control<float>(v))
                if(!mat_frame.PIXEL_COLOR_RED_VECT(v)) {
                    if(x1 > v.x)
                        x1 = v.x;
                    if(x2 < v.x)
                        x2 = v.x;
                }
        }
    }

    void Hips::first_search() {

        int x_l = 0, x_r = 0;

        s = Vect<float>(0.000000, -0.030254, 9.236752);

        first_pixel_l2r(x_l);
        first_pixel_r2l(x_r);
        p.y = (float)along_lenght(x_l, x_r);
        p.x = (float)x_l;

        init_offset = p;
        vect_offset.push_back(Vect<float>(.0f, .0f, .0f));

    }

    void Hips::search(float const &radius, int const &black_arc, Vect<float> vec_black_arc) {

        Root::search(radius, black_arc, vec_black_arc);

        // number of rays, the root is the center
        // nombre de rayons, le noeud étant le centre
        int nbr_rays = 32;

        float x1, x2;
        x1 = x2 = p.x;

        all_rays(nbr_rays, x1, x2, radius);

        float dep = (p.x - x1) - (x2 - x1) / 2;

        p.x -= dep;

    }

    void Hips::new_rot(Vect<float> const &neck) {

        // export rotation
        Vect<float> spin = p;
        spin.y -= model_lenght_hips_spine;
        Vect<float> s = spin - neck;

        try {
            if(vectors_maths::normal(s))
                vect_rot.push_back(Vect<float>(.0f, .0f, 180.0f / PI * asin(s.x / vectors_maths::normal(s))));
            else {
                vect_rot.push_back(Vect<float>(.0f, .0f, .0f));
                throw "(root_hips) division by 0";
            }
        }
        catch ( const exception &e )
        {
            cerr << "(Run) Exception caught !!" << endl;
            cerr << e.what() << endl;
            throw;
        }

        // export offset
        Vect<float> blend_loc = (p - init_offset) / 24.0f;
        blend_loc.y *= -1.0f;
        vect_offset.push_back(blend_loc);
    }
}
