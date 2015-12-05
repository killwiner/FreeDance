To build tron on Debian system (and Ubuntu)

    git clone https://github.com/killwiner/tron.git tron

    adduser $USER plugdev
    apt-get install git qt5-qmake qt5-default libboost-filesystem-dev \
            libav-tools freenect freeglut3-dev libusb-1.0-0-dev libopencv-dev

in ~/tron/kinect_blender :

    qmake
    make

If you get this error '/usr/bin/ld: cannot find -lGL' do :

    ln -s /usr/lib/libGL.so.xxx /usr/lib/libGL.so (replace xxx with the right version of course)

To build an open-kinect example :

    g++ -I /usr/include/libusb-1.0 -o cppview cppview.cpp -lfreenect -lusb-1.0 -l pthread -lGL -lGLU -lglut -lm
