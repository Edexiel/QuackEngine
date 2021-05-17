#include "Audio/Sound.hpp"

#include "Audio/SoundManager.hpp"

#include <algorithm>

#include <iostream>

using namespace Audio;

Sound::Sound() : Resources::Asset(Resources::ASSET_TYPE::A_SOUND){}

Sound::Sound(SoundManager* soundManager, unsigned int indexSound) :
Resources::Asset(Resources::ASSET_TYPE::A_SOUND),
_soundManager{soundManager}, _ID{indexSound} {}

unsigned int Sound::GetID() const
{
  return _ID;
}

void Sound::Play()
{
  if (_ID == 0)
    return;

  _soundManager->StartSound(_ID);
}

void Sound::Stop()
{
  if (_ID == 0)
        return;

  _soundManager->StopSound(_ID);
}

void Sound::Restart()
{
  if (_ID == 0)
    return;

  _soundManager->RestartSound(_ID);
}

float Sound::GetVolume()
{
  if (_ID == 0)
    return 0.f;

  return _soundManager->SoundVolume(_ID);
}

float Sound::SetVolume(float newVolume)
{
  if (_ID == 0)
    return 0.f;

  float& volume = _soundManager->SoundVolume(_ID);
  volume = std::max(newVolume, 0.f);
  return volume;
}

SoundType Sound::GetType()
{
  if (_ID == 0)
    return SoundType::S_MASTER;

  return _soundManager->Sound_SoundType(_ID);
}

void Sound::SetType(SoundType soundType)
{
  if (_ID == 0)
    return;

  _soundManager->Sound_SoundType(_ID) = soundType;
}