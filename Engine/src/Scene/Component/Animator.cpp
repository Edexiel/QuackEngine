#include "Scene/Component/Animator.hpp"

#include "Tools/Random.hpp"
#include "Maths/Matrix4.hpp"

#include <string>

using namespace Component;
using namespace Renderer;

Animator::Animator(Renderer::Animation& animation) : _currentAnimation{animation}
{
    _currentAnimation = animation;
    _bonesOffset.resize(100, Maths::Matrix4::Identity());

    /*for (unsigned int i = 0; i < 100; i++)
        _bonesOffset[i] = Maths::Matrix4::Identity();*/
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
    if (_currentTime > _currentAnimation.GetDuration() - 1)
        _currentTime = 0;

    Maths::Matrix4 identity = Maths::Matrix4::Identity();
    _currentAnimation.Update(_currentTime);
    CalculateBoneTransform(_currentAnimation.GetRootNode(), identity, identity);
}

void Animator::PlayAnimation(Renderer::Animation &animation)
{
    _currentTime = 0.f;
    _currentAnimation = animation;
}

void Animator::CalculateBoneTransform(const Renderer::NodeData& node, Maths::Matrix4 parentMatrixWorld, Maths::Matrix4 bonePlace)
{
    const Bone* bone = _currentAnimation.GetSkeleton().GetBone(node.name);

    //Maths::Matrix4 boneTransform = node.transform;
    Maths::Matrix4 globalTransform = parentMatrixWorld * node.transform;

    //std::cout << node.name << std::endl;
    //parentMatrixWorld *= node.transform;
    if (bone)
    {
        //boneTransform = bone->GetLocalTransformation();
        //_bonesOffset[bone->GetID()] = boneMatrix * parentMatrixWorld.GetInvert();

        globalTransform = parentMatrixWorld * bone->GetLocalTransformation();
        _bonesOffset[bone->GetID()] = globalTransform  * bone->GetOffsetTransformation().GetInvert();
    }

    for (unsigned int i = 0; i < node.listChildren.size(); i++)
    {
        //std::cout << i << std::endl;
        CalculateBoneTransform(node.listChildren[i], globalTransform, bonePlace);
    }
}
