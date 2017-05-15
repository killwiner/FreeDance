#ifndef TESTSSHADER_H
#define TESTSSHADER_H

#ifdef TESTS

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "../rendering/loadimgs.h"
#include "testsShaderRender.h"

namespace shader {

class TestsShader: public QTestSuite {
    Q_OBJECT

public:
    TestsShader();
    ~TestsShader();

private:

private slots:
    void testLoadFileFail();
    void testLoadFileSucces();
    void testBuildFail();
    void testBuildSucces();
    void testControlBuildFail();
    void testControlBuildSucces();
    void testControlLinkFail();
    void testControlLinkSucces();
    void testAffichage();
};

}

#endif // TESTS

#endif // TESTSSHADER_H
