#include "root_hand.h"

Hand::Hand(IplImage *frame_) : Root(frame_) {

}

// Recherche les mains gauche et droite en partant du côté droit et gauche de l'image
// Search hands from the sides of the picture
void Hand::first_search(bool l_r, Vect<float> elbow, Vect<float> shoulder) {

    // right hand
    // main droite
    if (!l_r == false) {
        s = Vect<float>(-1.345896, 0.069508, -2.310122);

        for (int x = 0; x < WIDTH; ++x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->PIXEL_COLOR_RED(x, y)) {
                    p.x = (float)x;
                    p.y = (float)y;

                    Vect<float> p_x_y = p;
                    p_x_y.z = .0f;

                    Vect<float> p_y_z = p;
                    p_y_z.x = .0f;
                    p_y_z.z *= 2.0f;

                    Vect<float> elbow_x_y = elbow;
                    elbow_x_y.z = .0f;

                    Vect<float> elbow_y_z = elbow;
                    elbow_y_z.x = .0f;
                    elbow_y_z.z *= 2.0f;

                    Vect<float> shoulder_to_elbow_y_z = elbow_y_z - shoulder;
                    Vect<float> shoulder_to_elbow_x_y = elbow_x_y - shoulder;
                    Vect<float> hand_to_elbow_y_z = elbow_y_z - p_y_z;
                    Vect<float> hand_to_elbow_x_y = elbow_x_y - p_x_y;

                    init_angle_y_z = angle_vects(shoulder_to_elbow_y_z, hand_to_elbow_y_z);
                    init_angle_x_y = angle_vects(shoulder_to_elbow_x_y, hand_to_elbow_x_y);

                    return;
                }
    }
    else {
        s = Vect<float>(1.345896, 0.069508, -2.310122);
        for (int x = WIDTH - 1; x >= 0; --x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->PIXEL_COLOR_RED(x, y)) {
                    p.x = (float)x;
                    p.y = (float)y;

                    Vect<float> p_x_y = p;
                    p_x_y.z = .0f;

                    Vect<float> p_y_z = p;
                    p_y_z.x = .0f;
                    p_y_z.z *= 2.0f;

                    Vect<float> elbow_x_y = elbow;
                    elbow_x_y.z = .0f;

                    Vect<float> elbow_y_z = elbow;
                    elbow_y_z.x = .0f;
                    elbow_y_z.z *= 2.0f;

                    Vect<float> shoulder_to_elbow_y_z = elbow_y_z - shoulder;
                    Vect<float> shoulder_to_elbow_x_y = elbow_x_y - shoulder;
                    Vect<float> hand_to_elbow_y_z = elbow_y_z - p_y_z;
                    Vect<float> hand_to_elbow_x_y = elbow_x_y - p_x_y;

                    init_angle_y_z = angle_vects(shoulder_to_elbow_y_z, hand_to_elbow_y_z);
                    init_angle_x_y = angle_vects(shoulder_to_elbow_x_y, hand_to_elbow_x_y);

                    return;
                }
    }
}

void Hand::search(IplImage* frame_, float const &radius, int const &black_arc, Vect<float> vec_black_arc, Vect<float> elbow) {

    Root::search(frame_, radius, black_arc, vec_black_arc);

    Vect<float> unit_dep = p - elbow;
    unit_dep.z = 0;
    unit_dep = unit_dep / normal(unit_dep);
    Vect<float> ray = unit_dep * radius;

    if(normal(unit_dep) == .0f)
        return;

    while(true) {

        Vect<float> v = p + ray;

        if(!control<float>(v)) {
            if(!frame->PIXEL_COLOR_RED_VECT(v))
                break;
        }
        else
            break;

        p = p + unit_dep;

    }
}

void Hand::new_rot(Vect<float> const &shoulder, Vect<float> const &elbow) {

    Vect<float> p_x_y = p;
    p_x_y.z = .0f;

    Vect<float> p_y_z = p;
    p_y_z.x = .0f;
    p_y_z.z *= 2.0f;

    Vect<float> elbow_x_y = elbow;
    elbow_x_y.z = .0f;

    Vect<float> elbow_y_z = elbow;
    elbow_y_z.x = .0f;
    elbow_y_z.z *= 2.0f;

    Vect<float> shoulder_to_elbow_y_z = elbow_y_z - shoulder;
    Vect<float> shoulder_to_elbow_x_y = elbow_x_y - shoulder;
    Vect<float> hand_to_elbow_y_z = elbow_y_z - p_y_z;
    Vect<float> hand_to_elbow_x_y = elbow_x_y - p_x_y;

    float init_angle_cor_y_z, init_angle_cor_x_y;
    init_angle_cor_y_z = init_angle_y_z;
    init_angle_cor_x_y = init_angle_x_y - PI / 2;

    vect_rot.push_back(Vect<float>(180.0f * (init_angle_cor_y_z - angle_vects(hand_to_elbow_y_z, shoulder_to_elbow_y_z)) / PI,
                                   180.0f * (init_angle_cor_x_y + angle_vects(hand_to_elbow_x_y, shoulder_to_elbow_x_y)) / PI, .0f));
}
