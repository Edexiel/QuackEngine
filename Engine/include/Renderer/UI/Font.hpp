#ifndef QUACKENGINE_FONT_HPP
#define QUACKENGINE_FONT_HPP

#include "Renderer/ProcessBase.hpp"

namespace Renderer
{
    class Font : public ProcessBase
    {
    public:
        Font() = default;
        Font(const std::string& name);
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) final;
    };
}
#endif //QUACKENGINE_FONT_HPP
