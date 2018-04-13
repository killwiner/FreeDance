A clone of Justdance for the Open Source projects.

***************** To Build the project ***************

--- Build opencv-3.2.0 ---

$ apt-get install build-essential gcc cmake subversion mesa-common-dev libgtk2.0-dev pkg-config libpng-dev libjpeg-dev libtiff5-dev libjasper-dev python-dev libavformat-dev libdc1394-22-dev libgtk2.0-dev libcv-dev libcvaux-dev
$ mkdir build
$ cd build
$ cmake -D WITH_OPENGL=ON -D WITH_QT=OFF -DENABLE_PRECOMPILED_HEADERS=OFF ..
$ make -j 2
$ make install
$ ldconfig

--- Install OpenAL ---
$ apt-get install libopenal-dev libalut-dev libvorbis-dev

--- Build freenect ---

& git clone https://github.com/OpenKinect/libfreenect

$ apt-get install libusb-1.0-0.dev libxi-dev libxmu-dev freeglut3-dev
$ mkdir build
$ cd build
$ cmake ..
$ make

    // Architecture 64 bits : si problème avec libGL.so, renommer provisoirement libGL.so.1 en libGL.so

$ sudo make install
$ sudo ldconfig /usr/local/lib

    // tester en root : //

    $ /usr/local/bin/freenect-glview

$ vim /etc/udev/rules.d/66-kinect.rules

    # ATTR{product}=="Xbox NUI Motor"
    SUBSYSTEM=="usb", ATTR{idVendor}=="045e", ATTR{idProduct}=="02b0", MODE="0666"
    # ATTR{product}=="Xbox NUI Audio"
    SUBSYSTEM=="usb", ATTR{idVendor}=="045e", ATTR{idProduct}=="02ad", MODE="0666"
    # ATTR{product}=="Xbox NUI Camera"
    SUBSYSTEM=="usb", ATTR{idVendor}=="045e", ATTR{idProduct}=="02ae", MODE="0666"
    # ATTR{product}=="Xbox NUI Motor"
    SUBSYSTEM=="usb", ATTR{idVendor}=="045e", ATTR{idProduct}=="02c2", MODE="0666"
    # ATTR{product}=="Xbox NUI Motor"
    SUBSYSTEM=="usb", ATTR{idVendor}=="045e", ATTR{idProduct}=="02be", MODE="0666"
    # ATTR{product}=="Xbox NUI Motor"
    SUBSYSTEM=="usb", ATTR{idVendor}=="045e", ATTR{idProduct}=="02bf", MODE="0666"

$ adduser USER_NAME video

--- Install QT ---

Install Qt 5.8 in the local path with the bin installer.

https://www.qt.io/developers

--- Build tron ---

$ apt-get install qt5-qmake qt5-default qtdeclarative5-dev
$ cd src
$ (the right local path)/qmake
$ make in ../bin

***************** Tools to work on the project ******************

--- colored QTest ---
$ apt-get install python-termcolor
$ ./tron | python qtest.py

--- memcheck with valgrind ---

$ vim ~/.valgrindrc

    --memcheck:leak-check=full
    --show-reachable=yes
    --suppressions=/home/blabla/errors.supp

    /// Ignorer les erreures externes au codes ///

    $ valgrind -v --gen-suppressions=all --log-file=logs --error-limit=no ./tron

--- Massif ---

Massif est un sous-outil pour Valgrind, permettant de surveiller les usages de la pile du programme.
Il faut ignorer les allocations de mémoire Qt (qMalloc…).

$ valgrind --tool=massif --alloc-fn='qMalloc()' ./tron

    /// Massif-Visualizer ///
    apt-get massif-visualizer, que sous testing, non disponible en stable :-(

--- git_crypt, init ---

$ vim tron/.gitattributes

    src/kinect/*.cpp filter=git-crypt diff=git-crypt
    src/armature/*.cpp filter=git-crypt diff=git-crypt
    src/kinect/*.h filter=git-crypt diff=git-crypt
    src/armature/*.h filter=git-crypt diff=git-crypt

$ git-crypt keygen /path/to/keyfile # génère une clé de cryptage
$ git-crypt status # affiche la liste des fichiers chiffrés et non chiffrés
$ cd tron
$ git-crypt unlock /path/to/keyfile # pour chiffrer après le commit, le faire q'une seule fois

Pour cloner et déchiffrer :

$ git clone /path/to/repo
$ cd repo
$ git-crypt unlock /path/to/keyfile
