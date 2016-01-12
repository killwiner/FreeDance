#include "root_elbow.h"
#include <stdio.h>

namespace root {

    Elbow::Elbow(QSharedPointer<IplImage> const &SP_frame_) : Root(SP_frame_) {
    }

    void Elbow::first_search(Vect<float> const &vect_shoulder, Vect<float> const &vect_hand, Vect<float> const &vect_neck, bool l_r_) {
        l_r = l_r_;
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

        Vect<float> h = v / vectors_maths::normal(v);
        Vect<float> u = vect_shoulder;

        u += shoulder_to_hand / 2.0f;

        while(!control<float>(u + w)) {

            if (SP_frame->PIXEL_COLOR_RED_VECT(u + w))
                p = u + w;

            if (SP_frame->PIXEL_COLOR_RED_VECT(u - w))
                p = u - w;

            if (SP_frame->PIXEL_COLOR_RED_VECT(u - w) || SP_frame->PIXEL_COLOR_RED_VECT(u + w)) {

                lenght_elbow_hand = vectors_maths::lenght(p, vect_hand);

                Vect<float> p_x_y = p;
                Vect<float> p_y_z = p;
                p_x_y.z = .0f;
                p_y_z.x = .0f;

                init_angle_x_y = vectors_maths::angle_vects(vect_shoulder - vect_neck, p_x_y - vect_shoulder);
                init_angle_y_z = -vectors_maths::angle_vects(Vect<float>(.0f, 1.0f, .0f), p_y_z - Vect<float>(.0f, vect_shoulder.y, .0f));

                return;
            }

            w += h;
        }
    }

