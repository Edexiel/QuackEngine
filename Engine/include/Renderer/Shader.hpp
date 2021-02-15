#ifndef _SHADER_
#define _SHADER_

namespace Renderer
{
    struct Shader
    {
        unsigned int ID;

        Shader(){};
        Shader(const unsigned int& _ID);
        ~Shader(){};

    };
}

#endif //_SHADER_