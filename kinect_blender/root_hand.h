#ifndef ROOT_HAND_H
#define ROOT_HAND_H

#include "root.h"

class Hand : public Root {
public:
    explicit Hand(IplImage*);
    void first_search(bool l_r);
    void z_axis(float const&);
    void search(IplImage *, float const &, int const &, Vect<float>, Vect<float> elbow);

    Vect<float> s;
};

inline void Hand::z_axis(const float &z) {
    p.z = z;
}

#endif // ROOT_HAND_H
