cmake_minimum_required(VERSION 3.16)
project(lab2_rotation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system QUIET)
if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
    )
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(lab2_rotation src/main.cpp)
target_link_libraries(lab2_rotation PRIVATE sfml-graphics sfml-window sfml-system)
