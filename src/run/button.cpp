#include "button.h"

namespace run {

Button::Button() {}

Button::Button(gameRender::GameRender *render, const QString &fileName, const maths::Vector<float> &Vsize,
               const maths::Vector<float> &Vtranslate, const quint16 &id, const bool &alpCh) : Box(render, Vtranslate,
               Vsize, .2f, BUTTON_LENGTH, id),
               buttonActivated(false), alpCh_(alpCh)
{
    loadImage(fileName, id);
}

bool Button::run(const maths::Vector<float> &VMouse, const bool &bMouse) {

    float ratio = (Vsize_.get_Y() * WIN_WIDTH) / (Vsize_.get_X() * WIN_HEIGHT);

    if (!alpCh_) {

        if(alpha_ < 1.0f)
            alpha_ += .1f;

        render_->setVAOAlpha(id_, alpha_);

        if(bMouse)
            if(!buttonActivated && (float)VMouse.get_X() < Vtrans.get_X() + (1.0f / (BUTTON_HEIGHT * ratio)) &&
                    VMouse.get_X() > Vtrans.get_X() &&
                    VMouse.get_Y() < Vtrans.get_Y() + (1.0f / BUTTON_HEIGHT) - .1f &&
                    VMouse.get_Y() > Vtrans.get_Y() - .1f)
                render_->m_boolButton(id_);

        return false;
    }

    if(!buttonActivated && (float)VMouse.get_X() < Vtrans.get_X() + (1.0f / (BUTTON_HEIGHT * ratio)) &&
            VMouse.get_X() > Vtrans.get_X() &&
            VMouse.get_Y() < Vtrans.get_Y() + (1.0f / BUTTON_HEIGHT) - .1f &&
            VMouse.get_Y() > Vtrans.get_Y() - .1f) {

        if(alpha_ < 1.0f)
            alpha_ += .1f;
        if(bMouse)
            buttonActivated = true;
    }
    else {
        if(alpha_ > .2f)
            alpha_ -= .1f;
    }
    render_->setVAOAlpha(id_, alpha_);
    return buttonActivated;
}

void Button::loadImage(const QString &fileName, const quint16 &id) {

    rendering::LoadImgs image;
    try {
        if(!image.load_image(fileName))
            throw "(button.cpp) error, can't open the image";

        // render pointe sur l'image
        render_->setImages(image.getImages());
        // on crée les textures
        if(render_->loadTexture(id, true))
            throw "(button.cpp) error, can't generate the texture";
        //render_->clearImages();
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

}
