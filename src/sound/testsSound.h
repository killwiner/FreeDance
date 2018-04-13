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

private slots:
    //void playSoundWav();
    void playSoundOgg();
};

}
#endif // TESTS

#endif // TESTSSOUND_H
