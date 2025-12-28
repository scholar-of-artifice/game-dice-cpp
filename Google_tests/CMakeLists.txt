# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_test' is the subproject name
project(Google_tests)
# load the module FetchContent so further commands are available
include(FetchContent)
# Declare the external source, define the dependency but do not download it yet
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# checks if googletest is already downloaded
# # if not... download the zip and decompress
# # runs add_subdirectory on the downloaded folder
FetchContent_MakeAvailable(googletest)
# turn on testing so ctest command can be used
enable_testing()
# create the executable
add_executable(
        unit_test_suite
        tests/DiceTest.cpp
        tests/ActionsTest.cpp
        tests/DynamicProbabilityTableTest.cpp
)
# link the executable to the GoogleTest library
target_link_libraries(
        unit_test_suite
        GTest::gtest_main
        game_dice_cpp
)
# register the tests so ctest can find them
include(GoogleTest)
gtest_discover_tests(unit_test_suite)
