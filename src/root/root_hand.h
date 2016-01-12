#ifndef ROOT_HAND_H
#define ROOT_HAND_H

#include "root.h"

namespace root {
    class Hand : public Root {
    public:
        explicit Hand(QSharedPointer<IplImage> const &);
        void first_search(bool l_r, Vect<float>, Vect<float>);
        void z_axis(float const&);
        void search(float const &, int const &, Vect<float>, Vect<float> elbow);
        void new_rot(Vect<float> const&, Vect<float> const&);

        std::vector< Vect <float> > vect_rot;

        Vect<float> s;

    private:
        float init_angle_x_y, init_angle_y_z;
    };

    inline void Hand::z_axis(const float &z) {
        p.z = z;
    }
}
#endif // ROOT_HAND_H
