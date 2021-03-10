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
    public:
      Mesh() = default;
      Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbVertices): _vao{vao},_vbo{vbo},_ebo{ebo},_nbVertices{nbVertices}{}
      ~Mesh();

      void Draw();
      Gluint buffer;
      unsigned int size;

    };
}

#endif //_MESH_