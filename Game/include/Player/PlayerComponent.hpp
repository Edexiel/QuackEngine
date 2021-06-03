#ifndef QUACKENGINE_PLAYERCOMPONENT_HPP
#define QUACKENGINE_PLAYERCOMPONENT_HPP


#include "Scene/Component/ComponentBase.hpp"
#include "PlayerSound.hpp"


class PlayerComponent : public Component::ComponentBase
{
    PlayerSound _playerSound;


public:
    PlayerComponent();
    int ok = 0;
    PlayerSound &GetPlayerSound();

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(ok));
    }

};


#endif //QUACKENGINE_PLAYERCOMPONENT_HPP
