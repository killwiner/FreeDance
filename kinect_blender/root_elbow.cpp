#include "root_elbow.h"

Elbow::Elbow(IplImage *frame_) : Root(frame_) {
}

void Elbow::first_search(Vect<float> const &vect_shoulder, Vect<float> const &vect_hand) {

    Vect<float> shoulder_to_hand = vect_hand - vect_shoulder;

    if(vect_hand.x == vect_shoulder.x || vect_hand.y == vect_shoulder.y)
        try {
            throw std::string("Division by 0 in root_elbow.");
        }
        catch(std::string const& str) {
            std::cerr << str << std::endl;
            return;
        }

    Vect<float> v(0, 0, 0);
    Vect<float> w(0, 0, 0);

    // we turn the vector on PI/2
    v = quick_rot(shoulder_to_hand, 0);

    Vect<float> h = v / normal(v);
    Vect<float> u = vect_shoulder;

    u += shoulder_to_hand / 2.0f;

    while(!control<float>(u + w)) {
        if (frame->PIXEL_COLOR_RED_VECT(u + v)) {
            p = u + w;
            return;
        }

        if (frame->PIXEL_COLOR_RED_VECT(u - v)) {
            p = u - w;
            return;
        }
        w += h;
    }
}
