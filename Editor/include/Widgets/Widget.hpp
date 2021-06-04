#ifndef QUACKENGINE_WIDGET_HPP
#define QUACKENGINE_WIDGET_HPP

#include <string>
#include <imgui.h>
#include <imgui_internal.h>
#include "Scene/Core/Types.hpp"

class Widget
{
protected:
    class Editor &_editor;
    class Engine &_engine;

    enum class Type
    {
        window,
        menu

    };

    explicit Widget(class Editor &editor) noexcept;

    std::string _title;
    bool _visible{true};
    Type _type{Type::window};
    float _position[2]{0.f, 0.f};
    float _size[2]{0.f, 0.f};

    ImGuiWindowFlags _windowFlags = 0;

public:
    virtual ~Widget() = default;

    virtual void Draw();

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

#endif //QUACKENGINE_WIDGET_HPP
