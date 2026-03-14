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

#include "Dice.h"

// this is the standard entry point for libFuzzer
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // need at least enough bytes to form an integer
  if (size < sizeof(int)) {
    return 0; // not enough data... tell libfuzzer to try again
  }
  // safely extract an integer from the fuzzer data
  int fuzz_sides;
  std::memcpy(&fuzz_sides, data, sizeof(int));
  // feed the fuzzed integer into the target class
  game_dice_cpp::Dice dice(fuzz_sides);
  // call the getter to ensure that code path is excercise as well
  // mark so compiler does not complain about unused variables
  [[maybe_unused]] int actual_sides = dice.GetNumSides();
  // return 0 to indicate successful execution of target
  return 0;
}

