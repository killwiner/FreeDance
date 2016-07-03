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

#include "skeleton.h"
#include <QtDebug>

Skeleton::Skeleton() : created(false) {

    // image with the human area
    // image avec la partition humaine
    mat_frame = cv::Mat(HEIGHT, WIDTH, CV_8UC3);
    // image with the human area and the skeleton draw
    // image avec la partition humaine et le dessin du squelette
    QSharedPointer<cv::Mat> mfd(new cv::Mat(HEIGHT, WIDTH, CV_8UC3));
    SP_mat_frame_draw = mfd;

    // Les images seront enregistrées dans la liste vect_imgs. On initialise toute la liste à 0
    // Images will saved in a list vect_imgs, this list is initialized.
    std::vector<cv::Mat>().swap(vect_imgs);
    vect_imgs.resize(0);

}

// destructor
// destructeur
Skeleton::~Skeleton() {
    mat_frame.release();
}

// return nbr_imgs
// retourne le nombre d'images
int Skeleton::get_nbr_imgs() {
    return nbr_imgs;
}

// Create all roots objects
void Skeleton::create_all_roots() {
    SP_head = QSharedPointer<root::Head>(new root::Head(mat_frame, SP_mat_frame_draw));
    SP_neck = QSharedPointer<root::Neck>(new root::Neck(mat_frame, SP_mat_frame_draw));
    SP_hips = QSharedPointer<root::Hips>(new root::Hips(mat_frame, SP_mat_frame_draw));
    SP_shoulder_r = QSharedPointer<root::Shoulder>(new root::Shoulder(mat_frame, SP_mat_frame_draw));
    SP_shoulder_l = QSharedPointer<root::Shoulder>(new root::Shoulder(mat_frame, SP_mat_frame_draw));
    SP_hand_r = QSharedPointer<root::Hand>(new root::Hand(mat_frame, SP_mat_frame_draw));
    SP_hand_l = QSharedPointer<root::Hand>(new root::Hand(mat_frame, SP_mat_frame_draw));
    SP_elbow_r = QSharedPointer<root::Elbow>(new root::Elbow(mat_frame, SP_mat_frame_draw));
    SP_elbow_l = QSharedPointer<root::Elbow>(new root::Elbow(mat_frame, SP_mat_frame_draw));
}

// search for the first time roots
// recherche les noeuds pour la première fois
void Skeleton::search_fT_roots() {
    SP_hips->first_search();
    Vect<float> neck_coord = SP_head->first_search();
    SP_neck->first_search(neck_coord, SP_hips->get_coord(), SP_head->get_coord());
    SP_shoulder_r->first_search(SP_neck->get_coord(), SP_hips->get_coord(), true);
    SP_shoulder_l->first_search(SP_neck->get_coord(), SP_hips->get_coord(), false);
    SP_hand_r->first_search(SP_elbow_r->get_coord(), SP_shoulder_r->get_coord(), true);
    SP_hand_l->first_search(SP_elbow_l->get_coord(), SP_shoulder_r->get_coord(), false);
    SP_elbow_r->first_search(SP_shoulder_r->get_coord(), SP_hand_r->get_coord(), true);
    SP_elbow_l->first_search(SP_shoulder_l->get_coord(), SP_hand_l->get_coord(), false);
}

// search new positions for roots
// recherche les nouvelles coordonnées des noeuds
void Skeleton::search_new_positions() {
    SP_hips->search(25, 1, Vect<float>(0, 1, 0));
    SP_head->search(40, 16, Vect<float>(0, -1, 0));
    SP_neck->search(30, 16, Vect<float>(0, -1, 0));

    SP_neck->bone(SP_hips->get_coord(), SP_head->get_coord());

    SP_shoulder_r->search(25, 16, Vect<float>(-1, -1, 0), SP_neck->get_coord(), SP_hips->get_coord());
    SP_shoulder_r->bone(SP_neck->get_coord());
    SP_shoulder_l->search(25, 16, Vect<float>(1, -1, 0), SP_neck->get_coord(), SP_hips->get_coord());
    SP_shoulder_l->bone(SP_neck->get_coord());

    SP_hand_r->search(25, 24, (SP_hand_r->get_coord() - SP_elbow_r->get_coord()) / vectors_maths::lenght(SP_hand_r->get_coord(), SP_elbow_r->get_coord()), SP_elbow_r->get_coord());
    //hand_r->z_axis(buffer_img->imageData[coord_gbr(Vect<int>(hand_r->p.x, hand_r->p.y, 0))] - offset_z);
    SP_hand_l->search(25, 24, (SP_hand_l->get_coord() - SP_elbow_l->get_coord()) / vectors_maths::lenght(SP_hand_l->get_coord(), SP_elbow_l->get_coord()), SP_elbow_l->get_coord());
    //hand_l->z_axis(buffer_img->imageData[coord_gbr(Vect<int>(hand_l->p.x, hand_l->p.y, 0))] - offset_z);

    SP_elbow_r->search(SP_shoulder_r->get_coord(), SP_hand_r->get_coord());
    SP_elbow_l->search(SP_shoulder_l->get_coord(), SP_hand_l->get_coord());

}

