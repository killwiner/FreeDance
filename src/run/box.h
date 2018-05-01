#ifndef BOX_H
#define BOX_H

#include "../gameRender/gameRender.h"

namespace run {

class Box
{
public:
    Box();
    Box(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions, const float &alpha, const float &length);
    //virtual void run();

protected:
    gameRender::GameRender *render_;

    maths::Vector<float> Vtrans;
    float alpha_;

};

}
#endif // BOX_H
