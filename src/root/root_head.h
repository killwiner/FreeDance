#ifndef ROOT_HEAD_H
#define ROOT_HEAD_H

#include "root.h"
#include <vector>

namespace root {
    class Head : public Root {
    public:
        explicit Head(QSharedPointer<IplImage> const &, QSharedPointer<IplImage> &);
        Vect<float> first_search();
        void bone(Vect<float> const&);
        void new_rot(Vect<float> const&, Vect<float> const&);

        Vect<float> s;
        std::vector< Vect <float> > vect_rot;

    private:
        float lenght_head_neck;
        int m_lines = 8; // every m_lines lines, ch_y turn to true
    };
}
#endif // ROOT_HEAD_H
