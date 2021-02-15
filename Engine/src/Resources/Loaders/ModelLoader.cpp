#include "Resources/Loaders/ModelLoader.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "glad/gl.h"

#include <Renderer/Model.hpp>

#include <iostream>

using namespace Resources;
using namespace Loaders;
using namespace Renderer;

ModelLoader::ModelLoader(Renderer::Model* _model, const char* _path) : model{_model}, path{_path} {}

void ModelLoader::ReadFile(ModelLoader* modelLoader)
{
      // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(modelLoader->path,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_SortByPType);

    if (!scene)
    {
        std::cout << "Object : " << modelLoader->path << " not found" << std::endl;
        return;
    }

    std::cout << "Object : " << modelLoader->path << " found" << std::endl;
    std::cout << "Nb Model : " << scene->mNumMeshes << " found" << std::endl;

    modelLoader->model->meshList.resize(scene->mNumMeshes);

    for (unsigned int i = 0; i < scene->mNumMeshes ; i++)
    {
        std::cout << "Pointer [" << i << "] = " << (scene->mMeshes[i]) << std::endl;
        std::cout << "nbVertice : " << (scene->mMeshes[i])->mNumVertices << std::endl;

        std::vector<float> Points(0.f);
        Points.resize(scene->mMeshes[i]->mNumVertices * 8);

        std::cout << "Size List = " << Points.size() / 8 << std::endl;

        unsigned int count = 0;

        Mesh newMesh;
        newMesh.size = scene->mMeshes[i]->mNumVertices;
        modelLoader->model->meshList[i] = newMesh;

        for (unsigned int e = 0 ; e < scene->mMeshes[i]->mNumVertices ; e++)
        {
            Points[count + 0] = (scene->mMeshes[i]->mVertices[e]).x;
            Points[count + 1] = (scene->mMeshes[i]->mVertices[e]).y;
            Points[count + 2] = (scene->mMeshes[i]->mVertices[e]).z;

            Points[count + 3] = (scene->mMeshes[i]->mNormals[e]).x;
            Points[count + 4] = (scene->mMeshes[i]->mNormals[e]).y;
            Points[count + 5] = (scene->mMeshes[i]->mNormals[e]).z;

            if (scene->mMeshes[i]->HasTextureCoords(e))
            {
                Points[count + 6] = (scene->mMeshes[i]->mTextureCoords[e])->x;
                Points[count + 7] = (scene->mMeshes[i]->mTextureCoords[e])->y;
            }
            else
            {
                Points[count + 6] = 0;
                Points[count + 7] = 0;
            }
            count += 8;
        }

        modelLoader->listMeshToLoad.push_back(Points);
    }
}

void ModelLoader::Apply()
{
    for (unsigned int i = 0; i < listMeshToLoad.size() ; i++)
    {
        glGenBuffers(1, &model->meshList[i].buffer); // Generate 1 buffer, put the resulting identifier in buffer
        glBindBuffer(GL_ARRAY_BUFFER, model->meshList[i].buffer);
        glBufferData(GL_ARRAY_BUFFER, listMeshToLoad[i].size() * sizeof (GLfloat), listMeshToLoad[i].data(), GL_STATIC_DRAW); // Give our vertices to OpenGL.

        std::cout << "Buffer = " << model->meshList[i].buffer << std::endl;
    }
}