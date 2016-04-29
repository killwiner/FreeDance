#ifndef RUN_H
#define RUN_H

#include <QFileDialog>
#include <QMessageBox>
#include "render_window.h"
#include "skeleton.h"
#include "export_motion.h"
#include "search_human.h"

#define MENU_OPEN 0

class Run
{
public:
    explicit Run();
    ~Run();
    void load(QString const &fileName);
    bool save(QString fileName);
    void play();
    void stop();
    QWidget *getwidget();
    bool change_play_pause();
    void preview(int &, int &);
    void connect_kinect();
    bool run_kinect();
    void recordCapture();
    void memory_info(QString &, QString &, QString &);
    bool createSkeleton();

private:
    QSharedPointer<RenderWindow> SP_renderwindow; // pointer on the OpenGL window
    QSharedPointer<Skeleton> SP_skeleton; // pointer on the skeleton with roots
    Kinect *kinect; // the device for the kinect
    QSharedPointer<IO_frames> SP_saveload; // to save or load a motion

    cv::Mat mat_preview_after;
};

#endif // RUN_H
