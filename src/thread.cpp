#include "thread.h"

TThread::TThread(QSharedPointer<Run> &SP_run_) : SP_run(SP_run_)
{
}

void TThread::run() {
    if(l_s)
        SP_run->save(file_name);
    else
        SP_run->load(file_name);
}

void TThread::load(QString file_name_) {
    file_name = file_name_;
    l_s = false;
}

void TThread::save(QString file_name_) {
    file_name = file_name_;
    l_s = true;
}
