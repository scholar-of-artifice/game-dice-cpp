# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_test' is the subproject name
project(game_dice_benchmarks)
# load the module FetchContent so further commands are available
include(FetchContent)
# do not look for googlebenchmark
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
# do not build googlebenchmark own tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
# do not install googlebenchmark
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
# Declare the external source, define the dependency but do not download it yet
FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.4
)
# checks if googlebenchmark is already downloaded
FetchContent_MakeAvailable(
        googlebenchmark
)
# create the executable
add_executable(
        game_dice_benchmarks
        benchmarks/StaticProbabilityTableBenchmark.cpp
)
#
target_compile_definitions(
        game_dice_benchmarks
        PRIVATE
        BENCHMARK_DISABLE_CLOCK
        BENCHMARK_DISABLE_THREAD_AFFINITY

)
# link to the library and the benchmark library
target_link_libraries(
        game_dice_benchmarks
        PRIVATE
        benchmark::benchmark
        game_dice_cpp
)