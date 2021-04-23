#ifndef _SKELETALMESH_HPP
#define _SKELETALMESH_HPP

#include "Renderer/Mesh.hpp"

namespace Renderer
{
    class SkeletalMesh : Mesh
    {
        explicit SkeletalMesh(const Mesh& mesh);
    };
}

#endif //_SKELETALMESH_HPP
