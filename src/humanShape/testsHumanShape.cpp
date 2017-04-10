#include "testsHumanShape.h"

#ifdef TESTS

namespace humanShape {

    TestsHumanShape::TestsHumanShape(rendering::TestsOpenglR *render) : render_(render) {
    }

    TestsHumanShape::~TestsHumanShape() {
    }

    void TestsHumanShape::affichage_image_a_traiter() {

        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        render_->setImages(image.getImages());
        render_->setGeometry(200, 200, 400, 400);
        render_->show();

        QBENCHMARK
        render_->loop_paint(TEST_IMAGE, 40);
    }

    void TestsHumanShape::pixelOutTest() {

        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);
        humanShape.idObjects->at<quint16>(0, 3) = 1;
        humanShape.idObjects->at<quint16>(0, 4) = 1;

        // le pixel (4, 0) reste colorisé alors que le pixel (3, 0) doit devenir noir et obtenir un identifiant à 0
        humanShape.pixelOut(4, 0, 0, 255, BLUE);
        QVERIFY(humanShape.idObjects->at<quint16>(0, 4) == 1);
        QVERIFY(Pimage->at<cv::Vec3b>(0, 4)[0] == 200); // rouge
        QVERIFY(Pimage->at<cv::Vec3b>(0, 4)[1] == 50); // vert
        QVERIFY(Pimage->at<cv::Vec3b>(0, 4)[2] == 0); // bleu

        //QVERIFY(Pimage->at<cv::Vec3b>(0, 3)[0] == 0);

