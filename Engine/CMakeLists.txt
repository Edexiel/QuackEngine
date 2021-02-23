cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME}
        src/main.cpp
        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp
        src/Thread/TaskSystem.cpp
        src/Thread/ThreadPool.cpp
        src/Resources/ResourcesManager.cpp
        src/Renderer/Model.cpp
        src/Renderer/Mesh.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Texture.cpp
        src/Resources/Loaders/TextureLoader.cpp
        src/Resources/Loaders/ShaderLoader.cpp
        src/Resources/Loaders/ModelLoader.cpp
        )

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw assimp)