#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "render_window.h"
#include "skeleton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private slots:
    void on_actionExit_triggered(); // exit the program

    void on_actionConnect_triggered(); // connect the kinect

    void on_actionRun_triggered(); // run the capture

    void on_actionLoad_Motion_triggered(); // load a motion from the file

    void on_actionSave_Motion_triggered(); // save a record to the file

    void on_actionRun_Motion_triggered(); // play the motion

    void on_actionStop_Motion_triggered(); // stop to play the motion

    void on_actionRecord_triggered(); // record the capture to the motion

    void on_actionCreate_triggered(); // create the skeleton from the file

    void on_actionPause_triggered();

private:
    Ui::MainWindow *ui;
    RenderWindow *Win = NULL;
    TheDevice *thedevice;
    SaveLoad saveload;
    Skeleton skeleton;
    Progress *prog;
};

#endif // MAINWINDOW_H
