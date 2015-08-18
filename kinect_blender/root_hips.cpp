#include "root_hips.h"

Hips::Hips(IplImage *frame_) : Root(frame_) {
}

void Hips::first_search() {

    int x = 0, y = 0;
    int x_l = 0, x_r = 0;

    for(; x < WIDTH; ++x)
        if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1, 0)) + 2)]) {

            for(;x < WIDTH;++x)
                if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1, 0)) + 2)]) {
                    x_l = x;
                    x= WIDTH;
                }
        }

    for(x = WIDTH - 1; x >= 0; --x)
        if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1, 0)) + 2)])
            for(; x > 0; --x)
                if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, HEIGHT - 1, 0)) + 2)]) {
                    x_r = x;
                    x= 0;
                }

    for(y = HEIGHT - 2; y >= 0; --y) {

        bool found = false;

        for(int cursor = x_l; cursor <= x_r; ++cursor) {
            if (!frame->imageData[(int)(coord_gbr<int>(Vect<int>(cursor, y, 0)) + 2)]) {

                x_l = cursor;
                found = true;
                break;
            }
        }

        for(int cursor = x_r; cursor >= x_l; --cursor) {
            if (!frame->imageData[(int)(coord_gbr<int>(Vect<int>(cursor, y, 0)) + 2)]) {

                x_r = cursor;
                found = true;
                break;
            }
        }

        if(!found)
            break;
    }

    p.x = (float)x_l;
    p.y = (float)y;

}
