#ifndef _SOUND_
#define _SOUND_


struct ma_decoder;

namespace Audio
{
    class SoundManager;
    class Sound
    {
        SoundManager* _soundManager;
        unsigned int _ID;


    public:

        Sound(SoundManager* soundManager, unsigned int index);
        void SetState(bool isPlaying);

        void Play();
        void Stop();
        void Restart();

    };
}


#endif