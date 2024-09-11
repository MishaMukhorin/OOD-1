cmake_minimum_required(VERSION 3.24)
project(OOD_1)

set(CMAKE_CXX_STANDARD 20)

# Main executable for Shapes
add_executable(ShapesOut
        part2/main.cpp
        part2/Picture/Picture.cpp
        part2/Canvas/PNGCanvas.cpp
        part2/Commands/ShapesCommandProcessor.cpp
)

# Include Canvas headers
include_directories(part2/Canvas)

# Additional executables
add_executable(FuncDuck part1/FuncSimUDuck/SimUDuck.cpp)
add_executable(SimDuck part1/SimUDuck/SimUDuck.cpp)

# Enable testing
enable_testing()

# Fetch GoogleTest and GoogleMock
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Add tests for Shapes
add_executable(ShapeTests
        part2/Tests/ShapeTest.cpp
        part2/Tests/PictureTest.cpp
        part2/Picture/Picture.cpp
        part2/Canvas/PNGCanvas.cpp
        part2/Commands/ShapesCommandProcessor.cpp
)

# Link libraries for tests
target_link_libraries(ShapeTests PRIVATE gtest gmock gtest_main)

# Ensure ShapesOut is built before ShapeTests
add_dependencies(ShapeTests ShapesOut)

# Add the test executable as a CMake test
add_test(NAME ShapeTests COMMAND ShapeTests)