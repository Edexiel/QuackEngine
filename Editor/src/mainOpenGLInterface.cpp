#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Model.hpp"
#include "Maths/Matrix4.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Resources/Loaders/ModelLoader.hpp"

int main()
{
  GLFWwindow* window;
  unsigned int width = 1280, height = 720;
  /* Initialize the library */
  if (!glfwInit())
    return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(width, height, "RendererPlatform", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  //Create RendererPlatform
  Renderer::RendererPlatform interface;
  interface.SetProjectionMatrix(
      Maths::Matrix4::OrthoMatrix(width, height, -1.f, 100.f)*
                   Maths::Matrix4::Perspective(width, height, -1.f, 100.f, 3.14f/2.f)
                   );
  interface.SetViewMatrix(Maths::Matrix4::Identity());
  Renderer::Vertex triangle[] = {
      // positions          // texture coords
      {{0.0f,  1.0f, 0.0f}, {0,0,1}, {0.5f, 1.0f} },
      {{1.0f,  0.0f, 0.0f},{0,0,1}, {1.0f, 0.5f}},
      {{-1.0f, 0.0f, 0.0f}, {0,0,1}, {0.0f, 0.5f}}
  };

  const Renderer::Vertex quad[] = {
      // positions          // texture coords
      {{0.5f,  0.5f, 0.0f}, {0,0,1}, {1.0f, 1.0f}}, // top right
      {{0.5f, -0.5f, 0.0f}, {0,0,1}, {1.0f, 0.0f}}, // bottom right
      {{-0.5f, -0.5f, 0.0f}, {0,0,1}, {0.0f, 0.0f}}, // bottom left
      {{-0.5f,  0.5f, 0.0f}, {0,0,1}, {0.0f, 1.0f}}  // top left
    };

//ASSIMP
  Resources::ResourcesManager rm;
  Renderer::Model model;
  Resources::Loaders::ModelLoader ml(&model,"../../../fbx/Dragon_Baked_Actions_fbx_7.4_binary.fbx");
  Resources::Loaders::ModelLoader::ReadFile(&ml);
  unsigned int vao = interface.CreateVertices(ml.listMeshToLoad[2].data(), sizeof(float) * ml.listMeshToLoad[2].size());

  //indices classic
  unsigned int triangleIndices[] = {0, 1 ,2};
  unsigned int quadIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
      };

  unsigned int quadID = interface.CreateMesh(quad, sizeof(quad), quadIndices, sizeof(quadIndices));
  unsigned int triangleID = interface.CreateMesh(triangle, sizeof(triangle), triangleIndices, sizeof(triangleIndices));

  unsigned int size = sizeof(ml.listMeshToLoad[0].data()) / sizeof(float) * ml.listMeshToLoad[0].size();

  //Framebuffer
  Renderer::Framebuffer framebuffer(width, height);
  while (!glfwWindowShouldClose(window))
  {
    interface.ClearColor({0.2f,0.2f,0.2f,1.f});
    interface.Clear();
    interface.UseProgram();
    interface.SetModelMatrix(Maths::Matrix4::Translate({0,0,1}));
//    interface.DrawMesh(quadID);
    interface.DrawMesh(triangleID);
    interface.SetModelMatrix(Maths::Matrix4::Translate({0,0,1}));
    interface.DrawVertices(vao, size);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  framebuffer.Delete();
  interface.Delete();
  glfwTerminate();
  return 0;
}