#ifndef PANEL_H
#define PANEL_H

#include "box.h"
#include "button.h"
#include "../gameRender/gameRender.h"

namespace run {

class Panel : public Box
{
public:
    Panel();
    Panel(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions, const quint16 &id);
    void run(const bool &activate, const maths::Vector<float> &VMouse, const bool &bMouse);

private:
    Button b_screenMode;
    MQSPEspace espace;

};

}

#endif // PANEL_H
