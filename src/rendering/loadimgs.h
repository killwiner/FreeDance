/*************************************************************************/
/* This file is part of FreeDance.                                       */
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

#ifndef LOADIMGS_H
#define LOADIMGS_H

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <QString>
#include <QSharedPointer>

#define QSPVImage QSharedPointer< std::vector<cv::Mat> >

namespace rendering {

class LoadImgs
{
public:
    LoadImgs();
    ~LoadImgs();
    bool load_image(const QString &fileName);
    bool load_video(const QString &fileName);
    QSPVImage getImages() const;

private:
    QSPVImage PVImage;

    // make a vector from the video
    void make_vector(cv::VideoCapture &video);
};
}
#endif // LOADIMGS_H
