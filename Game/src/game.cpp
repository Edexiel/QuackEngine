#include <stdio.h>

#include "game.hpp"

void Game::Init() {
    printf("Init");
}

void Game::Update(float DeltaTime) {
    printf("Update");
}

void Game::FixedUpdate(float FixedDeltaTime) {}

void Game::Render() {
    printf("Render");

}

void Game::Destroy() {
    printf("Destroy");
}