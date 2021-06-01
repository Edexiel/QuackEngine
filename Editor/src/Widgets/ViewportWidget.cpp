#include "Widgets/ViewportWidget.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/System/CameraSystem.hpp"

#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererInterface.hpp"

#include "GLFW/glfw3.h"
#include <memory>

using namespace Renderer;

ViewportWidget::ViewportWidget()
{
    _title = "Viewport";
}

void ViewportWidget::UpdateVisible()
{
    ImGui::BeginChild("ViewportRender");
    // Get the size of the child (i.e. the whole draw size of the windows).
    const ImVec2 wsize = ImGui::GetWindowSize();

    RendererInterface &rendererInterface = Engine::Instance().GetRendererInterface();

    //todo : make ref
    Engine::Instance().GetCurrentWorld().GetSystem<CameraSystem>()->GetActiveCamera().Resize(wsize.x, wsize.y);
    Framebuffer f = RendererInterface::GetSceneUpdatedFramebuffer();

    ImGui::Image((ImTextureID) (size_t) f.GetTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
}

void ViewportWidget::LockCursor()
{
    ImGuiIO &io = ImGui::GetIO();

    GLFWwindow *window = Engine::Instance().GetWindow();
    auto cs = Engine::Instance().GetCurrentWorld().GetSystem<CameraSystem>();
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !_isInGame)
    {
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        _isInGame = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS && _isInGame)
    {
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        _isInGame = false;
    }
}
