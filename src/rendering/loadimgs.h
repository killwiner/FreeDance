#ifndef LOADIMGS_H
#define LOADIMGS_H

#include "../defines.h"
//#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <QString>
#include <QSharedPointer>

class LoadImgs
{
public:
    LoadImgs();
    ~LoadImgs();
    bool load_image(const QString &fileName);
    bool load_video(const QString &fileName);
    QSPVImage getImages() const;

private:
    QSPVImage PVImage;
    void make_vector(cv::VideoCapture &video);
};

#endif // LOADIMGS_H
