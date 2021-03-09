#include "../include/Renderer/Model.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "glad/gl.h"

#include <iostream>

using namespace Renderer;

Model Model::LoadModel(const char *path)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(path,
                                           aiProcess_CalcTangentSpace   |
                                           aiProcess_Triangulate              |
                                           aiProcess_SortByPType              |
                                           aiProcess_JoinIdenticalVertices
                                           );

  if (!scene)
  {
    std::cout << "Object : " << path << " not found" << std::endl;
    return {};
  }

  Model model;
  model.meshList.resize(scene->mNumMeshes);

  unsigned int count;
  
  for (unsigned int i = 0; i < scene->mNumMeshes ; i++)
  {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    vertices.resize(scene->mMeshes[i]->mNumVertices * 8);

    // Load indices
    for (unsigned int g = 0; g < scene->mMeshes[i]->mNumFaces ; g++)
    {
        if (scene->mMeshes[i]->mFaces[g].mNumIndices == 3)
        {
            indices.push_back(scene->mMeshes[i]->mFaces[g].mIndices[0]);
            indices.push_back(scene->mMeshes[i]->mFaces[g].mIndices[1]);
            indices.push_back(scene->mMeshes[i]->mFaces[g].mIndices[2]);
        }
    }


    // Load Vertices
    count = 0;
    for (unsigned int e = 0 ; e < scene->mMeshes[i]->mNumVertices ; e++)
    {
      vertices[count + 0] = (scene->mMeshes[i]->mVertices[e]).x;
      vertices[count + 1] = (scene->mMeshes[i]->mVertices[e]).y;
      vertices[count + 2] = (scene->mMeshes[i]->mVertices[e]).z;

      vertices[count + 3] = (scene->mMeshes[i]->mNormals[e]).x;
      vertices[count + 4] = (scene->mMeshes[i]->mNormals[e]).y;
      vertices[count + 5] = (scene->mMeshes[i]->mNormals[e]).z;

      if (scene->mMeshes[i]->HasTextureCoords(e))
      {
        vertices[count + 6] = (scene->mMeshes[i]->mTextureCoords[e])->x;
        vertices[count + 7] = (scene->mMeshes[i]->mTextureCoords[e])->y;
      }
      else
      {
        vertices[count + 6] = 0;
        vertices[count + 7] = 0;
      }
      count += 8;
    }

    unsigned int vao, vbo, ebo, nbVertices, nbIndices;

    // Put loaded data in buffers

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    nbVertices = vertices.size();
    nbIndices = indices.size();

    model.meshList[i] = Mesh(vao, vbo, ebo, nbVertices, nbIndices);
  }

  return model;
}