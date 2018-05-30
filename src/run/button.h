#ifndef BUTTON_H
#define BUTTON_H

#include "box.h"
#include "../rendering/loadimgs.h"

#define BUTTON_HEIGHT 8.0f
//#define BUTTON_RESOLUTION 128

namespace run {

class Button : public Box
{
public:
    Button();
    Button(gameRender::GameRender *render, const QString &fileName, const maths::Vector<float> &Vsize, const maths::Vector<float> &Vtranslate, const quint16 &id);
    //Button(const QString &fileName);
    bool run(const maths::Vector<float> &VMouse, const bool &bMouse);
    void loadImage(const QString &fileName, const quint16 &id);

private:
    bool buttonActivated;

};

}
#endif // BUTTON_H
