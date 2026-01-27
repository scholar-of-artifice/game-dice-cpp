# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_benchmarks' is the subproject name
project(Google_benchmarks)
# load the module FetchContent so further commands are available
include(FetchContent)
# Declare the external source, define the dependency but do not download it yet
FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
)
# checks if googlebenchmark is already downloaded
# # if not... download the zip and decompress
# # runs add_subdirectory on the downloaded folder
FetchContent_MakeAvailable(googlebenchmark)
# turn on testing so ctest command can be used
enable_testing()
# create the executable
add_executable(
        benchmark_suite
        benchmarks/DiceBenchmarks.cpp
        benchmarks/ActionsBenchmarks.cpp
)
# link the executable to the GoogleBenchmark library
target_link_libraries(
        benchmark_suite
        PRIVATE
        benchmark::benchmark_main
        game_dice_cpp
)
