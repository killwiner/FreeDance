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

        // ok si on ne peut charger le fichier qui n'existe pas
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

        QString Source;

        // charge l'objet avec les programmes vertices et fragments
	    Shader shader(QString("../data/testsShaderSucces.vp"), QString("../data/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on peut charger un fichier qui existe
        try {
            Source = shader.loadFile(QString("../data/testsShaderSucces.vp"));
        }
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("loadFile fail test");
        }

        QString match = QString("gl_Position");
        QVERIFY(Source.contains(match));
    }

    void TestsShader::testBuildFail() {
	    Shader shader(QString("empty"), QString("empty"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on ne peut compiler un programme d'un fichier qui n'existe pas
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
	    Shader shader(QString("../data/testsShaderSucces.vp"), QString("../data/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on peut compiler un programme à partir d'un fichier qui existe
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
	    Shader shader(QString("../data/testsShaderFail.vp"), QString("../data/testsShaderFail.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on a des erreurs lexicale, synthaxique, sémentique
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
	    Shader shader(QString("../data/testsShaderSucces.vp"), QString("../data/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on n'a pas d'erreurs lexicale, synthaxique, sémentique
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
	    Shader shader(QString("../data/testsShaderFail.vp"), QString("../data/testsShaderFail.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on ne peut lier les fichiers binaires invalides
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
	    Shader shader(QString("../data/testsShaderSucces.vp"), QString("../data/testsShaderSucces.fp"), 24, 1000);

        // pour lancer initializeOpenGLFunctions()
        shader.setGeometry(200, 200, 400, 400);
        shader.show();
        QTest::qSleep(2000);

        // ok si on peut lier les fichiers binaires valides
        try {
            // compilation et control du programme vertex
            shader.buildShader(shader.vertexID, GL_VERTEX_SHADER, shader.vertexSource_);
            shader.controlBuild(shader.vertexID);

            // compilation et control du programme fragment
            shader.buildShader(shader.fragmentID, GL_FRAGMENT_SHADER, shader.fragmentSource_);
            shader.controlBuild(shader.fragmentID);

            // création du programme
            shader.programID = shader.glCreateProgram();

            // incorporation des deux binaires au programme
            shader.glAttachShader(shader.programID, shader.vertexID);
            shader.glAttachShader(shader.programID, shader.fragmentID);

            // linkage final
            shader.glLinkProgram(shader.programID);

            // control du linkage
            shader.controlLink();
        }
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("controlLink fail test");
        }
    }

    void TestsShader::testAffichage() {

        // On supprime la couleur rouge et la couleur bleue dans le programme fragment
        try {
        TestsShaderRender shaderRender(QString("../data/testsShaderSucces.vp"), QString("../data/testsShaderSucces.fp"), 24, 1000);

        shaderRender.setGeometry(200, 200, 400, 400);
        shaderRender.show();
        rendering::LoadImgs image;
        QVERIFY(image.load_image("../data/images/image_test_4.png") == true);
        shaderRender.setImages(image.getImages());
            shaderRender.load();
        shaderRender.loop_paint(40);
        }
        catch (const char* strException) {
            std::cerr << "Exception caught !!" << std::endl;
            std::cerr << strException << std::endl;
            QFAIL("testAffichage fail test");
        }

    }

    void TestsShader::testTutorials()
    {

        for(quint8 i = 0; i < 13; ++i) {

            try {
                TestsShaderRender shaderRender(QString("../data/tutorial_shader/tutorial_")+QString::number(i+1)+QString(".vp"),
                                               QString("../data/tutorial_shader/tutorial_")+QString::number(i+1)+QString(".fp"), 24, 1000);

                shaderRender.setGeometry(200, 200, 400, 400);
                shaderRender.show();
                shaderRender.load();
                shaderRender.loop_paint(40);
            }
            catch (const char* strException) {
                std::cerr << "Exception caught !!" << std::endl;
                std::cerr << strException << std::endl;
                std::cerr << i + 1 << std::endl;
                QFAIL("tutorial fail test");
            }
        }

    }
}

#endif //TESTS
