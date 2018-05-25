#include "button.h"

namespace run {

Button::Button() {}

Button::Button(gameRender::GameRender *render, const QString &fileName, const maths::Vector<float> &Vtranslate, const quint16 &id) : Box(render, Vtranslate,
               maths::Vector<float>((float)BUTTON_RESOLUTION, (float)BUTTON_RESOLUTION, .0f, Vtranslate.get_espace()), .2f, 8.0f, id),
               buttonActivated(false)
{
    loadImage(fileName, id);
}

bool Button::run(const maths::Vector<float> &VMouse, const bool &bMouse) {

    if(!buttonActivated && (float)VMouse.get_X() < Vtrans.get_X() + BUTTON_SIZE &&
       VMouse.get_X() > Vtrans.get_X() &&
       VMouse.get_Y() < Vtrans.get_Y() &&
       VMouse.get_Y() > Vtrans.get_Y() - BUTTON_SIZE) {
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
        std::cout << "file name : " << fileName.toStdString().c_str() << std::endl;
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
