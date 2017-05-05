#include "tests.h"

#ifdef TESTS

Tests::Tests(rendering::TestsOpenglR *renderImgs) {

    // Instanciation des classes pour lancer les tests

    //maths::TestsVector testsVector;
    //rendering::TestsRender testsRender(renderImgs);
    shader::TestsShader testsShader;
    //armature::TestsHumanShape testsHumanShape(renderImgs);
    //draw::TestsDraw testsDraw(renderImgs);
    //armature::TestsJoints testsJoints(renderImgs);
    //kinect::TestsKinect testsKinect(renderImgs);

    std::vector<QObject*>::iterator iSuite;
    for (iSuite = QTestSuite::m_suites.begin(); iSuite != QTestSuite::m_suites.end(); ++iSuite)
    {
        QTest::qExec(*iSuite);
    }
}

Tests::~Tests() {
}

#endif //TESTS
