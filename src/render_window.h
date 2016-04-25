#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "render.h"
#define TIMER 40

class RenderWindow : public Render
{
    Q_OBJECT
public:
    explicit RenderWindow(QGLWidget *parent, cv::Mat &mat_preview_after, Kinect *kinect, QSharedPointer<IO_frames> &SP_saveload_, QSharedPointer<Skeleton> &SP_skeleton_, int const &status_);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void change_status(int s); // change the render to skeleton view, kinect view, motion view
    int get_status();
    int get_position();

private:
    // run kinect in real time
    void run_kinect();
    // we init_the vector vect_imgs before to record
    void init_record();
    // render the texture from the kinect
    void render(const GLvoid *, const GLvoid *);
    // make the list from the kinect's images
    void make_list();
    void loop_the_movie(std::vector<cv::Mat> &, std::vector<cv::Mat>::const_iterator &);
    // new message
    void record_message();
    void memory_info();
    bool count_down();
    QSharedPointer<QMessageBox> SP_message;
    QString fileName;
    int timer = 0, count_d = 10;

    GLuint *gl_depth_tex;

    std::vector<cv::Mat>::const_iterator vect_motion_kinect, vect_motion_skeleton;
};

#endif // RENDER_WINDOW_H
