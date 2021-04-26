cmake_minimum_required(VERSION 3.0)
project(Game VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(${PROJECT_NAME} STATIC src/game.cpp) #todo change STATIC to SHARED later

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC Engine)