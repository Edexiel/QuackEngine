#ifndef QUACKENGINE_DIALOGBOX_HPP
#define QUACKENGINE_DIALOGBOX_HPP

#include "Renderer/ProcessBase.hpp"
#include "Renderer/UI/Font.hpp"

namespace Renderer
{
    class DialogBox : public ProcessBase
    {
    private:
        Font _font;

    public:
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) final;
    };
}
#endif //QUACKENGINE_DIALOGBOX_HPP
