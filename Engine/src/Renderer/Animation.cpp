#include "Renderer/Animation.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace Renderer;

Animation Animation::LoadAnimation(const char *path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_SortByPType |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_CalcTangentSpace);

    scene->mAnimations[0]->mMorphMeshChannels[0];

    //Animation animation;

    return {};
}
