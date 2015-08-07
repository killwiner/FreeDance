#include "render_window.h"

RenderWindow::RenderWindow(QWidget *parent, TheDevice *thedevice, SaveLoad *motion_, Skeleton *skeleton_, int status_)
    : Render(20, parent, thedevice, motion_, skeleton_, "Kinect Render")
{

    status = status_;
    width = WIDTH;
    height = HEIGHT;

    vect_motion=motion->vect_imgs.begin();
    vect_skeleton=skeleton->vect_imgs.begin();

}

void RenderWindow::change_status(int s) {
    status = s;
    vect_motion=motion->vect_imgs.begin();
    vect_skeleton=skeleton->vect_imgs.begin();

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

void RenderWindow::paintGL()
{

    if (status == STATUS_KINECT || status == STATUS_RECORD) {

    pthread_mutex_lock(&thedevice->gl_backbuf_mutex);

    // When using YUV_RGB mode, RGB frames only arrive at 15Hz, so we shouldn't force them to draw in lock-step.
    // However, this is CPU/GPU intensive when we are receiving frames in lockstep.
    if (thedevice->current_format == FREENECT_VIDEO_YUV_RGB) {
        while (!thedevice->got_depth) {
            pthread_cond_wait(&thedevice->gl_frame_cond, &thedevice->gl_backbuf_mutex);
        }
    } else {
        while ((!thedevice->got_depth) && thedevice->requested_format != thedevice->current_format) {
            pthread_cond_wait(&thedevice->gl_frame_cond, &thedevice->gl_backbuf_mutex);
        }
    }

    if (thedevice->requested_format != thedevice->current_format) {
        pthread_mutex_unlock(&thedevice->gl_backbuf_mutex);
        return;
    }

    uint8_t *tmp;

    if (thedevice->got_depth) {
        tmp = thedevice->depth_front;
        thedevice->depth_front = thedevice->depth_mid;
        thedevice->depth_mid = tmp;
        thedevice->got_depth = 0;
    }

    pthread_mutex_unlock(&thedevice->gl_backbuf_mutex);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, thedevice->depth_front);

        glBegin(GL_TRIANGLE_FAN);
        glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
        glTexCoord2f(0, 0); glVertex3f(0,0,0);
        glTexCoord2f(1, 0); glVertex3f(width,0,0);
        glTexCoord2f(1, 1); glVertex3f(width,height,0);
        glTexCoord2f(0, 1); glVertex3f(0,height,0);
        glEnd();

        if (status == STATUS_RECORD) {

            if(!count_down())
                return;

            if (!thedevice->is_recording()) {
                std::vector<IplImage>().swap(motion->vect_imgs);
                motion->vect_imgs.resize(0);
                thedevice->record(true);
            }

            //motion->make_list((char*)&depth[0]);
            motion->make_list((char*)thedevice->depth_front);
            memory_info();

        }

    }

    if (status == STATUS_MOTION) {

        if(motion->vect_imgs.empty())
            return;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, gl_depth_tex);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*vect_motion).width, (*vect_motion).height, 0, GL_BGR, GL_UNSIGNED_BYTE, (*vect_motion).imageData);

        glBegin(GL_TRIANGLE_FAN);
        glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
        glTexCoord2f(0, 0); glVertex3f(0,0,0);
        glTexCoord2f(1, 0); glVertex3f(width,0,0);
        glTexCoord2f(1, 1); glVertex3f(width,height,0);
        glTexCoord2f(0, 1); glVertex3f(0,height,0);
        glEnd();

        if (vect_motion + 1 != motion->vect_imgs.end()) {
            ++vect_motion;
        }
        else {
            vect_motion = motion->vect_imgs.begin();
        }

    }

    if (status == STATUS_SKELETON) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, gl_depth_tex);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*vect_skeleton).width, (*vect_skeleton).height, 0, GL_BGR, GL_UNSIGNED_BYTE, (*vect_skeleton).imageData);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
        glTexCoord2f(0, 0); glVertex3f(0,0,0);
        glTexCoord2f(1, 0); glVertex3f(width,0,0);
        glTexCoord2f(1, 1); glVertex3f(width,height,0);
        glTexCoord2f(0, 1); glVertex3f(0,height,0);
        glEnd();

        if (vect_skeleton + 1 != skeleton->vect_imgs.end())
            ++vect_skeleton;
        else
            vect_skeleton = skeleton->vect_imgs.begin();

    }


}

bool RenderWindow::count_down() {

    if(!count_d)
        return true;

    if (!message) {
        message = new QMessageBox;
        message->show();
    }

    if (timer == 40)
        timer = 0;

    if (timer) {
        ++timer;
        return false;
    }

    ++timer;

    std::string str("Will record in : ");
    std::stringstream ss;
    ss << count_d;
    str.append(ss.str());
    message->setText(str.c_str());
    message->update();

    --count_d;
    return false;

}


void RenderWindow::memory_info() {

    // show a new memory info box
    //if (!message_memory) {
    //    message_memory = new QMessageBox;
    //    message_memory->setStandardButtons(QMessageBox::Yes);
    //    message_memory->setDefaultButton(QMessageBox::Yes);
    //    message_memory->show();
    //}

    // save capture in the file
    if(message->clickedButton()) {
        motion->save();
        status = STATUS_KINECT;
        thedevice->record(false);
    }

    if (timer == 80)
        timer = 0;

    if (timer) {
        ++timer;
        return;
    }

    ++timer;

    FILE *in;
    if(in = popen("cat /proc/meminfo", "r")) {
        char buffer[128], mem_total_s[128], mem_free_s[128];
        int mem_total, mem_free;

        fscanf(in, "%s", buffer);
        fscanf(in, "%s", mem_total_s);
        fscanf(in, "%s", buffer);
        fscanf(in, "%s", buffer);
        fscanf(in, "%s", mem_free_s);

        pclose(in);

        std::istringstream smt(mem_total_s);
        std::istringstream smf(mem_free_s);

        smt >> mem_total;
        smf >> mem_free;

        std::stringstream ss;
        ss << int(mem_free * 100 / mem_total);

        std::string str("Mem total : ");
        str.append(mem_total_s);
        str.append(" Kb<br />Mem free : ");
        str.append(mem_free_s);
        str.append(" Kb<br />Mem free : ");
        str.append(ss.str());
        str.append(" %");

        message->setText(str.c_str());
        message->update();
    }

}
