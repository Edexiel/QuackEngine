#ifndef QUACKENGINE_ICOSPHERE_HPP
#define QUACKENGINE_ICOSPHERE_HPP

#include "Maths/Vector3.hpp"
#include "Renderer/Vertex.hpp"
namespace Renderer {

struct MeshSlice {
  int start;
  int count;
};


class IcoSphere
{

public:
  IcoSphere(const VertexDescriptor& descriptor, void** verticesPtr, int* vertexCount);

  MeshSlice GenTriangle(int* startIndex);
  MeshSlice GenIcosphere(int* startIndex, int depth = 2);
  MeshSlice LoadObj(int* startIndex, const char* objFile, const char* mtlDir, float scale = 1.f);

private:
  int size;
  void** verticesPtr;
  int* vertexCount;

  void* GetDst(int* startIndex, int count);
  void* Grow(int count);
  static void ConvertVertices(void* dst, const Vertex* src, int count, const int descriptor);

  MeshSlice GenIcosphereFace(int* index, Maths::Vector3f a, Maths::Vector3f b, Maths::Vector3f c, int depth);
};
}

#endif // QUACKENGINE_ICOSPHERE_HPP
