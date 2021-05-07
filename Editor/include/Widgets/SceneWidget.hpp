//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_SCENEWIDGET_HPP
#define QUACKENGINE_SCENEWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "CameraEditor.hpp"


class SceneWidget : public Widget
{
private:
    CameraEditor _camera = CameraEditor(1280, 720, 50.f, 0.01f, 3.1415f * 60 / 180.f);
    bool _isCameraRotating = false;
public:
    SceneWidget();

    void UpdateVisible() final;
    void CameraUpdate();
    void MouseMovement();

};


#endif //QUACKENGINE_SCENEWIDGET_HPP
