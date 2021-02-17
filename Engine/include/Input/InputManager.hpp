#pragma once

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

    std::map<std::string, std::function<void()>> eventFuncs;
    std::map<std::string, std::vector<Key>> eventKeys;

    void OnKeyEvent(bool pressed, Key key);

  public:
    InputManager(PlatformInput& platformInput);
    ~InputManager() = default;

    void BindEvent(std::string event, Key key);
    void RegisterEvent(std::string event, std::function<void()> func);
  };
}