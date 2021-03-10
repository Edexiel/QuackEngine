#ifndef QUACKENGINE_RENDERERPLATFORM_HPP
#define QUACKENGINE_RENDERERPLATFORM_HPP

#include "Maths/Matrix4.hpp"
#include <vector>

namespace Renderer
{
struct Vertex;
class Framebuffer;
class Shader;
class Mesh;
class Texture;

class RendererPlatform
{
public:

  static int LoadGL();
  static void ClearColor(const Maths::Vector4& color);
  static void Clear();

  static Mesh CreateMesh(const Vertex* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
  static Mesh CreateMesh(const float* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
  static void DrawMesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices);
  static void DeleteMesh(unsigned int vao, unsigned int vbo, unsigned int ebo);

  static void VerticesReading();

  static Shader CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
  static void UseShader(unsigned int shaderProgram);
  static void SetMatrix4(unsigned int shaderProgram, const char* name, const Maths::Matrix4& mat);
  static void DeleteShader(unsigned int shaderProgram);

  static Framebuffer CreateFramebuffer(unsigned int width, unsigned int height);
  static void BindFramebuffer(unsigned int ID);
  static void DeleteFramebuffer(unsigned int fbo, unsigned int rbo, unsigned int texture);

  static Texture CreateTexture();
  static void BindTexture(unsigned int texture);
  static void DeleteTexture(unsigned int texture);
  static void SetTextureImage2D(unsigned char *image, unsigned int nrChannels, unsigned int width, unsigned int height);
  static void TextureParameter();


  void DrawVertices(unsigned int vertices, unsigned int nbVertices);
};
}

#endif // QUACKENGINE_RENDERERPLATFORM_HPP
