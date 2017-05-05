#include "testsKinect.h"

namespace kinect {

TestsKinect::TestsKinect(rendering::TestsOpenglR *render) : render_(render) {
    kinect = nullptr;
}

TestsKinect::~TestsKinect() {
    if(kinect) {
        kinect->wait();
        delete kinect;
    }
}

void TestsKinect::init_kinect() {
    try {
        kinect = new Kinect();
        connect(render_, SIGNAL(nextSignal()), kinect , SLOT(next()));
    }
    catch (const std::string &Msg) {
        QFAIL("can't init the Kinect.");
    }
}

void TestsKinect::affichage_kinect()
{

    if(kinect == nullptr)
        QFAIL("Kinect is not initialized.");

    render_->setGeometry(200, 200, WIDTH_KINECT, HEIGHT_KINECT);
    render_->show();

    kinect->start();
    render_->setImage(kinect->getImage());
    render_->loop_paint(TEST_IMAGE, 500);
    kinect->stop();

}

}
