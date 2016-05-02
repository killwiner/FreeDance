#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "run.h"

enum {
    TH_NONE,
    TH_LOAD,
    TH_SAVE,
    TH_CREATESKEL,
    TH_EXPORTBVH
};

class TThread : public QThread
{

public:
    explicit TThread(QSharedPointer<Run> &);
    void load(QString);
    void save(QString);
    void createSkeleton(float *, const int &, const int &, const int &);
    void exportBVH();
    void run();
private:
    QString file_name;
    QSharedPointer<Run> SP_run;
    int l_s;
    int filter_blue, filter_green, nbr_pass;
    float *progValue;
};

#endif // THREAD_H
