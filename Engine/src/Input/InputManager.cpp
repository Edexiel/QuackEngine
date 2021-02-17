#include "InputManager.hpp"

using namespace Input;

InputManager::InputManager(PlatformInput& platformInput)
	: platformInput(platformInput)
{
	platformInput.keyEvent = std::bind(&InputManager::OnKeyEvent, std::ref(*this), std::placeholders::_1, std::placeholders::_2);
}


void InputManager::OnKeyEvent(bool pressed, Key key)
{
	if (pressed && eventKeys["Jump"].at(0) == key)
		eventFuncs["Jump"]();
}

void InputManager::BindEvent(std::string event, Key key)
{
	eventKeys[event].push_back(key);
}

void InputManager::RegisterEvent(std::string event, std::function<void()> func)
{
	eventFuncs[event] = func;
}