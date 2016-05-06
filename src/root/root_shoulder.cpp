#include "root_shoulder.h"

namespace root {
    Shoulder::Shoulder(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : Root(mat_frame_, mat_frame_draw_) {
    }

    Shoulder::~Shoulder() {
    }

    void Shoulder::first_search(Vect<float> const &vect_neck_, Vect<float> const &vect_hips_, bool l_r_) {

        l_r = l_r_;
        Vect<float> v(0, 0, 0);

        vect_neck = vect_neck_;
        neck_to_hips = vect_hips_ - vect_neck;

        if(vectors_maths::normal(neck_to_hips) == 0.0f)
            return;

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

        Vect<float> i = v / vectors_maths::normal(v);
        Vect<float> u = vect_neck;

        u += neck_to_hips / (float)14.0;

        // A partir du point u, nous cherchons à sortir de la zone rouge, une fois la zone noire trouvée, nous sommes alors sur l'épaule
        // From the point u, we try to exit from the red area, once found the black area, then we are on the shoulder
        while(!control<float>(u)) {
            if (!(mat_frame.PIXEL_COLOR_RED_VECT(u)))
                break;
            u += i;
        }

        p = u;

        lenght_neck_shoulder = vectors_maths::lenght(p, vect_neck);
        init_angle = vectors_maths::angle_vects(vect_hips_ - vect_neck_, p - vect_neck_);

    }

    void Shoulder::bone() {

        Vect<float>t = vect_neck;
        t += neck_to_hips / (float)14.0;
        Vect<float> u(p.x - t.x, p.y - t.y, 0.0f);
        if(p.x - t.x == 0.0f && p.y - t.y == 0.0f)
            return;
        float k = lenght_neck_shoulder / vectors_maths::normal(u);
        if(k < 1.0f) {
            p.x = k * u.x + t.x;
            p.y = k * u.y + t.y;
        }

    }

    void Shoulder::search(float const &radius, int const &black_arc, Vect<float> vec_black_arc, Vect<float> neck, Vect<float> hips) {

        Vect<float> last_p = p;

        Root::search(radius, black_arc, vec_black_arc);

        if(init_angle - vectors_maths::angle_vects(hips - neck, p - neck) > .3f || init_angle - vectors_maths::angle_vects(hips - neck, p - neck) < -.3f)
            p = last_p;

    }

    void Shoulder::new_rot(Vect<float> const &hips, Vect<float> const &neck) {

        Vect<float> neck_to_hips = hips - neck;
        Vect<float> shoulder_to_neck = neck - p;
        float init_angle_cor;
        if(l_r)
            init_angle_cor = init_angle + PI / 4;
        else
            init_angle_cor = init_angle - PI / 4;
        vect_rot.push_back(Vect<float>(.0f, 180.0f * (init_angle_cor + vectors_maths::angle_vects(neck_to_hips, shoulder_to_neck)) / PI, .0f));

    }

}
