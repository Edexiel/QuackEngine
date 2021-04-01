#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

Framebuffer::Framebuffer(unsigned int id, unsigned int rbo, unsigned int texture,
                         unsigned int width, unsigned int height) :
        _Id{id}, _rbo{rbo}, _texture{texture},
        _width{width}, _height{height}
{}

Framebuffer::~Framebuffer()
{
    RendererPlatform::DeleteFramebuffer(_Id, _rbo, _texture);
}

unsigned int Renderer::Framebuffer::GetId() const
{
    return _Id;
}

unsigned int Renderer::Framebuffer::GetTexture() const
{
    return _texture;
}

unsigned int Framebuffer::GetRbo() const
{
    return _rbo;
}


void Framebuffer::Bind() const
{
    RendererPlatform::BindFramebuffer(_Id);
}

void Framebuffer::BindTexture() const
{
    RendererPlatform::BindTexture(_texture);
}
