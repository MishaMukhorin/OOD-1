cmake_minimum_required(VERSION 3.28)
project(OOD_1)

set(CMAKE_CXX_STANDARD 20)


add_executable(ShapesOut part2/main.cpp
        part2/Picture.cpp
        part2/Canvas/PNGCanvas.cpp
        part2/Commands/ShapesCommandProcessor.cpp
        part2/Canvas/PNGCanvas.cpp)


include_directories(part2/Canvas/stb_image_write.h)
include_directories(part2/Canvas/stb_truetype.h.h)


# Add include directories for FreeType
target_include_directories(ShapesOut PRIVATE part2/Canvas/ft2build.h)

add_executable(FuncDuck part1/FuncSimUDuck/SimUDuck.cpp)
add_executable(SimDuck part1/SimUDuck/SimUDuck.cpp)
