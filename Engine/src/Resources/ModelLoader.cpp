#include "Resources/ModelLoader.hpp"

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
        std::vector<Vertex> newMesh;

        for (unsigned int e = 0 ; e < (*scene->mMeshes + i)->mNumVertices ; e++)
        {
            Vector3 position {(*scene->mMeshes + i)->mVertices->x, (*scene->mMeshes + i)->mVertices->y, (*scene->mMeshes + i)->mVertices->z};
            Vector3 normal {(*scene->mMeshes + i)->mNormals->x, (*scene->mMeshes + i)->mNormals->y, (*scene->mMeshes + i)->mNormals->z};
            Vector3 uv {0,0};//{(*scene->mMeshes + i)->mTextureCoords, (*scene->mMeshes + i)->mTextureCoords };

            std::cout << position.ToString() << std::endl;

            newMesh.push_back({position, normal, uv});
        }
        modelLoader.ToLoadMesh.push_back(newMesh);
    }
}