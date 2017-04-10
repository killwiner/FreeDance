TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x -Wextra

QT_VERSION = 5.8.0

# la première ligne est destinée à du 32 bits, erreur : moc: parse error "std"
INCLUDEPATH += /usr/include/i386-linux-gnu/c++/4.9/ \
/usr/local/include/opencv /usr/local/include/libfreenect

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_videoio \
-lopencv_imgcodecs \
-lfreenect
#-lopencv_ml \
#-lopencv_video \
#-lopencv_features2d \
#-lopencv_calib3d \
#-lopencv_objdetect \
#-lopencv_contrib \
#-lopencv_legacy \
#-lopencv_flann \

#LIBS += `pkg-config opencv --cflags --libs`
#LIBS += `pkg-config opencv --libs`
#LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_highgui
#LIBS += -lopencv_core -lopencv_highgui
#LIBS += -lopencv_imgproc -lopencv_highgui -lopencv_core

# QT += qml quick
QT += widgets core testlib opengl

DEFINES += TESTS
CONFIG += C++11

# pour valgrind
CONFIG += debug

SOURCES += main.cpp \
    maths/vectors.tpp \
    testsuite.cpp \
    maths/espace.cpp \
    maths/functions.tpp \
    rendering/render.cpp \
    maths/testsVector.cpp \
    rendering/testsRender.cpp \
    tests.cpp \
    rendering/testsOpenglRender.cpp \
    rendering/loadimgs.cpp \
    kinect/kinect.cpp \
    kinect/libfreenect.cpp \
    kinect/testsKinect.cpp \
    humanShape/humanShape.cpp \
    humanShape/testsHumanShape.cpp \
    draw/draw.cpp \
    draw/testsDraw.cpp \
    joints/joints.cpp \
    joints/testsJoints.cpp

# RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += maths/vectors.h \
    testsuite.h \
    maths/espace.h \
    maths/functions.h \
    rendering/render.h \
    maths/testsVector.h \
    rendering/testsRender.h \
    tests.h \
    rendering/testsOpenglRender.h \
    rendering/loadimgs.h \
    defines.h \
    kinect/kinect.h \
    kinect/libfreenect.h \
    kinect/testsKinect.h \
    humanShape/humanShape.h \
    freeQSPointer.h \
    humanShape/testsHumanShape.h \
    draw/draw.h \
    draw/testsDraw.h \
    joints/joints.h \
    joints/testsJoints.h
