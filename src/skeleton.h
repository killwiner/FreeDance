#ifndef SKELETON_H
#define SKELETON_H

#include "root/root_head.h"
#include "root/root_neck.h"
#include "root/root_hips.h"
#include "root/root_shoulder.h"
#include "root/root_hand.h"
#include "root/root_elbow.h"
#include "progress.h"
#include <vector>
#include "win_size.h"

class Skeleton {
public:
    explicit Skeleton();
    ~Skeleton();
    void start(Progress*, int, int);

    std::vector< cv::Mat > vect_imgs;

    root::Neck *neck;
    root::Head *head;
    root::Hips *hips;
    root::Shoulder *shoulder_r, *shoulder_l;
    root::Hand *hand_r, *hand_l;
    root::Elbow *elbow_r, *elbow_l;

    int nbr_imgs;

private:

    std::vector<int> *partition;
    std::vector<int> id_area;
    cv::Mat buffer_img;
    cv::Mat mat_frame, mat_frame_draw;
    int blue_color, green_color;
    float offset_z;
    Vect<long int> centroid;
    long int surface;

    int id_non_null(Vect<int> const&);
    void search_partitions();
    void search_human(Vect<int>);
    int scan_pixel(Vect<int>);
    bool fusion(Vect<int> const&);
    void replace(int a, int b);
    void draw_square(int ray, int x_, int y_);

    Vect<float> first_search_head(int *ray);
    Vect<float> first_search_hips();
    Vect<float> root_move(Vect<float> v, int ray_min, int ray_max, float deep);

};

Vect<float> cross(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);

// retoune l'identifiant de la partition d'un point, même si le point est en dehors de l'image
// return the area id from the point, even if the point is out from the picture
inline int Skeleton::id_non_null(Vect<int> const& a) {

    if(is_null(a))
        return -1;

    return partition->at(coord_gray(a));

}

// tous les points de l'ancienne partition prennent la valeur de l'identifiant de la nouvelle partition
// all points of the old area have the value of the identifier of the new area
inline void Skeleton::replace(int a, int b) {
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
        if (partition->at(i) == a)
            partition->at(i) = b;
}

#endif // SKELETON_H
