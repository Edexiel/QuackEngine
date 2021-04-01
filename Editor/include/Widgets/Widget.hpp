//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_WIDGET_HPP
#define QUACKENGINE_WIDGET_HPP


#include <string>

class Widget
{
private:
    bool _visible{true};

private:
    std::string _title{"Empty"};
    float _position[2]{0.f, 0.f};
    float _size[2]{0.f, 0.f};
    int _flags;

public:

    void Draw();

    virtual void UpdateAlways() = 0;

    virtual void UpdateVisible() = 0;

    virtual void OnShow() = 0;

    virtual void OnHide() = 0;

    bool IsVisible() const;

    void SetVisible(bool visible);

};

inline void Widget::Draw()
{

}

inline bool Widget::IsVisible() const
{
    return _visible;
}

inline void Widget::SetVisible(bool visible)
{
    _visible = visible;
}

#endif //QUACKENGINE_WIDGET_HPP
