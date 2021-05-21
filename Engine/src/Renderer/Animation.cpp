#include "Renderer/Animation.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace Renderer;

Animation::Animation() : Resources::Asset(Resources::AssetType::A_ANIMATION){}


Animation Animation::LoadAnimation(const char *path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices);

    Animation animation;
    animation.ReadBaseSkeleton((void*)scene->mMeshes[0]);
    auto assimpAnimation = scene->mAnimations[0];
    animation._duration = (float)assimpAnimation->mDuration;
    animation._tickPerSecond = (float)assimpAnimation->mTicksPerSecond;
    ReadHierarchy(animation._rootNode, (void*)scene->mRootNode);

    animation.ReadBones((void*)assimpAnimation);

    return animation;
}

void Animation::ReadBaseSkeleton(const void* baseMesh)
{
    aiMesh *mesh = (aiMesh *) baseMesh;

    int boneCounter = 0;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (!_skeleton.GetBone(boneName))
        {
            //newBone.id = m_BoneCounter;
            auto boneMatrix = mesh->mBones[boneIndex]->mOffsetMatrix;
            Maths::Matrix4 transform = {
                                boneMatrix.a1, boneMatrix.b1, boneMatrix.c1, boneMatrix.d1,
                                boneMatrix.a2, boneMatrix.b2, boneMatrix.c2, boneMatrix.d2,
                                boneMatrix.a3, boneMatrix.b3, boneMatrix.c3, boneMatrix.d3,
                                boneMatrix.a4, boneMatrix.b4, boneMatrix.c4, boneMatrix.d4};

            _skeleton.AddBone(Bone(boneName, boneCounter, transform));
            boneCounter++;
        }
    }
}

void Animation::ReadHierarchy(NodeData& node, const void *src)
{
    const aiNode* srcNode = (aiNode*)src;

    node.name = srcNode->mName.data;

    node.transform = {srcNode->mTransformation.a1, srcNode->mTransformation.b1, srcNode->mTransformation.c1, srcNode->mTransformation.d1,
                      srcNode->mTransformation.a2, srcNode->mTransformation.b2, srcNode->mTransformation.c2, srcNode->mTransformation.d2,
                      srcNode->mTransformation.a3, srcNode->mTransformation.b3, srcNode->mTransformation.c3, srcNode->mTransformation.d3,
                      srcNode->mTransformation.a4, srcNode->mTransformation.b4, srcNode->mTransformation.c4, srcNode->mTransformation.d4};

    for (unsigned int i = 0; i < srcNode->mNumChildren; i++)
    {
        NodeData newNode;
        ReadHierarchy(newNode, srcNode->mChildren[i]);
        node.listChildren.push_back(newNode);
    }
}

void Animation::ReadBones(const void *loadedAnimation)
{
    const aiAnimation* animation = (aiAnimation*)loadedAnimation;

    std::cout << "Animation Name : " << animation->mName.data << std::endl;

    for (unsigned int i = 0; i < animation->mNumChannels; i++)
    {
        const Bone* bone = _skeleton.GetBone(animation->mChannels[i]->mNodeName.data);
        if (bone)
            _skeleton.SetBoneAnimation(bone->GetName(), (void*)animation->mChannels[i]);
        else
        {
            _skeleton.AddBone(Bone(animation->mChannels[i]->mNodeName.data, _skeleton.GetBonesNb(),
                                   Maths::Matrix4::Identity()));
        }
    }
}

void Animation::Update(float currentTime)
{
    _skeleton.Update(currentTime);
}

float Animation::GetDuration() const
{
    return _duration;
}


float Animation::GetTickPerSecond() const
{
    return _tickPerSecond;
}

const NodeData &Animation::GetRootNode() const
{
    return _rootNode ;
}

const Skeleton &Animation::GetSkeleton() const
{
    return _skeleton;
}

void Animation::DisplayHierarchy(const NodeData& node, int depth)
{
    for (unsigned int i = 0; i < depth; i++)
        std::cout << " - ";

    std::cout << "| " << node.name << std::endl;
    for (unsigned int i = 0; i < node.listChildren.size(); i++)
    {
        DisplayHierarchy(node.listChildren[i], depth + 1);
    }
}