#include "menu.h"

namespace run {

Menu::Menu() {}

Menu::Menu(gameRender::GameRender *render) : render_(render)
{
    Button b_options(render_, QString("../data/images/options.png"));
    initMouse();
}

void Menu::run() {

    maths::Vector<quint16> xy = render_->getMouseXY();

    if(xy != VMouse) {
        VMouse = xy;
        render_->setMouseXY(xy);
        std::cout << "mouse : " << xy.get_X() << " - " << xy.get_Y() << std::endl;
    }

}

void Menu::initMouse() {
    MQSPEspace espace = MQSPEspace(new maths::Espace(200, 200, 200, 1000));
    render_->makeVertices(maths::Vector<float>(-1.0f, -1.0f, .8f, espace), 8.0f, (float)WIN_HEIGHT / (float)WIN_WIDTH);
    render_->makeVao(2);
    loadImage(QString("../data/images/mouse.png"));
}

void Menu::loadImage(const QString &fileName) {

    rendering::LoadImgs image;
    try {
        std::cout << "file name : " << fileName.toStdString().c_str() << std::endl;
        if(!image.load_image(fileName))
            throw "(menu.cpp) error, can't open the image";

        // render pointe sur l'image
        render_->setImages(image.getImages());
        // on crée les textures
        if(render_->loadTexture(GL_TEXTURE2))
            throw "(menu.cpp) error, can't generate the texture";
        //render_->clearImages();
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}
}