    void Elbow::search(Vect<float> const &shoulder, Vect<float> const &hand, Vect<float> const &hips) {

        Vect<float> ca = shoulder - hand;
        Vect<float> w = ca / vectors_maths::normal(ca);
        Vect<float> u(0, 0, 0);
        float epsilone = .001f;

        if(w.x == .0f && w.y == .0f)
            return;

        u.y = -w.x / (sqrt(w.x * w.x + w.y * w.y));

        if(w.x == .0f)
            return;

        u.x = -w.y * u.y / w.x;
        u.z = .0f;
        Vect<float> v = vectors_maths::cross_product(u, w);

        if(u.x == .0f)
            return;

        float gamma_v = u.x / (u.x * v.y - v.x * u.y);
        float gamma_w = u.x / (u.x * w.y - w.x * u.y);
        float lambda = gamma_w * w.z - gamma_v * v.z;

        Vect < Vect < float > > p1(Vect<float>(0.0f, 0.0f, 0.0f), Vect<float>(0.0f, 0.0f, 0.0f), Vect<float>(0.0f, 0.0f, 0.0f));
        Vect < Vect < float > > p2(Vect<float>(0.0f, 0.0f, 0.0f), Vect<float>(0.0f, 0.0f, 0.0f), Vect<float>(0.0f, 0.0f, 0.0f));

        p1.x.x = u.x;
        p1.x.y = u.y;
        p1.x.z = u.z;
        p1.y.x = v.x;
        p1.y.y = v.y;
        p1.y.z = v.z;
        p1.z.x = w.x;
        p1.z.y = w.y;
        p1.z.z = w.z;

        if(lambda == .0f)
            return;

        if(v.x * v.x > epsilone || v.y * v.y > epsilone) {

            p2.x.x = 1/u.x + (v.x * gamma_v * u.y / (u.x * u.x) + (gamma_v * v.z * u.y) * (gamma_v * v.x - gamma_w * w.x) / ((u.x * u.x) * lambda));
            p2.x.y = -gamma_v * gamma_v * u.y * v.z / (lambda * u.x) - gamma_v * u.y / u.x;
            p2.x.z = u.y * gamma_v * gamma_w * v.z / (u.x * lambda);
            p2.y.x = -v.x * gamma_v / u.x + (gamma_v * v.z) * (gamma_w * w.x - gamma_v * v.x) / (u.x * lambda);
            p2.y.y = gamma_v + gamma_v * gamma_v * v.z / lambda;
            p2.y.z = -gamma_w * gamma_v * v.z / lambda;
            p2.z.x = (gamma_v * v.x - gamma_w * w.x) / (u.x * lambda);
            p2.z.y = -gamma_v / lambda;
            p2.z.z = gamma_w / lambda;
        }
        else {
            p2.x.x = 1/u.x + gamma_w * u.y * w.x / (u.x * u.x);
            p2.x.y = gamma_w * u.y * w.z / u.x;
            p2.x.z = -gamma_w * u.y / u.x;
            p2.y.x = -gamma_w * w.x / u.x;
            p2.y.y =.0f;
            p2.y.z = gamma_w;
            p2.z.x = .0f;
            p2.z.y = 1.0f;
            p2.z.z = .0f;
        }

    //    printf("%f %f %f\n", p.x.x * u.x + p.x.y * v.x + p.x.z * w.x, p.y.x * u.x + p.y.y * v.x + p.y.z * w.x, p.z.x * u.x + p.z.y * v.x + p.z.z * w.x);
    //    printf("%f %f %f\n", p.x.x * u.y + p.x.y * v.y + p.x.z * w.y, p.y.x * u.y + p.y.y * v.y + p.y.z * w.y, p.z.x * u.y + p.z.y * v.y + p.z.z * w.y);
    //    printf("%f %f %f\n", p.x.x * u.z + p.x.y * v.z + p.x.z * w.z, p.y.x * u.z + p.y.y * v.z + p.y.z * w.z, p.z.x * u.z + p.z.y * v.z + p.z.z * w.z);

        float ray = lenght_elbow_hand * lenght_elbow_hand - (ca.x * ca.x + ca.y * ca.y) / 4;
        if (ray <= .0f)
            return;
        ray = sqrt(ray);

        Vect<float> n = vectors_maths::cross_product(p - shoulder, hips - shoulder);
        n = n / vectors_maths::normal(n);
        n = vectors_maths::matrix_3_3_product_1_3(p1, n);

        float t, at;

        Vect<float> r(.0f, .0f, .0f);
        bool start_r = false;

        if(n.x == .0f) {
            for(t = asin(-n.y); t < 2 * PI; t += PI / 10.0f)
                get_circle(shoulder, ray, t, p2, ca, start_r, r);
            p = r;
        }
        if(n.x > .0f) {
            at = atan(-n.y / n.x);
            for(t = (at <= .0f ? .0f : at); t < PI; t += PI / 10.0f)
                get_circle(shoulder, ray, t, p2, ca, start_r, r);
            p = r;
            for(t = PI; t < (at <= 2 * PI ? at : 2 * PI); t += PI / 10.0f)
                get_circle(shoulder, ray, t, p2, ca, start_r, r);
            p = r;
        }
        if(n.x < .0f) {
            at = atan(-n.y / n.x);
            for(t = 0; t < (at < PI ? at : PI); t += PI / 10.0f)
                get_circle(shoulder, ray, t, p2, ca, start_r, r);
            p = r;
            for(t = (at <= PI ? PI : at); t < 2 * PI; t += PI / 10.0f)
                get_circle(shoulder, ray, t, p2, ca, start_r, r);
            p = r;
        }
    }

    void Elbow::new_rot(Vect<float> const &neck, Vect<float> const &shoulder) {

        Vect<float> p_x_y = p;
        p_x_y.z = .0f;

        Vect<float> p_y_z = p;
        p_y_z.x = .0f;
        p_y_z.z *= 2.0f;

        Vect<float> neck_to_shoulder = shoulder - neck;
        Vect<float> elbow_to_shoulder_y_z = Vect<float>(.0f, 1.0f, .0f) - p_y_z;
        Vect<float> elbow_to_shoulder_x_y = shoulder - p_x_y;

        float init_angle_cor_y_z, init_angle_cor_x_y;
        init_angle_cor_y_z = init_angle_y_z - PI - PI / 8;
        init_angle_cor_x_y = init_angle_x_y - PI / 2 - PI / 8;

        vect_rot.push_back(Vect<float>(180.0f * (init_angle_cor_y_z - vectors_maths::angle_vects(Vect<float>(.0f, 1.0f, .0f), elbow_to_shoulder_y_z)) / PI,
                                       180.0f * (init_angle_cor_x_y + vectors_maths::angle_vects(neck_to_shoulder, elbow_to_shoulder_x_y)) / PI, .0f));
    }
}
