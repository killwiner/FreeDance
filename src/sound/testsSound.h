#ifndef TESTSSOUND_H
#define TESTSSOUND_H

#ifdef TESTS

#include "testsuite.h"
#include "sound.h"

namespace sound {

class TestsSound: public QTestSuite
{

    Q_OBJECT

public:
    TestsSound();

private:
    Sound Sd;

private slots:


    void playSoundWav();
    void playSoundOgg();
    void playSoundThread();
};

}
#endif // TESTS

#endif // TESTSSOUND_H
