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
    void sendToQml_fbt(QString val);
    void sendToQml_fbs(int val);
    void sendToQml_fgt(QString val);
    void sendToQml_fgs(int val);
    void sendToQml_play_pause(bool play_pause);
    void sendToQml_loaded_saved();
    void sendToQml_kinectOn();
    void sendToQml_message(QString val);

public:
    Q_INVOKABLE void receiveFromQml_fbt(QString val);
    Q_INVOKABLE void receiveFromQml_fbs(int val);
    Q_INVOKABLE void receiveFromQml_fgt(QString val);
    Q_INVOKABLE void receiveFromQml_fgs(int val);
    Q_INVOKABLE void receiveFromQml_loadFile(QString file_name);
    Q_INVOKABLE void receiveFromQml_saveFile(QString file_name);
    Q_INVOKABLE void receiveFromQml_play_pause();
    Q_INVOKABLE void receiveFromQml_preview();
    Q_INVOKABLE void receiveFromQml_connectKinect();

    void getrun(QSharedPointer<Run> &);
    void init_filters_values(int, int);

private:
    QSharedPointer<Run> SP_run;
    TThread *th;
    int filter_blue;
    int filter_green;

public slots:
    void SLOT_loaded_saved();
};

#endif // INTERF_H
