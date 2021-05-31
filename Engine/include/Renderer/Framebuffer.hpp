#ifndef QUACKENGINE_FRAMEBUFFER_HPP
#define QUACKENGINE_FRAMEBUFFER_HPP

namespace Renderer
{

    class Framebuffer
    {
    private:
        unsigned int _id;
        unsigned int _rbo;
        unsigned int _texture;
        unsigned int _width;
        unsigned int _height;

    public:
        Framebuffer() = default;
        Framebuffer(unsigned int id, unsigned int rbo, unsigned int texture,
                    unsigned int width, unsigned int height);

        void Delete() const;

        static Framebuffer LoadFramebuffer(unsigned int width, unsigned int height);


        unsigned int GetId() const;

        unsigned int GetTexture() const;

        unsigned int GetRbo() const;

        void Bind() const;

        void BindTexture(unsigned int index = 0) const;

        unsigned int GetWidth();

        unsigned int GetHeight();

        void Resize(unsigned int width, unsigned int height);
    };
}
#endif // QUACKENGINE_FRAMEBUFFER_HPP
