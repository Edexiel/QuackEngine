#ifndef _MODEL_
#define _MODEL_

#include <string>

namespace Renderer
{
    struct Model
    {
        int id;

        Model(){};
        Model(const int& _id);
        ~Model(){};
    };
}


#endif // _MODEL_