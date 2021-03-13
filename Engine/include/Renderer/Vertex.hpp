#ifndef _VERTEX_HPP
#define _VERTEX_HPP

#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
namespace Renderer
{
struct Vertex
{
  Maths::Vector3f position;
  Maths::Vector3f normal;
  Maths::Vector2f uv;
};
}

#endif // _VERTEX_HPP
