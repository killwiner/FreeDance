#include "draw.h"

namespace draw {

Draw::Draw(cv::Mat *Image) : Image_(Image)
{

}

void Draw::arrow(const maths::Vector<float> &from, const maths::Vector<float> &to)
{
    components<float> comp_from, comp_to;
    from.get_comp(comp_from);
    to.get_comp(comp_to);
    cv::arrowedLine(cv::InputOutputArray(*Image_), cv::Point2f(comp_from.x, comp_from.y), cv::Point2f(comp_to.x, comp_to.y), cv::Scalar(0, 255, 0), 2, CV_AA, 0, 0.2);
}

}
