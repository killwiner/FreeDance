#include "gameRender.h"

namespace gameRender {

GameRender::GameRender(const QString &vertexSource, const QString &fragmentSource,
                       const quint16 &framesPerSecond, const quint16 &interval_time) :
    Shader(vertexSource, fragmentSource, framesPerSecond, interval_time), count(0), id_vao(0), paint_status(MOTION) {

    VPointMouse = maths::Vector<quint16>(.0f, .0f, .0f, espace_mouse);

    init_loop();
}

GameRender::~GameRender() {
    // désactivation du shader
    glUseProgram(0);
}

void GameRender::makeVertices(const maths::Vector<float> &vloc, const float &length, const float &ratio) {

    float l = 1.0f / length;

    float vertices[60] = {
  //    X    Y    Z    U     V
        .0f, .0f, .0f, 0.0f, 1.0f,
        .0f, .0f, .0f, 1.0f, 1.0f,
        .0f, .0f, .0f, 1.0f, 0.0f,
        .0f, .0f, .0f, 0.0f, 1.0f,
        .0f, .0f, .0f, 0.0f, 0.0f,
        .0f, .0f, .0f, 1.0f, 0.0f
    };

    SPVertices[id_vao] = QSharedPointer<float>(new float[60], do_delete<float>);

    vertices[0] = vloc.get_X();
    vertices[1] = vloc.get_Y();
    vertices[2] = vloc.get_Z();

    vertices[5] = vloc.get_X() + l * ratio;
    vertices[6] = vloc.get_Y();
    vertices[7] = vloc.get_Z();

    vertices[10] = vloc.get_X() + l * ratio;
    vertices[11] = vloc.get_Y() + l;
    vertices[12] = vloc.get_Z();

    vertices[15] = vloc.get_X();
    vertices[16] = vloc.get_Y();
    vertices[17] = vloc.get_Z();

    vertices[20] = vloc.get_X();
    vertices[21] = vloc.get_Y() + l;
    vertices[22] = vloc.get_Z();

    vertices[25] = vloc.get_X() + l * ratio;
    vertices[26] = vloc.get_Y() + l;
    vertices[27] = vloc.get_Z();

    std::memcpy(SPVertices[id_vao].data(), vertices, 60 * sizeof(float));

    ++id_vao;
}

void GameRender::paintStatus(const quint8 &status)
{
    paint_status = status;
}

int GameRender::loadTexture(const GLenum &idText) {
    if(!PVImage_)
        return -1;

        // generate texture names
        VTexture.push_back(0);
        glGenTextures(1, &VTexture.back());

        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "(gameRender.cpp) OpenGL generate textures, error : " << err << std::endl;
            return -1;
        }

        // utilisation des textures
            glActiveTexture(idText);

        glBindTexture(GL_TEXTURE_2D, VTexture.back());

        // specify a two-dimensional texture image
        if(PVImage_)
            //glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_BGRA, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);

        // set textures parameters
        // GL_NEAREST : Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
        // GL_TEXTURE_MAG_FILTER : The texture magnification function is used whenever the level-of-detail function used when sampling from the
        // texture determines that the texture should be magified.
        // GL_TEXTURE_MIN_FILTER : The texture minifying function is used whenever the level-of-detail function used when sampling from the texture
        // determines that the texture should be minified.
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Set texture clamping method
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    return 0;
}

void GameRender::initializeGL()
{
    // pour avoir accès aux fonctions d'OpenGL
    initializeGLFunctions();

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Les valeurs acceptées sont GL_MODELVIEW, GL_PROJECTION, et GL_TEXTURE
    glMatrixMode(GL_PROJECTION);
    // charge la matrice Identité
    glLoadIdentity();
    // Multiplie la matrice courante par la matrice perspective
    // left, right, bottom, top distance near, distance far
    glFrustum(-1, 1, -1, 1, 5, 7);

    // Retour au mode par défaut
    glMatrixMode(GL_MODELVIEW);

    // vertex buffer object, génération
    glGenBuffers(3, vbo);
}

