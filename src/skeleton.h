/*************************************************************************/
/* This file is part of Tron.                                            */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

#ifndef SKELETON_H
#define SKELETON_H

#include "root/root_head.h"
#include "root/root_neck.h"
#include "root/root_hips.h"
#include "root/root_shoulder.h"
#include "root/root_hand.h"
#include "root/root_elbow.h"
#include "search_human.h"
#include "io_frames.h"
#include "draw.h"
#include <vector>
#include <QMutex>
#include "win_size.h"

class Skeleton {
public:
    explicit Skeleton();
    ~Skeleton();
    void start(float *progValue, int, int, int, int, int, int, QSharedPointer<IO_frames> &);
    bool isCreated();
    int get_nbr_imgs();
    std::vector< cv::Mat > vect_imgs;

    QSharedPointer<root::Neck> SP_neck;
    QSharedPointer<root::Head> SP_head;
    QSharedPointer<root::Hips> SP_hips;
    QSharedPointer<root::Shoulder> SP_shoulder_r, SP_shoulder_l;
    QSharedPointer<root::Hand> SP_hand_r, SP_hand_l;
    QSharedPointer<root::Elbow> SP_elbow_r, SP_elbow_l;

private:

    bool created;
    int nbr_imgs;
    cv::Mat buffer_img;
    cv::Mat mat_frame;
    QSharedPointer<cv::Mat> SP_mat_frame_draw;
    int blue_color, green_color, red_color, nbr_pass, smoth, escapeFrames;
    float offset_z;
    QMutex mutex;

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
