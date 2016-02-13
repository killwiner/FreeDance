#include "root_hand.h"

namespace root {

    void Hand::values_2D(Vect<float> const &elbow, Vect<float> const &shoulder, Vect<float> &shoulder_to_elbow_y_z, Vect<float> &shoulder_to_elbow_x_y, Vect<float> &hand_to_elbow_y_z, Vect<float> &hand_to_elbow_x_y) {
        Vect<float> p_x_y = vectors_maths::_3D_to_2D_xy(p);
        Vect<float> p_y_z = vectors_maths::_3D_to_2D_yz(p);
        p_y_z.z *= 2.0f;

        Vect<float> elbow_x_y = vectors_maths::_3D_to_2D_xy(elbow);
        Vect<float> elbow_y_z = vectors_maths::_3D_to_2D_yz(elbow);
        elbow_y_z.z *= 2.0f;

        shoulder_to_elbow_y_z = elbow_y_z - shoulder;
        shoulder_to_elbow_x_y = elbow_x_y - shoulder;
        hand_to_elbow_y_z = elbow_y_z - p_y_z;
        hand_to_elbow_x_y = elbow_x_y - p_x_y;
    }

    bool Hand::get_hand(int const &x, int const &y, Vect<float> const &elbow, Vect<float> const &shoulder) {

        if (SP_frame->PIXEL_COLOR_RED(x, y)) {

            p.x = (float)x;
            p.y = (float)y;

            Vect<float> shoulder_to_elbow_y_z, shoulder_to_elbow_x_y, hand_to_elbow_y_z, hand_to_elbow_x_y;

            values_2D(elbow, shoulder, shoulder_to_elbow_y_z, shoulder_to_elbow_x_y, hand_to_elbow_y_z, hand_to_elbow_x_y);

            init_angle_y_z = vectors_maths::angle_vects(shoulder_to_elbow_y_z, hand_to_elbow_y_z);
            init_angle_x_y = vectors_maths::angle_vects(shoulder_to_elbow_x_y, hand_to_elbow_x_y);

            return true;
        }
        return false;
    }

    Hand::Hand(QSharedPointer<IplImage> const &SP_frame_, QSharedPointer<IplImage> &SP_frame_draw_) : Root(SP_frame_, SP_frame_draw_) {
    }

    // Recherche les mains gauche et droite en partant du côté droit et gauche de l'image
    // Search hands from the sides of the picture
    void Hand::first_search(bool l_r, Vect<float> elbow, Vect<float> shoulder) {

        // right hand or left hand
        // main droite ou main gauche
        s = Vect<float>(.0f, 0.069508f, -2.310122f);
        l_r ? s.x = 1.345896 : -1.345896;


        if (!l_r == false) {

            for (int x = 0; x < WIDTH; ++x)
                for (int y = 0; y < HEIGHT; ++y)
                    if(get_hand(x, y, elbow, shoulder))
                        return;
        }
        else {
            for (int x = WIDTH - 1; x >= 0; --x)
                for (int y = 0; y < HEIGHT; ++y)
                    if(get_hand(x, y, elbow, shoulder))
                        return;
        }
    }

    void Hand::search(float const &radius, int const &black_arc, Vect<float> vec_black_arc, Vect<float> elbow) {

        Root::search(radius, black_arc, vec_black_arc);

        Vect<float> unit_dep = p - elbow;
        unit_dep.z = 0;
        unit_dep = unit_dep / vectors_maths::normal(unit_dep);
        Vect<float> ray = unit_dep * radius;

        if(vectors_maths::normal(unit_dep) == .0f)
            return;

        while(true) {

            Vect<float> v = p + ray;

            if(!control<float>(v)) {
                if(!SP_frame->PIXEL_COLOR_RED_VECT(v))
                    break;
            }
            else
                break;

            p = p + unit_dep;

        }
    }

    void Hand::new_rot(Vect<float> const &shoulder, Vect<float> const &elbow) {

        Vect<float> shoulder_to_elbow_y_z, shoulder_to_elbow_x_y, hand_to_elbow_y_z, hand_to_elbow_x_y;
        values_2D(elbow, shoulder, shoulder_to_elbow_y_z, shoulder_to_elbow_x_y, hand_to_elbow_y_z, hand_to_elbow_x_y);

        float init_angle_cor_y_z, init_angle_cor_x_y;
        init_angle_cor_y_z = init_angle_y_z;
        init_angle_cor_x_y = init_angle_x_y - PI / 2;

        vect_rot.push_back(Vect<float>(180.0f * (init_angle_cor_y_z - vectors_maths::angle_vects(hand_to_elbow_y_z, shoulder_to_elbow_y_z)) / PI,
                                       180.0f * (init_angle_cor_x_y + vectors_maths::angle_vects(hand_to_elbow_x_y, shoulder_to_elbow_x_y)) / PI, .0f));
    }
}
