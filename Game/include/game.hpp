#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP

#include "Debug/Log.hpp"
#include <map>
#include <string>
#include "Scene/Core/Types.hpp"

class Engine;

class World;

class Game
{
private:
    static void Register(World &world);
    static void InitGame(World &world);
    static void InitSystems(World &world);
    static void InitSettings(World &world);

    static void Build(const World& world,std::map<std::string, bool> &c,Entity id);
    template<class Archive>
    static void Save(const World& w,Archive *archive)
    {
        Log_Warning("SAVINNNNNG");
    }

    template<class Archive>
    static void Load(const World& w,Archive *archive)
    {
        Log_Warning("LOADINGGGGGG");
    }

public:
    Game() = delete;

    static void Init(Engine &engine);
};

#endif // QUACKENGINE_GAME_HPP
