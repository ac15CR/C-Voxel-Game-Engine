#include "window.h"
#include "exception.h"
#include <print>
#include <iostream>

int main()
{
    try {

        game::Window window{800u, 600u};

        while (window.running()) {
        }
    } catch (const game::Exception &err) {
        std::println(std::cerr, "{}", err);
    } catch (...) {
        std::println(std::cerr, "unknown error");
    }

    return 0;
}
