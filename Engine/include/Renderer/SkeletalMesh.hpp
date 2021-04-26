#ifndef _SKELETALMESH_HPP
#define _SKELETALMESH_HPP

#include "Renderer/Mesh.hpp"
#include "Maths/Matrix4.hpp"

namespace Renderer
{
    struct Bone
    {
        unsigned int id {};
        Maths::Matrix4 offset;
    };

    class SkeletalMesh : Mesh
    {
        SkeletalMesh() = default;
    };
}

#endif //_SKELETALMESH_HPP
