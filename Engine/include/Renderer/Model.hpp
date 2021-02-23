#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "../include/Renderer/Mesh.hpp"

namespace Renderer
{
    struct Model
    {
        std::vector<Mesh> meshList;
    };
}


#endif // _MODEL_