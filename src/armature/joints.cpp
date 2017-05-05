#include "joints.h"

namespace armature {

Joints::Joints(cv::Mat *Image, cv::Mat_<quint16> *idObject) : Armature(Image, idObject) {}

void Joints::edgeDetector() {
    cv::Mat grayImage(Image_->size(), CV_8UC1);
    cv::cvtColor(*Image_, grayImage, CV_BGR2GRAY);
    cv::Canny(grayImage, cannyImage, 50, 150, 3);
}

bool Joints::getP_cannyImage(const qint16 &x, const qint16 &y) {
    if(x < 0 || y < 0 || y >= cannyImage.size().height || x >= cannyImage.size().width)
        return false;
    return cannyImage.data[y * cannyImage.size().width + x];
}

bool Joints::getP_idObject(const qint16 &x, const qint16 &y) {
    if(x < 0 || y < 0 || y >= idObjects_->size().height || x >= idObjects_->size().width)
        return false;
    return idObjects_->at<quint16>(y, x);
}

void Joints::followPath(const quint16 &x, const quint16 &y) {

    cannyImage.data[y * cannyImage.size().width + x] = 0;
    Vgrad.push_back(v_p());
    Vgrad.back().x = x;
    Vgrad.back().y = y;

    for(quint8 i = 0; i < 8; ++i)
        if(getP_cannyImage(x+cx[i], y+cy[i])) {
            if(getP_idObject(x+ox[i], y+oy[i]))
                Vgrad.back().angle = alpha[i];
            else
                Vgrad.back().angle = beta[i];
            followPath(x+cx[i], y+cy[i]);
        }
}

void Joints::startFollowPath() {
    for (quint16 y = 0; y < cannyImage.size().height; ++y)
        for (quint16 x = 0; x < cannyImage.size().width; ++x)
            if(cannyImage.data[y * cannyImage.size().width + x]) {
                followPath(x, y);
                return;
            }
}
}
