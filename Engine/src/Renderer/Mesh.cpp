#include "Renderer/Mesh.hpp"
#include "Renderer/RendererPlatform.hpp"


using namespace Renderer;
Mesh::~Mesh()
{
  RendererPlatform::DeleteMesh(_vao,_vbo, _ebo);
}
void Mesh::Draw()
{
  RendererPlatform::DrawMesh(_vao, _nbVertices);
}
