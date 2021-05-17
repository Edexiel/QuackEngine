#include "Renderer/IcoSphere.hpp"
#include "Renderer/Vertex.hpp"
#include "Maths/Vector3.hpp"

#include <cmath>

#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

using namespace Maths;
using namespace Renderer;

MeshSlice IcoSphere::GenIcosphere(int *startIndex, int depth) {
  // Create iscosahedron positions (radius = 1)
  float t = 1.f + sqrtf(5.f) / 2.f; // Golden ratio
  float h = t;
  float w = 1.f;

  Vector3f positions[]
      {
          {-w, h, 0.f },
          { w, h, 0.f },
          {-w,-h, 0.f },
          { w,-h, 0.f },

          { 0.f,-w, h },
          { 0.f, w, h },
          { 0.f,-w,-h },
          { 0.f, w,-h },

          { h, 0.f,-w },
          { h, 0.f, w },
          {-h, 0.f,-w },
          {-h, 0.f, w },
      };

  // Triangles
  int indices[] =
      {
          0, 11,  5,
          0,  5,  1,
          0,  1,  7,
          0,  7, 10,
          0, 10, 11,

          1,  5,  9,
          5, 11,  4,
          11, 10,  2,
          10,  7,  6,
          7,  1,  8,

          3,  9,  4,
          3,  4,  2,
          3,  2,  6,
          3,  6,  8,
          3,  8,  9,

          4,  9,  5,
          2,  4, 11,
          6,  2, 10,
          8,  6,  7,
          9,  8,  1,
      };

  int count = (int)(ARRAYSIZE(indices) * powf(4, (float)depth));
  void* buffer = GetDst(startIndex, count);
  int index = *vertexCount - count;
  int indexTmp = index;

  for (int i = 0; i < ARRAYSIZE(indices); i += 3)
    GenIcosphereFace(&indexTmp, positions[indices[i+0]], positions[indices[i+1]], positions[indices[i+2]], depth);

  return { index, count };
}
void *IcoSphere::GetDst(int *startIndex, int count)
{
  void* dst;

  // todo: Check space is sufficient if startIndex is set
  if (startIndex)
    dst = (unsigned char*)(*verticesPtr) + *startIndex * size;
  else
    dst = Grow(count);

  return dst;
}
void *IcoSphere::Grow(int count)
{
  int oldCount = *vertexCount;
  *vertexCount += count;
  void* newPtr = realloc(*verticesPtr, *vertexCount * size);
  *verticesPtr = newPtr;

  return (unsigned char*)*verticesPtr + (oldCount * size);
}
MeshSlice IcoSphere::GenIcosphereFace(int *index, Maths::Vector3f a,
                                      Maths::Vector3f b, Maths::Vector3f c,
                                      int depth)
{
  int startIndex = *index;
  if (depth == 0)
  {
    a.Normalize();
    b.Normalize();
    c.Normalize();

    Vertex vertices[] =
        {
            { a * 0.5f, a, { 0.f, 0.f }},
            { b * 0.5f, b, { 0.f, 0.f }},
            { c * 0.5f, c, { 0.f, 0.f }},
        };
    int count = ARRAYSIZE(vertices);
    ConvertVertices(GetDst(index, count), vertices, count, size);
    *index += count;
  }
  else
  {
    Vector3f mab = a + (b-a) * 0.5f;
    Vector3f mbc = b + (c-b) * 0.5f;
    Vector3f mca = c + (a-c) * 0.5f;

    GenIcosphereFace(index, a, mab, mca, depth-1);
    GenIcosphereFace(index, b, mbc, mab, depth-1);
    GenIcosphereFace(index, c, mca, mbc, depth-1);
    GenIcosphereFace(index, mab, mbc, mca, depth-1);
  }

  return { startIndex, *index - startIndex };
}
void IcoSphere::ConvertVertices(void *dst, const Vertex *src, int count,
                                const int size)
{
  unsigned char* dstBuffer = (unsigned char*)dst;
  for (int i = 0; i < count; ++i)
  {
    const Vertex* srcVertex = src + i;
    unsigned char* vertexStart = dstBuffer + (i * size);
  }
}
