cmake_minimum_required(VERSION 3.17)

project(Editor VERSION 0.1.0 LANGUAGES CXX C)

add_executable(${PROJECT_NAME} src/mainECS.cpp)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw imgui reactphysics3d Engine)