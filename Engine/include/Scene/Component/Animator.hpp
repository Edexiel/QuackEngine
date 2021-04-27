#ifndef _ANIMATOR_HPP
#define _ANIMATOR_HPP

#include "Maths/Matrix4.hpp"

#include "Renderer/Animation.hpp"
#include "Renderer/Shader.hpp"

#include <vector>
#include <unordered_map>

namespace Component
{
    class Animator
    {
        std::vector<Maths::Matrix4> _bonesOffset;
        std::unordered_map<std::string, Renderer::Animation> _listAnimation;

        const std::vector<Maths::Matrix4>& GetBonesOffsets() const;

    public:
        void SetShader(Renderer::Shader& shader);

    };
}

#endif //_ANIMATOR_HPP
