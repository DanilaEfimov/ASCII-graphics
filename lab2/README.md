# Segment Rotation

A C++17 application that visualizes a line segment rotating around a fixed point using SFML.

## Requirements

- C++17 compiler
- CMake 3.16 or later
- SFML 2.x

If SFML is not installed, the CMake configuration downloads SFML 2.6.1 using `FetchContent` (an internet connection is required).

## Build and Run

```bash
cmake -S . -B build
cmake --build build -j
./build/lab2_rotation
```

## Usage

At startup, enter:

1. The coordinates of the first endpoint (`x1 y1`).
2. The coordinates of the second endpoint (`x2 y2`).
3. The rotation center (`cx cy`).
4. The angular velocity in degrees per second.

Coordinates are specified in pixels relative to the top-left corner of the window. Press `Esc` or close the window to exit.

## Implementation

Both endpoints are rotated around the specified center using the 2D rotation matrix. The animation uses the elapsed frame time (`delta time`), so the angular velocity is independent of the frame rate.

## Project Structure

```text
.
├── CMakeLists.txt
├── README.md
├── .gitignore
└── src/
    └── main.cpp
```
