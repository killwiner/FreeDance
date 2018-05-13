#include "options.h"

namespace run {

Options::Options() {}

Options::Options(gameRender::GameRender *render) : render_(render), activated(false)
{
    espace = MQSPEspace(new maths::Espace(2.0f, 2.0f, .0f, 1000));
    maths::Vector<float> Vtranslate(1.8f, 1.8f, .4f, espace);
    b_options = Button(render_, QString("../data/images/options.png"), Vtranslate, OPTIONSBID);
    p_options = Panel(render_, maths::Vector<float>(.5f, .5f, .2f, espace), maths::Vector<float>(.2f, .2f, .0f, espace), OPTIONSPID);
}

void Options::run(const maths::Vector<float> &VMouse, const bool &bMouse) {
    p_options.run(b_options.run(VMouse, bMouse));
}

}
