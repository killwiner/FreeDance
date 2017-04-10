#include "libfreenect.h"

pthread_t freenect_thread;
pthread_cond_t gl_frame_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t gl_backbuf_mutex = PTHREAD_MUTEX_INITIALIZER;

int kinect::FNect::got_depth = 0;
cv::Mat *kinect::FNect::StaticMDepth_mid;
cv::Mat *kinect::FNect::StaticMDepth_front;
std::vector<uint16_t> kinect::FNect::StaticVGamma;
QMutex kinect::FNect::mutex;
QWaitCondition kinect::FNect::Thread_Wait;

namespace kinect {
FNect::FNect() {
    StaticMDepth_front = new cv::Mat(HEIGHT_KINECT, WIDTH_KINECT, CV_8UC3, cv::Scalar(0, 0, 0));
    StaticMDepth_mid = new cv::Mat(HEIGHT_KINECT, WIDTH_KINECT, CV_8UC3, cv::Scalar(0, 0, 0));
}

FNect::~FNect() {
    delete StaticMDepth_front;
    delete StaticMDepth_mid;
}

cv::Mat *FNect::getImage() const {
    return StaticMDepth_front;
}

void FNect::get_VGamma(const std::vector<uint16_t> &VGamma) {
    StaticVGamma = VGamma;
}

void FNect::swap() {

    if (got_depth) {
        cv::Mat MTmp;
        MTmp = StaticMDepth_front->clone();
        StaticMDepth_mid->copyTo(*StaticMDepth_front);
        MTmp.copyTo(*StaticMDepth_mid);
        got_depth = 0;
    }
}

void FNect::depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp) {

    // pour les warning unused variables
    (void)*dev;
    (void)timestamp;

    uint16_t *depth = (uint16_t*)v_depth;

    //pthread_mutex_lock(&gl_backbuf_mutex);
    mutex.lock();

    for (int i=0; i<640*480; ++i) {
        int pval = StaticVGamma.at(depth[i]);
        int lb = pval & 0xff;

        // ->at, accès mémoire trop long par rapport à ->data, on perd des frames.
        switch (pval>>8) {

            case 0:
                StaticMDepth_mid->data[3*i] = 255;
                StaticMDepth_mid->data[3*i+1] = 255 - lb;
                StaticMDepth_mid->data[3*i+2] = 255 - lb;
                break;
            case 1:
                StaticMDepth_mid->data[3*i] = 255;
                StaticMDepth_mid->data[3*i+1] = lb;
                StaticMDepth_mid->data[3*i+2] = 0;
                break;
            case 2:
                StaticMDepth_mid->data[3*i] = 255 - lb;
                StaticMDepth_mid->data[3*i+1] = 255;
                StaticMDepth_mid->data[3*i+2] = 0;
                break;
            case 3:
                StaticMDepth_mid->data[3*i] = 0;
                StaticMDepth_mid->data[3*i+1] = 255;
                StaticMDepth_mid->data[3*i+2] = lb;
                break;
            case 4:
                StaticMDepth_mid->data[3*i] = 0;
                StaticMDepth_mid->data[3*i+1] = 255 - lb;
                StaticMDepth_mid->data[3*i+2] = 255;
                break;
            case 5:
                StaticMDepth_mid->data[3*i] = 0;
                StaticMDepth_mid->data[3*i+1] = 0;
                StaticMDepth_mid->data[3*i+2] = 255 - lb;
                break;
            default:
                StaticMDepth_mid->data[3*i] = 0;
                StaticMDepth_mid->data[3*i+1] = 0;
                StaticMDepth_mid->data[3*i+2] = 0;
                break;
        }
    }

        got_depth++;

        //émission du signal pour débloquer le thread
        Thread_Wait.wakeAll();
        //pthread_cond_signal(&gl_frame_cond);

        //unlock the mutex
        // déverrouillage du mutex
        mutex.unlock();
        //pthread_mutex_unlock(&gl_backbuf_mutex);
}
}
