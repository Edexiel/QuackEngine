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
    RendererPlatform::BindFramebuffer(_id);
}

void Framebuffer::BindTexture() const
{
    RendererPlatform::BindTexture(_texture);
}

unsigned int Framebuffer::GetWidth()
{
    return _width;
}

unsigned int Framebuffer::GetHeight()
{
    return _height;
}

void Framebuffer::Resize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;

    RendererPlatform::ResizeFramebuffer(_id, _rbo, _texture, width, height);
}
