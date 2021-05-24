#include "Renderer/ModelRenderer.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Engine.hpp"

#include "Debug/Assertion.hpp"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Skeleton.hpp"

#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

using namespace Resources;
using namespace Renderer;

ModelRenderer::ModelRenderer() : Asset(AssetType::A_MODEL)
{}

ModelRenderer::ModelRenderer(VertexType vertexType) : Asset(AssetType::A_MODEL), _vertexType{vertexType}
{}

void ModelRenderer::Destroy()
{
    for (const auto &i : _meshList)
    {
        i.Destroy();
    }
    _meshList.clear();
}

ModelRenderer ModelRenderer::LoadModel(const std::filesystem::path& path, VertexType vertexType)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_SortByPType |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_CalcTangentSpace);


    if (!scene)
    {
        fmt::print(fg(fmt::color::red), "[Model] Object can't be loaded: {}",path.string());

        return {};
    }

    ModelRenderer loadedModel;

    switch (vertexType)
    {
        case VertexType::V_SKELETAL :
            loadedModel = LoadSkeletalMeshModel(scene);
            break;
        case VertexType::V_NORMALMAP :
            loadedModel = LoadNormalMapModel(scene);
            break;
        default :
            loadedModel = LoadClassicModel(scene);
            break;
    }

    loadedModel.name = path;
    return loadedModel;
}

void ModelRenderer::ReLoadModel(ModelRenderer &model, const std::filesystem::path& path, Renderer::VertexType vertexType)
{
    model.Destroy();
    ModelRenderer newModel = LoadModel(path, vertexType);
    newModel._materialList = model._materialList;

    model = newModel;
}

void ModelRenderer::ReLoadModel(ModelRenderer &oldModel, ModelRenderer newModel)
{
    newModel._materialList = oldModel._materialList;
    oldModel = newModel;
}

ModelRenderer ModelRenderer::LoadClassicModel(const void *loadedScene)
{
    const aiScene *scene = (aiScene *) loadedScene;

    ModelRenderer model(VertexType::V_CLASSIC);
    model._meshList.resize(scene->mNumMeshes);

    unsigned int count;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices = LoadIndices(loadedScene, i);

        vertices.resize(scene->mMeshes[i]->mNumVertices * 8);

        // Load Vertices
        count = 0;
        for (unsigned int e = 0; e < scene->mMeshes[i]->mNumVertices; e++)
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
        model._meshList[i] = Renderer::RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(),
                                                                    indices.size(), VertexType::V_CLASSIC);
        RendererPlatform::VerticesReading();
    }
    return model;
}


ModelRenderer ModelRenderer::LoadNormalMapModel(const void *loadedScene)
{
    const aiScene *scene = (aiScene *) loadedScene;

    ModelRenderer model(VertexType::V_NORMALMAP);
    model._meshList.resize(scene->mNumMeshes);

    unsigned int count;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices = LoadIndices(loadedScene, i);


        // Load Vertices
        count = 0;
        for (unsigned int e = 0; e < scene->mMeshes[i]->mNumVertices; e++)
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
        model._meshList[i] = Renderer::RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(),
                                                                    indices.size(), Renderer::VertexType::V_NORMALMAP);
        RendererPlatform::VerticesReadingNormalMapping();
    }

    return model;
}

