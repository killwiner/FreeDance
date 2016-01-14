#ifndef ROOT_HIPS_H
#define ROOT_HIPS_H

#include "root.h"

namespace root {
    class Hips : public Root {
    public:
        explicit Hips(QSharedPointer<IplImage> const &, QSharedPointer<IplImage> &);
        void first_search();
        void search(float const &, int const &, Vect<float>);
        void new_rot(Vect<float> const &);

        Vect<float> s;
        std::vector< Vect <float> > vect_offset;
        std::vector< Vect <float> > vect_rot;

    private:
        Vect<float> init_offset;
    };
}
#endif // ROOT_HIPS_H
