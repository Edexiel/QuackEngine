#include "Scene/Component/Animator.hpp"

#include "Tools/Random.hpp"
#include "Maths/Matrix4.hpp"

#include <string>

using namespace Component;
using namespace Renderer;

Animator::Animator(Renderer::Animation& animation) : _currentAnimation{animation}
{
    _currentAnimation = animation;
    _bonesOffset.resize(100);

    for (unsigned int i = 0; i < 100; i++)
        _bonesOffset[i] = Maths::Matrix4::Identity();
}

const std::vector<Maths::Matrix4>& Animator::GetBonesOffsets() const
{
    return _bonesOffset;
}

void Animator::SetShader(Renderer::Shader &shader)
{
    for (unsigned int i = 0; i < 100; i++)
    {
        shader.SetMatrix4((std::string("finalBonesMatrices[") + std::to_string(i) + "]").c_str(),
                          _bonesOffset[i]);
    }
}

void Animator::Update(float deltaTime)
{
    _currentTime += _currentAnimation.GetTickPerSecond() * deltaTime;
    if (_currentTime > _currentAnimation.GetDuration())
        _currentTime = 0;

    Maths::Matrix4 identity = Maths::Matrix4::Identity();
    _currentAnimation.Update(_currentTime);
    CalculateBoneTransform(_currentAnimation.GetRootNode(), identity);
}

void Animator::PlayAnimation(Renderer::Animation &animation)
{
    _currentTime = 0.f;
    _currentAnimation = animation;
}

void Animator::CalculateBoneTransform(const Renderer::NodeData& node, Maths::Matrix4 parentMatrix)
{
    const Bone* bone = _currentAnimation.GetSkeleton().GetBone(node.name);

    //std::cout << node.name << std::endl;

    Maths::Matrix4 transform = parentMatrix;
    if (bone && &_currentAnimation.GetRootNode() != &node)
    {
        transform *= bone->GetLocalTransformation();
        _bonesOffset[bone->GetID()] = transform; //* bone->GetLocalTransformation();
    }
    else
    {
        //std::cout << "Didn't found " << node.name << std::endl;
    }

    for (unsigned int i = 0; i < node.listChildren.size(); i++)
    {
        //std::cout << i << std::endl;
        CalculateBoneTransform(node.listChildren[i], transform);
    }
}
