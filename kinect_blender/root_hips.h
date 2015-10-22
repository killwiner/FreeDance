#ifndef ROOT_HIPS_H
#define ROOT_HIPS_H

#include "root.h"

class Hips : public Root {
public:
    explicit Hips(IplImage*);
    void first_search();
    void search(IplImage *, float const &, int const &, Vect<float>);

    Vect<float> s;
};

#endif // ROOT_HIPS_H
