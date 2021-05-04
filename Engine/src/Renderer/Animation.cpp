#include "Renderer/Animation.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace Renderer;

Animation Animation::LoadAnimation(const char *path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate|
                                             aiProcess_SortByPType|
                                             aiProcess_PopulateArmatureData);

    Animation animation;
    animation.ReadBaseSkeleton((void*)scene->mMeshes[0]);
    auto assimpAnimation = scene->mAnimations[0];
    animation._duration = assimpAnimation->mDuration;
    animation._tickPerSecond = assimpAnimation->mTicksPerSecond;
    ReadHierarchy(animation._rootNode, (void*)scene->mRootNode);

    std::cout << "Num Mesh" << scene->mNumMeshes << std::endl;

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
                                boneMatrix.a4, boneMatrix.c3, boneMatrix.c4, boneMatrix.d4};

            _skeleton.AddBone(Bone(boneName, boneCounter, transform));
            boneCounter++;
        }
        else
        {
            std::cout << "Y'a une couille dans le potage" << std::endl;
        }
    }
}

void Animation::ReadHierarchy(NodeData& node, const void *src)
{
    const aiNode* srcNode = (aiNode*)src;

    node.name = srcNode->mName.data;

    //std::cout << node.name << std::endl;

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

    for (unsigned int i = 0; i < animation->mNumChannels; i++)
    {
        const Bone* bone = _skeleton.GetBone(animation->mChannels[i]->mNodeName.data);
        if (bone)
            _skeleton.SetBone(Bone(bone->GetName(), bone->GetID(), (void*)animation->mChannels[i]));
        else
        {
            _skeleton.AddBone(Bone(animation->mChannels[i]->mNodeName.data, _skeleton.GetBonesNb(),
                                   (void *) animation->mChannels[i]));
            std::cout << "Kes tu fou la ? " << animation->mChannels[i]->mNodeName.data <<  std::endl;
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