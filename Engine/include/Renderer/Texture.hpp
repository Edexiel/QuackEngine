#ifndef QUACKENGINE_TEXTURE_HPP
#define QUACKENGINE_TEXTURE_HPP

#include <string>

namespace Renderer
{
class Texture
{
private:
  std::string _name{""};
public:
  unsigned int _ID{0};

  Texture() = default;
  Texture(const unsigned int& ID);
  ~Texture();
  unsigned int GetID() const;
  static unsigned int LoadTexture(const char* filepath);
  void Bind();
};
}

#endif // QUACKENGINE_TEXTURE_HPP