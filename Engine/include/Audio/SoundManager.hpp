#ifndef _SOUND_MANAGER_
#define _SOUND_MANAGER_

#include <unordered_map>
#include <vector>
#include <mutex>

#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000

struct ma_decoder;
struct ma_device;

typedef unsigned int sUint;

namespace Audio
{
    class Sound;

    enum class SoundType {S_MUSIC, S_EFFECT};

    struct SoundData
    {
        ma_decoder* decoder;
        bool isActive {false};
        float volume {1.f};
        SoundType soundType {SoundType::S_EFFECT};
    };
    struct SoundManagerData
    {
        float masterVolume {1.0f};
        std::unordered_map<sUint, SoundData> soundMap;
    };


    class SoundManager
    {
        unsigned int _index {0};

        ma_device* _device;
        SoundManagerData _soundManagerData;

    public:
        SoundManager();
        ~SoundManager();

        Sound CreateSound(const char* path);

        void StartSound(sUint soundIndex);
        void StopSound(sUint soundIndex);
        void RestartSound(sUint soundIndex);

        float GetMasterVolume();
        float SetMasterVolume(float newVolume);

        float GetVolume(SoundType soundType);
        float SetVolume(SoundType soundType, float newVolume);
    };
}

#endif