#include "menu.h"

namespace run {

Menu::Menu() {}

Menu::Menu(gameRender::GameRender *render) : render_(render)
{
    espace = MQSPEspace(new maths::Espace(2.0f, 2.0f, .0f, 1000));
    options = Options(render);
    initMouse();
}

Menu::~Menu() {
}

void Menu::run() {

    maths::Vector<float> xy = render_->getMouseXY();
    //xy.set(xy.get_X(), xy.get_Y() - .1f, .0f);

    if(xy != VMouse) {
        VMouse = xy;
        render_->setMouseXY(xy);
    }
    options.run(xy, render_->mouseButton());
}

void Menu::initMouse() {
    MQSPEspace espace = MQSPEspace(new maths::Espace(200, 200, 200, 1000));
    render_->setStructVAO(maths::Vector<float>((float)128, (float)128, .0f, espace), 1.0f, 8.0f,
                          maths::Vector<float>(.0f, .0f, .8f, espace), MOUSEID);
    //render_->makeVertices(maths::Vector<float>(-1.0f, -1.0f, .8f, espace), 8.0f, (float)WIN_HEIGHT / (float)WIN_WIDTH);
    //render_->makeVao(2);
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
        if(render_->loadTexture(MOUSEID, true))
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
