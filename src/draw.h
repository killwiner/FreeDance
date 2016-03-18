#ifndef DRAW_H
#define DRAW_H

#include <QSharedPointer>
#include <opencv2/opencv.hpp>
#include "vectors_maths/maths_vect.h"
#include "root/root.h"

void draw_square(const int &, const int &, const int &, QSharedPointer<cv::Mat> &);

#endif // DRAW_H
