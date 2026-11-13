#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <sys/epoll.h>


namespace {
// enabling non-lock mode
void _setup_nonblocking_stdin() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

// try listen
// returns -1 if stream is empty
int _get_char_if_available() {
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    return (n == 1) ? c : -1;
}

bool _is_key_pressed(int epfd) {
    struct epoll_event events[1];
    return epoll_wait(epfd, events, 1, 0) > 0;
}

}

class Listener {

public:
    Listener() {
        static bool nonlock_mode_enabled = false;
        if(!nonlock_mode_enabled)
            _setup_nonblocking_stdin();
    }

    bool is_key_pressed() const {
        return _is_key_pressed();
    }

    int get_char_if_available() const {
        return _get_char_if_available();
    }
};