#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__


#include <map>
#include <iostream>
#include <functional>
#include <vector>
#include"PlatformInput.hpp"

namespace Input
{
  class InputManager
  {
  private:
    PlatformInput& platformInput;

    std::map<std::string, std::vector<std::function<void()>>> eventFuncs;

    std::map<std::string, std::vector<Key>> eventKeys;
    std::map<std::string, std::vector<MouseButton>> eventMouseButtons;
    std::map<std::string, Action> eventAction;

    

    void OnKeyEvent(Action action, Key key);
    void OnMouseButtonEvent(Action action, MouseButton button);
    void OnUpdateMousePositionEvent(const double xPos,const double yPos);

  public:
    InputManager(PlatformInput& platformInput);
    ~InputManager() = default;

    void BindEvent(std::string event, Key key, Action Action);
    void BindEvent(std::string event, MouseButton key, Action Action);
    template<typename C, typename F>
    void RegisterEvent(std::string event, C& classObject, F&& function);
    void Update();

    MousePosition mousePosition;
  };

  template<typename C, typename F>
  inline void InputManager::RegisterEvent(std::string event, C& classObject, F&& function)
  {
      eventFuncs[event].push_back(std::bind(function, classObject));
  }
}

#endif