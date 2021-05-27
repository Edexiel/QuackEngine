#include "Widgets/SceneWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Engine.hpp"

#include "GLFW/glfw3.h"

using namespace Renderer;
SceneWidget::SceneWidget()
{
    _title="Scene";
    _camera.SetInput(Engine::Instance().GetInputManager());
}


void SceneWidget::UpdateVisible()
{
    ImGui::BeginChild("ViewportRender");
    // Get the size of the child (i.e. the whole draw size of the windows).

    CameraUpdate();
    MouseMovement();

    ImGui::EndChild();
}

void SceneWidget::MouseMovement()
{
    ImGuiIO& io = ImGui::GetIO();
    Engine& engine = Engine::Instance();
    GLFWwindow *window = engine.GetWindow();


    if(ImGui::IsMouseClicked(1, true) && ImGui::IsItemHovered())
    {
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        _isCameraRotating = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
    {
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        io.WantCaptureMouse = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        _isCameraRotating = false;
    }
    if(_isCameraRotating)
    {
        Input::MousePosition mp = engine.GetInputManager().mousePosition;
        _camera.MouseMovement(mp.pos, mp.prevPos);
    }
}

void SceneWidget::CameraUpdate()
{
    const ImVec2 wsize = ImGui::GetWindowSize();

    _camera._width = (unsigned int)wsize.x;
    _camera._height = (unsigned int)wsize.y;


    _camera.FreeFly();

    RendererInterface &rendererInterface = Engine::Instance().GetRendererInterface();
    Maths::Matrix4 projection = Maths::Matrix4::Perspective((int)_camera._width, (int)_camera._height, _camera._near, _camera._far, _camera._fov);
    Maths::Matrix4 view = (Maths::Matrix4::Translate(_camera._position) * _camera._rotation.ToMatrix() * Maths::Matrix4::Scale({1, 1, -1})).GetInvert();

    rendererInterface.UpdateSceneFramebufferEditor(projection, view, _camera._framebuffer);
    ImGui::Image((ImTextureID) (size_t) _camera._framebuffer.GetTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ImGuizmoUpdate(view, projection);
}

void SceneWidget::ImGuizmoUpdate(const Maths::Matrix4& view, const Maths::Matrix4& projection)
{
    ImGuizmo::BeginFrame();
    SelectOperation();

    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, (float)_camera._width, (float)_camera._height);
    ImGuizmo::DrawGrid(view.e, projection.e, Maths::Matrix4::Identity().e, 100.f);

    ManipulateEntity(view, projection);
}

void SceneWidget::SelectOperation()
{
    GLFWwindow* window = Engine::Instance().GetWindow();

    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        _operation = ImGuizmo::OPERATION::TRANSLATE;
        std::cout << "translate\n";
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        _operation = ImGuizmo::OPERATION::ROTATE;
        std::cout << "rotate\n";
    }
    if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS)
    {
        _operation = ImGuizmo::OPERATION::SCALE;
        std::cout << "scale\n";
    }
}

void SceneWidget::ManipulateEntity(const Maths::Matrix4& view, const Maths::Matrix4& projection)
{
    auto &transform = Engine::Instance().GetCurrentWorld().GetComponent<Component::Transform>(_entity);

    ImGuizmo::RecomposeMatrixFromComponents(transform.position.e, (transform.rotation.ToEuler() * RadToDeg<float>()).e,  transform.scale.e, _mat.e);

    ImGuizmo::Manipulate(view.e, projection.e, _operation, _mode, _mat.e);
    Maths::Vector3f translation;
    Maths::Vector3f eulerRotation;
    Maths::Vector3f scale;
    ImGuizmo::DecomposeMatrixToComponents(_mat.e, translation.e, eulerRotation.e, scale.e);

    transform.position = translation;
    transform.rotation = Maths::Quaternion::EulerToQuaternion(eulerRotation * DegToRad<float>());
    transform.scale = scale;
}
