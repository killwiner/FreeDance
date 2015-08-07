#include "root_hand.h"

#include <stdio.h>

Hand::Hand() : Root() {
}

void Hand::first_search(bool l_r) {

    if (!l_r == false) {
        for (int x = 0; x < WIDTH; ++x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->imageData[coord_gbr(Vect<int>(x, y, 0)) + 2]) {
                    p.x = (float)x;
                    p.y = (float)y;
                    return;
                }
    }
    else {
        for (int x = WIDTH - 1; x >= 0; --x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->imageData[coord_gbr(Vect<int>(x, y, 0)) + 2]) {
                    p.x = (float)x;
                    p.y = (float)y;
                    return;
                }
    }
}
