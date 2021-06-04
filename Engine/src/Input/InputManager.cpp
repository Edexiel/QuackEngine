#include "Input/InputManager.hpp"
#include "Debug/Assertion.hpp"
#include "Debug/Log.hpp"

using namespace Input;

void InputManager::Init(PlatformInput* platformInput)
{
    _platformInput = platformInput;

    _platformInput->keyEvent = std::bind(&InputManager::OnKeyEvent, std::ref(*this), std::placeholders::_1,std::placeholders::_2);
    _platformInput->MouseButtonEvent = std::bind(&InputManager::OnMouseButtonEvent, std::ref(*this),std::placeholders::_1, std::placeholders::_2);
    _platformInput->UpdateMousePosition = std::bind(&InputManager::OnUpdateMousePositionEvent, std::ref(*this),std::placeholders::_1, std::placeholders::_2);

    InitInput();
}


void InputManager::OnKeyEvent(Action action, Key key)
{
    for (const std::pair<const std::string, std::vector<Key>> &eventKey : _eventKeys)
    {
        for (Input::Key _key : eventKey.second)
        {
            if(_eventFuncs[eventKey.first].first)
            {
                if (_key == key && _eventFuncs[eventKey.first].second == action)
                    _eventFuncs[eventKey.first].first();
            }
        }
    }
    //For axis event
    for (const std::pair<const std::string, std::vector<std::pair<Key, float>>> &eventKeyAxis : _eventKeysAxis)
    {
        for (std::pair<Key, float> _key : eventKeyAxis.second)
        {
            if(_eventFuncsAxis[eventKeyAxis.first])
            {
                    if (_key.first == key && action == Action::PRESS)
                        _eventFuncsAxis[eventKeyAxis.first](_key.second);
                    else if (_key.first == key && action == Action::RELEASE)
                        _eventFuncsAxis[eventKeyAxis.first](0);
            }
        }
    }
}

void InputManager::OnMouseButtonEvent(Action action, MouseButton button)
{
    for (const std::pair<const std::string, std::vector<MouseButton>> &eventMouseButton : _eventMouseButtons)
    {
        for (Input::MouseButton _button : eventMouseButton.second)
        {
            if(_eventFuncs[eventMouseButton.first].first)
            {
                if (_button == button && _eventFuncs[eventMouseButton.first].second == action)
                    _eventFuncs[eventMouseButton.first].first();
            }
        }
    }
}

void InputManager::OnUpdateMousePositionEvent(double xPos, double yPos)
{
    //todo: Delete this function or make a boolean to choose between update each frame or update when the mouse move
}

void InputManager::BindEvent(const std::string &event, Key key)
{
    for (Key _key : _eventKeys[event])
    {
        if (_key == key)
        {
            Log_Error("This input already exist for this action!");
            return;
        }
    }

    _eventKeys[event].push_back(key);
}

void InputManager::BindEvent(const std::string &event, MouseButton button)
{
    for (MouseButton _button : _eventMouseButtons[event])
    {
        if (_button == button)
        {
            Log_Error("This input already exist for this action!");
            return;
        }
    }
    _eventMouseButtons[event].push_back(button);
}

void InputManager::BindEventAxis(const std::string &event, Key key, float scale)
{
    _eventKeysAxis[event].push_back(std::pair<Key, float>(key, scale));
}

void InputManager::UnregisterEvent(const std::string &event)
{
    if(_eventFuncs[event].first)
        _eventFuncs.erase(event);
}

void InputManager::UnregisterEventAxis(const std::string &event)
{
    if(_eventFuncsAxis[event])
        _eventFuncsAxis.erase(event);
}

void InputManager::Update()
{
    Assert_Error(!_platformInput, "Plateform input not initialized");

    _platformInput->PollEvents();
    _platformInput->UpdateCursorPosition(mousePosition);
}

/**
 * Bind event. have to be replace by serialization.
 */

void InputManager::InitInput()
{
  BindEventAxis("CameraEditorMovementForward", Input::Key::KEY_W, 1.0f);
  BindEventAxis("CameraEditorMovementForward", Input::Key::KEY_S, -1.0f);
  BindEventAxis("CameraEditorMovementRight", Input::Key::KEY_D, 1.0f);
  BindEventAxis("CameraEditorMovementRight", Input::Key::KEY_A, -1.0f);
  BindEventAxis("CameraEditorMovementUp", Input::Key::KEY_SPACE, 1.0f);
  BindEventAxis("CameraEditorMovementUp", Input::Key::KEY_LEFT_CONTROL,-1.0f);

  BindEvent("Test unbind", Input::Key::KEY_SPACE);
}