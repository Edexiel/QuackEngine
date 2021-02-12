#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

#include <vector>
#include <string>

#include "Maths/Vector3.hpp"

namespace Renderer
{
    class Model;
}

namespace Resources
{
    struct Vertex
    {
        Maths::Vector3 positions;
        Maths::Vector3 normals;
        Maths::Vector3 uvs;
    };

    class ModelLoader
    {
    private:

    std::string path;

    std::vector<std::vector<Vertex>> ToLoadMesh;

    public:
        ModelLoader(const Renderer::Model& model, const char* _path);
        ~ModelLoader(){};

        static void ReadFile(ModelLoader& modelLoader);
    };
}


#endif //_MODEL_LOADER_