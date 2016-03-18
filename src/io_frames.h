#ifndef IO_FRAMES_H
#define IO_FRAMES_H

#include <opencv2/opencv.hpp>
#include <vector>
//#include <boost/filesystem.hpp>
#include <QFileDialog>
#include "win_size.h"
#include <QString>
#include <QSharedPointer>

class IO_frames
{

public:
    explicit IO_frames();
    void load(const QString &fileName);
    void save(std::vector< cv::Mat > &, QString &);
    void push_data(char*); // make a vector from data
    cv::VideoCapture open_input(const QString &);
    int get_nbr_imgs();
    bool loaded();

    std::vector< cv::Mat > vect_imgs;

private:
    int nbr_imgs;
    cv::Mat mat_frame;
    bool make_vector(int const &, cv::VideoCapture &);
    bool video_loaded;
};

#endif // IO_FRAMES_H
