#ifndef ROOT_HAND_H
#define ROOT_HAND_H

#include "root.h"

class Hand : public Root {
public:
    explicit Hand();
    void first_search(bool l_r);

};

#endif // ROOT_HAND_H
