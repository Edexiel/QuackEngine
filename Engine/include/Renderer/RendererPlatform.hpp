#ifndef QUACKENGINE_RENDERERPLATFORM_HPP
#define QUACKENGINE_RENDERERPLATFORM_HPP

#include <vector>

#include "Maths/Matrix4.hpp"

#include "Renderer/Vertex.hpp"

namespace Component
{
    struct Light;
}
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

        static void CloseWindow();

        static int LoadGl();
        static void ClearColor(const Maths::Vector4f &color);
        static void Clear();
        static void EnableDepthBuffer(bool isEnable);
        static void PixelStore(float param);

        static void SetTransparency(bool transparency);

        static Mesh CreateMesh(const Vertex *vertices, unsigned int verticesSize, const unsigned int *indices,
                               unsigned int indicesSize, Renderer::VertexType vertexType);
        static Mesh CreateMesh(const float *vertices, unsigned int verticesSize, const unsigned int *indices,
                               unsigned int indicesSize, Renderer::VertexType vertexType);
        static void DrawMesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices);
        static void DrawMeshNormalMap(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices);
        static void DrawSkeletalMesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices);
        static void DeleteMesh(unsigned int vao, unsigned int vbo, unsigned int ebo);

        static void VerticesReading();
        static void VerticesReadingNormalMapping();
        static void VerticesReadingSkeletalMesh();


        // Shader

        static Shader CreateShader(const char *vertexShaderSource, const char *fragmentShaderSource);
        static void UseShader(unsigned int shaderProgram);
        static void DeleteShader(unsigned int shaderProgram);


        static void SetFloat(unsigned int shaderProgram, const char *name, float value);
        static void SetMatrix4(unsigned int shaderProgram, const char *name, const Maths::Matrix4 &mat);
        static void SetVector3f(unsigned int shaderProgram, const char *name, const Maths::Vector3f &vec);
        static void SetVector4f(unsigned int shaderProgram, const char *name, const Maths::Vector4f &vec);
        static void SetUint(unsigned int shaderProgram, const char *name, unsigned int value);
        static void SetSampler(unsigned int shaderProgram, const char *name, int value);

        static Framebuffer CreateFramebuffer(unsigned int width, unsigned int height);
        static void BindFramebuffer(unsigned int ID);
        static void ResizeFramebuffer(unsigned int fbo, unsigned int rbo, unsigned int texture, unsigned int width,
                                      unsigned int height);
        static void DeleteFramebuffer(unsigned int fbo, unsigned int rbo, unsigned int texture);

        static Texture CreateTexture();
        static void BindTexture(unsigned int texture, unsigned int index = 0);
        static void DeleteTexture(unsigned int texture);
        static void
        SetTextureImage2D(unsigned char *image, unsigned int nrChannels, unsigned int width, unsigned int height);
        static void TextureParameter();

        // Light

        static void SetSpotLight(unsigned int shaderID, unsigned int index, const Component::Light &light);
        static void SetDirectionalLight(unsigned int shaderID, unsigned int index, const Component::Light &light);
        static void SetPointLight(unsigned int shaderID, unsigned int index, const Component::Light &light);
    };
}

#endif // QUACKENGINE_RENDERERPLATFORM_HPP
