#ifndef PANEL_H
#define PANEL_H

#include "box.h"

namespace run {

class Panel : public Box
{
public:
    Panel();
    Panel(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions);
};

}

#endif // PANEL_H
