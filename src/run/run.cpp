#include "run.h"

namespace run {

Run::Run(gameRender::GameRender *render) : render_(render) {
    menu = Menu(render_);
}

void Run::loop() {
    while(!render_->loop_paint()) {
        menu.run();
    }
}
}
