#include "tests.h"

#ifdef TESTS

Tests::Tests(rendering::TestsOpenglR *renderImgs) {

    // Instanciation des classes pour lancer les tests
    //maths::TestsVector testsVector;
    //rendering::TestsRender testsRender(renderImgs);
    //draw::TestsDraw testsDraw(renderImgs);
    humanShape::TestsHumanShape testsHumanShape(renderImgs);
    //joints::TestsJoints testsJoints(renderImgs);
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
