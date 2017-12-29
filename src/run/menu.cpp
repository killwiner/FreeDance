#include "menu.h"

namespace run {

Menu::Menu() {}

Menu::Menu(gameRender::GameRender *render) : render_(render)
{
    loadImage();
}

void Menu::loadImage() {
    rendering::LoadImgs image;
    try {
        if(!image.load_image("../data/images/options.png"))
            throw "(menu.cpp) error, can't open the image";

        // render pointe sur l'image
        render_->setImages(image.getImages());
        // on crée les textures
        if(render_->loadTextures())
            throw "(intro.cpp) error, can't generate textures";
        render_->clearImages();
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Menu::run() {

    maths::Vector<quint16> xy = render_->getMouseXY();

    if(xy != VMouse) {
        VMouse = xy;
        std::cout << "mouse : " << xy.get_X() << " - " << xy.get_Y() << std::endl;
    }

}
}
