#include <cstdio>

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


void Game::LoadScene(std::string sceneName)
{

}

