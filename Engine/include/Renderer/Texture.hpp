/*#ifndef _TEXTURE_
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

#endif //_TEXTURE_*/

#ifndef QUACKENGINE_TEXTURE_HPP
#define QUACKENGINE_TEXTURE_HPP

#include <string>
#include <iostream>

namespace Renderer
{
class Texture
{
  std::string _name{""};
public:
  unsigned int _ID{0};

  bool loaded{false};
  Texture() = default;
  Texture(const unsigned int& _ID);
  Texture(const char *filename, bool antiAliasing = false);
  ~Texture();

  static unsigned int LoadTexture(const char *filename, bool antiAliasing = false);
  static void FreeTexture(unsigned int &texture);
};
}

#endif // QUACKENGINE_TEXTURE_HPP