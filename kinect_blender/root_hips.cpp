#include "root_hips.h"

Hips::Hips(IplImage *frame_) : Root(frame_) {
}

void Hips::first_search() {

    int x, y;
    int x_l = 0, x_r = 0;

    s = Vect<float>(0.000000, 9.236752, 0.030254);

    // nous cherchons à partir de la ligne la plus basse le premier pixel rouge en partant de la gauche vers la droite
    // We seek from the lowest line the first red pixel from left to right
    for(x = 0; x < WIDTH; ++x)
        if (frame->PIXEL_COLOR_RED(x, HEIGHT - 1))

            // nous continuons dans la zone rouge jusqu'à la zone noire. x_l prend alors la valeur des coordonnées horizontales du dernier point
            // We continue in the red zone until the black area. x_l then takes the value of the horizontal coordinates of the last point
            for(;x < WIDTH;++x)
                if (frame->PIXEL_COLOR_RED(x, HEIGHT - 1)) {
                    x_l = x;
                    // sortie de boulce
                    // exit the loop
                    x= WIDTH;
                }

    // nous cherchons à partir de la ligne la plus basse le premier pixel rouge en partant de la droite vers la gauche
    // We seek from the lowest line the first red pixel from right to left
    for(x = WIDTH - 1; x >= 0; --x)
        if (frame->PIXEL_COLOR_RED(x, HEIGHT - 1))

            // nous continuons dans la zone rouge jusqu'à la zone noire. x_l prend alors la valeur des coordonnées horizontales du dernier point
            // We continue in the red zone until the black area. x_l then takes the value of the horizontal coordinates of the last point
            for(; x > 0; --x)
                if (frame->PIXEL_COLOR_RED(x, HEIGHT - 1)) {
                    x_r = x;
                    // sortie de boulce
                    // exit the loop
                    x= 0;
                }

    // nous continuons à remonter l'image
    // we keep up the image
    for(y = HEIGHT - 2; y >= 0; --y) {

        bool found = false;

        // nous approchons d'avantage x_l vers x_r tant que l'on est dans la zone rouge
        // we are approaching x_l to x_r as it is in the red zone
        for(int cursor = x_l; cursor <= x_r; ++cursor) {
            if (!frame->PIXEL_COLOR_RED(cursor, y)) {

                x_l = cursor;
                found = true;
                break;
            }
        }

        // nous approchons d'avantage x_r vers x_l tant que l'on est dans la zone rouge
        // we are approaching x_r to x_l as it is in the red zone
        for(int cursor = x_r; cursor >= x_l; --cursor) {
            if (!frame->PIXEL_COLOR_RED(cursor, y)) {

                x_r = cursor;
                found = true;
                break;
            }
        }

        // il n'y a plus de pixels rougles entre les deux jambes, nous sommes situés au niveau du bassin
        // we can't find red pixels between the two legs, we are located in the pelvis
        if(!found)
            break;
    }

    p.x = (float)x_l;
    p.y = (float)y;

}
