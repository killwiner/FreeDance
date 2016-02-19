#include "root_head.h"

namespace root {

    Head::Head(QSharedPointer<IplImage> const &SP_frame_, QSharedPointer<IplImage> &SP_frame_draw_) : Root(SP_frame_, SP_frame_draw_), m_lines(8) {
    }

    bool Head::web(Vect<float> &top, float &n_top_x, float const &y, float const &web_surface, float &web_surface_last, float &num_webs,
                   Vect<float> &bottom, float const &n_bottom_x,
                   Vect<float> &right, Vect<float> &left, Vect<float> &neck) {
        // if the web is growing more than 13% and we exceeded 6 bands
        // is la bande est plus importante de 13% que la précédente et que nous avons dépassé les 6 bandes
        if (web_surface > web_surface_last * 1.3 && num_webs > 4) {

                bottom.y = y - m_lines;
                if(n_top_x == 0)
                    top.x = 0;
                else
                    top.x = top.x / n_top_x;

                if(n_bottom_x == 0)
                    bottom.x = 0;
                else
                    bottom.x = bottom.x / n_bottom_x;
                neck.y = y;
                neck.x = bottom.x;
                right.y = left.y = top.y + (bottom.y - top.y) / 2;
                p = vectors_maths::cross_2D(left, right, bottom, top);

                lenght_head_neck = vectors_maths::lenght(p, neck);
                return true;
            }
        return false;
    }

    bool Head::every_m_lines(Vect<float> &top, float &n_top_x, float const &y, float &web_width, float &num_webs, bool const &start, bool &top_flag, Vect<float> &right,
                             Vect<float> &left, float const &right_last_x, float const &left_last_x,
                             float &web_surface, float &web_surface_last, Vect<float> &bottom, float &n_bottom_x, Vect<float> &neck) {
        // every m_lines lines
        // toutes les m_lines lines
        if (web_width >= m_lines && start) {

            // fin du calcul de la moyenne horizontale du haut de la tête
            // end of averaging the horizontal top of the head
            top_flag = false;

            // calcule à nouveau la largeur de la nouvelle bande
            // Calculate the new bandwidth again
            web_width = 0;

            // num_webs is the number of bands with width = m_lines
            ++num_webs;

            if(web(top, n_top_x, y, web_surface, web_surface_last, num_webs, bottom, n_bottom_x, right, left, neck))
                return true;

            right.x = right_last_x;
            left.x = left_last_x;

            web_surface_last = web_surface;
            web_surface = 0;

            bottom.x = 0;
            n_bottom_x = 0;
        }
        return false;
    }


    void Head::along_line(bool const &top_flag, bool &start, float &web_width, Vect<float> &v, float const &y, float &right_last_x, float &left_last_x,
                          Vect<float> &top, float &n_top_x, Vect<float> &bottom, float &n_bottom_x, float &web_surface) {
        // Recherche le long de la ligne X
        // Search along the line X
        for(float x = 0; x < WIDTH; ++x) {

            // Si le pixel est sur la partition recherchée
            // If the point is on the right area
            if (SP_frame->PIXEL_COLOR_RED(x, y)) {

                if (start == false)
                    web_width = 0;

                start = true;

                // v take the point coordinates
                // v prend les coordonnées du point
                v.x = x;
                v.y = y;

                // on décalle left_last_x encore plus à gauche
                // we move left_last_x more to the left
                if(v.x < left_last_x)
                    left_last_x = v.x;

                // on décalle right_last_x encore plus à droite
                // we move right_last_x more to the right
                if(v.x > right_last_x)
                    right_last_x = v.x;

                // take the uppermost y coordinates for the point 'top'
                // 'top' prend les coordonnées les plus hautes y
                if(is_null<float>(top))
                    top.y = y;

                // tant qu'on se situe dans la première bande on calcule la moyenne horizontale du haut de la tête
                if (top_flag == true) {
                    top.x += v.x;
                    ++n_top_x;
                }

                bottom.x += v.x;
                ++n_bottom_x;

                // surface de la bande
                // web surface
                ++web_surface;
            }
        }
    }

    bool Head::search_from_up_to_down(Vect<float> &neck) {

        Vect<float> v(WIDTH, HEIGHT, 0);
        Vect<float> top(WIDTH, HEIGHT, 0); // the coordinates of the uppermost point on the head
        Vect<float> bottom; // the coordinates of the lowest point on the head
        float n_bottom_x = 0;
        float web_width = .0f, num_web = .0f;
        bool start = false;
        bool top_flag = true;
        float left_last_x = WIDTH, right_last_x = 0;
        Vect<float> left;
        Vect<float> right;
        float web_surface = 0, web_surface_last = 0;
        float n_top_x = 0;

        for(float y = 0; y < HEIGHT; ++y) {

            if(every_m_lines(top, n_top_x, y, web_width, num_web, start, top_flag, right, left, right_last_x, left_last_x, web_surface, web_surface_last, bottom, n_bottom_x, neck))
                return true;
            along_line(top_flag, start, web_width, v, y, right_last_x, left_last_x, top, n_top_x, bottom, n_bottom_x, web_surface);

            ++web_width;
        }
    }

    Vect<float> Head::first_search() {

        Vect<float> neck;
        s = Vect<float>(0.000000, 0.084560, 1.094051);
        //s = Vect<float>(0.0f, 0.0f, 0.0f);

        // recherche verticale de haut vers le bas dans l'image
        // search from up to down in the picture
        if(search_from_up_to_down(neck))
            return neck;

        lenght_head_neck = vectors_maths::lenght(p, neck);
        return neck;
    }

    // keep lenght between head and neck
    void Head::bone(Vect<float> const& vect_neck) {

        Vect<float> u(p.x - vect_neck.x, p.y - vect_neck.y, 0);
        float k = lenght_head_neck / vectors_maths::normal(u);
        p.x = k * u.x + vect_neck.x;
        p.y = k * u.y + vect_neck.y;
    }

    void Head::new_rot(Vect<float> const &hips, Vect<float> const &neck) {
        Vect<float> hips_to_neck = neck - hips;
        Vect<float> neck_to_head = p - neck;
        vect_rot.push_back(Vect<float>(.0f, 180.0f * vectors_maths::angle_vects(hips_to_neck, neck_to_head) / PI, .0f));
    }

}
