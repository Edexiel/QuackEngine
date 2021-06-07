#include "Audio/SoundManager.hpp"

#define STB_VORBIS_HEADER_ONLY

#include "stb_vorbis.c"    /* Enables Vorbis decoding. */

#define MINIAUDIO_IMPLEMENTATION

#include "miniaudio.h"

/* stb_vorbis implementation must come after the implementation of miniaudio. */
#undef STB_VORBIS_HEADER_ONLY

#include "stb_vorbis.c"

#include "Audio/Sound.hpp"
#include "Debug/Assertion.hpp"

#include <algorithm>
#include <string>
#include <fmt/format.h>

using namespace Audio;

std::mutex AudioMutex;

float SoundManagerData::GetVolume(SoundType soundType)
{
    switch (soundType)
    {
        case SoundType::S_EFFECT :
            return effectVolume;
        case SoundType::S_MUSIC :
            return musicVolume;
        default:
            return 1.0f;
    }
    return 1.f;
}

unsigned int
SoundManagerData::ReadAndMixPcmFramesF32(const SoundData &soundData, float *pOutputF32, ma_uint32 frameCount)
{
    AudioMutex.lock();

    float temp[480];
    ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frameCount)
    {
        ma_uint32 iSample;
        ma_uint32 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;
        if (framesToReadThisIteration > totalFramesRemaining)
        {
            framesToReadThisIteration = totalFramesRemaining;
        }

        framesReadThisIteration = (ma_uint32) ma_decoder_read_pcm_frames(soundData.decoder, temp,
                                                                         framesToReadThisIteration);

        if (framesReadThisIteration == 0)
        {
            break;
        }

        /* Mix the frames together. */
        for (iSample = 0; iSample < framesReadThisIteration * CHANNEL_COUNT; ++iSample)
        {
            pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample]
                                                                     * soundData.volume * masterVolume *
                                                                     GetVolume(soundData.soundType);
        }

        totalFramesRead += framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration)
        {
            break;  /* Reached EOF. */
        }
    }

    AudioMutex.unlock();

    return totalFramesRead;
}

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    float *pOutputF32 = (float*)pOutput;

    SoundManagerData *soundManagerData = (SoundManagerData *) (pDevice->pUserData);

    MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);   /* <-- Importsant for this example. */

    for (std::pair<soundIndex, SoundData> element : soundManagerData->soundMap)
    {
        if (element.second.isActive)
            soundManagerData->ReadAndMixPcmFramesF32(element.second, pOutputF32, frameCount);
    }

    (void) pInput;
}

SoundManager::~SoundManager()
{
    for (std::pair<soundIndex, SoundData> element : _soundManagerData.soundMap)
    {
        ma_decoder_uninit(element.second.decoder);
        delete element.second.decoder;
    }

    if (_device)
    {
        ma_device_uninit(_device);
        delete _device;
    }
}

void SoundManager::Init()
{
    _device = new ma_device;

    ma_device_config deviceConfig;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate = SAMPLE_RATE;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &_soundManagerData;

    Assert_Fatal_Error((ma_device_init(nullptr, &deviceConfig, _device) != MA_SUCCESS),
                       "Failed to open playback device.");

    Assert_Fatal_Error((ma_device_start(_device) != MA_SUCCESS), "Failed to open playback device.");
}

Sound SoundManager::CreateSound(const std::filesystem::path &path, SoundType soundType)
{
    ma_decoder_config decoderConfig;

    decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
    ma_decoder *decoder = new ma_decoder;
    Assert_Error((ma_decoder_init_file(path.string().c_str(), &decoderConfig, decoder) != MA_SUCCESS),
                 "[Sound] Failed to open: {}", path.string());

    _index += 1;

    _soundManagerData.soundMap.insert({_index, {decoder, false, 1.f}});

    return Sound(this, _index);
}


float SoundManager::GetVolume(SoundType soundType)
{
    switch (soundType)
    {
        case SoundType::S_EFFECT :
            return _soundManagerData.effectVolume;
        case SoundType::S_MUSIC :
            return _soundManagerData.musicVolume;
        default:
            return _soundManagerData.masterVolume;
    }
}

float SoundManager::SetVolume(SoundType soundType, float newVolume)
{
    newVolume = std::clamp(newVolume, 0.f, VOLUME_MAX_VALUE);

    switch (soundType)
    {
        case SoundType::S_EFFECT :
        {
            _soundManagerData.effectVolume = newVolume;
            return _soundManagerData.effectVolume;
        }
        case SoundType::S_MUSIC :
        {
            _soundManagerData.musicVolume = newVolume;
            return _soundManagerData.musicVolume;
        }
        default :
        {
            _soundManagerData.masterVolume = newVolume;
            return _soundManagerData.masterVolume;
        }
    }
}

void SoundManager::StartSound(soundIndex soundIndex)
{
    _soundManagerData.soundMap.find(soundIndex)->second.isActive = true;
}

void SoundManager::StopSound(soundIndex soundIndex)
{
    _soundManagerData.soundMap.find(soundIndex)->second.isActive = false;
}

void SoundManager::RestartSound(soundIndex soundIndex)
{
    AudioMutex.lock();
    ma_decoder_seek_to_pcm_frame(_soundManagerData.soundMap.find(soundIndex)->second.decoder, 0);
    AudioMutex.unlock();
}

float &SoundManager::SoundVolume(soundIndex soundIndex)
{
    return _soundManagerData.soundMap.find(soundIndex)->second.volume;
}

SoundType &SoundManager::Sound_SoundType(soundIndex soundIndex)
{
    return _soundManagerData.soundMap.find(soundIndex)->second.soundType;
}