#ifndef OPKINECT_H
#define OPKINECT_H
/*
#include <libfreenect.hpp>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
*/
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libfreenect.h>

#include <pthread.h>

/*
class Mutex {
public:
        Mutex();
        void lock();
        void unlock();

        class ScopedLock
        {
            Mutex & _mutex;
        public:
            ScopedLock(Mutex & mutex)
                : _mutex(mutex)
            {
                _mutex.lock();
            }
            ~ScopedLock()
            {
                _mutex.unlock();
            }
        };

private:
        pthread_mutex_t m_mutex;
};
*/
/*
class MyFreenectDevice : public Freenect::FreenectDevice {
public:
    MyFreenectDevice(freenect_context *_ctx, int _index);
    void VideoCallback(void* _rgb, uint32_t timestamp);
    void DepthCallback(void* _depth, uint32_t timestamp);
    bool getRGB(std::vector<uint8_t> &buffer);
    bool getDepth(std::vector<uint8_t> &buffer);

private:
    std::vector<uint8_t> m_buffer_depth;
    std::vector<uint8_t> m_buffer_video;
    std::vector<uint16_t> m_gamma;
    Mutex m_rgb_mutex;
    Mutex m_depth_mutex;
    bool m_new_rgb_frame;
    bool m_new_depth_frame;
};
*/

//void DrawGLScene(MyFreenectDevice* device);

class TheDevice {
public:
    explicit TheDevice();
    /*
    MyFreenectDevice* device;

    double freenect_angle;
    int got_frames,window;
    int g_argc;
    char **g_argv;
*/

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
    static int got_rgb;
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

