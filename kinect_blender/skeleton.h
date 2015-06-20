#ifndef SKELETON_H
#define SKELETON_H

#include "root_head.h"
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
    Vect<float> neck, hips;
    float lenght_head_neck, neck_hips;

    Head *head;

    int comp(Vect<int> const&);
    void search_human();
    bool circle_search_human(Vect<int> const&);
    void replace(int a, int b);
    void draw_square(int ray, int x_, int y_);

    Vect<float> first_search_head(int *ray);
    Vect<float> first_search_hips();
    Vect<float> root_move(Vect<float> v, int ray_min, int ray_max, float deep);

};

Vect<float> cross(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);

#endif // SKELETON_H
