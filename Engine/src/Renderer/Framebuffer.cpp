#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

Framebuffer::Framebuffer(unsigned int id, unsigned int rbo, unsigned int texture,
                         unsigned int width, unsigned int height) :
        _id{id}, _rbo{rbo}, _texture{texture},
        _width{width}, _height{height}
{}

Framebuffer Framebuffer::LoadFramebuffer(unsigned int width, unsigned int height)
{
    Framebuffer framebuffer = RendererPlatform::CreateFramebuffer(width, height);
    return framebuffer;
}

void Framebuffer::Delete() const
{
    RendererPlatform::DeleteFramebuffer(_id, _rbo, _texture);
}

unsigned int Renderer::Framebuffer::GetId() const
{
    return _id;
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
    RendererPlatform::SetViewport(0,0, _width, _height);
    RendererPlatform::BindFramebuffer(_id);
}

void Framebuffer::BindTexture(unsigned int index) const
{
    RendererPlatform::BindTexture(_texture, index);
}

unsigned int Framebuffer::GetWidth() const
{
    return _width;
}

unsigned int Framebuffer::GetHeight() const
{
    return _height;
}

void Framebuffer::Resize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;

    RendererPlatform::ResizeFramebuffer(_id, _rbo, _texture, width, height);
}
