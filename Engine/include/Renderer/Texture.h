#ifndef QUACKENGINE_TEXTURE_H
#define QUACKENGINE_TEXTURE_H

#include <string>
#include <iostream>

namespace Shader
{
  class Texture
  {
  public:
    unsigned int nbTexture;
    std::string name {""};
    bool loaded{false};
    Texture() = default;
    Texture(const char *filename, bool antiAliasing = false);
    ~Texture();

    static unsigned int LoadTexture(const char *filename, bool antiAliasing = false);
    static void freeTexture(unsigned int &texture);
  };
}

#endif // QUACKENGINE_TEXTURE_H
