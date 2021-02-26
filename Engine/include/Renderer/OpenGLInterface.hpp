#ifndef QUACKENGINE_OPENGLINTERFACE_HPP
#define QUACKENGINE_OPENGLINTERFACE_HPP

class GLFWwindow;

namespace Renderer
{
class OpenGLInterface
{
public:
  OpenGLInterface(GLFWwindow* window);
  ~OpenGLInterface() = default;

  static GLFWwindow* InitWindow(const char* windowName, const unsigned int& width, const unsigned int& height);
  void Update(GLFWwindow* window);
};
}
#endif // QUACKENGINE_OPENGLINTERFACE_HPP
