#ifndef _SOUND_
#define _SOUND_

#include "Resources/Asset.hpp"

struct ma_decoder;

namespace Audio
{
    enum class SoundType;

    class SoundManager;
    class Sound : public Resources::Asset
    {
        SoundManager* _soundManager;
        unsigned int _ID {0};


    public:

        Sound();
        Sound(SoundManager* soundManager, unsigned int index);

        unsigned int GetID() const;

        void Play();
        void Stop();
        void Restart();

        float GetVolume();
        float SetVolume(float newVolume);


        SoundType GetType();
        void      SetType(SoundType soundType);

    };
}


#endif