#include "root.h"
#include <QDebug>

using namespace std;

namespace root {

    // constructor
    Root::Root(cv::Mat const &mat_frame_, QSharedPointer<cv::Mat> &mat_frame_draw_) : mat_frame(mat_frame_), mat_frame_draw(mat_frame_draw_) {
    }

    Root::~Root() {
    }

    Vect<float> Root::get_coord() {
        return p;
    }

    void Root::move_the_circle(bool const &black_arc_flag, Vect<float> const &vec_black_arc, float const &radius, int const &nbr_rays, int &total_black_ray) {

        if(!control<float>(p))
            if(mat_frame.PIXEL_COLOR_RED_VECT(p)) {
                if(!black_arc_flag) {

                    p.x += vec_black_arc.x * (radius * nbr_rays - total_black_ray) / (nbr_rays * radius);
                    p.y += vec_black_arc.y * (radius * nbr_rays - total_black_ray) / (nbr_rays * radius);

                }
                else {

                    p.x -= vec_black_arc.x * (radius * nbr_rays - total_black_ray) / (nbr_rays * radius);
                    p.y -= vec_black_arc.y * (radius * nbr_rays - total_black_ray) / (nbr_rays * radius);

                }
            }
    }

    // for all rays, *it is the weight
    // pour tous les rayons, *it représente le poids
    void Root::weight(int const &nbr_rays, vector<int> &vect_rays) {

        Vect<float> r(0, 0, 0);

        for (std::vector<int>::iterator it = vect_rays.begin(); it != vect_rays.end(); ++it) {

            // r is the vector to move the root into the right area with a speed proportional to the weight
            // r est le vecteur de déplacement du noeud vers l'intérieur de la partition avec une vitesse proportionnelle au poids
            r.x -= (float)*it / (float)nbr_rays * cosf((float)(it - vect_rays.begin()) * PI * 2 / (float)nbr_rays);
            r.y -= (float)*it / (float)nbr_rays * sinf((float)(it - vect_rays.begin()) * PI * 2 / (float)nbr_rays);

        }

        p += r;
    }

    // reverse the direction when the center of the circle is out from the right_zone
    // inverse la direction lorsque le centre du cercle est en dehors de la partition
    void Root::reverse(int const &nbr_rays, vector<int> &vect_rays, vector<int> const &vect_rays_op) {

        if(!control<float>(p))
            if(!mat_frame.PIXEL_COLOR_RED_VECT(p))
                for (std::vector<int>::iterator it = vect_rays.begin(); it != vect_rays.end(); ++it) {
                    if(vect_rays_op.at(it - vect_rays.begin())) {
                        if(it - vect_rays.begin() < nbr_rays / 2)
                            vect_rays.at(it - vect_rays.begin() + nbr_rays / 2) = 0;
                        else
                            vect_rays.at(it - vect_rays.begin() - nbr_rays / 2) = 0;
                        *it = -(*it);
                    }
                }

    }

    // we stop the loop when the arc out of the right area is bigger than black_arc
    // Lorsque l'arc de cercle en dehors de la partition est suffisemment grand, nous arrêtons la boucle principale
    bool Root::ray_vs_arc(bool &black_arc_flag, int const &black_arc, int const &black_ray, bool &black_ray_buff, float &ray, float const &radius) {

        if(black_ray > black_arc) {
            black_arc_flag = true;
            // to exit this loop
            ray = radius;
            black_ray_buff = true;
            return true;
        }

        return false;
    }

    // We draw rays in a white color
    // Nous dessinons les rayons en blanc
    void Root::draw_rays(int const &p_ray, bool &black_ray_buff, vector<int> &vect_rays_op, Vect<float> &v) {

        vect_rays_op.at(p_ray) += 1;
        black_ray_buff = true;
        mat_frame_draw->PIXEL_COLOR_BLUE_VECT(v) = 255;
        mat_frame_draw->PIXEL_COLOR_GREEN_VECT(v) = 255;

    }

    // We are out of the right zone
    // Nous sommes en dehors de la partition
    void Root::out_of_the_zone(int const & p_ray, int &black_ray, bool &black_ray_buff, vector<int> &vect_rays, vector<int> &vect_rays_op, Vect<float> &v) {
        if (!mat_frame.PIXEL_COLOR_RED_VECT(v)) {
            mat_frame_draw->PIXEL_COLOR_GREEN_VECT(v) = 255;

            ++black_ray;

            // the ray(j) is turning more heavy
            // le rayon(j) devient plus lours
            vect_rays.at(p_ray) += 1;

        }
        else
            draw_rays(p_ray, black_ray_buff, vect_rays_op, v);
    }

    // We are out of the window, then we are in black zone out of the right area
    // Nous sommes en dehors de la fenêtre, donc nous sommes en dehors de la partition
    bool Root::out_of_window(int &black_ray, vector<int> &vect_rays, Vect<float> &v, int const &p_ray) {
        if(control<float>(v)) {

            ++black_ray;

            // the ray(j) is turning more heavy
            // le rayon(j) devient plus lours
            vect_rays.at(p_ray) += 1;
            return true;
        }
        return false;
    }

