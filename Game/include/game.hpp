//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP


#include <string>

class Game
{
public:
    Game() = default;
    virtual ~Game() = default;

    void LoadScene(std::string sceneName);
    void Init();
    void UpdateInput();
    void Update(float deltaTime);
    void FixedUpdate(float fixedDeltaTime);
    void Render();
};

#endif // QUACKENGINE_GAME_HPP
