cmake_minimum_required(VERSION 3.20)

project(ARTracker VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Place the executable at the top of the build directory (e.g. build/ARTracker)
# instead of mirroring the source layout (build/src/ARTracker).
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
