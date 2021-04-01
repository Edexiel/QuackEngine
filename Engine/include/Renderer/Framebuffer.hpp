#ifndef QUACKENGINE_FRAMEBUFFER_HPP
#define QUACKENGINE_FRAMEBUFFER_HPP
#include <string>

namespace Renderer
{

class Framebuffer
{
private:
  unsigned int _ID;
  unsigned int _rbo;
  unsigned int _texture;
  unsigned int _width;
  unsigned int _height;

public:
  Framebuffer(unsigned int ID, unsigned int rbo, unsigned int texture,
              unsigned int width, unsigned int height);
  ~Framebuffer();

  void Delete();

  static Framebuffer LoadFramebuffer(unsigned int width, unsigned int height);


  unsigned int GetID() const;
  unsigned int GetTexture() const;
  unsigned int GetRbo() const;

  void Bind();
  void BindTexture();
};
}
#endif // QUACKENGINE_FRAMEBUFFER_HPP
