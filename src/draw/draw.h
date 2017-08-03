#ifndef DRAW_H
#define DRAW_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../maths/vectors.h"

#define S_RED cv::Scalar(255, 0, 0)
#define S_GREEN cv::Scalar(0, 255, 0)
#define S_BLUE cv::Scalar(0, 0, 255)
#define S_YELLOW cv::Scalar(255, 255, 0)
#define S_SKY_BLUE cv::Scalar(0, 255, 255)
#define S_PURPLE cv::Scalar(255, 0, 255)

namespace draw {

class Draw
{
public:
    Draw(cv::Mat *Image);
    void arrow(const maths::Vector<float> &from, const maths::Vector<float> &to);
    void point(const maths::Vector<float> &center, const cv::Scalar &color);

private:
    cv::Mat *Image_;
};

}

#endif // DRAW_H
