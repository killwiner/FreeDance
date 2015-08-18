sudo adduser $USER plugdev
apt-get install libboost-filesystem-dev libav-tools freenect freeglut3-dev libusb-1.0-0-dev libopencv-deb

to build an open-kinect example :
g++ -I /usr/include/libusb-1.0 -o cppview cppview.cpp -lfreenect -lusb-1.0 -l pthread -lGL -lGLU -lglut -lm
