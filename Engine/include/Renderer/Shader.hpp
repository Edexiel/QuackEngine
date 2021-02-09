#ifndef _SHADER_
#define _SHADER_

namespace Renderer
{
    struct Shader
    {
        int id;

        Shader(){};
        Shader(const int& _id);
        ~Shader(){};

    };
}

#endif //_SHADER_