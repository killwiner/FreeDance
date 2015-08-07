#include "save_load.h"
#include <stdio.h>

SaveLoad::SaveLoad() : capture(0), frame(0){
}

void SaveLoad::load() {

    capture = cvCaptureFromAVI("tmp/kinect_video_2.avi"); // read AVI video
    if( !capture ) {
        std::cerr << "Can't open the file.\n";
        return;
    }

    int nbr_imgs = (int) cvGetCaptureProperty( capture , CV_CAP_PROP_FRAME_COUNT );

    std::vector<IplImage>().swap(vect_imgs);
    vect_imgs.resize(0);

    for(int i = 0; i < nbr_imgs; ++i) {

        IplImage *buffer_img;
        buffer_img = cvQueryFrame( capture );
        if(!buffer_img)
            break;

        frame  = cvCloneImage(buffer_img);
        cvCvtColor(frame, frame, CV_RGB2BGR);

        vect_imgs.push_back(*frame);
    }

    cvReleaseCapture(&capture);
    //cvReleaseImage(&frame);

}

void SaveLoad::make_list(char* data) {

    IplImage *buffer_img = cvCreateImageHeader(cvSize(WIDTH, HEIGHT), 8, 3);
    cvSetData(buffer_img, data, buffer_img->widthStep);

    frame  = cvCloneImage(buffer_img);
    vect_imgs.push_back(*frame);

    cvReleaseImageHeader(&buffer_img);
}

void SaveLoad::save() {

    if(vect_imgs.empty()) {
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

    for (std::vector<IplImage>::iterator i = vect_imgs.begin() ; i != vect_imgs.end(); ++i)
    {
        frame = &(*i);
        cvWriteFrame(writer, &(*i));
    }

    cvReleaseVideoWriter(&writer);

    // without avconv we got a core dump when we load the motion
    system("avconv -y -i tmp/kinect_video_1.avi -vcodec mpeg4 -b 20000k -pass 1 tmp/kinect_video_2.avi");

}
