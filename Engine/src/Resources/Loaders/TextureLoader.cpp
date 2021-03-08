#include "Resources/Loaders/TextureLoader.hpp"
#include "Renderer/Texture.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/gl.h"

using namespace Resources;
using namespace Loaders;
using namespace Renderer;

TextureLoader::TextureLoader(const Texture* texture, const char* _filePath, bool _antiAliasing) : bindTexture{texture->_ID}, filePath{_filePath}, antiAliasing {_antiAliasing} {}

void TextureLoader::ReadFile(TextureLoader* textureLoader)
{
    stbi_set_flip_vertically_on_load(true);
    textureLoader->data = stbi_load(textureLoader->filePath, &textureLoader->width, &textureLoader->height, &textureLoader->nrChannels, 0);
}

unsigned int TextureLoader::Apply()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, bindTexture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (antiAliasing)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    }
    
    // generate the texture
    if (data)
    {
        if (nrChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "can't open image : " << filePath << std::endl;
    }

    stbi_image_free(data);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bindTexture);
    glFlush();

    return bindTexture;
}