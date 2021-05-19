#ifndef QUACKENGINE_MODEL_HPP
#define QUACKENGINE_MODEL_HPP

#include <vector>

#include "Renderer/Mesh.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Material.hpp"

#include "Renderer/Skeleton.hpp"

#include "Scene/Core/Types.hpp"
#include <cereal/access.hpp>

#include "Resources/Asset.hpp"

#include <memory>
#include <unordered_map>
#include <filesystem>

namespace Resources
{
    class Model : public Asset
    {

        std::vector<Renderer::Mesh> _meshList;
        std::vector<Renderer::MaterialInterface> _materialList;
        Renderer::VertexType _vertexType{Renderer::VertexType::V_CLASSIC};

        static std::vector<unsigned int> LoadIndices(const void *loadedScene, unsigned int meshId);

        static Model LoadClassicModel(const void *loadedScene);
        static Model LoadNormalMapModel(const void *loadedScene);
        static Model LoadSkeletalMeshModel(const void *loadedScene);

        static void SetVertexBoneData(Renderer::SkeletalVertex &vertex, int boneID, float weight);
        static void ExtractBoneWeightForVertices(std::vector<Renderer::SkeletalVertex> &vertices,
                                                 unsigned int meshId,
                                                 const void *loadedScene);

    public:

        std::unordered_map<std::string, Renderer::Bone> _skeleton;

        Model();
        Model(Renderer::VertexType vertexType);

        void Destroy();

        static Model LoadModel(const std::filesystem::path& path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);
        static void ReLoadModel(Model &model, const std::filesystem::path& path, Renderer::VertexType vertexType);
        static void ReLoadModel(Model &oldModel, Model newModel);

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
#endif //QUACKENGINE_MODEL_HPP
