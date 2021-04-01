#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

Framebuffer::Framebuffer(unsigned int ID, unsigned int rbo,unsigned int texture,
                         unsigned int width,unsigned int height):
                         _ID{ID}, _rbo{rbo}, _texture{texture},
                         _width{width},_height{height}{}

Framebuffer Framebuffer::LoadFramebuffer(unsigned int width, unsigned int height)
{
    Framebuffer framebuffer = RendererPlatform::CreateFramebuffer(width, height);
    return framebuffer;
}

void Framebuffer::Delete()
{
    RendererPlatform::DeleteFramebuffer(_ID, _rbo, _texture);
}

unsigned int Renderer::Framebuffer::GetID() const
{
  return _ID;
}

unsigned int Renderer::Framebuffer::GetTexture() const
{
  return _texture;
}
unsigned int Framebuffer::GetRbo() const
{
  return _rbo;
}
Framebuffer::~Framebuffer(){}

void Framebuffer::Bind()
{
  RendererPlatform::BindFramebuffer(_ID);
}
void Framebuffer::BindTexture()
{
  RendererPlatform::BindTexture(_texture);
}
