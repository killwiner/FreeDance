#ifndef TESTSRENDER_H
#define TESTSRENDER_H

#ifdef TESTS

#include "testsuite.h"
#include "testsOpenglRender.h"
#include "loadimgs.h"

namespace rendering {

class TestsRender: public QTestSuite {
     Q_OBJECT

public:
    TestsRender(rendering::TestsOpenglR *render);
    virtual ~TestsRender();

private:
    rendering::TestsOpenglR *render_;

    int width, height;

private slots:

    void affiche_fenetre();
    void fenetre_active();
    void timer();
    void generation_d_un_triangle();
    void affichage_d_une_image();
    void affichage_d_une_video();
};

}

#endif // TESTS

#endif // TESTS_H
