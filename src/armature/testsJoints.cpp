#include "testsJoints.h"

namespace armature {

TestsJoints::TestsJoints(rendering::TestsOpenglR *render) : render_(render) {
}

TestsJoints::~TestsJoints() {
}

void TestsJoints::contour() {

    LoadImgs image;
    QVERIFY(image.load_image("armature/image_test_2.png") == true);
    cv::Mat *Pimage = &image.getImages().data()->back();

    armature::HumanShape humanShape(Pimage);
    humanShape.filter(0, 0, 0, 0, 0, 255);
    humanShape.detectObjects();
    humanShape.erazeSmallPartitions();

    armature::Joints joints(Pimage, humanShape.idObjects_);
    joints.edgeDetector();

    for (quint16 y = 0; y < joints.cannyImage.size().height; ++y) {
        for (quint16 x = 0; x < joints.cannyImage.size().width; ++x)
            if(joints.cannyImage.at<quint8>(y, x))
                std::cout << "X";
            else
                std::cout << "0";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    QVERIFY(joints.cannyImage.at<quint8>(1, 1));
    QVERIFY(joints.cannyImage.at<quint8>(1, 2));
    QVERIFY(!joints.cannyImage.at<quint8>(1, 3));
}

void TestsJoints::testGetP_cannyImage()
{
    LoadImgs image;
    QVERIFY(image.load_image("armature/image_test_2.png") == true);
    cv::Mat *Pimage = &image.getImages().data()->back();

    armature::HumanShape humanShape(Pimage);
    humanShape.filter(0, 0, 0, 0, 0, 255);
    humanShape.detectObjects();
    humanShape.erazeSmallPartitions();

    armature::Joints joints(Pimage, humanShape.idObjects_);
    joints.edgeDetector();

    QVERIFY(!joints.getP_cannyImage(-1, -1));
    QVERIFY(!joints.getP_cannyImage(16, 16));
    QVERIFY(joints.getP_cannyImage(0, 3));
    QVERIFY(!joints.getP_cannyImage(0, 4));
}

void TestsJoints::testGetP_idObject()
{
    LoadImgs image;
    QVERIFY(image.load_image("armature/image_test_2.png") == true);
    cv::Mat *Pimage = &image.getImages().data()->back();

    armature::HumanShape humanShape(Pimage);
    humanShape.filter(0, 0, 0, 0, 0, 255);
    humanShape.detectObjects();
    humanShape.erazeSmallPartitions();

    armature::Joints joints(Pimage, humanShape.idObjects_);
    joints.edgeDetector();

    for (quint16 y = 0; y < joints.idObjects_->size().height; ++y) {
        for (quint16 x = 0; x < joints.idObjects_->size().width; ++x)
            if(joints.idObjects_->at<quint16>(y, x))
                std::cout << "X";
            else
                std::cout << "0";
        std::cout << std::endl;
    }
    std::cout << std::endl;
/*
    QVERIFY(!joints.getP_cannyImage(-1, -1));
    QVERIFY(!joints.getP_cannyImage(16, 16));
    QVERIFY(joints.getP_cannyImage(0, 3));
    QVERIFY(!joints.getP_cannyImage(0, 4));
*/
}

}
