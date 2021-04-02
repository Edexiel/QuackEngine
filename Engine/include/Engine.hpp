//
// Created by g.nisi on 3/9/21.
//

#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include "Input/PlatformInput.hpp"

class GLFWwindow;

class Engine
{
private:
    GLFWwindow *_window = nullptr;
public:
    Engine() = default;

    ~Engine() = default;

    void Init(Input::PlatformInput& input);

    void Update();
};


#endif //QUACKENGINE_ENGINE_HPP
