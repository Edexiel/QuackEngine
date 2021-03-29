#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Renderer/Mesh.hpp"
#include "Renderer/Vertex.hpp"

namespace Component
{
    struct Model
    {

      Model() = default;
      Model(Renderer::VertexType vertexType);

      std::vector<Renderer::Mesh> meshList;


      static Model LoadModel(const char* path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);

      void Draw();

    private:

        Renderer::VertexType _vertexType = Renderer::VertexType::V_CLASSIC;

      static Model LoadClassicModel(const void* loadedScene);
      static Model LoadNormalMapModel(const void* loadedScene);

    };
}


#endif // _MODEL_