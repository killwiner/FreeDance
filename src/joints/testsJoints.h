#ifndef TESTSJOINTS_H
#define TESTSJOINTS_H

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "joints.h"
#include "../rendering/loadimgs.h"
#include "../humanShape/humanShape.h"

namespace joints {

class TestsJoints: public QTestSuite {
     Q_OBJECT

public:
    TestsJoints(rendering::TestsOpenglR *render);
    virtual ~TestsJoints();

private:
    rendering::TestsOpenglR *render_;

private slots:

    void affichage_image_a_traiter();
    void contour();
};

}

#endif // TESTSJOINTS_H
