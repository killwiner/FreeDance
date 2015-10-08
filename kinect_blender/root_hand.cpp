#include "root_hand.h"

#include <stdio.h>

Hand::Hand(IplImage *frame_) : Root(frame_) {

}

// Recherche les mains gauche et droite en partant du côté droit et gauche de l'image
// Search hands from the sides of the picture
void Hand::first_search(bool l_r) {

    // right hand
    // main droite
    if (!l_r == false) {
        s = Vect<float>(-1.345895, -1.286322, 1.920122);

        for (int x = 0; x < WIDTH; ++x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->PIXEL_COLOR_RED(x, y)) {
                    p.x = (float)x;
                    p.y = (float)y;
                    return;
                }
    }
    else {
        s = Vect<float>(1.345895, -1.286322, 1.920122);
        for (int x = WIDTH - 1; x >= 0; --x)
            for (int y = 0; y < HEIGHT; ++y)
                if (frame->PIXEL_COLOR_RED(x, y)) {
                    p.x = (float)x;
                    p.y = (float)y;
                    return;
                }
    }
}
