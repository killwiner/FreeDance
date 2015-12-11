#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "win_param.h"

using namespace std;

// constructor
// constructeur
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    try {
        thedevice = new TheDevice();
        SP_skeleton = QSharedPointer<Skeleton>(new Skeleton());
    }
    catch ( const exception &e )
    {
        cerr << "(mainwindow) Exception caught !!" << endl;
        cerr << e.what() << endl;
    }
    ui->setupUi(this);    
}

// destroy all
// tout détruire
MainWindow::~MainWindow()
{

    try {
        thedevice->stop();
        delete thedevice;
        SP_renderwindow.clear();
        SP_skeleton.clear();
    }
    catch ( const exception &e )
    {
        cerr << "Exception caught !!" << endl;
        cerr << e.what() << endl;
    }

    delete ui;
}

// to exit the program
// on sort du programme
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// to connect the kinect
// connecte la kinect
void MainWindow::on_actionConnect_triggered()
{

    QMessageBox message;

    if (thedevice->connect())
        message.setText("Kinect connected");
    else
        message.setText("Can't connect to the Kinect");
    message.show();

}

// show images from the kinect
// On visualise les images en provenance de la kinect
void MainWindow::on_actionRun_triggered()
{

    if (!thedevice->is_connected()) {
        QMessageBox message;
        message.setText("Kinect not connected");
        message.show();
        return;
    }

    // first time, we create the opengl window and reajust the win size
    // Premier rendu, on redimensionne la fenettre et nous créons la fenêtre opengl
    if (SP_renderwindow.isNull()) {
        thedevice->start();

        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, thedevice, &saveload, SP_skeleton, STATUS_KINECT));

        //Sets the given widget to be the main window's central widget.
        // win devient la widget central
        this->setCentralWidget(SP_renderwindow.data());

        SP_renderwindow->setFixedSize(WIDTH, HEIGHT);
        this->adjustSize();
    }
    // the opengl window exists already. just change the status
    // la capture sur la fenêtre opengl existe déjà, il suffit de changer le status
    else {
        SP_renderwindow->change_status(STATUS_KINECT);
        SP_renderwindow->change_pause(false);
    }

}

// load the motion
void MainWindow::on_actionLoad_Motion_triggered()
{

    // movie on pause when it's loading
    // le filme est mis sur pause pendant le chargement
    if (!SP_renderwindow.isNull())
        SP_renderwindow->change_pause(true);

    QString fileName = QFileDialog::getOpenFileName(this, "Open Video", "", "Video Files (*.avi)");

    // we load the motion
    saveload.load(fileName);

    // first time, we create the opengl window and reajust the win size
    // Premier rendu, on redimensionne la fenettre et nous créons la fenêtre opengl
    if (SP_renderwindow.isNull()) {

        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, thedevice, &saveload, SP_skeleton, STATUS_MOTION));

        this->setCentralWidget(SP_renderwindow.data());
        SP_renderwindow->setFixedSize(WIDTH, HEIGHT);
        this->adjustSize();
    }
    else
        // the opengl window exists already. just change the status
        // la capture sur la fenêtre opengl existe déjà, il suffit de changer le status
        SP_renderwindow->change_status(STATUS_MOTION);

    SP_renderwindow->change_pause(false);

}

// save the motion
// sauvegarde la motion capture
void MainWindow::on_actionSave_Motion_triggered()
{

    if (!SP_renderwindow.isNull()) {
        SP_renderwindow->change_pause(true);
        saveload.save(saveload.vect_imgs);
    }

}

// play the motion
// fait tourner la motion capture à l'écran
void MainWindow::on_actionRun_Motion_triggered()
{

    if(SP_renderwindow.isNull()) {
        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, thedevice, &saveload, SP_skeleton, STATUS_MOTION));
        this->setCentralWidget(SP_renderwindow.data());
        SP_renderwindow->setFixedSize(WIDTH, HEIGHT);
        this->adjustSize();
    }
    else
        SP_renderwindow->change_status(STATUS_MOTION);
    SP_renderwindow->change_pause(false);

}

// pause the play
// met le film en pause
void MainWindow::on_actionStop_Motion_triggered()
{
    SP_renderwindow->change_pause(true);
}

// record the movie
// enregistre le film
void MainWindow::on_actionRecord_triggered()
{
    QMessageBox message;

    if (!thedevice->is_running()) {
        message.setText("Kinect is not running");
        message.exec();
        return;
    }

    if (!SP_renderwindow.isNull()) {
        SP_renderwindow->change_status(STATUS_RECORD);
        SP_renderwindow->change_pause(false);
    }
}

// create a skeleton from the saved motion
// crée l'armature à partir du film enregistré
void MainWindow::on_actionCreate_triggered()
{

    // default filters parameters
    // paramètres par défaut
    int blue_p = 128;
    int red_p = 32;

    // show the progress bar
    // affiche la barre de progression
    prog = new Progress(NULL);
    prog->show();

    // to set filters parameters values
    // pour changer les paramètres de filtrage
    WinParam wp(NULL, &blue_p, &red_p);
    wp.exec();

    // create the skeleton
    // crée l'armature
    SP_skeleton->start(prog, blue_p, red_p);

    prog->close();

    // show the skeleton moving
    // affichage de l'animation de l'armature
    if (SP_renderwindow.isNull()) {

        SP_renderwindow = QSharedPointer<RenderWindow>(new RenderWindow(NULL, thedevice, &saveload, SP_skeleton, STATUS_SKELETON));

        this->setCentralWidget(SP_renderwindow.data());
        SP_renderwindow->setFixedSize(WIDTH, HEIGHT);
        this->adjustSize();

    }
    else
        SP_renderwindow->change_status(STATUS_SKELETON);

}

// pause the play
// met le film en pause
void MainWindow::on_actionPause_triggered()
{
    if(thedevice->is_running())
        SP_renderwindow->change_pause(true);
}

// export the skeleton into a blender motion file
// enregistre dans un fichier, une armature pour blender
void MainWindow::on_actionExport_to_blender_2_triggered()
{

    QMessageBox message;

    if (SP_skeleton.isNull()) {
        message.setText("Please, build a skeleton first.");
        message.exec();
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "skeleton.bvh", "Motions (*.bvh)");
    ExportMotion exportmotion;

    exportmotion.save(fileName, SP_skeleton, SP_skeleton->nbr_imgs);

    message.setText("The file was saved.");
    message.exec();

}
