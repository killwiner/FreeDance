#ifndef MENU_H
#define MENU_H

#include "../gameRender/gameRender.h"
#include "../rendering/loadimgs.h"

namespace run {

class Menu
{
public:
    Menu();
    Menu(gameRender::GameRender *render);
    void run();

private:
    maths::Vector<quint16> VMouse;
    gameRender::GameRender *render_;
    void loadImage();
};

}
#endif // MENU_H
