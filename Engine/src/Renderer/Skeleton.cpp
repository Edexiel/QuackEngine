#include "Renderer/Skeleton.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure

#include "Debug/Assertion.hpp"

using namespace Maths;
using namespace Renderer;


Bone::Bone(const std::string& name, const int id, const Maths::Matrix4& transform) : _name(name), _id{id}, _offset{transform}
{}

void Bone::SetAnimation(const void *node)
{
    _animated = true;

    const aiNodeAnim* channel = (aiNodeAnim*)node;

    for (int i = 0; i < channel->mNumPositionKeys; i++)
    {
        _positions.push_back({{channel->mPositionKeys[i].mValue.x,
                               channel->mPositionKeys[i].mValue.y,
                               channel->mPositionKeys[i].mValue.z},
                               channel->mPositionKeys[i].mTime});
    }

    for (int i = 0; i < channel->mNumRotationKeys; i++)
    {
        _rotations.push_back({{channel->mRotationKeys[i].mValue.w,
                               channel->mRotationKeys[i].mValue.x,
                               channel->mRotationKeys[i].mValue.y,
                               channel->mRotationKeys[i].mValue.z},
                              channel->mRotationKeys[i].mTime});
    }

    for (int i = 0; i < channel->mNumScalingKeys; i++)
    {
        _scales.push_back({{channel->mScalingKeys[i].mValue.x,
                               channel->mScalingKeys[i].mValue.y,
                               channel->mScalingKeys[i].mValue.z},
                              channel->mScalingKeys[i].mTime});
    }
}

int Bone::GetPositionIndex(float animationTime)
{
    for (int i = 0; i < _positions.size() - 1; i++)
    {
        if (animationTime < _positions[i + 1].second)
            return i;
    }
    return 0;
}

int Bone::GetRotationIndex(float animationTime)
{
    for (int i = 0; i < _rotations.size(); i++)
    {
        if (animationTime < _rotations[i + 1].second)
            return i;
    }
    return 0;
}

int Bone::GetScaleIndex(float animationTime)
{
    for (int i = 0; i < _scales.size(); i++)
    {
        if (animationTime < _scales[i + 1].second)
            return i;
    }
    return 0;
}

float Bone::GetTimeScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    return (animationTime - lastTimeStamp) / (nextTimeStamp - lastTimeStamp);
}

Maths::Matrix4 Bone::InterpolatePosition(float animationTime)
{
    if (_positions.size() == 1)
        return Maths::Matrix4::Translate(_positions[0].first);

    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;

    float scaleFactor = GetTimeScaleFactor(_positions[p0Index].second,
                                       _positions[p1Index].second, animationTime);

    Vector3f finalPosition = Vector3f::Lerp(_positions[p0Index].first,
                              _positions[p1Index].first, scaleFactor);

    return  Matrix4::Translate(finalPosition);
}

Maths::Matrix4 Bone::InterpolateRotation(float animationTime)
{
    if (_rotations.size() == 1)
        return _rotations[0].first.ToMatrix();

    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;

    float scaleFactor = GetTimeScaleFactor(_rotations[p0Index].second,
                                           _rotations[p1Index].second, animationTime);

    Quaternion finalRotation = Quaternion::Lerp(_rotations[p0Index].first,
                                              _rotations[p1Index].first, scaleFactor);

    return  finalRotation.ToMatrix();
}

Maths::Matrix4 Bone::InterpolateScale(float animationTime)
{
    if (_scales.size() == 1)
        return Maths::Matrix4::Translate(_scales[0].first);

    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;

    float scaleFactor = GetTimeScaleFactor(_scales[p0Index].second,
                                           _scales[p1Index].second, animationTime);

    Vector3f finalScale = Vector3f::Lerp(_scales[p0Index].first,
                                         _scales[p1Index].first, scaleFactor);

    return Matrix4::Translate(finalScale);
}

void Bone::Update(float animationTime)
{
    if (!_animated)
        return;

    /*_localTransform = InterpolatePosition(animationTime) *
                      InterpolateRotation(animationTime) *
                      InterpolateScale(animationTime);*/

    _localTransform = InterpolateScale(animationTime) *
                      InterpolateRotation(animationTime) *
                      InterpolatePosition(animationTime);
}

int Bone::GetID() const
{
    return _id;
}

const Maths::Matrix4 &Bone::GetLocalTransformation() const
{
    return _localTransform;
}

const Maths::Matrix4 &Bone::GetOffsetTransformation() const
{
    return _offset;
}

const std::string &Bone::GetName() const
{
    return _name;
}

const Bone *Skeleton::GetBone(std::string name) const
{
    auto it = mapBones.find(name);
    if(it == mapBones.end())
    {
        return nullptr;
    }

    return &listBones[it->second];
}

void Skeleton::SetBone(const Bone& bone)
{
    auto it = mapBones.find(bone.GetName());
    if(it == mapBones.end())
    {
        AddBone(bone);
    }

    listBones[it->second] = bone;
}

void Skeleton::SetBoneAnimation(const std::string &name, const void *node)
{
    auto it = mapBones.find(name);
    if(it != mapBones.end())
    {
        listBones[it->second].SetAnimation(node);
    }
}

void Skeleton::AddBone(const Bone& bone)
{
    listBones.push_back(bone);
    mapBones.insert({bone.GetName(), listBones.size() - 1});
}

void Skeleton::Update(float currentTime)
{
    for (unsigned int i = 0; i < listBones.size(); i++)
    {
        listBones[i].Update(currentTime);
    }
}

unsigned int Skeleton::GetBonesNb() const
{
    return listBones.size();
}