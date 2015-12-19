#include "root_head.h"

Head::Head(IplImage *frame_) : Root(frame_) {
}

Vect<float> Head::first_search() {

    Vect<float> v(WIDTH, HEIGHT, 0);
    Vect<float> top(WIDTH, HEIGHT, 0); // the coordinates of the uppermost point on the head
    Vect<float> bottom(0, 0, 0); // the coordinates of the lowest point on the head
    Vect<float> left(0, 0, 0);
    Vect<float> right(0, 0, 0);
    Vect<float> neck(0, 0, 0);

    float web_surface = 0, web_width = 0, web_surface_last = 0, num_webs = 0;
    bool top_flag = true, start = false;
    float n_top_x = 0, n_bottom_x = 0;
    float left_last_x = WIDTH, right_last_x = 0;

    s = Vect<float>(0.000000, 0.084560, 1.094051);
    //s = Vect<float>(0.0f, 0.0f, 0.0f);

    // recherche verticale de haut vers le bas dans l'image
    // search from up to down in the picture
    for(float y = 0; y < HEIGHT; ++y) {

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
                    return neck;
                }

            right.x = right_last_x;
            left.x = left_last_x;

            web_surface_last = web_surface;
            web_surface = 0;

            bottom.x = 0;
            n_bottom_x = 0;
        }

        // Recherche le long de la ligne X
        // Search along the line X
        for(float x = 0; x < WIDTH; ++x) {

            // Si le pixel est sur la partition recherchée
            // If the point is on the right area
            if (frame->PIXEL_COLOR_RED(x, y)) {

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
        ++web_width;
    }

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
