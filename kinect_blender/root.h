#ifndef ROOT_H
#define ROOT_H

#include "vect.h"
#include "maths_vect.h"
#include <opencv2/opencv.hpp>

class Root {
public:
    explicit Root() {};
    Root(IplImage *);
    virtual void first_search();
    virtual void search(int, float);

    Vect<float> p;
    int radius;

protected:
    IplImage *frame;

};

typedef struct s_bone {
    Root root0, root1;
    float lenght;
} SBone;

#endif // ROOT_H
