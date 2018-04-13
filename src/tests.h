#ifndef TESTS_H
#define TESTS_H

#ifdef TESTS

#include "tools/testscircularvector.h"
#include "maths/testsVector.h"
#include "rendering/testsRender.h"
#include "kinect/testsKinect.h"
#include "armature/testsHumanShape.h"
#include "armature/testsSkeleton.h"
#include "draw/testsDraw.h"
#include "shader/testsShader.h"
#include "sound/testsSound.h"

class Tests : public QObject
{
    Q_OBJECT

public:
    Tests(rendering::TestsOpenglR *renderImgs);
    virtual ~Tests();
};

#endif //TESTS

#endif // TESTS_H
