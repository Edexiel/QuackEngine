#ifndef QUACKENGINE_SCENEWIDGET_HPP
#define QUACKENGINE_SCENEWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "ImGuizmo.h"
#include "Maths/Matrix4.hpp"

class SceneWidget : public Widget
{
private:
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
    SceneWidget(Editor &editor);

    void UpdateVisible() final;

};


#endif //QUACKENGINE_SCENEWIDGET_HPP
