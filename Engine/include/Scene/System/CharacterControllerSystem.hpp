#ifndef QUACKENGINE_CHARACTERCONTROLLER_HPP
#define QUACKENGINE_CHARACTERCONTROLLERSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Scene/Core/Types.hpp"
#include "Maths/Vector3.hpp"

class CharacterControllerSystem: public System
{
private:
    void MoveForward(float verticalAxis);
    void MoveBackward(float verticalAxis);
    void MoveLeft(float horizontalAxis);
    void MoveRight(float horizontalAxis);

    void  CharacterMovement(Entity entity);

public:
    void Init();
    void Update();
    static void CollideWithWall(Entity player,const Maths::Vector3f &normal, float depth);
};

#endif //QUACKENGINE_CHARACTERCONTROLLER_HPP