#ifndef _MODEL_
#define _MODEL_

#include <vector>

namespace Renderer
{

    struct Mesh;

    struct Model
    {
        std::vector<Mesh*> meshList;
    };
}


#endif // _MODEL_