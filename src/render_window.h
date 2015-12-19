#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "render.h"

class RenderWindow : public Render
{
    Q_OBJECT
public:
    explicit RenderWindow(QWidget *parent = 0, Kinect *thedevice = 0, SaveLoad *saveload = 0, QSharedPointer<Skeleton> SP_skeleton_ = QSharedPointer<Skeleton>(new Skeleton()), int const &status_ = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void change_status(int s); // change the render to skeleton view, kinect view, motion view

private:
    void memory_info();
    bool count_down();
    QMessageBox *message = NULL;
    int timer = 0, count_d = 10;

    GLuint gl_depth_tex;

    std::vector<IplImage>::const_iterator vect_motion_kinect, vect_motion_skeleton;
};



#endif // RENDER_WINDOW_H
