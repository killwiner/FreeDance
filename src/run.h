/*************************************************************************/
/* This file is part of Tron.                                            */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

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
    void preview(int &, int &, int &);
    void connect_kinect();
    bool run_kinect();
    void recordCapture();
    void memory_info(QString &, QString &, QString &);
    void createSkeleton(float *, const int&, const int&, const int&, const int&, const int&, const int&);
    bool isCreated();
    bool export_bvh(QString);
    bool frames_present();

private:
    QSharedPointer<RenderWindow> SP_renderwindow; // pointer on the OpenGL window
    QSharedPointer<Skeleton> SP_skeleton; // pointer on the skeleton with roots
    Kinect *kinect; // the device for the kinect
    QSharedPointer<IO_frames> SP_saveload; // to save or load a motion
    bool fram_present;
    cv::Mat mat_preview_after;
};

#endif // RUN_H
