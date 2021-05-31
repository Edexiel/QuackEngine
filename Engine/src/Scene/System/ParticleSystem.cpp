#include "Scene/System/ParticleSystem.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/Component/ParticleEmitter.hpp"

using namespace Renderer;

void ParticleSystem::Process(const Framebuffer &buffer, const Mesh &screenMesh)
{
    World& world = Engine::Instance().GetCurrentWorld();
    for (Entity entity : _entities)
    {
        world.GetComponent<Component::ParticleEmitter>(entity);
    }
}