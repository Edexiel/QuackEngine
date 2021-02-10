cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_executable(Editor src/main.cpp)

target_include_directories (Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Editor PUBLIC glad glfw )