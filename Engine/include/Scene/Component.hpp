//
// Created by g.nisi on 2/23/21.
//

#ifndef QUACKENGINE_COMPONENT_HPP
#define QUACKENGINE_COMPONENT_HPP

#include "Scene/Entity.hpp"
#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>

struct Transform
{
  Maths::Vector3 position;
  Maths::Vector3 scale;
  Maths::Quaternion rotation;
};

enum class Type
{
  E_STATIC,
  E_DYNAMIC
};

class Component
{
  Entity entity;
};

#endif // QUACKENGINE_COMPONENT_HPP
