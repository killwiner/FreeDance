#include "testsJoints.h"

namespace joints {

TestsJoints::TestsJoints(rendering::TestsOpenglR *render) : render_(render) {
}

TestsJoints::~TestsJoints() {
}

void TestsJoints::affichage_image_a_traiter() {
    LoadImgs image;
    QVERIFY(image.load_image("joints/image_test.png") == true);

    render_->setImages(image.getImages());
    render_->setGeometry(200, 200, image.getImages().data()->back().size().width, image.getImages().data()->back().size().height);
    render_->show();

    render_->loop_paint(TEST_IMAGE, 40);
}

void TestsJoints::contour() {

    LoadImgs image;
    QVERIFY(image.load_image("joints/image_test.png") == true);
    cv::Mat *Pimage = &image.getImages().data()->back();

    humanShape::HumanShape humanShape(Pimage);
    humanShape.filter(0, 0, 0, 0, 0, 255);
    //humanShape.detectObjects();
    //humanShape.erazePixelsSmallPartitions();

    render_->setImages(image.getImages());
    render_->setGeometry(200, 200, 400, 400);

    render_->loop_paint(TEST_IMAGE, 200);
}

}
