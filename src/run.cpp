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
        kinect->detach();
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
void Run::load(QString const &fileName) {

    // we load the motion
    SP_saveload->load(fileName);
    // the opengl window exists already. just change the status
    // la capture sur la fenêtre opengl existe déjà, il suffit de changer le status
    SP_renderwindow->change_status(STATUS_MOTION);
    SP_renderwindow->change_play_pause(true);

}

void Run::play() {
    try {
        if(!kinect->is_connected())
            throw;
        // the opengl window exists already. just change the status
        // la capture sur la fenêtre opengl existe déjà, il suffit de changer le status
        SP_renderwindow->change_status(STATUS_MOTION);
        SP_renderwindow->change_play_pause(true);
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
    }
}

void Run::stop() {
    SP_renderwindow->change_status(STATUS_KINECT);
    SP_renderwindow->change_play_pause(false);
    SP_renderwindow->updateGL();
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
    SearchHuman *sh;

    if(SP_renderwindow->get_status() == STATUS_KINECT) {

        // create the image with the data
        // crée l'image avec les données
        cv::Mat buffer_img(HEIGHT, WIDTH, CV_8UC3, (char*)kinect->get_depth_front());
        sh = new SearchHuman(buffer_img, mat_preview_after, filter_green, filter_blue);
    }
    else
        sh = new SearchHuman(SP_saveload->vect_imgs.at(SP_renderwindow->get_position()), mat_preview_after, filter_green, filter_blue);

    sh->clear_partition();
    sh->first_search();
    // change all colors to show only areas after filters
    // on change toutes les couleurs pour rendre évident les partitions après filtrage
    sh->unification();
//    SP_renderwindow->change_status(STATUS_MOTION);
    SP_renderwindow->updateGL();
    delete sh;
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

bool Run::run_kinect() {

    if(!kinect->is_connected())
        return true;

    try {
        kinect->start();

        SP_renderwindow->change_status(STATUS_KINECT);
        SP_renderwindow->change_play_pause(true);
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
    }

    return false;
}

void Run::recordCapture() {
    try {
        if(!kinect->is_connected())
            throw;
        if(!kinect->is_running() && !kinect->is_recording())
                    kinect->start();

        SP_renderwindow->change_status(STATUS_RECORD);
        SP_renderwindow->change_play_pause(true);
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
    }

}

// show in a window the free memory
void Run::memory_info(QString &QSmem_total, QString &QSmem_free, QString &QSratio) {

    try {

        FILE *in = popen("cat /proc/meminfo", "r");
        if(!in)
            throw "(render_window) error, can't open /proc/meminfo";

        char buffer[128], mem_total_s[128], mem_free_s[128];
        int mem_total, mem_free;

        fscanf(in, "%s", buffer);
        fscanf(in, "%s", mem_total_s);
        fscanf(in, "%s", buffer);
        fscanf(in, "%s", buffer);
        fscanf(in, "%s", mem_free_s);

        pclose(in);

        istringstream smt(mem_total_s);
        istringstream smf(mem_free_s);

        smt >> mem_total;
        smf >> mem_free;

        stringstream ratio_s;
        ratio_s << int(mem_free * 100 / mem_total);

        QSmem_total.append(mem_total_s);
        QSmem_free.append(mem_free_s);
        QSratio = QString::fromStdString(ratio_s.str());
    }
    catch (const char& strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }
}

// create a skeleton from the saved motion
// crée l'armature à partir du film enregistré
bool Run::createSkeleton()
{
    if(!SP_saveload->loaded())
        return false;
/*
    if(!SP_saveload->loaded()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Video", "", "Video Files (*.avi)");

        // we load the motion
        SP_saveload->load(fileName);
    }

    // default filters parameters
    // paramètres par défaut
    int blue_p = 128;
    int red_p = 32;
    int nbr_pass = 8;

    // show the progress bar
    // affiche la barre de progression
    prog = new Progress(NULL);
    prog->show();

    // to set filters parameters values
    // pour changer les paramètres de filtrage
    WinParam wp(NULL, blue_p, red_p, nbr_pass);
    wp.exec();

    // create the skeleton
    // crée l'armature
    SP_skeleton->start(prog, blue_p, red_p, nbr_pass, SP_saveload);

    prog->close();

    // show the skeleton moving
    // affichage de l'animation de l'armature
    if (SP_renderwindow->get_status() == STATUS_NONE) {

        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, kinect, SP_saveload, SP_skeleton, STATUS_SKELETON));

        this->setCentralWidget(SP_renderwindow.data());
        SP_renderwindow->setFixedSize(WIDTH, HEIGHT);
        this->adjustSize();

    }
    else
        SP_renderwindow->change_status(STATUS_SKELETON);
*/
    return true;
}
