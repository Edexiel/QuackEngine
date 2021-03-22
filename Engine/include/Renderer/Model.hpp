#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Renderer/Mesh.hpp"
#include "Renderer/Vertex.hpp"

namespace Renderer
{
    struct Model
    {

      Model() = default;
      Model(VertexType vertexType);

      std::vector<Mesh> meshList;

      static Model LoadModel(const char* path, VertexType vertexType = VertexType::V_CLASSIC);

      void Draw();

    private:

      VertexType _vertexType = VertexType::V_CLASSIC;

      static Model LoadClassicModel(const void* loadedScene);
      static Model LoadNormalMapModel(const void* loadedScene);

    };
}


#endif // _MODEL_