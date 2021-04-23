#include <Renderer/Material.hpp>
#include "Renderer/Mesh.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Renderer/Vertex.hpp"


using namespace Renderer;

Mesh::Mesh(VertexType vertexType) //: _vertexType {vertexType}
{

}


Mesh::~Mesh()
{
  //RendererPlatform::DeleteMesh(_vao,_vbo, _ebo);
}

void Mesh::Draw() const
{
    switch (_vertexType)
    {
        case VertexType::V_NORMALMAP : return RendererPlatform::DrawMeshNormalMap(_vao, _vbo, _ebo, _nbIndices);
        default : return RendererPlatform::DrawMesh(_vao, _vbo, _ebo, _nbIndices);
    }
}

void Mesh::Draw(VertexType vertexType) const
{
    switch (vertexType)
    {
        case VertexType::V_NORMALMAP : return RendererPlatform::DrawMeshNormalMap(_vao, _vbo, _ebo, _nbIndices);
        default : return RendererPlatform::DrawMesh(_vao, _vbo, _ebo, _nbIndices);
    }
}
