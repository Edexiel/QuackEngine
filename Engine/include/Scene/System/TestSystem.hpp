//
// Created by gnisi on 25/03/2021.
//

#ifndef QUACKENGINE_TESTSYSTEM_HPP
#define QUACKENGINE_TESTSYSTEM_HPP

#include "Scene/Core/System.hpp"

class TestSystem : public System
{
public:
    TestSystem();
    void Init();
    void Update(float deltaTime);
    void FixedUpdate(float fixedUpdate);
};


#endif //QUACKENGINE_TESTSYSTEM_HPP
