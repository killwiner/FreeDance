TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x -Wextra

QT_VERSION = 5.8.0

MOC_DIR = "../bin"
OBJECTS_DIR = "../bin"
DESTDIR = "../bin"
TERGET = "FreeDance"

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
    kinect/testsKinectRender.cpp \
    armature/humanShape.cpp \
    armature/testsHumanShape.cpp \
    draw/draw.cpp \
    draw/testsDraw.cpp \
    armature/armature.cpp \
    shader/shader.cpp \
    shader/testsShader.cpp \
    shader/testsShaderRender.cpp \
    armature/thread.cpp

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
    kinect/kinect.h \
    kinect/libfreenect.h \
    kinect/testsKinect.h \
    kinect/testsKinectRender.h \
    armature/humanShape.h \
    freeQSPointer.h \
    armature/testsHumanShape.h \
    draw/draw.h \
    draw/testsDraw.h \
    armature/armature.h \
    shader/shader.h \
    shader/testsShader.h \
    shader/testsShaderRender.h \
    armature/thread.h
