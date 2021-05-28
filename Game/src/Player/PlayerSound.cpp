#include <Player/PlayerSound.hpp>
#include "Engine.hpp"

void PlayerSound::PlayUpSound()
{
    _upSound.Restart();
    _upSound.Play();
}

void PlayerSound::PlayDownSound()
{
    _downSound.Restart();
    _downSound.Play();
}

void PlayerSound::PlayRightSound()
{
    //_rightSound.Restart();
    _rightSound.Play();
}

void PlayerSound::PlayLeftSound()
{
    _leftSound.Restart();
    _leftSound.Play();
}

PlayerSound::PlayerSound(const Audio::Sound up, const Audio::Sound down,
                         const Audio::Sound right, const Audio::Sound left) :
_upSound{up}, _downSound{down}, _rightSound{right}, _leftSound{left}{}