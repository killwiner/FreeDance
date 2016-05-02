TEMPLATE = app

LIBS += -lboost_system -lboost_filesystem -lfreenect -lusb-1.0 -lglut `pkg-config opencv --cflags --libs`
QMAKE_CXXFLAGS = -std=c++11
INCLUDEPATH += /usr/include/libusb-1.0

QT += qml quick widgets core gui
QT += opengl

SOURCES += main.cpp \
    interf.cpp \
    render.cpp \
    render_window.cpp \
    kinect.cpp \
    io_frames.cpp \
    skeleton.cpp \
    root/root.cpp \
    root/root_head.cpp \
    root/root_shoulder.cpp \
    root/root_elbow.cpp \
    root/root_hips.cpp \
    root/root_hand.cpp \
    root/root_neck.cpp \
    vectors_maths/maths_vect.cpp \
    vectors_maths/bezier.cpp \
    vect.tpp \
    vect.cpp \
    search_human.cpp \
    draw.cpp \
    run.cpp \
    export_motion.cpp \
    thread.cpp \
    win.cpp
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    interf.h \
    render.h \
    render_window.h \
    kinect.h \
    win_size.h \
    io_frames.h \
    skeleton.h \
    root/root.h \
    root/root_head.h \
    root/root_shoulder.h \
    root/root_elbow.h \
    root/root_hips.h \
    root/root_hand.h \
    root/root_neck.h \
    vectors_maths/maths_vect.h \
    vectors_maths/bezier.h \
    vect.h \
    search_human.h \
    draw.h \
    run.h \
    export_motion.h \
    bvh.h \
    thread.h \
    win.h

FORMS    += mainwindow.ui
