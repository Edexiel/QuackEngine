#ifndef QUACKENGINE_PLAYERCOMPONENT_HPP
#define QUACKENGINE_PLAYERCOMPONENT_HPP


#include "Scene/Component/ComponentBase.hpp"
#include "PlayerSound.hpp"

class PlayerComponent : public Component::ComponentBase
{
    PlayerSound _playerSound;

public:
    PlayerComponent();

    PlayerSound& GetPlayerSound();

};


#endif //QUACKENGINE_PLAYERCOMPONENT_HPP
