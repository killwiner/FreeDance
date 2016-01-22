#include "skeleton.h"
#include <stdio.h>

Skeleton::Skeleton() {

    SP_frame = QSharedPointer<IplImage>(cvCreateImage(cvSize(WIDTH, HEIGHT), 8, 3));
    SP_frame_draw = QSharedPointer<IplImage>(cvCreateImage(cvSize(WIDTH, HEIGHT), 8, 3));

    // Les images seront enregistrées dans la liste vect_imgs. On initialise toute la liste à 0
    // Images will saved in a list vect_imgs, this list is initialized.
    std::vector< QSharedPointer<IplImage> >().swap(vect_imgs);
    vect_imgs.resize(0);
    surface = 0;
}

Skeleton::~Skeleton() {
    IplImage *frame_delete, *frame_draw_delete;

    frame_delete = SP_frame.data();
    frame_draw_delete = SP_frame_draw.data();

    cvReleaseImage(&frame_delete);
    cvReleaseImage(&frame_draw_delete);
    SP_frame.clear();
    // core dump with this clear, why ? :-(
    //SP_frame_draw.clear();
}

void Skeleton::start(Progress *prog, int green_color_, int blue_color_) {

    int nbr_pass = 8;

    // couleurs de filtrage des images
    // colors to filter images
    blue_color = blue_color_;
    green_color = green_color_;

    // Les partitions sont représentées dans une matrice 2D par des identifiants
    // We find areas in a 2D matrix with identities
    partition = new std::vector<int>(WIDTH*HEIGHT, 0);

    // open the video
    CvCapture* capture = cvCaptureFromAVI("tmp/kinect_video_2.avi"); // read AVI video

    try {
        if( !capture )
            throw std::string("Can't open the file tmp/kinect_video_2.avi with cvCaptureFromAVI.");
    }
    catch(std::string const& str) {
        std::cerr << str << std::endl;
        return;
    }

    // We take the number of images in the video
    // Nous capturons le nombre d'images de la vidéo
    nbr_imgs = (int) cvGetCaptureProperty( capture , CV_CAP_PROP_FRAME_COUNT );

    std::vector<int>::iterator max;

    centroid.x = 0;
    centroid.y = 0;
    surface = 0;

    // for all images
    for(int i = 0; i < nbr_imgs; ++i) {

        // We show the progress in %
        prog->value(i * 100 / nbr_imgs);

        try {

        // we catch the next image
        buffer_img = cvQueryFrame( capture );

        if(!buffer_img)
            throw std::string("Can't open the file tmp/kinect_video_2.avi with cvCaptureFromAVI.");
        }
        catch(std::string const& str) {
            std::cerr << str << std::endl;
            cvReleaseCapture(&capture);
            return;
        }

        // To turn images in the right order colors
        // Remet les couleurs dans le bon ordre
        cvCvtColor(buffer_img, buffer_img, CV_RGB2BGR);

        // id_area contains all partition surfaces
        // id_area contient les surfaces des partitions
        std::vector<int>().swap(id_area);
        id_area.resize(0);

        //delete partition;
        //partition = new std::vector<int>(WIDTH*HEIGHT, 0);
        for(int ii = 0; ii < WIDTH*HEIGHT; ++ii)
            partition->at(ii) = 0;

        // on clone l'image
        // we clone the image
        //frame  = cvCloneImage(buffer_img);

        // Here only black
        cvZero(SP_frame.data());


        if(i == 0) {
            // recherche les partitions avec les surfaces
            // search areas with surfaces
            search_partitions();

            // Recherche la plus grosse partition
            // Search the largest area
            // id_area is the vector with all partition's areas
            // id_area contient toutes les aires de toutes les partitions
            max = id_area.begin() + 1;
            for (std::vector<int>::iterator it = id_area.begin() + 1 ; it != id_area.end(); ++it)
                if (*it > *max)
                    max = it;
            surface = (long int)*max;
        }
        else {

            Vect<int> v;
            v.x = centroid.x;
            v.y = centroid.y;
            surface = 0;
            centroid.x = 0;
            centroid.y = 0;

            search_human(v);

            if(surface) {
                centroid.x = centroid.x / surface;
                centroid.y = centroid.y / surface;
            }
            else
                centroid.x = centroid.y = 0;
        }

        long int s = 0;

        // change all colors to show only areas after filters
        // on change toutes les couleurs pour rendre évident les partitions après filtrage
        if (i == 0) {
            for(int y = 0; y < HEIGHT; ++y)
                for(int x = 0; x < WIDTH; ++x) {

                  // green and blue are turned into black
                    // les couleurs vert et bleu sont passées à du noir
                    //frame->PIXEL_COLOR_BLUE(x, y) = 0;
                    //frame->PIXEL_COLOR_GREEN(x, y) = 0;
                    //frame->PIXEL_COLOR_RED(x, y) = 0;

                    if(partition->at(coord_gray(Vect<int>(x, y, 0))) == max - id_area.begin()) {

                        // the human area is colored
                        // La partition représentant l'humain est colorisé
                        SP_frame->PIXEL_COLOR_RED(x, y) = 255;

                        ++s;

                        // réécrire le vecter partition
                        // rewrite the vector partitions
                        partition->at(coord_gray(Vect<int>(x, y, 0))) = 1;

                        centroid.x += (long int)x;
                        centroid.y += (long int)y;

                    }
                    else
                       partition->at(coord_gray(Vect<int>(x, y, 0))) = 0;

                }
            centroid.x = centroid.x / s;
            centroid.y = centroid.y / s;

        }

        cvCopy(SP_frame.data(), SP_frame_draw.data(), NULL);

        if(i == 0) {

            // Create all roots objects
            head = new root::Head(SP_frame, SP_frame_draw);
            neck = new root::Neck(SP_frame, SP_frame_draw);
            hips = new root::Hips(SP_frame, SP_frame_draw);
            shoulder_r = new root::Shoulder(SP_frame, SP_frame_draw);
            shoulder_l = new root::Shoulder(SP_frame, SP_frame_draw);
            hand_r = new root::Hand(SP_frame, SP_frame_draw);
            hand_l = new root::Hand(SP_frame, SP_frame_draw);
            elbow_r = new root::Elbow(SP_frame, SP_frame_draw);
            elbow_l = new root::Elbow(SP_frame, SP_frame_draw);

            // search for the first time roots
            // recherche les noeuds pour la première fois
            hips->first_search();
            neck->first_search(head->first_search(), hips->get_coord());
            shoulder_r->first_search(neck->get_coord(), hips->get_coord(), true);
            shoulder_l->first_search(neck->get_coord(), hips->get_coord(), false);
            hand_r->first_search(true, elbow_r->get_coord(), shoulder_r->get_coord());
            hand_l->first_search(false, elbow_l->get_coord(), shoulder_r->get_coord());

            elbow_r->first_search(shoulder_r->get_coord(), hand_r->get_coord(), neck->get_coord(), true);
            elbow_l->first_search(shoulder_l->get_coord(), hand_l->get_coord(), neck->get_coord(), false);

            // on considère le bassin comme le référentiel 0 pour la profondeur
            // hips are the reference for the deep as 0
            //offset_z = frame->imageData[coord_gbr(Vect<int>(hips->p.x, hips->p.y, 0))];

        }

        for(int j = 0; j < nbr_pass; ++j) {

            // search new positions for roots
            // recherche les nouvelles coordonnées des noeuds
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

        head->new_rot(hips->get_coord(), neck->get_coord());
        shoulder_l->new_rot(hips->get_coord(), neck->get_coord());
        shoulder_r->new_rot(hips->get_coord(), neck->get_coord());
        elbow_l->new_rot(neck->get_coord(), shoulder_r->get_coord());
        elbow_r->new_rot(neck->get_coord(), shoulder_r->get_coord());
        hand_r->new_rot(shoulder_r->get_coord(), elbow_r->get_coord());
        hand_l->new_rot(shoulder_l->get_coord(), elbow_l->get_coord());
        hips->new_rot(neck->get_coord());

        // draw roots
        if(!control<float>(hips->get_coord()))
            draw_square(10, (int)hips->get_coord().x, (int)hips->get_coord().y);

        if(!control<float>(head->get_coord()))
            draw_square(10, (int)head->get_coord().x, (int)head->get_coord().y);

        if(!control<float>(neck->get_coord()))
            draw_square(10, (int)neck->get_coord().x, (int)neck->get_coord().y);

        if(!control<float>(shoulder_r->get_coord()))
            draw_square(10, (int)shoulder_r->get_coord().x, (int)shoulder_r->get_coord().y);

        if(!control<float>(shoulder_l->get_coord()))
            draw_square(10, (int)shoulder_l->get_coord().x, (int)shoulder_l->get_coord().y);

        if(!control<float>(hand_r->get_coord()))
            draw_square(10, (int)hand_r->get_coord().x, (int)hand_r->get_coord().y);

        if(!control<float>(hand_l->get_coord()))
            draw_square(10, (int)hand_l->get_coord().x, (int)hand_l->get_coord().y);

        if(!control<float>(elbow_r->get_coord()))
            draw_square(10, (int)elbow_r->get_coord().x, (int)elbow_r->get_coord().y);

        if(!control<float>(elbow_l->get_coord()))
            draw_square(10, (int)elbow_l->get_coord().x, (int)elbow_l->get_coord().y);

        // We add the final image to the vector of images
        // Nous ajoutons l'image nouvellement crée au vecteur d'images
        IplImage *img_buff = NULL;
        img_buff = cvCloneImage(SP_frame_draw.data());
        //vect_imgs.push_back(QSharedPointer<IplImage>(cvCloneImage(hips->SP_frame_draw.data())));
        vect_imgs.push_back(QSharedPointer<IplImage>(img_buff));

        // plante le programme :-(
        // don't work :-(
        // cvReleaseImage(&buffer_img);

        //if(i == 300) break;

    }

    cvReleaseCapture(&capture);

}

void Skeleton::draw_square(int ray, int x_, int y_) {
    for (int x = x_ - ray; x < x_ + ray; ++x)
        for (int y = y_ - ray; y < y_ + ray; ++y)
            if (!control<int>(Vect<int>(x, y, 0))) {
                SP_frame->imageData[coord_gbr<int>(Vect<int>(x, y, 0))] = 255;
                SP_frame->imageData[coord_gbr<int>(Vect<int>(x, y, 0)) + 1] = 255;
                SP_frame->imageData[coord_gbr<int>(Vect<int>(x, y, 0)) + 2] = 255;
            }
}
