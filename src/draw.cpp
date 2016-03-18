#include "draw.h"

void draw_square(const int &ray, const int &x_, const int &y_, QSharedPointer<cv::Mat> &SP_mat) {

    Vect<int> v;

    for (v.x = x_ - ray; v.x < x_ + ray; ++v.x)
        for (v.y = y_ - ray; v.y < y_ + ray; ++v.y)
            if (!control<int>(v)) {
                SP_mat->PIXEL_COLOR_BLUE_VECT(v) = 255;
                SP_mat->PIXEL_COLOR_GREEN_VECT(v) = 255;
                SP_mat->PIXEL_COLOR_RED_VECT(v) = 255;
            }
}
