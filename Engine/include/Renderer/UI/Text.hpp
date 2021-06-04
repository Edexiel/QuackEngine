#ifndef QUACKENGINE_TEXT_HPP
#define QUACKENGINE_TEXT_HPP

#include "Renderer/ProcessBase.hpp"
#include "Maths/Vector2.hpp"
#include "Renderer/UI/Font.hpp"

#include <unordered_map>

namespace Renderer
{
    class Text : public ProcessBase
    {
    private:
        Font _font;
    public:
        Text() = default;
        explicit Text(const std::string &name);
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) final;
        void RenderText(std::string text, Maths::Vector2f position, float scale, Maths::Vector4f color, const Mesh& quad);
    };
}
#endif //QUACKENGINE_TEXT_HPP
