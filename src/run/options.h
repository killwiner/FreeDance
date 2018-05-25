#ifndef OPTIONS_H
#define OPTIONS_H

#include "panel.h"

namespace run {

class Options
{
public:
    Options();
    Options(gameRender::GameRender *render);
    void run(const maths::Vector<float> &VMouse, const bool &bMouse);
private:
    gameRender::GameRender *render_;
    MQSPEspace espace;
    Button b_options;
    Panel p_options;
    bool activated;
};

}

#endif // OPTIONS_H
