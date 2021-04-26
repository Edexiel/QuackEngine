#ifndef _MESH_
#define _MESH_

typedef unsigned int Gluint;

#include "Renderer/Vertex.hpp"

namespace Renderer
{
  class Mesh
  {
  protected:
    unsigned int _vao {0};
    unsigned int _vbo {0};
    unsigned int _ebo {0};
    unsigned int _nbVertices {0};
    unsigned int _nbIndices {0};

    VertexType _vertexType {VertexType::V_CLASSIC};

  public:

      unsigned int materialIndex {0};

    Mesh() = default;
    Mesh(VertexType vertexType);
    Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbVertices, unsigned int nbIndices, VertexType vertexType)
            : _vao{vao},_vbo{vbo}, _ebo{ebo}, _nbVertices{nbVertices}, _nbIndices{nbIndices}, _vertexType{vertexType} {}
    ~Mesh();
    void Destroy();

    void Draw() const;

    unsigned int GetVAO() const;
    unsigned int GetVBO() const;
    unsigned int GetEBO() const;
    unsigned int GetNBVertices() const;
    unsigned int GetNBindices() const;

  };
}

#endif //_MESH_