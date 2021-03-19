#include "Input/InputManager.hpp"

using namespace Input;

InputManager::InputManager(PlatformInput& platformInput)
	: platformInput(platformInput)
{
	platformInput.keyEvent = std::bind(&InputManager::OnKeyEvent, std::ref(*this), std::placeholders::_1, std::placeholders::_2);
	platformInput.MouseButtonEvent = std::bind(&InputManager::OnMouseButtonEvent, std::ref(*this), std::placeholders::_1, std::placeholders::_2);
	platformInput.UpdateMousePosition = std::bind(&InputManager::OnUpdateMousePositionEvent, std::ref(*this), std::placeholders::_1, std::placeholders::_2);
}


void InputManager::OnKeyEvent(Action action, Key key)
{
	for (std::pair<const std::string, std::vector<Key>> eventKey : eventKeys)
	{
		for (Input::Key _key : eventKey.second)
		{
			if (action == eventAction[eventKey.first] && _key == key)
				for (std::function<void()> func : eventFuncs[eventKey.first])
				{
					func();
				}
		}
	}
}

void Input::InputManager::OnMouseButtonEvent(Action action, MouseButton button)
{
	for (std::pair<const std::string, std::vector<MouseButton>> eventMouseButton : eventMouseButtons)
	{
		for (Input::MouseButton _button : eventMouseButton.second)
		{
			if (action == eventAction[eventMouseButton.first] && _button == button)
				for (std::function<void()> func : eventFuncs[eventMouseButton.first])
				{
					func();
				}
		}
	}
}

void Input::InputManager::OnUpdateMousePositionEvent(const double xPos, const double yPos)
{
	mousePosition.oldPos = mousePosition.pos;
	mousePosition.pos = {xPos, yPos};

        std::cout << "oldPos.x = " << mousePosition.oldPos.x << " oldPos.y = " << mousePosition.oldPos.y << std::endl;
        std::cout << "pos.x = " << mousePosition.pos.x << " pos.y = " << mousePosition.pos.y << std::endl;
}

void InputManager::BindEvent(std::string event, Key key, Action Action)
{
	for (Key _key : eventKeys[event])
	{
		if (_key == key)
		{
			std::cout << "This input already exist for this action!\n";
			return;
		}
	}

	eventKeys[event].push_back(key);
	eventAction[event] = Action;
}

void Input::InputManager::BindEvent(std::string event, MouseButton button, Action Action)
{
	for (MouseButton _button : eventMouseButtons[event])
	{
		if (_button == button)
		{
			std::cout << "This input already exist for this action!\n";
			return;
		}
	}
	eventMouseButtons[event].push_back(button);
	eventAction[event] = Action;
}
