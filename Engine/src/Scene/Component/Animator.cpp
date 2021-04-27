#include "Scene/Component/Animator.hpp"

#include <string>

using namespace Component;

const std::vector<Maths::Matrix4>& Animator::GetBonesOffsets() const
{
    return _bonesOffset;
}

void Animator::SetShader(Renderer::Shader &shader)
{
    for (unsigned int i = 0; i < 100; i++)
    {
        shader.SetMatrix4((std::string("finalBonesMatrices[") + std::to_string(i) + "]").c_str(),
                          Maths::Matrix4::Translate({(float)i,(float)i,(float)i}));
    }

}
