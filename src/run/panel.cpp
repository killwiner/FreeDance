#include "panel.h"

namespace run {

Panel::Panel() {}

Panel::Panel(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions, const quint16 &id) : Box(render, Vtranslate,
             Vdimensions, .0f, 1.0f, id)
{
}

void Panel::run(const bool &activate) {

    if(activate) {
        if(alpha_ < .2f)
            alpha_ += .01f;
    }
    else {
        if(alpha_ > .0f)
            alpha_ -= .01f;
    }
    render_->setVAOAlpha(id_, alpha_);
}

}
