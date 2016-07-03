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
    void createSkeleton(float *, const int &, const int &, const int &, const int &, const int &, const int &);
    void exportBVH();
    void run();
private:
    QString file_name;
    QSharedPointer<Run> SP_run;
    int l_s;
    int filter_blue, filter_green, filter_red, nbr_pass, smoth, escapeFrames;
    float *progValue;
};

#endif // THREAD_H
