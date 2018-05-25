#include "gameRender.h"

namespace gameRender {

GameRender::GameRender() : Shader(24, 1000),
    count(0), time_(.0f), paint_status(MOTION), textured(false) {

    VStVAO = std::vector<StructVAO>(NBR_VAO);

    VPointMouse = maths::Vector<float>(.0f, .0f, .0f, espace_mouse);

    init_loop();
}

GameRender::~GameRender() {
}

void GameRender::makeVertices(const float &length, const float &z, const float &ratio, const quint16 &mid) {

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

    SPVertices[mid] = QSharedPointer<float>(new float[60], do_delete<float>);

    vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] = z;

    vertices[5] = -1.0f + l * ratio;
    vertices[6] = -1.0f;
    vertices[7] = z;

    vertices[10] = -1.0f + l * ratio;
    vertices[11] = -1.0f + l;
    vertices[12] = z;

    vertices[15] = -1.0f;
    vertices[16] = -1.0f;
    vertices[17] = z;

    vertices[20] = -1.0f;
    vertices[21] = -1.0f + l;
    vertices[22] = z;

    vertices[25] = -1.0f + l * ratio;
    vertices[26] = -1.0f + l;
    vertices[27] = z;

    std::memcpy(SPVertices[mid].data(), vertices, 60 * sizeof(float));

}

void GameRender::paintStatus(const quint8 &status)
{
    paint_status = status;
}

int GameRender::loadTexture(const GLenum &idText, const bool &alpha) {

    textured = true;	
    if(!PVImage_)
        return -1;

        // generate texture names
        //VTexture.push_back(0);
        glGenTextures(1, &Texture[idText]);

        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "(gameRender.cpp) OpenGL generate textures, error : " << err << std::endl;
            return -1;
        }

        // utilisation des textures
        glActiveTexture(GL_TEXTURE0 + idText);

        glBindTexture(GL_TEXTURE_2D, Texture[idText]);

        // specify a two-dimensional texture image
        if(PVImage_) {
            if(!alpha)
                glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_BGRA, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);
        }

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
    glGenBuffers(NBR_VAO, vbo);
}

void GameRender::makeVao(const quint16 &mid) {

    // vérouillage
    glBindBuffer(GL_ARRAY_BUFFER, vbo[mid]);
    vao[mid].create();
    vao[mid].bind();

    // transfert de données
    // GL_STATIC_DRAW : données mises à jour rarrement
    // GL_DYNAMIC_DRAW : données mises à jour fréquemment
    // GL_STREAM_DRAW : données mises à jour à chaque frame
    glBufferData(GL_ARRAY_BUFFER, 60 * sizeof(float[60]), 0, GL_STATIC_DRAW);

    // envoie de données
    glBufferSubData(GL_ARRAY_BUFFER, 0, 60 * sizeof(float[60]), SPVertices[mid].data());

    // Vertex Attrib 0 (Vertices)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Coordonnées de textures Attrib 2 (Texture)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao[mid].release();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GameRender::setMouseXY(const maths::Vector<float> &vector)
{
    VPointMouse = vector;
}

void GameRender::setStructVAO(const maths::Vector<float> &Vtex_resolution, const float &alpha, const float &length,
                              const maths::Vector<float> &Vtranslate, const quint16 mid)
{
    StructVAO st;
    st.alpha = alpha;
    st.length = length;
    st.Vtex_resolution = Vtex_resolution;
    st.Vtranslate = Vtranslate;
    VStVAO.at(mid) = st;

    makeVertices(length, Vtranslate.get_Z(), Vtex_resolution.get_X() * (float)VWinSize.get_Y()/ (Vtex_resolution.get_Y() * (float)VWinSize.get_X()), mid);
    makeVao(mid);
}

void GameRender::setVAOAlpha(const quint8 &id, const float &alpha)
{
    VStVAO.at(id).alpha = alpha;
}

void GameRender::text(const quint8 &id) {
    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, Texture[id]);
}

void GameRender::activateShader(const quint8 &id)
{
    // activation du shader
    useProgramID(id);

    uniform_win_resol = glGetUniformLocation(getProgramID(id), "UNIF_win_resolution");
    uniform_tex_resol = glGetUniformLocation(getProgramID(id), "UNIF_tex_resolution");
    uniform_time = glGetUniformLocation(getProgramID(id), "UNIF_time");
    uniform_alpha_length = glGetUniformLocation(getProgramID(id), "UNIF_alpha_length");
    uniform_translate = glGetUniformLocation(getProgramID(id), "UNIF_translate");

    glUniform2f(uniform_win_resol, (float)VWinSize.get_X(), (float)VWinSize.get_Y());
    glUniform1f(uniform_time, time_);
}

