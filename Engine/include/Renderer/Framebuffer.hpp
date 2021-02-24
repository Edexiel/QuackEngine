#ifndef QUACKENGINE_FRAMEBUFFER_HPP
#define QUACKENGINE_FRAMEBUFFER_HPP
#include <string>

namespace Renderer
{
class Framebuffer
{
private:
  unsigned int _ID;
  std::string _name;

public:
  Framebuffer() = default;
  Framebuffer(const unsigned int ID): _ID{ ID }
  {}
  ~Framebuffer() = default;
};
}
#endif // QUACKENGINE_FRAMEBUFFER_HPP
