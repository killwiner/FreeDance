#ifndef TESTSSHADER_H
#define TESTSSHADER_H

#ifdef TESTS

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "shader.h"

namespace shader {

class TestsShader: public QTestSuite {
    Q_OBJECT

public:
//    TestsShader();
    virtual ~TestsShader();

private:

private slots:
    void testLoadFileFail();
    void testLoadFileSucces();
    void testBuildFail();
    void testBuildSucces();
};

}

#endif // TESTS

#endif // TESTSSHADER_H
