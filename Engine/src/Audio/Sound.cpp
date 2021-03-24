#include "Audio/Sound.hpp"

#include "Audio/SoundManager.hpp"

using namespace Audio;

Sound::Sound(SoundManager* soundManager, unsigned int indexSound) : _soundManager{soundManager}, _ID{indexSound} {}

void Sound::SetState(bool isPlaying)
{
}

void Sound::Play()
{
    _soundManager->StartSound(_ID);
}

void Sound::Stop()
{
    _soundManager->StopSound(_ID);
}

void Sound::Restart()
{
    _soundManager->RestartSound(_ID);
}