#include "Input/PlatformInputGLFW.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace Input;

PlatformInputGLFW::PlatformInputGLFW(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			PlatformInputGLFW* manager = static_cast<PlatformInputGLFW*>(glfwGetWindowUserPointer(window));
			manager->OnKeyEvent(key, scancode, action, mods);
		}
	);
	glfwSetCursorPosCallback(window,
		[](GLFWwindow* window, double xpos, double ypos)
		{
			PlatformInputGLFW* manager = static_cast<PlatformInputGLFW*>(glfwGetWindowUserPointer(window));
			manager->OnCursorPositionCallback(xpos, ypos);
		}
	);
	glfwSetMouseButtonCallback(window,
		[](GLFWwindow* window, int button, int action, int mods)
		{
			PlatformInputGLFW* manager = static_cast<PlatformInputGLFW*>(glfwGetWindowUserPointer(window));
			manager->OnMouseButtonCallback(button, action, mods);
		}
	);
	glfwSetScrollCallback(window,
		[](GLFWwindow* window, double xoffset, double yoffset)
		{
			PlatformInputGLFW* manager = static_cast<PlatformInputGLFW*>(glfwGetWindowUserPointer(window));
			manager->OnScrollCallback(xoffset, yoffset);
		}
	);
        _window = window;
}
void PlatformInputGLFW::OnKeyEvent(int key, int scancode, int action, int mods)
{
	if(keyEvent)
		keyEvent((Action)action, (Key)key);
}


void PlatformInputGLFW::OnMouseButtonCallback(int button, int action, int mods)
{
	if (MouseButtonEvent)
		MouseButtonEvent((Action)action,(MouseButton) button);
}

void PlatformInputGLFW::OnCursorPositionCallback(double xpos, double ypos)
{
	if (UpdateMousePosition)
		UpdateMousePosition(xpos, ypos);
}

void PlatformInputGLFW::OnScrollCallback(double xoffset, double yoffset)
{
	std::cout << "xoffset = " << xoffset << " yoffset = " << yoffset << std::endl;
}
void PlatformInputGLFW::PollEvents()
{
  glfwPollEvents();
}
void PlatformInputGLFW::UpdateCursorPosition(MousePosition &mousePosition)
{
  mousePosition.prevPos = mousePosition.pos;
  glfwGetCursorPos(_window, &mousePosition.pos.x,&mousePosition.pos.y);
}
