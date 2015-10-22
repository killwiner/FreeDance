#include "skeleton.h"
#include <stdio.h>

Skeleton::Skeleton() {
    // Les images seront enregistrées dans la liste vect_imgs. On initialise toute la liste à 0
    // Images will saved in a list vect_imgs, this list is initialized.
    std::vector<IplImage>().swap(vect_imgs);
    vect_imgs.resize(0);
    surface = 0;
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
        frame = cvCreateImage(cvSize(WIDTH, HEIGHT), 8, 3);
        cvZero(frame);

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

            centroid.x = centroid.x / surface;
            centroid.y = centroid.y / surface;
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
                        frame->PIXEL_COLOR_RED(x, y) = 255;

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

        if(i == 0) {

            // Create all roots objects
            head = new Head(frame);
            neck = new Neck(frame);
            hips = new Hips(frame);
            shoulder_r = new Shoulder(frame);
            shoulder_l = new Shoulder(frame);
            hand_r = new Hand(frame);
            hand_l = new Hand(frame);
            elbow_r = new Elbow(frame);
            elbow_l = new Elbow(frame);

            // search for the first time roots
            // recherche les noeuds pour la première fois
            hips->first_search();
            neck->first_search(head->first_search(), hips->p);
            shoulder_r->first_search(neck->p, hips->p, true);
            shoulder_l->first_search(neck->p, hips->p, false);
            hand_r->first_search(true);
            hand_l->first_search(false);

            elbow_r->first_search(shoulder_r->p, hand_r->p);
            elbow_l->first_search(shoulder_l->p, hand_l->p);

            // on considère le bassin comme le référentiel 0 pour la profondeur
            // hips are the reference for the deep as 0
            offset_z = frame->imageData[coord_gbr(Vect<int>(hips->p.x, hips->p.y, 0))];

        }

        for(int i = 0; i < nbr_pass; ++i) {

            // search new positions for roots
            // recherche les nouvelles coordonnées des noeuds
            hips->search(frame, 25, 1, Vect<float>(0, 1, 0));
            head->search(frame, 200, 16, Vect<float>(0, -1, 0));

            neck->search(frame, 40, 16, Vect<float>(0, 0, 0));
            neck->bone();
            head->bone(neck->p);

            shoulder_r->search(frame, 25, 16, Vect<float>(-1, -1, 0));
            shoulder_r->bone();
            shoulder_l->search(frame, 25, 16, Vect<float>(1, -1, 0));
            shoulder_l->bone();

            hand_r->search(frame, 25, 24, (hand_r->p - elbow_r->p) / lenght(hand_r->p, elbow_r->p), elbow_r->p);
            //hand_r->z_axis(buffer_img->imageData[coord_gbr(Vect<int>(hand_r->p.x, hand_r->p.y, 0))] - offset_z);
            hand_l->search(frame, 25, 24, (hand_l->p - elbow_l->p) / lenght(hand_l->p, elbow_l->p), elbow_l->p);
            //hand_l->z_axis(buffer_img->imageData[coord_gbr(Vect<int>(hand_l->p.x, hand_l->p.y, 0))] - offset_z);

            elbow_r->search(frame, shoulder_r->p, hand_r->p, hips->p);
            elbow_l->search(frame, shoulder_l->p, hand_l->p, hips->p);

        }

        head->new_rot(hips->p, neck->p);

        // draw roots
        if(!control<float>(hips->p))
            draw_square(10, (int)hips->p.x, (int)hips->p.y);

        if(!control<float>(head->p))
            draw_square(10, (int)head->p.x, (int)head->p.y);

        if(!control<float>(neck->p))
            draw_square(10, (int)neck->p.x, (int)neck->p.y);

        if(!control<float>(shoulder_r->p))
            draw_square(10, (int)shoulder_r->p.x, (int)shoulder_r->p.y);

        if(!control<float>(shoulder_l->p))
            draw_square(10, (int)shoulder_l->p.x, (int)shoulder_l->p.y);

        if(!control<float>(hand_r->p))
            draw_square(10, (int)hand_r->p.x, (int)hand_r->p.y);

        if(!control<float>(hand_l->p))
            draw_square(10, (int)hand_l->p.x, (int)hand_l->p.y);

        if(!control<float>(elbow_r->p))
            draw_square(10, (int)elbow_r->p.x, (int)elbow_r->p.y);

        if(!control<float>(elbow_l->p))
            draw_square(10, (int)elbow_l->p.x, (int)elbow_l->p.y);

        // We add the final image to the vector of images
        // Nous ajoutons l'image nouvellement crée au vecteur d'images
        vect_imgs.push_back(*frame);

        // plante le programme :-(
        // don't work :-(
        // cvReleaseImage(&buffer_img);

        //if(i == 10) break;

    }

    cvReleaseCapture(&capture);

}

void Skeleton::draw_square(int ray, int x_, int y_) {
    for (int x = x_ - ray; x < x_ + ray; ++x)
        for (int y = y_ - ray; y < y_ + ray; ++y)
            if (!control<int>(Vect<int>(x, y, 0))) {
                frame->imageData[coord_gbr<int>(Vect<int>(x, y, 0))] = 255;
                frame->imageData[coord_gbr<int>(Vect<int>(x, y, 0)) + 1] = 255;
                frame->imageData[coord_gbr<int>(Vect<int>(x, y, 0)) + 2] = 255;
            }
}
