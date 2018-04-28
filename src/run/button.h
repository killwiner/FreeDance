#ifndef BUTTON_H
#define BUTTON_H

#include "box.h"
#include "../rendering/loadimgs.h"

#define BUTTON_SIZE .1
#define BUTTON_RESOLUTION 128

namespace run {

class Button : public Box
{
public:
    Button();
    Button(gameRender::GameRender *render, const QString &fileName, const maths::Vector<float> &Vtranslate);
    Button(const QString &fileName);
    void run(const maths::Vector<float> &VMouse, const bool &bMouse);
    void loadImage(const QString &fileName);

private:
    bool buttonActivated;

};

}
#endif // BUTTON_H
