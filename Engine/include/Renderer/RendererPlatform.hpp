#ifndef QUACKENGINE_RENDERERPLATFORM_HPP
#define QUACKENGINE_RENDERERPLATFORM_HPP

#include "Maths/Matrix4.hpp"
#include "Renderer/Mesh.hpp"
#include <vector>

namespace Renderer
{
struct RendererImp {
  unsigned int  _program;
  std::vector<Mesh> _meshes;
  unsigned int _projectionLocation, _viewLocation, _modelLocation;
};

class RendererPlatform
{
private:

public:
  RendererImp impl;
  RendererPlatform();
  ~RendererPlatform() = default;

  void SetProjectionMatrix(const Maths::Matrix4& projectionMatrix);
  void SetViewMatrix(const Maths::Matrix4& viewMatrix);
  void SetModelMatrix(const Maths::Matrix4& modelMatrix);
  unsigned int CreateMesh(const float* vertices, const unsigned int& verticesSize, const unsigned int* indices, const unsigned int indicesSize);
  void BindTexture(const unsigned int& texture);
  void NewFrame();

  void DrawMesh(const unsigned int& mesh);

  void Delete();
};
}

#endif // QUACKENGINE_RENDERERPLATFORM_HPP
