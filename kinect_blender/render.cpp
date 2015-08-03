#include "render.h"
#include <stdio.h>

Render::Render(int framesPerSecond, QWidget *parent, TheDevice *thedevice_, SaveLoad *motion_, Skeleton *skeleton_, char *name)
    : QGLWidget(parent)
{

    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000;
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }

    thedevice = thedevice_;
    motion = motion_;
    skeleton = skeleton_;

}

void Render::change_pause(bool p) {

    if (p)
        printf("STOPED\n");
    else
        printf("RUNNING\n");
    if (p)
        t_Timer->stop();
    else
        t_Timer->start();

}

void Render::timeOutSlot()
{

    updateGL();

}
