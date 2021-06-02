#ifndef _PARTICLESYSTEM_HPP
#define _PARTICLESYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Mesh.hpp"
#include "Scene/Component/ParticleEmitter.hpp"

namespace Renderer
{
    class ParticleSystem : public System
    {
    public:
        void Process(const Framebuffer &buffer, const Mesh &screenMesh);
    };
}

#endif //_PARTICLESYSTEM_HPP
