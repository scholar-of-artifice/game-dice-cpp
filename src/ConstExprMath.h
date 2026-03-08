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

#ifndef GAME_DICE_CPP_SRC_CONSTEXPRMATH_H
#define GAME_DICE_CPP_SRC_CONSTEXPRMATH_H

namespace game_dice_cpp {

// Compute base ^ exponent safely at compile-time.
// This relies on Exponentiation by Squaring for O(log N) Time Complexity.
[[nodiscard]] constexpr double RaisePower(double base, std::size_t exponent) {
  // edge cases
  if (exponent == 0) {
    return 1.0;
  }
  if (exponent == 1) {
    return base;
  }
  if (base == 0.0) {
    return 0.0;
  }
  // setup for algorithm
  double result = 1.0;
  double current_base = base;
  std::size_t current_exponent = exponent;
  // exponeniation process
  while (current_exponent > 0) {
    // if the current exponent is odd, multiply the result by current base
    if (current_exponent % 2 != 0) {
      result = result * current_base;
    }
    current_base = current_base * current_base;
    // square the base and halve the exponent for the next iteration
    current_exponent = current_exponent / 2;
  }
  return result;
}

}  // namespace game_dice_cpp

#endif  // GAME_DICE_CPP_SRC_CONSTEXPRMATH_H