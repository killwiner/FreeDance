/*************************************************************************/
/* This file is part of Tron.                                            */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

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
    void first_frame();

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
    QSharedPointer<QMessageBox> SP_message;
    QString fileName;
    int timer = 0, count_d = 10;

    GLuint *gl_depth_tex;

    std::vector<cv::Mat>::const_iterator vect_motion_kinect, vect_motion_skeleton;
};

#endif // RENDER_WINDOW_H
