#include "thread.h"

TThread::TThread(QSharedPointer<Run> &SP_run_) : SP_run(SP_run_), l_s(TH_NONE)
{
}

void TThread::run() {
    switch(l_s) {
    case TH_LOAD:
        SP_run->load(file_name);
        break;
    case TH_SAVE:
        SP_run->save(file_name);
        break;
    case TH_CREATESKEL:
        SP_run->createSkeleton(progValue, filter_blue, filter_green, filter_red, nbr_pass);
        break;
    case TH_EXPORTBVH:
        SP_run->export_bvh(file_name);
        break;
    }
    l_s = TH_NONE;
}

void TThread::load(QString file_name_) {
    file_name = file_name_;
    l_s = TH_LOAD;
}

void TThread::save(QString file_name_) {
    file_name = file_name_;
    if(l_s != TH_EXPORTBVH)
        l_s = TH_SAVE;
}

void TThread::createSkeleton(float *progValue_, const int &filter_blue_, const int &filter_green_, const int &filter_red_, const int &nbr_pass_) {
    progValue = progValue_;
    filter_blue = filter_blue_;
    filter_green = filter_green_;
    filter_red = filter_red_;
    nbr_pass = nbr_pass_;
    l_s = TH_CREATESKEL;
}

void TThread::exportBVH() {
    l_s = TH_EXPORTBVH;
}
