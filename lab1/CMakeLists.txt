cmake_minimum_required(VERSION 3.10)
project(Sculptor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sculptor main.cpp)

target_include_directories(sculptor INTERFACE include)
