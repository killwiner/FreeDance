#ifndef ROOT_SHOULDER_H
#define ROOT_SHOULDER_H

#include "root.h"

class Shoulder : public Root {
public:
    explicit Shoulder();
    void first_search(Vect<float>, Vect<float>, bool );

};

#endif // ROOT_SHOULDER_H
