#ifndef BEZIER_H
#define BEZIER_H

#include "maths_vect.h"
#include <vector>

void bezier_deg_3(Vect<float> &, Vect<float> &, Vect<float> &, Vect<float> &);
void bezier(std::vector< Vect<float> > &);

#endif // BEZIER_H
