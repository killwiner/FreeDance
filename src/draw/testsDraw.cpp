#include "testsDraw.h"

using namespace maths;

namespace draw {

TestsDraw::TestsDraw(rendering::TestsOpenglR *render) : render_(render)
{

}

void TestsDraw::drawLine()
{
    // crée une image avec fond noir
    cv::Mat Image(400, 400, CV_8UC3, cv::Scalar(0, 0, 0));
    Draw draw(&Image);
    QSPEspace espace = QSPEspace(new Espace(Image.size().width, Image.size().height, 0, 1000));
    draw.arrow(maths::Vector<float>(200.0f, 200.0f, .0f, espace), maths::Vector<float>(200.0f, 100.0f, .0f, espace));
    draw.arrow(maths::Vector<float>(200.0f, 200.0f, .0f, espace), maths::Vector<float>(210.0f, 210.0f, .0f, espace));
    draw.arrow(maths::Vector<float>(200.0f, 200.0f, .0f, espace), maths::Vector<float>(-100.0f, 200.0f, .0f, espace));
    
    QVERIFY(Image.at<cv::Vec3b>(200, 200)[RED] == 255
         && Image.at<cv::Vec3b>(200, 200)[GREEN] == 255
         && Image.at<cv::Vec3b>(200, 200)[BLUE] == 255
    );
    QVERIFY(Image.at<cv::Vec3b>(0, 0)[RED] == 0
         && Image.at<cv::Vec3b>(0, 0)[GREEN] == 0
         && Image.at<cv::Vec3b>(0, 0)[BLUE] == 0
    );

    render_->setImage(&Image);
    render_->setGeometry(200, 200, Image.size().width, Image.size().height);
    render_->show();
    render_->loop_paint(TEST_IMAGE, 40);
}

}
