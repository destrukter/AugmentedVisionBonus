set(ARTRACKER_SOURCES
    main.cpp
    core/Application.cpp
    assets/AssetManager.cpp
)

add_executable(ARTracker ${ARTRACKER_SOURCES})

target_include_directories(ARTracker
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(assimp REQUIRED)

# OGRE has different package names depending on platform/distros.
find_package(OGRE QUIET)
if(NOT OGRE_FOUND)
    find_package(Ogre REQUIRED)
endif()

target_link_libraries(ARTracker
    PRIVATE
        ${OpenCV_LIBS}
        Eigen3::Eigen
        assimp::assimp
)

if(TARGET OgreMain)
    target_link_libraries(ARTracker PRIVATE OgreMain)
elseif(TARGET OGRE::OgreMain)
    target_link_libraries(ARTracker PRIVATE OGRE::OgreMain)
endif()
