#ifndef HUMANSHAPE_H
#define HUMANSHAPE_H

#include <QtGlobal>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include "../defines.h"

namespace humanShape {

#ifdef TESTS
class TestsHumanShape;
#endif // TESTS

class HumanShape
{

#ifdef TESTS
    friend TestsHumanShape;
#endif

public:
    HumanShape(cv::Mat *Image);
    ~HumanShape();
    void filter(const qint16 &red_min, const qint16 &red_max, const qint16 &green_min, const qint16 &green_max, const qint16 &blue_min, const qint16 &blue_max);
    void detectObjects();
    void erazePixelsSmallPartitions();
    cv::Mat cloneIdObjects() const;

private:
    cv::Mat *Image_;
    cv::Mat_<quint16> *idObjects;

    std::vector<quint16> VId_1, VId_2, VSum_Ids;
    quint16 id;

    void pixelOut(const qint16 &x, const qint16 &y, const qint16 &color_min, const qint16 &color_max, const qint8 &type_color);
    void linkId(const quint16 &id1, const quint16 &id2);
    void connectIds();
    void attribIds();
    void changeId(const qint16 &x, const qint16 &y, const quint16 &central_id);
    void searchAroundPixel(const qint16 &x, const qint16 &y);
    void searchPartitions();
    quint16 largestPartition();

};
}

#endif // HUMANSHAPE_H
