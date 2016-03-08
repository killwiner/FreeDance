#ifndef ROOT_H
#define ROOT_H

#include <QSharedPointer>
#include "vectors_maths/maths_vect.h"
#include "win_size.h"
#include <opencv2/opencv.hpp>

#define PIXEL_COLOR_BLUE(X, Y) data[coord_gbr(Vect<int>(X, Y, 0))]
#define PIXEL_COLOR_GREEN(X, Y) data[coord_gbr(Vect<int>(X, Y, 0)) + 1]
#define PIXEL_COLOR_RED(X, Y) data[coord_gbr(Vect<int>(X, Y, 0)) + 2]

#define PIXEL_COLOR_BLUE_VECT(V) data[coord_gbr(V)]
#define PIXEL_COLOR_GREEN_VECT(V) data[coord_gbr(V) + 1]
#define PIXEL_COLOR_RED_VECT(V) data[coord_gbr(V) + 2]

#define NBR_RAYS 32

namespace root {
    class Root {
    public:
        explicit Root(cv::Mat const &mat_frame_, cv::Mat &mat_frame_draw_);
        ~Root();
        virtual void search(float const &, int const &, Vect<float> const &);

        Vect<float> get_coord();

    protected:

        // coordinates of the root
        // coordonnées du noeud
        Vect<float> p;

        // frame to stude
        // référence à l'image qu'on étudie
        cv::Mat mat_frame;
        // the frame with draw of roots
        // l'image avec les dessins des noeuds
        cv::Mat mat_frame_draw;

    private:
        void move_the_circle(bool const &,  Vect<float> const &, float const &, int const &nbr_ray, int &);
        void weight(int const &, std::vector<int> &);
        void reverse(int const &, std::vector<int> &, std::vector<int> const &);
        bool ray_vs_arc(bool &, int const &black_arc, int const &, bool &, float &, float const &);
        void draw_rays(int const &, bool &, std::vector<int> &, Vect<float> &);
        void out_of_the_zone(int const&, int &, bool &, std::vector<int> &, std::vector<int> &, Vect<float> &);
        bool out_of_window(int &, std::vector<int> &, Vect<float> &, int const &);
        void explore_rays(bool &, int const &, int const &, float &, int &, bool &, std::vector<int> &, std::vector<int> &v, float &, float const &);
        // We explore all points along the ray
        // Nous testons tous les points situés sur le rayon
        void explore_circle(bool &, int const &, float const &, int const &, std::vector<int> &, std::vector<int> &, int &);

    };
}
#endif // ROOT_H
