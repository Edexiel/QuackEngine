#include <stdio.h>

#include "game.hpp"

void Game::Init()
{
    printf("Init");
}

void Game::UpdateInput()
{
    printf("Update Input");
}

void Game::Update(float DeltaTime)
{
    printf("Update");
}

void Game::FixedUpdate(float FixedDeltaTime)
{
    printf("Fixed Update");
}

void Game::Render()
{
    printf("Render");
}

void Game::Destroy()
{
    printf("Destroy");
}

Renderer::Framebuffer &Game::GetFramebuffer()
{
    return screenFB;

}

void Game::ResizeFramebuffer(Maths::Vector2 &size)
{
    //todo: uncomment once implemented
    //screenFB.resize(size);
}

