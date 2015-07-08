#include "root.h"
#include <stdio.h>

Root::Root() {
}

void Root::refresh(IplImage *frame_) {
    frame = frame_;
}

void Root::search(float coef_rad, int ray_max, float deep) {

    Vect<float> v = p;

    int nbr_rays = 32;
    float n_ray = 0, teta = 0, l_ray = 0;
    int max = 0;
    float alpha = 0;
    std::vector<int> vect_rays(nbr_rays, 0);

    for(float ray = 1; ray < (float)ray_max; ++ray) {
        n_ray = 0;
        l_ray = ray;
        for(int j = 0; j < nbr_rays; ++j) {
            teta = (float)j * 2 * PI / (float)nbr_rays;
            Vect<float> p(v.x + ray * cosf(teta), v.y + ray * sinf(teta));
            if(control<float>(p)) {
                ++n_ray;
                vect_rays.at(j) += 1;
                continue;
            }
            if (!frame->imageData[coord_gbr<float>(p) + 2]) {
                frame->imageData[coord_gbr<float>(p) + 1] = 255;
                ++n_ray;
                vect_rays.at(j) += 1;
            }
            else {
                frame->imageData[coord_gbr<float>(p)] = 255;
                frame->imageData[coord_gbr<float>(p) + 1] = 255;

            }

            if(n_ray > deep * (float)nbr_rays && ray > (float)radius * coef_rad) {

                ray = (float)ray_max;
                break;
            }
        }
    }

    int i = 0;

    Vect<float> r(0, 0);

    for (std::vector<int>::iterator it = vect_rays.begin(); it != vect_rays.end(); ++it) {

        r.x -= (float)*it / (float)nbr_rays * cosf((float)i * PI * 2 / (float)nbr_rays);
        r.y -= (float)*it / (float)nbr_rays * sinf((float)i * PI * 2 / (float)nbr_rays);

        /*
        if (max < *it) {
             max = *it;
             alpha = i;
        }
        ++i;
        */
        ++i;
    }

    r.x += v.x;
    r.y += v.y;

    //Vect<float> r(v.x -(float)max / 2 * cosf(alpha * PI * 2 / (float)nbr_rays), v.y - (float)max / 2 * sinf(alpha * PI * 2 / (float)nbr_rays));

    if (!control<float>(v))
        if(!frame->imageData[coord_gbr<float>(v)] && max > 0) {
            r.x = -r.x;
            r.y = -r.y;
        }

    p = r;

}
