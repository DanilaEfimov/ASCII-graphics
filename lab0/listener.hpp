#pragma once

#include <ncurses.h>
#include <optional>

class Listener {
public:
    Listener() { initscr(); cbreak(); noecho(); nodelay(stdscr, TRUE); }
    ~Listener() { endwin(); }

    std::optional<char> poll() {
        int c = getch();
        if (c == ERR) return std::nullopt;
        return static_cast<char>(c);
    }
};
