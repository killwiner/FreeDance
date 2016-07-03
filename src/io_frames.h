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

#ifndef IO_FRAMES_H
#define IO_FRAMES_H

#include <opencv2/opencv.hpp>
#include <vector>
//#include <boost/filesystem.hpp>
#include <QFileDialog>
#include "win_size.h"
#include <QString>
#include <QSharedPointer>

class IO_frames
{

public:
    explicit IO_frames();
    void load(const QString &fileName);
    void save(std::vector< cv::Mat > &, QString &);
    void push_data(char*); // make a vector from data
    cv::VideoCapture open_input(const QString &);
    int get_nbr_imgs();
    bool loaded();

    std::vector< cv::Mat > vect_imgs;

private:
    int nbr_imgs;
    cv::Mat mat_frame;
    bool make_vector(int const &, cv::VideoCapture &);
    bool video_loaded;
};

#endif // IO_FRAMES_H