        humanShape.pixelOut(3, 0, 0, 255, BLUE);
        QVERIFY(humanShape.idObjects->at<quint16>(0, 3) == 0);
        QVERIFY(Pimage->at<cv::Vec3b>(0, 3)[0] == 0); // rouge
        QVERIFY(Pimage->at<cv::Vec3b>(0, 3)[1] == 0); // vert
        QVERIFY(Pimage->at<cv::Vec3b>(0, 3)[2] == 0); // bleu
    }

    void TestsHumanShape::affichage_image_filtree() {

        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);
        humanShape.filter(0, 0, 0, 0, 0, 255);

        std::cout << "début filtrage" << std::endl;
        for(qint16 y = 0; y < Pimage->size().height; ++y) {
            for(qint16 x = 0; x < Pimage->size().width; ++x) {
                std::cout << humanShape.idObjects->at<quint16>(y, x) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\nfin filtrage" << std::endl;

        render_->setImages(image.getImages());

        render_->loop_paint(TEST_IMAGE, 40);
    }

    void TestsHumanShape::linkIdTest()
    {
        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        HumanShape humanShape(&image.getImages().data()->back());

        // vérifie si les identifiants 4 et 6 sont liés
        humanShape.linkId(4, 6);
        QVERIFY(humanShape.VId_1.back() == 4);
        QVERIFY(humanShape.VId_2.back() == 6);
    }

    void TestsHumanShape::changeIdTest()
    {
        cv::Mat image(16, 16, CV_8UC3, cv::Scalar(0, 0, 0));

        HumanShape humanShape(&image);
        humanShape.VSum_Ids.resize(10, 0);

        //vérifie si le pixel n'obtient pas d'identifiant
        humanShape.changeId(0, 0, 8);
        QVERIFY(humanShape.idObjects->at<quint16>(0, 0) == 0);

        //vérifie si le pixel obtient un nouveau identifiant
        humanShape.idObjects->at<qint16>(2, 2) = 1;
        humanShape.changeId(2, 2, 8);
        QVERIFY(humanShape.idObjects->at<quint16>(2, 2) == 8);
        QVERIFY(humanShape.VSum_Ids.at(8) == 1);

        //vérifie si le pixel garde son identifiant et s'il est lié à l'identifiant du pixel précédent
        humanShape.idObjects->at<qint16>(4, 4) = 8;
        humanShape.idObjects->at<qint16>(5, 4) = 9;
        humanShape.changeId(4, 5, 8);
        QVERIFY(humanShape.idObjects->at<quint16>(5, 4) == 9);
        QVERIFY(humanShape.VId_1.back() == 8);
        QVERIFY(humanShape.VId_2.back() == 9);

    }

    void TestsHumanShape::searchAroundPixelTest() {
        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);
        humanShape.filter(0, 0, 0, 0, 0, 255);

        // l'identifiant commence à 7
        humanShape.id = 7;
        humanShape.idObjects->at<quint16>(1, 2) = 5;

        humanShape.searchAroundPixel(1, 2);

        QVERIFY(humanShape.idObjects->at<quint16>(1, 0) == 0);
        QVERIFY(humanShape.idObjects->at<quint16>(1, 1) == humanShape.id);
        QVERIFY(humanShape.idObjects->at<quint16>(1, 2) == 5);
        QVERIFY(humanShape.idObjects->at<quint16>(2, 2) == humanShape.id);
        QVERIFY(humanShape.idObjects->at<quint16>(3, 0) == 0);
        QVERIFY(humanShape.idObjects->at<quint16>(3, 1) == 0);
        QVERIFY(humanShape.idObjects->at<quint16>(4, 2) == 0);
    }

    void TestsHumanShape::connectIdsTest()
    {
        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);

        //entrée : 2-3, 5-6, 6-2, 8-4
        //sortie :  2-3, 5-3, 6-3, 8-4

        humanShape.VId_1.push_back(2);
        humanShape.VId_2.push_back(3);
        humanShape.VId_1.push_back(5);
        humanShape.VId_2.push_back(6);
        humanShape.VId_1.push_back(6);
        humanShape.VId_2.push_back(2);
        humanShape.VId_1.push_back(8);
        humanShape.VId_2.push_back(4);

        humanShape.connectIds();

        QVERIFY(humanShape.VId_1.at(0) == 2);
        QVERIFY(humanShape.VId_2.at(0) == 3);
        QVERIFY(humanShape.VId_1.at(1) == 5);
        QVERIFY(humanShape.VId_2.at(1) == 3);
        QVERIFY(humanShape.VId_1.at(2) == 6);
        QVERIFY(humanShape.VId_2.at(2) == 3);
        QVERIFY(humanShape.VId_1.at(3) == 8);
        QVERIFY(humanShape.VId_2.at(3) == 4);
    }

    void TestsHumanShape::affichage_objets()
    {
        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);
        humanShape.filter(0, 0, 0, 0, 0, 255);
        humanShape.detectObjects();

        //cv::Mat idObjects = humanShape.cloneIdObjects();

        for(qint16 y = 0; y < Pimage->size().height; ++y) {
            for(qint16 x = 0; x < Pimage->size().width; ++x) {
                std::cout << humanShape.idObjects->at<quint16>(y, x) << " ";
                Pimage->at<cv::Vec3b>(y, x)[0] = humanShape.idObjects->at<quint16>(y, x) * 32; // rouge
                Pimage->at<cv::Vec3b>(y, x)[1] = humanShape.idObjects->at<quint16>(y, x) * 32; // vert
                Pimage->at<cv::Vec3b>(y, x)[2] = humanShape.idObjects->at<quint16>(y, x) * 32; // bleu

            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        QVERIFY(humanShape.idObjects->at<quint16>(5, 9) == 7);
        QVERIFY(humanShape.idObjects->at<quint16>(2, 2) == 2);
        QVERIFY(humanShape.idObjects->at<quint16>(2, 17) == 4);

        render_->setImages(image.getImages());
        render_->setGeometry(200, 200, 400, 400);

        render_->loop_paint(TEST_IMAGE, 40);
    }

    void TestsHumanShape::largestPartition() {
        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);
        humanShape.filter(0, 0, 0, 0, 0, 255);
        humanShape.detectObjects();

        QVERIFY(humanShape.largestPartition() == 7);
    }

    void TestsHumanShape::erazePixelsSmallPartitions() {
        LoadImgs image;
        QVERIFY(image.load_image("humanShape/image_test.png") == true);

        cv::Mat *Pimage = &image.getImages().data()->back();

        HumanShape humanShape(Pimage);
        humanShape.filter(0, 0, 0, 0, 0, 255);
        humanShape.detectObjects();
        humanShape.erazePixelsSmallPartitions();

        for(qint16 y = 0; y < Pimage->size().height; ++y) {
            for(qint16 x = 0; x < Pimage->size().width; ++x)
                std::cout << humanShape.idObjects->at<quint16>(y, x) << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;

        QVERIFY(humanShape.idObjects->at<quint16>(5, 9) == 7);
        QVERIFY(humanShape.idObjects->at<quint16>(2, 2) == 0);

        render_->setImages(image.getImages());
        render_->setGeometry(200, 200, 400, 400);

        render_->loop_paint(TEST_IMAGE, 40);
    }
}

#endif //TESTS
