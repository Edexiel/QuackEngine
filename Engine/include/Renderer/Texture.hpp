#ifndef QUACKENGINE_TEXTURE_HPP
#define QUACKENGINE_TEXTURE_HPP

#include <string>

namespace Renderer
{
class Texture
{
private:
  unsigned int _ID{0};

public:
  Texture() = default;
  //Texture(const Texture& texture): _ID{texture.GetID()}{};
  Texture(const unsigned int& ID);
  ~Texture();
  unsigned int GetID() const;
  static Texture LoadTexture(const char* filepath);
  void Bind();
};
}

#endif // QUACKENGINE_TEXTURE_HPP
