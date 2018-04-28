/*************************************************************************/
/* This file is part of FreeDance.                                       */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "../shader/shader.h"
#include "freeQSPointer.h"
#include "../maths/functions.h"

enum {
    MOTION,
    MENU
};

struct StructVAO {
    maths::Vector<float> Vtex_resolution;
    maths::Vector<float> Vtranslate;
    float alpha, length;
};

namespace gameRender {

class GameRender : public shader::Shader {

    Q_OBJECT

public:
    GameRender (const QString &vertexSource, const QString &fragmentSource,
                      const quint16 &framesPerSecond, const quint16 &interval_time);
    virtual ~GameRender();
    qint8 loop_paint();
    void loop_paint(const quint32 &max_count);
    int loadTexture(const GLenum &idText, const bool &alpha);
    void paintStatus(const quint8 &status);
    void setMouseXY(const maths::Vector<float> &vector);
    void setStructVAO(const quint8 &id, const maths::Vector<float> &Vtex_resolution, const float &alpha, const float &length,
                      const maths::Vector<float> &Vtranslate);
    void setVAOAlpha(const quint8 &id, const float &alpha);

protected:
    // initialise OpenGL
    virtual void initializeGL();
    // redimensionne l'écran
    //virtual void resizeGL(int width, int height);
    // dessine à l'écran
    virtual void paintGL();

private:

    GLint uniform_win_resol;
    GLint uniform_tex_resol;
    GLint uniform_alpha_length;
    GLint uniform_translate;
    GLint uniform_time;
    GLint uniform_idShader;

    StructVAO StVAO[NBR_VAO];

    maths::Vector<float> VPointMouse;
    quint8 paint_status;
    float time_;

    // identifiant des vertex buffer object
    GLuint vbo[3];

    // identifiant des vao
    QOpenGLVertexArrayObject vao[NBR_VAO];

    // coordonnées des vertices et des textures
    // ne fonctionne pas avec std::vector ou QList
    QSharedPointer<float> SPVertices[NBR_VAO];

    // taille de la fenêtre
    //int width_, height_;
    // itérations de la boucle animations
    quint32 count;
    // crée un thread pour effectuer une pause
    QEventLoop loop;
    // avec ou sans texture
    bool textured;

    // initialise le thread event_loop
    void init_loop();

    void makeVertices(const quint8 &id, const float &length, const float &z, const float &ratio);
    void makeVao(const quint8 &id);
    void showVAO(const quint8 &id);
    void ratio(const quint8 &id);

};
}

#endif // GAMERENDER_H
