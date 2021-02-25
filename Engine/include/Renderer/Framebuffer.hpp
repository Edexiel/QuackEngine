#ifndef QUACKENGINE_FRAMEBUFFER_HPP
#define QUACKENGINE_FRAMEBUFFER_HPP
#include <string>

namespace Renderer
{
class Framebuffer
{
private:
  std::string _name;
  unsigned int _ID, _rbo, _textureColorbuffer;

public:
  Framebuffer() = default;
  Framebuffer(const unsigned width, const unsigned height);

  Framebuffer(const unsigned int ID): _ID{ ID } {}
  ~Framebuffer() = default;
  void Example();
  unsigned int GetID() const;
  unsigned int GetTexture() const;
  void Delete();
};
}
#endif // QUACKENGINE_FRAMEBUFFER_HPP
