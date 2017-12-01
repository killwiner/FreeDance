#include "GameRender.h"

namespace gameRender {

const float GameRender::vertices_flat[60] = {
//    X      Y     Z     U     V
  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
   1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
   1.0f,  1.0f, 0.0f, 1.0f, .0f,
  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
   1.0f,  1.0f, 0.0f, 1.0f, 0.0f
};

GameRender::GameRender(const QString &vertexSource, const QString &fragmentSource,
                       const quint16 &framesPerSecond, const quint16 &interval_time) :
    Shader(vertexSource, fragmentSource, framesPerSecond, interval_time) {
}

GameRender::~GameRender() {
    // désactivation du shader
    glUseProgram(0);
}

void GameRender::initializeGL()
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
    // GL_STATIC_DRAW : données mises à jour rarrement
    // GL_DYNAMIC_DRAW : données mises à jour fréquemment
    // GL_STREAM_DRAW : données mises à jour à chaque frame
    glBufferData(GL_ARRAY_BUFFER, 60 * sizeof(vertices), 0, GL_STATIC_DRAW);

    // envoie de données
    glBufferSubData(GL_ARRAY_BUFFER, 0, 60 * sizeof(vertices), vertices);

    // Vertex Attrib 0 (Vertices)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Coordonnées de textures Attrib 2 (Texture)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameRender::resizeGL(int width, int height)
{
    // spécifie les dimensions de la fenêtre visible sous opengl
    glViewport(0, 0, width, height);

    width_ = width;
    height_ = height;

}

void GameRender::paintGL()
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
    if(PVImage_)
        glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);

    GLint uniformId = glGetUniformLocation(programID, "resolution");

    // activation du shader
    glUseProgram(getProgramID());

    glUniform2i(uniformId, width_, height_);

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

