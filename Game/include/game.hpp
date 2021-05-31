#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP

class Game
{
public:
    Game() = default;
    virtual ~Game() = default;

    void Init(class Engine& engine) const;
    void Update(float deltaTime);
};

#endif // QUACKENGINE_GAME_HPP
