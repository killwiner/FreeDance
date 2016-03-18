#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T11:51:53
#
#-------------------------------------------------

QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kinect_blender
TEMPLATE = app

LIBS += -lboost_system -lboost_filesystem -lfreenect -lusb-1.0 -lglut `pkg-config opencv --cflags --libs`# -lGL -lGLU -lglut
QMAKE_CXXFLAGS = -std=c++11

INCLUDEPATH += /usr/include/libusb-1.0

SOURCES += main.cpp\
        mainwindow.cpp \
    render.cpp \
    render_window.cpp \
    skeleton.cpp \
    win_param.cpp \
    progress.cpp \
    vect.tpp \
    root/root.cpp \
    root/root_head.cpp \
    root/root_shoulder.cpp \
    root/root_elbow.cpp \
    vectors_maths/maths_vect.cpp \
    root/root_hips.cpp \
    vect.cpp \
    root/root_hand.cpp \
    root/root_neck.cpp \
    export_motion.cpp \
    kinect.cpp \
    io_frames.cpp \
    search_human.cpp \
    draw.cpp

HEADERS  += mainwindow.h \
    render.h \
    render_window.h \
    vect.h \
    skeleton.h \
    win_param.h \
    progress.h \
    win_size.h \
    root/root.h \
    root/root_head.h \
    root/root_shoulder.h \
    root/root_elbow.h \
    vectors_maths/maths_vect.h \
    root/root_hips.h \
    root/root_hand.h \
    root/root_neck.h \
    export_motion.h \
    kinect.h \
    io_frames.h \
    search_human.h \
    draw.h

FORMS    += mainwindow.ui
