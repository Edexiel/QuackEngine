#include "Renderer/Light.hpp"

using namespace Renderer;

Maths::Vector3f Light::GetDirection() const
{
    //Maths::Vector3f direction = model * Maths::Vector4f{0.f, 0.f, 1.f, 0.f};
        return  {0,0,0};
}

Maths::Vector3f Light::GetPosition () const
{
  return {model.e[12], model.e[13], model.e[14]};
}