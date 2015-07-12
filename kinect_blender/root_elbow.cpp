#include "root_elbow.h"

#include <stdio.h>

Elbow::Elbow() : Root() {
}

void Elbow::first_search(Vect<float> shoulder, Vect<float> shoulder_to_hand) {

    Vect<float> v(0, 0);
    Vect<float> w(0, 0);

    v = quick_rot(shoulder_to_hand, 0);

    Vect<float> i = v / normal(v);
    Vect<float> u = shoulder;

    u += shoulder_to_hand / 2.0f;

    while(!control<float>(u + w)) {
        if (frame->imageData[(int)(coord_gbr(u + w) + 2)]) {
            p = u + w;
            return;
        }

        if (frame->imageData[(int)(coord_gbr(u - w) + 2)]) {
            p = u - w;
            return;
        }
        w += i;
    }
}
