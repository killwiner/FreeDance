#ifndef RTESTSOPENGL_H
#define RTESTSOPENGL_H

#ifdef TESTS

#include "render.h"

enum TESTS_OPENGL {
    TEST_TRIANGLE,
    TEST_IMAGE,
    TEST_VIDEO
};

namespace rendering {

class TestsOpenglR: public Render {
    Q_OBJECT
public:
    TestsOpenglR(const quint16 &framesPerSecond, const quint16 &interval_time);
    virtual ~TestsOpenglR();
    void loop_paint(const quint8 &test_funct, const qint32 &max_count);

public slots:
    void next_step();

signals:
    void test_timeout();
    void nextSignal();

protected:
    virtual void paintGL();

private:
    void drawTriangle();
    void drawImage();
    void drawVideo();

    float color;
    bool color_up_down;
    bool closed;
    quint8 test_funct_;
    qint32 count;
};
}

#endif //TESTS

#endif // RTESTSOPENGL_H
