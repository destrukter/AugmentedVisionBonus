cmake_minimum_required(VERSION 3.20)

project(ARTracker)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(assimp REQUIRED)
find_package(OGRE REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

add_executable(ARTracker
    src/main.cpp
)

target_link_libraries(ARTracker
    ${OpenCV_LIBS}
    assimp
    OgreMain
)