#include<glad/gl.h>
#include "Renderer/Mesh.hpp"

using namespace Renderer;

void Mesh::Delete()
{
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
}