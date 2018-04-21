#include "sound.h"

namespace sound {

Sound::Sound()
{
    // open the device
    try {
        device = alcOpenDevice(nullptr);
        if (!device)
            throw "(sound.cpp) error, can't open the device";

        // obligatoire pour alutCreateBufferFromFile
        alutInitWithoutContext(nullptr, nullptr);

        //Context creation and initialization
        //to render an audio scene
        context = alcCreateContext(device, NULL);
        if (!alcMakeContextCurrent(context))
            throw "(sound.cpp) error, error on context";

        //Create the audio source object
        alGenSources((ALuint)1, &source);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, can't create the audio source object";

    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;

        throw;
    }

}

Sound::~Sound() {
    terminate(); // terminate the thread
    // cleanup context
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void Sound::parametersWav()
{
    try {
        alSourcef(source, AL_PITCH, 1);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, PITCH";
        alSourcef(source, AL_GAIN, 1);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, GAIN";
        alSource3f(source, AL_POSITION, 0, 0, 0);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, POSITION";
        alSource3f(source, AL_VELOCITY, 0, 0, 0);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, VELOCITY";
        alSourcei(source, AL_LOOPING, AL_FALSE);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, LOOP";
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;

        throw;
    }
}

void Sound::loadSoundWav(const QString &file)
{
    try {
        // create the buffer
        alGenBuffers((ALuint)1, &buffer);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, Can't create the buffer";

        // load the sound file
        buffer = alutCreateBufferFromFile(file.toStdString().c_str());
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, Can't load the file";

        // bind buffer with source
        alSourcei(source, AL_BUFFER, buffer);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, Can't bind buffer";
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;

        throw;
    }
}

void Sound::loadSoundOgg(const QString &file)
{
    std::FILE *f;

    try {

        // create the buffer
        alGenBuffers(1, &buffer);

        f = fopen(file.toStdString().c_str(), "rb");
        if(f == NULL)
            throw "(sound.cpp) error, impossible d'ouvrir le fichier Ogg";

        //Note that there is no need to call fclose() anymore once this is done.
        ov_open(f, &oggFile, NULL, 0);

        parametersOgg();
        decodingOgg();

        // Upload sound data to buffer
        alBufferData(buffer, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);

        // Attach sound buffer to source
        alSourcei(source, AL_BUFFER, buffer);

        ov_clear(&oggFile);

    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;

        throw;
    }

}

void Sound::play()
{
    alSourcePlay(source);

    try {

        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        error = alGetError();
        if (error != AL_NO_ERROR)
            throw "(sound.cpp) error, Can't get source state";
        while (source_state == AL_PLAYING) {
            alGetSourcei(source, AL_SOURCE_STATE, &source_state);
            error = alGetError();
            if (error != AL_NO_ERROR)
                throw "(sound.cpp) error, playing error";
        }
    }
    catch (const char* strException) {
        std::cerr << "Exception caught !!" << std::endl;
        std::cerr << strException << std::endl;

        throw;
    }

}

void Sound::playThread()
{
    start();
}

void Sound::run()
{
    play();
}

void Sound::parametersOgg()
{
    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Check the number of channels... always use 16-bit samples
    if (pInfo->channels == 1)
      format = AL_FORMAT_MONO16;
    else
      format = AL_FORMAT_STEREO16;

    // The frequency of the sampling rate
    freq = pInfo->rate;
}

void Sound::decodingOgg()
{

    do {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, 0, 2, 1, &bitStream);
        // Append to end of buffer
        bufferData.insert(bufferData.end(), array, array + bytes);
      } while (bytes > 0);
}

}
