#ifndef ROOT_H
#define ROOT_H

#include "maths_vect.h"
#include "win_size.h"
#include <opencv2/opencv.hpp>

class Root {
public:
    explicit Root(IplImage*);
    virtual void search(IplImage*, float const &, int const &);

    Vect<float> p;

protected:
    IplImage *frame;

};

#endif // ROOT_H
