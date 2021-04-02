//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_WIDGET_HPP
#define QUACKENGINE_WIDGET_HPP


#include <string>
#include <imgui.h>

class Widget
{
protected:
    std::string _title;
    bool _visible{true};
    float _position[2]{0.f, 0.f};
    float _size[2]{0.f, 0.f};
    ImGuiWindowFlags _flags = 0;

    Widget() = default;

public:
    virtual ~Widget() = default;

    void Draw();

    virtual void UpdateBefore()
    {};

    virtual void UpdateVisible() = 0;

    //todo
//    virtual void OnShow()
//    {};
//
//    virtual void OnHide()
//    {};

    bool IsVisible() const;

    void SetVisible(bool visible);

};

inline bool Widget::IsVisible() const
{
    return _visible;
}

inline void Widget::SetVisible(bool visible)
{
    _visible = visible;
}

inline void Widget::Draw()
{
    UpdateBefore();

    if (!_visible)
        return;

    if (ImGui::Begin(_title.c_str(), &_visible, _flags))
    {
        UpdateVisible();
    }

    ImGui::End();

}


#endif //QUACKENGINE_WIDGET_HPP
