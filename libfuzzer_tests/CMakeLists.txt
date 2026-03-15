# enforce the minimum standard version of cmake
cmake_minimum_required(VERSION 3.31)
# 'Google_test' is the subproject name
project(libfuzzer_tests)

# turn on testing so ctest command can be used
enable_testing()
# create the executables
add_executable(
        fuzz_asan_ubsan_dice
        fuzz_tests/fuzz_dice.cpp
)
add_executable(
        fuzz_asan_ubsan_actions_roll_dice
        fuzz_tests/fuzz_actions_roll_dice.cpp
)
# link the executable to the library
target_link_libraries(
        fuzz_asan_ubsan_dice
        PRIVATE
        game_dice_cpp
)
target_link_libraries(
        fuzz_asan_ubsan_actions_roll_dice
        PRIVATE
        game_dice_cpp
)
# apply the libfuzzer instrumentation flags to this specific target
# with ASan + UBSan
target_compile_options(fuzz_asan_ubsan_dice PRIVATE -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer)
target_link_options(fuzz_asan_ubsan_dice PRIVATE -fsanitize=fuzzer,address,undefined)
target_compile_options(fuzz_asan_ubsan_actions_roll_dice PRIVATE -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer)
target_link_options(fuzz_asan_ubsan_actions_roll_dice PRIVATE -fsanitize=fuzzer,address,undefined)
# register the fuzz test with CTest and enforce a 2 minute limit
add_test(
        NAME RunFuzzAsanUbsanDiceTarget
        COMMAND fuzz_asan_ubsan_dice -max_total_time=60 corpora/fuzz_dice
)
add_test(
        NAME RunFuzzAsanUbsanActionsRollDiceTarget
        COMMAND fuzz_asan_ubsan_actions_roll_dice -max_total_time=60 corpora/fuzz_actions_roll_dice
)