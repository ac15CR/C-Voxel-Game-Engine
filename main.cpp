#include <format>
#include <iostream>
#include <numbers>
#include <ranges>
#include <type_traits>
#include <unordered_map>
#include <variant>

#include "camera.h"
#include "entity.h"
#include "event.h"
#include "exception.h"
#include "log.h"
#include "material.h"
#include "mesh.h"
#include "mouse_event.h"
#include "renderer.h"
#include "resource_loader.h"
#include "scene.h"
#include "shader.h"
#include "stop_event.h"
#include "texture.h"
#include "window.h"

int main()
{
    game::log::info("Initializing game");

    try
    {
        const game::Window window{800u, 600u};

        const game::ResourceLoader resource_loader{"../assets/"sv};

        const game::Texture texture{resource_loader.load_binary("wooden_crate.png"), 256, 256};
        const game::Sampler sampler{};

        const auto vertex_shader = game::Shader{resource_loader.load_string("simple.vert"), game::ShaderType::VERTEX};
        const auto fragment_shader = game::Shader{
            resource_loader.load_string("simple.frag"), game::ShaderType::FRAGMENT
        };
        const auto material = game::Material{vertex_shader, fragment_shader};
        const auto mesh = game::Mesh{};
        const auto renderer = game::Renderer{};

        auto entities = std::vector<game::Entity>{};

        for (auto i = -10; i < 10; ++i)
        {
            for (auto j = -10; j < 10; ++j)
            {
                entities.emplace_back(
                    &mesh, &material, game::Vector3{static_cast<float>(i) * 2.5f, -3.0f, static_cast<float>(j) * 2.5f},
                    &texture, &sampler
                );
            }
        }

        //        for (auto i = -15; i < 15; ++i) {
        //            for (auto j = -15; j < 15; ++j) {
        //                float distFromCenter = std::sqrt(i*i + j*j);
        //
        //                float height = -3.0f;
        //                if (distFromCenter < 10.0f) {
        //                    height += (10.0f - distFromCenter) * 0.5f;
        //                }
        //
        //                entities.emplace_back(
        //                        &mesh, &material,
        //                        game::Vector3{static_cast<float>(i) * 2.5f, height, static_cast<float>(j) * 2.5f});
        //            }
        //        }

        // int radius = 5;

        // for (int x = -radius; x <= radius; x += 1) {
        //     for (int y = -radius; y <= radius; y += 1) {
        //         for (int z = -radius; z <= radius; z += 1) {
        //             float distSquared = x * x + y * y + z * z;

        //             if (distSquared <= radius * radius) {
        //                 entities.emplace_back(
        //                     &mesh, &material,
        //                     game::Vector3{static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)},
        //                     &texture, &sampler);
        //             }
        //         }
        //     }
        // }

        auto scene = game::Scene{
            entities | std::views::transform([](const auto &e) { return &e; }) | std::ranges::to<std::vector<const
                game::Entity *> >(),
            {0.1f, 0.1f, 0.1f},
            {{-1.1f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.0f, 3.0f, 0.0f}, {0.5f, 0.5f, 0.5f}}
        };

        auto camera = game::Camera{
            {0.0f, 0.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.1f, 100.0f
        };

        std::unordered_map<game::Key, bool> key_state;

        auto running = true;
        while (running)
        {
            auto event = window.pump_event(); // TODO: Change to do while
            while (event && running)
            {
                std::visit(
                    [&](auto &&arg) // TODO: this is not good, it should be changed
                    {
                        using T = std::decay_t<decltype(arg)>;

                        if constexpr (std::same_as<T, game::StopEvent>)
                        {
                            running = false;
                        }
                        else if constexpr (std::same_as<T, game::KeyEvent>)
                        {
                            if (arg.key() == game::Key::ESC)
                            {
                                running = false;
                            }
                            else
                            {
                                key_state[arg.key()] = arg.state() == game::KeyState::DOWN;
                            }
                        }
                        else if constexpr (std::same_as<T, game::MouseEvent>)
                        {
                            static constexpr auto sensitivity = float{0.01f};
                            const auto delta_x = arg.delta_x() * sensitivity;
                            const auto delta_y = arg.delta_y() * sensitivity;
                            camera.adjust_yaw(delta_x);
                            camera.adjust_pitch(-delta_y);
                        }
                    }, *event
                );
                event = window.pump_event();
            }

            auto walk_direction = game::Vector3{0.0f, 0.0f, 0.0f};

            if (key_state[game::Key::W])
            {
                walk_direction += camera.direction();
            }

            if (key_state[game::Key::S])
            {
                walk_direction -= camera.direction();
            }

            if (key_state[game::Key::A])
            {
                walk_direction -= camera.right();
            }

            if (key_state[game::Key::D])
            {
                walk_direction += camera.right();
            }

            static constexpr auto speed = 0.03f;
            camera.translate(game::Vector3::normalize(walk_direction) * speed);

            static auto t = 0.0f;
            t += 0.002f;

            scene.point.position.x = std::sin(t) * 10.0f;
            scene.point.position.z = std::cos(t) * 10.0f;

            renderer.render(camera, scene);
            window.swap();
        }
    }
    catch (const game::Exception &err)
    {
        std::println(std::cerr, "{}", err);
    } catch (...)
    {
        std::println(std::cerr, "unknown error");
    }

    return 0;
}
