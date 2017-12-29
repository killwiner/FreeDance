#ifndef RUN_H
#define RUN_H

#include "../gameRender/gameRender.h"
#include "menu.h"

namespace run {

class Run
{
public:
    Run(gameRender::GameRender *render);
    void loop();

private:
    gameRender::GameRender *render_;
    Menu menu;
};
}

#endif // RUN_H
