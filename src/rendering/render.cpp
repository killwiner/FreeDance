#include "render.h"

namespace rendering {

Render::Render() {}

Render::Render(const quint16 &framesPerSecond, const quint16 &interval_time) :  PVImage_(nullptr), t_Timer(this), closing(false)
{
    //Qt takes care of deleting the window from memory as soon as it is closed.
    //If the parent will be destructed, then the children will be too.
    setAttribute(Qt::WA_DeleteOnClose);

    //Create the timer and start it
    quint16 timerInterval = interval_time / framesPerSecond;
    connect(&t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    t_Timer.start( timerInterval );

    // Permet d'automatiser le swap buffer d'opengl
    setAutoBufferSwap(true);
}

Render::~Render() {

   t_Timer.stop();
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

bool Render::toClose() const {
    return closing;
}

void Render::closeEvent(QCloseEvent *event)
{
    closing = true;
    emit close();
    event->ignore();
    // hide the window before to close
    hide();
}

void Render::timeOutSlot()
{
    // every top clock we update the OpenGl image
    updateGL();
}

void Render::initializeGL()
{

    // pour avoir accès aux fonctions d'OpenGL
    initializeGLFunctions();

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
