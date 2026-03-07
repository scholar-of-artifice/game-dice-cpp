# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# name the project
project(game_dice_cpp)

# define a library
add_library(
        game_dice_cpp
        INTERFACE
)

# enable strict compiler warnings
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU" )
    add_compile_options(
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
    )
endif ()

add_library(game_dev_cpp INTERFACE)

# tell the library where the header files are
target_include_directories(
        game_dice_cpp
        INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(
        game_dice_cpp
        INTERFACE
        cxx_std_23
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

# --- the tests/benchmarks live here ---
add_subdirectory(Google_tests)
add_subdirectory(Google_benchmarks)