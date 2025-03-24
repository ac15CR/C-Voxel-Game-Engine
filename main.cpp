#include <format>
#include <iostream>
#include <numbers>

#include "camera.h"
#include "entity.h"
#include "exception.h"
#include "log.h"
#include "material.h"
#include "mesh.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "window.h"

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
    game::log::info("Initializing game");

    try {
        const game::Window window{800u, 600u};

        const auto vertex_shader = game::Shader{vertex_shader_src, game::ShaderType::VERTEX};
        const auto fragment_shader = game::Shader{fragment_shader_src, game::ShaderType::FRAGMENT};
        const auto material = game::Material{vertex_shader, fragment_shader};
        const auto mesh = game::Mesh{};
        constexpr auto renderer = game::Renderer{};
        const auto entity1 = game::Entity{&mesh, &material, {0.0f, -1.0f, 0.0f}};
        const auto entity2 = game::Entity{&mesh, &material, {0.0f, 2.0f, 0.0f}};
        auto scene = game::Scene{{&entity1, &entity2}};

        const auto camera = game::Camera{
            {3.0f, 0.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.1f, 100.0f
        };

        while (window.running()) {
            renderer.render(camera, scene);
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
