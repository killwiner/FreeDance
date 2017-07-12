#include "loadimgs.h"

namespace rendering {

LoadImgs::LoadImgs() {
}

LoadImgs::~LoadImgs() {
    PVImage.clear();
}

bool LoadImgs::load_image(const QString &fileName) {

    PVImage = QSPVImage(new std::vector<cv::Mat>);
    PVImage.data()->push_back(cv::imread(fileName.toStdString().c_str(), CV_LOAD_IMAGE_COLOR));

    if(!PVImage->data())
        return false;

    // turn colors in right order RGB to BGR
    cv::cvtColor(PVImage.data()->back(), PVImage.data()->back(), cv::COLOR_RGB2BGR );

    return true;
}

bool LoadImgs::load_video(const QString &fileName) {

    // read AVI video
    // capture la video à partir du fichier
    cv::VideoCapture capturevideo(fileName.toStdString().c_str());

    if (!capturevideo.isOpened())
        return false;

    make_vector(capturevideo);
    capturevideo.release();

    return true;
}

void LoadImgs::make_vector(cv::VideoCapture &video) {

    cv::Mat buffer_image;
    PVImage = QSPVImage(new std::vector<cv::Mat>);

    // capture number of images from the video file and loop to convert video into a vector of images
    // capture le nombre d'images dans le fichier video et boucle la convertion de la video en un vecteur d'images
    double nbr_imgs = video.get(CV_CAP_PROP_FRAME_COUNT);

    for(quint64 i = 0; i < nbr_imgs; ++i) {

        // capture the next image
        // capture l'image suivante
        video >> buffer_image;

        // turn colors from RGB to BGR
        // change les couleurs de RVB vers BVR
        cv::cvtColor(buffer_image, buffer_image, CV_RGB2BGR);

        // we put the new image in the vector
        // nous mettons l'image dans le vecteur
        PVImage.data()->push_back(buffer_image.clone());
    }
}

QSPVImage LoadImgs::getImages() const {
    return PVImage;
}
}
