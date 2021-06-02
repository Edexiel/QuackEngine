#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP

class Engine;

class World;

class Game
{
private:
    static void Register(World &world);
    static void InitGame(World &world);
    static void InitSystems(World &world);
    static void InitSettings(World &world);
public:
    Game() = delete;
    static void Init(Engine &engine);
};

#endif // QUACKENGINE_GAME_HPP
