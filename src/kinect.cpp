#include "kinect.h"

using namespace std;

pthread_mutex_t Kinect::gl_backbuf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Kinect::gl_frame_cond = PTHREAD_COND_INITIALIZER;
uint8_t *Kinect::rgb_back = (uint8_t*)malloc(WIDTH*HEIGHT*3);
uint8_t *Kinect::rgb_front = (uint8_t*)malloc(WIDTH*HEIGHT*3);
uint8_t *Kinect::rgb_mid = (uint8_t*)malloc(WIDTH*HEIGHT*3);
uint8_t *Kinect::depth_front = (uint8_t*)malloc(WIDTH*HEIGHT*3);
uint8_t *Kinect::depth_mid = (uint8_t*)malloc(WIDTH*HEIGHT*3);
int Kinect::got_depth = 0;
uint16_t *Kinect::t_gamma = (uint16_t*)malloc(2048 * 2);

freenect_video_format Kinect::current_format = FREENECT_VIDEO_RGB;
freenect_video_format Kinect::requested_format = FREENECT_VIDEO_RGB;
freenect_context *Kinect::f_ctx = 0;
freenect_device *Kinect::f_dev = 0;

bool volatile Kinect::die = false;

Kinect::Kinect() {
    connected = running = recording = false;
}

// init the gamma table
// initialisation du tablea gamma
void Kinect::gamma_init() {

    for (int i=0; i<2048; i++) {
        float v = i/2048.0;
        v = powf(v, 3)* 6;
        t_gamma[i] = v*6*256;
    }

}

void Kinect::select_devices() {
    // select device and log levels
    // sélection des devices et du niveau de log
    freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
    freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));
}

// connect only the kinect
void Kinect::connect() {

    // init the freenect
    // initialise freenect
    try {

        if (freenect_init(&f_ctx, NULL) < 0)
            throw "(opkinect) error, can't init";
    }
    catch (const char& strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }

    gamma_init();
    select_devices();

    // number of devices connected
    // nombre de périphériques connetés
    int nr_devices = freenect_num_devices(f_ctx);

    int user_device_number = 0;

    try {

        if (nr_devices < 1) {
            freenect_shutdown(f_ctx);
            throw "(opkinect) error, the kinect is connected ?";
        }

        if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
            freenect_shutdown(f_ctx);
            throw "(opkinect) error, can't open the device";
        }

    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }

    // good, the kinect is connected
    // cool, la kinect est connectée
    connected = true;

}

    bool Kinect::is_connected() {
        return connected;
    }

    bool Kinect::is_running() {
        return running;
    }

    bool Kinect::is_recording() {
        return recording;
    }

    void Kinect::record(bool r) {
        recording = r;
    }

// stop the device
// arrêt du périphérique
void Kinect::stop() {

    if (connected) {

        die = true;

        freenect_stop_depth(f_dev);
        freenect_stop_video(f_dev);

        // no tests, this functions return 0 all time
        freenect_close_device(f_dev);
        freenect_shutdown(f_ctx);
    }

}

void Kinect::depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp)
{
    int i;
    uint16_t *depth = (uint16_t*)v_depth;

    //lock the mutex
    // verrouillage du mutex
    pthread_mutex_lock(&gl_backbuf_mutex);

    for (i=0; i<WIDTH*HEIGHT; i++) {
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

    //unlock the mutex
    // déverrouillage du mutex
    pthread_mutex_unlock(&gl_backbuf_mutex);
}

void Kinect::init_loop() {

    int freenect_angle = 0;
    freenect_set_tilt_degs(f_dev,freenect_angle);
    freenect_set_led(f_dev,LED_RED);

    freenect_set_depth_callback(f_dev, depth_cb);

    freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));

    freenect_start_depth(f_dev);
}

// the loop thread
void *Kinect::loop(void *arg) {

    init_loop();

     while (!die && freenect_process_events(f_ctx) >= 0) {
         if (requested_format != current_format) {
             freenect_stop_video(f_dev);
             freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
             freenect_start_video(f_dev);
             current_format = requested_format;
         }
     }
     return NULL;
}

// start the device
void Kinect::start() {

    try {

        if (!connected)
            throw "(opkinect) not connected";

        int res = pthread_create(&freenect_thread, NULL, loop, NULL);

        if (res < 0)
            throw "(opkinect) error on the freenect_thread";

    }
    catch (const char* strException) {
        running = false;
        freenect_shutdown(f_ctx);
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }

    running = true;
}
