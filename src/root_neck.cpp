#include "root_neck.h"

Neck::Neck(IplImage *frame_) : Root(frame_) {
}

void Neck::first_search(Vect<float> const &vect_neck_, Vect<float> const &vect_hips_) {
    s = Vect<float>(0.000000, -0.401210, 3.427901);
    p = vect_neck_;
    vect_hips = vect_hips_;
    lenght_neck_hips = vectors_maths::lenght(p, vect_hips);
}

// keep lenght between hips and neck
void Neck::bone() {

    Vect<float> u(p.x - vect_hips.x, p.y - vect_hips.y, 0);
    float k = lenght_neck_hips / vectors_maths::normal(u);
    p.x = k * u.x + vect_hips.x;
    p.y = k * u.y + vect_hips.y;
}
