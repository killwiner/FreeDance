#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "render_window.h"
#include "skeleton.h"
#include "export_motion.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered(); // exit the program

    void on_actionConnect_triggered(); // connect the kinect

    void on_actionRun_triggered(); // run the capture

    void on_actionLoad_Motion_triggered(); // load the motion from the file

    void on_actionSave_Motion_triggered(); // save the record to the file

    void on_actionRun_Motion_triggered(); // play the motion

    void on_actionStop_Motion_triggered(); // stop to play the motion

    void on_actionRecord_triggered(); // record the capture to the motion

    void on_actionCreate_triggered(); // create the skeleton from the file

    void on_actionPause_triggered(); // pause on the motion

    void on_actionExport_to_blender_2_triggered(); // export to the blender motion file

private:
    QSharedPointer<RenderWindow> SP_renderwindow; // pointer on the OpenGL window
    QSharedPointer<Skeleton> SP_skeleton; // pointer on the skeleton with roots
    Ui::MainWindow *ui;
    Kinect *thedevice; // the device for the kinect
    SaveLoad saveload; // to save or load a motion
    Progress *prog; // the progress bar when it's building the skeleton
};

#endif // MAINWINDOW_H