void GameRender::showVAO(const quint8 &id, const quint8 &programID) {

    glUniform1i(glGetUniformLocation(getProgramID(programID), "UNIF_surface"), id);
    glUniform2f(uniform_tex_resol, VStVAO.at(id).Vtex_resolution.get_X(), VStVAO.at(id).Vtex_resolution.get_Y());
    glUniform2f(uniform_alpha_length, VStVAO.at(id).alpha, VStVAO.at(id).length);
    glUniform2f(uniform_translate, VStVAO.at(id).Vtranslate.get_X(), VStVAO.at(id).Vtranslate.get_Y());
    glUniform1i(uniform_idShader, id);

    vao[id].bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao[id].release();
}

void GameRender::ratio(const quint8 &id) {
    // vérouillage
    glBindBuffer(GL_ARRAY_BUFFER, vbo[id]);

    float ratio = VStVAO.at(id).Vtex_resolution.get_X() * (float)VWinSize.get_Y()/ (VStVAO.at(id).Vtex_resolution.get_Y() * (float)VWinSize.get_X());
    float l = 1.0f / VStVAO.at(id).length;

    *(SPVertices[id].data() + 5) = -1.0f + l * ratio;
    *(SPVertices[id].data() + 10) = -1.0f + l * ratio;
    *(SPVertices[id].data() + 25) = -1.0f + l * ratio;

    // envoie de données
    glBufferSubData(GL_ARRAY_BUFFER, 0, 60 * sizeof(float[60]), SPVertices[id].data());

    // dévérouillage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameRender::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);

    activateShader(0);

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

        // dessine les objets au format triangles
        vao[INTROID].bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        vao[INTROID].release();

        break;

    case MENU :

        VStVAO.at(MOUSEID).Vtranslate = maths::Vector<float> ((float)VPointMouse.get_X() - .03f,
                              (float)VPointMouse.get_Y(), .0f, espace_mouse);

        text(0);
        showVAO(INTROID, 0);
/*

        useProgramID(2);

        uniform_win_resol = glGetUniformLocation(getProgramID(2), "UNIF_win_resolution");
        uniform_tex_resol = glGetUniformLocation(getProgramID(2), "UNIF_tex_resolution");
        uniform_time = glGetUniformLocation(getProgramID(2), "UNIF_time");
        uniform_alpha_length = glGetUniformLocation(getProgramID(2), "UNIF_alpha_length");
        uniform_translate = glGetUniformLocation(getProgramID(2), "UNIF_translate");

        glUniform2f(uniform_win_resol, (float)VWinSize.get_X(), (float)VWinSize.get_Y());



        glUniform1i(glGetUniformLocation(getProgramID(2), "UNIF_surface"), optionsPId);
        glUniform2f(uniform_tex_resol, VStVAO.at(optionsPId).Vtex_resolution.get_X(), VStVAO.at(optionsPId).Vtex_resolution.get_Y());
        glUniform2f(uniform_alpha_length, VStVAO.at(optionsPId).alpha, VStVAO.at(optionsPId).length);
        glUniform2f(uniform_translate, VStVAO.at(optionsPId).Vtranslate.get_X(), VStVAO.at(optionsPId).Vtranslate.get_Y());
        glUniform1i(uniform_idShader, optionsPId);

        vao[optionsPId].bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        vao[optionsPId].release();
*/


        activateShader(1);
        ratio(OPTIONSBID);
        text(OPTIONSBID);
        showVAO(OPTIONSBID, 1);

        ratio(MOUSEID);
        text(MOUSEID);
        showVAO(MOUSEID, 1);

        activateShader(2);
        showVAO(OPTIONSPID, 2);

        break;
    }
    // lance le shader
    startShader();
}

void GameRender::init_loop() {

    connect(&t_Timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    // Si on ferme la fenêtre, le thread doit se terminer tout de suite
    connect(this, SIGNAL(close()), &loop, SLOT(quit()));

}

qint8 GameRender::loop_paint() {

    time_ = time_ < PI * 80 ? time_ + PI/8.0f : .0f;

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
