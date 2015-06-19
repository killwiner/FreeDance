#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "render.h"

class RenderWindow : public Render
{
    Q_OBJECT
public:
    explicit RenderWindow(QWidget *parent = 0, TheDevice *thedevice = 0, SaveLoad *motion_ = 0, Skeleton *skeleton_ = 0, int status_ = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void change_status(int s); // change to skeleton view, kinect view, motion view

private:

    void memory_info();
    QMessageBox *message = NULL;
    int timer = 0;

    GLuint gl_depth_tex, gl_rgb_tex;

    std::vector<IplImage>::const_iterator vect_motion, vect_skeleton;

};



#endif // RENDER_WINDOW_H
