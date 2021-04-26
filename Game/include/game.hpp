//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP

#include "Renderer/Framebuffer.hpp"
#include "Maths/Vector2.hpp"
#include "Input/InputManager.hpp"


class Game
{
private:
    Renderer::Framebuffer screenFB;
    Input::InputManager input;

public:
    void Init();
    void UpdateInput();
    void Update(float deltaTime);
    void FixedUpdate(float fixedDeltaTime);
    void Render();
    void Destroy();

    Renderer::Framebuffer &GetFramebuffer();
    //void ResizeFramebuffer(Maths::Vector2 &size);
};

#endif // QUACKENGINE_GAME_HPP
