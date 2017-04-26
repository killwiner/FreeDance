#ifndef TESTSHUMANSHAPE_H
#define TESTSHUMANSHAPE_H

#ifdef TESTS

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "humanShape.h"
#include "../rendering/loadimgs.h"

namespace armature {

class TestsHumanShape: public QTestSuite {
     Q_OBJECT

public:
    TestsHumanShape(rendering::TestsOpenglR *render);
    virtual ~TestsHumanShape();

private:
    rendering::TestsOpenglR *render_;

private slots:

    void affichage_image_a_traiter();
    void pixelOutTest();
    void affichage_image_filtree();
    void linkIdTest();
    void changeIdTest();
    void searchAroundPixelTest();
    void connectIdsTest();
    void affichage_objets();
    void largestPartition();
    void erazePixelsSmallPartitions();
};

}

#endif // TESTS

#endif // TESTSHUMANSHAPE_H
