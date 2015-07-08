#include "root_shoulder.h"

Shoulder::Shoulder() : Root() {
}

void Shoulder::first_search(Vect<float> neck, Vect<float> neck_to_hips, bool l_r) {

    Vect<float> v(0, 0);

    if(!l_r)
        v = quick_rot(neck_to_hips, 0);
    else
        v = quick_rot(neck_to_hips, 1);

    Vect<float> i = v / normal(v);
    Vect<float> u = neck;

    u += neck_to_hips / (float)14.0;

    while(!control<float>(u)) {
        if (!(frame->imageData[(int)(coord_gbr(u) + 2)]))
            break;
        u += i;
    }

    p = u;

}

