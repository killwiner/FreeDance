#include "skeleton.h"
#include <stdio.h>

Skeleton::Skeleton() {
}

void Skeleton::start(Progress *prog, int green_, int blue_) {

    blue = blue_;
    green = green_;
    filt = new std::vector<int>(WIDTH*HEIGHT, 0);

    CvCapture* capture = cvCaptureFromAVI("tmp/kinect_out.avi"); // read AVI video
    if( !capture ) {
        std::cerr << "Can't open the file.\n";
        return;
    }

    int nbr_imgs = (int) cvGetCaptureProperty( capture , CV_CAP_PROP_FRAME_COUNT );

    std::vector<IplImage>().swap(vect_imgs);
    vect_imgs.resize(0);

    for(int i = 0; i < nbr_imgs; ++i) {

       prog->value(i * 100 / nbr_imgs);

       buffer_img = cvQueryFrame( capture );

        if(!buffer_img) {
            cvReleaseCapture(&capture);
            return;
        }

        cvCvtColor(buffer_img, buffer_img, CV_RGB2BGR);

        std::vector<int>().swap(surf);
        surf.resize(0);

        search_human();

        int max = 0, pos = 0, j = 1;

        for (std::vector<int>::iterator it = surf.begin() + 1 ; it != surf.end(); ++it) {
            if (*it > max) {
                max = *it;
                pos = j;
            }
            ++j;
        }

        frame  = cvCloneImage(buffer_img);

        for(int y = 0; y < HEIGHT; ++y)
            for(int x = 0; x < WIDTH; ++x) {
                frame->imageData[coord_gbr(Vect<int>(x, y))] = 0;
                frame->imageData[coord_gbr(Vect<int>(x, y)) + 1] = 0;

                int g_color = filt->at(coord_gray(Vect<int>(x, y)));
                if(filt->at(coord_gray(Vect<int>(x, y))) == pos)
                    frame->imageData[coord_gbr(Vect<int>(x, y)) + 2] = 255;
                else
                    frame->imageData[coord_gbr(Vect<int>(x, y)) + 2] = 0;
                if(g_color > 0)
                    frame->imageData[coord_gbr(Vect<int>(x, y))] = 255;
            }

        if(i == 0) {
            head = new Head();
            neck = new Root();
            hips = new Hips();
            shoulder_r = new Shoulder();
            shoulder_l = new Shoulder();
            head->refresh(frame);
            neck->refresh(frame);
            hips->refresh(frame);
            shoulder_r->refresh(frame);
            shoulder_l->refresh(frame);

            head->first_search(neck->p);
            hips->first_search();
            shoulder_r->first_search(neck->p, hips->p - neck->p, false);
            shoulder_l->first_search(neck->p, hips->p - neck->p, true);
            lenght_head_neck = dist(head->p, neck->p);
            lenght_neck_hips = dist(neck->p, hips->p);
        }
        else {
            head->refresh(frame);
            neck->refresh(frame);
            hips->refresh(frame);
            shoulder_r->refresh(frame);
            shoulder_l->refresh(frame);

        }

        if(!control<float>(head->p))
            draw_square(10, (int)head->p.x, (int)head->p.y);

        if(!control<float>(neck->p))
            draw_square(10, (int)neck->p.x, (int)neck->p.y);

        if(!control<float>(hips->p))
            draw_square(10, (int)hips->p.x, (int)hips->p.y);

        if(!control<float>(shoulder_r->p))
            draw_square(10, (int)shoulder_r->p.x, (int)shoulder_r->p.y);

        if(!control<float>(shoulder_l->p))
            draw_square(10, (int)shoulder_l->p.x, (int)shoulder_l->p.y);

        head->search(.5, 200, .2);
        neck->search(.25, 40, .2);
        hips->search(.25, 25, .2);
        shoulder_r->search(.25, 25, .2);
        shoulder_l->search(.25, 25, .2);

        Vect<float> u(neck->p.x - hips->p.x, neck->p.y - hips->p.y);
        float k = lenght_neck_hips / normal(u);
        neck->p.x = k * u.x + hips->p.x;
        neck->p.y = k * u.y + hips->p.y;

        u.x = head->p.x - neck->p.x;
        u.y = head->p.y - neck->p.y;
        k = lenght_head_neck / normal(u);
        head->p.x = k * u.x + neck->p.x;
        head->p.y = k * u.y + neck->p.y;

        vect_imgs.push_back(*frame);
        // cvReleaseImage(&buffer_img);

        //if(i == 4) break;

    }

    cvReleaseCapture(&capture);

}

