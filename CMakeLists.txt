# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# name the project
project(game_dice_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define a library
add_library(
        game_dice_cpp
        INTERFACE
)
# tell the library where the header files are
target_include_directories(
        game_dice_cpp
        INTERFACE
        src
)

# define an executable
add_executable(
        game_code
        main.cpp
)
# link the library to the game_code executable
target_link_libraries(
        game_code
        PRIVATE
        game_dice_cpp
)

# --- the tests live here ---
add_subdirectory(Google_tests)