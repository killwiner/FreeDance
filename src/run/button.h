#ifndef BUTTON_H
#define BUTTON_H

#include "../gameRender/gameRender.h"
#include "../rendering/loadimgs.h"

#define BUTTON_SIZE .1
#define BUTTON_RESOLUTION 128

namespace run {

class Button
{
public:
    Button();
    Button(gameRender::GameRender *render, const QString &fileName, const maths::Vector<float> &Vtranslate);
    void run(const maths::Vector<float> &VMouse);
    void loadImage(const QString &fileName);

private:
    gameRender::GameRender *render_;

    maths::Vector<float> Vtrans;
    float alpha;

};

}
#endif // BUTTON_H
