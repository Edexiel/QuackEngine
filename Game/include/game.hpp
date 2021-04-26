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

    void Init();
    void Update(float deltaTime);
};

#endif // QUACKENGINE_GAME_HPP
