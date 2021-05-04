#include "Scene/Component/Model.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Renderer/RendererPlatform.hpp"
#include "Engine.hpp"

#include "Debug/Assertion.hpp"

#include "Renderer/Skeleton.hpp"

#include <iostream>

using namespace Component;
using namespace Renderer;

Model::Model(VertexType vertexType) : _vertexType{vertexType} {}

void Model::Destroy()
{
    for (unsigned int i = 0; i < _meshList.size(); i++)
    {
        _meshList[i].Destroy();
    }
    _meshList.clear();
}

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

  Model loadedModel;

  switch (vertexType)
  {
      case VertexType::V_SKELETAL : loadedModel = LoadSkeletalMeshModel(scene); break;
      case VertexType::V_NORMALMAP : loadedModel = LoadNormalMapModel(scene); break;
      default : loadedModel = LoadClassicModel(scene); break;
  }

    loadedModel.name = path;
    return loadedModel;
}

void Model::ReLoadModel(Model& model, const char *path, Renderer::VertexType vertexType)
{
    model.Destroy();
    Model newModel = LoadModel(path, vertexType);
    newModel._materialList = model._materialList;

    model = newModel;
}

void Model::ReLoadModel(Model& oldModel, Model newModel)
{
    newModel._materialList = oldModel._materialList;
    oldModel = newModel;
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
    std::vector<unsigned int> indices = LoadIndices(loadedScene, i);

    vertices.resize(scene->mMeshes[i]->mNumVertices * 8);

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
    model._meshList[i] = Renderer::RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size(), VertexType::V_CLASSIC);
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
    std::vector<unsigned int> indices = LoadIndices(loadedScene, i);


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
    model._meshList[i] = Renderer::RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size(), Renderer::VertexType::V_NORMALMAP);
    RendererPlatform::VerticesReadingNormalMapping();
  }

  return model;
}

std::vector<unsigned int> Model::LoadIndices(const void* loadedScene, unsigned int meshId)
{
    const aiScene* scene = (aiScene*)loadedScene;

    std::vector<unsigned int> indices;

    // Load indices
    for (unsigned int g = 0; g < scene->mMeshes[meshId]->mNumFaces ; g++)
    {
        if (scene->mMeshes[meshId]->mFaces[g].mNumIndices == 3)
        {
            indices.push_back(scene->mMeshes[meshId]->mFaces[g].mIndices[0]);
            indices.push_back(scene->mMeshes[meshId]->mFaces[g].mIndices[1]);
            indices.push_back(scene->mMeshes[meshId]->mFaces[g].mIndices[2]);
        }
    }

    return indices;
}

Model Model::LoadSkeletalMeshModel(const void* loadedScene)
{
    const aiScene* scene = (aiScene*)loadedScene;

    Model model(VertexType::V_SKELETAL);
    model._meshList.resize(scene->mNumMeshes);

    unsigned int count;

    for (unsigned int i = 0; i < scene->mNumMeshes ; i++)
    {
        std::vector<SkeletalVertex> vertices;
        std::vector<unsigned int> indices = LoadIndices(loadedScene, i);

        vertices.resize(scene->mMeshes[i]->mNumVertices);

        // Load Vertices
        count = 0;
        for (unsigned int e = 0 ; e < scene->mMeshes[i]->mNumVertices ; e++)
        {
            Maths::Vector3f position {(scene->mMeshes[i]->mVertices[e]).x,
                                      (scene->mMeshes[i]->mVertices[e]).y,
                                      (scene->mMeshes[i]->mVertices[e]).z};

            Maths::Vector3f normal {(scene->mMeshes[i]->mNormals[e]).x,
                                    (scene->mMeshes[i]->mNormals[e]).y,
                                    (scene->mMeshes[i]->mNormals[e]).z};

            Maths::Vector2f texture;

            if (scene->mMeshes[i]->HasTextureCoords(0))
            {
                texture = {(scene->mMeshes[i]->mTextureCoords[0][e]).x,
                         (scene->mMeshes[i]->mTextureCoords[0][e]).y};
            }

            vertices[e] = {position, normal, texture};

            model.ExtractBoneWeightForVertices(vertices, i, scene);
        }

        //Skeleton skeletalMesh;

        /*for (unsigned int i = 0 ; i < vertices.size(); i++)
        {
            std::cout << "X = " << vertices[i].boneId.x <<
            ", Y = " << vertices[i].boneId.y <<
            ", Z = " << vertices[i].boneId.z <<
            ", W = " << vertices[i].boneId.w << std::endl;
        }*/

        // Put loaded data in buffers
        model._meshList[i] = Renderer::RendererPlatform::CreateMesh((float*)vertices.data(), vertices.size() * 16,
                                                                    indices.data(), indices.size(),
                                                                    Renderer::VertexType::V_SKELETAL);
        RendererPlatform::VerticesReadingSkeletalMesh();
    }

    return model;
}

