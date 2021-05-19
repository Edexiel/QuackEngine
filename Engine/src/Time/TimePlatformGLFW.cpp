#include "Time/TimePlatformGLFW.hpp"
#include "GLFW/glfw3.h"

using namespace Time;

double TimePlatformGLFW::GetTime() const
{
    return glfwGetTime();
}

void TimePlatformGLFW::SetTime(double time)
{
    glfwSetTime(time);
}
