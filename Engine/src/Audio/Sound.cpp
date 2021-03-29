#include "Audio/Sound.hpp"

#include "Audio/SoundManager.hpp"

#include <algorithm>

#include <iostream>

using namespace Audio;

Sound::Sound(SoundManager* soundManager, unsigned int indexSound) : _soundManager{soundManager}, _ID{indexSound} {}

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

float Sound::GetVolume()
{
    return _soundManager->SoundVolume(_ID);
}

float Sound::SetVolume(float newVolume)
{
    float& volume = _soundManager->SoundVolume(_ID);
    volume = std::max(newVolume, 0.f);
    return volume;
}

SoundType& Sound::Type()
{
    return _soundManager->Sound_SoundType(_ID);
}