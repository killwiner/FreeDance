#include "root_hand.h"
#include <iostream>

Hand::Hand(IplImage *frame_) : Root(frame_) {

}

// Recherche les mains gauche et droite en partant du côté droit et gauche de l'image
// Search hands from the sides of the picture
void Hand::first_search(bool l_r) {

    // right hand
    // main droite
    if (!l_r == false) {
        s = Vect<float>(-1.345896, 0.069508, -2.310122);

        for (int x = 0; x < WIDTH; ++x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->PIXEL_COLOR_RED(x, y)) {
                    p.x = (float)x;
                    p.y = (float)y;
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

        std::cout << "yooo : " << p.x << " " << p.y << " " << p.z << std::endl;
    }
}
