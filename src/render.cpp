#include "render.h"
#include <stdio.h>

Render::Render(int framesPerSecond, QWidget *parent, Kinect *kinect_, QSharedPointer<IO_frames> &SP_saveload_, QSharedPointer<Skeleton> &SP_skeleton_, const char *name)
    : QGLWidget(parent), SP_saveload(SP_saveload_), SP_skeleton(SP_skeleton_), kinect(kinect_)
{

    //setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = interval_time;
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
}

// to make a pause or to play
void Render::change_pause(bool p) {
    if (p)
        t_Timer->stop();
    else
        t_Timer->start();

}

void Render::timeOutSlot()
{
    updateGL();
}
