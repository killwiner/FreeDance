#ifndef TESTSJOINTS_H
#define TESTSJOINTS_H

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "joints.h"
#include "../rendering/loadimgs.h"
#include "../armature/humanShape.h"

namespace armature {

class TestsJoints: public QTestSuite {
     Q_OBJECT

public:
    TestsJoints(rendering::TestsOpenglR *render);
    virtual ~TestsJoints();

private:
    rendering::TestsOpenglR *render_;

private slots:
    void contour();
    void testGetP_cannyImage();
    void testGetP_idObject();
    void testFollowPath();
    void testStartFollowPath();
};

}

#endif // TESTSJOINTS_H
