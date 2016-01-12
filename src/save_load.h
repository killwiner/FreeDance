#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <boost/filesystem.hpp>
#include "win_size.h"
#include <QString>
#include <QSharedPointer>

class SaveLoad
{

private:
    CvCapture* capture;

public:
    explicit SaveLoad();
    void load(const QString &fileName);
    void save(std::vector< QSharedPointer<IplImage> > &);
    void make_list(char*); // make a vector from data

    QSharedPointer<IplImage> SP_frame;
    std::vector< QSharedPointer<IplImage> > vect_imgs;

};

#endif // SAVE_LOAD_H
