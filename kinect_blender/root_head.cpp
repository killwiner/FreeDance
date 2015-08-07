#include "root_head.h"

Head::Head() : Root() {
}

void Head::first_search(Vect<float> &neck) {

    Vect<float> v(WIDTH, HEIGHT, 0);
    Vect<float> top(WIDTH, HEIGHT, 0);
    Vect<float> bottom(0, 0, 0);
    Vect<float> left(0, 0, 0);
    Vect<float> right(0, 0, 0);

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
                    Vect<float> v_head = cross(left, right, bottom, top);

                    radius = (int)(right.x - left.x);
                    p = v_head;
                    return;
                }

            right.x = right_buff_x;
            left.x = left_buff_x;

            n_buff = n;
            n = 0;

            bottom.x = 0;
            n_bottom_x = 0;
        }

        for(float x = 0; x < WIDTH; ++x) {
            if (frame->imageData[(int)(coord_gbr<int>(Vect<int>(x, y, 0)) + 2)]) {

                v.x = x;
                v.y = y;

                if(v.x < left_buff_x)
                    left_buff_x = v.x;

                if(v.x > right_buff_x)
                    right_buff_x = v.x;

                if(is_null<float>(top))
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

