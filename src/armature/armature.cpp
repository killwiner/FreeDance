#ifndef ARMATURE_CPP
#define ARMATURE_CPP

#include "armature.h"

namespace armature {

Armature::Armature(cv::Mat *Image, cv::Mat_<quint16> *idObjects): Image_(Image), idObjects_(idObjects) {}

}

#endif // ARMATURE_H
