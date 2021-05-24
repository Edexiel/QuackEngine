#ifndef _TIMEPLATFORMGLFW_HPP
#define _TIMEPLATFORMGLFW_HPP

#include "Time/TimePlatform.hpp"

struct GLFWwindow;

namespace Time
{
    class TimePlatformGLFW : public TimePlatform
    {
        GLFWwindow *_window {nullptr};

    public:
        TimePlatformGLFW(GLFWwindow* window);

        double GetTime() const final;
        void SetTime(double time) final;
    };
}

#endif //_TIMEPLATFORMGLFW_HPP
