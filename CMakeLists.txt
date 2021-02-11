cmake_minimum_required (VERSION 3.0)
project (raytracer VERSION 1.0)

include_directories(src)

add_executable(raytracer src/main.cpp
                         src/functions.cpp
                         src/functions.h
                         src/input.h
                         src/camera.cpp
                         src/camera.h
                         src/ball.h)
