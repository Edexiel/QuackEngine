#pragma once

#include "PlatformInput.hpp"

struct GLFWwindow;
namespace Input
{
  class PlatformInputGLFW : public PlatformInput
  {
    bool keys[(unsigned int)Key::KEY_COUNT]{ false };
    void OnKeyEvent(int key, int scancode, int action, int mods);

  public:
    PlatformInputGLFW(GLFWwindow* window);
    ~PlatformInputGLFW() = default;
  };
}