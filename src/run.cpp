#include "run.h"

using namespace std;

Run::Run()
{
    try {
        kinect = new Kinect();
        SP_skeleton = QSharedPointer<Skeleton>(new Skeleton());
        SP_saveload = QSharedPointer<IO_frames>(new IO_frames());
        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, mat_preview_after, kinect, SP_saveload, SP_skeleton, STATUS_NONE));
        SP_renderwindow->setFixedSize(WIDTH * 2 + 4, HEIGHT);

        mat_preview_after = cv::Mat(HEIGHT, WIDTH, CV_8UC3);
        // Here only black
        mat_preview_after.setTo(cv::Scalar::all(0));
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
    SP_renderwindow->change_play_pause(true);

}

// load the motion
bool Run::save(QString fileName) {

    if (SP_renderwindow->get_status() == STATUS_NONE)
        return true;
    // we save the motion
    SP_saveload->save(SP_saveload->vect_imgs, fileName);
    return false;

}

bool Run::change_play_pause() {
        SP_renderwindow->change_play_pause(!SP_renderwindow->status_play_pause());
        return SP_renderwindow->status_play_pause();
}

void Run::preview(int &filter_green, int &filter_blue) {
    // Here only black
    mat_preview_after.setTo(cv::Scalar::all(0));
    SearchHuman sh(SP_saveload->vect_imgs.at(SP_renderwindow->get_position()), mat_preview_after, filter_green, filter_blue);
    sh.clear_partition();
    sh.first_search();
    // change all colors to show only areas after filters
    // on change toutes les couleurs pour rendre évident les partitions après filtrage
    sh.unification();
    SP_renderwindow->change_status(STATUS_MOTION);
    SP_renderwindow->updateGL();
}

// to connect the kinect
// connecte la kinect
void Run::connect_kinect()
{
    try {
        kinect->connect();
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }
}
