#include "root.h"

Root::Root(IplImage *frame_) : frame(frame_) {
}

// The root will move to stay inside the right zone
// Le noeud se déplace pour rester dans la bonne partition
// black_arc, lenght of the arc that is out from the right area
// black_arc, détermine la longueur de l'arc de cercle en dehors de la partition
// radius, the man lenght for the rays
// radius, longueur maximale des rayons
void Root::search(IplImage* frame_, float const &radius, int const &black_arc) {

    // actualise l'image
    frame = frame_;

    // number of rays, the root is the center
    // nombre de rayons, le noeud étant le centre
    int nbr_rays = 32;

    // black_ray, number of points along the ray and out of the right area
    // black_ray, nombre de points le long du rayon et en dehors de la partition
    int black_ray = 0;

    //teta is the ray's angle
    // teta représente l'angle du rayon
    float teta = 0;

    // vect_rays, vector with weight of rays. A ray is heavy when it's very out from the right area
    // vect_rays, vecteur comprenant les poids des rayons. Un rayond est de poid ford lorsqu'il est très en dehors de la partition
    std::vector<int> vect_rays(nbr_rays, 0);

    // We explore all points along the ray
    // Nous testons tous les points situés sur le rayon
    for(float ray = 1.0f; ray < radius; ++ray) {

        black_ray = 0;

        // We explore all rays
        // Nous testons tous les rayons
        for(int j = 0; j < nbr_rays; ++j) {

            teta = (float)j * 2 * PI / (float)nbr_rays;

            // the point v is exploring all rays
            // Le point v explore tous les rayons
            Vect<float> v(p.x + ray * cosf(teta), p.y + ray * sinf(teta), 0);

            // We are out of the window, then we are in black zone out of the right area
            // Nous sommes en dehors de la fenêtre, donc nous sommes en dehors de la partition
            if(control<float>(v)) {

                ++black_ray;

                // the ray(j) is turning more heavy
                // le rayon(j) devient plus lours
                vect_rays.at(j) += 1;
                continue;
            }

            // We are out of the right zone
            // Nous sommes en dehors de la partition
            if (!frame->PIXEL_COLOR_RED_VECT(v)) {
                frame->PIXEL_COLOR_GREEN_VECT(v) = 255;

                ++black_ray;

                // the ray(j) is turning more heavy
                // le rayon(j) devient plus lours
                vect_rays.at(j) += 1;
            }
            // We draw rays in a white color
            // Nous dessinons les rayons en blanc
            else {
                frame->PIXEL_COLOR_BLUE_VECT(v) = 255;
                frame->PIXEL_COLOR_GREEN_VECT(v) = 255;
            }

            // we stop the loop when the arc out of the right area is bigger than black_arc
            // Lorsque l'arc de cercle en dehors de la partition est suffisemment grand, nous arrêtons la boucle principale
            if(black_ray > black_arc) {

                // to exit this loop
                ray = radius;
                break;
            }
        }
    }

    Vect<float> r(0, 0, 0);

    // for all rays, *it is the weight
    // pour tous les rayons, *it représente le poids
    for (std::vector<int>::iterator it = vect_rays.begin(); it != vect_rays.end(); ++it) {

        // r is the vector to move the root into the right area with a speed proportional to the weight
        // r est le vecteur de déplacement du noeud vers l'intérieur de la partition avec une vitesse proportionnelle au poids
        r.x -= (float)*it / (float)nbr_rays * cosf((float)(it - vect_rays.begin()) * PI * 2 / (float)nbr_rays);
        r.y -= (float)*it / (float)nbr_rays * sinf((float)(it - vect_rays.begin()) * PI * 2 / (float)nbr_rays);
    }

    p += r;

}
