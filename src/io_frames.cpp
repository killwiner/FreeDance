#include "io_frames.h"
#include <stdio.h>

using namespace std;

IO_frames::IO_frames() {
}

bool IO_frames::make_vector(int const &nbr_imgs, cv::VideoCapture &capture) {
    // for all images
    // pour toutes les images
    for(int i = 0; i < nbr_imgs; ++i) {

        // capture the next image
        // capture l'image suivante

        cv::Mat buffer_img;
        capture >> buffer_img;

        // clone the image
        mat_frame = buffer_img.clone();

        // turn colors from RGB to BGR
        // change les couleurs de RVB vers BVR
        cv::cvtColor(mat_frame, mat_frame, CV_RGB2BGR);

        // free the memory
        // libère la mémoire
        buffer_img.release();

        // we put the new image in the vector
        // nous mettons l'image dans le vecteur
        vect_imgs.push_back(mat_frame);
    }
    return true;
}

void IO_frames::load(const QString &fileName) {

    try {

        // read AVI video
        // capture la video à partir du fichier
        cv::VideoCapture capturevideo(fileName.toStdString().c_str());
        if (!capturevideo.isOpened())
            throw "(io_frames) error while opening file AVI.";

        // capture number of images from the video file
        // capture le nombre d'images dans le fichier video
        int nbr_imgs = (int) capturevideo.get(CV_CAP_PROP_FRAME_COUNT);

        // reset vect_imgs
        vector<cv::Mat>().swap(vect_imgs);
        vect_imgs.resize(0);

        if(!make_vector(nbr_imgs, capturevideo))
            throw "(io_frames) error, all images are not loaded.";

        // we finished with the video, release
        // on en a fini avec la video, libération
        capturevideo.release();
    }
    catch (const char& strException)
    {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }


}

// create an image from data and put this in the vector
// crée l'image à partir du data pour la mettre dans le vecteur
void IO_frames::push_data(char* data) {

    // create the image with the data
    // crée l'image avec les données
    cv::Mat buffer_img(HEIGHT, WIDTH, CV_8UC3, data);

    // clone the image to put this inside the vector
    // clone l'image pour l'introduire dans le vecteur
    mat_frame = buffer_img.clone();
    vect_imgs.push_back(mat_frame);

    buffer_img.release();
}

void IO_frames::save(std::vector< cv::Mat> &vect_motion, QString &fileName) {

    try {
        if(vect_motion.empty())
            throw "(io_frames) Can't save the file, empty video.\n";

        // create the size
        CvSize size;
        size.width = WIDTH;
        size.height = HEIGHT;

        cv::VideoWriter outputvideo(fileName.toStdString().c_str(), CV_FOURCC('I','Y','U','V'), 20, size);

        if(!outputvideo.isOpened())
            throw "(io_frames) Can't write in the file.\n";

        for (std::vector<cv::Mat>::iterator i = vect_motion.begin() ; i != vect_motion.end(); ++i) {
            mat_frame = *i;
            outputvideo << mat_frame;
        }

        outputvideo.release();

        // without avconv we got a core dump when we load the motion
        QString st0("avconv -y -i ");
        QString st1(" -vcodec mpeg4 -b 20000k -pass 1 ");
        QString st2(st0 + fileName + st1 + fileName);
        system(st2.toStdString().c_str());
    }
    catch (const char& strException)
    {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        throw;
    }

}
