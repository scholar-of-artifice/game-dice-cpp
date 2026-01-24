//
// Copyright 2026 scholar-of-artifice
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

#include <iostream>
#include <random>

#include "src/Actions.h"
#include "src/Dice.h"

int main() {
  std::cout << "Hello, world from game-dice-cpp!" << std::endl;
  // make a d7
  auto d7 = game_dice_cpp::Dice(7);
  std::cout << "I have a shiny " << d7.GetNumSides() << "-sided die!"
            << std::endl;
  // create a random number generator
  std::mt19937_64 rand_generator(43);
  // roll the dice a few times...
  for (auto i = 0; i < 3; i++) {
    auto result = game_dice_cpp::Roll(d7, rand_generator);
    std::cout << "\tRolled " << result << "!" << std::endl;
  }
}