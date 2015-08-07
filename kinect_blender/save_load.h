#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <boost/filesystem.hpp>
#include "win_size.h"

class SaveLoad
{

public:
    explicit SaveLoad();
    void load();
    void save();
    void make_list(char*); // make a vector from data

    IplImage *frame;
    std::vector<IplImage> vect_imgs;

private:
    CvCapture* capture;
};

#endif // SAVE_LOAD_H
