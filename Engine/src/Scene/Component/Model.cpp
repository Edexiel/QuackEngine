#include "Scene/Component/Model.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Renderer/RendererPlatform.hpp"

#include <iostream>

using namespace Component;
using namespace Renderer;

Model::Model(VertexType vertexType) : _vertexType{vertexType} {}

Model Model::LoadModel(const char *path, VertexType vertexType)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(path,
                    aiProcess_Triangulate |
                    aiProcess_SortByPType |
                    aiProcess_JoinIdenticalVertices |
                    aiProcess_CalcTangentSpace);

  if (!scene)
  {
    std::cout << "Object : " << path << " not found" << std::endl;
    return {};
  }

  switch (vertexType)
  {
    case VertexType::V_NORMALMAP : return LoadNormalMapModel(scene);
    default : return LoadClassicModel(scene);
  }

  //if (normalMapping)
  //  return  LoadModelNormalMap(scene);

  return Model();
}


Model Model::LoadClassicModel(const void* loadedScene)
{
  const aiScene* scene = (aiScene*)loadedScene;

  Model model(VertexType::V_CLASSIC);
  model._meshList.resize(scene->mNumMeshes);

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

      //scene->mMeshes[i]->mTextureCoords[0][e].x;

      if (scene->mMeshes[i]->HasTextureCoords(0))
      {
        vertices[count + 6] = (scene->mMeshes[i]->mTextureCoords[0][e]).x;
        vertices[count + 7] = (scene->mMeshes[i]->mTextureCoords[0][e]).y;
      }
      else
      {
        vertices[count + 6] = 0;
        vertices[count + 7] = 0;
      }
      count += 8;
    }

    // Put loaded data in buffers
    model._meshList[i] = Renderer::RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size());
    RendererPlatform::VerticesReading();
  }
  return model;
}


Model Model::LoadNormalMapModel(const void* loadedScene)
{
  const aiScene* scene = (aiScene*)loadedScene;

  Model model(VertexType::V_NORMALMAP);
  model._meshList.resize(scene->mNumMeshes);

  unsigned int count;
  
  for (unsigned int i = 0; i < scene->mNumMeshes ; i++)
  {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    //vertices.resize(scene->mMeshes[i]->mNumVertices * 14);

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
      vertices.push_back((scene->mMeshes[i]->mVertices[e]).x);
      vertices.push_back((scene->mMeshes[i]->mVertices[e]).y);
      vertices.push_back((scene->mMeshes[i]->mVertices[e]).z);

      vertices.push_back((scene->mMeshes[i]->mNormals[e]).x);
      vertices.push_back((scene->mMeshes[i]->mNormals[e]).y);
      vertices.push_back((scene->mMeshes[i]->mNormals[e]).z);

      //scene->mMeshes[i]->mTextureCoords[0][e].x;

      if (scene->mMeshes[i]->HasTextureCoords(0))
      {
        vertices.push_back((scene->mMeshes[i]->mTextureCoords[0][e]).x);
        vertices.push_back((scene->mMeshes[i]->mTextureCoords[0][e]).y);
      }
      else
      {
        vertices.push_back(0);
        vertices.push_back(0);
      }

      vertices.push_back((scene->mMeshes[i]->mTangents[e]).x);
      vertices.push_back((scene->mMeshes[i]->mTangents[e]).y);
      vertices.push_back((scene->mMeshes[i]->mTangents[e]).z);

      vertices.push_back((scene->mMeshes[i]->mBitangents[e]).x);
      vertices.push_back((scene->mMeshes[i]->mBitangents[e]).y);
      vertices.push_back((scene->mMeshes[i]->mBitangents[e]).z);
      
      count += 14;
    }

    // Put loaded data in buffers
    model._meshList[i] = Renderer::RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size());
    RendererPlatform::VerticesReadingNormalMapping();
  }

  return model;
}


unsigned int Model::AddMaterial(const Renderer::Material& newMaterial)
{
    _materialList.push_back(newMaterial);

    if (newMaterial.shader.GetID() == 0)
    {
        _materialList[_materialList.size() - 1].GenerateShader();
    }

    return _materialList.size() - 1;
}

void Model::RemoveMaterial(unsigned int index)
{
    _materialList.erase(_materialList.cbegin() + index);

    for (unsigned int i = 0; i < _meshList.size() ; i++)
    {
        if (_meshList[i].materialIndex >= _meshList.size())
        {
            _meshList[i].materialIndex = 0;
        }
    }
}

Renderer::Material& Model::GetMaterial(unsigned int index)
{
    return _materialList[index];
}

void Model::Draw(const Maths::Matrix4& projection, const Maths::Matrix4& view, const Maths::Matrix4& transform)
{
  for (unsigned int i = 0 ; i < _meshList.size() ; i++)
  {
     Renderer::Material& material = _materialList[_meshList[i].materialIndex];

     material.Apply();

     material.shader.SetMatrix4("projection", projection);
     material.shader.SetMatrix4("view", view);
     material.shader.SetMatrix4("model", transform);


     _meshList[i].Draw(_vertexType);
  }
}