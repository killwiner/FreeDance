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

quint32 Render::CreateShader(const GLenum &type) {
    return glCreateShader(type);
}

void Render::ShaderSource(const QString &source, const quint32 &shader)
{
    const char *str = source.toStdString().c_str();
    glShaderSource(shader, 1, &str, 0);
}

void Render::CompileShader(const quint32 &shader)
{
    glCompileShader(shader);
}

void Render::GetShaderiv(const quint32 &shader, const GLenum &pname, int *params)
{
    glGetShaderiv(shader, pname, params);
}

void Render::GetShaderInfoLog(const quint32 &shader, int &lengthMessage, char *message)
{
    glGetShaderInfoLog(shader, lengthMessage, &lengthMessage, message);
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
