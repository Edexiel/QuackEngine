#ifndef _TEXTURE_
#define _TEXTURE_

namespace Renderer
{
    typedef unsigned int Gluint;

    struct Texture
    {
        unsigned int ID {0};

        Texture(){};
        Texture(const unsigned int& _ID);
        ~Texture(){};
    };
}

#endif //_TEXTURE_
