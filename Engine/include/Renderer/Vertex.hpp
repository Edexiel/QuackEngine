#ifndef _VERTEX_HPP
#define _VERTEX_HPP

#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
namespace Renderer
{
struct Vertex
{
  Maths::Vector3 position;
  Maths::Vector3 normal;
  Maths::Vector2 uv;
};
}

#endif // _VERTEX_HPP
