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
        SP_run->createSkeleton(progValue, filter_blue, filter_green, filter_red, nbr_pass, smoth, escapeFrames);
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

void TThread::createSkeleton(float *progValue_, const int &filter_blue_, const int &filter_green_, const int &filter_red_, const int &nbr_pass_, const int &smoth_, const int &escapeFrames_) {
    progValue = progValue_;
    filter_blue = filter_blue_;
    filter_green = filter_green_;
    filter_red = filter_red_;
    nbr_pass = nbr_pass_;
    smoth = smoth_;
    escapeFrames = escapeFrames_;
    l_s = TH_CREATESKEL;
}

void TThread::exportBVH() {
    l_s = TH_EXPORTBVH;
}
