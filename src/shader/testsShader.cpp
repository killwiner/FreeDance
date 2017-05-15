#include "testsShader.h"

#ifdef TESTS

namespace shader {

    TestsShader::TestsShader() {
    }
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
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
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
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("loadFile fail test");
        }

        QString match = QString("gl_Position");
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
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
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
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("build fail test");
        }

        qint32 buildError = 0;
        shader.glGetShaderiv(shader.vertexID, GL_COMPILE_STATUS, &buildError);
        QVERIFY(buildError == GL_TRUE);
    }

    void TestsShader::testControlBuildFail() {
	    Shader shader(QString("shader/testsShaderFail.vp"), QString("shader/testsShaderFail.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        try {
            shader.buildShader(shader.vertexID, GL_VERTEX_SHADER, shader.vertexSource_);
            shader.controlBuild(shader.vertexID);
            QFAIL("controlBuild fail test");
        }
        catch (const char *strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
        }
    }

    void TestsShader::testControlBuildSucces() {
	    Shader shader(QString("shader/testsShaderSucces.vp"), QString("shader/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        try {
            shader.buildShader(shader.vertexID, GL_VERTEX_SHADER, shader.vertexSource_);
            shader.controlBuild(shader.vertexID);
        }
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("controlBuild fail test");
        }
    } 

    void TestsShader::testControlLinkFail() {
	    Shader shader(QString("shader/testsShaderFail.vp"), QString("shader/testsShaderFail.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        try {
            shader.programID = 0;
            shader.controlLink();
            QFAIL("controlBuild fail test");
        }
        catch (const char *strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
        }
    }

    void TestsShader::testControlLinkSucces() {
	    Shader shader(QString("shader/testsShaderSucces.vp"), QString("shader/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        try {
            shader.buildShader(shader.vertexID, GL_VERTEX_SHADER, shader.vertexSource_);
            shader.controlBuild(shader.vertexID);
            shader.buildShader(shader.fragmentID, GL_FRAGMENT_SHADER, shader.fragmentSource_);
            shader.controlBuild(shader.fragmentID);
            shader.programID = shader.glCreateProgram();
            shader.glAttachShader(shader.programID, shader.vertexID);
            shader.glAttachShader(shader.programID, shader.fragmentID);
            shader.glLinkProgram(shader.programID);
            shader.controlLink();
        }
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("controlLink fail test");
        }
    }

    void TestsShader::testAffichage() {
        TestsShaderRender shaderRender(QString("shader/testsShaderSucces.vp"), QString("shader/testsShaderSucces.fp"), 24, 1000);

        shaderRender.setGeometry(200, 200, 400, 400);
        shaderRender.show();
        rendering::LoadImgs image;
        QVERIFY(image.load_image("rendering/image_test.png") == true);
        shaderRender.setImages(image.getImages());
        try {
            shaderRender.load();
        }
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("testAffichage fail test");
        }

        shaderRender.loop_paint(200);
    }
}

#endif //TESTS
