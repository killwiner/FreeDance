#ifdef TESTS
#include "tests.h"
#else
#include <QApplication>
#include "gameRender/gameRender.h"
#include "intro/intro.h"
#include "run/run.h"
#endif //TESTS

int main(int argc, char *argv[])
{

    QApplication Application(argc, argv);

    #ifdef TESTS

    rendering::TestsOpenglR renderImgs(24, 1000);
    Tests tests(&renderImgs);

    #endif //TESTS

    // rendu par défaut
    gameRender::GameRender render(QString("../data/shaderIntro.vp"), QString("../data/shaderIntro.fp"), 24, 1000);

    // on redimenssionne la fenêtre
    render.setGeometry(20, 20, 1280, 960);
    render.show();

    // lance l'intro
    intro::Intro intro(&render);
    run::Run run(&render);

    render.load();
    intro.video();
    run.loop();
    exit(0);
}
