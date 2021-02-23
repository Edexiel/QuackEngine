#ifndef _MESH_
#define _MESH_

typedef unsigned int Gluint;

namespace Renderer
{
    struct Mesh
    {
        Gluint buffer;
        unsigned int size;
    };
}

#endif //_MESH_