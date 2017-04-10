#include "testsRender.h"

#ifdef TESTS

namespace rendering {

    TestsRender::TestsRender(rendering::TestsOpenglR *render) : render_(render), width(400), height(400) {
    }

    TestsRender::~TestsRender() {
    }

    void TestsRender::affiche_fenetre() {
        render_->setGeometry(200, 200, width, height);
        render_->show();
    }

    void TestsRender::fenetre_active() {
        QVERIFY(QTest::qWaitForWindowActive(render_, 2000) == true);
    }

    void TestsRender::timer() {
        // vérifie si le loop du timer fonctionne
        QSignalSpy spy(render_, SIGNAL(test_timeout()));
        QVERIFY(spy.wait(2000));
    }

    void TestsRender::generation_d_un_triangle() {

        // pixels RGB
        quint16 inside_triangle_pixel[3], outside_triangle_pixel[3];

        QBENCHMARK
        render_->loop_paint(TEST_TRIANGLE, 40);

        // prend un pixel extérieur et intérieur au triangle
        glReadPixels(width / 2, height / 2, 1, 1, GL_RGB, GL_UNSIGNED_SHORT, inside_triangle_pixel);
        glReadPixels(width - 1, height - 1, 1, 1, GL_RGB, GL_UNSIGNED_SHORT, outside_triangle_pixel);
        // vérifie si le pixel est coloré
        QVERIFY(inside_triangle_pixel[0] || inside_triangle_pixel[1] || inside_triangle_pixel[2]);
        // vérifie si le pixel est noir
        QVERIFY(!outside_triangle_pixel[0] && !outside_triangle_pixel[1] && !outside_triangle_pixel[2]);

    }

    void TestsRender::affichage_d_une_image() {

        LoadImgs image;
        QVERIFY(image.load_image("rendering/image_test.png") == true);

        render_->setImages(image.getImages());

        QBENCHMARK
        render_->loop_paint(TEST_IMAGE, 40);

        // vérifie que le pixel soit bien rouge au niveau du petit cadre situé dans le coin
        quint16 pixel[3];
        glReadPixels(width - 1, height - 1, 1, 1, GL_RGB, GL_UNSIGNED_SHORT, pixel);
        QVERIFY(pixel[0] == 65535 && pixel[1] == 0 && pixel[2] == 0);
    }

    void TestsRender::affichage_d_une_video() {

        LoadImgs video;
        QVERIFY(video.load_video("rendering/video_test.ogg") == true);
        QSPVImage images = video.getImages();
        render_->setImages(images);
        render_->setGeometry(200, 200, images.data()->back().size().width, images.data()->back().size().height);

        QBENCHMARK
        render_->loop_paint(TEST_VIDEO, video.getImages()->size());
    }
}

#endif //TESTS
