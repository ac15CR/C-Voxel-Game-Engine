#include "window.h"

int main()
{

    game::Window window{800u, 600u};

    while (window.running()) {
    }

    return 0;
}
