#ifndef _VERTEX_HPP
#define _VERTEX_HPP

#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
namespace Renderer
{
  enum class VertexType{V_CLASSIC, V_NORMALMAP};

  struct Vertex
  {
    Maths::Vector3f position;
    Maths::Vector3f normal;
    Maths::Vector2f uv;
  };

  struct normalMapVertex : Vertex
  {
    Maths::Vector3f tangent;
    Maths::Vector3f biTangent;
  };
}

#endif // _VERTEX_HPP
