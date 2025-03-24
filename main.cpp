#include <format>
#include <iostream>

#include "exception.h"
#include "material.h"
#include "renderer.h"
#include "shader.h"
#include "window.h"
#include "matrix4.h"

#include "log.h"

namespace
{
constexpr auto vertex_shader_src = R"(
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertex_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vertex_color = color;
}
)";

constexpr auto fragment_shader_src = R"(
#version 460 core

in vec3 vertex_color;
out vec4 frag_color;

void main()
{
    frag_color = vec4(vertex_color, 1.0);
}
)";
}


int main()
{
    game::Matrix4 m1{
        {
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f
        }
    };

    game::Matrix4 m2{
        {
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f
        }
    };

    m1 *= m2;
    std::println("{}", m1);

    try {
        const game::Window window{800u, 600u};

        const auto vertex_shader = game::Shader{vertex_shader_src, game::ShaderType::VERTEX};
        const auto fragment_shader = game::Shader{fragment_shader_src, game::ShaderType::FRAGMENT};
        auto material = game::Material{vertex_shader, fragment_shader};
        const auto renderer = game::Renderer{std::move(material)};

        while (window.running()) {
            renderer.render();
            window.swap();
        }
    }
    catch (const game::Exception &err) {
        std::println(std::cerr, "{}", err);
    } catch (...) {
        std::println(std::cerr, "unknown error");
    }

    return 0;
}
