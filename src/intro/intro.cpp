#include "intro.h"

namespace intro {

Intro::Intro(gameRender::GameRender *render) : render_(render) {
}

void Intro::video() {

    rendering::LoadImgs video;
    try {
    if(!video.load_video("../data/videos/intro.avi"))
        throw "(intro.cpp) error, can't open the video";
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
    // on capture toutes les images de la vidéo
    QSPVImage images = video.getImages();
    // on pointe sur le vecteur images
    render_->setImages(images);
    // load the shader
    render_->load();
    // Attention, une exception est levée si on touche à la dernière image
    render_->loop_paint(video.getImages()->size() - 1);
}

}
