#include "Player/PlayerComponent.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Animator.hpp"

PlayerComponent::PlayerComponent()
{
    Engine& engine = Engine::Instance();
    Resources::ResourcesManager& resourcesManager = engine.GetResourcesManager();
    Audio::Sound upSound = resourcesManager.LoadSound("./Asset/Sound/Do.wav", Audio::SoundType::S_MUSIC);
    Audio::Sound downSound = resourcesManager.LoadSound("./Asset/Sound/Fa.wav", Audio::SoundType::S_EFFECT);
    Audio::Sound rightSound = resourcesManager.LoadSound("./Asset/Sound/Mi.wav", Audio::SoundType::S_EFFECT);
    Audio::Sound leftSound = resourcesManager.LoadSound("./Asset/Sound/Re.wav", Audio::SoundType::S_EFFECT);

    _idle = resourcesManager.LoadAnimation("./Asset/Animation/Idle.fbx");
    _running = resourcesManager.LoadAnimation("./Asset/Animation/Standard Run.fbx");

    _playerSound = {upSound, downSound, rightSound, leftSound};
}

PlayerSound &PlayerComponent::GetPlayerSound()
{
    return _playerSound;
}

void PlayerComponent::RunAnimation(bool running)
{
    if (running)
        Engine::Instance().GetCurrentWorld().GetComponent<Component::Animator>(_entity).SetAnimation(_running);
    else
        Engine::Instance().GetCurrentWorld().GetComponent<Component::Animator>(_entity).SetAnimation(_idle);
}
