#ifndef LIBFREENECT_H
#define LIBFREENECT_H

#include <libfreenect/libfreenect.h>
#include <QMutex>
#include <QWaitCondition>
#include <vector>
#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include <opencv2/highgui.hpp>

#define WIDTH_KINECT 640
#define HEIGHT_KINECT 480

namespace kinect {

class FNect : public QThread {

    Q_OBJECT

    public :
        FNect();
        ~FNect();
        cv::Mat *getImage() const;

    protected :

        static void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);
        static QWaitCondition Thread_Wait;
        static cv::Mat *StaticMDepth_front;
        static QMutex mutex;
        static int got_depth;
        void swap();
        void get_VGamma(const std::vector<uint16_t> &VGamma);

    private :
        static cv::Mat *StaticMDepth_mid;
        static std::vector<uint16_t> StaticVGamma;
};
}
#endif // LIBFREENECT_H
