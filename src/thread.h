#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "run.h"

class TThread : public QThread
{

public:
    explicit TThread(QSharedPointer<Run> &);
    void load(QString);
    void save(QString);
    void run();
private:
    QString file_name;
    QSharedPointer<Run> SP_run;
    bool l_s;
};

#endif // THREAD_H
