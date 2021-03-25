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
  for (std::pair<const std::string, std::vector<Key>> eventKey : _eventKeys)
  {
    for (Input::Key _key : eventKey.second)
    {
      for (std::pair<std::function<void()>, Action> function :
             _eventFuncs[eventKey.first])
      {
      if (_key == key && function.second == action)
        function.first();
      }
    }
  }
  for (std::pair<const std::string, std::vector<std::pair<Key, float>>> eventKeyAxis : _eventKeysAxis)
  {
    for (std::pair<Key,float> _key : eventKeyAxis.second)
    {
     for (std::function<void(float)> function : _eventFuncsAxis[eventKeyAxis.first])
     {
      if (_key.first == key && action == Action::PRESS)
        function(_key.second);
      else if(_key.first == key && action == Action::RELEASE)
        function(0);
     }
    }
  }
}

void InputManager::OnMouseButtonEvent(Action action, MouseButton button)
{
  for (std::pair<const std::string, std::vector<MouseButton>> eventMouseButton :
       _eventMouseButtons)
  {
    for (Input::MouseButton _button : eventMouseButton.second)
    {
      for (std::pair<std::function<void()>, Action> function :
           _eventFuncs[eventMouseButton.first])
        {
          if (_button == button && function.second == action)
            function.first();
        }
    }
  }
}

void InputManager::OnUpdateMousePositionEvent(const double xPos, const double yPos)
{
  //todo: Delete this function or make a boolean to choose between update each frame or update when the mouse move
}

void InputManager::BindEvent(const std::string& event, Key key)
{
	for (Key _key : _eventKeys[event])
	{
		if (_key == key)
		{
			std::cout << "This input already exist for this action!\n";
			return;
		}
	}

        _eventKeys[event].push_back(key);
}

void InputManager::BindEvent(const std::string& event, MouseButton button)
{
	for (MouseButton _button : _eventMouseButtons[event])
	{
		if (_button == button)
		{
			std::cout << "This input already exist for this action!\n";
			return;
		}
	}
        _eventMouseButtons[event].push_back(button);
}

void InputManager::BindEventAxis(const std::string& event, Key key, const float scale)
{
  _eventKeysAxis[event].push_back(std::pair<Key, float>(key, scale));
}

void InputManager::Update()
{
  platformInput.PollEvents();
  platformInput.UpdateCursorPosition(mousePosition);
}
