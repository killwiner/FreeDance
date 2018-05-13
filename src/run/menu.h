#ifndef MENU_H
#define MENU_H

#include "options.h"

namespace run {

class Menu
{
public:
    Menu();
    ~Menu();
    Menu(gameRender::GameRender *render);
    void run();

private:
    MQSPEspace espace;
    maths::Vector<float> VMouse;
    gameRender::GameRender *render_;
    Options options;

    void initMouse();
    void loadImage(const QString &fileName);
};

}
#endif // MENU_H