    void Root::explore_rays(bool &black_arc_flag, int const &black_arc, int const &nbr_rays, float &teta, int &black_ray, bool &black_ray_buff, vector<int> &vect_rays, vector<int> &vect_rays_op, float &ray, float const &radius) {

        // We explore all rays
        // Nous testons tous les rayons
        for(int j = 0; j < nbr_rays; ++j) {

            teta = (float)j * 2 * PI / (float)nbr_rays;

            // the point v is exploring all rays
            // Le point v explore tous les rayons
            Vect<float> v(p.x + ray * cosf(teta), p.y + ray * sinf(teta), 0);

            if(out_of_window(black_ray, vect_rays, v, j))
                continue;
            out_of_the_zone(j, black_ray, black_ray_buff, vect_rays, vect_rays_op, v);

            if(!control<float>(p))
                if(!mat_frame.PIXEL_COLOR_RED_VECT(p))
                    continue;

            if(ray_vs_arc(black_arc_flag, black_arc, black_ray, black_ray_buff, ray, radius))
                break;

        }
    }

    // We explore all points along the ray
    // Nous testons tous les points situés sur le rayon
    void Root::explore_circle(bool &black_arc_flag, int const &black_arc, float const &radius, int const &nbr_rays, vector<int> &vect_rays, vector<int> &vect_rays_op, int &total_black_ray) {

        //teta is the ray's angle
        // teta représente l'angle du rayon
        float teta = 0;

        // black_ray, number of points along the ray and out of the right area
        // black_ray, nombre de points le long du rayon et en dehors de la partition
        int black_ray = 0;
        bool black_ray_buff = false;

        for(float ray = 1.0f; ray < radius || !black_ray_buff; ray += 1.0f) {

            if(ray >= radius && !black_ray_buff)
                break;

            total_black_ray += black_ray;
            black_ray = 0;

            explore_rays(black_arc_flag, black_arc, nbr_rays, teta, black_ray, black_ray_buff, vect_rays, vect_rays_op, ray, radius);

        }
    }

    // The root will move to stay inside the right zone
    // Le noeud se déplace pour rester dans la bonne partition
    // black_arc, lenght of the arc that is out from the right area
    // black_arc, détermine la longueur de l'arc de cercle en dehors de la partition
    // radius, the man lenght for the rays
    // radius, longueur maximale des rayons
    void Root::search(float const &radius, int const &black_arc, Vect<float> const &vec_black_arc) {

        int total_black_ray = 0;

        // number of rays, the root is the center
        // nombre de rayons, le noeud étant le centre
        int nbr_rays = NBR_RAYS;

        // vect_rays, vector with weight of rays. A ray is heavy when it's very out from the right area
        // vect_rays, vecteur comprenant les poids des rayons. Un rayon est de poid ford lorsqu'il est très en dehors de la partition
        vector<int> vect_rays(nbr_rays, 0);
        vector<int> vect_rays_op(nbr_rays, 0);

        bool black_arc_flag = false;

        explore_circle(black_arc_flag, black_arc, radius, nbr_rays, vect_rays, vect_rays_op, total_black_ray);
        reverse(nbr_rays, vect_rays, vect_rays_op);
        weight(nbr_rays, vect_rays);
        move_the_circle(black_arc_flag, vec_black_arc, radius, nbr_rays, total_black_ray);

    }

    //smoth all coordinates
    bool Root::smoth(const float &epsi) {

        vector< Vect<double> > sum_points;
        vector<int> nbr_points;

        if(vect_offset.empty())
            return true;

        sum_points.push_back(Vect<double>((double)vect_offset.at(0).x,(double)vect_offset.at(0).y,(double)vect_offset.at(0).z));
        nbr_points.push_back(1);

        Vect<float> bary = vect_offset.at(0);

        for (vector< Vect <float> >::iterator it = vect_offset.begin() + 1; it != vect_offset.end(); ++it) {
            if(vectors_maths::lenght(*it, bary) < epsi) {
                sum_points.back() += Vect<double>((double)(*it).x,(double)(*it).y,(double)(*it).z);
                ++nbr_points.back();
            }
            else {
                for(vector< Vect <float> >::iterator iw = it - 1; iw != it - nbr_points.back() - 1; --iw) {
                    *iw = bary;
                }
                sum_points.push_back(Vect<double>((double)(*it).x,(double)(*it).y,(double)(*it).z));
                nbr_points.push_back(1);
            }
            bary.x = (float)(sum_points.back().x / (float)nbr_points.back());
            bary.y = (float)(sum_points.back().y / (float)nbr_points.back());
            bary.z = (float)(sum_points.back().z / (float)nbr_points.back());
        }

        return false;
    }
}
