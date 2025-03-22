#pragma once

#include <ranges>
#include <functional>

namespace game
{
template<class T, T Invalid = {}>
class AutoRelease
{
public:
    AutoRelease()
        : AutoRelease(Invalid, nullptr)
    {
    }

    AutoRelease(T obj, std::function<void(T)> deleter)
        : obj_(obj),
          deleter_(deleter)
    {
    }

    ~AutoRelease()
    {
        if (deleter_ && obj_ != Invalid) {
            deleter_(obj_);
        }
    }

    AutoRelease(const AutoRelease &) = delete;

    auto operator=(const AutoRelease &) -> AutoRelease & = delete;

    AutoRelease(AutoRelease &&other) noexcept
        : AutoRelease()
    {
        swap(other);
    }

    auto operator=(AutoRelease &&other) noexcept -> AutoRelease &
    {
        AutoRelease new_obj{std::move(other)};
        swap(new_obj);

        return *this;
    }

    auto swap(AutoRelease &other) noexcept -> void
    {
        std::ranges::swap(obj_, other.obj_);
        std::ranges::swap(deleter_, other.deleter_);
    }

    T get() const
    {
        return obj_;
    }

    operator T() const
    {
        return obj_;
    }

    explicit operator bool() const
    {
        return obj_ != Invalid;
    }

    T *operator&() noexcept
    {
        return std::addressof(obj_);
    }

private:
    T obj_;
    std::function<void(T)> deleter_;
};
}
