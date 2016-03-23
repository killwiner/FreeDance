#include "skeleton.h"

Skeleton::Skeleton() {

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
    SP_mat_frame_draw.clear();
    SP_human_area.clear();
    delete head;
    delete neck;
    delete hips;
    delete shoulder_r;
    delete shoulder_l;
    delete hand_r;
    delete hand_l;
    delete elbow_r;
    delete elbow_l;
}

// return nbr_imgs
// retourne le nombre d'images
int Skeleton::get_nbr_imgs() {
    return nbr_imgs;
}

// Create all roots objects
void Skeleton::create_all_roots() {
    head = new root::Head(mat_frame, SP_mat_frame_draw);
    neck = new root::Neck(mat_frame, SP_mat_frame_draw);
    hips = new root::Hips(mat_frame, SP_mat_frame_draw);
    shoulder_r = new root::Shoulder(mat_frame, SP_mat_frame_draw);
    shoulder_l = new root::Shoulder(mat_frame, SP_mat_frame_draw);
    hand_r = new root::Hand(mat_frame, SP_mat_frame_draw);
    hand_l = new root::Hand(mat_frame, SP_mat_frame_draw);
    elbow_r = new root::Elbow(mat_frame, SP_mat_frame_draw);
    elbow_l = new root::Elbow(mat_frame, SP_mat_frame_draw);
}

// search for the first time roots
// recherche les noeuds pour la première fois
void Skeleton::search_fT_roots() {
    hips->first_search();
    neck->first_search(head->first_search(), hips->get_coord());
    shoulder_r->first_search(neck->get_coord(), hips->get_coord(), true);
    shoulder_l->first_search(neck->get_coord(), hips->get_coord(), false);
    hand_r->first_search(true, elbow_r->get_coord(), shoulder_r->get_coord());
    hand_l->first_search(false, elbow_l->get_coord(), shoulder_r->get_coord());
    elbow_r->first_search(shoulder_r->get_coord(), hand_r->get_coord(), neck->get_coord(), true);
    elbow_l->first_search(shoulder_l->get_coord(), hand_l->get_coord(), neck->get_coord(), false);
}

// search new positions for roots
// recherche les nouvelles coordonnées des noeuds
void Skeleton::search_new_positions() {
    hips->search(25, 1, Vect<float>(0, 1, 0));
    head->search(200, 16, Vect<float>(0, -1, 0));

    neck->search(40, 16, Vect<float>(0, 0, 0));
    neck->bone();
    head->bone(neck->get_coord());

    shoulder_r->search(25, 16, Vect<float>(-1, -1, 0), neck->get_coord(), hips->get_coord());
    shoulder_r->bone();
    shoulder_l->search(25, 16, Vect<float>(1, -1, 0), neck->get_coord(), hips->get_coord());
    shoulder_l->bone();

    hand_r->search(25, 24, (hand_r->get_coord() - elbow_r->get_coord()) / vectors_maths::lenght(hand_r->get_coord(), elbow_r->get_coord()), elbow_r->get_coord());
    //hand_r->z_axis(buffer_img->imageData[coord_gbr(Vect<int>(hand_r->p.x, hand_r->p.y, 0))] - offset_z);
    hand_l->search(25, 24, (hand_l->get_coord() - elbow_l->get_coord()) / vectors_maths::lenght(hand_l->get_coord(), elbow_l->get_coord()), elbow_l->get_coord());
    //hand_l->z_axis(buffer_img->imageData[coord_gbr(Vect<int>(hand_l->p.x, hand_l->p.y, 0))] - offset_z);

    elbow_r->search(shoulder_r->get_coord(), hand_r->get_coord(), hips->get_coord());
    elbow_l->search(shoulder_l->get_coord(), hand_l->get_coord(), hips->get_coord());
}

// new rotations for the exportation
// nouvelles rotation destinées à l'exportation
void Skeleton::new_rot() {
    head->new_rot(hips->get_coord(), neck->get_coord());
    shoulder_l->new_rot(hips->get_coord(), neck->get_coord());
    shoulder_r->new_rot(hips->get_coord(), neck->get_coord());
    elbow_l->new_rot(neck->get_coord(), shoulder_r->get_coord());
    elbow_r->new_rot(neck->get_coord(), shoulder_r->get_coord());
    hand_r->new_rot(shoulder_r->get_coord(), elbow_r->get_coord());
    hand_l->new_rot(shoulder_l->get_coord(), elbow_l->get_coord());
    hips->new_rot(neck->get_coord());
}

void Skeleton::draw_roots() {
    if(!control<float>(hips->get_coord()))
        draw_square(10, (int)hips->get_coord().x, (int)hips->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(head->get_coord()))
        draw_square(10, (int)head->get_coord().x, (int)head->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(neck->get_coord()))
        draw_square(10, (int)neck->get_coord().x, (int)neck->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(shoulder_r->get_coord()))
        draw_square(10, (int)shoulder_r->get_coord().x, (int)shoulder_r->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(shoulder_l->get_coord()))
        draw_square(10, (int)shoulder_l->get_coord().x, (int)shoulder_l->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(hand_r->get_coord()))
        draw_square(10, (int)hand_r->get_coord().x, (int)hand_r->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(hand_l->get_coord()))
        draw_square(10, (int)hand_l->get_coord().x, (int)hand_l->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(elbow_r->get_coord()))
        draw_square(10, (int)elbow_r->get_coord().x, (int)elbow_r->get_coord().y, SP_mat_frame_draw);

    if(!control<float>(elbow_l->get_coord()))
        draw_square(10, (int)elbow_l->get_coord().x, (int)elbow_l->get_coord().y, SP_mat_frame_draw);
}

void Skeleton::start(Progress *prog, int green_color_, int blue_color_, int nbr_pass_, QSharedPointer<IO_frames> &SP_saveload) {

    // couleurs de filtrage des images
    // colors to filter images
    blue_color = blue_color_;
    green_color = green_color_;
    nbr_pass = nbr_pass_;

    // Here only black
    mat_frame.setTo(cv::Scalar::all(0));

    QSharedPointer<SearchHuman> sh(new SearchHuman(SP_saveload->vect_imgs, mat_frame, green_color, blue_color));
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

        // We show the progress in %
        prog->value(i * 100 / nbr_imgs);

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

        if(i == 10) break;

    }
}


