#ifndef _PARTICULESYSTEM_HPP
#define _PARTICULESYSTEM_HPP

#include "Texture.hpp"
#include "Maths/Vector3.hpp"

#include "Scene/Core/System.hpp"
#include "Renderer/PostProcessManager.hpp"

#include <vector>

namespace Renderer
{

    struct Particle
    {
        Maths::Vector3f start   {0.f, 0.f, 0.f};
        Maths::Vector3f end     {1.f, 1.f, 1.f};
        float life              {1.0f};
    };

    class ParticleProcess : public ProcessBase
    {
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) override;
    };
}

#endif //_PARTICULESYSTEM_HPP
