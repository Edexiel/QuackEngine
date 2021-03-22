#ifndef _MESH_
#define _MESH_

typedef unsigned int Gluint;

#include "Renderer/Vertex.hpp"

namespace Renderer
{
  class Mesh
  {
  private:
    unsigned int _vao {0};
    unsigned int _vbo {0};
    unsigned int _ebo {0};
    unsigned int _nbVertices {0};
    unsigned int _nbIndices {0};
  public:
    Mesh() = default;
    Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbVertices, unsigned int nbIndices)
            : _vao{vao},_vbo{vbo}, _ebo{ebo}, _nbVertices{nbVertices}, _nbIndices{nbIndices} {}
    ~Mesh();

    void Draw(VertexType vertexType = VertexType::V_CLASSIC);
  };
}

#endif //_MESH_