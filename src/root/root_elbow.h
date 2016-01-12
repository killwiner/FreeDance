#ifndef ROOT_ELBOW_H
#define ROOT_ELBOW_H

#include "root.h"

namespace root {
    class Elbow : public Root {
    public:
        explicit Elbow(QSharedPointer<IplImage> const &);
        void first_search(Vect<float> const &vect_shoulder, Vect<float> const &vect_hand, Vect<float> const &vect_neck, bool l_r_);
        void search(Vect<float> const &shoulder, Vect<float> const &hand, Vect<float> const &hips);
        void new_rot(Vect<float> const&, Vect<float> const&);

        std::vector< Vect <float> > vect_rot;

    private:
        void get_circle(Vect<float> shoulder, float ray, float t, Vect< Vect <float> > p2, Vect<float> ca, bool &start_r, Vect<float> &r);
        float lenght_elbow_hand;
        float init_angle_x_y, init_angle_y_z;
        bool l_r;
    };

    inline void Elbow::get_circle(Vect<float> shoulder, float ray, float t, Vect< Vect <float> > p2, Vect<float> ca, bool &start_r, Vect<float> &r) {
        Vect<float> circle(ray * cosf(t), ray * sinf(t), .0f);
        circle = vectors_maths::matrix_3_3_product_1_3(p2, circle);
        circle += shoulder;
        circle.x -= ca.x / 2;
        circle.y -= ca.y / 2;

        if(control(circle))
            return;
        if(!SP_frame->PIXEL_COLOR_RED_VECT(circle))
            return;

        if(!start_r) {
            start_r = true;
            r = circle;
        }
        if((p.x - r.x) * (p.x - r.x) + (p.y - r.y) * (p.y - r.y) > (p.x - circle.x) * (p.x - circle.x) + (p.y - circle.y) * (p.y - circle.y))
            r = circle;
    }
}
#endif // ROOT_ELBOW_H
