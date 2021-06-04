#ifndef _PARTICLEEMITTER_HPP
#define _PARTICLEEMITTER_HPP

#include "Maths/Vector3.hpp"
#include "Scene/Component/ComponentBase.hpp"
#include "Renderer/Particle.hpp"
#include "Engine.hpp"

namespace Component
{
    class ParticleEmitter : public Component::ComponentBase
    {
        std::vector<Renderer::Particle> _listParticle;
        Renderer::Shader _shader;
        Renderer::Texture _texture;

        Maths::Color4f _colorStart {1.f,1.f,1.f,1.f};
        Maths::Color4f _colorEnd {1.f,1.f,1.f,0.f};

        float _angleStart {0.f};
        float _angleEnd {6.283};

        float _lengthStart  {1.f};
        float _lengthEnd    {2.f};

        float _duration {5.f};

    public:

        ParticleEmitter();
        ParticleEmitter(unsigned int size, float duration, const Renderer::Texture& texture);
        ParticleEmitter(unsigned int size, float duration);
        void Process(const Renderer::Framebuffer& buffer, const Renderer::Mesh& screenMesh);

        void ResetParticle(Renderer::Particle& particle);
        void DrawParticle(const Renderer::Particle& particle, const Renderer::Mesh &screenMesh,
                          const Maths::Matrix4& scale, const Maths::Matrix4& emitterRotation);

        Maths::Color4f& ColorStart();
        Maths::Color4f& ColorEnd();

        float& AngleStart();
        float& AngleEnd();

        float& LengthStart();
        float& LengthEnd();

        float GetDuration();
        void SetDuration(float duration);

        int GetSize();
        void SetSize(unsigned int size);

        Renderer::Texture& GetTexture();

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(CEREAL_NVP(_colorStart), CEREAL_NVP(_colorEnd),
                    CEREAL_NVP(_angleStart), CEREAL_NVP(_angleEnd),
                    CEREAL_NVP(_lengthStart), CEREAL_NVP(_lengthEnd),
                    CEREAL_NVP(_duration), cereal::make_nvp("Size", _listParticle.size()),
                    cereal::make_nvp("Texture", _texture.GetPath()));
        }

        template<class Archive>
        void load(Archive &archive)
        {
            unsigned int size = 0;
            std::string path;
            archive(CEREAL_NVP(_colorStart), CEREAL_NVP(_colorEnd),
                    CEREAL_NVP(_angleStart), CEREAL_NVP(_angleEnd),
                    CEREAL_NVP(_lengthStart), CEREAL_NVP(_lengthEnd),
                    CEREAL_NVP(_duration), cereal::make_nvp("Size", size),
                    cereal::make_nvp("Texture", path));
            _texture.SetPath(path);

            _texture = Engine::Instance().GetResourcesManager().LoadTexture(_texture.GetPath());
            SetSize(size);
        }

    };
}

#endif //_PARTICLEEMITTER_HPP
