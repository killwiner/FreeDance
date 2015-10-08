#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "win_param.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    thedevice = new TheDevice();
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{

    thedevice->stop();
    delete ui;

}

// to exit the program
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// to connect the kinect
void MainWindow::on_actionConnect_triggered()
{

    QMessageBox *message = new QMessageBox;

    if (thedevice->connect())
        message->setText("Kinect connected");
    else
        message->setText("Can't connect to the Kinect");
    message->show();

}

// show images from the kinect
void MainWindow::on_actionRun_triggered()
{

    if (!thedevice->is_connected()) {
        QMessageBox *message = new QMessageBox;
        message->setText("Kinect not connected");
        message->show();
        return;
    }

    // first time, we create the opengl window and reajust the win size
    if (!Win) {
        thedevice->start();

        Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_KINECT);

        this->setCentralWidget(Win);
        Win->setFixedSize(640, 480);
        this->adjustSize();
    }
    else {
        Win->change_status(STATUS_KINECT);
        Win->change_pause(false);
    }

}

// load the motion
void MainWindow::on_actionLoad_Motion_triggered()
{

    // movie on pause when it's loading
    if (Win)
        Win->change_pause(true);

    QString fileName = QFileDialog::getOpenFileName(this, "Open Video", "", "Video Files (*.avi)");

    // we load the motion
    saveload.load(fileName);

    // first time, we create the opengl window and reajust the win size
    if (!Win) {

        Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_MOTION);

        this->setCentralWidget(Win);
        Win->setFixedSize(640, 480);
        this->adjustSize();
    }
    else
        Win->change_status(STATUS_MOTION);

    Win->change_pause(false);

}

// save the motion
void MainWindow::on_actionSave_Motion_triggered()
{

    if (Win) {
        Win->change_pause(true);
        if(skeleton.vect_imgs.empty())
            saveload.save(saveload.vect_imgs);
        else
            saveload.save(skeleton.vect_imgs);
    }
}

// play the motion
void MainWindow::on_actionRun_Motion_triggered()
{
    if(!Win) {
        Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_MOTION);
        this->setCentralWidget(Win);
        Win->setFixedSize(640, 480);
        this->adjustSize();
    }
    else
        Win->change_status(STATUS_MOTION);
    Win->change_pause(false);
}

// pause the play
void MainWindow::on_actionStop_Motion_triggered()
{
    Win->change_pause(true);
}

// record the movie
void MainWindow::on_actionRecord_triggered()
{
    QMessageBox *message = new QMessageBox;

    if (!thedevice->is_running()) {
        message->setText("Kinect is not running");
        message->show();
        return;
    }

    if (Win) {
        Win->change_status(STATUS_RECORD);
        Win->change_pause(false);
    }
}

// create a skeleton from the saved motion
void MainWindow::on_actionCreate_triggered()
{

    // default filters parameters
    int blue_p = 128;
    int red_p = 32;

    // show the progress bar
    prog = new Progress(NULL);
    prog->show();

    // to set filters parameters values
    WinParam wp(NULL, &blue_p, &red_p);
    wp.exec();

    // create the skeleton
    skeleton.start(prog, blue_p, red_p);

    prog->close();

    // show results
    if (!Win) {

        Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_SKELETON);

        this->setCentralWidget(Win);
        Win->setFixedSize(640, 480);
        this->adjustSize();

    }
    else
        Win->change_status(STATUS_SKELETON);

}

// pause on playing
void MainWindow::on_actionPause_triggered()
{
    if(thedevice->is_running())
        Win->change_pause(true);
}

void MainWindow::on_actionExport_to_blender_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "skeleton.bvh", "Motions (*.bvh)");
    ExportMotion exportmotion;
    exportmotion.save(fileName, skeleton, 10);
}
