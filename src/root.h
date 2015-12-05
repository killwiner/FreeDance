#ifndef ROOT_H
#define ROOT_H

#include "maths_vect.h"
#include "win_size.h"
#include <opencv2/opencv.hpp>

#define PIXEL_COLOR_BLUE(X, Y) imageData[coord_gbr(Vect<int>(X, Y, 0))]
#define PIXEL_COLOR_GREEN(X, Y) imageData[coord_gbr(Vect<int>(X, Y, 0)) + 1]
#define PIXEL_COLOR_RED(X, Y) imageData[coord_gbr(Vect<int>(X, Y, 0)) + 2]

#define PIXEL_COLOR_BLUE_VECT(V) imageData[coord_gbr(V)]
#define PIXEL_COLOR_GREEN_VECT(V) imageData[coord_gbr(V) + 1]
#define PIXEL_COLOR_RED_VECT(V) imageData[coord_gbr(V) + 2]

class Root {
public:
    explicit Root(IplImage*);
    virtual void search(IplImage*, float const &, int const &, Vect<float>);

    Vect<float> p;


protected:
    IplImage *frame;

};

#endif // ROOT_H
