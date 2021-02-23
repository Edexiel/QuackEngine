cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} src/main.cpp
        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp
        src/Scene/Scene.cpp
        src/Scene/Entity.cpp
        src/Scene/Component.cpp)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw assimp)