#include "intro.h"

namespace intro {

Intro::Intro(gameRender::GameRender *render) : render_(render) {

    loadVideo();

}

void Intro::loadVideo() {

    rendering::LoadImgs video;
    try {
        if(!video.load_video("../data/videos/intro.avi"))
            throw "(intro.cpp) error, can't open the video";
        // on capture toutes les images de la vidéo
        QSPVImage images = video.getImages();
        // Attention, une exception est levée si on touche à la dernière image
        images.data()->erase(images.data()->end() - 1);

        videoSize = images.data()->size();

        // on pointe sur le vecteur images
        render_->setImages(images);
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

void Intro::video() {
        render_->load();
        render_->loop_paint(videoSize - 1);
}

}
