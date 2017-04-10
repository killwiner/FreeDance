#ifndef JOINTS_H
#define JOINTS_H

#include <QtGlobal>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include "../defines.h"

namespace joints {

#ifdef TESTS
class TestsJoints;
#endif // TESTS

class Joints
{

#ifdef TESTS
    friend TestsJoints;
#endif

public:
    Joints(cv::Mat *Image);
private:
    cv::Mat *Image_;
};

}

#endif // JOINTS_H
