#include "Renderer/Particle.hpp"

#include "Scene/System/ParticleSystem.hpp"
#include "Scene/Component/ParticleEmitter.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/Framebuffer.hpp"

using namespace Renderer;


void ParticleProcess::Process(const Framebuffer &buffer, const Mesh &screenMesh)
{
    Engine::Instance().GetCurrentWorld().GetSystem<ParticleSystem>()->Process(buffer, screenMesh);
}