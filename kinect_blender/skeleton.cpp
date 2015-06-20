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
            bone_head_neck.root0.first_search();
            hips = first_search_hips();
            head_neck = sqrt((bone_head_neck.root0.p.x - neck.x) * (bone_head_neck.root0.p.x - neck.x) + (bone_head_neck.root0.p.y - neck.y) * (bone_head_neck.root0.p.y - neck.y));
            neck_hips = sqrt((neck.x - hips.x) * (neck.x - hips.x) + (neck.y - hips.y) * (neck.y - hips.y));
        }

        if(!control<float>(bone_head_neck.root0.p))
            draw_square(10, (int)bone_head_neck.root0.p.x, (int)bone_head_neck.root0.p.y);

        if(!control<float>(neck))
            draw_square(10, (int)neck.x, (int)neck.y);

        if(!control<float>(hips))
            draw_square(10, (int)hips.x, (int)hips.y);

        bone_head_neck.root0.search(200, .2);
        neck = root_move(neck, bone_head_neck.root0.radius / 2, 200, .2);
        hips = root_move(hips, bone_head_neck.root0.radius / 16, 25, .2);

        Vect<float> u(neck.x - hips.x, neck.y - hips.y);
        float k = neck_hips / sqrt(u.x * u.x + u.y * u.y);
        neck.x = k * u.x + hips.x;
        neck.y = k * u.y + hips.y;

        u.x = bone_head_neck.root0.p.x - neck.x;
        u.y = bone_head_neck.root0.p.y - neck.y;
        k = head_neck / sqrt(u.x * u.x + u.y * u.y);
        bone_head_neck.root0.p.x = k * u.x + neck.x;
        bone_head_neck.root0.p.y = k * u.y + neck.y;

        vect_imgs.push_back(*frame);
        // cvReleaseImage(&buffer_img);

       // if(i == 6) break;

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


Vect<float> Skeleton::first_search_hips() {

    int x = 0, y = 0;
    int x_l = 0, x_r = 0;

    for(; x < WIDTH; ++x)
        if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1)) + 2)]) {

            for(;x < WIDTH;++x)
                if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1)) + 2)]) {
                    x_l = x;
                    x= WIDTH;
                }
        }

    for(x = WIDTH - 1; x >= 0; --x)
        if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1)) + 2)])
            for(; x > 0; --x)
                if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1)) + 2)]) {
                    x_r = x;
                    x= 0;
                }

    for(y = HEIGHT - 2; y >= 0; --y) {

        bool found = false;

        for(int cursor = x_l; cursor <= x_r; ++cursor) {
            if (!frame->imageData[(int)(coord_gbr<int>(Vect<int>(cursor, y)) + 2)]) {

                x_l = cursor;
                found = true;
                break;
            }

        }

        for(int cursor = x_r; cursor >= x_l; --cursor) {
            if (!frame->imageData[(int)(coord_gbr<int>(Vect<int>(cursor, y)) + 2)]) {

                x_r = cursor;
                found = true;
                break;
            }
        }

        if(!found)
            break;
    }

    return Vect<float>((float)x_l, (float)y);

}

Vect<float> cross(Vect<float> const &v1, Vect<float> const &w1, Vect<float> const &v2, Vect<float> const &w2) {

    float a1 = (v1.y - w1.y) / (v1.x - w1.x);
    float b1 = v1.y - v1.x * a1;

    float a2 = (v2.y - w2.y) / (v2.x - w2.x);
    float b2 = v2.y - v2.x * a2;

    float x = (b2 - b1) / (a1 - a2);
    float y = a1 * x + b1;

    return Vect<float>(x, y);
}
