#ifndef _MESH_
#define _MESH_

typedef unsigned int Gluint;

namespace Renderer
{
  struct Vertex;
    class Mesh
    {
    private:
      unsigned int _vao;
      unsigned int _vbo;
      unsigned int _ebo;
      unsigned int _nbVertices;
      unsigned int _nbIndices;
    public:
      Mesh() = default;
      Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbVertices, unsigned int nbIndices)
            : _vao{vao},_vbo{vbo}, _ebo{ebo}, _nbVertices{nbVertices}, _nbIndices{nbIndices} {}
      ~Mesh();

      void Draw();
    };
}

#endif //_MESH_