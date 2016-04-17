#include "render_window.h"

using namespace std;

RenderWindow::RenderWindow(QGLWidget *parent, Kinect *kinect, QSharedPointer<IO_frames> &SP_saveload_, QSharedPointer<Skeleton> &SP_skeleton_, int const &status_)
    : Render(20, parent, kinect, SP_saveload_, SP_skeleton_, "Kinect Render")
{

    status = status_;
    width = WIDTH;
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

    glGenTextures(1, &gl_depth_tex);
    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    resizeGL(width, height);

}

void RenderWindow::resizeGL(int width, int height)
{

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, 640, 480, 0, -1.0f, 1.0f);
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

void RenderWindow::render(const GLvoid *data) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 0); glVertex3f(0,0,0);
    glTexCoord2f(1, 0); glVertex3f(width,0,0);
    glTexCoord2f(1, 1); glVertex3f(width,height,0);
    glTexCoord2f(0, 1); glVertex3f(0,height,0);
    glEnd();

}

void RenderWindow::loop_the_movie(vector<cv::Mat> &vect_imgs, vector<cv::Mat>::const_iterator &it) {

    it + 1 != vect_imgs.end() ? ++it : it = vect_imgs.begin();

}

void RenderWindow::make_list() {
    SP_saveload->push_data((char*)kinect->get_depth_front());
}

void RenderWindow::paintGL()
{

    if (status == STATUS_KINECT || status == STATUS_RECORD) {

        run_kinect();
        render(kinect->get_depth_front());

        if (status == STATUS_RECORD) {

            // wait until to start to render the record
            if(!count_down())
                return;

            // we init_the vector vect_imgs before to record
            if (!kinect->is_recording())
                init_record();

          // make the list from the kinect's images
          make_list();

          // show the free space memory
          memory_info();
      }
    }

    if (status == STATUS_MOTION) {

        // if the vector of images is empty, we can't show the motions
        if(SP_saveload->vect_imgs.empty())
            return;

        // render the current motion image
        render(vect_motion_kinect->data);

        // loop the movie with increment
        // boucle le film en incrémentant
        loop_the_movie(SP_saveload->vect_imgs, vect_motion_kinect);

    }

    if (status == STATUS_SKELETON) {

        render(vect_motion_skeleton->data);
        // loop the movie with increment
        // boucle le film en incrémentant
        loop_the_movie(SP_skeleton->vect_imgs, vect_motion_skeleton);
    }
}

void RenderWindow::record_message() {
    std::string str("Will record in : ");
    std::stringstream ss;
    ss << count_d;
    str.append(ss.str());
    SP_message->setText(str.c_str());
    SP_message->update();
}

// return false when the count_down finish
bool RenderWindow::count_down() {

    // count down
    // fin du chronomètre
    if(!count_d)
        return true;

    // we create the message box
    // création de la fenêtre de message
    if (SP_message.isNull())
        SP_message->show();

    // internal clock to refresh the message box message
    // horloge internet pour raffraichir le message
    if (timer == TIMER)
        timer = 0;

    // too early to refresh the message
    // trop tôt pour rafraichir le essage
    if (timer) {
        ++timer;
        return false;
    }

    ++timer;

    // new message
    // nouveau message
    record_message();

    --count_d;
    return false;
}

// show in a window the free memory
void RenderWindow::memory_info() {

    // save capture in the file
    if(SP_message->clickedButton()) {
        SP_saveload->save(SP_saveload->vect_imgs, fileName);
        status = STATUS_KINECT;
        kinect->record(false);
    }

    if (timer == 2 * TIMER)
        timer = 0;

    if (timer) {
        ++timer;
        return;
    }

    ++timer;

    try {

        FILE *in = popen("cat /proc/meminfo", "r");
        if(!in)
            throw "(render_window) error, can't open /proc/meminfo";

        char buffer[128], mem_total_s[128], mem_free_s[128];
        int mem_total, mem_free;

        fscanf(in, "%s", buffer);
        fscanf(in, "%s", mem_total_s);
        fscanf(in, "%s", buffer);
        fscanf(in, "%s", buffer);
        fscanf(in, "%s", mem_free_s);

        pclose(in);

        istringstream smt(mem_total_s);
        istringstream smf(mem_free_s);

        smt >> mem_total;
        smf >> mem_free;

        stringstream ss;
        ss << int(mem_free * 100 / mem_total);

        string str("Mem total : ");
        str.append(mem_total_s);
        str.append(" Kb<br />Mem free : ");
        str.append(mem_free_s);
        str.append(" Kb<br />Mem free : ");
        str.append(ss.str());
        str.append(" %");

        SP_message->setText(str.c_str());
        SP_message->update();

    }
    catch (const char& strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }

}
