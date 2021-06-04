#ifndef QUACKENGINE_GAME_HPP
#define QUACKENGINE_GAME_HPP

#include "Debug/Log.hpp"
#include <map>
#include <string>
#include "Scene/Core/Types.hpp"


class Engine;

class World;

namespace cereal
{
    class JSONInputArchive;

    class JSONOutputArchive;
}

class Game
{
private:
    static void Register(World &world);
    static void InitGame(World &world);
    static void InitSystems(World &world);
    static void InitSettings(World &world);

    static void Build(const World &world, std::map<std::string, bool> &c, Entity id);
    static void Save(const World &w, cereal::JSONOutputArchive &a, const std::map<std::string, bool> &c, Entity e);
    static void Load(const World &w, cereal::JSONInputArchive &a, const std::map<std::string, bool> &c, Entity e);

public:
    Game() = delete;

    static void Init(Engine &engine);
};

#endif // QUACKENGINE_GAME_HPP
