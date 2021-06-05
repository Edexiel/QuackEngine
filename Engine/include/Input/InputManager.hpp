#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__


#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <vector>
#include "PlatformInput.hpp"

namespace Input
{
    class InputManager
    {
    private:
        PlatformInput *_platformInput = nullptr;

        std::unordered_map<std::string, std::pair<std::function<void()>, Action>> _eventFuncs;
        std::unordered_map<std::string, std::function<void(float)>> _eventFuncsAxis;

        std::unordered_map<std::string, std::vector<Key>> _eventKeys;
        std::unordered_map<std::string, std::vector<std::pair<Key, float>>> _eventKeysAxis;
        std::unordered_map<std::string, std::vector<MouseButton>> _eventMouseButtons;

        void OnKeyEvent(Action action, Key key);
        void OnMouseButtonEvent(Action action, MouseButton button);
        void OnUpdateMousePositionEvent(double xPos, double yPos);
        void InitInput();// todo: Remove this function by serialisation of BindEvent

    public:
        InputManager() = default;

        void Init(PlatformInput *platformInput);
        void BindEvent(const std::string &event, Key key);
        void BindEvent(const std::string &event, MouseButton key);
        void BindEventAxis(const std::string &event, Key key, float scale);

        template<typename C, typename F>
        void RegisterEvent(const std::string &event, Action action, C *classObject, F &&function);
        void UnregisterEvent(const std::string &event);

        template<typename C, typename F>
        void RegisterEventAxis(const std::string &event, C *classObject, F &&function);
        void UnregisterEventAxis(const std::string &event);
        void Update();

        void Clear();

        MousePosition mousePosition;
    };

    template<typename C, typename F>
    inline void InputManager::RegisterEvent(const std::string &event, Action action, C *classObject, F &&function)
    {
        if(!_eventFuncs[event].first)
            _eventFuncs[event] = std::pair<std::function<void()>, Action>(std::bind(function, classObject), action);
    }


    template<typename C, typename F>
    inline void InputManager::RegisterEventAxis(const std::string &event, C *classObject, F &&function)
    {
        if(!_eventFuncsAxis[event])
            _eventFuncsAxis[event] = std::bind(function, classObject, std::placeholders::_1);
    }
}

#endif