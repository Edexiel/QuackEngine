#ifndef QUACKENGINE_SCENEWIDGET_HPP
#define QUACKENGINE_SCENEWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "CameraEditor.hpp"
#include "ImGuizmo.h"

class SceneWidget : public Widget
{
private:
    CameraEditor _camera = CameraEditor(1280, 720, 50.f, 0.01f, 3.1415f * 60 / 180.f);
    bool _isCameraRotating = false;

    ImGuizmo::OPERATION _operation = ImGuizmo::OPERATION::TRANSLATE;
    ImGuizmo::MODE _mode = ImGuizmo::MODE::WORLD;

    void CameraUpdate();
    void MouseMovement();
    void ImGuizmoUpdate(const Maths::Matrix4& view, const Maths::Matrix4& projection);
    void SelectOperation();
    void ManipulateEntity(const Maths::Matrix4& view, const Maths::Matrix4& projection);

    Maths::Matrix4 _mat;

public:
    SceneWidget();

    void UpdateVisible() final;

};


#endif //QUACKENGINE_SCENEWIDGET_HPP
