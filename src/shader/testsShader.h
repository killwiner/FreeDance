#ifndef TESTSSHADER_H
#define TESTSSHADER_H

#ifdef TESTS

#include "testsuite.h"
#include "shader.h"
#include "../rendering/testsOpenglRender.h"

namespace shader {

class TestsShader: public QTestSuite {
     Q_OBJECT

public:
    TestsShader(rendering::TestsOpenglR *render);
    virtual ~TestsShader();

private:
    rendering::TestsOpenglR *render_;

private slots:

    void chargement();
};

}

#endif // TESTS

#endif // TESTSSHADER_H
