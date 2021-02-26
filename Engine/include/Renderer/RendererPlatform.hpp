#ifndef QUACKENGINE_RENDERERPLATFORM_HPP
#define QUACKENGINE_RENDERERPLATFORM_HPP

#include "Maths/Matrix4.hpp"


namespace Renderer
{
struct OpenGLInterfaceImp
{
  unsigned int  _program;
  unsigned int _vao, _vbo, _ebo;
  unsigned int _projectionLocation, _viewLocation, _modelLocation;
};
class RendererPlatform
{
private:

public:
  OpenGLInterfaceImp* impl;
  RendererPlatform();
  ~RendererPlatform();

  void SetProjectionMatrix(const Maths::Matrix4& projectionMatrix);
  void SetViewMatrix(const Maths::Matrix4& viewMatrix);
  void SetModelMatrix(const Maths::Matrix4& modelMatrix);

  void SetVertices(const float* vertices, const unsigned int& size);
  void SetIndices(const unsigned int* indices, const unsigned int& size);
  void NewFrame();

  void Delete();
};
}

#endif // QUACKENGINE_RENDERERPLATFORM_HPP
