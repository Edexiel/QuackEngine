#ifndef QUACKENGINE_PLAYERCOMPONENT_HPP
#define QUACKENGINE_PLAYERCOMPONENT_HPP


#include "Scene/Component/ComponentBase.hpp"
#include "PlayerSound.hpp"
#include "Renderer/Animation.hpp"

class PlayerComponent : public Component::ComponentBase
{
    PlayerSound _playerSound;
    Renderer::Animation _idle;
    Renderer::Animation _running;


public:
    PlayerComponent();
    int ok = 0;
    PlayerSound &GetPlayerSound();

    void RunAnimation(bool running);

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(ok));
    }

};


#endif //QUACKENGINE_PLAYERCOMPONENT_HPP
