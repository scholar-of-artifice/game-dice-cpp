# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_test' is the subproject name
project(libfuzzer_tests)

# create the executables
add_executable(
        fuzz_dice
        fuzz_tests/fuzz_dice.cpp
)
add_executable(
        fuzz_actions_roll_dice
        fuzz_tests/fuzz_actions_roll_dice.cpp
)
# link the executable to the library
target_link_libraries(
        fuzz_dice
        PRIVATE
        game_dice_cpp
)
target_link_libraries(
        fuzz_actions_roll_dice
        PRIVATE
        game_dice_cpp
)
# apply the libfuzzer instrumentation flags to this specific target
target_compile_options(fuzz_dice PRIVATE -fsanitize=fuzzer)
target_link_options(fuzz_dice PRIVATE -fsanitize=fuzzer)
target_compile_options(fuzz_actions_roll_dice PRIVATE -fsanitize=fuzzer)
target_link_options(fuzz_actions_roll_dice PRIVATE -fsanitize=fuzzer)
# register the fuzz test with CTest and enforce a 2 minute limit
add_test(
        NAME RunFuzzTarget
        COMMAND fuzz_dice -max_total_time=60
)
add_test(
        NAME RunFuzzTarget
        COMMAND fuzz_actions_roll_dice -max_total_time=60
)