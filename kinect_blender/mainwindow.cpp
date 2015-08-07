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

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionConnect_triggered()
{

    QMessageBox *message = new QMessageBox;

    if (thedevice->connect())
        message->setText("Kinect connected");
    else
        message->setText("Can't connect to the Kinect");
    message->show();

}

void MainWindow::on_actionRun_triggered()
{

    if (!thedevice->is_connected()) {
        QMessageBox *message = new QMessageBox;
        message->setText("Kinect not connected");
        message->show();
        return;
    }

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

void MainWindow::on_actionLoad_Motion_triggered()
{

    if (Win)
        Win->change_pause(true);

    saveload.load();

    if (!Win) {

        Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_MOTION);

        this->setCentralWidget(Win);
        Win->setFixedSize(640, 480);
        this->adjustSize();
    }
    else
        Win->change_status(STATUS_MOTION);
    Win->change_pause(false);
printf("ICI\n");
}

void MainWindow::on_actionSave_Motion_triggered()
{
    if (Win) {
        Win->change_pause(true);
        saveload.save();
    }
}

void MainWindow::on_actionRun_Motion_triggered()
{
    Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_MOTION);
    this->setCentralWidget(Win);
    Win->setFixedSize(640, 480);
    this->adjustSize();
    Win->change_pause(false);

}

void MainWindow::on_actionStop_Motion_triggered()
{
    Win->change_pause(true);
}

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

void MainWindow::on_actionCreate_triggered()
{

    int blue_p = 128;
    int red_p = 32;

    prog = new Progress(NULL);
    prog->show();

    WinParam wp(NULL, &blue_p, &red_p);
    wp.exec();

    skeleton.start(prog, blue_p, red_p);

    prog->close();

    if (!Win) {

        Win = new RenderWindow(NULL, thedevice, &saveload, &skeleton, STATUS_SKELETON);

        this->setCentralWidget(Win);
        Win->setFixedSize(640, 480);
        this->adjustSize();

    }
    else
        Win->change_status(STATUS_SKELETON);

}

void MainWindow::on_actionPause_triggered()
{
    if(thedevice->is_running())
        Win->change_pause(true);
}
