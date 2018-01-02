#ifndef MENU_H
#define MENU_H

#include "button.h"

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

    void initMouse();
    void loadImage(const QString &fileName);
};

}
#endif // MENU_H
