#ifndef ARMATURE_H
#define ARMATURE_H

#include <QtGlobal>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include "maths/vectors.h"
#include "../defines.h"

struct v_p {
    qint16 x, y;
    quint8 angle;
};

namespace armature {

class Armature 
{

public:
    Armature(cv::Mat *Image, cv::Mat_<quint16> *idObjects);

    cv::Mat *Image_;
    cv::Mat_<quint16> *idObjects_;
    cv::Mat cannyImage;
};

}

#endif // ARMATURE_H
