#include "run.h"

namespace run {

Run::Run(gameRender::GameRender *render) : render_(render) {

    //when you allocate using new[] you need to call delete[], and not delete, to free the resource.
    MQSPEspace espace = MQSPEspace(new maths::Espace(200, 200, 200, 1000));
    render_->makeVertices(maths::Vector<float>(-1.0f, -1.0f, .0f, espace), .5f, 1.0f);
    render_->makeVao(0);

    menu = Menu(render_);
}

void Run::loop() {
    render_->paintStatus(MENU);
    while(!render_->loop_paint()) {
        menu.run();
    }
}
}
