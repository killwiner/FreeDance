#include "kinect.h"

extern pthread_t freenect_thread;
extern pthread_cond_t gl_frame_cond;
extern pthread_mutex_t gl_backbuf_mutex;

namespace kinect {
Kinect::Kinect() : die(false) {

    requested_format = FREENECT_VIDEO_RGB;
    current_format = FREENECT_VIDEO_RGB;

    // initialise freenect
    try {
        if (freenect_init(&f_ctx, nullptr) < 0)
            throw "(kinect.cpp) error, can't init the kinect";
    }
    catch (const char& strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }

    gamma_init();
    select_devices();
    get_VGamma(VGamma);

    // number of devices connected
    // nombre de périphériques connetés
    int nbr_devices = freenect_num_devices(f_ctx);

    try {

        if (nbr_devices < 1)
            throw std::string("(kinect.cpp) error, bad number of devices");

        if (freenect_open_device(f_ctx, &f_dev, 0) < 0)
            throw std::string("(kinect.cpp) error, can't open the device");

    }
    catch (const std::string &Msg) {
        std::cerr << Msg << std::endl;

        freenect_shutdown(f_ctx);
        throw;
    }

    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

Kinect::~Kinect() {
    die = true;

    freenect_stop_depth(f_dev);
    freenect_stop_video(f_dev);

    freenect_close_device(f_dev);

    freenect_shutdown(f_ctx);

}

// init the gamma table
// initialisation du tablea gamma
void Kinect::gamma_init() {
    for (double i=0; i<2048; i++)
        VGamma.push_back((i / 256.0f) * (i / 256.0f) * (i / 128.0f) * 9);

}

void Kinect::select_devices() {

    // select device and log levels
    // sélection des devices et du niveau de log
    freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
    freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

}

void Kinect::init_run() {

    freenect_set_tilt_degs(f_dev, 0);
    freenect_set_led(f_dev, LED_RED);

    freenect_set_depth_callback(f_dev, depth_cb);
    freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));

    freenect_start_depth(f_dev);

}

// the loop thread
void Kinect::run() {

    init_run();

    while (!die && freenect_process_events(f_ctx) >= 0) {
        if (requested_format != current_format) {
            freenect_stop_video(f_dev);
            freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
            freenect_start_video(f_dev);
            current_format = requested_format;
        }
    }
}

void Kinect::wait_device() {

    if (current_format == FREENECT_VIDEO_YUV_RGB) {
        while (!got_depth)
            Thread_Wait.wait(&mutex);
            //pthread_cond_wait(&gl_frame_cond, &gl_backbuf_mutex);
    } else {
        while ((!got_depth) && requested_format != current_format)
            Thread_Wait.wait(&mutex);
            //pthread_cond_wait(&gl_frame_cond, &gl_backbuf_mutex);
    }
}

void Kinect::stop() {
    die = true;
}

void Kinect::next() {

    //pthread_mutex_lock(&gl_backbuf_mutex);
    mutex.lock();

    // When using YUV_RGB mode, RGB frames only arrive at 15Hz, so we shouldn't force them to draw in lock-step.
    // However, this is CPU/GPU intensive when we are receiving frames in lockstep.
    if (current_format == FREENECT_VIDEO_YUV_RGB) {
    } else {
        while (!got_depth && requested_format != current_format) {
            Thread_Wait.wait(&mutex);
            //pthread_cond_wait(&gl_frame_cond, &gl_backbuf_mutex);
        }
    }

    if (requested_format != current_format) {
        //pthread_mutex_unlock(&gl_backbuf_mutex);
        mutex.unlock();
        return;
    }

    swap();
    //pthread_mutex_unlock(&gl_backbuf_mutex);
    mutex.unlock();

}
}
