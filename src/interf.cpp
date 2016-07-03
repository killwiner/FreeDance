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

#include "interf.h"
#include <QDebug>

using namespace std;

Interf::Interf() {
    progValue = new float(.0f);
    SP_run = QSharedPointer<Run>(new Run());
    th = new TThread(SP_run);
    QObject::connect(th, SIGNAL(finished()), this, SLOT(SLOT_loaded_saved()));
}

Interf::~Interf() {
    delete th;
    delete progValue;
}

QWidget *Interf::getwidget() {
    return SP_run->getwidget();
}

void Interf::receiveFromQml_smoth_t(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_smoth_s(val_i);
    smoth = val_i;
}

void Interf::receiveFromQml_escapeFt(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_escapeFs(val_i);
    escapeFrames = val_i;
}

void Interf::receiveFromQml_fbt(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_fbs(val_i);
    filter_blue = val_i;
}

void Interf::receiveFromQml_fgt(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_fgs(val_i);
    filter_green = val_i;
}

void Interf::receiveFromQml_frt(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_frs(val_i);
    filter_red = val_i;
}

void Interf::receiveFromQml_npt(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_nps(val_i);
    nbr_pass = val_i;
}

void Interf::getrun(QSharedPointer<Run> &r) {
        SP_run = r;
}

void Interf::receiveFromQml_smoth_s(int val) {
    sendToQml_smoth_t(QString::number(val));
    smoth = val;
}

void Interf::receiveFromQml_escapeFs(int val) {
    sendToQml_escapeFt(QString::number(val));
    escapeFrames = val;
}

void Interf::receiveFromQml_fbs(int val) {
    sendToQml_fbt(QString::number(val));
    filter_blue = val;
}

void Interf::receiveFromQml_fgs(int val) {
    sendToQml_fgt(QString::number(val));
    filter_green = val;
}

void Interf::receiveFromQml_frs(int val) {
    sendToQml_frt(QString::number(val));
    filter_red = val;
}

void Interf::receiveFromQml_nps(int val) {
    sendToQml_npt(QString::number(val));
    nbr_pass = val;
}


void Interf::receiveFromQml_loadFile(QString file_name) {
    th->load(file_name);
    th->start();
}

void Interf::receiveFromQml_saveFile(QString file_name) {
    th->save(file_name);
    th->start();
}

void Interf::receiveFromQml_play_pause() {
    SP_run->change_play_pause() ? sendToQml_play_pause(true) : sendToQml_play_pause(false);
}

void Interf::receiveFromQml_preview() {
    SP_run->preview(filter_green, filter_blue, filter_red);
}

void Interf::receiveFromQml_connectKinect() {
    try {
        SP_run->connect_kinect();
        sendToQml_kinectOn();
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        sendToQml_message(QString("Kinect is not connected"));
    }
}

void Interf::receiveFromQml_startCapture() {
    try {
        SP_run->run_kinect();
        sendToQml_stopWatch();
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
        sendToQml_message(QString("Kinect is not connected"));
    }
}

void Interf::receiveFromQml_recordCapture() {
    try {
        SP_run->recordCapture();
    }
    catch (const char* strException) {
        cerr << "Exception caught !!" << endl;
        cerr << strException << endl;
    }
}

void Interf::receiveFromQml_runKinect() {
    if(SP_run->run_kinect())
        sendToQml_message(QString("Kinect is not connected"));
}

void Interf::receiveFromQml_getMemInfo() {
    QString mem_total, mem_free, mem_ratio;
    SP_run->memory_info(mem_total, mem_free, mem_ratio);
    sendToQml_memInfo(mem_total, mem_free, mem_ratio);
}

void Interf::receiveFromQml_play() {
    SP_run->play();
}

void Interf::receiveFromQml_stop() {
    SP_run->stop();
}

void Interf::receiveFromQml_createSkeleton() {

    SP_run->stop();
    if(!SP_run->frames_present())
        sendToQml_message(QString("Load or get a motion first"));
    else {
        th->createSkeleton(progValue, filter_blue, filter_green, filter_red, nbr_pass, smoth, escapeFrames);
        th->start();
    }
}

void Interf::receiveFromQml_exportSkeleton() {
    if (!SP_run->isCreated()) {
        sendToQml_message(QString("Create the skeleton first"));
        return;
    }
    th->exportBVH();
    sendToQml_exportBVH();

}

void Interf::receiveFromQml_getProgress() {
    mutex.lock();
    sendToQml_progress(*progValue);
    mutex.unlock();

    if(th->isFinished())
        sendToQml_loaded_saved();

}

void Interf::SLOT_loaded_saved() {
    sendToQml_loaded_saved();
}

void Interf::init_values(int fb, int fg, int fr, int wt, int np, int s, int ef) {
    sendToQml_fbs(fb);
    sendToQml_fgs(fg);
    sendToQml_frs(fr);
    sendToQml_wts(wt);
    sendToQml_nps(np);
    sendToQml_smoth_s(s);
    sendToQml_escapeFs(ef);
    filter_blue = fb;
    filter_green = fg;
    filter_red = fr;
    smoth = s;
    escapeFrames = ef;
}

