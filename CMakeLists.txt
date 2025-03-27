cmake_minimum_required(VERSION 3.29)
project(terrain_simulation)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glad OpenGL glfw3)