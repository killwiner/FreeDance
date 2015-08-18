#include "root_shoulder.h"

Shoulder::Shoulder(IplImage *frame_) : Root(frame_) {
}

void Shoulder::first_search(Vect<float> const &vect_neck_, Vect<float> const &vect_hips_, bool l_r) {

    Vect<float> v(0, 0, 0);

    vect_neck = vect_neck_;
    neck_to_hips = vect_hips_ - vect_neck;

    if(!l_r)
        v = quick_rot(neck_to_hips, 0);
    else
        v = quick_rot(neck_to_hips, 1);

    Vect<float> i = v / normal(v);
    Vect<float> u = vect_neck;

    u += neck_to_hips / (float)14.0;

    while(!control<float>(u)) {
        if (!(frame->imageData[(int)(coord_gbr(u) + 2)]))
            break;
        u += i;
    }

    p = u;

    lenght_neck_shoulder = lenght(p, vect_neck);
}

void Shoulder::bone() {
    Vect<float>t = vect_neck;
    t += neck_to_hips / (float)14.0;
    Vect<float> u(p.x - t.x, p.y - t.y, 0.0f);
    float k = lenght_neck_shoulder / normal(u);
    if(k < 1.0f) {
        p.x = k * u.x + t.x;
        p.y = k * u.y + t.y;
    }
}
