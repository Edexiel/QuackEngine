cmake_minimum_required(VERSION 3.17)

project(Editor VERSION 0.1.0 LANGUAGES CXX C)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Editor.cpp
        src/Widgets/Widget.cpp
        src/Widgets/SceneWidget.cpp
        src/Widgets/ViewportWidget.cpp
        src/Widgets/PropertiesWidget.cpp
        src/Widgets/LogWidget.cpp
        src/Widgets/ExplorerWidget.cpp
        src/Widgets/ViewerWidget.cpp
        src/CameraEditor.cpp
        src/Widgets/ToolboxWidget.cpp
        src/Widgets/MenuWidget.cpp)


target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw imgui ImGuizmo Engine Game)
