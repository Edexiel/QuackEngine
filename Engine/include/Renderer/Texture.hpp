#ifndef _TEXTURE_
#define _TEXTURE_

namespace Renderer
{
    struct Texture
    {
        int id;

        Texture(){};
        Texture(const int& _id);
        Texture(const char* path);
        ~Texture();    
    };
}

#endif //_TEXTURE_
