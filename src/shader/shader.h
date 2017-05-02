#ifndef SHADER_H
#define SHADER_H

#include <QtGlobal>
#include "rendering/render.h"
#include <QGLFunctions>
#include <string>
#include <iostream>
#include <QFile>

namespace shader {

class Shader {

public:
    Shader(const QString &vertexSource, const QString &fragmentSource, rendering::Render *render);
    ~Shader();

    quint32 getProgramID() const;
    void load();

private:
    rendering::Render *render_;
    quint32 vertexID, fragmentID, programID;
    QString vertexSource_, fragmentSource_, Source;

    // type : type de shader
    void buildShader(quint32 &shader, GLenum type, const QString &file);
    void LoadFile(const QString &file_name);
    void control(const quint32 &shader);
};
}
#endif //SHADER_H
