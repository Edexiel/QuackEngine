#ifndef QUACKENGINE_RENDERERPLATFORM_HPP
#define QUACKENGINE_RENDERERPLATFORM_HPP

#include "Maths/Matrix4.hpp"
#include "Renderer/Mesh.hpp"

#include <vector>

namespace Renderer
{
struct Vertex;
class Framebuffer;

class RendererPlatform
{
public:
  RendererPlatform();
  ~RendererPlatform() = default;

  unsigned int CreateVertices(const float* vertices, unsigned int verticesSize);
  void BindTexture(const unsigned int& texture);
  void ClearColor(const Maths::Vector4& color);
  void Clear();

  static Mesh CreateMesh(const Vertex* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
  static void DrawMesh(const Mesh& mesh);
  static void DeleteMesh(Mesh& mesh);

  static unsigned int CreateProgramShader(const char* vertexShaderSource, const char* fragmentShaderSource);
  static void UseShader(unsigned int shaderProgram);
  static void SetMatrix4(unsigned int shaderProgram, const char* name, const Maths::Matrix4& mat);
  static void DeleteShader(unsigned int shaderProgram);

  static Framebuffer CreateFramebuffer(unsigned int width, unsigned int height);
  static void BindFramebuffer(unsigned int ID);

  static void DeleteBuffer(unsigned int buffer);
  static void DeleteTexture(unsigned int texture);

  void DrawVertices(unsigned int vertices, unsigned int nbVertices);
};
}

#endif // QUACKENGINE_RENDERERPLATFORM_HPP
