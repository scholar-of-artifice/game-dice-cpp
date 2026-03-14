# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_test' is the subproject name
project(libfuzzer_tests)

# create the executable
add_executable(
        fuzz_target
        fuzz_target.cpp
)
# link the executable to the GoogleTest library
target_link_libraries(
        fuzz_target
        PRIVATE
        game_dice_cpp
)
# apply the libfuzzer instrumentation flags to this specific target
target_compile_options(fuzz_target PRIVATE -fsanitize=fuzzer)
target_link_options(fuzz_target PRIVATE -fsanitize=fuzzer)

