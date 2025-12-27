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

#include <gtest/gtest.h>

#include "../../src/Dice.h"

TEST(DiceConstructorTest, AssignsCorrectValueForValidInput) {
  // GIVEN an input number of sides z
  for (int z = 2; z <= 2'000'000; z++) {
    // WHEN a Dice is constructed
    const auto dz = game_dice::Dice(z);
    // THEN there are the correct number of sides
    EXPECT_EQ(dz.GetNumSides(), z)
        << "FAILURE: Unexpected number of sides for Dice(" << z << ").";
  }
}

TEST(DiceConstructorTest, AssignsCorrectValueForSmallInput) {
  // GIVEN an input number of sides z
  // AND z is <= 2
  for (int z = -2'000'000; z <= 2; z++) {
    // WHEN a Dice is constructed
    const auto dz = game_dice::Dice(z);
    // THEN there are the correct number of sides
    EXPECT_EQ(dz.GetNumSides(), 2)
        << "FAILURE: Unexpected number of sides for Dice(" << z << ").";
  }
}

TEST(DiceConstructorTest, AssignsCorrectValueForLargeInput) {
  // GIVEN an input number of sides z
  // AND z is the numeric limit of an int
  // WHEN a Dice is constructed
  const auto dz = game_dice::Dice(std::numeric_limits<int>::max());
  // THEN there are the correct number of sides
  EXPECT_EQ(dz.GetNumSides(), std::numeric_limits<int>::max() - 1)
      << "FAILURE: Unexpected number of sides for Dice(large_value).";
}
