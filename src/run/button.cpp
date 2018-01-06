#include "button.h"

namespace run {

Button::Button() {}

Button::Button(gameRender::GameRender *render, const QString &fileName) : render_(render)
{
    MQSPEspace espace = MQSPEspace(new maths::Espace(200, 200, 200, 1000));
    render_->setStructVAO(1, maths::Vector<float>((float)128, (float)128, .0f, espace), .2f, 8.0f, maths::Vector<float>(1.8f, 1.8f, .4f, espace));
//    render_->makeVertices(maths::Vector<float>(.7f, .7f, .4f, espace), .1f, (float)WIN_HEIGHT / (float)WIN_WIDTH);
    //render_->makeVertices(maths::Vector<float>(-1.0f, -1.0f, .4f, espace), 8.0f, (float)WIN_HEIGHT / (float)WIN_WIDTH);

    //render_->makeVao(1);
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
