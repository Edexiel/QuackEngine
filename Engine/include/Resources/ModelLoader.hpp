#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

#include <vector>
#include <string>

namespace Resources
{
    class ModelLoader
    {
    private:

    std::string path;

    public:
        ModelLoader() {};
        ~ModelLoader(){};



        static void ReadFile(ModelLoader& modelLoader);
    };
}


#endif //_MODEL_LOADER_