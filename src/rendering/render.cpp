#include "render.h"

namespace rendering {

Render::Render(const quint16 &framesPerSecond, const quint16 &interval_time) : closing(false)
{
    setAttribute(Qt::WA_DeleteOnClose);

    quint16 timerInterval = interval_time / framesPerSecond;
    t_Timer = new QTimer(this);
    connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    t_Timer->start( timerInterval );

    // Permet d'automatiser le swap buffer d'opengl
    setAutoBufferSwap(true);

}

Render::~Render() {

   t_Timer->stop();
   delete t_Timer;
   t_Timer = nullptr;
   glDeleteTextures(1, &texture);

}

void Render::setImages(const QSPVImage &PVImage) {
    PVImage_ = PVImage;
}

void Render::setImage(const cv::Mat *Image)
{
    if(!PVImage_.data())
        PVImage_ = QSPVImage(new std::vector<cv::Mat>);
    PVImage_.data()->push_back(*Image);
}

bool Render::toClose() {
    return closing;
}

void Render::closeEvent(QCloseEvent *event)
{
    closing = true;
    emit close();
    event->ignore();
    hide();
}

void Render::timeOutSlot()
{
    updateGL();
}

void Render::initializeGL()
{

    // Les valeurs acceptées sont GL_MODELVIEW, GL_PROJECTION, et GL_TEXTURE
    glMatrixMode(GL_PROJECTION);
    // charge la matrice Identité
    glLoadIdentity();
    // Multiplie la matrice courante par la matrice perspective
    // left, right, bottom, top distance near, distance far
    glFrustum(-1, 1, -1, 1, 5, 7);

    // Retour au mode par défaut
    glMatrixMode(GL_MODELVIEW);

    // generate texture names
    glGenTextures(1, &texture);
}

void Render::resizeGL(int width, int height)
{

    // spécifie les dimensions de la fenêtre visible sous opengl
    glViewport(0, 0, width, height);

}

void Render::paintGL()
{
}

}
