#ifndef QUACKENGINE_RENDERERPLATFORM_HPP
#define QUACKENGINE_RENDERERPLATFORM_HPP

#include "Maths/Matrix4.hpp"
#include "Renderer/Mesh.hpp"
#include <vector>

namespace Renderer
{
struct Vertex
{
  float position[3];
  float normal[3];
  float uv[2];
};

class RendererPlatform
{
private:
  unsigned int _shaderProgram;
  std::vector<Mesh> _meshes;
  unsigned int _projectionLocation, _viewLocation, _modelLocation;

public:
  RendererPlatform();
  ~RendererPlatform() = default;

  void SetProjectionMatrix(const Maths::Matrix4& projectionMatrix);
  void SetViewMatrix(const Maths::Matrix4& viewMatrix);
  void SetModelMatrix(const Maths::Matrix4& modelMatrix);
  unsigned int CreateMesh(const Vertex* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
  unsigned int CreateVertices(const float* vertices, unsigned int verticesSize);
  void BindTexture(const unsigned int& texture);
  void ClearColor(const Maths::Vector4& color);
  void Clear();

  void DrawMesh(const unsigned int& mesh);
  void DrawVertices(unsigned int vertices, unsigned int nbVertices);
  void UseProgram();

  void Delete();
};
}

#endif // QUACKENGINE_RENDERERPLATFORM_HPP
