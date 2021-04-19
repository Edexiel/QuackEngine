#ifndef __PLATFORMINPUTGLFW_HPP__
#define __PLATFORMINPUTGLFW_HPP__

#include "Input/PlatformInput.hpp"

struct GLFWwindow;

namespace Input
{
    class PlatformInputGLFW : public PlatformInput
    {
    private:
        GLFWwindow *_window= nullptr;

        void OnKeyEvent(int key, int scancode, int action, int mods);
        void OnMouseButtonCallback(int button, int action, int mods);
        void OnCursorPositionCallback(double xpos, double ypos);
        void OnScrollCallback(double xoffset, double yoffset);

    public:
        explicit PlatformInputGLFW(GLFWwindow *window);

        void PollEvents() override;
        void UpdateCursorPosition(MousePosition &mousePosition) override;
    };
}

#endif