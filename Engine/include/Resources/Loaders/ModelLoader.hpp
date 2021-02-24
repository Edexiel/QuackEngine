#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

#include <vector>
#include <string>

#include "Maths/Vector3.hpp"

typedef float GLfloat;

namespace Renderer
{
    class Model;
}

namespace Resources
{
    namespace Loaders
    {

        class ModelLoader
        {
        private:
            std::string path;
            std::vector<std::vector<float>> listMeshToLoad;

            Renderer::Model* model;

        public:
            ModelLoader(Renderer::Model* _model, const char* _path);
            ~ModelLoader(){};

            static void ReadFile(ModelLoader* modelLoader);
            void Apply();

        };
    }
}


#endif //_MODEL_LOADER_