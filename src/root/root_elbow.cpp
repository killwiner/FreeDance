#include "root_elbow.h"
#include <stdio.h>

using namespace std;

namespace root {

    Elbow::Elbow(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : Root(mat_frame_, mat_frame_draw_) {
    }

    Elbow::~Elbow() {
    }

    void Elbow::find_elbow(Vect<float> const &u, Vect<float> &w,Vect<float> const &vect_shoulder, Vect<float> const &vect_hand, Vect<float> const &vect_neck, Vect<float> const &h) {

        while(!control<float>(u + w)) {

        if (mat_frame.PIXEL_COLOR_RED_VECT(u + w))
            p = u + w;

        if (mat_frame.PIXEL_COLOR_RED_VECT(u - w))
            p = u - w;

        if (mat_frame.PIXEL_COLOR_RED_VECT(u - w) || mat_frame.PIXEL_COLOR_RED_VECT(u + w)) {

            lenght_elbow_hand = vectors_maths::lenght(p, vect_hand);

            Vect<float> p_x_y = vectors_maths::_3D_to_2D_xy(p);
            Vect<float> p_y_z = vectors_maths::_3D_to_2D_yz(p);

            init_angle_x_y = vectors_maths::angle_vects(vect_shoulder - vect_neck, p_x_y - vect_shoulder);
            init_angle_y_z = -vectors_maths::angle_vects(Vect<float>(.0f, 1.0f, .0f), p_y_z - Vect<float>(.0f, vect_shoulder.y, .0f));

            return;
        }

        w += h;
    }
}

    void Elbow::first_search(Vect<float> const &vect_shoulder, Vect<float> const &vect_hand, Vect<float> const &vect_neck, bool l_r_) {

        l_r = l_r_;
        Vect<float> shoulder_to_hand = vect_hand - vect_shoulder;

        if(vect_hand.x == vect_shoulder.x || vect_hand.y == vect_shoulder.y)
            try {
                throw string("Division by 0 in root_elbow. T0");
            }
            catch(string const& str) {
                cerr << str << endl;
                return;
            }

        Vect<float> v;
        Vect<float> w;

        // we turn the vector on PI/2
        v = quick_rot(shoulder_to_hand, 0);

        Vect<float> h = v / vectors_maths::normal(v);
        Vect<float> u = vect_shoulder;

        u += shoulder_to_hand / 2.0f;

        find_elbow(u, w, vect_shoulder, vect_hand, vect_neck, h);

    }

    Vect < Vect < float > > Elbow::make_matrix(Vect<float> const &u,Vect<float> const &v, Vect<float> const &w,float const &gamma_v,float const &gamma_w,float const &lambda) {

        Vect < Vect < float > > p2(V_NULL, V_NULL, V_NULL);

        if(v.x * v.x > EPSILONE || v.y * v.y > EPSILONE) {

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

        return p2;
    }

    Vect<float> Elbow::make_vector_n(Vect<float>const &p, Vect<float> const &shoulder, Vect<float> const &hips, Vect < Vect < float > > const &p1) {

        Vect<float> n = vectors_maths::cross_product(p - shoulder, hips - shoulder);
        n = n / vectors_maths::normal(n);
        n = vectors_maths::matrix_3_3_product_1_3(p1, n);

        return n;

    }

    void Elbow::n_x_cases(Vect<float> const &shoulder, Vect < Vect < float > > const &p2, Vect<float> const &ca, Vect<float> const &n) {

        float ray = lenght_elbow_hand * lenght_elbow_hand - (ca.x * ca.x + ca.y * ca.y) / 4;
        if (ray <= .0f)
            throw string("Division by 0 in root_elbow. T5");
        ray = sqrt(ray);

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

    void Elbow::search(Vect<float> const &shoulder, Vect<float> const &hand, Vect<float> const &hips) {

        Vect<float> ca = shoulder - hand;
        Vect<float> w = ca / vectors_maths::normal(ca);
        Vect<float> u;

        try {

            // to escape division by zero
            // on échappe à la division par zéro
            if(w.x == .0f && w.y == .0f)
                throw string("Division by 0 in root_elbow. T1");

            u.y = -w.x / (sqrt(w.x * w.x + w.y * w.y));

            // to escape division by zero
            // on échappe à la division par zéro
            if(w.x == .0f)
                throw string("Division by 0 in root_elbow. T2");

            u.x = -w.y * u.y / w.x;
            u.z = .0f;
            Vect<float> v = vectors_maths::cross_product(u, w);

            if(u.x == .0f)
                throw string("Division by 0 in root_elbow. T3");

            float gamma_v = u.x / (u.x * v.y - v.x * u.y);
            float gamma_w = u.x / (u.x * w.y - w.x * u.y);
            float lambda = gamma_w * w.z - gamma_v * v.z;

            Vect < Vect < float > > p1(u, v, w);
            Vect < Vect < float > > p2(V_NULL, V_NULL, V_NULL);

            if(lambda == .0f)
                throw string("Division by 0 in root_elbow. T4");

            p2 = make_matrix(u, v, w, gamma_v, gamma_w, lambda);

            Vect<float> n = make_vector_n(p, shoulder, hips, p1);

            n_x_cases(shoulder, p2, ca, n);

        }
        catch(string const& str) {
            cerr << str << endl;
            return;
        }
    }

    void Elbow::new_rot(Vect<float> const &neck, Vect<float> const &shoulder) {

        Vect<float> p_x_y = vectors_maths::_3D_to_2D_xy(p);
        Vect<float> p_y_z = vectors_maths::_3D_to_2D_yz(p);
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
