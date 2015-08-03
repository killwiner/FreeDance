#ifndef ROOT_H
#define ROOT_H

#include "maths_vect.h"
#include "win_size.h"
#include <opencv2/opencv.hpp>

class Root {
public:
    explicit Root();
    virtual void search(float, int, float);
    void refresh(IplImage *);

    Vect<float> p;
    int radius;

protected:
    IplImage *frame;

};

#endif // ROOT_H
