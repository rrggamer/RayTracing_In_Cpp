cmake_minimum_required(VERSION 3.10)
project(ray_tracing LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find Packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)


add_executable(raytracing sdl_test.cpp)

target_link_libraries(raytracing PRIVATE
 SDL2::SDL2
 SDL2_ttf
)