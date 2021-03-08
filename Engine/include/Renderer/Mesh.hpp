#ifndef _MESH_
#define _MESH_

typedef unsigned int Gluint;

namespace Renderer
{
    class Mesh
    {
    public:
      Mesh() = default;
      Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbVertices): _vao{vao},_vbo{vbo},_ebo{ebo},_nbVertices{nbVertices}{}
      Gluint buffer;
      unsigned int size;

      unsigned int _vao, _vbo, _ebo, _nbVertices;

      void Delete();
      void Bonsoir();
    };
}

#endif //_MESH_