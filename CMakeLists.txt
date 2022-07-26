cmake_minimum_required(VERSION 3.21)
project(My_Rendering)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(My_Rendering
        hitable.h
        hitablelist.h
        main.cpp
        ray.h
        sphere.h
        vec3.h)
