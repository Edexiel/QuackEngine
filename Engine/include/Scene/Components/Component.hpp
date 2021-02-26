//
// Created by g.nisi on 2/23/21.
//
#ifndef QUACKENGINE_COMPONENT_HPP
#define QUACKENGINE_COMPONENT_HPP

#include "Scene/Entity.hpp"

enum class Type
{
  Physics,
  Renderer,
  Script,
  Transform
};

class Component
{
  Entity entity;

  virtual void Start()=0;
  virtual void Stop()=0;
  virtual void Update()=0;
  virtual void Serialize()=0;
  virtual void Deserialize()=0;
};

#endif // QUACKENGINE_COMPONENT_HPP
