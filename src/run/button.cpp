#include "button.h"

namespace run {

Button::Button() {}

Button::Button(gameRender::GameRender *render, const QString &fileName) : render_(render)
{
    MQSPEspace espace = MQSPEspace(new maths::Espace(200, 200, 200, 1000));
    render_->makeVertices(maths::Vector<float>(.7f, .7f, .4f, espace), .1f, (float)WIN_HEIGHT / (float)WIN_WIDTH);
    render_->makeVao(1);
    loadImage(fileName);
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
        if(render_->loadTexture(GL_TEXTURE1))
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
