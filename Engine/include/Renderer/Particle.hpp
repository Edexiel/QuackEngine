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
        Maths::Color3f color        {1, 1, 1};
        Maths::Vector3f position    {1, 1, 1};
        Maths::Vector3f direction   {1, 1, 1};
        float life                  {1.0f};
    };

    class ParticleProcess : public ProcessBase
    {
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) override;
    };
}

#endif //_PARTICULESYSTEM_HPP
