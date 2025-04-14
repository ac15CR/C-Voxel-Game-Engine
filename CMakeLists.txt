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
        src/log.h
        src/vector3.h
        src/color.h
        src/vertex_data.h
        src/matrix4.h
        src/matrix4.cpp
        src/camera.h
        src/Camera.cpp
        src/entity.h
        src/entity.cpp
        src/scene.h
        src/stop_event.h
        src/event.h
        src/key.h
        src/key_event.h
        src/key_event.cpp
        src/mouse_event.h
        src/mouse_event.cpp)

#target_include_directories(Voxalite PRIVATE src third_party/opengl)
