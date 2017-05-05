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
    Shader(const QString &vertexSource, const QString &fragmentSource,
           const quint16 &framesPerSecond, const quint16 &interval_time);
    ~Shader();

    quint32 getProgramID() const;
    void load();

private:
    quint32 vertexID, fragmentID, programID;
    QString vertexSource_, fragmentSource_;
    QString Source;

    // type : type de shader
    void buildShader(quint32 &shader, GLenum type, const QString &file);
    void loadFile(const QString &file_name);
    void controlLink(const quint32 &shader);
    void controlBuild(const quint32 &shader);
};
}
#endif //SHADER_H
