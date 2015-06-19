#ifndef SKELETON_H
#define SKELETON_H

#include <opencv2/opencv.hpp>
#include "vect.h"
#include "vect_f.h"
#include "progress.h"
#include <vector>
#include "win_size.h"

class Skeleton {
public:
    explicit Skeleton();
    void start(Progress *prog, int green_, int blue_);

    std::vector<IplImage> vect_imgs;

private:

    std::vector<int> *filt;
    std::vector<int> surf;
    IplImage *buffer_img;
    IplImage *frame;
    int blue, green;
    Vect_f head, neck, hips;
    float head_neck, neck_hips;

    int comp(Vect const&);
    void search_human();
    bool circle_search_head(Vect const&);
    void replace(int a, int b);
    void draw_square(int ray, int x_, int y_);

    Vect_f first_search_head(int *ray);
    Vect_f first_search_hips();
    Vect_f root_move(Vect_f v, int ray_min, int ray_max, float deep);

};

#endif // SKELETON_H
