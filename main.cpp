#include <format>
#include <iostream>
#include <numbers>
#include <type_traits>
#include <ranges>
#include <variant>

#include "camera.h"
#include "entity.h"
#include "exception.h"
#include "event.h"
#include "stop_event.h"
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

        auto entities = std::vector<game::Entity>{};

        for (auto i = -10; i < 10; ++i) {
            for (auto j = -10; j < 10; ++j) {
                entities.emplace_back(
                    &mesh, &material, game::Vector3{static_cast<float>(i) * 2.5f, -3.0f, static_cast<float>(j) * 2.5f});
            }
        }

        // I still don't understand this but this is how it works I guess
        const auto scene = game::Scene{entities | std::views::transform([](const auto &e) { return &e; }) | std::ranges::to<std::vector<const game::Entity *>>()};

        auto camera = game::Camera{
            {0.0f, 0.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.1f, 100.0f
        };

        auto velocity = game::Vector3{0.0f, 0.0f, 0.0f};

        auto running = true;
        while (running) {
            auto event = window.pump_event(); // TODO: Change to do while
            while (event && running) {
                std::visit(
                    [&](auto &&arg) // TODO: this is not good, it should be changed
                    {
                        using T = std::decay_t<decltype(arg)>;

                        if constexpr (std::same_as<T, game::StopEvent>) {
                            running = false;
                        } else if constexpr (std::same_as<T, game::KeyEvent>) {
                            if (arg.key() == game::Key::ESC) {
                                running = false;
                            } else if (arg.key() == game::Key::W) {
                                // Temporary very volatile
                                velocity += arg.state() == game::KeyState::UP
                                                ? game::Vector3{0.0f, 0.0f, 1.0f}
                                                : game::Vector3{0.0f, 0.0f, -1.0f};
                            } else if (arg.key() == game::Key::A) {
                                velocity += arg.state() == game::KeyState::UP
                                                ? game::Vector3{1.0f, 0.0f, 0.0f}
                                                : game::Vector3{-1.0f, 0.0f, 0.0f};
                            } else if (arg.key() == game::Key::S) {
                                velocity += arg.state() == game::KeyState::UP
                                                ? game::Vector3{0.0f, 0.0f, -1.0f}
                                                : game::Vector3{0.0f, 0.0f, 1.0f};
                            } else if (arg.key() == game::Key::D) {
                                velocity += arg.state() == game::KeyState::UP
                                                ? game::Vector3{-1.0f, 0.0f, 0.0f}
                                                : game::Vector3{1.0f, 0.0f, 0.0f};
                            }
                        }
                    }, *event
                );
                event = window.pump_event();
            }

            camera.translate(game::Vector3::normalize(velocity));

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
