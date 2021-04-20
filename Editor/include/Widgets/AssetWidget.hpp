#ifndef _ASSETWIDGET_HPP
#define _ASSETWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "Scene/Component/Camera.hpp"

class AssetWidget : public Widget
{
private:
    Component::Camera _camera;

public:
    AssetWidget();

    void UpdateVisible() final;

};

#endif //_ASSETWIDGET_HPP
