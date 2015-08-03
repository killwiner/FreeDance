#include "opkinect.h"

//Freenect::Freenect freenect;

/*
Mutex::Mutex() {
    pthread_mutex_init( &m_mutex, NULL );
}

void Mutex::lock() {
    pthread_mutex_lock( &m_mutex );
}

void Mutex::unlock() {
    pthread_mutex_unlock( &m_mutex );
}
*/

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
    //freenect_angle = got_frames = window = 0;



}


bool TheDevice::connect() {
/*
    try {
        device = &freenect.createDevice<MyFreenectDevice>(0);

    }
    catch ( const std::exception & e ) {
        return false;
    }

    connected = true;
    return true;
*/

    if (freenect_init(&f_ctx, NULL) < 0) {
        return false;
    }

    for (int i=0; i<2048; i++) {
        float v = i/2048.0;
        v = powf(v, 3)* 6;
        t_gamma[i] = v*6*256;
            printf(">>> %d >>>\n", i);
    }

printf(">>> NEXT >>>\n");

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
    /*
    device->stopVideo();
    device->stopDepth();
    connected = false;
    */

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

    //freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, current_format));
    freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
    //freenect_set_video_buffer(f_dev, rgb_back);

    freenect_start_depth(f_dev);
    //freenect_start_video(f_dev);

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

/*
   device->startVideo();
   device->startDepth();
   */
}
/*
MyFreenectDevice::MyFreenectDevice(freenect_context *_ctx, int _index)
                : Freenect::FreenectDevice(_ctx, _index), m_buffer_depth(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),m_buffer_video(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes), m_gamma(2048), m_new_rgb_frame(false), m_new_depth_frame(false)
        {
                for( unsigned int i = 0 ; i < 2048 ; i++) {
                        float v = i/2048.0;
                        v = std::pow(v, 3)* 6;
                        m_gamma[i] = v*6*256;
                }
        }
        //~MyFreenectDevice(){}
        // Do not call directly even in child
        void MyFreenectDevice::VideoCallback(void* _rgb, uint32_t timestamp) {
                Mutex::ScopedLock lock(m_rgb_mutex);
                uint8_t* rgb = static_cast<uint8_t*>(_rgb);
                std::copy(rgb, rgb+getVideoBufferSize(), m_buffer_video.begin());
                m_new_rgb_frame = true;
        };
        // Do not call directly even in child
        void MyFreenectDevice::DepthCallback(void* _depth, uint32_t timestamp) {
                Mutex::ScopedLock lock(m_depth_mutex);
                uint16_t* depth = static_cast<uint16_t*>(_depth);
                for( unsigned int i = 0 ; i < 640*480 ; i++) {
                        int pval = m_gamma[depth[i]];
                        int lb = pval & 0xff;
                        switch (pval>>8) {
                        case 0:
                                m_buffer_depth[3*i+0] = 255;
                                m_buffer_depth[3*i+1] = 255-lb;
                                m_buffer_depth[3*i+2] = 255-lb;
                                break;
                        case 1:
                                m_buffer_depth[3*i+0] = 255;
                                m_buffer_depth[3*i+1] = lb;
                                m_buffer_depth[3*i+2] = 0;
                                break;
                        case 2:
                                m_buffer_depth[3*i+0] = 255-lb;
                                m_buffer_depth[3*i+1] = 255;
                                m_buffer_depth[3*i+2] = 0;
                                break;
                        case 3:
                                m_buffer_depth[3*i+0] = 0;
                                m_buffer_depth[3*i+1] = 255;
                                m_buffer_depth[3*i+2] = lb;
                                break;
                        case 4:
                                m_buffer_depth[3*i+0] = 0;
                                m_buffer_depth[3*i+1] = 255-lb;
                                m_buffer_depth[3*i+2] = 255;
                                break;
                        case 5:
                            m_buffer_depth[3*i+0] = 0;
                            m_buffer_depth[3*i+1] = 0;
                            m_buffer_depth[3*i+2] = 255-lb;
                            break;
                    default:
                            m_buffer_depth[3*i+0] = 0;
                            m_buffer_depth[3*i+1] = 0;
                            m_buffer_depth[3*i+2] = 0;
                            break;
                    }
            }
            m_new_depth_frame = true;
    }

    bool MyFreenectDevice::getRGB(std::vector<uint8_t> &buffer) {
            Mutex::ScopedLock lock(m_rgb_mutex);
            if (!m_new_rgb_frame)
                    return false;
            buffer.swap(m_buffer_video);
            m_new_rgb_frame = false;
            return true;
    }

    bool MyFreenectDevice::getDepth(std::vector<uint8_t> &buffer) {
            Mutex::ScopedLock lock(m_depth_mutex);
            if (!m_new_depth_frame)
                    return false;
            buffer.swap(m_buffer_depth);
            m_new_depth_frame = false;
            return true;
    }
*/
