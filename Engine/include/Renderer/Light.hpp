#ifndef _LIGHT_
#define _LIGHT_

#define MAX_POINT_LIGHT_NB 5
#define MAX_DIRECTIONAL_LIGHT_NB 5
#define MAX_SPOT_LIGHT_NB 5

#include "Maths/Vector3.hpp"
#include "Maths/Matrix4.hpp"

namespace Renderer
{
    enum class Light_Type{L_POINT, L_DIRECTIONAL, L_SPOT};

    class Light
    {
    public:

      Light(Light_Type lightType);

      Light_Type type = Light_Type::L_POINT;

      Maths::Matrix4 model = Maths::Matrix4::Identity();

      Maths::Color3f ambient   {0,0,0}; // colors of the lights
      Maths::Color3f diffuse   {0,0,0};
      Maths::Color3f specular  {0,0,0};

      float constant              {1.0f}; // use for attenuation
      float linear                {0.0f};
      float quadratic             {0.0f};
        
      float spotAngle             {0.0f}; // angle of the spot
      float outerSpotAngle        {0.0f}; // angle of the spot

      Maths::Vector3f GetDirection() const;
      Maths::Vector3f GetPosition () const;

  };
}

#endif