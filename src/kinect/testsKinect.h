#ifndef TESTSKINECT_H
#define TESTSKINECT_H

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "kinect.h"

namespace kinect {

class TestsKinect: public QTestSuite
{

    Q_OBJECT

public:
    TestsKinect(rendering::TestsOpenglR *render);
    virtual ~TestsKinect();

private:
    rendering::TestsOpenglR *render_;
    kinect::Kinect *kinect;

private slots:
    void init_kinect();
    void affichage_kinect();
};

}

#endif // TESTSKINECT_H
