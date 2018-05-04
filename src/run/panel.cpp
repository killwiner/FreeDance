#include "panel.h"

namespace run {

Panel::Panel() {}

Panel::Panel(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions) : Box(render, Vtranslate,
             Vdimensions, .2, 1.0f)
{
    render_->loadShader(QString("../data/shaders/shaderPanel"));
}

}
