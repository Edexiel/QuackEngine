#ifndef QUACKENGINE_PLAYERSYSTEM_HPP
#define QUACKENGINE_PLAYERSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Engine.hpp"


class PlayerSystem : public System
{
public:

    PlayerSystem();

    void Update();

    void Up();
    void Down();
    void Right();
    void Left();

private:
    Engine& engine;
    bool _running {true};

    void MoveForward(float verticalAxis);
    void MoveBackward(float verticalAxis);
    void MoveLeft(float horizontalAxis);
    void MoveRight(float horizontalAxis);

    void StartRunning();
    void StopRunning();
};


#endif //QUACKENGINE_PLAYERSYSTEM_HPP
