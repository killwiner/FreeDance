#ifndef ROOT_HEAD_H
#define ROOT_HEAD_H

#include "root.h"

class Head : public Root {
public:
    explicit Head();
    void first_search(Vect<float> &);

};

#endif // ROOT_HEAD_H
