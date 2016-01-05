#ifndef KINECT_H
#define KINECT_H

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libfreenect.h>
#include "win_size.h"
#include <pthread.h>
#include <iostream>

class Kinect {
public:
    explicit Kinect();
    // connect the device
    void connect();
    //stop the device
    void stop();
    // start the device
    void start();
    // record the device
    void record(bool);
    // the kinect is connected ?
    bool is_connected();
    // the kinect si running ?
    bool is_running();
    // the kinect is recording ?
    bool is_recording();
    // lock the mutex
    void lock();
    //unlock the mutex
    void unlock();
    // When using YUV_RGB mode, RGB frames only arrive at 15Hz, so we shouldn't force them to draw in lock-step.
    // However, this is CPU/GPU intensive when we are receiving frames in lockstep.
    void lockstep();
    // if requested frame is the same of the current frame then return
    bool requested_current();
    // swap depths
    void swap();
    // get depth font
    const uint8_t *get_depth_front();

private:

    // depth call back
    static void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);

    static freenect_video_format current_format;
    static freenect_video_format requested_format;
    static int got_depth;

    static uint16_t *t_gamma;
    static pthread_cond_t gl_frame_cond;
    static pthread_mutex_t gl_backbuf_mutex;
    static uint8_t *rgb_back, *rgb_front, *rgb_mid, *depth_mid, *depth_front;

    //init loop thread
    static void init_loop();
    static void *loop(void *arg);

    // select devices
    static void select_devices();

    static freenect_context *f_ctx;
    static freenect_device *f_dev;

    static volatile bool die;

    pthread_t freenect_thread;
    bool connected, running, recording;

    // init the gamma table
    // initialisation du tablea gamma
    void gamma_init();
};

#endif // KINECT_H
