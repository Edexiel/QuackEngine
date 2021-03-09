#ifndef _MESH_
#define _MESH_

typedef unsigned int Gluint;

namespace Renderer
{
    class Mesh
    {
    public:
      Mesh() = default;
      Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbVertices, unsigned int nbIndices):
            _vao{vao},_vbo{vbo},_ebo{ebo},_nbVertices{nbVertices}, _nbIndices{nbIndices} {}

      unsigned int _vao, _vbo, _ebo, _nbVertices, _nbIndices;

      void Delete();
    };
}

#endif //_MESH_