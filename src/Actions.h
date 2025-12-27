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

#ifndef GAME_DICE_CPP_SRC_ACTION_H
#define GAME_DICE_CPP_SRC_ACTION_H
#include <random>

#include "Dice.h"

namespace game_dice {

// Roll a die to generate a random value.
//
// This function creates a uniform integer distribution based on the die
// geometry and uses the provided engine to select a result.
//
// die: The die to roll (defines the range [1, N])
// engine: A C++ STL compatible random number engine
template <typename Engine>
[[nodiscard]] int roll(const Dice& die, Engine& engine) {
  // create the uniform distribution from 1->N on the stack
  std::uniform_int_distribution<int> distribution(1, die.GetNumSides());
  // pull a number from the distribution using the provided entropy source
  return distribution(engine);
}

}  // namespace game_dice

#endif  // GAME_DICE_CPP_SRC_ACTION_H
