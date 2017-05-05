#include "testsShader.h"

#ifdef TESTS

namespace shader {

//    TestsShader::TestsShader() {
//}
    TestsShader::~TestsShader() {}

    void TestsShader::testLoadFileFail() {
	    Shader shader(QString("empty"), QString("empty"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);
        try {
            shader.loadFile(QString("empty"));
            QFAIL("empty file loader");
        }
        catch(...) {
        }
    }

    void TestsShader::testLoadFileSucces() {
	    Shader shader(QString("shader/testsShaderSucces.vp"), QString("shader/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);
        try {
            shader.loadFile(QString("shader/testsShaderSucces.vp"));
        }
        catch (...) {
            std::cerr << "Exception caught !!" << std::endl;
        }

        QString match = QString("uniform vec3");
        QVERIFY(shader.Source.contains(match));
    }

    void TestsShader::testBuildFail() {
	    Shader shader(QString("empty"), QString("empty"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);
        try {
            shader.buildShader(shader.vertexID, GL_VERTEX_SHADER, shader.vertexSource_);
            QFAIL("empty file loader");
        }
        catch(...) {
        }
    }
    void TestsShader::testBuildSucces() {
	    Shader shader(QString("shader/testsShaderSucces.vp"), QString("shader/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);
        try {
            shader.buildShader(shader.vertexID, GL_VERTEX_SHADER, shader.vertexSource_);
        }
        catch (...) {
            std::cerr << "Exception caught !!" << std::endl;
        }

        qint32 buildError = 0;
        shader.glGetShaderiv(shader.vertexID, GL_COMPILE_STATUS, &buildError);
        QVERIFY(buildError == GL_TRUE);
    }
    
}

#endif //TESTS
