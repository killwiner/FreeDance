#ifndef SOUND_H
#define SOUND_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <vorbis/vorbisfile.h>
#include <iostream>
#include <QString>
#include <vector>
#include <QThread>

#define BUFFER_SIZE 32768

namespace sound {

class Sound : public QThread
{
    Q_OBJECT

public:
    Sound();
    ~Sound();

    void parametersWav();
    void loadSoundWav(const QString &file);
    void loadSoundOgg(const QString &file);
    void play();
    void playThread();

private:
    std::FILE *f;
    ALCdevice *device;
    ALCcontext *context;
    ALCenum error;
    ALuint source;
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop;
    ALuint buffer;
    ALint source_state;
    OggVorbis_File oggFile;
    vorbis_info *pInfo;
    std::vector<char> bufferData;
    long bytes;
    char array[BUFFER_SIZE];
    int bitStream;

    void parametersOgg();
    void decodingOgg();
    void run();
};

}
#endif // SOUND_H
