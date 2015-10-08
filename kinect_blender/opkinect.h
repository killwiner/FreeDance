#ifndef OPKINECT_H
#define OPKINECT_H

#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libfreenect.h>

#include <pthread.h>

class TheDevice {
public:
    explicit TheDevice();

    bool connect();
    void stop();
    void start();
    void record(bool);
    bool is_connected();
    bool is_running();
    bool is_recording();

    static void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);

    static freenect_video_format current_format;
    static freenect_video_format requested_format;
    static int got_depth;

    static uint16_t *t_gamma;
    static pthread_cond_t gl_frame_cond;
    static pthread_mutex_t gl_backbuf_mutex;
    static uint8_t *rgb_back, *rgb_front, *rgb_mid, *depth_mid, *depth_front;

    static void *loop(void *arg);

    static freenect_context *f_ctx;
    static freenect_device *f_dev;

    static volatile bool die;

private:

    pthread_t freenect_thread;


    bool connected, running, recording;
};

#endif // OPKINECT_H
