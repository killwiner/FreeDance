#include "testsSound.h"

namespace sound {

TestsSound::TestsSound()
{

}

void TestsSound::playSoundOgg()
{
    Sound Sd;
    Sd.loadSoundOgg(QString("../data/sounds/menu.ogg"));
    Sd.play();
}

/*
void TestsSound::playSoundWav()
{
    Sound Sd;
    Sd.parametersWav();
    Sd.loadSoundWav(QString("../data/sounds/test.wav"));
    Sd.play();
}
*/

}
