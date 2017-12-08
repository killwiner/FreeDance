#ifndef INTRO_H
#define INTRO_H

#include "../gameRender/gameRender.h"
#include "../rendering/loadimgs.h"

namespace intro {

class Intro
{
public:
    Intro(gameRender::GameRender *render);
    void video();

private:
    gameRender::GameRender *render_;
};
}

#endif // INTRO_H
