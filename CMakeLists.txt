cmake_minimum_required(VERSION 3.30)
project(
        Voxalite
        VERSION 0.1.0
        DESCRIPTION "A simple voxel engine"
        LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_executable(Voxalite main.cpp
        src/auto_release.h
        src/window.h
        src/window.cpp
        src/exception.h
        src/exception.cpp)
