#include "../include/Resources/ModelLoader.hpp"
#include "../include/Renderer/Mesh.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <iostream>

using namespace Resources;

void ModelLoader::ReadFile(ModelLoader& modelLoader)
{
      // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(modelLoader.path,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

    if (!scene)
    {
        std::cout << "Object : " << modelLoader.path << " not found" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes ; i++)
    {
        for (unsigned int e = 0 ; e < (*scene->mMeshes + i)->mNumVertices ; e++)
        {
            (*scene->mMeshes + i)->mVertices;
            (*scene->mMeshes + i)->mNormals;
            (*scene->mMeshes + i)->mTextureCoords;
        }
    }
}