#ifndef ROOT_SHOULDER_H
#define ROOT_SHOULDER_H

#include "root.h"

class Shoulder : public Root {
public:
    explicit Shoulder(IplImage*);
    void first_search(Vect<float> const &, Vect<float> const &, bool);
    void bone();

private:
    Vect<float> vect_neck, neck_to_hips;
    float lenght_neck_shoulder;
};

#endif // ROOT_SHOULDER_H
