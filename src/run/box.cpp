#include "box.h"

namespace run {

Box::Box() {}

Box::Box(gameRender::GameRender *render, const maths::Vector<float> &Vtranslate, const maths::Vector<float> &Vdimensions, const float &alpha,
		const float &length) : render_(render), Vtrans(Vtranslate), alpha_(alpha)
{
    render_->setStructVAO(Vdimensions, alpha, length, Vtranslate);
}

//void run() {};

}
