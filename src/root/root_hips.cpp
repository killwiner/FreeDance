#include "root_hips.h"

namespace root {
    Hips::Hips() : Root() {
    }

    void Hips::first_search() {

        int x, y;
        int x_l = 0, x_r = 0;

        s = Vect<float>(0.000000, -0.030254, 9.236752);

        // nous cherchons à partir de la ligne la plus basse le premier pixel rouge en partant de la gauche vers la droite
        // We seek from the lowest line the first red pixel from left to right
        for(x = 0; x < WIDTH; ++x)
            if (SP_frame->PIXEL_COLOR_RED(x, HEIGHT - 1))

                // nous continuons dans la zone rouge jusqu'à la zone noire. x_l prend alors la valeur des coordonnées horizontales du dernier point
                // We continue in the red zone until the black area. x_l then takes the value of the horizontal coordinates of the last point
                for(;x < WIDTH;++x)
                    if (SP_frame->PIXEL_COLOR_RED(x, HEIGHT - 1)) {
                        x_l = x;
                        // sortie de boulce
                        // exit the loop
                        x= WIDTH;
                    }

        // nous cherchons à partir de la ligne la plus basse le premier pixel rouge en partant de la droite vers la gauche
        // We seek from the lowest line the first red pixel from right to left
        for(x = WIDTH - 1; x >= 0; --x)
            if (SP_frame->PIXEL_COLOR_RED(x, HEIGHT - 1))

                // nous continuons dans la zone rouge jusqu'à la zone noire. x_l prend alors la valeur des coordonnées horizontales du dernier point
                // We continue in the red zone until the black area. x_l then takes the value of the horizontal coordinates of the last point
                for(; x > 0; --x)
                    if (SP_frame->PIXEL_COLOR_RED(x, HEIGHT - 1)) {
                        x_r = x;
                        // sortie de boulce
                        // exit the loop
                        x= 0;
                    }

        // nous continuons à remonter l'image
        // we keep up the image
        for(y = HEIGHT - 2; y >= 0; --y) {

            bool found = false;

            // nous approchons d'avantage x_l vers x_r tant que l'on est dans la zone rouge
            // we are approaching x_l to x_r as it is in the red zone
            for(int cursor = x_l; cursor <= x_r; ++cursor) {
                if (!SP_frame->PIXEL_COLOR_RED(cursor, y)) {

                    x_l = cursor;
                    found = true;
                    break;
                }
            }

            // nous approchons d'avantage x_r vers x_l tant que l'on est dans la zone rouge
            // we are approaching x_r to x_l as it is in the red zone
            for(int cursor = x_r; cursor >= x_l; --cursor) {
                if (!SP_frame->PIXEL_COLOR_RED(cursor, y)) {

                    x_r = cursor;
                    found = true;
                    break;
                }
            }

            // il n'y a plus de pixels rougles entre les deux jambes, nous sommes situés au niveau du bassin
            // we can't find red pixels between the two legs, we are located in the pelvis
            if(!found)
                break;
        }

        p.x = (float)x_l;
        p.y = (float)y;

        init_offset = p;
        vect_offset.push_back(Vect<float>(.0f, .0f, .0f));

    }

    void Hips::search(QSharedPointer<IplImage> const &frame_, float const &radius, int const &black_arc, Vect<float> vec_black_arc) {

        Root::search(frame_, radius, black_arc, vec_black_arc);

        // number of rays, the root is the center
        // nombre de rayons, le noeud étant le centre
        int nbr_rays = 32;

        float x1, x2;
        x1 = x2 = p.x;

        // We explore all rays
        // Nous testons tous les rayons
        for(int j = 0; j < nbr_rays; ++j) {

            float teta = (float)j * 2 * PI / (float)nbr_rays;

            // the point v is exploring all top of rays
            // Le point v explore tous les sommets des rayons
            Vect<float> v(p.x + radius * cosf(teta), p.y + radius * sinf(teta), 0);

            if(!control<float>(v))
                if(!SP_frame->PIXEL_COLOR_RED_VECT(v)) {
                    if(x1 > v.x)
                        x1 = v.x;
                    if(x2 < v.x)
                        x2 = v.x;

                }

        }

        float dep = (p.x - x1) - (x2 - x1) / 2;

            p.x -= dep;

    }

    void Hips::new_rot(Vect<float> const &neck) {

        Vect<float> neck_x_y, p_x_y;
        neck_x_y = neck;
        p_x_y = p;
        neck_x_y.z = .0f;
        p_x_y.z = .0f;

        Vect<float> hips_to_neck_x_y = neck_x_y - p_x_y;

        vect_rot.push_back(Vect<float>(.0f, .0f, 180.0f * vectors_maths::angle_vects(Vect<float>(.0f, -1.0f, .0f), hips_to_neck_x_y) / PI));
        vect_offset.push_back(Vect<float>((p.x - init_offset.x)/10.0f, (p.z - init_offset.z)/10.0f, (p.y - init_offset.y)/10.0f));
    }
}