std::vector<unsigned int> ModelRenderer::LoadIndices(const void *loadedScene, unsigned int meshId)
{
    const aiScene *scene = (aiScene *) loadedScene;

    std::vector<unsigned int> indices;

    // Load indices
    for (unsigned int g = 0; g < scene->mMeshes[meshId]->mNumFaces; g++)
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

ModelRenderer ModelRenderer::LoadSkeletalMeshModel(const void *loadedScene)
{
    const aiScene *scene = (aiScene *) loadedScene;

    ModelRenderer model(VertexType::V_SKELETAL);
    model._meshList.resize(scene->mNumMeshes);

    unsigned int count;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        std::vector<SkeletalVertex> vertices;
        std::vector<unsigned int> indices = LoadIndices(loadedScene, i);

        vertices.resize(scene->mMeshes[i]->mNumVertices);

        // Load Vertices
        count = 0;
        for (unsigned int e = 0; e < scene->mMeshes[i]->mNumVertices; e++)
        {
            Maths::Vector3f position{(scene->mMeshes[i]->mVertices[e]).x,
                                     (scene->mMeshes[i]->mVertices[e]).y,
                                     (scene->mMeshes[i]->mVertices[e]).z};

            Maths::Vector3f normal{(scene->mMeshes[i]->mNormals[e]).x,
                                   (scene->mMeshes[i]->mNormals[e]).y,
                                   (scene->mMeshes[i]->mNormals[e]).z};

            Maths::Vector2f texture;

            if (scene->mMeshes[i]->HasTextureCoords(0))
            {
                texture = {(scene->mMeshes[i]->mTextureCoords[0][e]).x,
                           (scene->mMeshes[i]->mTextureCoords[0][e]).y};
            }

            vertices[e] = {position, normal, texture};

            ExtractBoneWeightForVertices(vertices, i, scene);
        }

        // Put loaded data in buffers
        model._meshList[i] = Renderer::RendererPlatform::CreateMesh((float *) vertices.data(),
                                                                    vertices.size() * sizeof(SkeletalVertex) /
                                                                    sizeof(float),
                                                                    indices.data(), indices.size(),
                                                                    Renderer::VertexType::V_SKELETAL);
        RendererPlatform::VerticesReadingSkeletalMesh();
    }

    return model;
}

void ModelRenderer::SetVertexBoneData(SkeletalVertex &vertex, int boneID, float weight)
{
    for (int i = 0; i < 4; ++i)
    {
        if (vertex.boneId.e[i] == -1)
        {
            vertex.weights.e[i] = weight;
            vertex.boneId.e[i] = boneID;
            break;
        }
    }
}

void ModelRenderer::ExtractBoneWeightForVertices(std::vector<Renderer::SkeletalVertex> &vertices,
                                                 unsigned int meshId,
                                                 const void *loadedScene)
{
    const aiScene *scene = (aiScene *) loadedScene;
    aiMesh *mesh = scene->mMeshes[meshId];

    int boneCounter = 0;

    std::unordered_map<std::string, int> _skeleton;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (_skeleton.find(boneName) == _skeleton.end())
        {
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

        for (unsigned int i = 0; i < mesh->mBones[boneIndex]->mNumWeights; i++)
        {
            SetVertexBoneData(vertices[weights[i].mVertexId], boneID, weights[i].mWeight);
        }
    }
}

unsigned int ModelRenderer::AddMaterial(const MaterialInterface &newMaterial)
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

void ModelRenderer::RemoveMaterial(unsigned int index)
{
    _materialList.erase(_materialList.cbegin() + index);

    for (auto &i : _meshList)
    {
        if (i.materialIndex >= _meshList.size())
        {
            i.materialIndex = 0;
        }
    }
}

Renderer::MaterialInterface &ModelRenderer::GetMaterial(unsigned int index)
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

void ModelRenderer::Draw(const Maths::Matrix4 &projection, const Maths::Matrix4 &view, const Maths::Matrix4 &transform)
{
    for (auto &i : _meshList)
    {
        Renderer::MaterialInterface &material = _materialList[i.materialIndex];

        material->Apply();

        material->shader.SetMatrix4("projection", projection);
        material->shader.SetMatrix4("view", view);
        material->shader.SetMatrix4("model", transform);

        i.Draw();
    }
}

unsigned int ModelRenderer::ChangeMaterial(const MaterialInterface &newMaterial, unsigned int index)
{
    if ((index >= _materialList.size()))
    {
        Assert_Warning(true, "The material index in model is invalid");
        return 0;
    }

    _materialList[index] = newMaterial;
    return index;
}

void ModelRenderer::SetMeshMaterial(unsigned int meshIndex, unsigned int materialIndex)
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

const Renderer::Mesh &ModelRenderer::GetMesh(unsigned int index) const
{
    if (index >= _meshList.size())
    {
        Assert_Error(true, "Invalid mesh index");
        //todo: urgent à fix
        return _meshList[0];
    }
    return _meshList[index];
}

unsigned int *ModelRenderer::GetMeshMaterialIndex(unsigned int index)
{
    if (index >= _meshList.size())
    {
        Assert_Error(true, "Invalid mesh index");
        return nullptr;
    }
    return &_meshList[index].materialIndex;
}

unsigned int ModelRenderer::GetNumberMesh() const
{
    return _meshList.size();
}

unsigned int ModelRenderer::GetNumberMaterial() const
{
    return _materialList.size();
}

Renderer::VertexType ModelRenderer::GetVertexType() const
{
    return _vertexType;
}