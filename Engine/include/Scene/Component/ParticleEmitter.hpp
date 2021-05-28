#ifndef _PARTICLEEMITTER_HPP
#define _PARTICLEEMITTER_HPP

#include "Maths/Vector3.hpp"
#include "Scene/Component/ComponentBase.hpp"
#include "Renderer/Particle.hpp"

namespace Component
{
    class ParticleEmitter : public Component::ComponentBase
    {
        std::vector<Renderer::Particle> _listParticle;
        Renderer::Shader _shader;
        Renderer::Texture _texture;

        float _duration {1.f};

        Maths::Vector3f _direction {0,1,0};

    public:

        ParticleEmitter(unsigned int size, float duration, const Renderer::Shader& shader, const Renderer::Texture& texture);
        void Process(const Renderer::Framebuffer& buffer, const Renderer::Mesh& screenMesh);

        void ResetParticle(Renderer::Particle& particle);

    };
}

#endif //_PARTICLEEMITTER_HPP
