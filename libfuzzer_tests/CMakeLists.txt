# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_test' is the subproject name
project(libfuzzer_tests)

# create the executable
add_executable(
        fuzz_dice
        fuzz_dice.cpp
)
# link the executable to the GoogleTest library
target_link_libraries(
        fuzz_dice
        PRIVATE
        game_dice_cpp
)
# apply the libfuzzer instrumentation flags to this specific target
target_compile_options(fuzz_dice PRIVATE -fsanitize=fuzzer)
target_link_options(fuzz_dice PRIVATE -fsanitize=fuzzer)
# register the fuzz test with CTest and enforce a 2 minute limit
add_test(
        NAME RunFuzzDice
        COMMAND fuzz_dice -max_total_time=120
)