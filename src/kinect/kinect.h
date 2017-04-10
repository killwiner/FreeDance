#ifndef KINECT_H
#define KINECT_H

#include "libfreenect.h"
#include <iostream>
#include <cmath>

namespace kinect {

class Kinect : public FNect
{
    Q_OBJECT

public:
    Kinect();
    ~Kinect();

    freenect_context *get_f_ctx() { return f_ctx; };
    freenect_device *get_f_dev() { return f_dev; };

public slots:
    void stop();
    void next();

private:

    freenect_context *f_ctx;
    freenect_device *f_dev;
    std::vector<uint16_t> VGamma;
    pthread_mutex_t gl_backbuf_mutex;
    pthread_cond_t gl_frame_cond;
    freenect_video_format requested_format, current_format;
    bool die;

    void gamma_init();
    void select_devices();
    void wait_device();
    void init_run();
    void run();

};
}
#endif // KINECT_H
