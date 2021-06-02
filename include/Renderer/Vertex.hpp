#ifndef _VERTEX_HPP
#define _VERTEX_HPP

#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"

namespace Renderer
{
  enum class VertexType{V_CLASSIC, V_NORMALMAP, V_SKELETAL};

  struct Vertex
  {
    Maths::Vector3f position    {0.f,0.f,0.f};
    Maths::Vector3f normal      {0.f,0.f,0.f};
    Maths::Vector2f uv          {0.f,0.f};
  };

  struct NormalMapVertex
  {
      Maths::Vector3f position  {0.f,0.f,0.f};
      Maths::Vector3f normal    {0.f,0.f,0.f};
      Maths::Vector2f uv        {0.f,0.f};

      Maths::Vector3f tangent   {0.f,0.f,0.f};
      Maths::Vector3f biTangent {0.f,0.f,0.f};
  };

  struct SkeletalVertex
  {
      Maths::Vector3f position  {0.f,0.f,0.f};
      Maths::Vector3f normal    {0.f,0.f,0.f};
      Maths::Vector2f uv        {0.f,0.f};

      Maths::Vector4<int> boneId    {-1,-1,-1,-1};
      Maths::Vector4f weights   {0.f,0.f,0.f,0.f};
  };
}

#endif // _VERTEX_HPP
