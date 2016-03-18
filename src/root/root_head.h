#ifndef ROOT_HEAD_H
#define ROOT_HEAD_H

#include "root.h"
#include <vector>

namespace root {
    class Head : public Root {
    public:
        explicit Head(cv::Mat const &, QSharedPointer<cv::Mat> &);
        Vect<float> first_search();
        void bone(Vect<float> const&);
        void new_rot(Vect<float> const&, Vect<float> const&);

        Vect<float> s;
        std::vector< Vect <float> > vect_rot;

    private:
        bool web(Vect<float> &, float &, float const &, float const &, float &, float &, Vect<float> &, float const &, Vect<float> &, Vect<float> &, Vect<float> &);
        bool every_m_lines(Vect<float> &, float &, float const &, float &, float &, bool const &, bool &, Vect<float> &, Vect<float> &, float const &, float const &,
                           float &, float &, Vect<float> &, float &, Vect<float> &);
        void along_line(bool const &, bool &, float &, Vect<float> &, float const &, float &, float &,
                        Vect<float> &, float &, Vect<float> &, float &, float &);
        bool search_from_up_to_down(Vect<float> &neck);

        float lenght_head_neck;
        int m_lines; // every m_lines lines, ch_y turn to true
    };
}
#endif // ROOT_HEAD_H
