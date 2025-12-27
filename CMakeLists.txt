# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# name the project
project(game_dice_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# add my own executable
# do not include test files here.
add_executable(
        game_code
        main.cpp
        src/Dice.h)

# --- the tests live here ---
add_subdirectory(Google_tests)