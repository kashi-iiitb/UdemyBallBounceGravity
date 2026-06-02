cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++17)
set(CXX_FLAGS, "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(BallBounce)
find_package(SDL2 REQUIRED)

add_executable(BallBounce "src/SDL_Circle.cpp")
target_link_libraries(BallBounce PRIVATE SDL2::SDL2)