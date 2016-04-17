#include "run.h"

using namespace std;

Run::Run()
{
    try {
        kinect = new Kinect();
        SP_skeleton = QSharedPointer<Skeleton>(new Skeleton());
        SP_saveload = QSharedPointer<IO_frames>(new IO_frames());
        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, kinect, SP_saveload, SP_skeleton, STATUS_NONE));
        SP_renderwindow->setFixedSize(WIDTH, HEIGHT);
    }
    catch ( const exception &e )
    {
        cerr << "(mainwindow) Exception caught !!" << endl;
        cerr << e.what() << endl;
    }
}

Run::~Run() {
    try {
        kinect->stop();
        delete kinect;
        SP_renderwindow.clear();
        SP_saveload.clear();
        SP_skeleton.clear();

    }
    catch ( const exception &e )
    {
        cerr << "Exception caught !!" << endl;
        cerr << e.what() << endl;
    }
}

QWidget *Run::getwidget() {
    return SP_renderwindow.data();
}

// load the motion
void Run::load(QString fileName) {

        // we load the motion
        SP_saveload->load(fileName);
        // the opengl window exists already. just change the status
        // la capture sur la fenêtre opengl existe déjà, il suffit de changer le status
        SP_renderwindow->change_status(STATUS_MOTION);
        SP_renderwindow->change_pause(false);

}
