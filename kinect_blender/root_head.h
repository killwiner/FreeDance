#ifndef ROOT_HEAD_H
#define ROOT_HEAD_H

#include "root.h"

class Head : public Root {
public:
    explicit Head(IplImage*);
    Vect<float> first_search();
    void bone(Vect<float> const&);

private:
    float lenght_head_neck;
};

#endif // ROOT_HEAD_H
