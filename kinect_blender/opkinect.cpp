#include "opkinect.h"

Freenect::Freenect freenect;

Mutex::Mutex() {
    pthread_mutex_init( &m_mutex, NULL );
}

void Mutex::lock() {
    pthread_mutex_lock( &m_mutex );
}

void Mutex::unlock() {
    pthread_mutex_unlock( &m_mutex );
}

TheDevice::TheDevice() {
    connected = running = recording = false;
    freenect_angle = got_frames = window = 0;

}

bool TheDevice::connect() {

    try {
        device = &freenect.createDevice<MyFreenectDevice>(0);
    }
    catch ( const std::exception & e ) {
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
    if (!connected)
        return
    device->stopVideo();
    device->stopDepth();
    connected = false;
}

void TheDevice::start() {
    if (!connected)
        return;

   running = true;

   device->startVideo();
   device->startDepth();
}

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
