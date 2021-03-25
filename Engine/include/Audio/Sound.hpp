#ifndef _SOUND_
#define _SOUND_


struct ma_decoder;

namespace Audio
{
    enum class SoundType;

    class SoundManager;
    class Sound
    {
        SoundManager* _soundManager;
        unsigned int _ID {0};


    public:

        Sound(SoundManager* soundManager, unsigned int index);

        void Play();
        void Stop();
        void Restart();

        float GetVolume();
        float SetVolume(float newVolume);


        SoundType& Type();

    };
}


#endif