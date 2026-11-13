#pragma once

#include "render.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

namespace {
    
    WindowSize current_window_size() {
        struct winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return WindowSize{w.ws_col, w.ws_row};
    }

}
