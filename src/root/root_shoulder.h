#ifndef ROOT_SHOULDER_H
#define ROOT_SHOULDER_H

#include "root.h"

namespace root {
    class Shoulder : public Root {
    public:
        explicit Shoulder(QSharedPointer<IplImage> const &, QSharedPointer<IplImage> &);
        void first_search(Vect<float> const &, Vect<float> const &, bool);
        void bone();
        void search(float const &, int const &, Vect<float>, Vect<float>, Vect<float>);
        void new_rot(Vect<float> const&, Vect<float> const&);

        std::vector< Vect <float> > vect_rot;

    private:
        Vect<float> vect_neck, neck_to_hips;
        float lenght_neck_shoulder;
        float init_angle;
        bool l_r;
    };
}
#endif // ROOT_SHOULDER_H
