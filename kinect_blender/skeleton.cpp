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

    int ray = 0;

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
                frame->imageData[coord_gbr(Vect(x, y))] = 0;
                frame->imageData[coord_gbr(Vect(x, y)) + 1] = 0;

                int g_color = filt->at(coord_gray(Vect(x, y)));
                if(filt->at(coord_gray(Vect(x, y))) == pos)
                    frame->imageData[coord_gbr(Vect(x, y)) + 2] = 255;
                else
                    frame->imageData[coord_gbr(Vect(x, y)) + 2] = 0;
                if(g_color > 0)
                    frame->imageData[coord_gbr(Vect(x, y))] = 255;
            }

        if(i == 0) {
            head = first_search_head(&ray);
            hips = first_search_hips();
            head_neck = sqrt((head.x - neck.x) * (head.x - neck.x) + (head.y - neck.y) * (head.y - neck.y));
            neck_hips = sqrt((neck.x - hips.x) * (neck.x - hips.x) + (neck.y - hips.y) * (neck.y - hips.y));
        }

        if(!control_f(head))
            draw_square(10, (int)head.x, (int)head.y);

        if(!control_f(neck))
            draw_square(10, (int)neck.x, (int)neck.y);

        if(!control_f(hips))
            draw_square(10, (int)hips.x, (int)hips.y);

        head = root_move(head, ray, 200, .2);
        neck = root_move(neck, ray / 2, 200, .2);
        hips = root_move(hips, ray / 16, 25, .2);

        Vect_f u(neck.x - hips.x, neck.y - hips.y);
        float k = neck_hips / sqrt(u.x * u.x + u.y * u.y);
        neck.x = k * u.x + hips.x;
        neck.y = k * u.y + hips.y;

        u.x = head.x - neck.x;
        u.y = head.y - neck.y;
        k = head_neck / sqrt(u.x * u.x + u.y * u.y);
        head.x = k * u.x + neck.x;
        head.y = k * u.y + neck.y;

        vect_imgs.push_back(*frame);
        // cvReleaseImage(&buffer_img);

       // if(i == 6) break;

    }

    cvReleaseCapture(&capture);

}

bool Skeleton::circle_search_head(Vect const& v0) {

    int dist0, dist1, dist2, dist3;

    Vect v1 = v0 + Vect(-1, 0);
    dist0 = comp(v1);

    Vect v2 = v0 + Vect(-1, -1);
    dist1 = comp(v2);

    Vect v3 = v0 + Vect(0, -1);
    dist2 = comp(v3);

    Vect v4 = v0 + Vect(1, -1);
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

    Vect v;
    int id_partition = 0;
    surf.push_back(0);

    for(int y = 0; y < HEIGHT; ++y)
        for(int x = 0; x < WIDTH; ++x) {

            v.x = x;
            v.y = y;

            if ((uint8_t)buffer_img->imageData[coord_gbr(v)] > green) {
                filt->at(coord_gray(v)) = 0;
                surf.at(0) +=1;
                continue;
            }

            if ((uint8_t)buffer_img->imageData[coord_gbr(v) + 1] < 255 - blue) {
                filt->at(coord_gray(v)) = 0;
                surf.at(0) +=1;
                continue;
            }

            if(!circle_search_head(v)) {
                id_partition += 1;
                filt->at(coord_gray(v)) = id_partition;
                surf.push_back(1);
            }
        }
}

int Skeleton::comp(Vect const& a) {

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
            if (!control(Vect(x, y))) {
                frame->imageData[coord_gbr(Vect(x, y))] = 255;
                frame->imageData[coord_gbr(Vect(x, y)) + 1] = 255;
                frame->imageData[coord_gbr(Vect(x, y)) + 2] = 255;
            }
}

