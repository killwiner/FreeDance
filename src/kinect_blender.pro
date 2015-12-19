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
    save_load.cpp \
    skeleton.cpp \
    win_param.cpp \
    progress.cpp \
    vect.tpp \
    root.cpp \
    root_head.cpp \
    root_shoulder.cpp \
    root_elbow.cpp \
    vectors_maths/maths_vect.cpp \
    root_hips.cpp \
    vect.cpp \
    root_hand.cpp \
    root_neck.cpp \
    search_partitions.cpp \
    export_motion.cpp \
    kinect.cpp

HEADERS  += mainwindow.h \
    render.h \
    render_window.h \
    save_load.h \
    vect.h \
    skeleton.h \
    win_param.h \
    progress.h \
    win_size.h \
    root.h \
    root_head.h \
    root_shoulder.h \
    root_elbow.h \
    vectors_maths/maths_vect.h \
    root_hips.h \
    root_hand.h \
    root_neck.h \
    export_motion.h \
    kinect.h

FORMS    += mainwindow.ui
