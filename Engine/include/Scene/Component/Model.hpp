#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Renderer/Mesh.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Material.hpp"

#include "Scene/Core/Types.hpp"

namespace Component
{
    class Model
    {

        std::vector<Renderer::Mesh> _meshList;
        std::vector<Renderer::MaterialInterface> _materialList;
        Renderer::VertexType _vertexType {Renderer::VertexType::V_CLASSIC};

        static Model LoadClassicModel(const void *loadedScene);
        static Model LoadNormalMapModel(const void *loadedScene);

    public:

        Model() = default;

        Model(Renderer::VertexType vertexType);

        //Entity entity;

        static Model LoadModel(const char *path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);

        unsigned int AddMaterial(const Renderer::MaterialInterface& newMaterial);
        unsigned int ChangeMaterial(const Renderer::MaterialInterface& newMaterial, unsigned int index);
        void RemoveMaterial(unsigned int index);

        //void SetMaterial(const Renderer::MaterialInterface & newMaterial, unsigned int index);

        void SetMeshMaterial(unsigned int meshIndex, unsigned int materialIndex);

        Renderer::MaterialInterface& GetMaterial(unsigned int index);

        void Draw(const Maths::Matrix4& projection, const Maths::Matrix4& view, const Maths::Matrix4& transform);

        const Renderer::Mesh& GetMesh(unsigned int index) const;
        unsigned int GetNumberMesh() const;
        Renderer::VertexType GetVertexType() const;

    };
}


#endif // _MODEL_