Vect_f Skeleton::first_search_head(int *ray) {

    Vect_f v(WIDTH, HEIGHT);
    Vect_f top(WIDTH, HEIGHT);
    Vect_f bottom(0, 0);
    Vect_f left(0, 0);
    Vect_f right(0, 0);

    float n = 0, y_l = 0, n_buff = 0, y_l_n = 0;
    bool ch_y = false, top_flag = true;
    float n_top_x = 0, n_bottom_x = 0;
    float left_buff_x = WIDTH, right_buff_x = 0;

    for(float y = 0; y < HEIGHT; ++y) {
        ch_y = true;

        if (y_l == 8) {
            top_flag = false;
            y_l = 0;
            ++y_l_n;

            if (n > n_buff * 1.3 && y_l_n > 4) {

                    bottom.y = y - 8;
                    top.x = top.x / n_top_x;
                    bottom.x = bottom.x / n_bottom_x;
                    neck.y = y;
                    neck.x = bottom.x;
                    right.y = left.y = top.y + (bottom.y - top.y) / 2;
                    Vect_f v_head = cross(left, right, bottom, top);

                    *ray = (int)(right.x - left.x);

                    return v_head;
                }

            right.x = right_buff_x;
            left.x = left_buff_x;

            n_buff = n;
            n = 0;

            bottom.x = 0;
            n_bottom_x = 0;
        }

        for(float x = 0; x < WIDTH; ++x) {
            if (frame->imageData[(int)(coord_gbr(Vect(x, y)) + 2)]) {

                v.x = x;
                v.y = y;

                if(v.x < left_buff_x)
                    left_buff_x = v.x;

                if(v.x > right_buff_x)
                    right_buff_x = v.x;

                if(is_null_f(top))
                    top.y = y;

                    if (top_flag == true) {
                        top.x += v.x;
                        ++n_top_x;
                    }

                bottom.x += v.x;
                ++n_bottom_x;

                if(ch_y == true) {
                    ch_y = false;
                    ++y_l;
                }

                ++n;
            }
        }
        ch_y = false;
    }
}

Vect_f Skeleton::first_search_hips() {

    int x = 0, y = 0;
    int x_l = 0, x_r = 0;

    for(; x < WIDTH; ++x)
        if (frame->imageData[(int)(coord_gbr(Vect(x, HEIGHT - 1)) + 2)]) {

            for(;x < WIDTH;++x)
                if (frame->imageData[(int)(coord_gbr(Vect(x, HEIGHT - 1)) + 2)]) {
                    x_l = x;
                    x= WIDTH;
                }
        }

    for(x = WIDTH - 1; x >= 0; --x)
        if (frame->imageData[(int)(coord_gbr(Vect(x, HEIGHT - 1)) + 2)])
            for(; x > 0; --x)
                if (frame->imageData[(int)(coord_gbr(Vect(x, HEIGHT - 1)) + 2)]) {
                    x_r = x;
                    x= 0;
                }

    for(y = HEIGHT - 2; y >= 0; --y) {

        bool found = false;

        for(int cursor = x_l; cursor <= x_r; ++cursor) {
            if (!frame->imageData[(int)(coord_gbr(Vect(cursor, y)) + 2)]) {

                x_l = cursor;
                found = true;
                break;
            }

        }

        for(int cursor = x_r; cursor >= x_l; --cursor) {
            if (!frame->imageData[(int)(coord_gbr(Vect(cursor, y)) + 2)]) {

                x_r = cursor;
                found = true;
                break;
            }
        }

        if(!found)
            break;
    }

    return Vect_f((float)x_l, (float)y);

}

Vect_f Skeleton::root_move(Vect_f v, int ray_min, int ray_max, float deep) {

    int nbr_rays = 32;
    float n_ray = 0, teta = 0, l_ray = 0;
    int max = 0;
    float alpha = 0;
    std::vector<int> vect_rays(nbr_rays, 0);

    for(float ray = 1; ray < (float)ray_max; ++ray) {
        n_ray = 0;
        l_ray = ray;
        for(int j = 0; j < nbr_rays; ++j) {
            teta = (float)j * 2 * PI / (float)nbr_rays;
            Vect_f p(v.x + ray * cosf(teta), v.y + ray * sinf(teta));
            if(control_f(p)) {
                ++n_ray;
                vect_rays.at(j) += 1;
                continue;
            }
            if (!frame->imageData[coord_gbr_f(p) + 2]) {
                frame->imageData[coord_gbr_f(p) + 1] = 255;
                ++n_ray;
                vect_rays.at(j) += 1;
            }
            else {
                frame->imageData[coord_gbr_f(p)] = 255;
                frame->imageData[coord_gbr_f(p) + 1] = 255;

            }

            if(n_ray > deep * (float)nbr_rays && ray > (float)ray_min * .5) {

                ray = (float)ray_max;
                break;
            }
        }
    }

    int i = 0;

    for (std::vector<int>::iterator it = vect_rays.begin(); it != vect_rays.end(); ++it) {

        if (max < *it) {
             max = *it;
             alpha = i;
        }
        ++i;
    }

    Vect_f r(v.x -(float)max / 2 * cosf(alpha * PI * 2 / (float)nbr_rays), v.y - (float)max / 2 * sinf(alpha * PI * 2 / (float)nbr_rays));

    if (!control_f(v))
        if(!frame->imageData[coord_gbr_f(v)] && max > 0) {
            r.x = -r.x;
            r.y = -r.y;
        }

    return r;

}

