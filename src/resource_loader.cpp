#include "resource_loader.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "error.h"

namespace
{
std::string load(const std::filesystem::path &path, auto open_mode)
{
    std::ifstream file{path, open_mode};
    game::ensure(!!file, "failed to open file"); // Use !! to convert to boolean

    std::stringstream strm{};
    strm << file.rdbuf();

    return strm.str();
}
}

namespace game
{
ResourceLoader::ResourceLoader(const std::filesystem::path &root) // TODO: change to rvalue and use std::move?
    : root_(root)
{
}

std::string ResourceLoader::load_string(const std::string_view name) const
{
    return load(root_ / name, std::ios::in); // division is overloaded for path concatenation
}

std::vector<std::byte> ResourceLoader::load_binary(std::string_view name) const
{
    const auto data = load(root_ / name, std::ios::in | std::ios::binary);
    return data | std::views::transform([](auto b) { return static_cast<std::byte>(b); }) | std::ranges::to<
               std::vector>();
}
}
