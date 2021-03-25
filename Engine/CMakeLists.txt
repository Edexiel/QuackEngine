cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC
        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp
        src/Thread/TaskSystem.cpp
        src/Thread/ThreadPool.cpp
        src/Resources/ResourcesManager.cpp
        src/Renderer/Model.cpp
        src/Renderer/Mesh.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Texture.cpp
        src/Renderer/Material.cpp
        src/Renderer/RendererPlatform.cpp
        src/Renderer/Framebuffer.cpp
        src/Renderer/IcoSphere.cpp
        src/Renderer/Light.cpp
        src/Scene/World.cpp
        src/Scene/System/TestSystem.cpp
        include/Scene/System/TestSystem.hpp
        src/Scene/System/ScriptSystem.cpp
        include/Scene/System/ScriptSystem.hpp
        src/Scene/System/PhysicsSystem.cpp
        include/Scene/System/PhysicsSystem.hpp
        include/Scene/Component/Mesh.hpp
        )

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw assimp stb)
