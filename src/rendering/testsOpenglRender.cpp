#include "testsOpenglRender.h"

#ifdef TESTS

namespace rendering {

TestsOpenglR::TestsOpenglR(const quint16 &framesPerSecond, const quint16 &interval_time) : Render(framesPerSecond, interval_time), color(.0f), color_up_down(true) {
    connect(t_Timer, SIGNAL(timeout()), this, SLOT(next_step()));
}

TestsOpenglR::~TestsOpenglR() {
}

void TestsOpenglR::loop_paint(const quint8 &test_funct, const qint32 &max_count) {

    test_funct_ = test_funct;

    QEventLoop loop;
    connect(t_Timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    connect(this, SIGNAL(close()), &loop, SLOT(quit()));
    for(count = 0; count < max_count; ++count) {

        if(toClose())
            break;

        loop.exec();
    }
}

void TestsOpenglR::next_step() {

    // envoie un signal de test
    emit test_timeout();

    // fait tourner les couleurs
    if(color < .0f)
        color_up_down = true;

    if(color > 1.0f)
        color_up_down = false;

    if(color_up_down)
        color += .02f;
    else
        color -= .02f;
}

void TestsOpenglR::paintGL()
{
    switch(test_funct_) {
    case TEST_TRIANGLE:
        drawTriangle();
        break;
    case TEST_IMAGE:
        drawImage();
        break;
    case TEST_VIDEO:
        drawVideo();
    default:
        break;
    }
}

void TestsOpenglR::drawTriangle() {

    // nettoie les buffers
    // GL_COLOR_BUFFER_BIT : Indique les buffers courrants actifs pour une écriture des couleurs
    // GL_DEPTH_BUFFER_BIT : Nettoie les Z-buffers (pour éviter la supperposition de couleurs arrière sur des couleurs avant)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // charge la matrice Identité
    glLoadIdentity();

    glTranslatef (0.0, 0.0, -5.0);

    // dessine le triangle
    glBegin (GL_TRIANGLES);
    glColor3f (color, 1.0f - color, 0.0f);
    glVertex3f (-1.0f, -1.0f, 0.0f);

    glColor3f (0.0f, color, 1.0f - color);
    glVertex3f (1.0f, -1.0f, 0.0f);

    glColor3f (1.0f - color, 0.0f, color);
    glVertex3f (0.0f, 1.0f, 0.0f);
    glEnd ();

}

void TestsOpenglR::drawImage() {

    // signal pour lever le vérou de la kinect
    emit nextSignal();

    // set textures parameters
    // GL_NEAREST : Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
    // GL_TEXTURE_MAG_FILTER : The texture magnification function is used whenever the level-of-detail function used when sampling from the
    // texture determines that the texture should be magified.
    // GL_TEXTURE_MIN_FILTER : The texture minifying function is used whenever the level-of-detail function used when sampling from the texture
    // determines that the texture should be minified.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // specify a two-dimensional texture image

    glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->back().data);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
    glEnable(GL_TEXTURE_2D);

    //glBindTexture(GL_TEXTURE_2D, VTexture.back());
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 1); glVertex3f(-1.0f,-1.0f,0);
    glTexCoord2f(1, 1); glVertex3f(1.0f,-1.0f,0);
    glTexCoord2f(1, 0); glVertex3f(1.0f,1.0f,0);
    glTexCoord2f(0, 0); glVertex3f(-1.0f,1.0f,0);
    glEnd();
}

void TestsOpenglR::drawVideo() {

    // set textures parameters
    // GL_NEAREST : Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
    // GL_TEXTURE_MAG_FILTER : The texture magnification function is used whenever the level-of-detail function used when sampling from the
    // texture determines that the texture should be magified.
    // GL_TEXTURE_MIN_FILTER : The texture minifying function is used whenever the level-of-detail function used when sampling from the texture
    // determines that the texture should be minified.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // specify a two-dimensional texture image

    glTexImage2D(GL_TEXTURE_2D, 0, 3, PVImage_.data()->back().size().width, PVImage_.data()->back().size().height, 0, GL_RGB, GL_UNSIGNED_BYTE, PVImage_.data()->at(count).data);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
    glEnable(GL_TEXTURE_2D);

    //glBindTexture(GL_TEXTURE_2D, VTexture.back());
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 1); glVertex3f(-1.0f,-1.0f,0);
    glTexCoord2f(1, 1); glVertex3f(1.0f,-1.0f,0);
    glTexCoord2f(1, 0); glVertex3f(1.0f,1.0f,0);
    glTexCoord2f(0, 0); glVertex3f(-1.0f,1.0f,0);
    glEnd();
}
}

#endif //TESTS

