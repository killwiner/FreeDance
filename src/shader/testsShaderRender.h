#ifndef TESTSSHADERRENDER_H
#define TESTSSHADERRENDER_H

#ifdef TESTS

#include "shader.h"

namespace shader {

class TestsShaderRender: public Shader {
    Q_OBJECT
public:
    TestsShaderRender(const QString &vertexSource, const QString &fragmentSource,
                      const quint16 &framesPerSecond, const quint16 &interval_time);
    virtual ~TestsShaderRender();
    void loop_paint(const qint32 &max_count);

protected:
    virtual void initializeGL();
    virtual void paintGL();

private:
    GLuint vbo;
    qint32 count;
    static const float vertices[60];
};
}

#endif //TESTS

#endif // TESTSSHADERRENDER_H
