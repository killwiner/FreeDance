#ifndef JOINTS_H
#define JOINTS_H

#include "armature.h"

namespace armature {

#ifdef TESTS
class TestsJoints;
#endif // TESTS

class Joints: public Armature
{

#ifdef TESTS
    friend TestsJoints;
#endif

public:
    Joints(cv::Mat *Image, cv::Mat_<quint16> *idObject);
    void edgeDetector();
private:

    qint8 cx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    qint8 cy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    qint8 ox[8] = {0, 1, 1, 0, 0, -1, -1, -1};
    qint8 oy[8] = {-1, 0, 0, 1, 1, 1, 0, -1};
    quint8 alpha[8] = {5, 6, 7, 0, 1, 2, 3, 4};
    quint8 beta[8] = {1, 2, 3, 4, 5, 6, 7, 0};

    std::vector<v_p> Vgrad;
    bool getP_cannyImage(const qint16 &x, const qint16 &y);
    bool getP_idObject(const qint16 &x, const qint16 &y);
    void followPath(const quint16 &x, const quint16 &y);
    void startFollowPath();
};

}

#endif // JOINTS_H
