//
// Copyright 2025 scholar-of-artifice
//
// Licensed under the MIT License
//
// Copyright (c) 2025 scholar-of-artifice
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

#ifndef GAME_DICE_CPP_SRC_DICE_H
#define GAME_DICE_CPP_SRC_DICE_H

#include <limits>

namespace game_dice {

// An immutable descriptor of a die geometry.
// The Dice class represents the physical properties of a dice (number of
// sides). It is a lightweight, data-oriented structure that contains no rolling
// logic or mutable state.
class Dice {
 private:
  // The number of faces on this die.
  int num_sides_;

 public:
  // Constructs a Dice with a specified number of sides.
  //
  // The number of sides is automatically clamped to a safe range.
  //
  // sides: The number of sides.
  //  - minimum: 2 (example: a coin)
  //  - maximum std::numeric_limits<int>::max() - 1
  constexpr explicit Dice(int sides)
    : num_sides_((sides < 2)? 2
      : (sides >= std::numeric_limits<int>::max())
        ? (std::numeric_limits<int>::max() - 1)
        : sides ) {}
  // Retrieves the number of sides.
  [[nodiscard]] constexpr int GetNumSides() const noexcept {
    return num_sides_; }
};

}  // namespace game_dice

#endif  // GAME_DICE_CPP_SRC_DICE_H
