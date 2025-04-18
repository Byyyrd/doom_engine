cmake_minimum_required(VERSION 3.10.0)

project(Doom_Engine VERSION 0.1.0 LANGUAGES C)

find_package(SDL2 REQUIRED)
include_directories(Doom_Engine ${SDL2_INCLUDE_DIRS})

add_executable(Doom_Engine
    src/main.c
    src/state.c
    src/state.h
)

target_link_libraries(Doom_Engine ${SDL2_LIBRARIES} m)

