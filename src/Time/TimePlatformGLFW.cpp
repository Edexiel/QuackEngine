#include "Time/TimePlatformGLFW.hpp"
#include "GLFW/glfw3.h"

#include <chrono>

using namespace Time;

TimePlatformGLFW::TimePlatformGLFW(GLFWwindow *window) : _window{window} {}

double TimePlatformGLFW::GetTime() const
{
    return glfwGetTime();
}

void TimePlatformGLFW::SetTime(double time)
{
    glfwSetTime(time);
}