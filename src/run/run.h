#ifndef RUN_H
#define RUN_H

#include "../gameRender/gameRender.h"
#include "../sound/sound.h"
#include "menu.h"

namespace run {

class Run
{
public:
    Run(gameRender::GameRender *render);
    ~Run();
    void loop();

private:
    gameRender::GameRender *render_;
    Menu menu;
    sound::Sound Sd;

};
}

#endif // RUN_H
