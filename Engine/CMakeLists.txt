cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC
        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp
        src/Scene/Scene.cpp
        src/Scene/Entity.cpp
        src/Thread/TaskSystem.cpp
        src/Thread/ThreadPool.cpp
        src/Resources/ResourcesManager.cpp
        src/Renderer/Model.cpp
        src/Renderer/Mesh.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Texture.cpp
        src/Renderer/Framebuffer.cpp
        src/Renderer/RendererPlatform.cpp
        src/Resources/Loaders/TextureLoader.cpp
        src/Resources/Loaders/ShaderLoader.cpp
        src/Resources/Loaders/ModelLoader.cpp
        src/Scene/Archetype.cpp
        src/Scene/Components/Component.cpp
        src/Scene/Components/Transform.cpp
        src/Scene/Components/Renderer.cpp
        src/Scene/Components/Physics.cpp
        src/Scene/Components/Script.cpp)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw assimp stb)