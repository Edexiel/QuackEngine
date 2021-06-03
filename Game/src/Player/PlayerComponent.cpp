#include "Player/PlayerComponent.hpp"

#include "Engine.hpp"

PlayerComponent::PlayerComponent()
{
    Engine& engine = Engine::Instance();
    Resources::ResourcesManager& resourcesManager = engine.GetResourcesManager();
    Audio::Sound upSound = resourcesManager.LoadSound("../../Game/Asset/Player/Sound/inactive.ogg", Audio::SoundType::S_EFFECT);
    Audio::Sound downSound = resourcesManager.LoadSound("../../Game/Asset/Player/Sound/inactive.ogg", Audio::SoundType::S_EFFECT);
    Audio::Sound rightSound = resourcesManager.LoadSound("../../Game/Asset/Player/Sound/inactive.ogg", Audio::SoundType::S_EFFECT);
    Audio::Sound leftSound = resourcesManager.LoadSound("../../Game/Asset/Player/Sound/inactive.ogg", Audio::SoundType::S_EFFECT);

    _playerSound = {upSound, downSound, rightSound, leftSound};
}

PlayerSound &PlayerComponent::GetPlayerSound()
{
    return _playerSound;
}
