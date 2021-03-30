#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Renderer/Mesh.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Material.hpp"

namespace Component
{
    class Model
    {

        std::vector<Renderer::Mesh> _meshList;
        std::vector<Renderer::Material> _materialList;
        Renderer::VertexType _vertexType {Renderer::VertexType::V_CLASSIC};

        static Model LoadClassicModel(const void *loadedScene);
        static Model LoadNormalMapModel(const void *loadedScene);

    public:

        Model() = default;

        Model(Renderer::VertexType vertexType);

        static Model LoadModel(const char *path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);

        unsigned int AddMaterial(const Renderer::Material& newMaterial);
        void RemoveMaterial(unsigned int index);

        Renderer::Material& GetMaterial(unsigned int index);

        void Draw(const Maths::Matrix4& projection, const Maths::Matrix4& view, const Maths::Matrix4& transform);

    };
}


#endif // _MODEL_