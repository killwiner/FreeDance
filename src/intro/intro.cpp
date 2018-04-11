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
        if(render_->loadTexture(GL_TEXTURE0, false))
            throw "(intro.cpp) error, can't generate the texture";
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;
        throw;
    }
}

void Intro::video() {

    //when you allocate using new[] you need to call delete[], and not delete, to free the resource.
    MQSPEspace espace = MQSPEspace(new maths::Espace(200, 200, 200, 1000));
    render_->setStructVAO(0, maths::Vector<float>((float)WIN_WIDTH, (float)WIN_HEIGHT, .0f, espace), 1.0f, .5f, maths::Vector<float>(.0f, .0f, .0f, espace));

    render_->paintStatus(MOTION);
    render_->loop_paint(videoSize);
}

}
