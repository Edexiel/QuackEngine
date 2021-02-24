#ifndef QUACKENGINE_FRAMEBUFFER_HPP
#define QUACKENGINE_FRAMEBUFFER_HPP
#include <string>

class Framebuffer
{
private:
  unsigned int _ID;
  std::string _name;
public:
  FrameBuffer() = default;
  FrameBuffer(const unsigned int ID): _ID{ID}{}
  ~FrameBuffer() = default;
};

#endif // QUACKENGINE_FRAMEBUFFER_HPP
