#ifndef RUN_H
#define RUN_H

#include <QFileDialog>
#include <QMessageBox>
#include "render_window.h"
#include "skeleton.h"
#include "export_motion.h"

#define MENU_OPEN 0

class Run
{
public:
    explicit Run();
    ~Run();
    void load(QString fileName);
    QWidget *getwidget();

private:
    QSharedPointer<RenderWindow> SP_renderwindow; // pointer on the OpenGL window
    QSharedPointer<Skeleton> SP_skeleton; // pointer on the skeleton with roots
    Kinect *kinect; // the device for the kinect
    QSharedPointer<IO_frames> SP_saveload; // to save or load a motion

};

#endif // RUN_H
