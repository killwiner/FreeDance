#include "testsSound.h"

#ifdef TESTS

namespace sound {

TestsSound::TestsSound()
{
}

void TestsSound::playSoundWav()
{

    //Sd.parametersWav();
    //Sd.loadSoundWav(QString("../data/sounds/test1.wav"));
    //Sd.play();
}

void TestsSound::playSoundOgg()
{
    QThread::sleep(1);
    Sd.loadSoundOgg(QString("../data/sounds/test2.ogg"));
    Sd.play();

}

void TestsSound::playSoundThread()
{
    QThread::sleep(1);
    Sd.loadSoundOgg(QString("../data/sounds/test3.ogg"));
    //Sd.playThread();
    Sd.play();
    for(short i = 0; i < 10; ++i) {
        QThread::sleep(1);
        std::cout << std::to_string(i) << "-" << std::flush;
    }
    std::cout << std::endl;
}

}

#endif //TESTS
