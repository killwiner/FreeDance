#include "panel.h"

namespace run {

Panel::Panel() {}

Panel::Panel(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions, const quint16 &id) : Box(render, Vtranslate,
             Vdimensions, .0f, 1.0f, id)
{
    espace = MQSPEspace(new maths::Espace(2.0f, 2.0f, .0f, 1000));
    maths::Vector<float> VtranslateB(1.f, 1.f, .4f, espace);
    maths::Vector<float> VsizeB(244.f, 64.f, .4f, espace);
    b_screenMode = Button(render_, QString("../data/images/buttonScreenMode.png"), VsizeB, VtranslateB, SCREENBID, false);
}

void Panel::run(const bool &activate, const maths::Vector<float> &VMouse, const bool &bMouse) {

    if(activate) {
        if(alpha_ < .2f)
            alpha_ += .01f;
    }
    else {
        if(alpha_ > .0f)
            alpha_ -= .01f;
    }
    render_->setVAOAlpha(id_, alpha_);

    b_screenMode.run(VMouse, bMouse);

}

}
