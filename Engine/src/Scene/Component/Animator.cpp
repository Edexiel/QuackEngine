#include "Scene/Component/Animator.hpp"

#include "Tools/Random.hpp"
#include "Maths/Matrix4.hpp"

#include <string>

using namespace Component;
using namespace Renderer;

Animator::Animator()
{
    _bonesOffset.resize(100, Maths::Matrix4::Identity());
}

Animator::Animator(const Renderer::Animation& animation) : _currentAnimation{animation}
{
    _bonesOffset.resize(100, Maths::Matrix4::Identity());
}

void Animator::SetAnimation(const Animation& animation)
{
    _currentTime = 0;
    _currentAnimation = animation;
    _bonesOffset.clear();
    _bonesOffset.resize(100, Maths::Matrix4::Identity());
    Update(0);
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
    _currentTime += _currentAnimation.GetTickPerSecond() * _currentAnimation.GetTickPerSecond() * deltaTime;
    if (_currentTime > _currentAnimation.GetDuration())
        _currentTime = 0;

    Maths::Matrix4 identity = Maths::Matrix4::Identity();
    _currentAnimation.Update(_currentTime);
    CalculateBoneTransform(_currentAnimation.GetRootNode(), identity);
}

void Animator::PlayAnimation(const Renderer::Animation& animation)
{
    _currentTime = 0.f;
    _currentAnimation = animation;
}

void Animator::CalculateBoneTransform(const Renderer::NodeData& node, Maths::Matrix4 parentMatrixWorld)
{
    Maths::Matrix4 nodeTransform = node.transform;

    const Bone* bone = _currentAnimation.GetSkeleton().GetBone(node.name);

    if (bone && bone->IsAnimated())
    {
        nodeTransform = bone->GetLocalTransformation();
    }

    Maths::Matrix4 globalTransform = parentMatrixWorld * nodeTransform;

    if (bone)
    {
        _bonesOffset[bone->GetID()] = globalTransform * bone->GetOffsetTransformation();
    }

    for (int i = 0; i < node.listChildren.size(); i++)
        CalculateBoneTransform(node.listChildren[i], globalTransform);
}

const Renderer::Animation& Animator::GetAnimation() const
{
    return _currentAnimation;
}