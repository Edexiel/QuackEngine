#ifndef _SHAPE_
#define _SHAPE_

#include "Renderer/Mesh.hpp"

namespace Renderer
{
    class Shape
    {
    public:
        static Mesh CreateQuad();
        static Mesh CreateCube();
        static Mesh CreateSphere(int sectorCount = 36, int stackCount = 18);
    };
}
#endif //_SHAPE_
