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

namespace gameRender {

class GameRender : public shader::Shader {

    Q_OBJECT

public:
    GameRender (const QString &vertexSource, const QString &fragmentSource,
                      const quint16 &framesPerSecond, const quint16 &interval_time);
    virtual ~GameRender();
    qint8 loop_paint();
    void loop_paint(const quint32 &max_count);
    int loadTextures();
    QSharedPointer<float> makeVertices(const maths::Vector<float> &vloc, const float &length);

protected:
    // initialise OpenGL
    virtual void initializeGL();
    // redimensionne l'écran
    virtual void resizeGL(int width, int height);
    // dessine à l'écran
    virtual void paintGL();

private:
    // identifiant des vertex buffer object
    GLuint vbo[2];
    // identifiant des vao
    QOpenGLVertexArrayObject vao[2];

    // coordonnées des vertices et des textures
    // ne fonctionne pas avec std::vector ou QList
    QSharedPointer<float> vertices[2];

    // taille de la fenêtre
    int width_, height_;
    // itérations de la boucle animations
    quint32 count;
    // crée un thread pour effectuer une pause
    QEventLoop loop;

    // initialise le thread event_loop
    void init_loop();
};
}

#endif // GAMERENDER_H
