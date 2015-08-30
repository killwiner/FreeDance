#include "root_shoulder.h"

Shoulder::Shoulder(IplImage *frame_) : Root(frame_) {
}

void Shoulder::first_search(Vect<float> const &vect_neck_, Vect<float> const &vect_hips_, bool l_r) {

    Vect<float> v(0, 0, 0);

    vect_neck = vect_neck_;
    neck_to_hips = vect_hips_ - vect_neck;

    if(vect_hips_.x == vect_neck.x || vect_hips_.y == vect_neck.y)
        try {
            throw std::string("Division by 0 in root_shoulder.");
        }
        catch(std::string const& str) {
            std::cerr << str << std::endl;
            return;
        }

    // is it the left shoulder or the right shoulder ?
    // s'agit-il de l'épaule droite ou de l'épaule gauche ?
    // nous pivotons le vecteur de PI/2 dans le sens direct ou indirect, suivant s'il s'agit de l'épaule gauche ou droite
    // we rotate the vector of PI / 2 in the direct or indirect way, following the case of the left or right shoulder
    if(!l_r)
        v = quick_rot(neck_to_hips, 0);
    else
        v = quick_rot(neck_to_hips, 1);

    Vect<float> i = v / normal(v);
    Vect<float> u = vect_neck;

    u += neck_to_hips / (float)14.0;

    // A partir du point u, nous cherchons à sortir de la zone rouge, une fois la zone noire trouvée, nous sommes alors sur l'épaule
    // From the point u, we try to exit from the red area, once found the black area, then we are on the shoulder
    while(!control<float>(u)) {
        if (!(frame->PIXEL_COLOR_RED_VECT(u)))
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
