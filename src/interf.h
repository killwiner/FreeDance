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
    void sendToQml_npt(QString val);
    void sendToQml_fbt(QString val);
    void sendToQml_fgt(QString val);
    void sendToQml_nps(int val);
    void sendToQml_fbs(int val);
    void sendToQml_fgs(int val);
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
    Q_INVOKABLE void receiveFromQml_fbt(QString val);
    Q_INVOKABLE void receiveFromQml_fbs(int val);
    Q_INVOKABLE void receiveFromQml_fgt(QString val);
    Q_INVOKABLE void receiveFromQml_fgs(int val);
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
    void init_values(int, int, int, int);

private:
    QSharedPointer<Run> SP_run;
    TThread *th;
    int filter_blue, filter_green, nbr_pass;
    float *progValue;
    QMutex mutex;

public slots:
    void SLOT_loaded_saved();
};

#endif // INTERF_H
