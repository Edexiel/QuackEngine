#ifndef QUACKENGINE_OPENGLINTERFACE_HPP
#define QUACKENGINE_OPENGLINTERFACE_HPP

#include "Maths/Matrix4.hpp"


namespace Renderer
{
struct OpenGLInterfaceImp
{
  unsigned int _vao, _vbo, _ebo, _program;
  Maths::Matrix4 _projectionMatrix, _viewMatrix, _modelMatrix;
};
class OpenGLInterface
{
private:

public:
  OpenGLInterfaceImp* impl;
  OpenGLInterface();
  ~OpenGLInterface();

  void SetProjectionMatrix(const Maths::Matrix4& projectionMatrix);
  void SetViewMatrix(const Maths::Matrix4& viewMatrix);
  void SetModelMatrix(const Maths::Matrix4& modelMatrix);

  void SetVertices(const float* vertices, const unsigned int& size);
  void SetIndices(const unsigned int* indices, const unsigned int& size);
  void NewFrame();

  void Delete();
};
}

#endif // QUACKENGINE_OPENGLINTERFACE_HPP
