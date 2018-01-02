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
        images = video.getImages();
        // Attention, une exception est levée si on touche à la dernière image
        images.data()->erase(images.data()->end() - 1);

        videoSize = images.data()->size();

        // on pointe sur le vecteur images
        render_->setImages(images);

        // on crée la texture du background
        if(render_->loadTexture(GL_TEXTURE0))
            throw "(intro.cpp) error, can't generate the texture";
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Intro::video() {
    render_->paintStatus(MOTION);
    render_->loop_paint(videoSize);
}

}
