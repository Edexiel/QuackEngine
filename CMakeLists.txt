cmake_minimum_required(VERSION 3.17)
project(QuackEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#find_package(OpenGL REQUIRED)
#OpenGL::GL

#GLAD
add_subdirectory(Vendor/glad)

#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Vendor/glfw)

#IMGUI
set(IMGUI_SOURCES
        "Vendor/imgui/imgui.cpp"
        "Vendor/imgui/imgui_demo.cpp"
        "Vendor/imgui/imgui_draw.cpp"
        "Vendor/imgui/imgui_widgets.cpp"
        "Vendor/imgui/backends/imgui_impl_glfw.cpp"
        "Vendor/imgui/backends/imgui_impl_opengl3.cpp"
        )
add_library(imgui INTERFACE)
target_sources(imgui INTERFACE $(IMGUI_SOURCES))
target_include_directories(imgui INTERFACE Vendor/imgui)


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)




#Engine
add_subdirectory(Engine)
#Editor
add_subdirectory(Editor)