#include "render_window.h"

using namespace std;

RenderWindow::RenderWindow(QGLWidget *parent, cv::Mat &mat_preview_after_, Kinect *kinect, QSharedPointer<IO_frames> &SP_saveload_, QSharedPointer<Skeleton> &SP_skeleton_, int const &status_)
    : Render(20, parent, mat_preview_after_, kinect, SP_saveload_, SP_skeleton_, "Kinect Render")
{

    status = status_;
    width = WIDTH * 2 + 4;
    height = HEIGHT;

    // vectors with motion movie or the skeleton movie
    vect_motion_kinect=SP_saveload->vect_imgs.begin();
    vect_motion_skeleton=SP_skeleton->vect_imgs.begin();

    SP_message = QSharedPointer<QMessageBox>(new QMessageBox());

}

// change to show the kinect motion, the record ...
void RenderWindow::change_status(int s) {
    status = s;
    vect_motion_kinect=SP_saveload->vect_imgs.begin();
    vect_motion_skeleton=SP_skeleton->vect_imgs.begin();

}

int RenderWindow::get_status() {
    return status;
}

void RenderWindow::initializeGL()
{

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);

    gl_depth_tex = new GLuint[2];
    glGenTextures(2, gl_depth_tex);

    resizeGL(width, height);

}

void RenderWindow::resizeGL(int width, int height)
{

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, width, height, 0, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

}

void RenderWindow::run_kinect() {

    // lock the mutex
    kinect->lock();

    // When using YUV_RGB mode, RGB frames only arrive at 15Hz, so we shouldn't force them to draw in lock-step.
    // However, this is CPU/GPU intensive when we are receiving frames in lockstep.
    kinect->lockstep();

    // // if requested frame is the same of the current frame then return
    if(kinect->requested_current())
        return;

    // swap depths
    kinect->swap();

    // unlock the mutex
    kinect->unlock();

}

void RenderWindow::init_record() {

    // reset the vector
    std::vector<cv::Mat>().swap(SP_saveload->vect_imgs);
    SP_saveload->vect_imgs.resize(0);

    kinect->record(true);

}

void RenderWindow::render(const GLvoid *data_0, const GLvoid *data_1) {

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, data_0);

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, data_1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex[0]);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 0); glVertex3f(0,0,0);
    glTexCoord2f(1, 0); glVertex3f(WIDTH,0,0);
    glTexCoord2f(1, 1); glVertex3f(WIDTH,HEIGHT,0);
    glTexCoord2f(0, 1); glVertex3f(0,HEIGHT,0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex[1]);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 0); glVertex3f(WIDTH + 4,0,0);
    glTexCoord2f(1, 0); glVertex3f(width,0,0);
    glTexCoord2f(1, 1); glVertex3f(width,HEIGHT,0);
    glTexCoord2f(0, 1); glVertex3f(WIDTH + 4,HEIGHT,0);
    glEnd();

}

void RenderWindow::loop_the_movie(vector<cv::Mat> &vect_imgs, vector<cv::Mat>::const_iterator &it) {

    it + 1 != vect_imgs.end() ? ++it : it = vect_imgs.begin();

}

void RenderWindow::first_frame() {
    vect_motion_kinect = SP_saveload->vect_imgs.begin();
    vect_motion_skeleton = SP_skeleton->vect_imgs.begin();
}

void RenderWindow::make_list() {
    SP_saveload->push_data((char*)kinect->get_depth_front());
}

void RenderWindow::paintGL()
{

    if (status == STATUS_KINECT || status == STATUS_RECORD) {

        run_kinect();
        render(kinect->get_depth_front(), mat_preview_after.data);

        if (status == STATUS_RECORD) {

            // we init_the vector vect_imgs before to record
            if (!kinect->is_recording())
                init_record();

          // make the list from the kinect's images
          make_list();

          // show the free space memory
          //memory_info();
      }
    }

    if (status == STATUS_MOTION) {

        // if the vector of images is empty, we can't show the motions
        if(SP_saveload->vect_imgs.empty())
            return;

        // render the current motion image
        render(vect_motion_kinect->data, mat_preview_after.data);

        // loop the movie with increment
        // boucle le film en incrémentant
        loop_the_movie(SP_saveload->vect_imgs, vect_motion_kinect);

    }

    if (status == STATUS_SKELETON) {

        render(vect_motion_kinect->data, vect_motion_skeleton->data);
        // loop the movie with increment
        // boucle le film en incrémentant
        loop_the_movie(SP_skeleton->vect_imgs, vect_motion_skeleton);
        loop_the_movie(SP_saveload->vect_imgs, vect_motion_kinect);

    }
}

int RenderWindow::get_position() {
   return vect_motion_kinect - SP_saveload->vect_imgs.begin();
}


