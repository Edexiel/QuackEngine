#ifndef _LIGHT_
#define _LIGHT_

#define MAX_POINT_LIGHT_NB 5
#define MAX_DIRECTIONAL_LIGHT_NB 5
#define MAX_SPOT_LIGHT_NB 5

#include "Maths/Vector3.hpp"
#include "Maths/Matrix4.hpp"

namespace Component
{
    enum class Light_Type{L_POINT, L_DIRECTIONAL, L_SPOT};

    struct Light
    {
      Light_Type type {Light_Type::L_POINT};

      Maths::Vector3f position {0.f, 0.f, 0.f};
      Maths::Vector3f direction {0.f, 0.f, 0.f};

      Maths::Color3f ambient   {0,0,0}; // colors of the lights
      Maths::Color3f diffuse   {0,0,0};
      Maths::Color3f specular  {0,0,0};

      float constant              {1.0f}; // use for attenuation
      float linear                {0.0f};
      float quadratic             {0.0f};
        
      float spotAngle             {0.0f}; // angle of the spot
      float outerSpotAngle        {0.0f};

  };
}

#endif