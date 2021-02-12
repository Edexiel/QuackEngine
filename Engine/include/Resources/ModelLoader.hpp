#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

#include <vector>
#include <string>

namespace Resources
{

    /*struct Vertex
    {
        positions;
        normals;
        uvs;
    };*/

    class ModelLoader
    {
    private:

    std::string path;

    //std::vector<std::vector<Vertex>> ToLoadMesh;

    public:
        ModelLoader() {};
        ~ModelLoader(){};

        static void ReadFile(ModelLoader& modelLoader);
    };
}


#endif //_MODEL_LOADER_