cmake_minimum_required(VERSION 3.24)
project(OOD_1)

set(CMAKE_CXX_STANDARD 20)


add_executable(ShapesOut part2/main.cpp
        part2/Picture/Picture.cpp
        part2/Canvas/PNGCanvas.cpp
        part2/Commands/ShapesCommandProcessor.cpp)


include_directories(part2/Canvas/stb_image_write.h)
include_directories(part2/Canvas/stb_truetype.h.h)


# Add include directories for FreeType
target_include_directories(ShapesOut PRIVATE part2/Canvas/ft2build.h)

add_executable(FuncDuck part1/FuncSimUDuck/SimUDuck.cpp)
add_executable(SimDuck part1/SimUDuck/SimUDuck.cpp)

enable_testing()

# Use FetchContent to pull in GoogleTest and GoogleMock from GitHub
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # Choose an appropriate release tag or branch
)

# Make sure GTest is available for use
FetchContent_MakeAvailable(googletest)

# Add the GTest and GMock targets to the project
add_executable(ShapeTests
        part2/Tests/ShapeTest.cpp
        part2/Tests/PictureTest.cpp
        )



target_link_libraries(ShapeTests PRIVATE Shapes gtest gmock gtest_main)

# Add the test executable as a CMake test
add_test(NAME ShapeTests COMMAND ShapeTests)