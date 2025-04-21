#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace game
{
class ResourceLoader
{
public:
    ResourceLoader(const std::filesystem::path &root);

    std::string load_string(std::string_view name) const;

    std::vector<std::byte> load_binary(std::string_view name) const;

private:
    std::filesystem::path root_;
};
}
