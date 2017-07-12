#include "testsShaderRender.h"

#ifdef TESTS

namespace shader {

const float TestsShaderRender::vertices[60] = {
//    X      Y     Z     U     V
  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
   1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
   1.0f,  1.0f, 0.0f, 1.0f, .0f,
  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
   1.0f,  1.0f, 0.0f, 1.0f, 0.0f
};

TestsShaderRender::TestsShaderRender(const QString &vertexSource, const QString &fragmentSource,
                                     const quint16 &framesPerSecond, const quint16 &interval_time) :
    Shader(vertexSource, fragmentSource, framesPerSecond, interval_time) {
}

TestsShaderRender::~TestsShaderRender() {
    // désactivation du shader
    glUseProgram(0);
}

void TestsShaderRender::loop_paint(const qint32 &max_count) {

    // crée un thread pour effectuer une pause
    QEventLoop loop;
    connect(t_Timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    // Si on ferme la fenêtre, le thread doit se terminer tout de suite
    connect(this, SIGNAL(close()), &loop, SLOT(quit()));
    for(count = 0; count < max_count; ++count) {

        // On arrête tout si on ferme la fenêtre
        if(toClose())
            break;

        // On lance le thread pour effectuer une pause entre chaque image
        loop.exec();
    }
}

void TestsShaderRender::initializeGL()
{
    // pour avoir accès aux fonctions d'OpenGL
    initializeGLFunctions();

    // Les valeurs acceptées sont GL_MODELVIEW, GL_PROJECTION, et GL_TEXTURE
    glMatrixMode(GL_PROJECTION);
    // charge la matrice Identité
    glLoadIdentity();
    // Multiplie la matrice courante par la matrice perspective
    // left, right, bottom, top distance near, distance far
    glFrustum(-1, 1, -1, 1, 5, 7);

    // Retour au mode par défaut
    glMatrixMode(GL_MODELVIEW);

    // generate texture names
    glGenTextures(1, &texture);

    // vertex buffer object, génération
    glGenBuffers(1, &vbo);

    // vérouillage
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // transfert de données
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // dévérouillage
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Vertex Attrib 0 (Vertices)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Coordonnées de textures Attrib 2 (Texture)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);

    // Déverrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TestsShaderRender::paintGL()
{
    // set textures parameters
    // GL_NEAREST : Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
    // GL_TEXTURE_MAG_FILTER : The texture magnification function is used whenever the level-of-detail function used when sampling from the
    // texture determines that the texture should be magified.
    // GL_TEXTURE_MIN_FILTER : The texture minifying function is used whenever the level-of-detail function used when sampling from the texture
    // determines that the texture should be minified.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // specify a two-dimensional texture image
    glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);

    // activation du shader
    glUseProgram(getProgramID());

    glEnable(GL_TEXTURE_2D);

    // utilisation des textures
    glBindTexture(GL_TEXTURE_2D, texture);

    // dessine l'objet au format triangles
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // lance le shader
    glUseProgram(0);
}

}

#endif //TESTS

