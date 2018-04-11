#include "button.h"

namespace run {

Button::Button() {}

Button::Button(gameRender::GameRender *render, const QString &fileName, const maths::Vector<float> &Vtranslate) : render_(render), Vtrans(Vtranslate), alpha(.2f)
{
    render_->setStructVAO(1, maths::Vector<float>((float)BUTTON_RESOLUTION, (float)BUTTON_RESOLUTION, .0f, Vtranslate.get_espace()), alpha, 8.0f, Vtranslate);
    loadImage(fileName);
}

void Button::run(const maths::Vector<float> &VMouse) {

    if((float)VMouse.get_X() < Vtrans.get_X() + BUTTON_SIZE &&
       VMouse.get_X() > Vtrans.get_X() &&
       VMouse.get_Y() < Vtrans.get_Y() &&
       VMouse.get_Y() > Vtrans.get_Y() - BUTTON_SIZE) {
        if(alpha < 1.0f)
            alpha += .1f;
    }
    else {
        if(alpha > .2f)
            alpha -= .1f;
    }
    render_->setVAOAlpha(1, alpha);
}

void Button::loadImage(const QString &fileName) {

    rendering::LoadImgs image;
    try {
        std::cout << "file name : " << fileName.toStdString().c_str() << std::endl;
        if(!image.load_image(fileName))
            throw "(button.cpp) error, can't open the image";

        // render pointe sur l'image
        render_->setImages(image.getImages());
        // on crée les textures
        if(render_->loadTexture(GL_TEXTURE1, true))
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
