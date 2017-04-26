#ifndef TESTS_H
#define TESTS_H

#ifdef TESTS

#include "maths/testsVector.h"
#include "rendering/testsRender.h"
#include "kinect/testsKinect.h"
#include "armature/testsHumanShape.h"
#include "draw/testsDraw.h"
#include "armature/testsJoints.h"

class Tests : public QObject
{
    Q_OBJECT

public:
    Tests(rendering::TestsOpenglR *renderImgs);
    virtual ~Tests();
};

#endif //TESTS

#endif // TESTS_H
