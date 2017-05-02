#ifndef ARMATURE_H
#define ARMATURE_H

#include <QtGlobal>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include "maths/vectors.h"

enum typeColor {
    RED, GREEN, BLUE
};

// tangeante en un point sur une courbe 2D
struct v_p {
    qint16 x, y;
    quint8 angle;
};

// armature, squelette humain
namespace armature {

class Armature 
{

public:
    Armature(cv::Mat *Image, cv::Mat_<quint16> *idObjects);

    // image reçue par la kinect
    cv::Mat *Image_;
    // identifiants sur les partitions affichées
    cv::Mat_<quint16> *idObjects_;
    // silouhette sur la partition principale
    cv::Mat cannyImage;
};

}

#endif // ARMATURE_H
