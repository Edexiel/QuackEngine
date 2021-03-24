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


using namespace Audio;

std::mutex AudioMutex;

ma_uint32 read_and_mix_pcm_frames_f32(SoundData soundData, float masterVolume, float* pOutputF32, ma_uint32 frameCount)
{
    AudioMutex.lock();

    /*
    The way mixing works is that we just read into a temporary buffer, then take the contents of that buffer and mix it with the
    contents of the output buffer by simply adding the samples together. You could also clip the samples to -1..+1, but I'm not
    doing that in this example.
    */
    float temp[4096];
    ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frameCount) {
        ma_uint32 iSample;
        ma_uint32 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;
        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        framesReadThisIteration = (ma_uint32)ma_decoder_read_pcm_frames(soundData.decoder, temp, framesToReadThisIteration);

        if (framesReadThisIteration == 0) {
            break;
        }

        /* Mix the frames together. */
        for (iSample = 0; iSample < framesReadThisIteration * CHANNEL_COUNT; ++iSample) {
            pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample] * soundData.volume * masterVolume;
        }

        totalFramesRead += framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration) {
            break;  /* Reached EOF. */
        }
    }

    AudioMutex.unlock();

    return totalFramesRead;
}

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    float* pOutputF32 = (float*)pOutput;
    //ma_uint32 iDecoder;

    SoundManagerData* soundManagerData =  (SoundManagerData*)(pDevice->pUserData);

    //ma_decoder* g_pDecodersList = (ma_decoder*)pDevice->pUserData;

    MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);   /* <-- Importsant for this example. */

    for (std::pair<sUint, SoundData> element : soundManagerData->soundMap)
    {
        if(element.second.isActive)
            read_and_mix_pcm_frames_f32(element.second, soundManagerData->masterVolume , pOutputF32, frameCount);
    }

    (void)pInput;
}

SoundManager::SoundManager()
{
    _device = new ma_device;
    //_soundManagerData = new SoundManagerData;

    //decoderConfig = new ma_decoder_config;
    ma_device_config deviceConfig;// = new ma_device_config;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &_soundManagerData;

    Assert_Fatal_Error((ma_device_init(NULL, &deviceConfig, _device) != MA_SUCCESS),
        "Failed to open playback device.\n");

    Assert_Fatal_Error((ma_device_start(_device) != MA_SUCCESS), "Failed to open playback device.\n");
}

SoundManager::~SoundManager()
{
    for (std::pair<sUint, SoundData> element : _soundManagerData.soundMap)
    {
        ma_decoder_uninit(element.second.decoder);
        delete element.second.decoder;
    }

    ma_device_uninit(_device);
    delete _device;
    //delete _soundManagerData;

}

Sound SoundManager::CreateSound(const char *path)
{
    ma_decoder_config decoderConfig;

    decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
    ma_decoder* decoder = new ma_decoder;
    Assert_Warning((ma_decoder_init_file(path, &decoderConfig, decoder) != MA_SUCCESS), "Failed to open playback device.\n");

    _index += 1;

    //SoundManagerData->listDecoder.push_back(decoder);
    //(&_soundManagerData.soundMap)->insert({_index, {true, 1, decoder}});

    _soundManagerData.soundMap.insert({_index, {decoder, true, 1.f}});

    return Sound(this, _index);
}

void SoundManager::StartSound(sUint soundIndex)
{
    //_soundManagerData->
    _soundManagerData.soundMap.find(soundIndex)->second.isActive = true;
}

void SoundManager::StopSound(sUint soundIndex)
{
    //_soundManagerData->soundMap.find(decoder)->second = false;
    _soundManagerData.soundMap.find(soundIndex)->second.isActive = false;
}

void SoundManager::RestartSound(sUint soundIndex)
{
    AudioMutex.lock();
    ma_decoder_seek_to_pcm_frame(_soundManagerData.soundMap.find(soundIndex)->second.decoder, 0);
    AudioMutex.unlock();
}

/*float SoundManager::GetVolume()
{
    return _soundManagerData.masterVolume;
}

float SoundManager::SetVolume(float newVolume)
{
    _soundManagerData.masterVolume = newVolume;
    return _soundManagerData.masterVolume;
}*/