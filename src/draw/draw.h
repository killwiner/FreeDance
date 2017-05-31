#ifndef DRAW_H
#define DRAW_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../maths/vectors.h"

namespace draw {

class Draw
{
public:
    Draw(cv::Mat *Image);
    void arrow(const maths::Vector<float> &from, const maths::Vector<float> &to);

private:
    cv::Mat *Image_;
};

}

#endif // DRAW_H
