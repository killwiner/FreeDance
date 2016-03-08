#ifndef ROOT_HIPS_H
#define ROOT_HIPS_H

#include "root.h"

namespace root {
    class Hips : public Root {
    public:
        explicit Hips(cv::Mat const &, cv::Mat &);
        void first_search();
        void search(float const &, int const &, Vect<float>);
        void new_rot(Vect<float> const &);

        Vect<float> s;
        std::vector< Vect <float> > vect_offset;
        std::vector< Vect <float> > vect_rot;

    private:
        void first_pixel_l2r(int &);
        void first_pixel_r2l(int &);
        bool x_l_move_to_x_r(int const &, int &, int const &);
        bool x_r_move_to_x_l(int const &, int &, int const &);
        int along_lenght(int &, int &);
        void all_rays(int const &, float &, float &, float const &);
        Vect<float> init_offset;
    };
}
#endif // ROOT_HIPS_H
