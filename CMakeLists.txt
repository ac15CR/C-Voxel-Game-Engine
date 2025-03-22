cmake_minimum_required(VERSION 3.30)
project(
        Voxalite
        VERSION 0.1.0
        DESCRIPTION "A simple voxel engine"
        LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)

include_directories(src third_party/opengl)

add_executable(Voxalite main.cpp
        src/auto_release.h
        src/window.h
        src/window.cpp
        src/exception.h
        src/exception.cpp
        src/error.h
        third_party/opengl/wglext.h
        third_party/opengl/glext.h
        src/opengl.h
        src/shader.h
        src/shader.cpp
        src/material.h
        src/material.cpp
        src/mesh.h
        src/mesh.cpp
        src/renderer.h
        src/renderer.cpp
        src/log.h)

#target_include_directories(Voxalite PRIVATE src third_party/opengl)
