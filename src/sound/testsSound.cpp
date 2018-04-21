#include "testsSound.h"

#ifdef TESTS

namespace sound {

TestsSound::TestsSound()
{
}

void TestsSound::playSoundWav()
{
    Sd.parametersWav();
    Sd.loadSoundWav(QString("../data/sounds/test.wav"));
    Sd.play();
}

void TestsSound::playSoundOgg()
{
    Sd.loadSoundOgg(QString("../data/sounds/menu.ogg"));
    Sd.play();
}

void TestsSound::playSoundThread()
{
    Sd.loadSoundOgg(QString("../data/sounds/menu.ogg"));
    Sd.playThread();
    for(short i = 0; i < 8; ++i) {
        QThread::sleep(1);
        std::cout << "*";
    }
    std::cout << std::endl;
}

}

#endif //TESTS
