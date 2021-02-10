#ifndef _TEXTURE_
#define _TEXTURE_

namespace Renderer
{
    typedef unsigned int Gluint;

    struct Texture
    {
        Gluint id;

        Texture(){};
        Texture(const unsigned& _id);
        ~Texture(){};
    };
}

#endif //_TEXTURE_
