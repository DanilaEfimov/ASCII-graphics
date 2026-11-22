cmake_minimum_required(VERSION 3.16)
project(Sculptor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Системный SFML 3 (Arch: `pacman -S sfml`), иначе скачиваем с GitHub
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    message(STATUS "System SFML 3 not found, fetching from GitHub")
    include(FetchContent)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON)
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(sculptor src/main.cpp)

target_include_directories(sculptor PRIVATE include)
target_link_libraries(sculptor PRIVATE SFML::Graphics)

if(NOT MSVC)
    target_compile_options(sculptor PRIVATE -Wall -Wextra -Wpedantic)
endif()
