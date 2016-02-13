#ifndef RENDER_H
#define RENDER_H

#include <QtOpenGL>
#include <QGLWidget>

#include "kinect.h"
#include "save_load.h"
#include "skeleton.h"

class Render : public QGLWidget
{
    Q_OBJECT
public:
    explicit Render(int framesPerSecond, QWidget *parent, Kinect *kinect, QSharedPointer<SaveLoad> &saveload_, QSharedPointer<Skeleton> &SP_skeleton_, const char *name);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;

    void change_pause(bool p); // to pause or run the motion loop

public slots:
    virtual void timeOutSlot();

private:
    QTimer *t_Timer;
    int interval_time = 1000; // interval time between each image

protected:
    QSharedPointer<SaveLoad> SP_saveload;
    QSharedPointer<Skeleton> SP_skeleton;
    Kinect *kinect;
    int width, height;
    int status; // can be STATUS_KINECT, STATUS_MOTION, STATUS_RECORD, STATUS_SKELETON
};

enum {
    STATUS_NONE,
    STATUS_KINECT,
    STATUS_MOTION,
    STATUS_RECORD,
    STATUS_SKELETON
};

#endif // RENDER_H
