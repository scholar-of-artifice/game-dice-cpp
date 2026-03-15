//
// Copyright 2026 scholar-of-artifice
//
// Licensed under the MIT License
//
// Copyright (c) 2026 scholar-of-artifice
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>
#include <cstddef>
#include <cstring>

#include "Actions.h"
#include "Dice.h"

// this is the standard entry point for libFuzzer
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // need at least enough bytes to form the dice size and the input seed
  if (size < sizeof(int) + sizeof(uint64_t)) {
    return 0; // not enough data... tell libfuzzer to try again
  }
  // safely extract some data from the fuzzer result
  int fuzz_sides;
  std::memcpy(&fuzz_sides, data, sizeof(int));
  uint64_t fuzz_seed;
  std::memcpy(&fuzz_seed, data + sizeof(int), sizeof(uint64_t));
  // feed the fuzzed data into the target input variables
  std::mt19937_64 rand_generator(fuzz_seed);
  game_dice_cpp::Dice dice(fuzz_sides);
  // call the function to ensure that code path is excercised as well
  // mark so compiler does not complain about unused variables
  [[maybe_unused]] auto result = game_dice_cpp::Roll(dice, rand_generator);
  // return 0 to indicate successful execution of target
  return 0;
}

