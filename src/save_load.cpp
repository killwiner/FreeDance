#include "save_load.h"
#include <stdio.h>

SaveLoad::SaveLoad() : capture(0) {
}

void SaveLoad::load(const QString &fileName) {

    capture = cvCaptureFromAVI(fileName.toStdString().c_str()); // read AVI video
    if( !capture ) {
        std::cerr << "Can't open the file.\n";
        return;
    }

    int nbr_imgs = (int) cvGetCaptureProperty( capture , CV_CAP_PROP_FRAME_COUNT );

    std::vector<QSharedPointer<IplImage> >().swap(vect_imgs);
    vect_imgs.resize(0);

    for(int i = 0; i < nbr_imgs; ++i) {

        IplImage *buffer_img;
        buffer_img = cvQueryFrame( capture );
        if(!buffer_img)
            break;

        SP_frame = QSharedPointer<IplImage>(cvCloneImage(buffer_img));
        cvCvtColor(SP_frame.data(), SP_frame.data(), CV_RGB2BGR);

        vect_imgs.push_back(SP_frame);
    }

    cvReleaseCapture(&capture);
    //cvReleaseImage(&frame);

}

void SaveLoad::make_list(char* data) {

    IplImage *buffer_img = cvCreateImageHeader(cvSize(WIDTH, HEIGHT), 8, 3);
    cvSetData(buffer_img, data, buffer_img->widthStep);

    SP_frame = QSharedPointer<IplImage>(cvCloneImage(buffer_img));
    vect_imgs.push_back(SP_frame);

    cvReleaseImageHeader(&buffer_img);
}

void SaveLoad::save(std::vector< QSharedPointer<IplImage> > &vect_motion) {

    if(vect_motion.empty()) {
        std::cerr << "Can't save the file, empty video.\n";
        return;
    }
    CvSize size;
    size.width = WIDTH;
    size.height = HEIGHT;

    boost::filesystem::path dir("tmp");
    boost::filesystem::create_directory(dir);
    CvVideoWriter *writer = cvCreateVideoWriter("tmp/kinect_video_1.avi", CV_FOURCC('I','Y','U','V'), 20, size);

    if(writer == NULL) {
        std::cerr << "Can't create the file.\n";
        return;
    }

    for (std::vector< QSharedPointer<IplImage> >::iterator i = vect_motion.begin() ; i != vect_motion.end(); ++i)
    {
        SP_frame = QSharedPointer<IplImage>(*i);
        cvWriteFrame(writer, SP_frame.data());
    }

    cvReleaseVideoWriter(&writer);

    // without avconv we got a core dump when we load the motion
    system("avconv -y -i tmp/kinect_video_1.avi -vcodec mpeg4 -b 20000k -pass 1 tmp/kinect_video_2.avi");

}