// new rotations for the exportation
// nouvelles rotation destinées à l'exportation
void Skeleton::new_rot() {
    SP_hips->new_rot(SP_neck->get_coord());
    SP_neck->new_rot(SP_head->get_coord(), SP_hips->get_coord());
    SP_shoulder_l->new_rot(SP_hips->get_coord(), SP_neck->get_coord());
    SP_shoulder_r->new_rot(SP_hips->get_coord(), SP_neck->get_coord());
    SP_elbow_l->new_rot(SP_neck->get_coord(), SP_shoulder_l->get_coord());
    SP_elbow_r->new_rot(SP_neck->get_coord(), SP_shoulder_r->get_coord());
    SP_hand_r->new_rot(SP_shoulder_r->get_coord(), SP_elbow_r->get_coord());
    SP_hand_l->new_rot(SP_shoulder_l->get_coord(), SP_elbow_l->get_coord());
}

void Skeleton::draw_roots() {
    if(!control<float>(SP_hips->get_coord()))
        draw_square(10, (int)SP_hips->get_coord().x, (int)SP_hips->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_head->get_coord()))
        draw_square(10, (int)SP_head->get_coord().x, (int)SP_head->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_neck->get_coord()))
        draw_square(10, (int)SP_neck->get_coord().x, (int)SP_neck->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_shoulder_r->get_coord()))
        draw_square(10, (int)SP_shoulder_r->get_coord().x, (int)SP_shoulder_r->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_shoulder_l->get_coord()))
        draw_square(10, (int)SP_shoulder_l->get_coord().x, (int)SP_shoulder_l->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_hand_r->get_coord()))
        draw_square(10, (int)SP_hand_r->get_coord().x, (int)SP_hand_r->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_hand_l->get_coord()))
        draw_square(10, (int)SP_hand_l->get_coord().x, (int)SP_hand_l->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_elbow_r->get_coord()))
        draw_square(10, (int)SP_elbow_r->get_coord().x, (int)SP_elbow_r->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(SP_elbow_l->get_coord()))
        draw_square(10, (int)SP_elbow_l->get_coord().x, (int)SP_elbow_l->get_coord().y, SP_mat_frame_draw);
}

void Skeleton::start(float *progValue, int green_color_, int blue_color_, int red_color_, int nbr_pass_, int smoth_, int escapeFrames_, QSharedPointer<IO_frames> &SP_saveload) {

    // couleurs de filtrage des images
    // colors to filter images
    blue_color = blue_color_;
    green_color = green_color_;
    red_color = red_color_;
    nbr_pass = nbr_pass_;
    smoth = smoth_;
    escapeFrames = escapeFrames_;

    // Here only black
    mat_frame.setTo(cv::Scalar::all(0));

    QSharedPointer<SearchHuman> sh(new SearchHuman(SP_saveload->vect_imgs, mat_frame, green_color, blue_color, red_color));
    SP_human_area = sh;
    SP_human_area->clear_partition();
    SP_human_area->first_search();
    // change all colors to show only areas after filters
    // on change toutes les couleurs pour rendre évident les partitions après filtrage
    SP_human_area->unification();

    mat_frame.copyTo(*SP_mat_frame_draw.data());

    create_all_roots();
    search_fT_roots();

    // on considère le bassin comme le référentiel 0 pour la profondeur
    // hips are the reference for the deep as 0
    //offset_z = frame->imageData[coord_gbr(Vect<int>(hips->p.x, hips->p.y, 0))];

    // for all images
    nbr_imgs = SP_saveload->get_nbr_imgs();
    for(int i = 1; i < nbr_imgs; ++i) {

        //qDebug() << i;

        // We show the progress in %
        mutex.lock();
        *progValue = (float)i / (float)nbr_imgs;
        mutex.unlock();

        // Here only black
        mat_frame.setTo(cv::Scalar::all(0));

        SP_human_area->clear_partition();
        SP_human_area->search();

        mat_frame.copyTo(*SP_mat_frame_draw.data());

        for(int j = 0; j < nbr_pass; ++j)
            search_new_positions();

        new_rot();
        draw_roots();

        // We add the final image to the vector of images
        // Nous ajoutons l'image nouvellement crée au vecteur d'images
        vect_imgs.push_back(SP_mat_frame_draw->clone());

    }

    SP_hips->smoth(3.0f);
    SP_hips->bezier_curve(8);
    SP_neck->smoth(3.0f);
    SP_neck->bezier_curve(8);
    nbr_imgs /= 8;

    created = true;
}

bool Skeleton::isCreated() {
    return created;
}
