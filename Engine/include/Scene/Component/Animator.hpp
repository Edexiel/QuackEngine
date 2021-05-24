#ifndef _ANIMATOR_HPP
#define _ANIMATOR_HPP

#include "Maths/Matrix4.hpp"

#include "Renderer/Animation.hpp"
#include "Renderer/Shader.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Engine.hpp"

#include <vector>
#include <unordered_map>

namespace Component
{
    class Animator
    {
        std::vector<Maths::Matrix4> _bonesOffset;
        Renderer::Animation _currentAnimation;

        float _currentTime {0.f};

        const std::vector<Maths::Matrix4>& GetBonesOffsets() const;

        void CalculateBoneTransform(const Renderer::NodeData& node, Maths::Matrix4 parentMatrixWorld);

    public:

        Animator() = default;
        explicit Animator(const Renderer::Animation& animation);
        void SetAnimation(const Renderer::Animation& animation);

        void Update(float deltaTime);
        void SetShader(Renderer::Shader& shader);

        void PlayAnimation(Renderer::Animation& animation);

        const Renderer::Animation& GetAnimation() const;

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(cereal::make_nvp("path",_currentAnimation.name));
        }

        template<class Archive>
        void load(Archive &archive)
        {

            std::string name;
            archive(cereal::make_nvp("path",name));
            Resources::ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();
            SetAnimation(resourcesManager.LoadAnimation(name));
        }

    };
}

#endif //_ANIMATOR_HPP
