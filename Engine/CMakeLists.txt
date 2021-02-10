cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(Engine src/main.cpp)

target_include_directories (Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include)

target_link_libraries(Engine PUBLIC glad glfw assimp flatbuffers)