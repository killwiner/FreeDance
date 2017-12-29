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

#ifndef SHADER_H
#define SHADER_H

#include <QtGlobal>
#include "rendering/render.h"
#include <QGLFunctions>
#include <string>
#include <iostream>
#include <QFile>

namespace shader {

#ifdef TESTS
class TestsShader;
#endif // TESTS

class Shader : public rendering::Render {

#ifdef TESTS
    friend TestsShader;
#endif

public:
    // interval_time : interval time between each image
    // framesPerSecond : max of frames per second
    Shader(const QString &vertexSource, const QString &fragmentSource,
           const quint16 &framesPerSecond, const quint16 &interval_time);
    ~Shader();

    // accesseur qui retourne l'identifiant du programme
    quint32 getProgramID() const;

    void load();

protected:
    quint32 programID;

private:
    quint32 vertexID, fragmentID;
    QString vertexSource_, fragmentSource_;

    // type : type de shader
    void buildShader(quint32 &shader, GLenum type, const QString &file);
    QString loadFile(const QString &file_name);
    void controlLink();
    void controlBuild(const quint32 &shader);
};
}
#endif //SHADER_H