bool Skeleton::circle_search_human(Vect<int> const& v0) {

    int dist0, dist1, dist2, dist3;

    Vect<int> v1 = v0 + Vect<int>(-1, 0);
    dist0 = comp(v1);

    Vect<int> v2 = v0 + Vect<int>(-1, -1);
    dist1 = comp(v2);

    Vect<int> v3 = v0 + Vect<int>(0, -1);
    dist2 = comp(v3);

    Vect<int> v4 = v0 + Vect<int>(1, -1);
    dist3 = comp(v4);

    int inf = 0;

    if (dist0 > 0) {
        filt->at(coord_gray(v0)) = filt->at(coord_gray(v1));
        surf.at(filt->at(coord_gray(v0))) += 1;
        inf = filt->at(coord_gray(v0));
    }

    if (dist1 > 0) {
        filt->at(coord_gray(v0)) = filt->at(coord_gray(v2));
        surf.at(filt->at(coord_gray(v0))) += 1;
        if (inf > 0 && inf < filt->at(coord_gray(v0))) {
            surf.at(inf) += surf.at(filt->at(coord_gray(v0)));
            surf.at(filt->at(coord_gray(v0))) = 0;
            replace(filt->at(coord_gray(v0)), inf);

        }
        inf = filt->at(coord_gray(v0));
    }

    if (dist2 > 0) {
        filt->at(coord_gray(v0)) = filt->at(coord_gray(v3));
        surf.at(filt->at(coord_gray(v0))) += 1;
        if (inf > 0 && inf < filt->at(coord_gray(v0))) {
            surf.at(inf) += surf.at(filt->at(coord_gray(v0)));
            surf.at(filt->at(coord_gray(v0))) = 0;
            replace(filt->at(coord_gray(v0)), inf);
        }
        inf = filt->at(coord_gray(v0));
    }

    if (dist3 > 0) {
        filt->at(coord_gray(v0)) = filt->at(coord_gray(v4));
        surf.at(filt->at(coord_gray(v0))) += 1;
        if (inf > 0 && inf < filt->at(coord_gray(v0))) {
            surf.at(inf) += surf.at(filt->at(coord_gray(v0)));
            surf.at(filt->at(coord_gray(v0))) = 0;
            replace(filt->at(coord_gray(v0)), inf);
        }
        inf = filt->at(coord_gray(v0));

    }

    if(inf > 0)
        return true;

    return false;
}

void Skeleton::search_human() {

    Vect<int> v;
    int id_partition = 0;
    surf.push_back(0);

    for(int y = 0; y < HEIGHT; ++y)
        for(int x = 0; x < WIDTH; ++x) {

            v.x = x;
            v.y = y;

            if ((uint8_t)buffer_img->imageData[coord_gbr<int>(v)] > green) {
                filt->at(coord_gray<int>(v)) = 0;
                surf.at(0) +=1;
                continue;
            }

            if ((uint8_t)buffer_img->imageData[coord_gbr<int>(v) + 1] < 255 - blue) {
                filt->at(coord_gray<int>(v)) = 0;
                surf.at(0) +=1;
                continue;
            }

            if(!circle_search_human(v)) {
                id_partition += 1;
                filt->at(coord_gray<int>(v)) = id_partition;
                surf.push_back(1);
            }
        }
}

int Skeleton::comp(Vect<int> const& a) {

    if(is_null(a))
        return -1;

    return filt->at(coord_gray(a));

}

void Skeleton::replace(int a, int b) {
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
        if (filt->at(i) == a)
            filt->at(i) = b;
}

void Skeleton::draw_square(int ray, int x_, int y_) {
    for (int x = x_ - ray; x < x_ + ray; ++x)
        for (int y = y_ - ray; y < y_ + ray; ++y)
            if (!control<int>(Vect<int>(x, y))) {
                frame->imageData[coord_gbr<int>(Vect<int>(x, y))] = 255;
                frame->imageData[coord_gbr<int>(Vect<int>(x, y)) + 1] = 255;
                frame->imageData[coord_gbr<int>(Vect<int>(x, y)) + 2] = 255;
            }
}
