#ifndef BUTTON_H
#define BUTTON_H

#include "../gameRender/gameRender.h"
#include "../rendering/loadimgs.h"

namespace run {

class Button
{
public:
    Button();
    Button(gameRender::GameRender *render, const QString &fileName);
    void loadImage(const QString &fileName);

private:
    gameRender::GameRender *render_;

};

}
#endif // BUTTON_H