void GameRender::makeVao(const quint8 &id) {

    // vérouillage
    glBindBuffer(GL_ARRAY_BUFFER, vbo[id]);

    vao[id].create();
    vao[id].bind();

    // transfert de données
    // GL_STATIC_DRAW : données mises à jour rarrement
    // GL_DYNAMIC_DRAW : données mises à jour fréquemment
    // GL_STREAM_DRAW : données mises à jour à chaque frame
    glBufferData(GL_ARRAY_BUFFER, 60 * sizeof(float[60]), 0, GL_STATIC_DRAW);

    // envoie de données
    glBufferSubData(GL_ARRAY_BUFFER, 0, 60 * sizeof(float[60]), SPVertices[id].data());

    // Vertex Attrib 0 (Vertices)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Coordonnées de textures Attrib 2 (Texture)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao[id].release();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameRender::setMouseXY(const maths::Vector<quint16> &vector)
{
    VPointMouse = vector;
}

void GameRender::setStructVAO(const GLenum &id, const maths::Vector<float> &Vtex_resolution, const float &alpha, const float &length, const maths::Vector<float> &Vtranslate)
{
    StVAO[id].alpha = alpha;
    StVAO[id].lrngth = length;
    StVAO[id].Vtex_resolution = Vtex_resolution;
    StVAO[id].Vtranslate = Vtranslate;
}

void GameRender::resizeGL(int width, int height)
{
    // spécifie les dimensions de la fenêtre visible sous opengl
    glViewport(0, 0, width, height);

    width_ = width;
    height_ = height;
}

void GameRender::showVAO(const GLenum &id) {

    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, VTexture.at(id));
    glUniform1i(glGetUniformLocation(programID, "UNIF_surface"), id);
    glUniform2f(uniformId1, StVAO[id].Vtex_resolution.get_X(), StVAO[id].Vtex_resolution.get_Y());
    glUniform2f(uniformId2, StVAO[id].alpha, StVAO[id].length);
    glUniform2f(uniformId3, StVAO[id].Vtranslate.get_X(), StVAO[id].Vtranslate.get_Y());

    vao[id].bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao[id].release();
}

void GameRender::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);

    GLint uniformId0 = glGetUniformLocation(programID, "UNIF_win_resolution");
    GLint uniformId1 = glGetUniformLocation(programID, "UNIF_tex_resolution");
    GLint uniformId2 = glGetUniformLocation(programID, "UNIF_alpha_length");
    GLint uniformId3 = glGetUniformLocation(programID, "UNIF_translate");

    // activation du shader
    glUseProgram(getProgramID());

    glUniform2f(uniformId0, (float)width_, (float)height_);

    glEnable(GL_TEXTURE_2D);

    switch(paint_status) {

    case MOTION :

        glActiveTexture(GL_TEXTURE0);

        if(PVImage_)
            glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->at(count).size().width, PVImage_.data()->at(count).size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->at(count).data);

        // set textures parameters
        // GL_NEAREST : Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
        // GL_TEXTURE_MAG_FILTER : The texture magnification function is used whenever the level-of-detail function used when sampling from the
        // texture determines that the texture should be magified.
        // GL_TEXTURE_MIN_FILTER : The texture minifying function is used whenever the level-of-detail function used when sampling from the texture
        // determines that the texture should be minified.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glUniform1i(glGetUniformLocation(programID, "UNIF_surface"), 0);
        glUniform2f(uniformId1, 1280, 960);
        glUniform2f(uniformId2, 1.0f, .5f);
        glUniform2f(uniformId3, .0f, .0f);

        // dessine les objets au format triangles
        vao[0].bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        vao[0].release();

        break;

    case MENU :

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, VTexture.at(0));
    glUniform1i(glGetUniformLocation(programID, "UNIF_surface"), 0);
    glUniform2f(uniformId1, 1280, 960);
    glUniform2f(uniformId2, 1.0f, .5f);
    glUniform2f(uniformId3, .0f, .0f);

    vao[0].bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao[0].release();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, VTexture.at(1));
    glUniform1i(glGetUniformLocation(programID, "UNIF_surface"), 1);
    glUniform2f(uniformId1, 128, 128);
    glUniform2f(uniformId2, .2f, 8.0f);
    glUniform2f(uniformId3, 1.8f, 1.8f);

    vao[1].bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao[1].release();

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, VTexture.at(2));
    glUniform1i(glGetUniformLocation(programID, "UNIF_surface"), 2);
    glUniform2f(uniformId1, 128, 128);
    glUniform2f(uniformId2, 1.0f, 8.0f);
    glUniform2f(uniformId3, ((float)VPointMouse.get_X() - 20.0f) * 2.0f / (float)WIN_WIDTH, 2.0f - (((float)VPointMouse.get_Y() + 56.0f) * 2.0f / (float)WIN_HEIGHT));

    vao[2].bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao[2].release();

        // lance le shader
        break;
    }

    glUseProgram(0);
}

void GameRender::init_loop() {

    connect(&t_Timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    // Si on ferme la fenêtre, le thread doit se terminer tout de suite
    connect(this, SIGNAL(close()), &loop, SLOT(quit()));

}

qint8 GameRender::loop_paint() {

    // On arrête tout si on ferme la fenêtre
    if(toClose())
        return 1;

    // On lance le thread pour effectuer une pause entre chaque image
    loop.exec();

    return 0;

}

void GameRender::loop_paint(const quint32 &max_count) {

    for(count = 0; count < max_count; ++count) {

        // On arrête tout si on ferme la fenêtre
        if(toClose())
            break;

        // On lance le thread pour effectuer une pause entre chaque image
        loop.exec();
    }
}

}
