#include "tests.h"

#ifdef TESTS

Tests::Tests(rendering::TestsOpenglR *renderImgs) {

    // Instanciation des classes pour lancer les tests
/*
    tools::TestsCircularVector testsCircularVector;
    maths::TestsVector testsVector;
    rendering::TestsRender testsRender(renderImgs);
    shader::TestsShader testsShader;
*/
    armature::TestsHumanShape testsHumanShape(renderImgs);
    /*
    armature::TestsSkeleton testsSkeleton(renderImgs);
    draw::TestsDraw testsDraw(renderImgs);
    kinect::TestsKinect testsKinect;
    */
    std::vector<QObject*>::iterator iSuite;
    for (iSuite = QTestSuite::m_suites.begin(); iSuite != QTestSuite::m_suites.end(); ++iSuite)
    {
        QTest::qExec(*iSuite);
    }
}

Tests::~Tests() {
}

#endif //TESTS