void Model::SetVertexBoneData(SkeletalVertex &vertex, int boneID, float weight)
{
    for (int i = 0; i < 4; ++i)
    {
        if (vertex.boneId.e[i] == -1.0f)
        {
            vertex.weights.e[i] = weight;
            vertex.boneId.e[i] = boneID;
            break;
        }
    }
}

void Model::ExtractBoneWeightForVertices(std::vector<Renderer::SkeletalVertex> &vertices,
                                         unsigned int meshId,
                                         const void *loadedScene)
{

    //std::cout << 035746 << std::endl;

    const aiScene* scene = (aiScene*)loadedScene;
    aiMesh* mesh = scene->mMeshes[meshId];

    int boneCounter = 0;

    //std::cout << mesh->mBones[0]->mNumWeights << std::endl;

    std::unordered_map<std::string, int> _skeleton;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (_skeleton.find(boneName) == _skeleton.end())
        {
            /*Bone newBone;
            //newBone.id = m_BoneCounter;
            auto boneMatrix = mesh->mBones[boneIndex]->mOffsetMatrix;
            newBone.offset = {boneMatrix.a1, boneMatrix.a2, boneMatrix.a3, boneMatrix.a4,
                              boneMatrix.b1, boneMatrix.b2, boneMatrix.b3, boneMatrix.b4,
                              boneMatrix.c1, boneMatrix.c2, boneMatrix.c3, boneMatrix.c4,
                              boneMatrix.d1, boneMatrix.d2, boneMatrix.d3, boneMatrix.d4};

            newBone.offset = newBone.offset.GetTranspose();*/
            _skeleton.insert({boneName, boneCounter});
            boneID = boneCounter;
            boneCounter++;
        }
        else
        {
            boneID = _skeleton[boneName];
        }
        assert(boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (unsigned int weightIndex = 0; weightIndex < numWeights; weightIndex++)
        {
            unsigned int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
    /*for (unsigned int i = 0; i < vertices.size(); i++)
    {
        std::cout << "X = " << vertices[i].boneId.x << ", Y = " << vertices[i].boneId.y << ", Z = " << vertices[i].boneId.z << ", W = " << vertices[i].boneId.w << std::endl;
    }*/
}

unsigned int Model::AddMaterial(const MaterialInterface& newMaterial)
{
    // todo put back when the PropertiesWidget allow material selection for the "Add Material" button
    /*for (unsigned int i = 0; i < _materialList.size(); i++)
    {
        if (newMaterial == _materialList[i])
            return i;
    }*/

    _materialList.push_back(newMaterial);

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

Renderer::MaterialInterface& Model::GetMaterial(unsigned int index)
{
    if (_materialList.size() <= index)
    {
        if (_materialList.empty())
        {
            MaterialInterface material = Engine::Instance().GetResourcesManager().LoadMaterial(DEFAULT_MATERIAL_STRING);
            _materialList.push_back(material);
        }
        return _materialList[0];
    }
    return _materialList[index];
}

void Model::Draw(const Maths::Matrix4& projection, const Maths::Matrix4& view, const Maths::Matrix4& transform)
{
  for (unsigned int i = 0 ; i < _meshList.size() ; i++)
  {
     Renderer::MaterialInterface& material = _materialList[_meshList[i].materialIndex];

     material->Apply();

     material->shader.SetMatrix4("projection", projection);
     material->shader.SetMatrix4("view", view);
     material->shader.SetMatrix4("model", transform);

     _meshList[i].Draw();
  }
}

unsigned int Model::ChangeMaterial(const MaterialInterface &newMaterial, unsigned int index)
{
    if ((index >= _materialList.size()))
    {
        Assert_Warning(true, "The material index in model is invalid");
        return 0;
    }

    _materialList[index] = newMaterial;
    return index;
}

void Model::SetMeshMaterial(unsigned int meshIndex, unsigned int materialIndex)
{
    if (meshIndex >= _meshList.size())
    {
        Assert_Warning(true, "Mesh index invalid");
    }
    if (materialIndex >= _materialList.size())
    {
        Assert_Warning(true, "Material index invalid");
    }

    _meshList[meshIndex].materialIndex = materialIndex;
}

const Renderer::Mesh& Model::GetMesh(unsigned int index) const
{
    if (index >= _meshList.size())
    {
        Assert_Error(true, "Invalid mesh index");
        return Mesh();
    }
    return _meshList[index];
}

unsigned int* Model::GetMeshMaterialIndex(unsigned int index)
{
    if (index >= _meshList.size())
    {
        Assert_Error(true, "Invalid mesh index");
        return nullptr;
    }
    return &_meshList[index].materialIndex;
}

unsigned int Model::GetNumberMesh() const
{
    return _meshList.size();
}

unsigned int Model::GetNumberMaterial() const
{
    return _materialList.size();
}

Renderer::VertexType Model::GetVertexType() const
{
    return _vertexType;
}