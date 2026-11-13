#pragma once

#include "render.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

namespace {
    
    struct WindowSize {
        std::size_t width;
        std::size_t height;
    };

    WindowSize current_window_size() {
        struct winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return WindowSize{w.ws_col, w.ws_row};
    }

}
