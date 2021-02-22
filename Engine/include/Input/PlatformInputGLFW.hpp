#pragma once

#include "PlatformInput.hpp"

struct GLFWwindow;
namespace Input
{
  class PlatformInputGLFW : public PlatformInput
  {
    void OnKeyEvent(int key, int scancode, int action, int mods);
    void OnMouseButtonCallback(int button, int action, int mods);
    void OnCursorPositionCallback(double xpos, double ypos);
    void OnScrollCallback(double xoffset, double yoffset);

  public:
    PlatformInputGLFW(GLFWwindow* window);
    ~PlatformInputGLFW() = default;
  };
}