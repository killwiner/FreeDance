#ifndef SKELETON_H
#define SKELETON_H

#include "root/root_head.h"
#include "root/root_neck.h"
#include "root/root_hips.h"
#include "root/root_shoulder.h"
#include "root/root_hand.h"
#include "root/root_elbow.h"
#include "progress.h"
#include "search_human.h"
#include "io_frames.h"
#include "draw.h"
#include <vector>
#include "win_size.h"

class Skeleton {
public:
    explicit Skeleton();
    ~Skeleton();
    void start(Progress*, int, int, int, QSharedPointer<IO_frames> &);
    int get_nbr_imgs();
    std::vector< cv::Mat > vect_imgs;

    root::Neck *neck;
    root::Head *head;
    root::Hips *hips;
    root::Shoulder *shoulder_r, *shoulder_l;
    root::Hand *hand_r, *hand_l;
    root::Elbow *elbow_r, *elbow_l;

private:

    int nbr_imgs;
    cv::Mat buffer_img;
    cv::Mat mat_frame;
    QSharedPointer<cv::Mat> SP_mat_frame_draw;
    int blue_color, green_color, nbr_pass;
    float offset_z;

    QSharedPointer<SearchHuman> SP_human_area;

    void replace(int a, int b);
    void create_all_roots();
    void search_fT_roots();
    void search_new_positions();
    void new_rot();
    void draw_roots();

    Vect<float> first_search_head(int *ray);
    Vect<float> first_search_hips();
    Vect<float> root_move(Vect<float> v, int ray_min, int ray_max, float deep);

};

Vect<float> cross(SearchHuman const &sh, Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2);

#endif // SKELETON_H
