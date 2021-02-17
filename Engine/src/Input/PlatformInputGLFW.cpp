#include "PlatformInputGLFW.hpp"
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
}
void PlatformInputGLFW::OnKeyEvent(int key, int scancode, int action, int mods)
{
	keys[key] = (action == GLFW_PRESS);

	if(keyEvent)
		keyEvent(keys[key], (Key)key);
}