#ifndef _PLAYERSOUND_HPP
#define _PLAYERSOUND_HPP

#include "Audio/Sound.hpp"

class PlayerSound
{
    Audio::Sound _upSound;
    Audio::Sound _downSound;
    Audio::Sound _rightSound;
    Audio::Sound _leftSound;

public:
    void PlayUpSound();
    void PlayDownSound();
    void PlayRightSound();
    void PlayLeftSound();

    PlayerSound() = default;
    PlayerSound(const Audio::Sound up, const Audio::Sound down,
                const Audio::Sound right, const Audio::Sound left);

};

#endif //_PLAYERSOUND_HPP
