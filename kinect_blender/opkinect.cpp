#include "opkinect.h"

pthread_mutex_t TheDevice::gl_backbuf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t TheDevice::gl_frame_cond = PTHREAD_COND_INITIALIZER;
uint8_t *TheDevice::rgb_back = (uint8_t*)malloc(640*480*3);
uint8_t *TheDevice::rgb_front = (uint8_t*)malloc(640*480*3);
uint8_t *TheDevice::rgb_mid = (uint8_t*)malloc(640*480*3);
uint8_t *TheDevice::depth_front = (uint8_t*)malloc(640*480*3);
uint8_t *TheDevice::depth_mid = (uint8_t*)malloc(640*480*3);
int TheDevice::got_rgb = 0;
int TheDevice::got_depth = 0;
uint16_t *TheDevice::t_gamma = (uint16_t*)malloc(2048 * 2);

freenect_video_format TheDevice::current_format = FREENECT_VIDEO_RGB;
freenect_video_format TheDevice::requested_format = FREENECT_VIDEO_RGB;
freenect_context *TheDevice::f_ctx = 0;
freenect_device *TheDevice::f_dev = 0;

bool volatile TheDevice::die = false;


TheDevice::TheDevice() {

    connected = running = recording = false;

}


bool TheDevice::connect() {

    if (freenect_init(&f_ctx, NULL) < 0) {
        return false;
    }

    for (int i=0; i<2048; i++) {
        float v = i/2048.0;
        v = powf(v, 3)* 6;
        t_gamma[i] = v*6*256;
    }

    freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
    freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

    int nr_devices = freenect_num_devices (f_ctx);

    int user_device_number = 0;

    if (nr_devices < 1) {
        freenect_shutdown(f_ctx);
        return false;
    }

    if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
        freenect_shutdown(f_ctx);
        return false;
    }

    connected = true;
    return true;

}

    bool TheDevice::is_connected() {
        return connected;
    }

    bool TheDevice::is_running() {
        return running;
    }

    bool TheDevice::is_recording() {
        return recording;
    }

    void TheDevice::record(bool r) {
        recording = r;
    }

void TheDevice::stop() {

    if (connected) {

        die = true;

        freenect_stop_depth(f_dev);
        freenect_stop_video(f_dev);

        freenect_close_device(f_dev);

        freenect_shutdown(f_ctx);
    }

}

void TheDevice::depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp)
{
    int i;
    uint16_t *depth = (uint16_t*)v_depth;

    pthread_mutex_lock(&gl_backbuf_mutex);
    for (i=0; i<640*480; i++) {
        int pval = t_gamma[depth[i]];
        int lb = pval & 0xff;
        switch (pval>>8) {
            case 0:
                depth_mid[3*i+0] = 255;
                depth_mid[3*i+1] = 255-lb;
                depth_mid[3*i+2] = 255-lb;
                break;
            case 1:
                depth_mid[3*i+0] = 255;
                depth_mid[3*i+1] = lb;
                depth_mid[3*i+2] = 0;
                break;
            case 2:
                depth_mid[3*i+0] = 255-lb;
                depth_mid[3*i+1] = 255;
                depth_mid[3*i+2] = 0;
                break;
            case 3:
                depth_mid[3*i+0] = 0;
                depth_mid[3*i+1] = 255;
                depth_mid[3*i+2] = lb;
                break;
            case 4:
                depth_mid[3*i+0] = 0;
                depth_mid[3*i+1] = 255-lb;
                depth_mid[3*i+2] = 255;
                break;
            case 5:
                depth_mid[3*i+0] = 0;
                depth_mid[3*i+1] = 0;
                depth_mid[3*i+2] = 255-lb;
                break;
            default:
                depth_mid[3*i+0] = 0;
                depth_mid[3*i+1] = 0;
                depth_mid[3*i+2] = 0;
                break;
        }
    }
    got_depth++;
    pthread_cond_signal(&gl_frame_cond);
    pthread_mutex_unlock(&gl_backbuf_mutex);
}

void *TheDevice::loop(void *arg) {
   int freenect_angle = 0;
    freenect_set_tilt_degs(f_dev,freenect_angle);
    freenect_set_led(f_dev,LED_RED);
    freenect_set_depth_callback(f_dev, depth_cb);

    freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));

    freenect_start_depth(f_dev);

     while (!die && freenect_process_events(f_ctx) >= 0) {
         if (requested_format != current_format) {
             freenect_stop_video(f_dev);
             freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
             freenect_start_video(f_dev);
             current_format = requested_format;
         }
     }
}

void TheDevice::start() {

    if (!connected)
        return;

    int res = pthread_create(&freenect_thread, NULL, loop, NULL);

    if (res) {
        freenect_shutdown(f_ctx);
        return;
    }

   running = true;

}
