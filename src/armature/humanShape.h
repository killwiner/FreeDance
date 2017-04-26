#ifndef HUMANSHAPE_H
#define HUMANSHAPE_H

#include "armature.h"

namespace armature {

#ifdef TESTS
class TestsHumanShape;
#endif // TESTS

class HumanShape: public Armature
{

#ifdef TESTS
    friend TestsHumanShape;
#endif

public:
    HumanShape(cv::Mat *Image);
    ~HumanShape();
    void filter(const qint16 &red_min, const qint16 &red_max, const qint16 &green_min, const qint16 &green_max, const qint16 &blue_min, const qint16 &blue_max);
    void detectObjects();
    void erazeSmallPartitions();

private:
    std::vector<quint16> VId_1, VId_2;
    std::vector<quint32> VSum_Ids;
    std::vector<bool> VId_check;
    quint16 id;

    void pixelOut(const quint16 &x, const quint16 &y, const qint16 &color_min, const qint16 &color_max, const qint8 &type_color);
    void linkId(const quint16 &id1, const quint16 &id2);
    void connectIds();
    void attribIds();
    void changeId(const quint16 &x, const quint16 &y, const quint16 &central_id);
    void searchAroundPixel(const quint16 &x, const quint16 &y);
    void searchPartitions();
    quint32 largestPartition();

};
}

#endif // HUMANSHAPE_H
