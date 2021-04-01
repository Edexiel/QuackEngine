//
// Created by g.nisi on 03/02/2021.
//

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "Input/InputManager.hpp"
#include "Input/PlatformInputGLFW.hpp"
#include "Resources/ResourcesManager.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "Renderer/Model.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include <cstdio>

void debugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                     GLsizei length, const GLchar *message,
                     const void *userParam) {
  printf("OpenGL error = %s\n", message);
}

/*static void HelpMarker(const char* desc)
{
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}*/

int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1280, 720, "QuackEngine", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* load Glad OpenGL */
  int version = gladLoadGL(glfwGetProcAddress);
  // printf("OpenGL version : %d.%d\n", GLAD_VERSION_MAJOR(version),
  // GLAD_VERSION_MINOR(version));

  if (version == 0) {
    printf("Failed to initialize OpenGL context");
    glfwTerminate();
    return -1;
  }

  printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n", glGetString(GL_VERSION));

  // todo : debug output
  /*if (GLAD_GL_KHR_debug)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugGLCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE,
  0, nullptr, GL_FALSE); glDebugMessageControl(GL_DONT_CARE,
  GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
  }*/
  //--------------------------------------------------------------- imgui config

  // Init ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
  // Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable
  // Multi-Viewport / Platform Windows io.ConfigViewportsNoAutoMerge = true;
  // io.ConfigViewportsNoTaskBarIcon = true;

  // ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 460");
  //---------------------------------------------------------------imguiconfig
  //end

  // Windows
  bool window_scene = true;
  bool window_viewport = true;
  bool window_properties = true;
  bool window_explorer = true;
  bool window_log = true;

  // todo : doit etre dans le game
  // input manager
  Input::PlatformInputGLFW platformInput(window);
  Input::InputManager input(platformInput);

  // wtf ?
  // todo : doit etre dans la scene et donc dans le game
  // ResourcesManager
  //  Resources::ResourcesManager resourcesManager;
  //
  //  Renderer::Texture texture =
  //  resourcesManager.LoadTexture("../../../DirtCube.jpg"); Renderer::Shader
  //  shader  =
  //  resourcesManager.LoadShader("../../../BasicVertexShader.vs","../../../BasicFragmentShader.fs");
  //
  //  resourcesManager.ReadFiles();

  while (!glfwWindowShouldClose(window)) {

    /* Poll for and process events */
    glfwPollEvents();
    // resourcesManager

    // imgui
    {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      { // ImGUI windows
        // DockSpace
        {
          //        ImGuiWindowFlags window_flags=0;
          //          window_flags |= ImGuiWindowFlags_Popup ;

          // ImGuiID dockspace_id = ImGui::GetId("DockSpace");
          // ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
          ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

          // Menu bar
          {
            if (ImGui::BeginMainMenuBar()) {
              if (ImGui::BeginMenu("Files")) {
                if (ImGui::MenuItem("New scene")) {
                }
                if (ImGui::MenuItem("Save scene")) {
                }

                ImGui::Separator();
                if (ImGui::MenuItem("Import object")) {
                }

                ImGui::EndMenu();
              }

              if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {
                }
                if (ImGui::MenuItem("Redo", "CTRL+Y")) {
                } // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {
                }
                if (ImGui::MenuItem("Copy", "CTRL+C")) {
                }
                if (ImGui::MenuItem("Paste", "CTRL+V")) {
                }
                ImGui::EndMenu();
              }

              if (ImGui::BeginMenu("Windows")) {
                if (ImGui::MenuItem("Viewport", NULL, window_viewport)) {
                  window_viewport = !window_viewport;
                }
                if (ImGui::MenuItem("Logs", NULL, window_log)) {
                  window_log = !window_log;
                }
                ImGui::EndMenu();
              }
            }
            ImGui::EndMainMenuBar();
          }
        }

        // ImGui::ShowDemoWindow();

        // Scene
        {
          ImGui::Begin("Scene", &window_scene);
          // ImGui::
          ImGui::End();
        }

        // ViewPort
        if (window_viewport) {
          ImGui::Begin("Viewport");
          // ImGui::Text("Hello from another window!");
          // ImGui::Image()
          ImGui::End();
        }

        // Properties
        if (window_properties) {
          ImGui::Begin("Properties", &window_properties);
          ImGui::End();
        }

        // File Explorer
        if (window_explorer) {
          ImGui::Begin("Explorer", &window_explorer);
          ImGui::End();
        }

        // Logs
        if (window_log) {
          ImGui::Begin("Logs", &window_log);
          ImGui::End();
        }
        ImGui::Render();
      }

      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);
      // glViewport(0, 0, display_w, display_h);
      // glClearColor(1.f,0.f,0.f,0.f);
      // glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
      }
    }

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}