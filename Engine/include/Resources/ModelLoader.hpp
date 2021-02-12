#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

#include <vector>
#include <string>

#include "Vector3.hpp"

namespace Resources
{

    struct Vertex
    {
        Vector3 positions;
        Vector3 normals;
        Vector3 uvs;
    };

    class ModelLoader
    {
    private:

    std::string path;

    std::vector<std::vector<Vertex>> ToLoadMesh;

    public:
        ModelLoader() {};
        ~ModelLoader(){};

        static void ReadFile(ModelLoader& modelLoader);
    };
}


#endif //_MODEL_LOADER_