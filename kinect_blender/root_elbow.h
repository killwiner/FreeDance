#ifndef ROOT_ELBOW_H
#define ROOT_ELBOW_H

#include "root.h"

class Elbow : public Root {
public:
    explicit Elbow();
    void first_search(Vect<float> shoulder, Vect<float> shoulder_to_hand);

};

#endif // ROOT_ELBOW_H
