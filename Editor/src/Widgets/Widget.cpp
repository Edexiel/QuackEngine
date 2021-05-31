#include "Widgets/Widget.hpp"
#include "Engine.hpp"
#include "Editor.hpp"

//std::string Widget::_assetName = std::string();


Widget::Widget(Editor &editor) noexcept: _editor{editor}, _engine{editor.GetEngine()}
{}

bool Widget::IsVisible() const
{
    return _visible;
}

void Widget::SetVisible(bool visible)
{
    _visible = visible;
}

void Widget::Draw()
{
    UpdateBefore();

    if (!_visible)
        return;

    if (ImGui::Begin(_title.c_str(), &_visible, _windowFlags))
    {
        UpdateVisible();
    }

    ImGui::End();

}

