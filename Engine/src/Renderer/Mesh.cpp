#include "Renderer/Mesh.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Renderer/Vertex.hpp"


using namespace Renderer;
Mesh::~Mesh()
{
  //RendererPlatform::DeleteMesh(_vao,_vbo, _ebo);
}

void Mesh::Draw(VertexType vertexType)
{

    switch (vertexType)
    {
        case VertexType::V_NORMALMAP : return RendererPlatform::DrawMeshNormalMap(_vao, _vbo, _ebo, _nbIndices);
        default : return RendererPlatform::DrawMesh(_vao, _vbo, _ebo, _nbIndices);
    }
}
