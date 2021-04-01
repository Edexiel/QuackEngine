#ifndef _WINDOW_
#define _WINDOW_

namespace Renderer
{
    class Window
    {
        void *_window{nullptr};

        unsigned int _width{0};
        unsigned int _height{0};

    public:

        ~Window();

        void Init(unsigned int width, unsigned height, const char* name);
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;

        void* GetWindowPtr();

        void Display();
    };
}

#endif