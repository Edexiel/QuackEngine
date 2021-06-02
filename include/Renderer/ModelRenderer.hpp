#ifndef QUACKENGINE_MODELRENDERER_HPP
#define QUACKENGINE_MODELRENDERER_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <filesystem>

#include "Renderer/Mesh.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Skeleton.hpp"
#include "Resources/Asset.hpp"

#include "Scene/Core/Types.hpp"


namespace Renderer
{
    class ModelRenderer : public Resources::Asset
    {

        std::vector<Renderer::Mesh> _meshList;
        std::vector<Renderer::MaterialInterface> _materialList;

        //SkeletonOffset _skeletonOffset;

    public:
        const std::vector<Renderer::MaterialInterface> &GetMaterialList() const;
    private:

        static std::vector<unsigned int> LoadIndices(const void *loadedScene, unsigned int meshId);

        static ModelRenderer LoadClassicModel(const void *loadedScene);
        static ModelRenderer LoadNormalMapModel(const void *loadedScene);
        static ModelRenderer LoadSkeletalMeshModel(const void *loadedScene);

        void LoadSkeleton(const void* meshAssimp);

        static void SetVertexBoneData(Renderer::SkeletalVertex &vertex, int boneID, float weight);
        static void ExtractBoneWeightForVertices(std::vector<Renderer::SkeletalVertex> &vertices,
                                                 unsigned int meshId,
                                                 const void *loadedScene);

    public:

        std::unordered_map<std::string, Renderer::Bone> _skeleton;
        Renderer::VertexType _vertexType{Renderer::VertexType::V_CLASSIC};


        ModelRenderer();
        ModelRenderer(Renderer::VertexType vertexType);

        void Destroy();

        static ModelRenderer LoadModel(const std::filesystem::path& path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);
        static void ReLoadModel(ModelRenderer &model, const std::filesystem::path& path, Renderer::VertexType vertexType);
        static void ReLoadModel(ModelRenderer &oldModel, ModelRenderer newModel);

        unsigned int AddMaterial(const Renderer::MaterialInterface &newMaterial);
        unsigned int ChangeMaterial(const Renderer::MaterialInterface &newMaterial, unsigned int index);
        void RemoveMaterial(unsigned int index);

        void SetMeshMaterial(unsigned int meshIndex, unsigned int materialIndex);

        Renderer::MaterialInterface &GetMaterial(unsigned int index);

        void Draw(const Maths::Matrix4 &projection, const Maths::Matrix4 &view, const Maths::Matrix4 &transform);

        const Renderer::Mesh &GetMesh(unsigned int index) const;
        unsigned int *GetMeshMaterialIndex(unsigned int index);
        unsigned int GetNumberMesh() const;
        unsigned int GetNumberMaterial() const;
        Renderer::VertexType GetVertexType() const;

    };
}
#endif //QUACKENGINE_MODELRENDERER_HPP
