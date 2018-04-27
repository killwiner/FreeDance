#include "render.h"

namespace rendering {

Render::Render() {}

Render::Render(const quint16 &framesPerSecond, const quint16 &interval_time) :  PVImage_(nullptr), t_Timer(this), closing(false), BMouse(false)
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

    // construction des coordonnées de la position de la souris par défaut
    espace_mouse = MQSPEspace(new maths::Espace(WIN_WIDTH, WIN_HEIGHT, 0, 1000));
    VMouse = maths::Vector<float>(2.0f, 2.0f, 0, espace_mouse);
    VWinSize = maths::Vector<quint16>(WIN_WIDTH, WIN_HEIGHT, 0, espace_mouse);

    setMouseTracking(true);
    setCursor(Qt::BlankCursor);
}

Render::~Render() {

   t_Timer.stop();
   //for(std::vector<GLuint>::iterator it = VTexture.begin(); it < VTexture.end(); ++it)
   //   glDeleteTextures(1, &(*it));
}

void Render::setImages(QSPVImage PVImage) {
    //PVImage_.data() += PVImage.data();
    if(PVImage_)
        PVImage_.data()->insert( PVImage_.data()->end(), PVImage.data()->begin(), PVImage.data()->end() );
    else
        // clone vector from PVImage to PVImage_
        PVImage_ = QSPVImage(new std::vector<cv::Mat>(*PVImage.data()));
}

void Render::setImage(const cv::Mat *Image)
{
    if(!PVImage_.data())
        PVImage_ = QSPVImage(new std::vector<cv::Mat>);
    PVImage_.data()->push_back(*Image);
}

void Render::clearImages() {
    PVImage_.clear();
}

maths::Vector<float> Render::getMouseXY()
{
    return VMouse;
}

bool Render::mouseButton()
{
    if(BMouse) {
        BMouse = false;
        return true;
    }
    return false;
}

maths::Vector<quint16> Render::getWinSize()
{
    return VWinSize;
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
    //glGenTextures(1, &texture);
}

void Render::resizeGL(int width, int height)
{
    // spécifie les dimensions de la fenêtre visible sous opengl
    glViewport(0, 0, width, height);

    VWinSize.set(width, height, 0);

}

void Render::paintGL()
{
}

void Render::mouseMoveEvent(QMouseEvent *event)
{
    VMouse = maths::Vector<float>(2.0f * ((float)event->x() / VWinSize.get_X()), 2.0f - 2.0f * ((float)event->y() / VWinSize.get_Y()) - .09f, .0f, espace_mouse);
}

void Render::mousePressEvent(QMouseEvent *event)
{
    BMouse = true;
}
}
