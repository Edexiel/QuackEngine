#include "Renderer/Window.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

Window::~Window()
{
    RendererPlatform::CloseWindow();
}

void Window::Init(unsigned int width, unsigned int height, const char* name)
{
    _width = width;
    _height = height;

    _window = RendererPlatform::LoadScreen(width, height, name);
}

void* Window::GetWindowPtr()
{
    return _window;
}

void Window::Display()
{

}

unsigned int Window::GetWidth() const
{
    return _width;
}

unsigned int Window::GetHeight() const
{
    return _height;
}