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

#ifndef INTERF_H
#define INTERF_H

#include <sstream>
#include <QObject>
#include "thread.h"

class Interf : public QObject
{
    Q_OBJECT

public:

    explicit Interf();
    ~Interf();
    QWidget *getwidget();

signals:
    void sendToQml_smoth_t(QString val);
    void sendToQml_escapeFt(QString val);
    void sendToQml_npt(QString val);
    void sendToQml_fbt(QString val);
    void sendToQml_fgt(QString val);
    void sendToQml_frt(QString val);
    void sendToQml_smoth_s(int val);
    void sendToQml_escapeFs(int val);
    void sendToQml_nps(int val);
    void sendToQml_fbs(int val);
    void sendToQml_fgs(int val);
    void sendToQml_frs(int val);
    void sendToQml_wts(int val);
    void sendToQml_play_pause(bool play_pause);
    void sendToQml_loaded_saved();
    void sendToQml_kinectOn();
    void sendToQml_message(QString val);
    void sendToQml_stopWatch();
    void sendToQml_memInfo(QString mem_total, QString mem_free, QString mem_ratio);
    void sendToQml_loadFile();
    void sendToQml_progress(float val);
    void sendToQml_exportBVH();

public:
    Q_INVOKABLE void receiveFromQml_smoth_t(QString val);
    Q_INVOKABLE void receiveFromQml_smoth_s(int val);
    Q_INVOKABLE void receiveFromQml_escapeFt(QString val);
    Q_INVOKABLE void receiveFromQml_escapeFs(int val);
    Q_INVOKABLE void receiveFromQml_fbt(QString val);
    Q_INVOKABLE void receiveFromQml_fbs(int val);
    Q_INVOKABLE void receiveFromQml_fgt(QString val);
    Q_INVOKABLE void receiveFromQml_fgs(int val);
    Q_INVOKABLE void receiveFromQml_frt(QString val);
    Q_INVOKABLE void receiveFromQml_frs(int val);
    Q_INVOKABLE void receiveFromQml_npt(QString val);
    Q_INVOKABLE void receiveFromQml_nps(int val);
    Q_INVOKABLE void receiveFromQml_loadFile(QString file_name);
    Q_INVOKABLE void receiveFromQml_saveFile(QString file_name);
    Q_INVOKABLE void receiveFromQml_play_pause();
    Q_INVOKABLE void receiveFromQml_preview();
    Q_INVOKABLE void receiveFromQml_connectKinect();
    Q_INVOKABLE void receiveFromQml_runKinect();
    Q_INVOKABLE void receiveFromQml_startCapture();
    Q_INVOKABLE void receiveFromQml_recordCapture();
    Q_INVOKABLE void receiveFromQml_getMemInfo();
    Q_INVOKABLE void receiveFromQml_play();
    Q_INVOKABLE void receiveFromQml_stop();
    Q_INVOKABLE void receiveFromQml_createSkeleton();
    Q_INVOKABLE void receiveFromQml_exportSkeleton();
    Q_INVOKABLE void receiveFromQml_getProgress();

    void getrun(QSharedPointer<Run> &);
    void init_values(int, int, int, int, int, int, int);

private:
    QSharedPointer<Run> SP_run;
    TThread *th;
    int filter_blue, filter_green, filter_red, nbr_pass, smoth, escapeFrames;
    float *progValue;
    QMutex mutex;

public slots:
    void SLOT_loaded_saved();
};

#endif // INTERF_H
